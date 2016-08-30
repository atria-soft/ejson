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
	return [0,6,0]

def create(target, module_name):
	my_module = module.Module(__file__, module_name, get_type())
	my_module.add_module_depend(['elog', 'etk', 'ememory'])
	my_module.add_extra_compile_flags()
	my_module.add_src_file([
		'ejson/debug.cpp',
		'ejson/FilePos.cpp',
		'ejson/valueType.cpp',
		'ejson/Document.cpp',
		'ejson/Array.cpp',
		'ejson/Boolean.cpp',
		'ejson/Null.cpp',
		'ejson/Number.cpp',
		'ejson/String.cpp',
		'ejson/Object.cpp',
		'ejson/Value.cpp',
		'ejson/internal/Document.cpp',
		'ejson/internal/Array.cpp',
		'ejson/internal/Boolean.cpp',
		'ejson/internal/Null.cpp',
		'ejson/internal/Number.cpp',
		'ejson/internal/String.cpp',
		'ejson/internal/Object.cpp',
		'ejson/internal/Value.cpp'
		])
	my_module.add_header_file([
		'ejson/FilePos.h',
		'ejson/ejson.h',
		'ejson/valueType.h',
		'ejson/Document.h',
		'ejson/Array.h',
		'ejson/Boolean.h',
		'ejson/Null.h',
		'ejson/Number.h',
		'ejson/String.h',
		'ejson/Object.h',
		'ejson/Value.h',
		'ejson/iterator.h',
		'ejson/details/iterator.hxx',
		'ejson/internal/Document.h',
		'ejson/internal/Array.h',
		'ejson/internal/Boolean.h',
		'ejson/internal/Null.h',
		'ejson/internal/Number.h',
		'ejson/internal/String.h',
		'ejson/internal/Object.h',
		'ejson/internal/Value.h'
		])
	my_module.add_path(tools.get_current_path(__file__))
	return my_module


