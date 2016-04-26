/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <ejson/internal/Null.h>
#include <ejson/debug.h>
#include <ejson/internal/Document.h>

ememory::SharedPtr<ejson::internal::Null> ejson::internal::Null::create() {
	return ememory::SharedPtr<ejson::internal::Null>(new ejson::internal::Null());
}


bool ejson::internal::Null::iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) {
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


bool ejson::internal::Null::iGenerate(std::string& _data, size_t _indent) const {
	_data += "null";
	return true;
}


bool ejson::internal::Null::transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) {
	if (_obj == nullptr) {
		EJSON_ERROR("Request transfer on an nullptr pointer");
		return false;
	}
	ememory::SharedPtr<ejson::internal::Null> other = _obj->toNull();
	if (other == nullptr) {
		EJSON_ERROR("Request transfer on an element that is not an Null");
		return false;
	}
	return true;
}

ememory::SharedPtr<ejson::internal::Value> ejson::internal::Null::clone() const {
	ememory::SharedPtr<ejson::internal::Null> output = ejson::internal::Null::create();
	if (output == nullptr) {
		EJSON_ERROR("Allocation error ...");
		return ememory::SharedPtr<ejson::internal::Value>();
	}
	return output;
}


