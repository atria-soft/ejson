/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <ejson/Value.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

ejson::Value::~Value() {
	clear();
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

void ejson::Value::drawElementParsed(char32_t _val, const ejson::FilePos& _filePos) const {
	if (_val == '\n') {
		JSON_DEBUG(_filePos << " parse '\\n'");
	} else if (_val == '\t') {
		JSON_DEBUG(_filePos << " parse '\\t'");
	} else {
		JSON_DEBUG(_filePos << " parse '" << _val << "'");
	}
}

int32_t ejson::Value::countWhiteChar(const std::string& _data, size_t _pos, ejson::FilePos& _filePos) const {
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

ememory::SharedPtr<ejson::Value> ejson::Value::toValue() {
	return shared_from_this();
};
const ememory::SharedPtr<const ejson::Value> ejson::Value::toValue() const {
	return shared_from_this();
};
ememory::SharedPtr<ejson::Document> ejson::Value::toDocument() {
	return std::dynamic_pointer_cast<ejson::Document>(shared_from_this());
};
const ememory::SharedPtr<const ejson::Document> ejson::Value::toDocument() const {
	return std::dynamic_pointer_cast<const ejson::Document>(shared_from_this());
};
ememory::SharedPtr<ejson::Array> ejson::Value::toArray() {
	return std::dynamic_pointer_cast<ejson::Array>(shared_from_this());
};
const ememory::SharedPtr<const ejson::Array> ejson::Value::toArray() const{
	return std::dynamic_pointer_cast<const ejson::Array>(shared_from_this());
};
ememory::SharedPtr<ejson::Object> ejson::Value::toObject() {
	return std::dynamic_pointer_cast<ejson::Object>(shared_from_this());
};
const ememory::SharedPtr<const ejson::Object> ejson::Value::toObject() const{
	return std::dynamic_pointer_cast<const ejson::Object>(shared_from_this());
};
ememory::SharedPtr<ejson::String> ejson::Value::toString() {
	return std::dynamic_pointer_cast<ejson::String>(shared_from_this());
};
const ememory::SharedPtr<const ejson::String> ejson::Value::toString() const{
	return std::dynamic_pointer_cast<const ejson::String>(shared_from_this());
};
ememory::SharedPtr<ejson::Number> ejson::Value::toNumber() {
	return std::dynamic_pointer_cast<ejson::Number>(shared_from_this());
};
const ememory::SharedPtr<const ejson::Number> ejson::Value::toNumber() const{
	return std::dynamic_pointer_cast<const ejson::Number>(shared_from_this());
};
ememory::SharedPtr<ejson::Boolean> ejson::Value::toBoolean() {
	return std::dynamic_pointer_cast<ejson::Boolean>(shared_from_this());
};
const ememory::SharedPtr<const ejson::Boolean> ejson::Value::toBoolean() const{
	return std::dynamic_pointer_cast<const ejson::Boolean>(shared_from_this());
};
ememory::SharedPtr<ejson::Null> ejson::Value::toNull() {
	return std::dynamic_pointer_cast<ejson::Null>(shared_from_this());
};
const ememory::SharedPtr<const ejson::Null> ejson::Value::toNull() const{
	return std::dynamic_pointer_cast<const ejson::Null>(shared_from_this());
};

void ejson::Value::display() const {
	std::string tmpp;
	iGenerate(tmpp, 0);
	JSON_INFO("Generated JSON : \n" << tmpp);
}


bool ejson::Value::isDocument() const {
	return toDocument() != nullptr;
}

bool ejson::Value::isArray() const {
	return toArray() != nullptr;
}

bool ejson::Value::isObject() const {
	return toObject() != nullptr;
}

bool ejson::Value::isString() const {
	return toString() != nullptr;
}

bool ejson::Value::isNumber() const {
	return toNumber() != nullptr;
}

bool ejson::Value::isBoolean() const {
	return toBoolean() != nullptr;
}

bool ejson::Value::isNull() const {
	return toNull() != nullptr;
}


void ejson::Value::clear() {
	
}

bool ejson::Value::transfertIn(ememory::SharedPtr<ejson::Value> _obj) {
	return false;
}

ememory::SharedPtr<ejson::Value> ejson::Value::clone() const {
	return ememory::SharedPtr<ejson::Value>();
}

