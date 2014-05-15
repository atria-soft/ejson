/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_JSON_OBJECT_H__
#define __ETK_JSON_OBJECT_H__

#include <etk/types.h>
#include <map>
#include <algorithm>
#include <ejson/Value.h>

namespace ejson {
	class Object : public ejson::Value {
		public:
			/**
			 * @brief basic element of a xml structure
			 */
			Object() { };
			/**
			 * @brief destructor
			 */
			virtual ~Object() { };
		protected:
			std::map<std::string, ejson::Value*> m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
		public:
			// TODO : add direct id  access....
			/**
			 * @brief check if an element exist.
			 * @param[in] _name name of the object.
			 * @return The existance of the element.
			 */
			bool exist(const std::string& _name) const;
			/**
			 * @brief get the sub element with his name (no cast check)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Value* get(const std::string& _name);
			//! @previous
			const ejson::Value* get(const std::string& _name) const;
			//! @previous
			ejson::Value* operator[] (const std::string& _name) {
				return get(_name);
			}
			//! @previous
			const ejson::Value* operator[] (const std::string& _name) const {
				return get(_name);
			}
		public:
			/**
			 * @brief Get all the element name (keys).
			 * @return a vector of all name (key).
			 */
			std::vector<std::string> getKeys() const {
				std::vector<std::string> keys;
				for (auto &it : m_value) {
					keys.push_back(it.first);
				}
				return keys;
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
			 * @return NULL if the element does not exist.
			 */
			ejson::Value* get(size_t _id) {
				size_t id = 0;
				for(auto &it : m_value) {
					if (id == _id) {
						return it.second;
					}
					id++;
				}
				return NULL;
			};
			//! @previous
			const ejson::Value* get(size_t _id) const{
				size_t id = 0;
				for(auto &it : m_value) {
					if (id == _id) {
						return it.second;
					}
					id++;
				}
				return NULL;
			};
			//! @previous
			ejson::Value* operator[] (size_t _id) {
				return get(_id);
			}
			//! @previous
			const ejson::Value* operator[] (size_t _id) const {
				return get(_id);
			}
			/**
			 * @brief Get the element name (key).
			 * @param[in] _id Id of the element.
			 * @return The name (key).
			 */
			std::string getKey(size_t _id) const {
				size_t id = 0;
				for(auto it = m_value.begin(); it != m_value.end(); ++it, ++id) {
					if (id == _id) {
						return it->first;
					}
				}
				return NULL;
			}
			/**
			 * @brief get the sub element with his name (Casted as Object if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Object* getObject(const std::string& _name);
			//! @previous
			const ejson::Object* getObject(const std::string& _name) const;
			/**
			 * @brief get the sub element with his name (Casted as Array if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Array* getArray(const std::string& _name);
			//! @previous
			const ejson::Array* getArray(const std::string& _name) const;
			/**
			 * @brief get the sub element with his name (Casted as Null if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Null* getNull(const std::string& _name);
			//! @previous
			const ejson::Null* getNull(const std::string& _name) const;
			/**
			 * @brief get the sub element with his name (Casted as String if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::String* getString(const std::string& _name);
			//! @previous
			const ejson::String* getString(const std::string& _name) const;
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
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Boolean* getBoolean(const std::string& _name);
			//! @previous
			const ejson::Boolean* getBoolean(const std::string& _name) const;
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
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Number* getNumber(const std::string& _name);
			//! @previous
			const ejson::Number* getNumber(const std::string& _name) const;
			/**
			 * @brief get the sub Number value of the requested element.
			 * @param[in] _name name of the object.
			 * @param[in] _errorValue The return value if the element does not exist.
			 * @return Value of the Number or the _errorValue;
			 */
			double getNumberValue(const std::string& _name, double _errorValue=false) const;
		public:
			/**
			 * @brief add an element in the Object
			 * @param[in] _name name of the object
			 * @param[in] _value Element to add
			 * @return false if an error occured
			 */
			bool add(const std::string& _name, ejson::Value* _value);
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
			virtual bool transfertIn(ejson::Value* _obj);
			virtual ejson::Value* duplicate() const;
	};
};

#endif

