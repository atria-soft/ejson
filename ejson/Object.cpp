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

#undef __class__
#define __class__	"Object"



std::shared_ptr<ejson::Object> ejson::Object::create() {
	return std::shared_ptr<ejson::Object>(new ejson::Object());
}

void ejson::Object::clear() {
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
		} else if(_data[iii] == '#') {
			// comment Line ...
			for (iii++; iii<_data.size(); iii++) {
				if(    _data[iii] == '\n'
				    || _data[iii] == '\r') {
					break;
				}
			}
		} else if(_data[iii] == '}') {
			// find end of value:
			_pos=iii; //  == > return the end element type ==> usefull to check end and check if adding element is needed
			return true;
		} else {
			if (mode == parseName) {
				JSON_PARSE_ELEMENT("name START " << '"');
				if (    _data[iii] == '"'
				     || _data[iii] == '\'') {
					char startValue=_data[iii];
					currentName = "";
					for (iii++; iii<_data.size(); iii++) {
						_filePos.check(_data[iii]);
						#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
							drawElementParsed(_data[iii], _filePos);
						#endif
						if (_data[iii] == startValue) {
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
					std::shared_ptr<ejson::Object> tmpElement = ejson::Object::create();
					if (tmpElement == nullptr) {
						EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in object");
						_pos=iii;
						return false;
					}
					tmpElement->iParse(_data, iii, _filePos, _doc);
					add(currentName, tmpElement);
					currentName = "";
				} else if (    _data[iii] == '"'
				            || _data[iii] == '\'') {
					// find a string:
					JSON_PARSE_ELEMENT("find String quoted");
					std::shared_ptr<ejson::String> tmpElement = ejson::String::create();
					if (tmpElement == nullptr) {
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
					std::shared_ptr<ejson::Array> tmpElement = ejson::Array::create();
					if (tmpElement == nullptr) {
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
					std::shared_ptr<ejson::Boolean> tmpElement = ejson::Boolean::create();
					if (tmpElement == nullptr) {
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
					std::shared_ptr<ejson::Null> tmpElement = ejson::Null::create();
					if (tmpElement == nullptr) {
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
					std::shared_ptr<ejson::Number> tmpElement = ejson::Number::create();
					if (tmpElement == nullptr) {
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
			std::shared_ptr<ejson::Value> tmp = m_value[iii];
			if (tmp == nullptr) {
				continue;
			}
			if (tmp->isObject() == true) {
				oneLine=false;
				break;
			}
			if (tmp->isArray() == true) {
				oneLine=false;
				break;
			}
			if (tmp->isString() == true) {
				std::shared_ptr<ejson::String> tmp2 = tmp->toString();
				if (tmp2 != nullptr) {
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

std::shared_ptr<ejson::Value> ejson::Object::get(const std::string& _name) {
	if (false == m_value.exist(_name)) {
		return nullptr;
	}
	return m_value[_name];
}

const std::shared_ptr<const ejson::Value> ejson::Object::get(const std::string& _name) const {
	if (false == m_value.exist(_name)) {
		return nullptr;
	}
	return m_value[_name];
}

std::shared_ptr<ejson::Object> ejson::Object::getObject(const std::string& _name) {
	std::shared_ptr<ejson::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return nullptr;
	}
	return std::dynamic_pointer_cast<ejson::Object>(tmp);
}

const std::shared_ptr<const ejson::Object> ejson::Object::getObject(const std::string& _name) const {
	const std::shared_ptr<const ejson::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return nullptr;
	}
	return std::dynamic_pointer_cast<const ejson::Object>(tmp);
}

std::shared_ptr<ejson::Array> ejson::Object::getArray(const std::string& _name) {
	std::shared_ptr<ejson::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return nullptr;
	}
	return std::dynamic_pointer_cast<ejson::Array>(tmp);
}

const std::shared_ptr<const ejson::Array> ejson::Object::getArray(const std::string& _name) const {
	const std::shared_ptr<const ejson::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return nullptr;
	}
	return std::dynamic_pointer_cast<const ejson::Array>(tmp);
}

std::shared_ptr<ejson::Null> ejson::Object::getNull(const std::string& _name) {
	std::shared_ptr<ejson::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return nullptr;
	}
	return std::dynamic_pointer_cast<ejson::Null>(tmp);
}

const std::shared_ptr<const ejson::Null> ejson::Object::getNull(const std::string& _name) const {
	const std::shared_ptr<const ejson::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return nullptr;
	}
	return std::dynamic_pointer_cast<const ejson::Null>(tmp);
}

std::shared_ptr<ejson::String> ejson::Object::getString(const std::string& _name) {
	std::shared_ptr<ejson::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return nullptr;
	}
	return std::dynamic_pointer_cast<ejson::String>(tmp);
}

const std::shared_ptr<const ejson::String> ejson::Object::getString(const std::string& _name) const {
	const std::shared_ptr<const ejson::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return nullptr;
	}
	return std::dynamic_pointer_cast<const ejson::String>(tmp);
}

const std::string& ejson::Object::getStringValue(const std::string& _name) const {
	static const std::string errorString("");
	const std::shared_ptr<const ejson::String> tmpp = getString(_name);
	if (tmpp == nullptr) {
		return errorString;
	}
	return tmpp->get();
}

std::string ejson::Object::getStringValue(const std::string& _name, const std::string& _errorValue) const {
	const std::shared_ptr<const ejson::String> tmpp = getString(_name);
	if (tmpp == nullptr) {
		return _errorValue;
	}
	return tmpp->get();
}

std::shared_ptr<ejson::Boolean> ejson::Object::getBoolean(const std::string& _name) {
	std::shared_ptr<ejson::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return nullptr;
	}
	return tmp->toBoolean();
}

const std::shared_ptr<const ejson::Boolean> ejson::Object::getBoolean(const std::string& _name) const {
	const std::shared_ptr<const ejson::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return nullptr;
	}
	return tmp->toBoolean();
}

bool ejson::Object::getBooleanValue(const std::string& _name, bool _errorValue) const {
	const std::shared_ptr<const ejson::Boolean> tmpp = getBoolean(_name);
	if (tmpp == nullptr) {
		return _errorValue;
	}
	return tmpp->get();
}

std::shared_ptr<ejson::Number> ejson::Object::getNumber(const std::string& _name) {
	std::shared_ptr<ejson::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return nullptr;
	}
	return tmp->toNumber();
}

const std::shared_ptr<const ejson::Number> ejson::Object::getNumber(const std::string& _name) const {
	const std::shared_ptr<const ejson::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return nullptr;
	}
	return tmp->toNumber();
}

