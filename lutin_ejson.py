#!/usr/bin/python
import lutin.debug as debug
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
	return "authors.txt"

def get_version():
	return "version.txt"

def configure(target, my_module):
	my_module.add_depend([
	    'elog',
	    'etk',
	    'ememory'
	    ])
	my_module.add_extra_flags()
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
	    'ejson/FilePos.hpp',
	    'ejson/ejson.hpp',
	    'ejson/valueType.hpp',
	    'ejson/Document.hpp',
	    'ejson/Array.hpp',
	    'ejson/Boolean.hpp',
	    'ejson/Null.hpp',
	    'ejson/Number.hpp',
	    'ejson/String.hpp',
	    'ejson/Object.hpp',
	    'ejson/Value.hpp',
	    'ejson/iterator.hpp',
	    'ejson/details/iterator.hxx',
	    'ejson/internal/Document.hpp',
	    'ejson/internal/Array.hpp',
	    'ejson/internal/Boolean.hpp',
	    'ejson/internal/Null.hpp',
	    'ejson/internal/Number.hpp',
	    'ejson/internal/String.hpp',
	    'ejson/internal/Object.hpp',
	    'ejson/internal/Value.hpp'
	    ])
	my_module.add_path(".")
	return True


