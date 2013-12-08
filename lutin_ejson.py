#!/usr/bin/python
import lutinModule
import lutinTools

def Create(target):
	myModule = lutinModule.module(__file__, 'ejson', 'LIBRARY')
	# enable doculentation :
	myModule.doc_enable()
	myModule.documentation.set_website("http://HeeroYui.github.io/ejson/")
	myModule.documentation.set_path(lutinTools.GetCurrentPath(__file__) + "/ejson/")
	myModule.documentation.set_external_link(['ewol'])
	
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


