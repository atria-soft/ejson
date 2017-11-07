/** @file
 * @author Edouard DUPIN
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <test-debug/debug.hpp>
#include <ejson/ejson.hpp>
#include "write.hpp"

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
	//! [ejson_sample_write_file_safe_mode]
	retGenerate = doc.storeSafe("generate.json");
	//! [ejson_sample_write_file_safe_mode]
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
	etk::String streamOut;
	bool retGenerate = doc.generate(streamOut);
	//! [ejson_sample_write_stream]
	TEST_INFO("parse ret = " << retGenerate);
	TEST_INFO("Debug display of the tree:");
	doc.display();
}

static void writeAll() {
	ejson::Document doc;
	
	//! [ejson_sample_write_add_string]
	doc.add("A", ejson::String("2.5"));
	//! [ejson_sample_write_add_string]
	
	//! [ejson_sample_write_add_null]
	doc.add("B", ejson::Null());
	//! [ejson_sample_write_add_null]
	
	//! [ejson_sample_write_add_number]
	doc.add("C", ejson::Number(2010));
	//! [ejson_sample_write_add_number]
	
	//! [ejson_sample_write_add_boolean]
	doc.add("D", ejson::Boolean(false));
	//! [ejson_sample_write_add_boolean]
	
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

