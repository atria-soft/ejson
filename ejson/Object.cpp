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
#define __class__	"Object"

void ejson::Object::clear(void) {
	for (int32_t iii=0; iii<m_value.size(); ++iii) {
		if (NULL == m_value[iii]) {
			continue;
		}
		delete(m_value[iii]);
		m_value[iii] = NULL;
	}
	m_value.clear();
}


enum statusParsing {
	parseName,
	parseMiddle,
	parseValue,
};

bool ejson::Object::iParse(const std::string& _data, size_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc) {
	enum statusParsing mode = parseName;
	std::string currentName;
	JSON_PARSE_ELEMENT("start parse : 'Object' ");
	bool standalone = true;
	size_t startPos = _pos+1;
	if (_data[_pos] != '{' ) { // when the main node call it, it can be start with != '{'
		standalone = false;
		startPos = _pos;
	}
	for (size_t iii=startPos; iii<_data.size(); iii++) {
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
		} else if(_data[iii] == '}') {
			// find end of value:
			_pos=iii; //  == > return the end element type ==> usefull to check end and check if adding element is needed
			return true;
		} else {
			if (mode == parseName) {
				JSON_PARSE_ELEMENT("name START " << '"');
				if (_data[iii] == '"') {
					currentName = "";
					for (iii++; iii<_data.size(); iii++) {
						_filePos.check(_data[iii]);
						#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
						 drawElementParsed(_data[iii], _filePos);
						#endif
						if (_data[iii] == '\"') {
							mode = parseMiddle;
							break;
						} else {
							currentName += _data[iii];
						}
					}
				} else if (checkString(_data[iii]) ) {
					currentName += _data[iii];
					for (iii++; iii<_data.size(); iii++) {
						_filePos.check(_data[iii]);
						#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
						 drawElementParsed(_data[iii], _filePos);
						#endif
						if (false == checkString(_data[iii])) {
							mode = parseMiddle;
							iii--;
							break;
						} else {
							currentName += _data[iii];
						}
					}
				} else {
					EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "element unknow ...");
					_pos = iii;
					return false;
				}
				JSON_PARSE_ELEMENT("name END ");
			} else if (mode == parseMiddle) {
				JSON_PARSE_ELEMENT(" middle ... ");
				if (_data[iii] == ':') {
					mode = parseValue;
				} else {
					EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "separator is not ':'");
					return false;
				}
			} else if (mode == parseValue) {
				if (_data[iii] == '{') {
					// find an object:
					JSON_PARSE_ELEMENT("find Object");
					ejson::Object * tmpElement = new ejson::Object();
					if (NULL == tmpElement) {
						EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in object");
						_pos=iii;
						return false;
					}
					tmpElement->iParse(_data, iii, _filePos, _doc);
					add(currentName, tmpElement);
					currentName = "";
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
					add(currentName, tmpElement);
					currentName = "";
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
					add(currentName, tmpElement);
					currentName = "";
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
					add(currentName, tmpElement);
					currentName = "";
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
					add(currentName, tmpElement);
					currentName = "";
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
					add(currentName, tmpElement);
					currentName = "";
				} else if(_data[iii] == ',') {
					// find Separator : Restart cycle ...
					mode = parseName;
					currentName = "";
				} else {
					// find an error ....
					EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, std::string("Find '") + _data[iii] + "' with no element in the element...");
					// move the curent index
					_pos = iii+1;
					return false;
				}
			}
		}
	}
	_pos = _data.size();
	if (false == standalone) {
		return true;
	}
	return false;
}
bool ejson::Object::iGenerate(std::string& _data, size_t _indent) const {
	bool oneLine=true;
	if (m_value.size()>3) {
		oneLine=false;
	} else if (_indent<=1) {
		oneLine=false;
	} else {
		for (int32_t iii=0; iii<m_value.size() ; iii++) {
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
					if(    tmp2->get().size()>25
					    || m_value.getKey(iii).size()>25) {
						oneLine=false;
						break;
					}
				}
			}
		}
	}
	if (true == oneLine) {
		_data += "{ ";
	} else {
		_data += "{\n";
	}
	for (int32_t iii=0; iii<m_value.size() ; iii++) {
		if (false == oneLine) {
			addIndent(_data, _indent);
		}
		_data += "\"";
		_data += m_value.getKey(iii);
		_data += "\": ";
		m_value.getValue(iii)->iGenerate(_data, _indent+1);
		if (iii<m_value.size()-1) {
			_data += ",";
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
	_data += "}";
	return true;
}

bool ejson::Object::exist(const std::string& _name) const {
	return m_value.exist(_name);
}

ejson::Value* ejson::Object::get(const std::string& _name) {
	if (false == m_value.exist(_name)) {
		return NULL;
	}
	return m_value[_name];
}

const ejson::Value* ejson::Object::get(const std::string& _name) const {
	if (false == m_value.exist(_name)) {
		return NULL;
	}
	return m_value[_name];
}

ejson::Object* ejson::Object::getObject(const std::string& _name) {
	ejson::Value* tmp = get(_name);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->toObject();
}

const ejson::Object* ejson::Object::getObject(const std::string& _name) const {
	const ejson::Value* tmp = get(_name);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->toObject();
}

ejson::Array* ejson::Object::getArray(const std::string& _name) {
	ejson::Value* tmp = get(_name);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->toArray();
}

const ejson::Array* ejson::Object::getArray(const std::string& _name) const {
	const ejson::Value* tmp = get(_name);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->toArray();
}

ejson::Null* ejson::Object::getNull(const std::string& _name) {
	ejson::Value* tmp = get(_name);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->toNull();
}

const ejson::Null* ejson::Object::getNull(const std::string& _name) const {
	const ejson::Value* tmp = get(_name);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->toNull();
}

ejson::String* ejson::Object::getString(const std::string& _name) {
	ejson::Value* tmp = get(_name);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->toString();
}

const ejson::String* ejson::Object::getString(const std::string& _name) const {
	const ejson::Value* tmp = get(_name);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->toString();
}

const std::string& ejson::Object::getStringValue(const std::string& _name) const {
	static const std::string errorString("");
	const ejson::String* tmpp = getString(_name);
	if (NULL == tmpp) {
		return errorString;
	}
	return tmpp->get();
}

std::string ejson::Object::getStringValue(const std::string& _name, const std::string& _errorValue) const {
	const ejson::String* tmpp = getString(_name);
	if (NULL == tmpp) {
		return _errorValue;
	}
	return tmpp->get();
}

ejson::Boolean* ejson::Object::getBoolean(const std::string& _name) {
	ejson::Value* tmp = get(_name);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->toBoolean();
}

const ejson::Boolean* ejson::Object::getBoolean(const std::string& _name) const {
	const ejson::Value* tmp = get(_name);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->toBoolean();
}

bool ejson::Object::getBooleanValue(const std::string& _name, bool _errorValue) const {
	const ejson::Boolean* tmpp = getBoolean(_name);
	if (NULL == tmpp) {
		return _errorValue;
	}
	return tmpp->get();
}

ejson::Number* ejson::Object::getNumber(const std::string& _name) {
	ejson::Value* tmp = get(_name);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->toNumber();
}

const ejson::Number* ejson::Object::getNumber(const std::string& _name) const {
	const ejson::Value* tmp = get(_name);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->toNumber();
}

double ejson::Object::getNumberValue(const std::string& _name, double _errorValue) const {
	const ejson::Number* tmpp = getNumber(_name);
	if (NULL == tmpp) {
		return _errorValue;
	}
	return tmpp->get();
}


bool ejson::Object::add(const std::string& _name, ejson::Value* _value) {
	if (NULL == _value) {
		return false;
	}
	if (_name.size() == 0) {
		return false;
	}
	if (m_value.exist(_name)) {
		ejson::Value* tmp = m_value[_name];
		delete(tmp);
		m_value[_name] = _value;
		return true;
	}
	m_value.add(_name, _value);
	return true;
}

bool ejson::Object::addString(const std::string& _name, const std::string& _value) {
	return add(_name, new ejson::String(_value));
}

bool ejson::Object::addNull(const std::string& _name) {
	return add(_name, new ejson::Null());
}

bool ejson::Object::addBoolean(const std::string& _name, bool _value) {
	return add(_name, new ejson::Boolean(_value));
}

bool ejson::Object::addNumber(const std::string& _name, double _value) {
	return add(_name, new ejson::Number(_value));
}

bool ejson::Object::transfertIn(ejson::Value* _obj) {
	if (NULL == _obj) {
		JSON_ERROR("Request transfer on an NULL pointer");
		return false;
	}
	ejson::Object* other = _obj->toObject();
	if (NULL == other) {
		JSON_ERROR("Request transfer on an element that is not an object");
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
ejson::Value* ejson::Object::duplicate(void) const {
	ejson::Object* output = new ejson::Object();
	if (NULL == output) {
		JSON_ERROR("Allocation error ...");
		return NULL;
	}
	for (int32_t iii=0; iii<m_value.size(); ++iii) {
		ejson::Value* val = m_value.getValue(iii);
		std::string key = m_value.getKey(iii);
		if (NULL == val) {
			continue;
		}
		output->add(key, val->duplicate());
	}
	return output;
}
