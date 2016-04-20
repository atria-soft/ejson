/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */


#include <ejson/internal/Document.h>
#include <ejson/internal/Object.h>
#include <ejson/internal/Array.h>
#include <ejson/internal/String.h>
#include <ejson/internal/Null.h>
#include <ejson/internal/Number.h>
#include <ejson/internal/Boolean.h>
#include <ejson/debug.h>


ememory::SharedPtr<ejson::internal::Object> ejson::internal::Object::create() {
	return ememory::SharedPtr<ejson::internal::Object>(new ejson::internal::Object());
}
ememory::SharedPtr<ejson::internal::Object> ejson::internal::Object::create(const std::string& _data) {
	ejson::internal::Document doc;
	doc.parse(_data);
	return doc.cloneObj();
}


void ejson::internal::Object::clear() {
	m_value.clear();
}


enum statusParsing {
	parseName,
	parseMiddle,
	parseValue,
};

bool ejson::internal::Object::iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) {
	enum statusParsing mode = parseName;
	std::string currentName;
	EJSON_PARSE_ELEMENT("start parse : 'Object' ");
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
		} else if(_data[iii] == '}') {
			// find end of value:
			_pos=iii; //  == > return the end element type ==> usefull to check end and check if adding element is needed
			return true;
		} else {
			if (mode == parseName) {
				EJSON_PARSE_ELEMENT("name START " << '"');
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
				EJSON_PARSE_ELEMENT("name END ");
			} else if (mode == parseMiddle) {
				EJSON_PARSE_ELEMENT(" middle ... ");
				if (_data[iii] == ':') {
					mode = parseValue;
				} else {
					EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "separator is not ':'");
					return false;
				}
			} else if (mode == parseValue) {
				if (_data[iii] == '{') {
					// find an object:
					EJSON_PARSE_ELEMENT("find Object");
					ememory::SharedPtr<ejson::internal::Object> tmpElement = ejson::internal::Object::create();
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
					EJSON_PARSE_ELEMENT("find String quoted");
					ememory::SharedPtr<ejson::internal::String> tmpElement = ejson::internal::String::create();
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
					EJSON_PARSE_ELEMENT("find List");
					ememory::SharedPtr<ejson::internal::Array> tmpElement = ejson::internal::Array::create();
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
					EJSON_PARSE_ELEMENT("find Boolean");
					ememory::SharedPtr<ejson::internal::Boolean> tmpElement = ejson::internal::Boolean::create();
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
					EJSON_PARSE_ELEMENT("find Null");
					ememory::SharedPtr<ejson::internal::Null> tmpElement = ejson::internal::Null::create();
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
					EJSON_PARSE_ELEMENT("find Number");
					ememory::SharedPtr<ejson::internal::Number> tmpElement = ejson::internal::Number::create();
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
bool ejson::internal::Object::iGenerate(std::string& _data, size_t _indent) const {
	bool oneLine=true;
	if (m_value.size()>3) {
		oneLine=false;
	} else if (_indent<=1) {
		oneLine=false;
	} else {
		for (int32_t iii=0; iii<m_value.size() ; iii++) {
			ememory::SharedPtr<ejson::internal::Value> tmp = m_value[iii];
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
				ememory::SharedPtr<ejson::internal::String> tmp2 = tmp->toString();
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

bool ejson::internal::Object::exist(const std::string& _name) const {
	return m_value.exist(_name);
}

ememory::SharedPtr<ejson::internal::Value> ejson::internal::Object::get(const std::string& _name) {
	if (false == m_value.exist(_name)) {
		return ememory::SharedPtr<ejson::internal::Value>();
	}
	return m_value[_name];
}

const ememory::SharedPtr<const ejson::internal::Value> ejson::internal::Object::get(const std::string& _name) const {
	if (false == m_value.exist(_name)) {
		return ememory::SharedPtr<const ejson::internal::Value>();
	}
	return m_value[_name];
}

ememory::SharedPtr<ejson::internal::Object> ejson::internal::Object::getObject(const std::string& _name) {
	ememory::SharedPtr<ejson::internal::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return ememory::SharedPtr<ejson::internal::Object>();
	}
	return std::dynamic_pointer_cast<ejson::internal::Object>(tmp);
}

const ememory::SharedPtr<const ejson::internal::Object> ejson::internal::Object::getObject(const std::string& _name) const {
	const ememory::SharedPtr<const ejson::internal::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return ememory::SharedPtr<const ejson::internal::Object>();
	}
	return std::dynamic_pointer_cast<const ejson::internal::Object>(tmp);
}

ememory::SharedPtr<ejson::internal::Array> ejson::internal::Object::getArray(const std::string& _name) {
	ememory::SharedPtr<ejson::internal::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return ememory::SharedPtr<ejson::internal::Array>();
	}
	return std::dynamic_pointer_cast<ejson::internal::Array>(tmp);
}

const ememory::SharedPtr<const ejson::internal::Array> ejson::internal::Object::getArray(const std::string& _name) const {
	const ememory::SharedPtr<const ejson::internal::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return ememory::SharedPtr<const ejson::internal::Array>();
	}
	return std::dynamic_pointer_cast<const ejson::internal::Array>(tmp);
}

ememory::SharedPtr<ejson::internal::Null> ejson::internal::Object::getNull(const std::string& _name) {
	ememory::SharedPtr<ejson::internal::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return ememory::SharedPtr<ejson::internal::Null>();
	}
	return std::dynamic_pointer_cast<ejson::internal::Null>(tmp);
}

