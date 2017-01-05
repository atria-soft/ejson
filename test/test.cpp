/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <vector>
#include <etk/etk.hpp>
#include <etk/types.hpp>
#include <etk/archive/Archive.hpp>
#include <test-debug/debug.hpp>
#include <ejson/ejson.hpp>
#include <gtest/gtest.h>
#include <etk/os/FSNode.hpp>

#include "testDocument.hpp"
#include "testBoolean.hpp"
#include "testNull.hpp"
#include "testNumber.hpp"
#include "testAll.hpp"

int main(int argc, const char *argv[]) {
	// init Google test :
	::testing::InitGoogleTest(&argc, const_cast<char **>(argv));
	// init etk log system and file interface:
	etk::init(argc, argv);
	// Run all test with gtest
	return RUN_ALL_TESTS();
}

