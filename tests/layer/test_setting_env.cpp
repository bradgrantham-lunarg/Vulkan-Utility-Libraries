// Copyright 2023 The Khronos Group Inc.
// Copyright 2023 Valve Corporation
// Copyright 2023 LunarG, Inc.
//
// SPDX-License-Identifier: Apache-2.0
//
// Author(s):
// - Christophe Riccio <christophe@lunarg.com>

#include <gtest/gtest.h>

#include "vulkan/layer/vk_layer_settings.h"
#include <vector>
#include <cstdlib>

static void SetEnv(const char* value) {
#ifdef _WIN32
    _putenv(value);
#else
    putenv(const_cast<char *>(value));
#endif
}

TEST(test_layer_setting_env, EnvVar_TrimNone) {
    SetEnv("VK_LUNARG_TEST_MY_SETTING_A=true,false");

    VlLayerSettingSet layerSettingSet = VK_NULL_HANDLE;
    vlCreateLayerSettingSet("VK_LAYER_LUNARG_test", nullptr, nullptr, nullptr, &layerSettingSet);

    EXPECT_TRUE(vlHasLayerSetting(layerSettingSet, "my_setting_a"));

    uint32_t value_count_a = 0;
    VkResult result_count_a =
        vlGetLayerSettingValues(layerSettingSet, "my_setting_a", VL_LAYER_SETTING_TYPE_BOOL32, &value_count_a, nullptr);
    EXPECT_EQ(VK_SUCCESS, result_count_a);
    EXPECT_EQ(2, value_count_a);

    std::vector<VkBool32> values_a(static_cast<std::size_t>(value_count_a));
    VkResult result_complete_a =
        vlGetLayerSettingValues(layerSettingSet, "my_setting_a", VL_LAYER_SETTING_TYPE_BOOL32, &value_count_a, &values_a[0]);
    EXPECT_EQ(VK_SUCCESS, result_complete_a);
    EXPECT_EQ(VK_TRUE, values_a[0]);
    EXPECT_EQ(VK_FALSE, values_a[1]);
    EXPECT_EQ(2, value_count_a);

    vlDestroyLayerSettingSet(layerSettingSet, nullptr);
}

TEST(test_layer_setting_env, EnvVar_TrimVendor) {
    SetEnv("VK_TEST_MY_SETTING_B=true,false");

    VlLayerSettingSet layerSettingSet = VK_NULL_HANDLE;
    vlCreateLayerSettingSet("VK_LAYER_LUNARG_test", nullptr, nullptr, nullptr, &layerSettingSet);

    EXPECT_TRUE(vlHasLayerSetting(layerSettingSet, "my_setting_b"));

    uint32_t value_count_b = 0;
    VkResult result_count_b =
        vlGetLayerSettingValues(layerSettingSet, "my_setting_b", VL_LAYER_SETTING_TYPE_BOOL32, &value_count_b, nullptr);
    EXPECT_EQ(VK_SUCCESS, result_count_b);
    EXPECT_EQ(2, value_count_b);

    std::vector<VkBool32> values_b(static_cast<std::size_t>(value_count_b));
    VkResult result_complete_b =
        vlGetLayerSettingValues(layerSettingSet, "my_setting_b", VL_LAYER_SETTING_TYPE_BOOL32, &value_count_b, &values_b[0]);
    EXPECT_EQ(VK_SUCCESS, result_complete_b);
    EXPECT_EQ(VK_TRUE, values_b[0]);
    EXPECT_EQ(VK_FALSE, values_b[1]);
    EXPECT_EQ(2, value_count_b);

    vlDestroyLayerSettingSet(layerSettingSet, nullptr);
}

TEST(test_layer_setting_env, EnvVar_TrimNamespace) {
    SetEnv("VK_MY_SETTING_C=true,false");

    VlLayerSettingSet layerSettingSet = VK_NULL_HANDLE;
    vlCreateLayerSettingSet("VK_LAYER_LUNARG_test", nullptr, nullptr, nullptr, &layerSettingSet);

    EXPECT_TRUE(vlHasLayerSetting(layerSettingSet, "my_setting_c"));

    uint32_t value_count_c = 0;
    VkResult result_count_c =
        vlGetLayerSettingValues(layerSettingSet, "my_setting_c", VL_LAYER_SETTING_TYPE_BOOL32, &value_count_c, nullptr);
    EXPECT_EQ(VK_SUCCESS, result_count_c);
    EXPECT_EQ(2, value_count_c);

    std::vector<VkBool32> values_c(static_cast<std::size_t>(value_count_c));
    VkResult result_complete_c =
        vlGetLayerSettingValues(layerSettingSet, "my_setting_c", VL_LAYER_SETTING_TYPE_BOOL32, &value_count_c, &values_c[0]);
    EXPECT_EQ(VK_SUCCESS, result_complete_c);
    EXPECT_EQ(VK_TRUE, values_c[0]);
    EXPECT_EQ(VK_FALSE, values_c[1]);
    EXPECT_EQ(2, value_count_c);

    vlDestroyLayerSettingSet(layerSettingSet, nullptr);
}

