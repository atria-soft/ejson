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
#include <etk/UString.h>
#include <etk/Hach.h>
#include <etk/math/Vector2D.h>
#include <ejson/Value.h>

namespace ejson
{
	class Object : public ejson::Value
	{
		public:
			/**
			 * @brief basic element of a xml structure
			 */
			Object(void) { };
			/**
			 * @brief destructor
			 */
			virtual ~Object(void) { };
		protected:
			etk::Hash<ejson::Value*> m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
		public:
			/**
			 * @brief Check if an element exist.
			 * @param[in] _name name of the object.
			 * @return The existance of the element.
			 */
			bool Exist(const etk::UString& _name) const;
			/**
			 * @brief Get the sub element with his name (no cast check)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Value* Get(const etk::UString& _name) const;
			/**
			 * @brief Get the sub element with his name (Casted as Object if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Object* GetObject(const etk::UString& _name) const;
			/**
			 * @brief Get the sub element with his name (Casted as Array if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Array* GetArray(const etk::UString& _name) const;
			/**
			 * @brief Get the sub element with his name (Casted as Null if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Null* GetNull(const etk::UString& _name) const;
			/**
			 * @brief Get the sub element with his name (Casted as String if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::String* GetString(const etk::UString& _name) const;
			/**
			 * @brief Get the sub string value of the requested element
			 * @param[in] _name name of the object
			 * @return Value of the string or an error string (empty)
			 */
			const etk::UString& GetStringValue(const etk::UString& _name) const;
			/**
			 * @brief Get the sub string value of the requested element (with error return value)
			 * @param[in] _name name of the object
			 * @param[in] _errorValue The return value if the element does not exist.
			 * @return Value of the string or an error string (empty)
			 */
			etk::UString GetStringValue(const etk::UString& _name, const etk::UString& _errorValue) const;
			/**
			 * @brief Get the sub element with his name (Casted as Boolean if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Boolean* GetBoolean(const etk::UString& _name) const;
			/**
			 * @brief Get the sub boolean value of the requested element.
			 * @param[in] _name name of the object.
			 * @param[in] _errorValue The return value if the element does not exist.
			 * @return Value of the Boolean or the _errorValue;
			 */
			bool GetBooleanValue(const etk::UString& _name, bool _errorValue=false) const;
			/**
			 * @brief Get the sub element with his name (Casted as Number if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Number* GetNumber(const etk::UString& _name) const;
			/**
			 * @brief Get the sub Number value of the requested element.
			 * @param[in] _name name of the object.
			 * @param[in] _errorValue The return value if the element does not exist.
			 * @return Value of the Number or the _errorValue;
			 */
			double GetNumberValue(const etk::UString& _name, double _errorValue=false) const;
		public:
			/**
			 * @brief Add an element in the Object
			 * @param[in] _name name of the object
			 * @param[in] _value Element to add
			 * @return false if an error occured
			 */
			bool Add(const etk::UString& _name, ejson::Value* _value);
			/**
			 * @brief Add a string element in the Object (automatic creation)
			 * @param[in] _name name of the object
			 * @param[in] _value string value to add
			 * @return false if an error occured
			 */
			bool AddString(const etk::UString& _name, const etk::UString& _value);
			/**
			 * @brief Add a "null" element in the Object (automatic creation)
			 * @param[in] _name name of the object
			 * @return false if an error occured
			 */
			bool AddNull(const etk::UString& _name);
			/**
			 * @brief Add a boolean element in the Object (automatic creation)
			 * @param[in] _name name of the object
			 * @param[in] _value boolean value to add
			 * @return false if an error occured
			 */
			bool AddBoolean(const etk::UString& _name, bool _value);
			/**
			 * @brief Add a double element in the Object (automatic creation)
			 * @param[in] _name name of the object
			 * @param[in] _value double value to add
			 * @return false if an error occured
			 */
			bool AddNumber(const etk::UString& _name, double _value);
		public: // herited function :
			virtual bool IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc);
			virtual bool IGenerate(etk::UString& _data, int32_t _indent) const;
			virtual nodeType_te GetType(void) const { return typeObject; };
			virtual ejson::Object* ToObject(void) { return this; };
			virtual const ejson::Object* ToObject(void) const{ return this; };
			virtual void Clear(void);
			virtual bool TransfertIn(ejson::Value* _obj);
			virtual ejson::Value* Duplicate(void) const;
	};
};

#endif

