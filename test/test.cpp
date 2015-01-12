/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <vector>
#include <etk/types.h>
#include <etk/archive/Archive.h>
#include <ejson/debug.h>
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
	// the only one init for etk:
	etk::log::setLevel(etk::log::logLevelNone);
	for (int32_t iii=0; iii<argc ; ++iii) {
		std::string data = argv[iii];
		if (data == "-l0") {
			etk::log::setLevel(etk::log::logLevelNone);
		} else if (data == "-l1") {
			etk::log::setLevel(etk::log::logLevelCritical);
		} else if (data == "-l2") {
			etk::log::setLevel(etk::log::logLevelError);
		} else if (data == "-l3") {
			etk::log::setLevel(etk::log::logLevelWarning);
		} else if (data == "-l4") {
			etk::log::setLevel(etk::log::logLevelInfo);
		} else if (data == "-l5") {
			etk::log::setLevel(etk::log::logLevelDebug);
		} else if (data == "-l6") {
			etk::log::setLevel(etk::log::logLevelVerbose);
		}
	}
	etk::setArgZero(argv[0]);
	etk::initDefaultFolder("ejson_test");
	return RUN_ALL_TESTS();
}

