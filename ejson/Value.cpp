/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <ejson/Value.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"Value"


etk::CCout& ejson::operator <<(etk::CCout& _os, const ejson::filePos& _obj)
{
	_os << "(l=";
	_os << _obj.GetLine();
	_os << ",c=";
	_os << _obj.GetCol();
	_os << ")";
	return _os;
}


void ejson::Value::AddIndent(etk::UString& _data, int32_t _indent) const
{
	for (int32_t iii=0; iii<_indent; iii++) {
		_data+="\t";
	}
}

void ejson::Value::DrawElementParsed(const etk::UniChar& _val, const ejson::filePos& _filePos) const
{
	if (_val=='\n') {
		JSON_DEBUG(_filePos << " Parse '\\n'");
	} else if (_val=='\t') {
		JSON_DEBUG(_filePos << " Parse '\\t'");
	} else {
		JSON_DEBUG(_filePos << " Parse '" << _val << "'");
	}
}

int32_t ejson::Value::CountWhiteChar(const etk::UString& _data, int32_t _pos, ejson::filePos& _filePos) const
{
	_filePos.Clear();
	int32_t white=0;
	for (int32_t iii=_pos; iii<_data.Size(); iii++) {
		_filePos.Check(_data[iii]);
		if(true == _data[iii].IsWhiteChar()) {
			white++;
		} else {
			break;
		}
	}
	--_filePos;
	return white;
}


bool ejson::Value::CheckAvaillable(const etk::UniChar& _val, bool _firstChar) const
{
	if(    _val == '!'
	    || _val == '"'
	    || _val == '#'
	    || _val == '$'
	    || _val == '%'
	    || _val == '&'
	    || _val == '\'' // '
	    || _val == '('
	    || _val == ')'
	    || _val == '*'
	    || _val == '+'
	    || _val == ','
	    || _val == '/'
	    || _val == ';'
	    || _val == '<'
	    || _val == '='
	    || _val == '>'
	    || _val == '?'
	    || _val == '@'
	    || _val == '['
	    || _val == '\\'
	    || _val == ']'
	    || _val == '^'
	    || _val == '`'
	    || _val == '{'
	    || _val == '|'
	    || _val == '}'
	    || _val == '~'
	    || _val == ' '
	    || _val == '\n'
	    || _val == '\t'
	    || _val == '\r') {
		return false;
	}
	return true;
}


bool ejson::Value::IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc)
{
	JSON_PARSE_ELEMENT("start parse : 'Value' ");
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
		} else if (_data[iii]=='{') {
			// find an object:
			
		} else if (_data[iii]=='"') {
			// find a string:
			
		} else if (_data[iii]=='[') {
			// find a list:
			
		} else if( CheckAvaillable(_data[iii]) ) {
			// find a string without "" ==> special hook for the etk-json parser
			
		} else if(    _data[iii]==']'
		           || _data[iii]=='}'
		           || _data[iii]==',') {
			// find end of value:
			_pos+=iii; // ==> return the end element type ==> usefull to check end and check if adding element is needed
			return true;
		} else {
			// find an error ....
			EJSON_CREATE_ERROR(_doc, _data, _pos, _filePos, "Find '>' with no element in the element...");
			// move the curent index
			_pos += iii+1;
			return false;
		}
	}
	
	return false;
}
