/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <ejson/internal/Value.h>
#include <ejson/debug.h>
#include <ejson/internal/Document.h>


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

void ejson::internal::Value::addIndent(std::string& _data, size_t _indent) const {
	for (size_t iii=0; iii<_indent; iii++) {
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

ememory::SharedPtr<ejson::internal::Value> ejson::internal::Value::toValue() {
	return shared_from_this();
};
const ememory::SharedPtr<const ejson::internal::Value> ejson::internal::Value::toValue() const {
	return shared_from_this();
};
ememory::SharedPtr<ejson::internal::Document> ejson::internal::Value::toDocument() {
	return std::dynamic_pointer_cast<ejson::internal::Document>(shared_from_this());
};
const ememory::SharedPtr<const ejson::internal::Document> ejson::internal::Value::toDocument() const {
	return std::dynamic_pointer_cast<const ejson::internal::Document>(shared_from_this());
};
ememory::SharedPtr<ejson::internal::Array> ejson::internal::Value::toArray() {
	return std::dynamic_pointer_cast<ejson::internal::Array>(shared_from_this());
};
const ememory::SharedPtr<const ejson::internal::Array> ejson::internal::Value::toArray() const{
	return std::dynamic_pointer_cast<const ejson::internal::Array>(shared_from_this());
};
ememory::SharedPtr<ejson::internal::Object> ejson::internal::Value::toObject() {
	return std::dynamic_pointer_cast<ejson::internal::Object>(shared_from_this());
};
const ememory::SharedPtr<const ejson::internal::Object> ejson::internal::Value::toObject() const{
	return std::dynamic_pointer_cast<const ejson::internal::Object>(shared_from_this());
};
ememory::SharedPtr<ejson::internal::String> ejson::internal::Value::toString() {
	return std::dynamic_pointer_cast<ejson::internal::String>(shared_from_this());
};
const ememory::SharedPtr<const ejson::internal::String> ejson::internal::Value::toString() const{
	return std::dynamic_pointer_cast<const ejson::internal::String>(shared_from_this());
};
ememory::SharedPtr<ejson::internal::Number> ejson::internal::Value::toNumber() {
	return std::dynamic_pointer_cast<ejson::internal::Number>(shared_from_this());
};
const ememory::SharedPtr<const ejson::internal::Number> ejson::internal::Value::toNumber() const{
	return std::dynamic_pointer_cast<const ejson::internal::Number>(shared_from_this());
};
ememory::SharedPtr<ejson::internal::Boolean> ejson::internal::Value::toBoolean() {
	return std::dynamic_pointer_cast<ejson::internal::Boolean>(shared_from_this());
};
const ememory::SharedPtr<const ejson::internal::Boolean> ejson::internal::Value::toBoolean() const{
	return std::dynamic_pointer_cast<const ejson::internal::Boolean>(shared_from_this());
};
ememory::SharedPtr<ejson::internal::Null> ejson::internal::Value::toNull() {
	return std::dynamic_pointer_cast<ejson::internal::Null>(shared_from_this());
};
const ememory::SharedPtr<const ejson::internal::Null> ejson::internal::Value::toNull() const{
	return std::dynamic_pointer_cast<const ejson::internal::Null>(shared_from_this());
};

void ejson::internal::Value::display() const {
	std::string tmpp;
	iGenerate(tmpp, 0);
	EJSON_INFO("Generated JSON : \n" << tmpp);
}


bool ejson::internal::Value::isDocument() const {
	return toDocument() != nullptr;
}

bool ejson::internal::Value::isArray() const {
	return toArray() != nullptr;
}

bool ejson::internal::Value::isObject() const {
	return toObject() != nullptr;
}

bool ejson::internal::Value::isString() const {
	return toString() != nullptr;
}

bool ejson::internal::Value::isNumber() const {
	return toNumber() != nullptr;
}

bool ejson::internal::Value::isBoolean() const {
	return toBoolean() != nullptr;
}

bool ejson::internal::Value::isNull() const {
	return toNull() != nullptr;
}


void ejson::internal::Value::clear() {
	
}

bool ejson::internal::Value::transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) {
	return false;
}

ememory::SharedPtr<ejson::internal::Value> ejson::internal::Value::clone() const {
	return ememory::SharedPtr<ejson::internal::Value>();
}

