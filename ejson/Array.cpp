/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */


#include <ejson/Object.h>
#include <ejson/Array.h>
#include <ejson/String.h>
#include <ejson/Null.h>
#include <ejson/Number.h>
#include <ejson/Boolean.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

ememory::SharedPtr<ejson::Array> ejson::Array::create() {
	return ememory::SharedPtr<ejson::Array>(new ejson::Array());
}

void ejson::Array::clear() {
	m_value.clear();
}

bool ejson::Array::iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::Document& _doc) {
	JSON_PARSE_ELEMENT("start parse : 'Object' ");
	for (size_t iii=_pos+1; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
		 drawElementParsed(_data[iii], _filePos);
		#endif
		ejson::FilePos tmpPos;
		if(    _data[iii] == ' '
		    || _data[iii] == '\t'
		    || _data[iii] == '\n'
		    || _data[iii] == '\r') {
			// white space  == > nothing to do ...
		} else if(_data[iii] == '#') {
			// comment Line ...
			for (iii++; iii<_data.size(); iii++) {
				if(    _data[iii] == '\n'
				    || _data[iii] == '\r') {
					break;
				}
			}
		} else if(_data[iii] == ']') {
			// find end of value:
			_pos=iii; //  == > return the end element type ==> usefull to check end and check if adding element is needed
			return true;
		} else if (_data[iii] == '{') {
			// find an object:
			JSON_PARSE_ELEMENT("find Object");
			ememory::SharedPtr<ejson::Object> tmpElement = ejson::Object::create();
			if (tmpElement == nullptr) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in object");
				_pos=iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
		} else if (    _data[iii] == '"'
		            || _data[iii] == '\'') {
			// find a string:
			JSON_PARSE_ELEMENT("find String quoted");
			ememory::SharedPtr<ejson::String> tmpElement = ejson::String::create();
			if (tmpElement == nullptr) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in String");
				_pos=iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
		} else if (_data[iii] == '[') {
			// find a list:
			JSON_PARSE_ELEMENT("find List");
			ememory::SharedPtr<ejson::Array> tmpElement = ejson::Array::create();
			if (tmpElement == nullptr) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Array");
				_pos=iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
		} else if(    _data[iii] == 'f'
		           || _data[iii] == 't' ) {
			// find boolean:
			JSON_PARSE_ELEMENT("find Boolean");
			ememory::SharedPtr<ejson::Boolean> tmpElement = ejson::Boolean::create();
			if (tmpElement == nullptr) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Boolean");
				_pos=iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
		} else if( _data[iii] == 'n') {
			// find null:
			JSON_PARSE_ELEMENT("find Null");
			ememory::SharedPtr<ejson::Null> tmpElement = ejson::Null::create();
			if (tmpElement == nullptr) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Boolean");
				_pos=iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
		} else if(true == checkNumber(_data[iii])) {
			// find number:
			JSON_PARSE_ELEMENT("find Number");
			ememory::SharedPtr<ejson::Number> tmpElement = ejson::Number::create();
			if (tmpElement == nullptr) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Boolean");
				_pos=iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
		} else if(_data[iii] == ',') {
			// find Separator : Restart cycle ...
			// TODO : check if element are separated with ','
		} else {
			// find an error ....
			EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Find '?' with no element in the element...");
			// move the curent index
			_pos = iii+1;
			return false;
		}
	}
	_pos = _data.size();
	return false;
}


