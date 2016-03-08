/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <etk/Hash.h>
#include <algorithm>
#include <ejson/Value.h>

namespace ejson {
	class Object : public ejson::Value {
		protected:
			/**
			 * @brief basic element of a xml structure
			 */
			Object() { };
		public:
			static std::shared_ptr<Object> create();
			static std::shared_ptr<Object> create(const std::string& _data);
			/**
			 * @brief destructor
			 */
			virtual ~Object() { };
		protected:
			etk::Hash<std::shared_ptr<ejson::Value> > m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
		public:
			/**
			 * @brief check if an element exist.
			 * @param[in] _name name of the object.
			 * @return The existance of the element.
			 */
			bool exist(const std::string& _name) const;
			/**
			 * @brief get the sub element with his name (no cast check)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or nullptr if it not the corect type or does not existed
			 */
			std::shared_ptr<ejson::Value> get(const std::string& _name);
			//! @previous
			const std::shared_ptr<const ejson::Value> get(const std::string& _name) const;
			//! @previous
			std::shared_ptr<ejson::Value> operator[] (const std::string& _name) {
				return get(_name);
			}
			//! @previous
			const std::shared_ptr<const ejson::Value> operator[] (const std::string& _name) const {
				return get(_name);
			}
		public:
			/**
			 * @brief Get all the element name (keys).
			 * @return a vector of all name (key).
			 */
			std::vector<std::string> getKeys() const {
				return m_value.getKeys();
			}
			/**
			 * @brief get the number of sub element in the current one
			 * @return the Number of stored element
			 */
			size_t size() const {
				return m_value.size();
			};
			/**
			 * @brief get the pointer on an element reference with his ID.
			 * @param[in] _id Id of the element.
			 * @return nullptr if the element does not exist.
			 */
			std::shared_ptr<ejson::Value> get(size_t _id) {
				return m_value[_id];
			};
			//! @previous
			const std::shared_ptr<const ejson::Value> get(size_t _id) const{
				return m_value[_id];
			};
			//! @previous
			std::shared_ptr<ejson::Value> operator[] (size_t _id) {
				return m_value[_id];
			}
			//! @previous
			const std::shared_ptr<const ejson::Value> operator[] (size_t _id) const {
				return m_value[_id];
			}
			/**
			 * @brief Get the element name (key).
			 * @param[in] _id Id of the element.
			 * @return The name (key).
			 */
			std::string getKey(size_t _id) const {
				return m_value.getKey(_id);
			}
			/**
			 * @brief get the sub element with his name (Casted as Object if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or nullptr if it not the corect type or does not existed
			 */
			std::shared_ptr<ejson::Object> getObject(const std::string& _name);
			//! @previous
			const std::shared_ptr<const ejson::Object> getObject(const std::string& _name) const;
			/**
			 * @brief get the sub element with his name (Casted as Array if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or nullptr if it not the corect type or does not existed
			 */
			std::shared_ptr<ejson::Array> getArray(const std::string& _name);
			//! @previous
			const std::shared_ptr<const ejson::Array> getArray(const std::string& _name) const;
			/**
			 * @brief get the sub element with his name (Casted as Null if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or nullptr if it not the corect type or does not existed
			 */
			std::shared_ptr<ejson::Null> getNull(const std::string& _name);
			//! @previous
			const std::shared_ptr<const ejson::Null> getNull(const std::string& _name) const;
			/**
			 * @brief get the sub element with his name (Casted as String if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or nullptr if it not the corect type or does not existed
			 */
			std::shared_ptr<ejson::String> getString(const std::string& _name);
			//! @previous
			const std::shared_ptr<const ejson::String> getString(const std::string& _name) const;
			/**
			 * @brief get the sub string value of the requested element
			 * @param[in] _name name of the object
			 * @return Value of the string or an error string (empty)
			 */
			const std::string& getStringValue(const std::string& _name) const;
			/**
			 * @brief get the sub string value of the requested element (with error return value)
			 * @param[in] _name name of the object
			 * @param[in] _errorValue The return value if the element does not exist.
			 * @return Value of the string or an error string (empty)
			 */
			std::string getStringValue(const std::string& _name, const std::string& _errorValue) const;
			/**
			 * @brief get the sub element with his name (Casted as Boolean if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or nullptr if it not the corect type or does not existed
			 */
			std::shared_ptr<ejson::Boolean> getBoolean(const std::string& _name);
			//! @previous
			const std::shared_ptr<const ejson::Boolean> getBoolean(const std::string& _name) const;
			/**
			 * @brief get the sub boolean value of the requested element.
			 * @param[in] _name name of the object.
			 * @param[in] _errorValue The return value if the element does not exist.
			 * @return Value of the Boolean or the _errorValue;
			 */
			bool getBooleanValue(const std::string& _name, bool _errorValue=false) const;
			/**
			 * @brief get the sub element with his name (Casted as Number if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or nullptr if it not the corect type or does not existed
			 */
			std::shared_ptr<ejson::Number> getNumber(const std::string& _name);
			//! @previous
			const std::shared_ptr<const ejson::Number> getNumber(const std::string& _name) const;
			/**
			 * @brief get the sub Number value of the requested element.
			 * @param[in] _name name of the object.
			 * @param[in] _errorValue The return value if the element does not exist.
			 * @return Value of the Number or the _errorValue;
			 */
			double getNumberValue(const std::string& _name, double _errorValue=0.0) const;
		public:
			/**
			 * @brief add an element in the Object
			 * @param[in] _name name of the object
			 * @param[in] _value Element to add
			 * @return false if an error occured
			 */
			bool add(const std::string& _name, std::shared_ptr<ejson::Value> _value);
			/**
			 * @brief add a string element in the Object (automatic creation)
			 * @param[in] _name name of the object
			 * @param[in] _value string value to add
			 * @return false if an error occured
			 */
			bool addString(const std::string& _name, const std::string& _value);
			/**
			 * @brief add a "null" element in the Object (automatic creation)
			 * @param[in] _name name of the object
			 * @return false if an error occured
			 */
			bool addNull(const std::string& _name);
			/**
			 * @brief add a boolean element in the Object (automatic creation)
			 * @param[in] _name name of the object
			 * @param[in] _value boolean value to add
			 * @return false if an error occured
			 */
			bool addBoolean(const std::string& _name, bool _value);
			/**
			 * @brief add a double element in the Object (automatic creation)
			 * @param[in] _name name of the object
			 * @param[in] _value double value to add
			 * @return false if an error occured
			 */
			bool addNumber(const std::string& _name, double _value);
		public: // herited function :
			virtual bool iParse(const std::string& _data, size_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc);
			virtual bool iGenerate(std::string& _data, size_t _indent) const;
			virtual void clear();
			virtual bool transfertIn(std::shared_ptr<ejson::Value> _obj);
			virtual bool cloneIn(const std::shared_ptr<ejson::Object>& _obj) const;
			virtual std::shared_ptr<ejson::Value> clone() const;
			virtual std::shared_ptr<ejson::Object> cloneObj() const;
	};
}

