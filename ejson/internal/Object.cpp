/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <ejson/internal/Document.hpp>
#include <ejson/internal/Object.hpp>
#include <ejson/internal/Array.hpp>
#include <ejson/internal/String.hpp>
#include <ejson/internal/Null.hpp>
#include <ejson/internal/Number.hpp>
#include <ejson/internal/Boolean.hpp>
#include <ejson/debug.hpp>


ememory::SharedPtr<ejson::internal::Object> ejson::internal::Object::create() {
	return ememory::SharedPtr<ejson::internal::Object>(new ejson::internal::Object());
}
ememory::SharedPtr<ejson::internal::Object> ejson::internal::Object::create(const etk::String& _data) {
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

bool ejson::internal::Object::iParse(const etk::String& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) {
	enum statusParsing mode = parseName;
	etk::String currentName;
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
					EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, etk::String("Find '") + _data[iii] + "' with no element in the element...");
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
bool ejson::internal::Object::iGenerate(etk::String& _data, size_t _indent) const {
	bool oneLine = true;
	if (m_value.size()>3) {
		oneLine = false;
	} else if (_indent<=1) {
		oneLine = false;
	} else {
		for (int32_t iii=0; iii<m_value.size() ; iii++) {
			const ememory::SharedPtr<ejson::internal::Value> tmp = m_value[iii];
			if (tmp == nullptr) {
				continue;
			}
			if (    tmp->getType() == ejson::valueType::object
			     || tmp->getType() == ejson::valueType::document) {
				oneLine=false;
				break;
			}
			if (tmp->getType() == ejson::valueType::array) {
				oneLine=false;
				break;
			}
			if (tmp->getType() == ejson::valueType::string) {
				const ememory::SharedPtr<ejson::internal::String> tmp2 = ememory::staticPointerCast<ejson::internal::String>(tmp);
				if(    tmp2->get().size()>25
				    || m_value.getKey(iii).size()>25) {
					oneLine=false;
					break;
				}
			}
		}
	}
	if (oneLine == true) {
		_data += "{ ";
	} else {
		_data += "{\n";
	}
	for (int32_t iii=0; iii<m_value.size(); ++iii) {
		if (oneLine == false) {
			addIndent(_data, _indent);
		}
		_data += "\"";
		_data += m_value.getKey(iii);
		_data += "\": ";
		m_value.getValue(iii)->iGenerate(_data, _indent+1);
		if (iii<m_value.size()-1) {
			_data += ",";
		}
		if (oneLine == true) {
			_data += " ";
		} else {
			_data += "\n";
		}
	}
	if (oneLine == false) {
		addIndent(_data, _indent-1);
	}
	_data += "}";
	return true;
}

void ejson::internal::Object::iMachineGenerate(etk::String& _data) const {
	_data += "{";
	bool needComa = false;
	for (int32_t iii=0; iii<m_value.size(); ++iii) {
		if (needComa == true) {
			_data += ",";
		}
		needComa = true;
		_data += "\"";
		_data += m_value.getKey(iii);
		_data += "\":";
		m_value.getValue(iii)->iMachineGenerate(_data);
	}
	_data += "}";
}

bool ejson::internal::Object::exist(const etk::String& _name) const {
	return m_value.exist(_name);
}

etk::Vector<etk::String> ejson::internal::Object::getKeys() const {
	return m_value.getKeys();
}

size_t ejson::internal::Object::size() const {
	return m_value.size();
}

ememory::SharedPtr<ejson::internal::Value> ejson::internal::Object::get(size_t _id) {
	return m_value[_id];
}

const ememory::SharedPtr<ejson::internal::Value> ejson::internal::Object::get(size_t _id) const{
	return m_value[_id];
}

ememory::SharedPtr<ejson::internal::Value> ejson::internal::Object::get(const etk::String& _name) {
	if (m_value.exist(_name) == false) {
		return ememory::SharedPtr<ejson::internal::Value>();
	}
	return m_value[_name];
}

const ememory::SharedPtr<ejson::internal::Value> ejson::internal::Object::get(const etk::String& _name) const {
	if (m_value.exist(_name) == false) {
		return ememory::SharedPtr<ejson::internal::Value>();
	}
	return m_value[_name];
}

etk::String ejson::internal::Object::getKey(size_t _id) const {
	return m_value.getKey(_id);
}

bool ejson::internal::Object::add(const etk::String& _name, ememory::SharedPtr<ejson::internal::Value> _value) {
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

void ejson::internal::Object::remove(const etk::String& _name) {
	m_value.remove(_name);
}

void ejson::internal::Object::remove(size_t _id) {
	m_value.remove(getKey(_id));
}

bool ejson::internal::Object::transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) {
	if (_obj == nullptr) {
		EJSON_ERROR("Request transfer on an nullptr pointer");
		return false;
	}
	if (    _obj->getType() != ejson::valueType::object
	     && _obj->getType() != ejson::valueType::document) {
		EJSON_ERROR("Request transfer on an element that is not an object");
		return false;
	}
	ememory::SharedPtr<ejson::internal::Object> other = ememory::staticPointerCast<ejson::internal::Object>(_obj);
	// remove destination elements
	other->clear();
	// Copy to the destination
	other->m_value = m_value;
	// remove current:
	m_value.clear();
	return true;
}

bool ejson::internal::Object::cloneIn(ememory::SharedPtr<ejson::internal::Object>& _obj) const {
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
		etk::String key = m_value.getKey(iii);
		if (val == nullptr) {
			continue;
		}
		output->add(key, val->clone());
	}
	return output;
}
