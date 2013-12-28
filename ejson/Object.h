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
#include <etk/types.h>
#include <etk/Hash.h>
#include <etk/math/Vector2D.h>
#include <ejson/Value.h>

namespace ejson {
	class Object : public ejson::Value {
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
			ejson::Value* get(const std::string& _name) const;
			/**
			 * @brief get the sub element with his name (Casted as Object if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Object* getObject(const std::string& _name) const;
			/**
			 * @brief get the sub element with his name (Casted as Array if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Array* getArray(const std::string& _name) const;
			/**
			 * @brief get the sub element with his name (Casted as Null if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Null* getNull(const std::string& _name) const;
			/**
			 * @brief get the sub element with his name (Casted as String if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::String* getString(const std::string& _name) const;
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
			ejson::Boolean* getBoolean(const std::string& _name) const;
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
			ejson::Number* getNumber(const std::string& _name) const;
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
			virtual enum nodeType getType(void) const {
				return typeObject;
			};
			virtual ejson::Object* toObject(void) {
				return this;
			};
			virtual const ejson::Object* toObject(void) const{
				return this;
			};
			virtual void clear(void);
			virtual bool transfertIn(ejson::Value* _obj);
			virtual ejson::Value* duplicate(void) const;
	};
};

#endif

