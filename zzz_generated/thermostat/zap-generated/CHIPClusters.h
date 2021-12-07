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

// Prevent multiple inclusion
#pragma once

#include <app-common/zap-generated/ids/Clusters.h>
#include <app-common/zap-generated/ids/Commands.h>

#include <controller/CHIPCluster.h>
#include <lib/core/CHIPCallback.h>
#include <lib/support/Span.h>

namespace chip {
namespace Controller {

class DLL_EXPORT IdentifyCluster : public ClusterBase
{
public:
    IdentifyCluster() : ClusterBase(app::Clusters::Identify::Id) {}
    ~IdentifyCluster() {}

    // Cluster Commands
    CHIP_ERROR Identify(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t identifyTime);
    CHIP_ERROR IdentifyQuery(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);

    // Cluster Attributes
    CHIP_ERROR SubscribeAttributeIdentifyTime(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                              uint16_t minInterval, uint16_t maxInterval);
    CHIP_ERROR ReportAttributeIdentifyTime(Callback::Cancelable * onReportCallback);
    CHIP_ERROR SubscribeAttributeIdentifyType(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                              uint16_t minInterval, uint16_t maxInterval);
    CHIP_ERROR ReportAttributeIdentifyType(Callback::Cancelable * onReportCallback);
    CHIP_ERROR SubscribeAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                                 uint16_t minInterval, uint16_t maxInterval);
    CHIP_ERROR ReportAttributeClusterRevision(Callback::Cancelable * onReportCallback);

private:
};

} // namespace Controller
} // namespace chip
