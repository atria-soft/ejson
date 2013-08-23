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
#define __class__	"Array"


void ejson::Array::Clear(void)
{
	for (esize_t iii=0; iii<m_value.Size(); ++iii) {
		if (NULL == m_value[iii]) {
			continue;
		}
		delete(m_value[iii]);
		m_value[iii] = NULL;
	}
	m_value.Clear();
}

bool ejson::Array::IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc)
{
	JSON_PARSE_ELEMENT("start parse : 'Object' ");
	for (int32_t iii=_pos+1; iii<_data.Size(); iii++) {
		_filePos.Check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			DrawElementParsed(_data[iii], _filePos);
		#endif
		ejson::filePos tmpPos;
		if(    _data[iii]==' '
		    || _data[iii]=='\t'
		    || _data[iii]=='\n'
		    || _data[iii]=='\r') {
			// white space ==> nothing to do ...
		} else if(_data[iii]==']') {
			// find end of value:
			_pos=iii; // ==> return the end element type ==> usefull to check end and check if adding element is needed
			return true;
		} else if (_data[iii]=='{') {
			// find an object:
			JSON_PARSE_ELEMENT("find Object");
			ejson::Object * tmpElement = new ejson::Object();
			if (NULL==tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in object");
				_pos=iii;
				return false;
			}
			tmpElement->IParse(_data, iii, _filePos, _doc);
			m_value.PushBack(tmpElement);
		} else if (_data[iii]=='"') {
			// find a string:
			JSON_PARSE_ELEMENT("find String quoted");
			ejson::String * tmpElement = new ejson::String();
			if (NULL==tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in String");
				_pos=iii;
				return false;
			}
			tmpElement->IParse(_data, iii, _filePos, _doc);
			m_value.PushBack(tmpElement);
		} else if (_data[iii]=='[') {
			// find a list:
			JSON_PARSE_ELEMENT("find List");
			ejson::Array * tmpElement = new ejson::Array();
			if (NULL==tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Array");
				_pos=iii;
				return false;
			}
			tmpElement->IParse(_data, iii, _filePos, _doc);
			m_value.PushBack(tmpElement);
		} else if(    _data[iii] == 'f'
		           || _data[iii] == 't' ) {
			// find boolean:
			JSON_PARSE_ELEMENT("find Boolean");
			ejson::Boolean * tmpElement = new ejson::Boolean();
			if (NULL==tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Boolean");
				_pos=iii;
				return false;
			}
			tmpElement->IParse(_data, iii, _filePos, _doc);
			m_value.PushBack(tmpElement);
		} else if( _data[iii] == 'n') {
			// find null:
			JSON_PARSE_ELEMENT("find Null");
			ejson::Null * tmpElement = new ejson::Null();
			if (NULL==tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Boolean");
				_pos=iii;
				return false;
			}
			tmpElement->IParse(_data, iii, _filePos, _doc);
			m_value.PushBack(tmpElement);
		} else if(true==CheckNumber(_data[iii])) {
			// find number:
			JSON_PARSE_ELEMENT("find Number");
			ejson::Number * tmpElement = new ejson::Number();
			if (NULL==tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Boolean");
				_pos=iii;
				return false;
			}
			tmpElement->IParse(_data, iii, _filePos, _doc);
			m_value.PushBack(tmpElement);
		} else if(_data[iii]==',') {
			// find Separator : Restart cycle ...
			// TODO : check if element are separated with ','
		} else {
			// find an error ....
			EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Find '>' with no element in the element...");
			// move the curent index
			_pos = iii+1;
			return false;
		}
	}
	_pos = _data.Size();
	return false;
}


