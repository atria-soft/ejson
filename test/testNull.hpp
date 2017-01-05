/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include "testCommon.hpp"
#include <gtest/gtest.h>


static std::string refOutputNull("{\n\t\"tmpElement\": null\n}\n");
TEST(TestNull, testBasicNullElement) {
	localTest(refOutputNull, "{ tmpElement:null }\n", -1);
}

TEST(TestNull, testTabbedNullElement) {
	localTest(refOutputNull, "{ \t\ntmpElement:null \t\n }\n", -1);
}

TEST(TestNull, testTabbedNullElementNoPThese) {
	localTest(refOutputNull, "tmpElement:null\n", -1);
}


TEST(TestNull, multipleElement) {
	localTest("{\n\t\"tmpElement\": null,\n\t\"tmpElement2\": null\n}\n", "{tmpElement:null, tmpElement2:null\n}", -1);
}