TEST(test_layer_setting_env, vlGetLayerSettingValues_Bool) {
    SetEnv("VK_LUNARG_TEST_MY_SETTING=true,false");

    VlLayerSettingSet layerSettingSet = VK_NULL_HANDLE;
    vlCreateLayerSettingSet("VK_LAYER_LUNARG_test", nullptr, nullptr, nullptr, &layerSettingSet);

    EXPECT_TRUE(vlHasLayerSetting(layerSettingSet, "my_setting"));

    uint32_t value_count = 0;
    VkResult result_count =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_BOOL32, &value_count, nullptr);
    EXPECT_EQ(VK_SUCCESS, result_count);
    EXPECT_EQ(2, value_count);

    std::vector<VkBool32> values(static_cast<uint32_t>(value_count));

    value_count = 1;
    VkResult result_incomplete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_BOOL32, &value_count, &values[0]);
    EXPECT_EQ(VK_INCOMPLETE, result_incomplete);
    EXPECT_EQ(VK_TRUE, values[0]);
    EXPECT_EQ(VK_FALSE, values[1]);
    EXPECT_EQ(1, value_count);

    value_count = 2;
    VkResult result_complete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_BOOL32, &value_count, &values[0]);
    EXPECT_EQ(VK_SUCCESS, result_complete);
    EXPECT_EQ(VK_TRUE, values[0]);
    EXPECT_EQ(VK_FALSE, values[1]);
    EXPECT_EQ(2, value_count);

    vlDestroyLayerSettingSet(layerSettingSet, nullptr);
}

TEST(test_layer_setting_env, vlGetLayerSettingValues_Int32) {
    SetEnv("VK_LUNARG_TEST_MY_SETTING=76,-82");

    VlLayerSettingSet layerSettingSet = VK_NULL_HANDLE;
    vlCreateLayerSettingSet("VK_LAYER_LUNARG_test", nullptr, nullptr, nullptr, &layerSettingSet);

    EXPECT_TRUE(vlHasLayerSetting(layerSettingSet, "my_setting"));

    uint32_t value_count = 2;
    VkResult result_count =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_INT32, &value_count, nullptr);
    EXPECT_EQ(VK_SUCCESS, result_count);
    EXPECT_EQ(2, value_count);

    std::vector<std::int32_t> values(static_cast<uint32_t>(value_count));

    value_count = 1;
    VkResult result_incomplete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_INT32, &value_count, &values[0]);
    EXPECT_EQ(VK_INCOMPLETE, result_incomplete);
    EXPECT_EQ(76, values[0]);
    EXPECT_EQ(0, values[1]);
    EXPECT_EQ(1, value_count);

    value_count = 2;
    VkResult result_complete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_INT32, &value_count, &values[0]);
    EXPECT_EQ(VK_SUCCESS, result_complete);
    EXPECT_EQ(76, values[0]);
    EXPECT_EQ(-82, values[1]);
    EXPECT_EQ(2, value_count);

    vlDestroyLayerSettingSet(layerSettingSet, nullptr);
}

TEST(test_layer_setting_env, vlGetLayerSettingValues_Int64) {
    SetEnv("VK_LUNARG_TEST_MY_SETTING=76,-82");

    VlLayerSettingSet layerSettingSet = VK_NULL_HANDLE;
    vlCreateLayerSettingSet("VK_LAYER_LUNARG_test", nullptr, nullptr, nullptr, &layerSettingSet);

    EXPECT_TRUE(vlHasLayerSetting(layerSettingSet, "my_setting"));

    uint32_t value_count = 2;
    VkResult result_count =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_INT64, &value_count, nullptr);
    EXPECT_EQ(VK_SUCCESS, result_count);
    EXPECT_EQ(2, value_count);

    std::vector<std::int64_t> values(static_cast<uint32_t>(value_count));

    value_count = 1;
    VkResult result_incomplete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_INT64, &value_count, &values[0]);
    EXPECT_EQ(VK_INCOMPLETE, result_incomplete);
    EXPECT_EQ(76, values[0]);
    EXPECT_EQ(0, values[1]);
    EXPECT_EQ(1, value_count);

    value_count = 2;
    VkResult result_complete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_INT64, &value_count, &values[0]);
    EXPECT_EQ(VK_SUCCESS, result_complete);
    EXPECT_EQ(76, values[0]);
    EXPECT_EQ(-82, values[1]);
    EXPECT_EQ(2, value_count);

    vlDestroyLayerSettingSet(layerSettingSet, nullptr);
}

