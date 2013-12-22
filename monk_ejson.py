#!/usr/bin/python
import monkModule as module
import monkTools as tools

def create():
	# module name is 'edn' and type binary.
	myModule = module.Module(__file__, 'ejson', 'LIBRARY')
	# enable doculentation :
	myModule.set_website("http://heeroyui.github.io/ejson/")
	myModule.set_path(tools.get_current_path(__file__) + "/ejson/")
	# add the currrent module at the 
	return myModule

def get_desc():
	return ""
