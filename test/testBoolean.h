/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */


#ifndef __EJSON_TEST_BOOLEAN_H__
#define __EJSON_TEST_BOOLEAN_H__

#include "testCommon.h"
#include <gtest/gtest.h>


static std::string refOutputBoolean1("{\n\t\"tmpElement\": true\n}\n");
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


static std::string refOutputBoolean2("{\n\t\"tmpElement\": false\n}\n");
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

#endif