TEST(test_layer_setting_env, vlGetLayerSettingValues_Uint32) {
    SetEnv("VK_LUNARG_TEST_MY_SETTING=76,82");

    VlLayerSettingSet layerSettingSet = VK_NULL_HANDLE;
    vlCreateLayerSettingSet("VK_LAYER_LUNARG_test", nullptr, nullptr, nullptr, &layerSettingSet);

    EXPECT_TRUE(vlHasLayerSetting(layerSettingSet, "my_setting"));

    uint32_t value_count = 0;
    VkResult result_count =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_UINT32, &value_count, nullptr);
    EXPECT_EQ(VK_SUCCESS, result_count);
    EXPECT_EQ(2, value_count);

    std::vector<std::uint32_t> values(static_cast<uint32_t>(value_count));

    value_count = 1;
    VkResult result_incomplete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_UINT32, &value_count, &values[0]);
    EXPECT_EQ(VK_INCOMPLETE, result_incomplete);
    EXPECT_EQ(76, values[0]);
    EXPECT_EQ(0, values[1]);
    EXPECT_EQ(1, value_count);

    value_count = 2;
    VkResult result_complete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_UINT32, &value_count, &values[0]);
    EXPECT_EQ(VK_SUCCESS, result_complete);
    EXPECT_EQ(76, values[0]);
    EXPECT_EQ(82, values[1]);
    EXPECT_EQ(2, value_count);

    vlDestroyLayerSettingSet(layerSettingSet, nullptr);
}

TEST(test_layer_setting_env, vlGetLayerSettingValues_Uint64) {
    SetEnv("VK_LUNARG_TEST_MY_SETTING=76,82");

    VlLayerSettingSet layerSettingSet = VK_NULL_HANDLE;
    vlCreateLayerSettingSet("VK_LAYER_LUNARG_test", nullptr, nullptr, nullptr, &layerSettingSet);

    EXPECT_TRUE(vlHasLayerSetting(layerSettingSet, "my_setting"));

    uint32_t value_count = 0;
    VkResult result_count =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_UINT64, &value_count, nullptr);
    EXPECT_EQ(VK_SUCCESS, result_count);
    EXPECT_EQ(2, value_count);

    std::vector<std::uint64_t> values(static_cast<uint32_t>(value_count));

    value_count = 1;
    VkResult result_incomplete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_UINT64, &value_count, &values[0]);
    EXPECT_EQ(VK_INCOMPLETE, result_incomplete);
    EXPECT_EQ(76, values[0]);
    EXPECT_EQ(0, values[1]);
    EXPECT_EQ(1, value_count);

    value_count = 2;
    VkResult result_complete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_UINT64, &value_count, &values[0]);
    EXPECT_EQ(VK_SUCCESS, result_complete);
    EXPECT_EQ(76, values[0]);
    EXPECT_EQ(82, values[1]);
    EXPECT_EQ(2, value_count);

    vlDestroyLayerSettingSet(layerSettingSet, nullptr);
}

TEST(test_layer_setting_env, vlGetLayerSettingValues_Float) {
    SetEnv("VK_LUNARG_TEST_MY_SETTING=76.1f,-82.5f");

    VlLayerSettingSet layerSettingSet = VK_NULL_HANDLE;
    vlCreateLayerSettingSet("VK_LAYER_LUNARG_test", nullptr, nullptr, nullptr, &layerSettingSet);

    EXPECT_TRUE(vlHasLayerSetting(layerSettingSet, "my_setting"));

    uint32_t value_count = 0;
    VkResult result_count =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_FLOAT32, &value_count, nullptr);
    EXPECT_EQ(VK_SUCCESS, result_count);
    EXPECT_EQ(2, value_count);

    std::vector<float> values(static_cast<uint32_t>(value_count));

    value_count = 1;
    VkResult result_incomplete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_FLOAT32, &value_count, &values[0]);
    EXPECT_EQ(VK_INCOMPLETE, result_incomplete);
    EXPECT_TRUE(std::abs(values[0] - 76.1f) <= 0.0001f);
    EXPECT_EQ(1, value_count);

    value_count = 2;
    VkResult result_complete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_FLOAT32, &value_count, &values[0]);
    EXPECT_EQ(VK_SUCCESS, result_complete);
    EXPECT_TRUE(std::abs(values[0] - 76.1f) <= 0.0001f);
    EXPECT_TRUE(std::abs(values[1] - -82.5f) <= 0.0001f);
    EXPECT_EQ(2, value_count);

    vlDestroyLayerSettingSet(layerSettingSet, nullptr);
}

