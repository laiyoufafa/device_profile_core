/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "content_sensor_manager.h"

#include "device_info_collector.h"
#include "device_profile_log.h"
#include "system_info_collector.h"

namespace OHOS {
namespace DeviceProfile {
namespace {
const std::string TAG = "ContentSensorManager";
}

IMPLEMENT_SINGLE_INSTANCE(ContentSensorManager);

bool ContentSensorManager::Init()
{
    auto runner = AppExecFwk::EventRunner::Create("csCollector");
    csCollectorHandler_ = std::make_shared<AppExecFwk::EventHandler>(runner);
    if (csCollectorHandler_ == nullptr) {
        return false;
    }
    return Collect();
}

bool ContentSensorManager::Collect()
{
    auto csTask = []() {
        HILOGI("ContentSensorManager Collect");
        std::list<std::shared_ptr<ContentCollector>> taskList;
        taskList.push_back(std::make_shared<DeviceInfoCollector>());
        taskList.push_back(std::make_shared<SystemInfoCollector>());
        for (auto& task : taskList) {
            ServiceCharacteristicProfile profileData;
            task->ConvertToProfileData(profileData);
            task->DoCollect(profileData);
        }
    };
    if (!csCollectorHandler_->PostTask(csTask)) {
        HILOGE("post task failed");
        return false;
    }
    return true;
}
} // namespace DeviceProfile
} // namespace OHOS