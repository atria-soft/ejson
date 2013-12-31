#!/usr/bin/python
import lutinModule as module
import lutinTools as tools

def get_desc():
	return "e-json Json parser and genrator"


def create(target):
	myModule = module.Module(__file__, 'ejson', 'LIBRARY')
	
	myModule.add_module_depend(['etk'])
	
	# add extra compilation flags :
	myModule.add_extra_compile_flags()
	myModule.add_src_file([
		'ejson/debug.cpp',
		'ejson/ejson.cpp',
		'ejson/Array.cpp',
		'ejson/Boolean.cpp',
		'ejson/Null.cpp',
		'ejson/Number.cpp',
		'ejson/String.cpp',
		'ejson/Object.cpp',
		'ejson/Value.cpp'])
	
	myModule.add_export_path(tools.get_current_path(__file__))
	
	# add the currrent module at the 
	return myModule

