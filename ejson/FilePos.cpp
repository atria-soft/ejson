/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <ejson/FilePos.h>

ejson::FilePos::FilePos() :
  m_col(0),
  m_line(0) {
	
}

ejson::FilePos::FilePos(size_t _line, size_t _col) :
  m_col(_col),
  m_line(_line) {
	
}

ejson::FilePos& ejson::FilePos::operator ++() {
	m_col++;
	return *this;
}

ejson::FilePos& ejson::FilePos::operator --() {
	if(m_col>0) {
		m_col--;
	}
	return *this;
}

ejson::FilePos& ejson::FilePos::operator +=(const ejson::FilePos& _obj) {
	if (_obj.m_line == 0) {
		m_col += _obj.m_col;
	} else {
		m_col = _obj.m_col;
		m_line += _obj.m_line;
	}
	return *this;
}

ejson::FilePos& ejson::FilePos::operator +=(size_t _col) {
	m_col += _col;
	return *this;
}

ejson::FilePos& ejson::FilePos::operator= (const ejson::FilePos& _obj ) {
	m_col = _obj.m_col;
	m_line = _obj.m_line;
	return *this;
}

void ejson::FilePos::newLine() {
	m_col=0;
	m_line++;
}

bool ejson::FilePos::check(char32_t _val) {
	m_col++;
	if (_val == '\n') {
		newLine();
		return true;
	}
	return false;
}

void ejson::FilePos::set(size_t _line, size_t _col) {
	m_col = _col;
	m_line = _line;
}

void ejson::FilePos::clear() {
	m_col = 0;
	m_line = 0;
}

size_t ejson::FilePos::getCol() const {
	return m_col;
}

size_t ejson::FilePos::getLine() const {
	return m_line;
}

std::ostream& ejson::operator <<(std::ostream& _os, const ejson::FilePos& _obj) {
	_os << "(l=";
	_os << _obj.getLine();
	_os << ",c=";
	_os << _obj.getCol();
	_os << ")";
	return _os;
}
