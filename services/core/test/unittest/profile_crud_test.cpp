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

#include "gtest/gtest.h"

#include "utils.h"

#define private public
#define protected public
#include "device_profile_errors.h"
#include "distributed_device_profile_client.h"
#include "nlohmann/json.hpp"
#undef private
#undef protected

namespace OHOS {
namespace DeviceProfile {
using namespace testing;
using namespace testing::ext;

class ProfileCrudTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void ProfileCrudTest::SetUpTestCase()
{
}

void ProfileCrudTest::TearDownTestCase()
{
}

void ProfileCrudTest::SetUp()
{
}

void ProfileCrudTest::TearDown()
{
}

/**
 * @tc.name: PutDeviceProfile_001
 * @tc.desc: put device profile with empty service id
 * @tc.type: FUNC
 */
HWTEST_F(ProfileCrudTest, PutDeviceProfile_001, TestSize.Level0)
{
    auto dps = DistributedDeviceProfileClient::GetInstance().GetDeviceProfileService();
    if (dps == nullptr) {
        DTEST_LOG << "device profile service is nullptr" << std::endl;
        return;
    }

    ServiceCharacteristicProfile profile;
    profile.SetServiceId("");
    profile.SetServiceType("test");
    nlohmann::json j;
    j["testVersion"] = "3.0.0";
    j["testApiLevel"] = 7;
    profile.SetCharacteristicProfileJson(j.dump());
    int32_t result = DistributedDeviceProfileClient::GetInstance().PutDeviceProfile(profile);
    EXPECT_TRUE(result == ERR_DP_INVALID_PARAMS);
}

/**
 * @tc.name: PutDeviceProfile_002
 * @tc.desc: put device profile with empty service type
 * @tc.type: FUNC
 */
HWTEST_F(ProfileCrudTest, PutDeviceProfile_002, TestSize.Level0)
{
    auto dps = DistributedDeviceProfileClient::GetInstance().GetDeviceProfileService();
    if (dps == nullptr) {
        DTEST_LOG << "device profile service is nullptr" << std::endl;
        return;
    }

    ServiceCharacteristicProfile profile;
    profile.SetServiceId("test");
    profile.SetServiceType("");
    nlohmann::json j;
    j["testVersion"] = "3.0.0";
    j["testApiLevel"] = 7;
    profile.SetCharacteristicProfileJson(j.dump());
    int32_t result = DistributedDeviceProfileClient::GetInstance().PutDeviceProfile(profile);
    EXPECT_TRUE(result == ERR_DP_INVALID_PARAMS);
}

/**
 * @tc.name: PutDeviceProfile_003
 * @tc.desc: put device profile with empty characteristics
 * @tc.type: FUNC
 */
HWTEST_F(ProfileCrudTest, PutDeviceProfile_003, TestSize.Level0)
{
    auto dps = DistributedDeviceProfileClient::GetInstance().GetDeviceProfileService();
    if (dps == nullptr) {
        DTEST_LOG << "device profile service is nullptr" << std::endl;
        return;
    }

    ServiceCharacteristicProfile profile;
    profile.SetServiceId("test");
    profile.SetServiceType("test");
    nlohmann::json j;
    // the result string is "null"
    profile.SetCharacteristicProfileJson(j.dump());
    int32_t result = DistributedDeviceProfileClient::GetInstance().PutDeviceProfile(profile);
    EXPECT_TRUE(result == ERR_DP_INVALID_PARAMS);
}

/**
 * @tc.name: PutDeviceProfile_004
 * @tc.desc: put device profile without set characteristics
 * @tc.type: FUNC
 */
HWTEST_F(ProfileCrudTest, PutDeviceProfile_004, TestSize.Level0)
{
    auto dps = DistributedDeviceProfileClient::GetInstance().GetDeviceProfileService();
    if (dps == nullptr) {
        DTEST_LOG << "device profile service is nullptr" << std::endl;
        return;
    }

    ServiceCharacteristicProfile profile;
    profile.SetServiceId("test");
    profile.SetServiceType("test");
    int32_t result = DistributedDeviceProfileClient::GetInstance().PutDeviceProfile(profile);
    EXPECT_TRUE(result == ERR_DP_INVALID_PARAMS);
}

/**
 * @tc.name: DeleteDeviceProfile_001
 * @tc.desc: delete an empty profile
 * @tc.type: FUNC
 */
HWTEST_F(ProfileCrudTest, DeleteDeviceProfile_001, TestSize.Level0)
{
    auto dps = DistributedDeviceProfileClient::GetInstance().GetDeviceProfileService();
    if (dps == nullptr) {
        DTEST_LOG << "device profile service is nullptr" << std::endl;
        return;
    }

    int32_t result = DistributedDeviceProfileClient::GetInstance().DeleteDeviceProfile("");
    EXPECT_TRUE(result == ERR_DP_INVALID_PARAMS);
}
}
}