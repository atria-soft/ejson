/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <ejson/Object.h>
#include <ejson/Array.h>
#include <ejson/String.h>
#include <ejson/Null.h>
#include <ejson/Number.h>
#include <ejson/Boolean.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"Array"


void ejson::Array::clear(void) {
	for (esize_t iii=0; iii<m_value.size(); ++iii) {
		if (NULL == m_value[iii]) {
			continue;
		}
		delete(m_value[iii]);
		m_value[iii] = NULL;
	}
	m_value.clear();
}

bool ejson::Array::iParse(const std::string& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc) {
	JSON_PARSE_ELEMENT("start parse : 'Object' ");
	for (int32_t iii=_pos+1; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
		 drawElementParsed(_data[iii], _filePos);
		#endif
		ejson::filePos tmpPos;
		if(    _data[iii] == ' '
		    || _data[iii] == '\t'
		    || _data[iii] == '\n'
		    || _data[iii] == '\r') {
			// white space  == > nothing to do ...
		} else if(_data[iii] == ']') {
			// find end of value:
			_pos=iii; //  == > return the end element type ==> usefull to check end and check if adding element is needed
			return true;
		} else if (_data[iii] == '{') {
			// find an object:
			JSON_PARSE_ELEMENT("find Object");
			ejson::Object * tmpElement = new ejson::Object();
			if (NULL == tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in object");
				_pos=iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
		} else if (_data[iii] == '"') {
			// find a string:
			JSON_PARSE_ELEMENT("find String quoted");
			ejson::String * tmpElement = new ejson::String();
			if (NULL == tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in String");
				_pos=iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
		} else if (_data[iii] == '[') {
			// find a list:
			JSON_PARSE_ELEMENT("find List");
			ejson::Array * tmpElement = new ejson::Array();
			if (NULL == tmpElement) {
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
			ejson::Boolean * tmpElement = new ejson::Boolean();
			if (NULL == tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Boolean");
				_pos=iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
		} else if( _data[iii] == 'n') {
			// find null:
			JSON_PARSE_ELEMENT("find Null");
			ejson::Null * tmpElement = new ejson::Null();
			if (NULL == tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Boolean");
				_pos=iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
		} else if(true == checkNumber(_data[iii])) {
			// find number:
			JSON_PARSE_ELEMENT("find Number");
			ejson::Number * tmpElement = new ejson::Number();
			if (NULL == tmpElement) {
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
			EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Find '>' with no element in the element...");
			// move the curent index
			_pos = iii+1;
			return false;
		}
	}
	_pos = _data.size();
	return false;
}


bool ejson::Array::iGenerate(std::string& _data, int32_t _indent) const {
	bool oneLine=true;
	if (m_value.size()>3) {
		oneLine=false;
	} else {
		for (esize_t iii=0; iii<m_value.size() ; iii++) {
			ejson::Value* tmp = m_value[iii];
			if (tmp == NULL) {
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
				ejson::String* tmp2 = tmp->toString();
				if (NULL!=tmp2) {
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
	for (esize_t iii=0; iii<m_value.size() ; iii++) {
		if (false == oneLine) {
			addIndent(_data, _indent);
		}
		if (NULL != m_value[iii]) {
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

bool ejson::Array::add(ejson::Value* _element) {
	if (NULL == _element) {
		JSON_ERROR("Request add on an NULL pointer");
		return false;
	}
	m_value.push_back(_element);
	return true;
}

bool ejson::Array::addString(const std::string& _value) {
	return add(new ejson::String(_value));
}

bool ejson::Array::addNull(void) {
	return add(new ejson::Null());
}

bool ejson::Array::addBoolean(bool _value) {
	return add(new ejson::Boolean(_value));
}

bool ejson::Array::addNumber(double _value) {
	return add(new ejson::Number(_value));
}


bool ejson::Array::transfertIn(ejson::Value* _obj) {
	if (NULL == _obj) {
		JSON_ERROR("Request transfer on an NULL pointer");
		return false;
	}
	ejson::Array* other = _obj->toArray();
	if (NULL == other) {
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
ejson::Value* ejson::Array::duplicate(void) const {
	ejson::Array* output = new ejson::Array();
	if (NULL == output) {
		JSON_ERROR("Allocation error ...");
		return NULL;
	}
	for (esize_t iii=0; iii<m_value.size(); ++iii) {
		ejson::Value* val = m_value[iii];
		if (NULL == val) {
			continue;
		}
		output->add(val->duplicate());
	}
	return output;
}

ejson::Object* ejson::Array::getObject(esize_t _id) {
	ejson::Value* tmpElement = m_value[_id];
	if (NULL == tmpElement) {
		return NULL;
	}
	return tmpElement->toObject();
}

ejson::String* ejson::Array::getString(esize_t _id) {
	ejson::Value* tmpElement = m_value[_id];
	if (NULL == tmpElement) {
		return NULL;
	}
	return tmpElement->toString();
}

ejson::Array* ejson::Array::getArray(esize_t _id) {
	ejson::Value* tmpElement = m_value[_id];
	if (NULL == tmpElement) {
		return NULL;
	}
	return tmpElement->toArray();
}

ejson::Null* ejson::Array::getNull(esize_t _id) {
	ejson::Value* tmpElement = m_value[_id];
	if (NULL == tmpElement) {
		return NULL;
	}
	return tmpElement->toNull();
}

ejson::Number* ejson::Array::getNumber(esize_t _id) {
	ejson::Value* tmpElement = m_value[_id];
	if (NULL == tmpElement) {
		return NULL;
	}
	return tmpElement->toNumber();
}

ejson::Boolean* ejson::Array::getBoolean(esize_t _id) {
	ejson::Value* tmpElement = m_value[_id];
	if (NULL == tmpElement) {
		return NULL;
	}
	return tmpElement->toBoolean();
}

const std::string& ejson::Array::getStringValue(esize_t _id) {
	static const std::string errorValue("");
	ejson::String* tmpElement = getString(_id);
	if (NULL == tmpElement) {
		return errorValue;
	}
	return tmpElement->get();
}

std::string ejson::Array::getStringValue(esize_t _id, const std::string& _errorValue) {
	ejson::String* tmpElement = getString(_id);
	if (NULL == tmpElement) {
		return _errorValue;
	}
	return tmpElement->get();
}

double ejson::Array::getNumberValue(esize_t _id, double _errorValue) {
	ejson::Number* tmpElement = getNumber(_id);
	if (NULL == tmpElement) {
		return _errorValue;
	}
	return tmpElement->get();
}

bool ejson::Array::getBooleanValue(esize_t _id, bool _errorValue) {
	ejson::Boolean* tmpElement = getBoolean(_id);
	if (NULL == tmpElement) {
		return _errorValue;
	}
	return tmpElement->get();
}


