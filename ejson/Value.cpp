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

std::ostream& ejson::operator <<(std::ostream& _os, const ejson::filePos& _obj) {
	_os << "(l=";
	_os << _obj.getLine();
	_os << ",c=";
	_os << _obj.getCol();
	_os << ")";
	return _os;
}


bool ejson::Value::isWhiteChar(char32_t _val) {
	if(    _val == ' '
	    || _val == '\t'
	    || _val == '\n'
	    || _val == '\r') {
		return true;
	}
	return false;
}


void ejson::Value::addIndent(std::string& _data, size_t _indent) const {
	for (size_t iii=0; iii<_indent; iii++) {
		_data+="\t";
	}
}

void ejson::Value::drawElementParsed(char32_t _val, const ejson::filePos& _filePos) const {
	if (_val == '\n') {
		JSON_DEBUG(_filePos << " parse '\\n'");
	} else if (_val == '\t') {
		JSON_DEBUG(_filePos << " parse '\\t'");
	} else {
		JSON_DEBUG(_filePos << " parse '" << _val << "'");
	}
}

int32_t ejson::Value::countWhiteChar(const std::string& _data, size_t _pos, ejson::filePos& _filePos) const {
	_filePos.clear();
	size_t white=0;
	for (size_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		if(true == isWhiteChar(_data[iii])) {
			white++;
		} else {
			break;
		}
	}
	--_filePos;
	return white;
}


bool ejson::Value::checkString(char32_t _val) const {
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

bool ejson::Value::checkNumber(char32_t _val) const {
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


ejson::Document* ejson::Value::toDocument(void) {
	return dynamic_cast<ejson::Document*>(this);
};
const ejson::Document* ejson::Value::toDocument(void) const {
	return dynamic_cast<const ejson::Document*>(this);
};
ejson::Array* ejson::Value::toArray(void) {
	return dynamic_cast<ejson::Array*>(this);
};
const ejson::Array* ejson::Value::toArray(void) const{
	return dynamic_cast<const ejson::Array*>(this);
};
ejson::Object* ejson::Value::toObject(void) {
	return dynamic_cast<ejson::Object*>(this);
};
const ejson::Object* ejson::Value::toObject(void) const{
	return dynamic_cast<const ejson::Object*>(this);
};
ejson::String* ejson::Value::toString(void) {
	return dynamic_cast<ejson::String*>(this);
};
const ejson::String* ejson::Value::toString(void) const{
	return dynamic_cast<const ejson::String*>(this);
};
ejson::Number* ejson::Value::toNumber(void) {
	return dynamic_cast<ejson::Number*>(this);
};
const ejson::Number* ejson::Value::toNumber(void) const{
	return dynamic_cast<const ejson::Number*>(this);
};
ejson::Boolean* ejson::Value::toBoolean(void) {
	return dynamic_cast<ejson::Boolean*>(this);
};
const ejson::Boolean* ejson::Value::toBoolean(void) const{
	return dynamic_cast<const ejson::Boolean*>(this);
};
ejson::Null* ejson::Value::toNull(void) {
	return dynamic_cast<ejson::Null*>(this);
};
const ejson::Null* ejson::Value::toNull(void) const{
	return dynamic_cast<const ejson::Null*>(this);
};