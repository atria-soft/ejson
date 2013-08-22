/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <ejson/Null.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"Null"

bool ejson::Null::IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc)
{
	JSON_PARSE_ELEMENT("start parse : 'Null' ");
	if (_pos+3 >= _data.Size()){
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
	_pos+=4;
	_filePos+=4;
	return true;
}


bool ejson::Null::IGenerate(etk::UString& _data, int32_t _indent) const
{
	_data += "null";
	return true;
}


bool ejson::Null::TransfertIn(ejson::Value* _obj)
{
	if (NULL==_obj) {
		JSON_ERROR("Request transfer on an NULL pointer");
		return false;
	}
	ejson::Null* other = _obj->ToNull();
	if (NULL==other) {
		JSON_ERROR("Request transfer on an element that is not an Null");
		return false;
	}
	return true;
}

ejson::Value* ejson::Null::Duplicate(void) const
{
	ejson::Null* output = new ejson::Null();
	if (NULL==output) {
		JSON_ERROR("Allocation error ...");
		return NULL;
	}
	return output;
}


