/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include "testCommon.hpp"
#include <etest/etest.hpp>

static etk::String refOutputNumber("{\n\t\"tmpElement\": 956256\n}\n");
TEST(TestNumber, testBase) {
	localTest(refOutputNumber, "{ tmpElement:956256 }\n", -1);
}
TEST(TestNumber, testTabbed) {
	localTest(refOutputNumber, "{ \t\ntmpElement:956256 \t\n }\n", -1);
}
TEST(TestNumber, testNone) {
	localTest(refOutputNumber, "tmpElement:956256\n", -1);
}
TEST(TestNumber, testNegative) {
	localTest("{\n\t\"tmpElement\": -956256\n}\n", "{tmpElement:-956256}\n", -1);
}
TEST(TestNumber, testFloat) {
	localTest("{\n\t\"tmpElement\": -956.256000\n}\n", "{tmpElement : -956.256}\n", -1);
}

