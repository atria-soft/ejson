#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools
import datetime

def get_desc():
	return "e-json test application"


def create(target):
	# module name is 'edn' and type binary.
	my_module = module.Module(__file__, 'ejson-test', 'BINARY')
	
	# add the file to compile:
	my_module.add_src_file([
		'test/test.cpp'])
	
	my_module.add_module_depend(['ejson', 'gtest'])
	
	now = datetime.datetime.now()
	versionID=str(now.year-2012)+"."+str(now.month)+"."+str(now.day)
	
	# set the package properties :
	my_module.pkg_set("VERSION", versionID)
	my_module.pkg_set("COMPAGNY_TYPE", "org")
	my_module.pkg_set("COMPAGNY_NAME", "Edouard DUPIN")
	my_module.pkg_set("MAINTAINER", ["Mr DUPIN Edouard <yui.heero@gmail.com>"])
	my_module.pkg_set("SECTION", ["Development"])
	my_module.pkg_set("PRIORITY", "optional")
	my_module.pkg_set("DESCRIPTION", "e-json tester soft")
	my_module.pkg_set("NAME", "exml_tester")
	
	# add the currrent module at the 
	return my_module