bool ejson::Array::iGenerate(std::string& _data, size_t _indent) const {
	bool oneLine=true;
	if (m_value.size()>3) {
		oneLine=false;
	} else {
		for (size_t iii=0; iii<m_value.size() ; iii++) {
			ememory::SharedPtr<const ejson::Value> tmp = m_value[iii];
			if (tmp == nullptr) {
				continue;
			}
			if (true == tmp->isObject()) {
				oneLine=false;
				break;
			}
			if (true == tmp->isArray()) {
				oneLine=false;
				break;
			}
			if (true == tmp->isString()) {
				ememory::SharedPtr<const ejson::String> tmp2 = tmp->toString();
				if (tmp2 != nullptr) {
					if(tmp2->get().size()>40) {
						oneLine=false;
						break;
					}
				}
			}
		}
	}
	if (true == oneLine) {
		_data += "[ ";
	} else {
		_data += "[\n";
	}
	for (size_t iii=0; iii<m_value.size() ; iii++) {
		if (false == oneLine) {
			addIndent(_data, _indent);
		}
		if (m_value[iii] != nullptr) {
			m_value[iii]->iGenerate(_data, _indent+1);
			if (iii<m_value.size()-1) {
				_data += ",";
			}
		}
		if (true == oneLine) {
			_data += " ";
		} else {
			_data += "\n";
		}
	}
	if (false == oneLine) {
		addIndent(_data, _indent-1);
	}
	_data += "]";
	return true;
}

bool ejson::Array::add(ememory::SharedPtr<ejson::Value> _element) {
	if (_element == nullptr) {
		JSON_ERROR("Request add on an nullptr pointer");
		return false;
	}
	m_value.push_back(_element);
	return true;
}

bool ejson::Array::addString(const std::string& _value) {
	return add(ejson::String::create(_value));
}

bool ejson::Array::addNull() {
	return add(ejson::Null::create());
}

bool ejson::Array::addBoolean(bool _value) {
	return add(ejson::Boolean::create(_value));
}

bool ejson::Array::addNumber(double _value) {
	return add(ejson::Number::create(_value));
}


bool ejson::Array::transfertIn(ememory::SharedPtr<ejson::Value> _obj) {
	if (_obj == nullptr) {
		JSON_ERROR("Request transfer on an nullptr pointer");
		return false;
	}
	ememory::SharedPtr<ejson::Array> other = _obj->toArray();
	if (other == nullptr) {
		JSON_ERROR("Request transfer on an element that is not an array");
		return false;
	}
	// remove destination elements
	other->clear();
	// Copy to the destination
	other->m_value = m_value;
	// remove current:
	m_value.clear();
	return true;
}

// TODO : Manage error ...
ememory::SharedPtr<ejson::Value> ejson::Array::clone() const {
	ememory::SharedPtr<ejson::Array> output = ejson::Array::create();
	if (output == nullptr) {
		JSON_ERROR("Allocation error ...");
		return ememory::SharedPtr<ejson::Value>();
	}
	for (size_t iii=0; iii<m_value.size(); ++iii) {
		ememory::SharedPtr<const ejson::Value> val = m_value[iii];
		if (val == nullptr) {
			continue;
		}
		output->add(val->clone());
	}
	return output;
}

ememory::SharedPtr<ejson::Object> ejson::Array::getObject(size_t _id) {
	ememory::SharedPtr<ejson::Value> tmpElement = m_value[_id];
	if (tmpElement == nullptr) {
		return ememory::SharedPtr<ejson::Object>();
	}
	return tmpElement->toObject();
}
const ememory::SharedPtr<const ejson::Object> ejson::Array::getObject(size_t _id) const {
	const ememory::SharedPtr<const ejson::Value> tmpElement = m_value[_id];
	if (tmpElement == nullptr) {
		return ememory::SharedPtr<const ejson::Object>();
	}
	return tmpElement->toObject();
}

ememory::SharedPtr<ejson::String> ejson::Array::getString(size_t _id) {
	ememory::SharedPtr<ejson::Value> tmpElement = m_value[_id];
	if (tmpElement == nullptr) {
		return ememory::SharedPtr<ejson::String>();
	}
	return tmpElement->toString();
}

const ememory::SharedPtr<const ejson::String> ejson::Array::getString(size_t _id) const {
	const ememory::SharedPtr<const ejson::Value> tmpElement = m_value[_id];
	if (tmpElement == nullptr) {
		return ememory::SharedPtr<const ejson::String>();
	}
	return tmpElement->toString();
}

