/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include "testCommon.hpp"
#include <gtest/gtest.h>


static etk::String refOutputBoolean1("{\n\t\"tmpElement\": true\n}\n");
TEST(TestBoolean, testBaseTrue) {
	localTest(refOutputBoolean1, "{ tmpElement:true }\n", -1);
}
TEST(TestBoolean, testTabbedTrue) {
	localTest(refOutputBoolean1, "{ \t\ntmpElement:true \t\n }\n", -1);
}
TEST(TestBoolean, testNoneTrue) {
	localTest(refOutputBoolean1, "tmpElement:true\n", -1);
}
TEST(TestBoolean, testBaseTrue1) {
	localTest(refOutputBoolean1, "{ tmpElement:TRUE }\n", 1);
}
TEST(TestBoolean, testBaseTrue2) {
	localTest(refOutputBoolean1, "{ tmpElement:True }\n", 1);
}


static etk::String refOutputBoolean2("{\n\t\"tmpElement\": false\n}\n");
TEST(TestBoolean, testBaseFalse) {
	localTest(refOutputBoolean2, "{ tmpElement:false }\n", -1);
}
TEST(TestBoolean, testTabbedFalse) {
	localTest(refOutputBoolean2, "{ \t\ntmpElement:false \t\n }\n", -1);
}
TEST(TestBoolean, testNoneFalse) {
	localTest(refOutputBoolean2, "tmpElement:false\n", -1);
}
TEST(TestBoolean, testBaseFalse1) {
	localTest(refOutputBoolean2, "{ tmpElement:FALSE }\n", 1);
}
TEST(TestBoolean, testBaseFalse2) {
	localTest(refOutputBoolean2, "{ tmpElement:False }\n", 1);
}

TEST(TestBoolean, multipleValue) {
	localTest("{\n\t\"tmpElement\": false,\n\t\"tmpElement2\": true\n}\n", "{ tmpElement:false, tmpElement2:true }\n", -1);
}