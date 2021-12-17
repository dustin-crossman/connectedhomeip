/**
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/****************************************************************************
 * @file
 * @brief Routines for the Door Lock Server plugin.
 *******************************************************************************
 ******************************************************************************/

#include "door-lock-server.h"
#include <app-common/zap-generated/attribute-id.h>
#include <app-common/zap-generated/attribute-type.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/callback.h>
#include <app-common/zap-generated/cluster-id.h>
#include <app-common/zap-generated/command-id.h>
#include <app/util/af-event.h>
#include <app/util/af.h>
#include <app/util/time-util.h>

#include <app/CommandHandler.h>
#include <app/ConcreteAttributePath.h>
#include <app/ConcreteCommandPath.h>
#include <lib/support/CodeUtils.h>

using namespace chip;
using namespace chip::app::Clusters::DoorLock;

EmberEventControl emberAfPluginDoorLockServerLockoutEventControl;
EmberEventControl emberAfPluginDoorLockServerRelockEventControl;

DoorLockServer DoorLockServer::instance;

// TODO: Remove hardcoded pin when SetCredential command is implemented.
chip::ByteSpan mPin({ 1, 2, 3, 4 });

/**********************************************************
 * DoorLockServer Implementation
 *********************************************************/

DoorLockServer & DoorLockServer::Instance()
{
    return instance;
}

/**
 * @brief Initializes given endpoint for a server.
 *
 * @param endpointId
 */
void DoorLockServer::InitServer(chip::EndpointId endpointId)
{
    emberAfDoorLockClusterPrintln("Door Lock cluster initialized at %d", endpointId);

    SetLockState(endpointId, DlLockState::kLocked);
    SetActuatorEnabled(endpointId, true);
}

bool DoorLockServer::SetLockState(chip::EndpointId endpointId, DlLockState newLockState)
{
    auto lockState = static_cast<uint8_t>(newLockState);

    emberAfDoorLockClusterPrintln("Setting Lock State to '%hhu'", lockState);

    auto status = Attributes::LockState::Set(endpointId, lockState);
    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        ChipLogError(Zcl, "Unable to set the Lock State to %hhu: internal error", lockState);
    }

    return status == EMBER_ZCL_STATUS_SUCCESS;
}

bool DoorLockServer::SetActuatorEnabled(chip::EndpointId endpointId, bool newActuatorState)
{
    auto actuatorState = static_cast<uint8_t>(newActuatorState);

    emberAfDoorLockClusterPrintln("Setting Actuator Enabled State to '%hhu'", actuatorState);

    auto status = Attributes::ActuatorEnabled::Set(endpointId, actuatorState);
    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        ChipLogError(Zcl, "Unable to set the Actuator Enabled State to %hhu: internal error", actuatorState);
    }

    return status == EMBER_ZCL_STATUS_SUCCESS;
}

bool DoorLockServer::SetDoorState(chip::EndpointId endpointId, DlLockState newDoorState)
{
    auto doorState = static_cast<uint8_t>(newDoorState);

    emberAfDoorLockClusterPrintln("Setting Door State to '%hhu'", doorState);
    auto status = Attributes::DoorState::Set(endpointId, doorState);

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        ChipLogError(Zcl, "Unable to set the Door State to %hhu: internal error", doorState);
    }

    return status == EMBER_ZCL_STATUS_SUCCESS;
}

bool DoorLockServer::SetLanguage(chip::EndpointId endpointId, const char * newLanguage)
{
    return true;
}

bool DoorLockServer::SetAutoRelockTime(chip::EndpointId endpointId, uint32_t newAutoRelockTimeSec)
{
    auto autoRelockTimeSec = static_cast<uint8_t>(newAutoRelockTimeSec);

    emberAfDoorLockClusterPrintln("Setting Auto Relock Time to '%hhu'", autoRelockTimeSec);
    auto status = Attributes::AutoRelockTime::Set(endpointId, autoRelockTimeSec);

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        ChipLogError(Zcl, "Unable to set the Auto Relock Time to %hhu: internal error", autoRelockTimeSec);
    }

    return status == EMBER_ZCL_STATUS_SUCCESS;
}