const ememory::SharedPtr<const ejson::internal::Null> ejson::internal::Object::getNull(const std::string& _name) const {
	const ememory::SharedPtr<const ejson::internal::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return ememory::SharedPtr<const ejson::internal::Null>();
	}
	return std::dynamic_pointer_cast<const ejson::internal::Null>(tmp);
}

ememory::SharedPtr<ejson::internal::String> ejson::internal::Object::getString(const std::string& _name) {
	ememory::SharedPtr<ejson::internal::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return ememory::SharedPtr<ejson::internal::String>();
	}
	return std::dynamic_pointer_cast<ejson::internal::String>(tmp);
}

const ememory::SharedPtr<const ejson::internal::String> ejson::internal::Object::getString(const std::string& _name) const {
	const ememory::SharedPtr<const ejson::internal::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return ememory::SharedPtr<const ejson::internal::String>();
	}
	return std::dynamic_pointer_cast<const ejson::internal::String>(tmp);
}

const std::string& ejson::internal::Object::getStringValue(const std::string& _name) const {
	static const std::string errorString("");
	const ememory::SharedPtr<const ejson::internal::String> tmpp = getString(_name);
	if (tmpp == nullptr) {
		return errorString;
	}
	return tmpp->get();
}

std::string ejson::internal::Object::getStringValue(const std::string& _name, const std::string& _errorValue) const {
	const ememory::SharedPtr<const ejson::internal::String> tmpp = getString(_name);
	if (tmpp == nullptr) {
		return _errorValue;
	}
	return tmpp->get();
}

ememory::SharedPtr<ejson::internal::Boolean> ejson::internal::Object::getBoolean(const std::string& _name) {
	ememory::SharedPtr<ejson::internal::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return ememory::SharedPtr<ejson::internal::Boolean>();
	}
	return tmp->toBoolean();
}

const ememory::SharedPtr<const ejson::internal::Boolean> ejson::internal::Object::getBoolean(const std::string& _name) const {
	const ememory::SharedPtr<const ejson::internal::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return ememory::SharedPtr<const ejson::internal::Boolean>();
	}
	return tmp->toBoolean();
}

bool ejson::internal::Object::getBooleanValue(const std::string& _name, bool _errorValue) const {
	const ememory::SharedPtr<const ejson::internal::Boolean> tmpp = getBoolean(_name);
	if (tmpp == nullptr) {
		return _errorValue;
	}
	return tmpp->get();
}

ememory::SharedPtr<ejson::internal::Number> ejson::internal::Object::getNumber(const std::string& _name) {
	ememory::SharedPtr<ejson::internal::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return ememory::SharedPtr<ejson::internal::Number>();
	}
	return tmp->toNumber();
}

const ememory::SharedPtr<const ejson::internal::Number> ejson::internal::Object::getNumber(const std::string& _name) const {
	const ememory::SharedPtr<const ejson::internal::Value> tmp = get(_name);
	if (tmp == nullptr) {
		return ememory::SharedPtr<const ejson::internal::Number>();
	}
	return tmp->toNumber();
}

double ejson::internal::Object::getNumberValue(const std::string& _name, double _errorValue) const {
	const ememory::SharedPtr<const ejson::internal::Number> tmpp = getNumber(_name);
	if (tmpp == nullptr) {
		return _errorValue;
	}
	return tmpp->get();
}


bool ejson::internal::Object::add(const std::string& _name, ememory::SharedPtr<ejson::internal::Value> _value) {
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

bool ejson::internal::Object::addString(const std::string& _name, const std::string& _value) {
	return add(_name, ejson::internal::String::create(_value));
}

bool ejson::internal::Object::addNull(const std::string& _name) {
	return add(_name, ejson::internal::Null::create());
}

bool ejson::internal::Object::addBoolean(const std::string& _name, bool _value) {
	return add(_name, ejson::internal::Boolean::create(_value));
}

bool ejson::internal::Object::addNumber(const std::string& _name, double _value) {
	return add(_name, ejson::internal::Number::create(_value));
}

bool ejson::internal::Object::transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) {
	if (_obj == nullptr) {
		EJSON_ERROR("Request transfer on an nullptr pointer");
		return false;
	}
	ememory::SharedPtr<ejson::internal::Object> other = _obj->toObject();
	if (other == nullptr) {
		EJSON_ERROR("Request transfer on an element that is not an object");
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

bool ejson::internal::Object::cloneIn(const ememory::SharedPtr<ejson::internal::Object>& _obj) const {
	if (_obj == nullptr) {
		return false;
	}
	_obj->clear();
	for (int32_t iii=0; iii<m_value.size(); ++iii) {
		_obj->add(m_value.getKey(iii), m_value[iii]->clone());
	}
	return true;
}


// TODO : Manage error ...
ememory::SharedPtr<ejson::internal::Value> ejson::internal::Object::clone() const {
	return cloneObj();
}

ememory::SharedPtr<ejson::internal::Object> ejson::internal::Object::cloneObj() const {
	ememory::SharedPtr<ejson::internal::Object> output = ejson::internal::Object::create();
	if (output == nullptr) {
		EJSON_ERROR("Allocation error ...");
		return ememory::SharedPtr<ejson::internal::Object>();
	}
	for (int32_t iii=0; iii<m_value.size(); ++iii) {
		ememory::SharedPtr<ejson::internal::Value> val = m_value.getValue(iii);
		std::string key = m_value.getKey(iii);
		if (val == nullptr) {
			continue;
		}
		output->add(key, val->clone());
	}
	return output;
}
