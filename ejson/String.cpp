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
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"String"

void ejson::String::Clear(void)
{
	
}


bool ejson::String::IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc)
{
	JSON_PARSE_ELEMENT("start parse : 'String' ");
	for (int32_t iii=_pos+1; iii<_data.Size(); iii++) {
		_filePos.Check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			DrawElementParsed(_data[iii], _filePos);
		#endif
		ejson::filePos tmpPos;
		if(m_quoted==true) {
			// TODO : manage \x
			if(    _data[iii]!= '\"') {
				m_value += _data[iii];
			} else {
				_pos = iii;
				return true;
			}
		} else {
			if (CheckAvaillable(_data[iii]) ) {
				m_value += _data[iii];
			} else {
				_pos = iii;
				return true;
			}
		}
	}
	if(m_quoted==true) {
		_pos=_data.Size();
		EJSON_CREATE_ERROR(_doc, _data, _pos, _filePos, "get end of string whithout fincding end of quote");
		return false;
	}
	_pos=_data.Size();
	return true;
}


bool ejson::String::IGenerate(etk::UString& _data, int32_t _indent) const
{
	//if (m_quoted==true) {
		_data += "\"";;
	//}
	_data += m_value;
	//if (m_quoted==true) {
		_data += "\"";;
	//}
	return true;
}


bool ejson::String::TransfertIn(ejson::Value* _obj)
{
	if (NULL==_obj) {
		JSON_ERROR("Request transfer on an NULL pointer");
		return false;
	}
	ejson::String* other = _obj->ToString();
	if (NULL==other) {
		JSON_ERROR("Request transfer on an element that is not an String");
		return false;
	}
	// remove destination elements
	other->m_quoted = m_quoted;
	other->m_value = m_value;
	m_quoted = true;
	m_value = "";
	return true;
}

ejson::Value* ejson::String::Duplicate(void) const
{
	ejson::String* output = new ejson::String(m_quoted);
	if (NULL==output) {
		JSON_ERROR("Allocation error ...");
		return NULL;
	}
	output->SetValue(m_value);
	return output;
}