bool DoorLockServer::SetSoundVolume(chip::EndpointId endpointId, uint8_t newSoundVolume)
{
    return true;
}

bool DoorLockServer::SetOneTouchLocking(chip::EndpointId endpointId, bool isEnabled)
{
    return true;
}

bool DoorLockServer::SetPrivacyModeButton(chip::EndpointId endpointId, bool isEnabled)
{
    return true;
}

// =======================================================

bool emberAfDoorLockClusterLockDoorCallback(chip::app::CommandHandler * commandObj,
                                            const chip::app::ConcreteCommandPath & commandPath,
                                            const chip::app::Clusters::DoorLock::Commands::LockDoor::DecodableType & commandData)
{
    emberAfDoorLockClusterPrintln("Received Lock Door command");
    bool success = false;

    chip::EndpointId endpoint = commandPath.mEndpointId;

    bool require_pin = false;
    Attributes::RequirePINforRemoteOperation::Get(endpoint, &require_pin);

    if (commandData.pinCode.HasValue())
    {
        // TODO: Search through list of stored PINs and check each.
        if (mPin.data_equal(commandData.pinCode.Value()))
        {
            success = emberAfPluginDoorLockOnDoorLockCommand(endpoint, commandData.pinCode);
        }
        else
        {
            success = false; // Just to be explicit. success == false at this point anyway
        }
    }
    else
    {
        if (!require_pin)
        {
            success = emberAfPluginDoorLockOnDoorLockCommand(endpoint, commandData.pinCode);
        }
        else
        {
            success = false;
        }
    }

    if (success)
    {
        success = DoorLockServer::Instance().SetLockState(endpoint, DlLockState::kLocked) == EMBER_ZCL_STATUS_SUCCESS;
    }

    emberAfSendImmediateDefaultResponse(success ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_FAILURE);

    return true;
}

bool emberAfDoorLockClusterUnlockDoorCallback(
    chip::app::CommandHandler * commandObj, const chip::app::ConcreteCommandPath & commandPath,
    const chip::app::Clusters::DoorLock::Commands::UnlockDoor::DecodableType & commandData)
{
    emberAfDoorLockClusterPrintln("Received Unlock Door command");
    bool success = false;

    chip::EndpointId endpoint = commandPath.mEndpointId;

    bool require_pin = false;
    Attributes::RequirePINforRemoteOperation::Get(endpoint, &require_pin);

    if (commandData.pinCode.HasValue())
    {
        // TODO: Search through list of stored PINs and check each.
        if (mPin.data_equal(commandData.pinCode.Value()))
        {
            success = emberAfPluginDoorLockOnDoorUnlockCommand(endpoint, commandData.pinCode);
        }
        else
        {
            success = false; // Just to be explicit. success == false at this point anyway
        }
    }
    else
    {
        if (!require_pin)
        {
            success = emberAfPluginDoorLockOnDoorUnlockCommand(endpoint, commandData.pinCode);
        }
        else
        {
            success = false;
        }
    }

    if (success)
    {
        success = DoorLockServer::Instance().SetLockState(endpoint, DlLockState::kUnlocked) == EMBER_ZCL_STATUS_SUCCESS;
    }

    emberAfSendImmediateDefaultResponse(success ? EMBER_ZCL_STATUS_SUCCESS : EMBER_ZCL_STATUS_FAILURE);

    return true;
}

bool emberAfDoorLockClusterSetUserCallback(chip::app::CommandHandler * commandObj,
                                           const chip::app::ConcreteCommandPath & commandPath,
                                           const chip::app::Clusters::DoorLock::Commands::SetUser::DecodableType & commandData)
{
    emberAfDoorLockClusterPrintln("Received Set User command (not implemented)");
    // SetUser command fields are:
    // DlDataOperationType operationType;
    // uint16_t userIndex;
    // DataModel::Nullable<chip::CharSpan> userName;
    // DataModel::Nullable<uint32_t> userUniqueId;
    // DlUserStatus userStatus;
    // DlUserType userType;
    // DlCredentialRule credentialRule;

    // TODO: Implement setting the user
    emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
    return true;
}

