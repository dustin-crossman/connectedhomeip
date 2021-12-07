/*
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

// THIS FILE IS GENERATED BY ZAP

#include "CHIPClusters.h"

#include <app-common/zap-generated/ids/Attributes.h>
#include <zap-generated/CHIPClientCallbacks.h>

namespace chip {

using namespace app::Clusters;
using namespace System;
using namespace Encoding::LittleEndian;

namespace Controller {

// TODO(#4502): onCompletion is not used by IM for now.
// TODO(#4503): length should be passed to commands when byte string is in argument list.
// TODO(#4503): Commands should take group id as an argument.

// FlowMeasurement Cluster Commands
// FlowMeasurement Cluster Attributes
CHIP_ERROR FlowMeasurementCluster::SubscribeAttributeMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                   Callback::Cancelable * onFailureCallback, uint16_t minInterval,
                                                                   uint16_t maxInterval)
{
    chip::app::AttributePathParams attributePath;
    attributePath.mEndpointId  = mEndpoint;
    attributePath.mClusterId   = mClusterId;
    attributePath.mAttributeId = FlowMeasurement::Attributes::MeasuredValue::Id;
    return mDevice->SendSubscribeAttributeRequest(attributePath, minInterval, maxInterval, onSuccessCallback, onFailureCallback);
}

CHIP_ERROR FlowMeasurementCluster::ReportAttributeMeasuredValue(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(FlowMeasurement::Attributes::MeasuredValue::Id, onReportCallback,
                                     BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR FlowMeasurementCluster::SubscribeAttributeMinMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                      Callback::Cancelable * onFailureCallback,
                                                                      uint16_t minInterval, uint16_t maxInterval)
{
    chip::app::AttributePathParams attributePath;
    attributePath.mEndpointId  = mEndpoint;
    attributePath.mClusterId   = mClusterId;
    attributePath.mAttributeId = FlowMeasurement::Attributes::MinMeasuredValue::Id;
    return mDevice->SendSubscribeAttributeRequest(attributePath, minInterval, maxInterval, onSuccessCallback, onFailureCallback);
}

CHIP_ERROR FlowMeasurementCluster::ReportAttributeMinMeasuredValue(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(FlowMeasurement::Attributes::MinMeasuredValue::Id, onReportCallback,
                                     BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR FlowMeasurementCluster::SubscribeAttributeMaxMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                      Callback::Cancelable * onFailureCallback,
                                                                      uint16_t minInterval, uint16_t maxInterval)
{
    chip::app::AttributePathParams attributePath;
    attributePath.mEndpointId  = mEndpoint;
    attributePath.mClusterId   = mClusterId;
    attributePath.mAttributeId = FlowMeasurement::Attributes::MaxMeasuredValue::Id;
    return mDevice->SendSubscribeAttributeRequest(attributePath, minInterval, maxInterval, onSuccessCallback, onFailureCallback);
}

CHIP_ERROR FlowMeasurementCluster::ReportAttributeMaxMeasuredValue(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(FlowMeasurement::Attributes::MaxMeasuredValue::Id, onReportCallback,
                                     BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR FlowMeasurementCluster::SubscribeAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                                     Callback::Cancelable * onFailureCallback, uint16_t minInterval,
                                                                     uint16_t maxInterval)
{
    chip::app::AttributePathParams attributePath;
    attributePath.mEndpointId  = mEndpoint;
    attributePath.mClusterId   = mClusterId;
    attributePath.mAttributeId = Globals::Attributes::ClusterRevision::Id;
    return mDevice->SendSubscribeAttributeRequest(attributePath, minInterval, maxInterval, onSuccessCallback, onFailureCallback);
}

CHIP_ERROR FlowMeasurementCluster::ReportAttributeClusterRevision(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(Globals::Attributes::ClusterRevision::Id, onReportCallback,
                                     BasicAttributeFilter<Int16uAttributeCallback>);
}

// PressureMeasurement Cluster Commands
// PressureMeasurement Cluster Attributes
CHIP_ERROR PressureMeasurementCluster::SubscribeAttributeMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                       Callback::Cancelable * onFailureCallback,
                                                                       uint16_t minInterval, uint16_t maxInterval)
{
    chip::app::AttributePathParams attributePath;
    attributePath.mEndpointId  = mEndpoint;
    attributePath.mClusterId   = mClusterId;
    attributePath.mAttributeId = PressureMeasurement::Attributes::MeasuredValue::Id;
    return mDevice->SendSubscribeAttributeRequest(attributePath, minInterval, maxInterval, onSuccessCallback, onFailureCallback);
}

CHIP_ERROR PressureMeasurementCluster::ReportAttributeMeasuredValue(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(PressureMeasurement::Attributes::MeasuredValue::Id, onReportCallback,
                                     BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR PressureMeasurementCluster::SubscribeAttributeMinMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                          Callback::Cancelable * onFailureCallback,
                                                                          uint16_t minInterval, uint16_t maxInterval)
{
    chip::app::AttributePathParams attributePath;
    attributePath.mEndpointId  = mEndpoint;
    attributePath.mClusterId   = mClusterId;
    attributePath.mAttributeId = PressureMeasurement::Attributes::MinMeasuredValue::Id;
    return mDevice->SendSubscribeAttributeRequest(attributePath, minInterval, maxInterval, onSuccessCallback, onFailureCallback);
}

CHIP_ERROR PressureMeasurementCluster::ReportAttributeMinMeasuredValue(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(PressureMeasurement::Attributes::MinMeasuredValue::Id, onReportCallback,
                                     BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR PressureMeasurementCluster::SubscribeAttributeMaxMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                          Callback::Cancelable * onFailureCallback,
                                                                          uint16_t minInterval, uint16_t maxInterval)
{
    chip::app::AttributePathParams attributePath;
    attributePath.mEndpointId  = mEndpoint;
    attributePath.mClusterId   = mClusterId;
    attributePath.mAttributeId = PressureMeasurement::Attributes::MaxMeasuredValue::Id;
    return mDevice->SendSubscribeAttributeRequest(attributePath, minInterval, maxInterval, onSuccessCallback, onFailureCallback);
}

CHIP_ERROR PressureMeasurementCluster::ReportAttributeMaxMeasuredValue(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(PressureMeasurement::Attributes::MaxMeasuredValue::Id, onReportCallback,
                                     BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR PressureMeasurementCluster::SubscribeAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                                         Callback::Cancelable * onFailureCallback,
                                                                         uint16_t minInterval, uint16_t maxInterval)
{
    chip::app::AttributePathParams attributePath;
    attributePath.mEndpointId  = mEndpoint;
    attributePath.mClusterId   = mClusterId;
    attributePath.mAttributeId = Globals::Attributes::ClusterRevision::Id;
    return mDevice->SendSubscribeAttributeRequest(attributePath, minInterval, maxInterval, onSuccessCallback, onFailureCallback);
}

CHIP_ERROR PressureMeasurementCluster::ReportAttributeClusterRevision(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(Globals::Attributes::ClusterRevision::Id, onReportCallback,
                                     BasicAttributeFilter<Int16uAttributeCallback>);
}

// TemperatureMeasurement Cluster Commands
// TemperatureMeasurement Cluster Attributes
CHIP_ERROR TemperatureMeasurementCluster::SubscribeAttributeMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                          Callback::Cancelable * onFailureCallback,
                                                                          uint16_t minInterval, uint16_t maxInterval)
{
    chip::app::AttributePathParams attributePath;
    attributePath.mEndpointId  = mEndpoint;
    attributePath.mClusterId   = mClusterId;
    attributePath.mAttributeId = TemperatureMeasurement::Attributes::MeasuredValue::Id;
    return mDevice->SendSubscribeAttributeRequest(attributePath, minInterval, maxInterval, onSuccessCallback, onFailureCallback);
}

CHIP_ERROR TemperatureMeasurementCluster::ReportAttributeMeasuredValue(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(TemperatureMeasurement::Attributes::MeasuredValue::Id, onReportCallback,
                                     BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR TemperatureMeasurementCluster::SubscribeAttributeMinMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                             Callback::Cancelable * onFailureCallback,
                                                                             uint16_t minInterval, uint16_t maxInterval)
{
    chip::app::AttributePathParams attributePath;
    attributePath.mEndpointId  = mEndpoint;
    attributePath.mClusterId   = mClusterId;
    attributePath.mAttributeId = TemperatureMeasurement::Attributes::MinMeasuredValue::Id;
    return mDevice->SendSubscribeAttributeRequest(attributePath, minInterval, maxInterval, onSuccessCallback, onFailureCallback);
}

CHIP_ERROR TemperatureMeasurementCluster::ReportAttributeMinMeasuredValue(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(TemperatureMeasurement::Attributes::MinMeasuredValue::Id, onReportCallback,
                                     BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR TemperatureMeasurementCluster::SubscribeAttributeMaxMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                             Callback::Cancelable * onFailureCallback,
                                                                             uint16_t minInterval, uint16_t maxInterval)
{
    chip::app::AttributePathParams attributePath;
    attributePath.mEndpointId  = mEndpoint;
    attributePath.mClusterId   = mClusterId;
    attributePath.mAttributeId = TemperatureMeasurement::Attributes::MaxMeasuredValue::Id;
    return mDevice->SendSubscribeAttributeRequest(attributePath, minInterval, maxInterval, onSuccessCallback, onFailureCallback);
}

CHIP_ERROR TemperatureMeasurementCluster::ReportAttributeMaxMeasuredValue(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(TemperatureMeasurement::Attributes::MaxMeasuredValue::Id, onReportCallback,
                                     BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR TemperatureMeasurementCluster::SubscribeAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                                            Callback::Cancelable * onFailureCallback,
                                                                            uint16_t minInterval, uint16_t maxInterval)
{
    chip::app::AttributePathParams attributePath;
    attributePath.mEndpointId  = mEndpoint;
    attributePath.mClusterId   = mClusterId;
    attributePath.mAttributeId = Globals::Attributes::ClusterRevision::Id;
    return mDevice->SendSubscribeAttributeRequest(attributePath, minInterval, maxInterval, onSuccessCallback, onFailureCallback);
}

CHIP_ERROR TemperatureMeasurementCluster::ReportAttributeClusterRevision(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(Globals::Attributes::ClusterRevision::Id, onReportCallback,
                                     BasicAttributeFilter<Int16uAttributeCallback>);
}

} // namespace Controller
} // namespace chip
