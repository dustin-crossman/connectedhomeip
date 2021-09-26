/**
 *
 *    Copyright (c) 2021 Project CHIP Authors
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

#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app/MessageDef/AttributeDataElement.h>
#include <app/util/attribute-storage.h>
#include <platform/PlatformManager.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::GeneralDiagnostics::Attributes;
using chip::DeviceLayer::PlatformManager;

namespace {

class GeneralDiagosticsAttrAccess : public AttributeAccessInterface
{
public:
    // Register for the GeneralDiagnostics cluster on all endpoints.
    GeneralDiagosticsAttrAccess() : AttributeAccessInterface(Optional<EndpointId>::Missing(), GeneralDiagnostics::Id) {}

    CHIP_ERROR Read(ClusterInfo & aClusterInfo, TLV::TLVWriter * aWriter, bool * aDataRead) override;

private:
    template <typename T>
    CHIP_ERROR ReadIfSupported(CHIP_ERROR (PlatformManager::*getter)(T &), TLV::TLVWriter * aWriter);
};

template <typename T>
CHIP_ERROR GeneralDiagosticsAttrAccess::ReadIfSupported(CHIP_ERROR (PlatformManager::*getter)(T &), TLV::TLVWriter * aWriter)
{
    T data;
    CHIP_ERROR err = (DeviceLayer::PlatformMgr().*getter)(data);
    if (err == CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE)
    {
        data = 0;
    }
    else if (err != CHIP_NO_ERROR)
    {
        return err;
    }

    return aWriter->Put(TLV::ContextTag(AttributeDataElement::kCsTag_Data), data);
}

GeneralDiagosticsAttrAccess gAttrAccess;

CHIP_ERROR GeneralDiagosticsAttrAccess::Read(ClusterInfo & aClusterInfo, TLV::TLVWriter * aWriter, bool * aDataRead)
{
    if (aClusterInfo.mClusterId != GeneralDiagnostics::Id)
    {
        // We shouldn't have been called at all.
        return CHIP_ERROR_INVALID_ARGUMENT;
    }

    *aDataRead = true;
    switch (aClusterInfo.mFieldId)
    {
    case Ids::RebootCount: {
        return ReadIfSupported(&PlatformManager::GetRebootCount, aWriter);
    }
    case Ids::UpTime: {
        return ReadIfSupported(&PlatformManager::GetUpTime, aWriter);
    }
    case Ids::TotalOperationalHours: {
        return ReadIfSupported(&PlatformManager::GetTotalOperationalHours, aWriter);
    }
    case Ids::BootReasons: {
        return ReadIfSupported(&PlatformManager::GetBootReasons, aWriter);
    }
    default: {
        *aDataRead = false;
        break;
    }
    }
    return CHIP_NO_ERROR;
}
} // anonymous namespace

void emberAfGeneralDiagnosticsClusterServerInitCallback(EndpointId endpoint)
{
    static bool attrAccessRegistered = false;
    if (!attrAccessRegistered)
    {
        registerAttributeAccessOverride(&gAttrAccess);
        attrAccessRegistered = true;
    }
}
