#!/usr/bin/python
import realog.debug as debug
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
	return "MPL-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return ["Mr DUPIN Edouard <yui.heero@gmail.com>"]

def configure(target, my_module):
	my_module.add_src_file([
	    'test/test.cpp',
	    'test/testCommon.cpp',
	    'test/testDocument.cpp',
	    'test/testBoolean.cpp',
	    'test/testNull.cpp',
	    'test/testNumber.cpp',
	    'test/testAll.cpp',
	    ])
	my_module.add_depend([
	    'ejson',
	    'etest',
	    'test-debug'
	    ])
	return True

