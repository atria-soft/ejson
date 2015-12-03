#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools


def get_type():
	return "LIBRARY"

def get_desc():
	return "Json parser and generator"

def get_licence():
	return "APACHE-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return ["Mr DUPIN Edouard <yui.heero@gmail.com>"]

def get_version():
	return [0,4,"dev"]

def create(target, module_name):
	my_module = module.Module(__file__, module_name, get_type())
	my_module.add_module_depend(['etk'])
	my_module.add_extra_compile_flags()
	my_module.add_src_file([
		'ejson/debug.cpp',
		'ejson/ejson.cpp',
		'ejson/Array.cpp',
		'ejson/Boolean.cpp',
		'ejson/Null.cpp',
		'ejson/Number.cpp',
		'ejson/String.cpp',
		'ejson/Object.cpp',
		'ejson/Value.cpp'
		])
	my_module.add_header_file([
		'ejson/ejson.h',
		'ejson/Array.h',
		'ejson/Boolean.h',
		'ejson/Null.h',
		'ejson/Number.h',
		'ejson/String.h',
		'ejson/Object.h',
		'ejson/Value.h'
		])
	my_module.add_path(tools.get_current_path(__file__))
	return my_module