bool emberAfDoorLockClusterGetUserCallback(chip::app::CommandHandler * commandObj,
                                           const chip::app::ConcreteCommandPath & commandPath,
                                           const chip::app::Clusters::DoorLock::Commands::GetUser::DecodableType & commandData)
{
    emberAfDoorLockClusterPrintln("Received Get User command (not implemented)");
    // GetUser command fields are:
    // uint16_t userIndex;

    // TODO: Implement getting the user
    emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
    return true;
}

bool emberAfDoorLockClusterClearUserCallback(chip::app::CommandHandler * commandObj,
                                             const chip::app::ConcreteCommandPath & commandPath,
                                             const chip::app::Clusters::DoorLock::Commands::ClearUser::DecodableType & commandData)
{
    emberAfDoorLockClusterPrintln("Received Clear User command (not implemented)");
    // ClearUser command fields are:
    // uint16_t userIndex;

    // TODO: Implement clearing the user
    emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
    return true;
}

bool emberAfDoorLockClusterSetCredentialCallback(
    chip::app::CommandHandler * commandObj, const chip::app::ConcreteCommandPath & commandPath,
    const chip::app::Clusters::DoorLock::Commands::SetCredential::DecodableType & commandData)
{
    emberAfDoorLockClusterPrintln("Received Set Credential command (not implemented)");
    // SetCredential command fields are:
    // DlDataOperationType operationType;
    // Structs::DlCredential::Type credential;
    // chip::ByteSpan credentialData;
    // uint16_t userIndex;
    // DlUserStatus userStatus;

    // TODO: Implement clearing the user
    emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
    return true;
}

bool emberAfDoorLockClusterGetCredentialStatusCallback(
    chip::app::CommandHandler * commandObj, const chip::app::ConcreteCommandPath & commandPath,
    const chip::app::Clusters::DoorLock::Commands::GetCredentialStatus::DecodableType & commandData)
{
    emberAfDoorLockClusterPrintln("Received Get Credential Status command (not implemented)");
    // GetCredentialStatus command fields are:
    // Structs::DlCredential::Type credential;

    // TODO: Implement clearing the user
    emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
    return true;
}

bool emberAfDoorLockClusterClearCredentialCallback(
    chip::app::CommandHandler * commandObj, const chip::app::ConcreteCommandPath & commandPath,
    const chip::app::Clusters::DoorLock::Commands::ClearCredential::DecodableType & commandData)
{
    emberAfDoorLockClusterPrintln("Received Clear Credential command (not implemented)");
    // ClearCredential command fields are:
    // Structs::DlCredential::Type credential;

    // TODO: Implement clearing the user
    emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
    return true;
}

chip::Protocols::InteractionModel::Status
MatterDoorLockClusterServerPreAttributeChangedCallback(const chip::app::ConcreteAttributePath & attributePath,
                                                       EmberAfAttributeType attributeType, uint16_t size, uint8_t * value)
{
    // TODO: Implement attribute changes
    return chip::Protocols::InteractionModel::Status::Success;
}

void emberAfPluginDoorLockServerLockoutEventHandler(void) {}

void emberAfPluginDoorLockServerRelockEventHandler(void) {}

void MatterDoorLockPluginServerInitCallback()
{
    emberAfDoorLockClusterPrintln("Door Lock server initialized");
}

void MatterDoorLockClusterServerAttributeChangedCallback(const app::ConcreteAttributePath & attributePath) {}

bool __attribute__((weak))
emberAfPluginDoorLockOnDoorLockCommand(chip::EndpointId endpointId, chip::Optional<chip::ByteSpan> pinCode)
{
    return false;
}

bool __attribute__((weak))
emberAfPluginDoorLockOnDoorUnlockCommand(chip::EndpointId endpointId, chip::Optional<chip::ByteSpan> pinCode)
{
    return false;
}
