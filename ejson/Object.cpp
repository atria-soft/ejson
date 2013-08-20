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
#define __class__	"Object"

void ejson::Object::Clear(void)
{
	
}
typedef enum {
	parseName,
	parseMiddle,
	parseValue,
} statusParsing_te;

bool ejson::Object::IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc)
{
	statusParsing_te mode = parseName;
	etk::UString currentName;
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
		} else if(_data[iii]=='}') {
			// find end of value:
			_pos=iii; // ==> return the end element type ==> usefull to check end and check if adding element is needed
			return true;
		} else {
			if (mode == parseName) {
				JSON_PARSE_ELEMENT("name START " << '"');
				if (_data[iii]=='"') {
					currentName = "";
					for (iii++; iii<_data.Size(); iii++) {
						_filePos.Check(_data[iii]);
						#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
							DrawElementParsed(_data[iii], _filePos);
						#endif
						if (_data[iii]=='\"') {
							mode = parseMiddle;
							break;
						} else {
							currentName += _data[iii];
						}
					}
				} else if (CheckAvaillable(_data[iii]) ) {
					currentName += _data[iii];
					for (iii++; iii<_data.Size(); iii++) {
						_filePos.Check(_data[iii]);
						#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
							DrawElementParsed(_data[iii], _filePos);
						#endif
						if (false==CheckAvaillable(_data[iii])) {
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
				if (_data[iii]==':') {
					mode = parseValue;
				} else {
					EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "separator is not ':'");
					return false;
				}
			} else if (mode == parseValue) {
				if (_data[iii]=='{') {
					// find an object:
					JSON_PARSE_ELEMENT("find Object");
					ejson::Object * tmpElement = new ejson::Object();
					if (NULL==tmpElement) {
						EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in object");
						_pos=iii;
						return false;
					}
					tmpElement->IParse(_data, iii, _filePos, _doc);
					m_value.Add(currentName, tmpElement);
					currentName = "";
				} else if (_data[iii]=='"') {
					// find a string:
					JSON_PARSE_ELEMENT("find String quoted");
					ejson::String * tmpElement = new ejson::String(true);
					if (NULL==tmpElement) {
						EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in String");
						_pos=iii;
						return false;
					}
					tmpElement->IParse(_data, iii, _filePos, _doc);
					m_value.Add(currentName, tmpElement);
					currentName = "";
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
					m_value.Add(currentName, tmpElement);
					currentName = "";
				} else if( CheckAvaillable(_data[iii]) ) {
					// find a string without "" ==> special hook for the etk-json parser
					JSON_PARSE_ELEMENT("find String");
					ejson::String * tmpElement = new ejson::String(false);
					if (NULL==tmpElement) {
						EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in String");
						_pos=iii;
						return false;
					}
					iii--;
					tmpElement->IParse(_data, iii, _filePos, _doc);
					iii--;
					//JSON_ERROR(" add : " << currentName );
					m_value.Add(currentName, tmpElement);
					currentName = "";
				} else if(_data[iii]==',') {
					// find Separator : Restart cycle ...
					mode = parseName;
					currentName = "";
				} else {
					// find an error ....
					EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Find '>' with no element in the element...");
					// move the curent index
					_pos = iii+1;
					return false;
				}
			}
		}
	}
	_pos = _data.Size();
	return false;
}
bool ejson::Object::IGenerate(etk::UString& _data, int32_t _indent) const
{
	_data += "{\n";
	for (esize_t iii=0; iii<m_value.Size() ; iii++) {
		AddIndent(_data, _indent);
		_data += "\"";
		_data += m_value.GetKey(iii);
		_data += "\": ";
		m_value.GetValue(iii)->IGenerate(_data, _indent+1);
		if (iii<m_value.Size()-1) {
			_data += ",";
		}
		_data += "\n";
	}
	AddIndent(_data, _indent-1);
	_data += "}";
	return true;
}


ejson::Value* ejson::Object::GetSub(const etk::UString& _named) const
{
	return m_value[_named];
}

ejson::Object* ejson::Object::GetSubObject(const etk::UString& _named) const
{
	ejson::Value* tmp = m_value[_named];
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->ToObject();
}

ejson::String* ejson::Object::GetSubString(const etk::UString& _named) const
{
	ejson::Value* tmp = m_value[_named];
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->ToString();
}

ejson::Array* ejson::Object::GetSubArray(const etk::UString& _named) const
{
	ejson::Value* tmp = m_value[_named];
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->ToArray();
}


void ejson::Object::AddSub(const etk::UString& _name, ejson::Value* _value)
{
	if (NULL == _value) {
		return;
	}
	if (_name.Size()==0) {
		return;
	}
	m_value.Add(_name, _value);
}

