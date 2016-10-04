#!/usr/bin/python
import lutin.debug as debug
import lutin.tools as tools


def get_type():
	return "BINARY"

def get_sub_type():
	return "TEST"

def get_name():
	return "e-json-test"

def get_desc():
	return "e-json test application"

def get_licence():
	return "APACHE-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return ["Mr DUPIN Edouard <yui.heero@gmail.com>"]

def configure(target, my_module):
	my_module.add_src_file([
	    'test/test.cpp'
	    ])
	my_module.add_depend([
	    'ejson',
	    'gtest',
	    'test-debug'
	    ])
	return True

