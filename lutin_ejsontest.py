#!/usr/bin/python
import lutinModule as module
import lutinTools as tools
import datetime

def get_desc():
	return "e-json test application"


def create(target):
	# module name is 'edn' and type binary.
	myModule = module.Module(__file__, 'ejsontest', 'BINARY')
	
	# add the file to compile:
	myModule.add_src_file([
		'ejson/test.cpp'])
	
	myModule.add_module_depend(['ejson'])
	
	now = datetime.datetime.now()
	versionID=str(now.year-2012)+"."+str(now.month)+"."+str(now.day)
	
	# set the package properties :
	myModule.pkg_set("VERSION", versionID)
	myModule.pkg_set("COMPAGNY_TYPE", "org")
	myModule.pkg_set("COMPAGNY_NAME", "Edouard DUPIN")
	myModule.pkg_set("MAINTAINER", ["Mr DUPIN Edouard <yui.heero@gmail.com>"])
	myModule.pkg_set("SECTION", ["Development"])
	myModule.pkg_set("PRIORITY", "optional")
	myModule.pkg_set("DESCRIPTION", "e-json tester soft")
	myModule.pkg_set("NAME", "exml_tester")
	
	# add the currrent module at the 
	return myModule

