/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include "testCommon.hpp"
#include <gtest/gtest.h>

static std::string refOutputDocument("{\n}\n");
TEST(TestDocument, testEmptyDoc) {
	localTest(refOutputDocument, "{}\n", -1);
}

TEST(TestDocument, testTabbedDoc) {
	localTest(refOutputDocument, "{    \t\r   }\n", -1);
}

