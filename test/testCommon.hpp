/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <test-debug/debug.hpp>
#include <ejson/ejson.hpp>

// _errorPos : -1 : no error , 1 : parsing error, 2 generation error, 3 comparaison error ????
static void localTest(const etk::String& _ref, const etk::String& _input, int32_t _errorPos) {
	ejson::Document doc;
	bool retParse = doc.parse(_input);
	if (_errorPos == 1) {
		EXPECT_EQ(retParse, false);
		return;
	} else {
		EXPECT_EQ(retParse, true);
	}
	etk::String out("");
	bool retGenerate = doc.generate(out);
	if (_errorPos == 2) {
		EXPECT_EQ(retGenerate, false);
		return;
	} else {
		EXPECT_EQ(retGenerate, true);
	}
	if (_errorPos == 3) {
		EXPECT_NE(_ref, out);
		return;
	} else {
		EXPECT_EQ(_ref, out);
		/*
		JSON_ERROR("[TEST] {ERROR } different output");
		etk::Vector<etk::String> tmpout = etk::split(out, '\n');
		etk::Vector<etk::String> tmpref = etk::split(_ref, '\n');
		//JSON_ERROR("generate : \n" << out);
		//JSON_ERROR("reference : \n" << l_list[iii].m_ref);
		for (int32_t jjj=0; jjj<tmpout.size() || jjj<tmpref.size(); ++jjj) {
			if (jjj<tmpref.size()) {
				TEST_INFO("[" << jjj << "] " << tmpref[jjj] );
			}
			if (jjj<tmpout.size()) {
				if (jjj>=tmpref.size() || tmpref[jjj] != tmpout[jjj]) {
					TEST_ERROR("[" << jjj << "] " << tmpout[jjj] );
				}
			}
		}
		*/
	}
}

