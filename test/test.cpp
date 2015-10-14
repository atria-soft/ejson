/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <vector>
#include <etk/etk.h>
#include <etk/types.h>
#include <etk/archive/Archive.h>
#include <test-debug/debug.h>
#include <ejson/ejson.h>
#include <gtest/gtest.h>
#include <etk/os/FSNode.h>

#include "testDocument.h"
#include "testBoolean.h"
#include "testNull.h"
#include "testNumber.h"
#include "testAll.h"

#undef __class__
#define __class__	"ejson::test"


int main(int argc, const char *argv[]) {
	// init Google test :
	::testing::InitGoogleTest(&argc, const_cast<char **>(argv));
	// init etk log system and file interface:
	etk::init(argc, argv);
	// TODO : Check this ...
	etk::initDefaultFolder("ejson_test");
	// Run all test with gtest
	return RUN_ALL_TESTS();
}