TEST(test_layer_setting_env, vlGetLayerSettingValues_Double) {
    SetEnv("VK_LUNARG_TEST_MY_SETTING=76.1,-82.5");

    VlLayerSettingSet layerSettingSet = VK_NULL_HANDLE;
    vlCreateLayerSettingSet("VK_LAYER_LUNARG_test", nullptr, nullptr, nullptr, &layerSettingSet);

    EXPECT_TRUE(vlHasLayerSetting(layerSettingSet, "my_setting"));

    uint32_t value_count = 0;
    VkResult result_count =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_FLOAT64, &value_count, nullptr);
    EXPECT_EQ(VK_SUCCESS, result_count);
    EXPECT_EQ(2, value_count);

    std::vector<double> values(static_cast<uint32_t>(value_count));

    value_count = 1;
    VkResult result_incomplete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_FLOAT64, &value_count, &values[0]);
    EXPECT_EQ(VK_INCOMPLETE, result_incomplete);
    EXPECT_TRUE(std::abs(values[0] - 76.1) <= 0.0001);
    EXPECT_EQ(1, value_count);

    value_count = 2;
    VkResult result_complete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_FLOAT64, &value_count, &values[0]);
    EXPECT_EQ(VK_SUCCESS, result_complete);
    EXPECT_TRUE(std::abs(values[0] - 76.1) <= 0.0001);
    EXPECT_TRUE(std::abs(values[1] - -82.5) <= 0.0001);
    EXPECT_EQ(2, value_count);

    vlDestroyLayerSettingSet(layerSettingSet, nullptr);
}

TEST(test_layer_setting_env, vlGetLayerSettingValues_Frameset) {
    SetEnv("VK_LUNARG_TEST_MY_SETTING=76-100-10,1-100-1");

    VlLayerSettingSet layerSettingSet = VK_NULL_HANDLE;
    vlCreateLayerSettingSet("VK_LAYER_LUNARG_test", nullptr, nullptr, nullptr, &layerSettingSet);

    EXPECT_TRUE(vlHasLayerSetting(layerSettingSet, "my_setting"));

    uint32_t value_count = 0;
    VkResult result_count =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_FRAMESET, &value_count, nullptr);
    EXPECT_EQ(VK_SUCCESS, result_count);
    EXPECT_EQ(2, value_count);

    std::vector<VlFrameset> values(static_cast<uint32_t>(value_count));

    value_count = 1;
    VkResult result_incomplete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_FRAMESET, &value_count, &values[0]);
    EXPECT_EQ(VK_INCOMPLETE, result_incomplete);
    EXPECT_EQ(76, values[0].first);
    EXPECT_EQ(100, values[0].count);
    EXPECT_EQ(10, values[0].step);
    EXPECT_EQ(1, value_count);

    value_count = 2;
    VkResult result_complete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_FRAMESET, &value_count, &values[0]);
    EXPECT_EQ(VK_SUCCESS, result_complete);
    EXPECT_EQ(76, values[0].first);
    EXPECT_EQ(100, values[0].count);
    EXPECT_EQ(10, values[0].step);
    EXPECT_EQ(1, values[1].first);
    EXPECT_EQ(100, values[1].count);
    EXPECT_EQ(1, values[1].step);
    EXPECT_EQ(2, value_count);

    vlDestroyLayerSettingSet(layerSettingSet, nullptr);
}

TEST(test_layer_setting_env, vlGetLayerSettingValues_String) {
    SetEnv("VK_LUNARG_TEST_MY_SETTING=VALUE_A,VALUE_B");

    VlLayerSettingSet layerSettingSet = VK_NULL_HANDLE;
    vlCreateLayerSettingSet("VK_LAYER_LUNARG_test", nullptr, nullptr, nullptr, &layerSettingSet);

    EXPECT_TRUE(vlHasLayerSetting(layerSettingSet, "my_setting"));

    uint32_t value_count = 0;
    VkResult result_count =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_STRING, &value_count, nullptr);
    EXPECT_EQ(VK_SUCCESS, result_count);
    EXPECT_EQ(2, value_count);

    std::vector<const char*> values(static_cast<uint32_t>(value_count));

    value_count = 1;
    VkResult result_incomplete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_STRING, &value_count, &values[0]);
    EXPECT_EQ(VK_INCOMPLETE, result_incomplete);
    EXPECT_STREQ("VALUE_A", values[0]);
    EXPECT_STREQ(nullptr, values[1]);
    EXPECT_EQ(1, value_count);

    value_count = 2;
    VkResult result_complete =
        vlGetLayerSettingValues(layerSettingSet, "my_setting", VL_LAYER_SETTING_TYPE_STRING, &value_count, &values[0]);
    EXPECT_EQ(VK_SUCCESS, result_complete);
    EXPECT_STREQ("VALUE_A", values[0]);
    EXPECT_STREQ("VALUE_B", values[1]);
    EXPECT_EQ(2, value_count);

    vlDestroyLayerSettingSet(layerSettingSet, nullptr);
}
