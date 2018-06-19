/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <ejson/internal/Null.hpp>
#include <ejson/debug.hpp>
#include <ejson/internal/Document.hpp>

ememory::SharedPtr<ejson::internal::Null> ejson::internal::Null::create() {
	return ememory::SharedPtr<ejson::internal::Null>(ETK_NEW(ejson::internal::Null));
}

ejson::internal::Null::Null() {
	m_type = ejson::valueType::null;
}

bool ejson::internal::Null::iParse(const etk::String& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) {
	EJSON_PARSE_ELEMENT("start parse : 'Null' ");
	if (_pos+3 >= _data.size()){
		EJSON_CREATE_ERROR(_doc, _data, _pos, _filePos, "can not parse null !!! ");
		return false;
	}
	if(    _data[_pos] != 'n'
	    || _data[_pos+1] != 'u'
	    || _data[_pos+2] != 'l'
	    || _data[_pos+3] != 'l' ) {
		EJSON_CREATE_ERROR(_doc, _data, _pos, _filePos, "Not a corect 'null' element");
		return false;
	}
	_pos+=3;
	_filePos+=3;
	return true;
}


bool ejson::internal::Null::iGenerate(etk::String& _data, size_t _indent) const {
	_data += "null";
	return true;
}

void ejson::internal::Null::iMachineGenerate(etk::String& _data) const {
	_data += "null";
}


bool ejson::internal::Null::transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) {
	if (_obj == null) {
		EJSON_ERROR("Request transfer on an null pointer");
		return false;
	}
	if (_obj->getType() == ejson::valueType::null) {
		EJSON_ERROR("Request transfer on an element that is not an Null");
		return false;
	}
	return true;
}

ememory::SharedPtr<ejson::internal::Value> ejson::internal::Null::clone() const {
	ememory::SharedPtr<ejson::internal::Null> output = ejson::internal::Null::create();
	if (output == null) {
		EJSON_ERROR("Allocation error ...");
		return ememory::SharedPtr<ejson::internal::Value>();
	}
	return output;
}


