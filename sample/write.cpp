/** @file
 * @author Edouard DUPIN
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

//! [ejson_sample_write_all]
#include <test-debug/debug.h>
#include <ejson/ejson.h>
#include "write.h"

static void writeToFile() {
	ejson::Document doc;
	doc.add("A", ejson::String("2.5"));
	doc.add("B", ejson::Number(2010));
	doc.add("C", ejson::Boolean(false));
	doc.add("D", ejson::Array());
	TEST_INFO("store");
	//! [ejson_sample_write_file]
	bool retGenerate = doc.store("generate.json");
	//! [ejson_sample_write_file]
	TEST_INFO("parse ret = " << retGenerate);
	TEST_INFO("Debug display of the tree:");
	doc.display();
}

static void writeToString() {
	ejson::Document doc;
	doc.add("A", ejson::String("2.5"));
	doc.add("B", ejson::Number(2010));
	doc.add("C", ejson::Boolean(false));
	doc.add("D", ejson::Array());
	TEST_INFO("generate");
	//! [ejson_sample_write_stream]
	std::string streamOut;
	bool retGenerate = doc.generate(streamOut);
	//! [ejson_sample_write_stream]
	TEST_INFO("parse ret = " << retGenerate);
	TEST_INFO("Debug display of the tree:");
	doc.display();
}

static void writeAll() {
	ejson::Document doc;
	
	//! [ejson_sample_write_add_string_1]
	doc.add("A", ejson::String("2.5"));
	//! [ejson_sample_write_add_string_1]
	//! [ejson_sample_write_add_string_2]
	doc.addString("Aa", "lkjlkjlkj");
	//! [ejson_sample_write_add_string_2]
	
	//! [ejson_sample_write_add_null_1]
	doc.add("B", ejson::Null());
	//! [ejson_sample_write_add_null_1]
	//! [ejson_sample_write_add_null_2]
	doc.addNull("Bb");
	//! [ejson_sample_write_add_null_2]
	
	//! [ejson_sample_write_add_number_1]
	doc.add("C", ejson::Number(2010));
	//! [ejson_sample_write_add_number_1]
	//! [ejson_sample_write_add_number_2]
	doc.addNumber("Cc", 5161.2);
	//! [ejson_sample_write_add_number_2]
	
	//! [ejson_sample_write_add_boolean_1]
	doc.add("D", ejson::Boolean(false));
	//! [ejson_sample_write_add_boolean_1]
	//! [ejson_sample_write_add_boolean_2]
	doc.addBoolean("Dd", true);
	//! [ejson_sample_write_add_boolean_2]
	
	//! [ejson_sample_write_add_array]
	ejson::Array array;
	array.add(ejson::String("elem1"));
	array.add(ejson::Number(22));
	array.add(ejson::Null());
	doc.add("E", array);
	//! [ejson_sample_write_add_array]
	
	//! [ejson_sample_write_add_object]
	ejson::Object object;
	object.add("ee", ejson::String("elem1"));
	object.add("55", ejson::Number(22));
	object.add("lk", ejson::Null());
	doc.add("F", object);
	//! [ejson_sample_write_add_object]
	
	// remove the object named "F"
	//! [ejson_sample_write_rm_object]
	doc.remove("F");
	//! [ejson_sample_write_rm_object]
	
	// Remove element 2 in the array
	//! [ejson_sample_write_rm_array]
	array.remove(2);
	//! [ejson_sample_write_rm_array]
	doc.display();
}


void appl::write() {
	writeToFile();
	writeToString();
	writeAll();
}
//! [ejson_sample_write_all]

