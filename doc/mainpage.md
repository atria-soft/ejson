EJSON library                                {#mainpage}
=============

@tableofcontents

What is EJSON:                               {#ejson_mainpage_what}
==============

EJSON, or Ewol JSON interface is a simple, small, efficient, C++ JSON parser/generator that can be easily integrating into other programs.

What it does:                               {#ejson_mainpage_what_it_does}
-------------

EJSON parses an JSON document, and builds from that a Document Object Model (DOM) that can be read, modified, and saved.

JSON stands for "JavaScript Object Notation". It is a general purpose human and machine readable machine language to describe arbitrary data (base internal system of the JavaScript object).
All those random file formats created to store application data can all be replaced with JSON. One parser for everything.

http://wikipedia.org/wiki/JSON

There are different ways to access and interact with JSON data.
EJSON uses a Document Object Model (DOM), meaning the JSON data is parsed into a C++ objects that can be browsed and manipulated, and then written to disk.
You can also construct an JSON document from scratch with C++ objects and write this to disk.

EJSON is designed to be easy and fast to learn.

EJSON is dependent of the STL (compatible with MacOs stl (CXX))

What it doesn't do:                          {#ejson_mainpage_what_it_not_does}
-------------------

I do not know...

Internal extention:                          {#ejson_mainpage_extention}
-------------------

I Add some costum feature of JSON:
  - Support inline comment starting with **#**
  - Support Unquotet name if the name is not separate with space and not start with number
  - Support simple quote **'** instead of double quote **"**
  - Support removing of the **{}** arround the file (by default present)


What languages are supported?                    {#ejson_mainpage_language}
=============================

EJSON is written in C++.


Are there any licensing restrictions?            {#ejson_mainpage_license_restriction}
=====================================

EJSON is **FREE software** and _all sub-library are FREE and staticly linkable !!!_


License (MPL v2.0)                               {#ejson_mainpage_license}
==================

Copyright EJSON Edouard DUPIN

Licensed under the Mozilla Public License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

<https://www.mozilla.org/MPL/2.0>

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Other pages                              {#ejson_mainpage_sub_page}
===========

  - @ref ejson_build
  - @ref ejson_tutorial_read
  - @ref ejson_tutorial_write
  - [**ewol coding style**](http://atria-soft.github.io/ewol/ewol_coding_style.html)

