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

Add String:
@snippet write.cpp ejson_sample_write_add_string

Add Null:
@snippet write.cpp ejson_sample_write_add_null

Add Number:
@snippet write.cpp ejson_sample_write_add_number

Add Boolean:
@snippet write.cpp ejson_sample_write_add_boolean

Add Array with values:
@snippet write.cpp ejson_sample_write_add_array

Add Object with values:
@snippet write.cpp ejson_sample_write_add_object

Remove a Value in an Object:
@snippet write.cpp ejson_sample_write_rm_object

Remove a Value in an Object:
@snippet write.cpp ejson_sample_write_rm_array


Object concept                                    {#ejson_tutorial_concept}
==============

The ejson concept is to abstract the implementation of the internal system. All the element are mapped on shared memory.
Then if you asign an element to an other, it is the same. You need to clone it if you want to have new standalone element.

@snippet read.cpp ejson_sample_read_clone

All example file                                  {#ejson_tutorial_write_all}
================

@include write.cpp

