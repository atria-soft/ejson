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
#include <etk/UString.h>
#include <etk/math/Vector2D.h>
#include <ejson/Value.h>

namespace ejson
{
	class Array : public ejson::Value
	{
		public:
			/**
			 * @brief basic element of a xml structure
			 */
			Array(void) { };
			/**
			 * @brief destructor
			 */
			virtual ~Array(void) { };
		private:
			etk::Vector<ejson::Value*> m_value; //!< vector of sub elements
		public:
			/**
			 * @brief Get the number of sub element in the current one
			 * @return the Number of stored element
			 */
			esize_t Size(void) const { return m_value.Size(); };
			/**
			 * @brief Get the pointer on an element reference with his ID.
			 * @param[in] _id Id of the element.
			 * @return NULL if the element does not exist.
			 */
			const ejson::Value* Get(esize_t _id) const { return m_value[_id]; };
			ejson::Value* Get(esize_t _id) { return m_value[_id]; };
			/**
			 * @brief Get the pointer on an element reference with his ID (casted in Object if it is an object).
			 * @param[in] _id Id of the element.
			 * @return NULL if the element does not exist.
			 */
			ejson::Object* GetObject(esize_t _id);
			/**
			 * @brief Get the pointer on an element reference with his ID (casted in String if it is an String).
			 * @param[in] _id Id of the element.
			 * @return NULL if the element does not exist.
			 */
			ejson::String* GetString(esize_t _id);
			/**
			 * @brief Get the value of the string element (if not a string return "")
			 * @param[in] _id Id of the element.
			 * @return value of the element.
			 */
			const etk::UString& GetStringValue(esize_t _id);
			/**
			 * @brief Get the value of the string element
			 * @param[in] _id Id of the element.
			 * @param[in] _errorValue The return value if an error occured.
			 * @return value of the element, or the _errorValue.
			 */
			etk::UString GetStringValue(esize_t _id, const etk::UString& _errorValue);
			/**
			 * @brief Get the pointer on an element reference with his ID (casted in Array if it is an Array).
			 * @param[in] _id Id of the element.
			 * @return NULL if the element does not exist.
			 */
			ejson::Array* GetArray(esize_t _id);
			/**
			 * @brief Get the pointer on an element reference with his ID (casted in Null if it is an Null).
			 * @param[in] _id Id of the element.
			 * @return NULL if the element does not exist.
			 */
			ejson::Null* GetNull(esize_t _id);
			/**
			 * @brief Get the pointer on an element reference with his ID (casted in Number if it is an Number).
			 * @param[in] _id Id of the element.
			 * @return NULL if the element does not exist.
			 */
			ejson::Number* GetNumber(esize_t _id);
			/**
			 * @brief Get the value of the Number element
			 * @param[in] _id Id of the element.
			 * @param[in] _errorValue The return value if an error occured.
			 * @return value of the element, or the _errorValue.
			 */
			double GetNumberValue(esize_t _id, double _errorValue);
			/**
			 * @brief Get the pointer on an element reference with his ID (casted in Boolean if it is an Boolean).
			 * @param[in] _id Id of the element.
			 * @return NULL if the element does not exist.
			 */
			ejson::Boolean* GetBoolean(esize_t _id);
			/**
			 * @brief Get the value of the Boolean element
			 * @param[in] _id Id of the element.
			 * @param[in] _errorValue The return value if an error occured.
			 * @return value of the element, or the _errorValue.
			 */
			bool GetBooleanValue(esize_t _id, bool _errorValue);
			/**
			 * @brief Add an element on the array.
			 * @param[in] _element element to add.
			 * @return false if an error occured.
			 */
			bool Add(ejson::Value* _element);
			/**
			 * @brief Add a string element in the Object (automatic creation)
			 * @param[in] _value string value to add
			 * @return false if an error occured
			 */
			bool AddString(const etk::UString& _value);
			/**
			 * @brief Add a "null" element in the Object (automatic creation)
			 * @return false if an error occured
			 */
			bool AddNull(void);
			/**
			 * @brief Add a boolean element in the Object (automatic creation)
			 * @param[in] _value boolean value to add
			 * @return false if an error occured
			 */
			bool AddBoolean(bool _value);
			/**
			 * @brief Add a double element in the Object (automatic creation)
			 * @param[in] _value double value to add
			 * @return false if an error occured
			 */
			bool AddNumber(double _value);
			
		public: // herited function :
			virtual bool IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc);
			virtual bool IGenerate(etk::UString& _data, int32_t _indent) const;
			virtual nodeType_te GetType(void) const { return typeArray; };
			virtual ejson::Array* ToArray(void) { return this; };
			virtual const ejson::Array* ToArray(void) const{ return this; };
			virtual void Clear(void);
			virtual bool TransfertIn(ejson::Value* _obj);
			virtual ejson::Value* Duplicate(void) const;
	};
};

#endif

