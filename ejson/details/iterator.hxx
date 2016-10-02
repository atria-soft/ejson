/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#include <ejson/iterator.hpp>

template<class EJSON_BASE_T>
ejson::iterator<EJSON_BASE_T>::iterator(EJSON_BASE_T& _obj, size_t _pos) :
  m_data(_obj),
  m_id(_pos) {
	m_id = std::avg(size_t(0), m_id, m_data.size());
}

template<class EJSON_BASE_T>
ejson::iterator<EJSON_BASE_T>::iterator(const EJSON_BASE_T& _obj, size_t _pos) :
  m_data(const_cast<EJSON_BASE_T&>(_obj)),
  m_id(_pos) {
	m_id = std::avg(size_t(0), m_id, m_data.size());
}

template<class EJSON_BASE_T>
ejson::iterator<EJSON_BASE_T>::iterator(const ejson::iterator<EJSON_BASE_T>& _obj) :
  m_data(_obj.m_data),
  m_id(_obj.m_id) {
	m_id = std::avg(size_t(0), m_id, m_data.size());
}

template<class EJSON_BASE_T>
ejson::iterator<EJSON_BASE_T>& ejson::iterator<EJSON_BASE_T>::operator= (const ejson::iterator<EJSON_BASE_T>& _obj) {
	m_data = _obj.m_data;
	m_id = _obj.m_id;
	m_id = std::avg(size_t(0), m_id, m_data.size());
	return *this;
}

template<class EJSON_BASE_T>
ejson::iterator<EJSON_BASE_T>& ejson::iterator<EJSON_BASE_T>::operator+= (int32_t _val) {
	int64_t val = m_id;
	val += _val;
	m_id = std::avg(int64_t(0), val, int64_t(m_data.size()));
	return *this;
}

template<class EJSON_BASE_T>
ejson::iterator<EJSON_BASE_T> ejson::iterator<EJSON_BASE_T>::operator+ (int32_t _val) const {
	ejson::iterator<EJSON_BASE_T> result(*this);
	result += _val;
	return result;
}

template<class EJSON_BASE_T>
ejson::iterator<EJSON_BASE_T>& ejson::iterator<EJSON_BASE_T>::operator-= (int32_t _val) {
	int64_t val = m_id;
	val -= _val;
	m_id = std::avg(int64_t(0), val, int64_t(m_data.size()));
	return *this;
}

template<class EJSON_BASE_T>
ejson::iterator<EJSON_BASE_T> ejson::iterator<EJSON_BASE_T>::operator- (int32_t _val) const {
	ejson::iterator<EJSON_BASE_T> result = *this;
	result -= _val;
	return result;
}

template<class EJSON_BASE_T>
ejson::iterator<EJSON_BASE_T>& ejson::iterator<EJSON_BASE_T>::operator++() {
	int64_t val = m_id;
	++val;
	m_id = std::avg(int64_t(0), val, int64_t(m_data.size()));
	return *this;
}

template<class EJSON_BASE_T>
ejson::iterator<EJSON_BASE_T> ejson::iterator<EJSON_BASE_T>::operator++(int) {
	ejson::iterator<EJSON_BASE_T> result = *this;
	++(*this);
	return result;
}

template<class EJSON_BASE_T>
ejson::iterator<EJSON_BASE_T>& ejson::iterator<EJSON_BASE_T>::operator--() {
	int64_t val = m_id;
	--val;
	m_id = std::avg(int64_t(0), val, int64_t(m_data.size()));
	return *this;
}

template<class EJSON_BASE_T>
ejson::iterator<EJSON_BASE_T> ejson::iterator<EJSON_BASE_T>::operator--(int) {
	ejson::iterator<EJSON_BASE_T> result = *this;
	--(*this);
	return result;
}

template<class EJSON_BASE_T>
bool ejson::iterator<EJSON_BASE_T>::operator== (const ejson::iterator<EJSON_BASE_T>& _obj) const {
	//ejson_WARNING("compare : " << _obj.m_id << " == " << m_id );
	return (    _obj.m_id == m_id
	         && &_obj.m_data == &m_data);
}

template<class EJSON_BASE_T>
bool ejson::iterator<EJSON_BASE_T>::operator!= (const ejson::iterator<EJSON_BASE_T>& _obj) const {
	//ejson_WARNING("compare : " << _obj.m_id << " != " << m_id );
	return (    _obj.m_id != m_id
	         || &_obj.m_data != &m_data);
}

template<class EJSON_BASE_T>
const ejson::Value ejson::iterator<EJSON_BASE_T>::operator *() const noexcept {
	return m_data[m_id];
}

template<class EJSON_BASE_T>
ejson::Value ejson::iterator<EJSON_BASE_T>::operator *() noexcept {
	return m_data[m_id];
}

template<class EJSON_BASE_T>
size_t ejson::iterator<EJSON_BASE_T>::getId() const noexcept {
	return m_id;
}