bool ejson::Array::IGenerate(etk::UString& _data, int32_t _indent) const
{
	bool oneLine=true;
	if (m_value.Size()>3) {
		oneLine=false;
	} else {
		for (esize_t iii=0; iii<m_value.Size() ; iii++) {
			ejson::Value* tmp = m_value[iii];
			if (tmp == NULL) {
				continue;
			}
			if (true==tmp->IsObject()) {
				oneLine=false;
				break;
			}
			if (true==tmp->IsArray()) {
				oneLine=false;
				break;
			}
			if (true==tmp->IsString()) {
				ejson::String* tmp2 = tmp->ToString();
				if (NULL!=tmp2) {
					if(tmp2->Get().Size()>40) {
						oneLine=false;
						break;
					}
				}
			}
		}
	}
	if (true==oneLine) {
		_data += "[ ";
	} else {
		_data += "[\n";
	}
	for (esize_t iii=0; iii<m_value.Size() ; iii++) {
		if (false==oneLine) {
			AddIndent(_data, _indent);
		}
		if (NULL != m_value[iii]) {
			m_value[iii]->IGenerate(_data, _indent+1);
			if (iii<m_value.Size()-1) {
				_data += ",";
			}
		}
		if (true==oneLine) {
			_data += " ";
		} else {
			_data += "\n";
		}
	}
	if (false==oneLine) {
		AddIndent(_data, _indent-1);
	}
	_data += "]";
	return true;
}

bool ejson::Array::Add(ejson::Value* _element)
{
	if (NULL==_element) {
		JSON_ERROR("Request add on an NULL pointer");
		return false;
	}
	m_value.PushBack(_element);
	return true;
}

bool ejson::Array::AddString(const etk::UString& _value)
{
	return Add(new ejson::String(_value));
}

bool ejson::Array::AddNull(void)
{
	return Add(new ejson::Null());
}

bool ejson::Array::AddBoolean(bool _value)
{
	return Add(new ejson::Boolean(_value));
}

bool ejson::Array::AddNumber(double _value)
{
	return Add(new ejson::Number(_value));
}


bool ejson::Array::TransfertIn(ejson::Value* _obj)
{
	if (NULL==_obj) {
		JSON_ERROR("Request transfer on an NULL pointer");
		return false;
	}
	ejson::Array* other = _obj->ToArray();
	if (NULL==other) {
		JSON_ERROR("Request transfer on an element that is not an array");
		return false;
	}
	// remove destination elements
	other->Clear();
	// Copy to the destination
	other->m_value = m_value;
	// remove current:
	m_value.Clear();
	return true;
}

// TODO : Manage error ...
ejson::Value* ejson::Array::Duplicate(void) const
{
	ejson::Array* output = new ejson::Array();
	if (NULL==output) {
		JSON_ERROR("Allocation error ...");
		return NULL;
	}
	for (esize_t iii=0; iii<m_value.Size(); ++iii) {
		ejson::Value* val = m_value[iii];
		if (NULL == val) {
			continue;
		}
		output->Add(val->Duplicate());
	}
	return output;
}

ejson::Object* ejson::Array::GetObject(esize_t _id)
{
	ejson::Value* tmpElement = m_value[_id];
	if (NULL == tmpElement) {
		return NULL;
	}
	return tmpElement->ToObject();
}

ejson::String* ejson::Array::GetString(esize_t _id)
{
	ejson::Value* tmpElement = m_value[_id];
	if (NULL == tmpElement) {
		return NULL;
	}
	return tmpElement->ToString();
}

ejson::Array* ejson::Array::GetArray(esize_t _id)
{
	ejson::Value* tmpElement = m_value[_id];
	if (NULL == tmpElement) {
		return NULL;
	}
	return tmpElement->ToArray();
}

ejson::Null* ejson::Array::GetNull(esize_t _id)
{
	ejson::Value* tmpElement = m_value[_id];
	if (NULL == tmpElement) {
		return NULL;
	}
	return tmpElement->ToNull();
}

ejson::Number* ejson::Array::GetNumber(esize_t _id)
{
	ejson::Value* tmpElement = m_value[_id];
	if (NULL == tmpElement) {
		return NULL;
	}
	return tmpElement->ToNumber();
}

ejson::Boolean* ejson::Array::GetBoolean(esize_t _id)
{
	ejson::Value* tmpElement = m_value[_id];
	if (NULL == tmpElement) {
		return NULL;
	}
	return tmpElement->ToBoolean();
}

