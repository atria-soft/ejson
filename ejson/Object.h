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
			 * @brief Get tht sub element with his name (no cast check)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Value* GetSub(const etk::UString& _name) const;
			/**
			 * @brief Get tht sub element with his name (Casted as Object if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Object* GetSubObject(const etk::UString& _name) const;
			/**
			 * @brief Get tht sub element with his name (Casted as String if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::String* GetSubString(const etk::UString& _name) const;
			/**
			 * @brief Get tht sub element with his name (Casted as Array if it is possible)
			 * @param[in] _name name of the object
			 * @return pointer on the element requested or NULL if it not the corect type or does not existed
			 */
			ejson::Array* GetSubArray(const etk::UString& _name) const;
		public:
			/**
			 * @brief Add an element in the Object
			 * @param[in] _name name of the object
			 * @param[in] _value Element to add
			 * @return false if an error occured
			 */
			bool AddSub(const etk::UString& _name, ejson::Value* _value);
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

