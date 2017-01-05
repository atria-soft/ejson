/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <ejson/internal/Value.hpp>
#include <ejson/debug.hpp>
#include <ejson/internal/Document.hpp>


enum ejson::valueType ejson::internal::Value::getType() const {
	return m_type;
}

ejson::internal::Value::~Value() {
	clear();
}

bool ejson::internal::Value::isWhiteChar(char32_t _val) {
	if(    _val == ' '
	    || _val == '\t'
	    || _val == '\n'
	    || _val == '\r') {
		return true;
	}
	return false;
}

void ejson::internal::Value::addIndent(std::string& _data, int32_t _indent) const {
	if (_indent <= 0) {
		return;
	}
	for (int32_t iii=0; iii<_indent; iii++) {
		_data+="\t";
	}
}

void ejson::internal::Value::drawElementParsed(char32_t _val, const ejson::FilePos& _filePos) const {
	if (_val == '\n') {
		EJSON_DEBUG(_filePos << " parse '\\n'");
	} else if (_val == '\t') {
		EJSON_DEBUG(_filePos << " parse '\\t'");
	} else {
		EJSON_DEBUG(_filePos << " parse '" << _val << "'");
	}
}

int32_t ejson::internal::Value::countWhiteChar(const std::string& _data, size_t _pos, ejson::FilePos& _filePos) const {
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

bool ejson::internal::Value::checkString(char32_t _val) const {
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

bool ejson::internal::Value::checkNumber(char32_t _val) const {
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

void ejson::internal::Value::display() const {
	std::string tmpp;
	iGenerate(tmpp, 0);
	EJSON_INFO("Generated JSON : \n" << tmpp);
}

void ejson::internal::Value::clear() {
	
}

bool ejson::internal::Value::transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) {
	return false;
}

ememory::SharedPtr<ejson::internal::Value> ejson::internal::Value::clone() const {
	return ememory::SharedPtr<ejson::internal::Value>();
}