ememory::SharedPtr<ejson::Array> ejson::Array::getArray(size_t _id) {
	ememory::SharedPtr<ejson::Value> tmpElement = m_value[_id];
	if (tmpElement == nullptr) {
		return ememory::SharedPtr<ejson::Array>();
	}
	return tmpElement->toArray();
}

const ememory::SharedPtr<const ejson::Array> ejson::Array::getArray(size_t _id) const {
	const ememory::SharedPtr<const ejson::Value> tmpElement = m_value[_id];
	if (tmpElement == nullptr) {
		return ememory::SharedPtr<const ejson::Array>();
	}
	return tmpElement->toArray();
}

ememory::SharedPtr<ejson::Null> ejson::Array::getNull(size_t _id) {
	ememory::SharedPtr<ejson::Value> tmpElement = m_value[_id];
	if (tmpElement == nullptr) {
		return ememory::SharedPtr<ejson::Null>();
	}
	return tmpElement->toNull();
}

const ememory::SharedPtr<const ejson::Null> ejson::Array::getNull(size_t _id) const {
	const ememory::SharedPtr<const ejson::Value> tmpElement = m_value[_id];
	if (tmpElement == nullptr) {
		return ememory::SharedPtr<const ejson::Null>();
	}
	return tmpElement->toNull();
}

ememory::SharedPtr<ejson::Number> ejson::Array::getNumber(size_t _id) {
	ememory::SharedPtr<ejson::Value> tmpElement = m_value[_id];
	if (tmpElement == nullptr) {
		return ememory::SharedPtr<ejson::Number>();
	}
	return tmpElement->toNumber();
}

const ememory::SharedPtr<const ejson::Number> ejson::Array::getNumber(size_t _id) const {
	const ememory::SharedPtr<const ejson::Value> tmpElement = m_value[_id];
	if (tmpElement == nullptr) {
		return ememory::SharedPtr<const ejson::Number>();
	}
	return tmpElement->toNumber();
}

ememory::SharedPtr<ejson::Boolean> ejson::Array::getBoolean(size_t _id) {
	ememory::SharedPtr<ejson::Value> tmpElement = m_value[_id];
	if (tmpElement == nullptr) {
		return ememory::SharedPtr<ejson::Boolean>();
	}
	return tmpElement->toBoolean();
}

const ememory::SharedPtr<const ejson::Boolean> ejson::Array::getBoolean(size_t _id) const {
	const ememory::SharedPtr<const ejson::Value> tmpElement = m_value[_id];
	if (tmpElement == nullptr) {
		return ememory::SharedPtr<const ejson::Boolean>();
	}
	return tmpElement->toBoolean();
}

std::string ejson::Array::getStringValue(size_t _id) {
	ememory::SharedPtr<ejson::String> tmpElement = getString(_id);
	if (tmpElement == nullptr) {
		return "";
	}
	return tmpElement->get();
}

const std::string& ejson::Array::getStringValue(size_t _id) const {
	static const std::string errorValue("");
	const ememory::SharedPtr<const ejson::String> tmpElement = getString(_id);
	if (tmpElement == nullptr) {
		return errorValue;
	}
	return tmpElement->get();
}

std::string ejson::Array::getStringValue(size_t _id, const std::string& _errorValue) const {
	const ememory::SharedPtr<const ejson::String> tmpElement = getString(_id);
	if (tmpElement == nullptr) {
		return _errorValue;
	}
	return tmpElement->get();
}

double ejson::Array::getNumberValue(size_t _id, double _errorValue) const {
	const ememory::SharedPtr<const ejson::Number> tmpElement = getNumber(_id);
	if (tmpElement == nullptr) {
		return _errorValue;
	}
	return tmpElement->get();
}

bool ejson::Array::getBooleanValue(size_t _id, bool _errorValue) const {
	const ememory::SharedPtr<const ejson::Boolean> tmpElement = getBoolean(_id);
	if (tmpElement == nullptr) {
		return _errorValue;
	}
	return tmpElement->get();
}


