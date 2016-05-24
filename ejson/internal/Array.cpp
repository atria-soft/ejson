/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
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

ememory::SharedPtr<ejson::internal::Array> ejson::internal::Array::create() {
	return ememory::SharedPtr<ejson::internal::Array>(new ejson::internal::Array());
}

void ejson::internal::Array::clear() {
	m_value.clear();
}

bool ejson::internal::Array::iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) {
	EJSON_PARSE_ELEMENT("start parse : 'Object' ");
	for (size_t iii=_pos+1; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
		 drawElementParsed(_data[iii], _filePos);
		#endif
		ejson::FilePos tmpPos;
		if (    _data[iii] == ' '
		     || _data[iii] == '\t'
		     || _data[iii] == '\n'
		     || _data[iii] == '\r') {
			// white space  == > nothing to do ...
		} else if (_data[iii] == '#') {
			// comment Line ...
			for (iii++; iii<_data.size(); iii++) {
				if(    _data[iii] == '\n'
				    || _data[iii] == '\r') {
					break;
				}
			}
		} else if (_data[iii] == ']') {
			// find end of value:
			_pos=iii; //  == > return the end element type ==> usefull to check end and check if adding element is needed
			return true;
		} else if (_data[iii] == '{') {
			// find an object:
			EJSON_PARSE_ELEMENT("find Object");
			ememory::SharedPtr<ejson::internal::Object> tmpElement = ejson::internal::Object::create();
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
			EJSON_PARSE_ELEMENT("find String quoted");
			ememory::SharedPtr<ejson::internal::String> tmpElement = ejson::internal::String::create();
			if (tmpElement == nullptr) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in String");
				_pos=iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
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
			m_value.push_back(tmpElement);
		} else if (    (    _data[iii] == 'f'
		                 && iii+4 < _data.size()
		                 && _data[iii+1] == 'a'
		                 && _data[iii+2] == 'l'
		                 && _data[iii+3] == 's'
		                 && _data[iii+4] == 'e')
		            || (    _data[iii] == 't'
		                 && iii+3 < _data.size()
		                 && _data[iii+1] == 'r'
		                 && _data[iii+2] == 'u'
		                 && _data[iii+3] == 'e') ) {
			// find boolean:
			EJSON_PARSE_ELEMENT("find Boolean");
			ememory::SharedPtr<ejson::internal::Boolean> tmpElement = ejson::internal::Boolean::create();
			if (tmpElement == nullptr) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Boolean");
				_pos=iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
		} else if (    _data[iii] == 'n'
		            && iii+3 < _data.size()
		            && _data[iii+1] == 'u'
		            && _data[iii+2] == 'l'
		            && _data[iii+3] == 'l') {
			// find null:
			EJSON_PARSE_ELEMENT("find Null");
			ememory::SharedPtr<ejson::internal::Null> tmpElement = ejson::internal::Null::create();
			if (tmpElement == nullptr) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Boolean");
				_pos = iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
		} else if (checkNumber(_data[iii]) == true) {
			// find number:
			EJSON_PARSE_ELEMENT("find Number");
			ememory::SharedPtr<ejson::internal::Number> tmpElement = ejson::internal::Number::create();
			if (tmpElement == nullptr) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Boolean");
				_pos=iii;
				return false;
			}
			tmpElement->iParse(_data, iii, _filePos, _doc);
			m_value.push_back(tmpElement);
		} else if (_data[iii] == ',') {
			// find Separator : Restart cycle ...
			// TODO : check if element are separated with ','
		} else if (_data[iii] == '}') {
			// find an error ....
			EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Find '}' with no element in the element... Check if is not a ']' element (to stop array)");
			// move the curent index
			_pos = iii+1;
			return false;
		} else {
			// find an error ....
			EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, std::string("Find '") + _data[iii] + "' with no element in the element...");
			// move the curent index
			_pos = iii+1;
			return false;
		}
	}
	_pos = _data.size();
	return false;
}


bool ejson::internal::Array::iGenerate(std::string& _data, size_t _indent) const {
	bool oneLine=true;
	if (m_value.size()>3) {
		oneLine=false;
	} else {
		for (size_t iii=0; iii<m_value.size() ; iii++) {
			ememory::SharedPtr<const ejson::internal::Value> tmp = m_value[iii];
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
				ememory::SharedPtr<const ejson::internal::String> tmp2 = std::static_pointer_cast<const ejson::internal::String>(tmp);
				if(tmp2->get().size()>40) {
					oneLine=false;
					break;
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

void ejson::internal::Array::iMachineGenerate(std::string& _data) const {
	_data += "[";
	bool needComa = false;
	for (size_t iii=0; iii<m_value.size() ; iii++) {
		if (m_value[iii] == nullptr) {
			continue;
		}
		if (needComa == true) {
			_data += ",";
		}
		m_value[iii]->iMachineGenerate(_data);
		needComa = true;
	}
	_data += "]";
}

size_t ejson::internal::Array::size() const {
	return m_value.size();
}

ememory::SharedPtr<ejson::internal::Value> ejson::internal::Array::get(size_t _id) {
	return m_value[_id];
}

const ememory::SharedPtr<const ejson::internal::Value> ejson::internal::Array::get(size_t _id) const {
	return m_value[_id];
}

bool ejson::internal::Array::add(ememory::SharedPtr<ejson::internal::Value> _element) {
	if (_element == nullptr) {
		EJSON_ERROR("Request add on an nullptr pointer");
		return false;
	}
	m_value.push_back(_element);
	return true;
}

void ejson::internal::Array::remove(size_t _id) {
	if (_id > m_value.size()) {
		EJSON_ERROR("try remove out of bound element");
	}
	m_value.erase(m_value.begin() + _id);
}


bool ejson::internal::Array::transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) {
	if (_obj == nullptr) {
		EJSON_ERROR("Request transfer on an nullptr pointer");
		return false;
	}
	if (_obj->getType() != ejson::valueType::array) {
		EJSON_ERROR("Request transfer on an element that is not an Array");
		return false;
	}
	ememory::SharedPtr<ejson::internal::Array> other = std::static_pointer_cast<ejson::internal::Array>(_obj);
	// remove destination elements
	other->clear();
	// Copy to the destination
	other->m_value = m_value;
	// remove current:
	m_value.clear();
	return true;
}

// TODO : Manage error ...
ememory::SharedPtr<ejson::internal::Value> ejson::internal::Array::clone() const {
	ememory::SharedPtr<ejson::internal::Array> output = ejson::internal::Array::create();
	if (output == nullptr) {
		EJSON_ERROR("Allocation error ...");
		return ememory::SharedPtr<ejson::internal::Value>();
	}
	for (size_t iii=0; iii<m_value.size(); ++iii) {
		ememory::SharedPtr<const ejson::internal::Value> val = m_value[iii];
		if (val == nullptr) {
			continue;
		}
		output->add(val->clone());
	}
	return output;
}

