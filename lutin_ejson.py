#!/usr/bin/python
import lutinModule
import lutinTools

def Create(target):
	myModule = lutinModule.module(__file__, 'ejson', 'LIBRARY')
	
	myModule.AddModuleDepend(['etk'])
	
	# add extra compilation flags :
	myModule.add_extra_compile_flags()
	myModule.AddSrcFile([
		'ejson/debug.cpp',
		'ejson/ejson.cpp',
		'ejson/Array.cpp',
		'ejson/Boolean.cpp',
		'ejson/Null.cpp',
		'ejson/Number.cpp',
		'ejson/String.cpp',
		'ejson/Object.cpp',
		'ejson/Value.cpp'])
	
	myModule.AddExportPath(lutinTools.GetCurrentPath(__file__))
	
	# add the currrent module at the 
	return myModule


