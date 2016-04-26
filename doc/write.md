Write an JSON content                                {#ejson_tutorial_write}
====================

@tableofcontents

The first thing to do when reading or writing a JSON file/stream, is to declare the Document interface

Include ejson
@snippet read.cpp ejson_sample_include

Declare document interface
@snippet read.cpp ejson_sample_declare_doc


Write an JSON file                                  {#ejson_tutorial_write_file}
=================

Write an json tree is done like:
@snippet write.cpp ejson_sample_write_file


Write an JSON Stream                                {#ejson_tutorial_write_stream}
===================

Writing a stream is done like this:
@snippet write.cpp ejson_sample_write_stream

Operation on Tree                                  {#ejson_tutorial_write_operation}
=================

Add Node/Declaration:
@snippet write.cpp ejson_sample_write_add_declaration

Add an Node/Element:
@snippet write.cpp ejson_sample_write_add_element

Remove a Node/Element:
@snippet write.cpp ejson_sample_write_rm_node


Add an attribute (simple version):
@snippet write.cpp ejson_sample_write_add_attribute_simple

Add an attribute (complex version):
@snippet write.cpp ejson_sample_write_add_attribute_complex

Remove an attribute:
@snippet write.cpp ejson_sample_write_rm_attribute

Object concept                                    {#ejson_tutorial_concept}
==============

the ejson concept is to abstract the implementation of the internal system. All the element are maped on shared memory.
Then if you asign an element to an other, it is the same. You need to clone it if you want to have new standalone element.


All example file                                  {#ejson_tutorial_write_all}
================

@snippet write.cpp ejson_sample_write_all

