=?=Read a json file=?=
__________________________________________________
[left][tutorial[000_Build | Previous: Build example]][/left] [right][tutorial[002_Write | Next: Write a file]][/right]


A json file is like a xml, but in a simplest way.
It is in the minimum constituated of:
[code style=json]
{}
[/code]
This is the simplest json code.

for example we will use the next json file :
[code style=json]
{
	"element1":25622.53,
	"element2":"a string...",
	"is active":false,
	"NULL element":null,
	"exampleObject":{
		"a string":"my super example of string",
		"a null element":null,
		"an array element":[
			12, 25, 65, 654
		],
		"a boolean Element":true,
		"a simple sumber"=156156.343,
		"an other object":{
			"plop": 1,
			"plop2": 2
		}
	},
	"exampleArray":[
		12,
		25,
		65,
		654,
		{
			"plup": true,
			"plup2": false
		},
		true,
		null,
		[ 22, 23, 24, 25]
	}
}
[/code]



== Open the file ==

The first step to open a file is to create the json document:

[code style=c++]
#include <ejson/ejson.h>

int main() {
	// declare document
	ejson::Document doc;
	...
}
[/code]

=== Load a stored file ===

It is important to remember that the input file is manage by etk, 
then the naming form is describe by the class: [class[etk::FSNode]]

[code style=c++]
	// read file
	if (doc.load("DATA:example.json") == false) {
		APPL_ERROR("An error occured when reading the file...");
		// TODO : STANDARDIZE ERROR....
		return -1;
	}
[/code]

=== Load a file stored in memory ===

This step is easyest has a reading in a file.

In the first step, declare a string containing the json description:
[code style=c++]
	std:string myJson = "{ \"element1\":25622.53, \"element2\":\"a string...\" }";
[/code]

Now we just need to load the string:
[code style=c++]
	if (doc.parse(myJson) == false) {
		APPL_ERROR("An error occured when parsing the string");
		return -1;
	}
[/code]

it could be interesting to add some \n in the string to find some error in the json string

== Access on the data ==

now we have the data stored in the doc instance, it could be interesting to access on it.

Despite of XML interface that is not designed to be keep in memory but just parsed and drop,
the json element is many time use as a simple interface to acces on the data.

This is the reason for this json interfce is designed for simple acces and use.

=== The simple way ===

Read a number value in the doc:
[code style=c++]
	double myValue = doc.getNumberValue("element1", 49);
	APPL_INFO("Get the element value:" << myValue);
[/code]
Note that we had a return value, in case of the element is not present or in the wrong form.

We have the same interface for boolean, string and number:
:** [methode[ejson::Object::getNumberValue]]
:** [methode[ejson::Object::getStringValue]]
:** [methode[ejson::Object::getBooleanValue]]

These interface methode are availlable for [class[ejson::Document]], [class[ejson::Object]].
The similar interface are availlable on [class[ejson:Array]]:
:** [methode[ejson::Array::getNumberValue]]
:** [methode[ejson::Array::getStringValue]]
:** [methode[ejson::Array::getBooleanValue]]

It could be interesting to remember that the maain node of a json file in an object,
this is the reason that [class[ejson::Document]] herited of [class[ejson::Object]].

=== The generic way ===

The classical way to read a json file is to parse it like a xml:

==== Object ====
We are now reading all node in an object:
[code style=c++]
	std::shared_ptr<ejson::Object> obj = doc.getObject("exampleObject");
	// note that the obj is NULL if it not an "Object"
	if (obj == nullptr) {
		APPL_ERROR("Can not get the object 'exampleObject' in the json file");
		return -1;
	}
[/code]
Note at this point we can parse an object in 2 way:

1: The fastest but not the best:
[code style=c++]
	for (size_t iii=0; iii < obj->size(); ++iii) {
		std::string key = obj->getKey(iii);
		std::shared_ptr<ejson::Value> val = obj[iii];
		// note that error can appear, then check result...
		if (val == nullptr) {
			APPL_ERROR("Can not read the object id=" << iii);
			continue;
		}
		switch(val->getType()) {
			case typeArray: {
				std::shared_ptr<ejson::Array> myArray = val->toArray();
				APPL_INFO("Find an Array @" << key);
				} break;
			case typeString: {
				std::shared_ptr<ejson::String> myString = val->toString();
				APPL_INFO("Find a String @" << key << " value='" << myString->get() << "'");
				} break;
			case typeNumber: {
				std::shared_ptr<ejson::Number> myNumber = val->toNumber();
				APPL_INFO("Find a Number @" << key << " value='" << myNumber->get() << "'");
				} break;
			case typeBoolean: {
				std::shared_ptr<ejson::Boolean> myBoolean = val->toBoolean();
				APPL_INFO("Find a Boolean @" << key << " value='" << myBoolean->get() << "'");
				} break;
			case typeNull:
				APPL_INFO("Find a null @" << key);
				break;
			case typeObject: {
				std::shared_ptr<ejson::Object> myObject = val->toObject();
				APPL_INFO("Find an Object @" << key);
				} break;
		}
	}
