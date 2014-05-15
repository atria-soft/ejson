/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_JSON_ARRAY_H__
#define __ETK_JSON_ARRAY_H__

#include <etk/types.h>
#include <ejson/Value.h>

namespace ejson {
	class Array : public ejson::Value {
		public:
			/**
			 * @brief basic element of a xml structure
			 */
			Array() { };
			/**
			 * @brief destructor
			 */
			virtual ~Array() { };
		private:
			std::vector<ejson::Value*> m_value; //!< vector of sub elements
		public:
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
				return m_value[_id];
			};
			//! @previous
			const ejson::Value* get(size_t _id) const{
				return m_value[_id];
			};
			//! @previous
			ejson::Value* operator[] (size_t _id) {
				return m_value[_id];
			}
			//! @previous
			const ejson::Value* operator[] (size_t _id) const {
				return m_value[_id];
			}
			/**
			 * @brief get the pointer on an element reference with his ID (casted in Object if it is an object).
			 * @param[in] _id Id of the element.
			 * @return NULL if the element does not exist.
			 */
			ejson::Object* getObject(size_t _id);
			//! @previous
			const ejson::Object* getObject(size_t _id) const;
			/**
			 * @brief get the pointer on an element reference with his ID (casted in String if it is an String).
			 * @param[in] _id Id of the element.
			 * @return NULL if the element does not exist.
			 */
			ejson::String* getString(size_t _id);
			//! @previous
			const ejson::String* getString(size_t _id) const;
			/**
			 * @brief get the value of the string element (if not a string return "")
			 * @param[in] _id Id of the element.
			 * @return value of the element.
			 */
			std::string getStringValue(size_t _id);
			//! @previous
			const std::string& getStringValue(size_t _id) const;
			/**
			 * @brief get the value of the string element
			 * @param[in] _id Id of the element.
			 * @param[in] _errorValue The return value if an error occured.
			 * @return value of the element, or the _errorValue.
			 */
			std::string getStringValue(size_t _id, const std::string& _errorValue) const;
			/**
			 * @brief get the pointer on an element reference with his ID (casted in Array if it is an Array).
			 * @param[in] _id Id of the element.
			 * @return NULL if the element does not exist.
			 */
			ejson::Array* getArray(size_t _id);
			//! @previous
			const ejson::Array* getArray(size_t _id) const;
			/**
			 * @brief get the pointer on an element reference with his ID (casted in Null if it is an Null).
			 * @param[in] _id Id of the element.
			 * @return NULL if the element does not exist.
			 */
			ejson::Null* getNull(size_t _id);
			//! @previous
			const ejson::Null* getNull(size_t _id) const;
			/**
			 * @brief get the pointer on an element reference with his ID (casted in Number if it is an Number).
			 * @param[in] _id Id of the element.
			 * @return NULL if the element does not exist.
			 */
			ejson::Number* getNumber(size_t _id);
			//! @previous
			const ejson::Number* getNumber(size_t _id) const;
			/**
			 * @brief get the value of the Number element
			 * @param[in] _id Id of the element.
			 * @param[in] _errorValue The return value if an error occured.
			 * @return value of the element, or the _errorValue.
			 */
			double getNumberValue(size_t _id, double _errorValue) const;
			/**
			 * @brief get the pointer on an element reference with his ID (casted in Boolean if it is an Boolean).
			 * @param[in] _id Id of the element.
			 * @return NULL if the element does not exist.
			 */
			ejson::Boolean* getBoolean(size_t _id);
			//! @previous
			const ejson::Boolean* getBoolean(size_t _id) const;
			/**
			 * @brief get the value of the Boolean element
			 * @param[in] _id Id of the element.
			 * @param[in] _errorValue The return value if an error occured.
			 * @return value of the element, or the _errorValue.
			 */
			bool getBooleanValue(size_t _id, bool _errorValue) const;
			/**
			 * @brief add an element on the array.
			 * @param[in] _element element to add.
			 * @return false if an error occured.
			 */
			bool add(ejson::Value* _element);
			/**
			 * @brief add a string element in the Object (automatic creation)
			 * @param[in] _value string value to add
			 * @return false if an error occured
			 */
			bool addString(const std::string& _value);
			/**
			 * @brief add a "null" element in the Object (automatic creation)
			 * @return false if an error occured
			 */
			bool addNull();
			/**
			 * @brief add a boolean element in the Object (automatic creation)
			 * @param[in] _value boolean value to add
			 * @return false if an error occured
			 */
			bool addBoolean(bool _value);
			/**
			 * @brief add a double element in the Object (automatic creation)
			 * @param[in] _value double value to add
			 * @return false if an error occured
			 */
			bool addNumber(double _value);
			
		public: // herited function :
			virtual bool iParse(const std::string& _data, size_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc);
			virtual bool iGenerate(std::string& _data, size_t _indent) const;
			virtual void clear();
			virtual bool transfertIn(ejson::Value* _obj);
			virtual ejson::Value* duplicate() const;
	};
};

#endif

