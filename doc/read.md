Read an JSON content                                {#ejson_tutorial_read}
===================

@tableofcontents

The first thing to do when reading or writing a JSON file/stream, is to declare the Document interface

Include ejson
@snippet read.cpp ejson_sample_include

Declare document interface
@snippet read.cpp ejson_sample_declare_doc


Read an JSON file                                 {#ejson_tutorial_read_file}
================

File to read: "read.json"
@include read.json

Reading a file is done like this:
@snippet read.cpp ejson_sample_read_file

The file naming is manage by @ref etk::FSNode that provide "DATA:" start string for internal application asset. You can use external path like "./plop/file.json" too.


Read an JSON Stream                              {#ejson_tutorial_read_stream}
==================

Reading a stream is done like this:
@snippet read.cpp ejson_sample_read_stream1

In C and C++ it is very hard to read string with the \\" then to simplify parsing of json the parser engine support the use of simple **'** interface:
@snippet read.cpp ejson_sample_read_stream2


Access at all Element datas                     {#ejson_tutorial_read_folow}
===========================

In an ejson::Object (or ejson::Document) the sub-nodes are accessible threw an abstraction class stores in an element name **Value**

Get a value with its name:
@snippet read.cpp ejson_sample_read_get_element

Access to a string in an Object:
-------------------------------

The generic Way to access to an element is to convert it in the corect type:
@snippet read.cpp ejson_sample_read_convert_string

And after Get the Value:
@snippet read.cpp ejson_sample_read_get_string_value

Commonly you might use like this:
@snippet read.cpp ejson_sample_read_get_string_1

Helper function:
@snippet read.cpp ejson_sample_read_get_string_2



Access to a boolean in an Object:
---------------------------------

@snippet read.cpp ejson_sample_read_get_boolean_1

Helper function:
@snippet read.cpp ejson_sample_read_get_boolean_2


Access to a Number in an Object:
---------------------------------

@snippet read.cpp ejson_sample_read_get_number_1

Helper function:
@snippet read.cpp ejson_sample_read_get_number_2


Access to a Array in an Object:
---------------------------------

Get the Array
@snippet read.cpp ejson_sample_read_get_array

Move threw all element:
@snippet read.cpp ejson_sample_read_move_threw_array

Move threw all element in C mode:
@snippet read.cpp ejson_sample_read_move_threw_array_c


Access to a Object in an Object:
---------------------------------

Get the Object
@snippet read.cpp ejson_sample_read_get_object

Move threw all element:
@snippet read.cpp ejson_sample_read_move_threw_object

Move threw all element in C mode:
@snippet read.cpp ejson_sample_read_move_threw_object_c


Now we can copy the Object we want
==================================

ejson manage reference object, then it is possible that 2 part of the software access at the same object/element ...

You can copy object to separate or duplicate section.

This is named cloning:
@snippet read.cpp ejson_sample_read_clone


All example file                                  {#ejson_tutorial_read_all}
================

@snippet read.cpp ejson_sample_read_all

