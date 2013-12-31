#!/usr/bin/python
import monkModule as module
import monkTools as tools

def get_desc():
	return "e-json Json parser and genrator"

def create():
	# module name is 'edn' and type binary.
	myModule = module.Module(__file__, 'ejson', 'LIBRARY')
	# enable doculentation :
	myModule.set_website("http://heeroyui.github.io/ejson/")
	myModule.set_website_sources("http://github.com/heeroyui/ejson/")
	myModule.set_path(tools.get_current_path(__file__) + "/ejson/")
	myModule.set_path_general_doc(tools.get_current_path(__file__) + "/doc/")
	# add the currrent module at the 
	return myModule