[/code]

2: A more generic way to acces on the elemnts:
[code style=c++]
	stk::vector<std::string> keys = obj->getKeys();
	for (auto key in keys) {
		std::shared_ptr<ejson::Value> val = obj[key];
		// note that error can appear, then check result...
		if (val == nullptr) {
			APPL_ERROR("Can not read the object key=" << key);
			continue;
		}
		switch(val->getType()) {
			case typeArray: {
				std::shared_ptr<ejson::Array> myArray = val->toArray();
				APPL_INFO("Find an Array @" << key);
				} break;
			case typeString: {
				std::shared_ptr<ejson::String> myString = val->toString();
				APPL_INFO("Find a String @" << key << " value='" << myString->get() << "'");
				} break;
			case typeNumber: {
				std::shared_ptr<ejson::Number> myNumber = val->toNumber();
				APPL_INFO("Find a Number @" << key << " value='" << myNumber->get() << "'");
				} break;
			case typeBoolean: {
				std::shared_ptr<ejson::Boolean> myBoolean = val->toBoolean();
				APPL_INFO("Find a Boolean @" << key << " value='" << myBoolean->get() << "'");
				} break;
			case typeNull:
				APPL_INFO("Find a null @" << key);
				break;
			case typeObject: {
				std::shared_ptr<ejson::Object> myObject = val->toObject();
				APPL_INFO("Find an Object @" << key);
				} break;
		}
	}
[/code]

==== Array ====

We are now reading all node in an Array:
[code style=c++]
	std::shared_ptr<ejson::Array> obj = doc.getArray("exampleArray");
	// note that the obj is nullptr if it not an "Array"
	if (obj == nullptr) {
		APPL_ERROR("Can not get the array 'exampleArray' in the json file");
		return -1;
	}
[/code]

Note for an array we have only one methode to parse the data :

[code style=c++]
	for (size_t iii=0; iii < obj->size(); ++iii) {
		std::shared_ptr<ejson::Value> val = obj[iii];
		// or std::shared_ptr<ejson::Value> val = obj->get(iii);
		// note that error can appear, then check result...
		if (val == nullptr) {
			APPL_ERROR("Can not read the object id=" << iii);
			continue;
		}
		switch(val->getType()) {
			case typeArray: {
				std::shared_ptr<ejson::Array> myArray = val->toArray();
				APPL_INFO("Find an Array @" << key);
				} break;
			case typeString: {
				std::shared_ptr<ejson::String> myString = val->toString();
				APPL_INFO("Find a String @" << key << " value='" << myString->get() << "'");
				} break;
			case typeNumber: {
				std::shared_ptr<ejson::Number> myNumber = val->toNumber();
				APPL_INFO("Find a Number @" << key << " value='" << myNumber->get() << "'");
				} break;
			case typeBoolean: {
				std::shared_ptr<ejson::Boolean> myBoolean = val->toBoolean();
				APPL_INFO("Find a Boolean @" << key << " value='" << myBoolean->get() << "'");
				} break;
			case typeNull:
				APPL_INFO("Find a null @" << key);
				break;
			case typeObject: {
				std::shared_ptr<ejson::Object> myObject = val->toObject();
				APPL_INFO("Find an Object @" << key);
				} break;
		}
	}
[/code]


It is important to note that many time the user know what type will appear in a list or in an object , then you can directly use:
:** [methode[ejson::Array::getNumber]]
:** [methode[ejson::Array::getNull]]
:** [methode[ejson::Array::getArray]]
:** [methode[ejson::Array::getObject]]
:** [methode[ejson::Array::getBoolean]]
:** [methode[ejson::Array::getstring]]
These fuction automatly cast the result in the good form (if it is the real one)

