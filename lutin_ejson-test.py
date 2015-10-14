#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools
import datetime


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

def create(target, module_name):
	my_module = module.Module(__file__, module_name, get_type())
	my_module.add_src_file([
		'test/test.cpp'
		])
	my_module.add_module_depend(['ejson', 'gtest', 'test-debug'])
	now = datetime.datetime.now()
	versionID=str(now.year-2012)+"."+str(now.month)+"."+str(now.day)
	# set the package properties :
	my_module.pkg_set("VERSION", versionID)
	my_module.pkg_set("SECTION", ["Development"])
	my_module.pkg_set("PRIORITY", "optional")
	return my_module

