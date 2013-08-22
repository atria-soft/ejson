/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <ejson/Number.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"Number"

bool ejson::Number::IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc)
{
	JSON_PARSE_ELEMENT("start parse : 'Number' ");
	etk::UString tmpVal;
	for (int32_t iii=_pos+1; iii<_data.Size(); iii++) {
		_filePos.Check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			DrawElementParsed(_data[iii], _filePos);
		#endif
		if(true==CheckNumber(_data[iii])) {
			tmpVal+=_data[iii];
		} else {
			_pos = iii;
			m_value = tmpVal.ToDouble();
			return true;
		}
	}
	_pos=_data.Size();
	EJSON_CREATE_ERROR(_doc, _data, _pos, _filePos, "get end of string whithout fincding end of quote");
	return false;
}


bool ejson::Number::IGenerate(etk::UString& _data, int32_t _indent) const
{
	_data += m_value;
	return true;
}


bool ejson::Number::TransfertIn(ejson::Value* _obj)
{
	if (NULL==_obj) {
		JSON_ERROR("Request transfer on an NULL pointer");
		return false;
	}
	ejson::Number* other = _obj->ToNumber();
	if (NULL==other) {
		JSON_ERROR("Request transfer on an element that is not an Number");
		return false;
	}
	// remove destination elements
	other->m_value = m_value;
	m_value = 0;
	return true;
}

ejson::Value* ejson::Number::Duplicate(void) const
{
	ejson::Number* output = new ejson::Number(m_value);
	if (NULL==output) {
		JSON_ERROR("Allocation error ...");
		return NULL;
	}
	return output;
}


