/** @file
 * @author Edouard DUPIN
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <test-debug/debug.hpp>
//! [ejson_sample_include]
#include <ejson/ejson.hpp>
//! [ejson_sample_include]
#include "read.hpp"


static void readFromFile() {
	//! [ejson_sample_declare_doc]
	ejson::Document doc;
	//! [ejson_sample_declare_doc]
	//! [ejson_sample_read_file]
	bool retParse = doc.load("DATA:///read.json");
	//! [ejson_sample_read_file]
	TEST_INFO("parse ret = " << retParse);
	TEST_INFO("Debug display of the tree:");
	doc.display();
}

static void readFromString1() {
	ejson::Document doc;
	TEST_INFO("parse");
	//! [ejson_sample_read_stream1]
	etk::String stream = "{"
	                     "	\"object A\":\"bonjour\","
	                     "	\"object B\":null,"
	                     "	\"object C\":true,"
	                     "	\"object D\":123854.215,"
	                     "	\"object E\":["
	                     "		1,2,3,54,false"
	                     "	],"
	                     "	\"object F\":{"
	                     "		\"a\":1,"
	                     "		\"b\":2"
	                     "	}"
	                     "}";
	bool retParse = doc.parse(stream);
	//! [ejson_sample_read_stream1]
	TEST_INFO("parse ret = " << retParse);
	TEST_INFO("Debug display of the tree:");
	doc.display();
}

static void readFromString2() {
	ejson::Document doc;
	TEST_INFO("parse");
	//! [ejson_sample_read_stream2]
	etk::String stream = "{"
	                     "	objectA:'bonjour',"
	                     "	objectB:null,"
	                     "	objectC:true,"
	                     "	objectD:123854.215,"
	                     "	objectE:["
	                     "		#simple comment one Line"
	                     "		1,2,3,54,false"
	                     "	],"
	                     "	objectF:{"
	                     "		a:1,"
	                     "		b:2"
	                     "	}"
	                     "}";
	bool retParse = doc.parse(stream);
	//! [ejson_sample_read_stream2]
	TEST_INFO("parse ret = " << retParse);
	TEST_INFO("Debug display of the tree:");
	doc.display();
}


static void readFull() {
	ejson::Document doc;
	TEST_INFO("parse");
	bool retParse = doc.load("DATA:///read.json");
	TEST_INFO("parse ret = " << retParse);
	TEST_INFO("Debug display of the tree:");
	doc.display();
	TEST_INFO("list of Object:");
	for (const auto it: doc) {
		TEST_INFO("	" << it);
		if (it.isObject() == true) {
			ejson::Object obj = it.toObject();
			// check if the convertion in ejson::Object has been done corectly
			if (obj.exist() == false) {
				continue;
			}
			TEST_INFO("		list of object:");
			for (const auto itObj: obj) {
				TEST_INFO("			" << itObj);
			}
		} else if (it.isArray() == true) {
			ejson::Array array = it.toArray();
			// check if the convertion in ejson::Array has been done corectly
			if (array.exist() == false) {
				continue;
			}
			TEST_INFO("		list of object:");
			for (const auto itArray: array) {
				TEST_INFO("			" << itArray);
			}
		} else if (it.isBoolean() == true) {
			ejson::Boolean boolean = it.toBoolean();
			// check if the convertion in ejson::Boolean has been done corectly
			if (boolean.exist() == false) {
				continue;
			}
			TEST_INFO("		boolean Value:" << boolean.get());
		} else if (it.isString() == true) {
			ejson::String str = it.toString();
			// check if the convertion in ejson::String has been done corectly
			if (str.exist() == false) {
				continue;
			}
			TEST_INFO("		String Value:" << str.get());
		} else if (it.isNumber() == true) {
			ejson::Number num = it.toNumber();
			// check if the convertion in ejson::Number has been done corectly
			if (num.exist() == false) {
				continue;
			}
			TEST_INFO("		Number Value:" << num.get());
		}
	}
	
	for (size_t iii=0; iii<doc.size(); ++iii) {
		switch (doc[iii].getType()) {
			case ejson::valueType::Object:
				TEST_INFO("		Get an Object:" << doc.getKey(iii) );
				break;
			case ejson::valueType::Array:
				TEST_INFO("		Get an Array:" << doc.getKey(iii) );
				break;
			case ejson::valueType::Boolean:
				TEST_INFO("		Get an Boolean:" << doc.getKey(iii) );
				break;
			case ejson::valueType::Null:
				TEST_INFO("		Get an Null:" << doc.getKey(iii) );
				break;
			case ejson::valueType::Number:
				TEST_INFO("		Get an Number:" << doc.getKey(iii) );
				break;
			case ejson::valueType::String:
				TEST_INFO("		Get an String:" << doc.getKey(iii) );
				break;
			default:
				TEST_INFO("		Inknow element:" << doc.getKey(iii) );
				break;
		}
	}
	
	TEST_INFO("	Direct get node exml:");
	//! [ejson_sample_read_get_element]
	ejson::Value element = doc["object C"];
	//! [ejson_sample_read_get_element]
	//! [ejson_sample_read_check_element]
	if (element.exist() == false) {
		TEST_ERROR("The element does not exist");
	}
	//! [ejson_sample_read_check_element]
	
	TEST_INFO("Read String:");
	{
		// you can simply change the type of the exml value if you know what it is:
		//! [ejson_sample_read_convert_string]
		ejson::String elem = doc["object A"].toString();
		// Get the value:
		etk::String value = elem.get();
		//! [ejson_sample_read_convert_string]
		TEST_INFO("    String Value:" << value);
	}
	// or simply:
	{
		// Get the value:
		//! [ejson_sample_read_get_string]
		etk::String value = doc["object A"].toString().get();
		//! [ejson_sample_read_get_string]
		TEST_INFO("    String Value:" << value);
	}
	
	TEST_INFO("Read Boolean:");
	
	// Get a Boolean value:
	{
		// Get the value:
		//! [ejson_sample_read_get_boolean]
		bool value = doc["object C"].toBoolean().get();
		//! [ejson_sample_read_get_boolean]
		TEST_INFO("    Boolean Value:" << value);
	}
	
	TEST_INFO("Read Number:");
	
	// Get a number value:
	{
		// Get the value:
		//! [ejson_sample_read_get_number]
		double valueDouble = doc["object D"].toNumber().get();
		//! [ejson_sample_read_get_number]
		//! [ejson_sample_read_get_number_64_bits]
		uint64_t valueUint = doc["object D"].toNumber().getU64();
		//! [ejson_sample_read_get_number_64_bits]
		TEST_INFO("    Number Value double:" << valueDouble << "  int64=" << valueUint);
	}
	
	TEST_INFO("Read Array:");
	{
		//! [ejson_sample_read_get_array]
		ejson::Array array = doc["object E"].toArray();
		//! [ejson_sample_read_get_array]
		// check if the convertion in ejson::Array has been done corectly
		if (array.exist() == true) {
			TEST_INFO("		list of Element in Array:");
			//! [ejson_sample_read_move_threw_array]
			for (const auto itArray: array) {
				TEST_INFO("			" << itArray);
			}
			//! [ejson_sample_read_move_threw_array]
			TEST_INFO("		list of Element in Array (C mode):");
			//! [ejson_sample_read_move_threw_array_c]
			for (size_t iii=0; iii<array.size(); ++iii) {
				TEST_INFO("			" << array[iii]);
			}
			//! [ejson_sample_read_move_threw_array_c]
		}
	}
	
	TEST_INFO("Read Object:");
	{
		//! [ejson_sample_read_get_object]
		ejson::Object obj = doc["object F"].toObject();
		//! [ejson_sample_read_get_object]
		// check if the convertion in ejson::Object has been done corectly
		if (obj.exist() == true) {
			TEST_INFO("		list of Element in Object:");
			//! [ejson_sample_read_move_threw_object]
			for (const auto itObj: obj) {
				TEST_INFO("			" << itObj);
			}
			//! [ejson_sample_read_move_threw_object]
			TEST_INFO("		list of Element in Object (C mode):");
			//! [ejson_sample_read_move_threw_object_c]
			for (size_t iii=0; iii<obj.size(); ++iii) {
				TEST_INFO("			" << obj[iii]);
			}
			//! [ejson_sample_read_move_threw_object_c]
		}
	}
	
	TEST_INFO("Clone Object:");
	// in the local system, All element get are not copied but referenced. the to have a copy of an object, you need to clone it :
	{
		// Clone object:
		//! [ejson_sample_read_clone]
		ejson::Value tmpClone = doc["object F"].clone();
		//! [ejson_sample_read_clone]
		ejson::Object obj = tmpClone.toObject();
		// check if the clone and convertion in ejson::Object has been done corectly
		if (obj.exist() == true) {
			TEST_INFO("		list of Element in Object:");
			for (const auto itObj: obj) {
				TEST_INFO("			" << itObj);
			}
		}
	}
	
}

void appl::read() {
	readFromFile();
	readFromString1();
	readFromString1();
	readFull();
}
