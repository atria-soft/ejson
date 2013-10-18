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


ejson::Value::~Value(void) {
	clear();
}

etk::CCout& ejson::operator <<(etk::CCout& _os, const ejson::filePos& _obj) {
	_os << "(l=";
	_os << _obj.getLine();
	_os << ",c=";
	_os << _obj.getCol();
	_os << ")";
	return _os;
}


void ejson::Value::addIndent(etk::UString& _data, int32_t _indent) const {
	for (int32_t iii=0; iii<_indent; iii++) {
		_data+="\t";
	}
}

void ejson::Value::drawElementParsed(const etk::UChar& _val, const ejson::filePos& _filePos) const {
	if (_val == '\n') {
		JSON_DEBUG(_filePos << " parse '\\n'");
	} else if (_val == '\t') {
		JSON_DEBUG(_filePos << " parse '\\t'");
	} else {
		JSON_DEBUG(_filePos << " parse '" << _val << "'");
	}
}

int32_t ejson::Value::countWhiteChar(const etk::UString& _data, int32_t _pos, ejson::filePos& _filePos) const {
	_filePos.clear();
	int32_t white=0;
	for (int32_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		if(true == _data[iii].isWhiteChar()) {
			white++;
		} else {
			break;
		}
	}
	--_filePos;
	return white;
}


bool ejson::Value::checkString(const etk::UChar& _val) const {
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
	    || _val == ':'
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

bool ejson::Value::checkNumber(const etk::UChar& _val) const {
	if(    _val == '-'
	    || _val == '+'
	    || _val == 'e'
	    || _val == '.'
	    || (    _val>='0'
	         && _val<='9' ) ) {
		return true;
	}
	return false;
}

