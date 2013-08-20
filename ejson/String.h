/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_JSON_STRING_H__
#define __ETK_JSON_STRING_H__

#include <etk/types.h>
#include <etk/UString.h>
#include <etk/math/Vector2D.h>
#include <ejson/Value.h>

namespace ejson
{
	class String : public ejson::Value
	{
		private:
			bool m_quoted; //!< this is for all element that is not generised (like null & numbers)
		public:
			/**
			 * @brief basic element of a xml structure
			 */
			String(bool _quoted=false) : m_quoted(_quoted) { };
			String(const etk::UString& _value) : m_quoted(false), m_value(_value) { };
			/**
			 * @brief destructor
			 */
			virtual ~String(void) { };
		public:
			/**
			 * @brief Parse the Current node [pure VIRUAL]
			 * @param[in] _data data string to parse.
			 * @param[in,out] _pos position in the string to start parse, return the position end of parsing.
			 * @param[in] _caseSensitive Request a parsion of element that is not case sensitive (all element is in low case)
			 * @param[in,out] file parsing position (line x col x)
			 * @return false if an error occured.
			 */
			virtual bool IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc);
			/**
			 * @brief Generate a string with the tree of the xml
			 * @param[in,out] _data string where to add the elements
			 * @param[in] current indentation of the file
			 * @return false if an error occured.
			 */
			virtual bool IGenerate(etk::UString& _data, int32_t _indent) const;
		protected:
			etk::UString m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
		public:
			/**
			 * @brief Set the value of the node.
			 * @param[in] _value New value of the node.
			 */
			void SetValue(const etk::UString& _value) { m_value = _value; };
			/**
			 * @brief Get the current element Value.
			 * @return the reference of the string value.
			 */
			const etk::UString& GetValue(void) const { return m_value; };
		public:
			/**
			 * @brief Get the node type.
			 * @return the type of the Node.
			 */
			virtual nodeType_te GetType(void) const { return typeString; };
		public:
			/**
			 * @brief Cast the element in a Object if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::String* ToString(void) { return this; };
			virtual const ejson::String* ToString(void) const{ return this; };
			/**
			 * @brief Clear the Node
			 */
			virtual void Clear(void);
	};
};

#endif