double ejson::Object::getNumberValue(const std::string& _name, double _errorValue) const {
	const std::shared_ptr<const ejson::Number> tmpp = getNumber(_name);
	if (tmpp == nullptr) {
		return _errorValue;
	}
	return tmpp->get();
}


bool ejson::Object::add(const std::string& _name, std::shared_ptr<ejson::Value> _value) {
	if (_value == nullptr) {
		return false;
	}
	if (_name.size() == 0) {
		return false;
	}
	if (m_value.exist(_name)) {
		m_value[_name] = _value;
		return true;
	}
	m_value.add(_name, _value);
	return true;
}

bool ejson::Object::addString(const std::string& _name, const std::string& _value) {
	return add(_name, ejson::String::create(_value));
}

bool ejson::Object::addNull(const std::string& _name) {
	return add(_name, ejson::Null::create());
}

bool ejson::Object::addBoolean(const std::string& _name, bool _value) {
	return add(_name, ejson::Boolean::create(_value));
}

bool ejson::Object::addNumber(const std::string& _name, double _value) {
	return add(_name, ejson::Number::create(_value));
}

bool ejson::Object::transfertIn(std::shared_ptr<ejson::Value> _obj) {
	if (_obj == nullptr) {
		JSON_ERROR("Request transfer on an nullptr pointer");
		return false;
	}
	std::shared_ptr<ejson::Object> other = _obj->toObject();
	if (other == nullptr) {
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
std::shared_ptr<ejson::Value> ejson::Object::clone() const {
	std::shared_ptr<ejson::Object> output = ejson::Object::create();
	if (output == nullptr) {
		JSON_ERROR("Allocation error ...");
		return nullptr;
	}
	for (int32_t iii=0; iii<m_value.size(); ++iii) {
		std::shared_ptr<ejson::Value> val = m_value.getValue(iii);
		std::string key = m_value.getKey(iii);
		if (val == nullptr) {
			continue;
		}
		output->add(key, val->clone());
	}
	return output;
}
