/**
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include "testCommon.hpp"
#include <etest/etest.hpp>

static etk::String refOutputDocument("{\n}\n");
TEST(TestDocument, testEmptyDoc) {
	localTest(refOutputDocument, "{}\n", -1);
}

TEST(TestDocument, testTabbedDoc) {
	localTest(refOutputDocument, "{    \t\r   }\n", -1);
}

