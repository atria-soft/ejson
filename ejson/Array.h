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
		private:
			etk::Vector<ejson::Value*> m_value; //!< vector of sub elements
		public:
			
		public:
			/**
			 * @brief Get the node type.
			 * @return the type of the Node.
			 */
			virtual nodeType_te GetType(void) const { return typeArray; };
		public:
			/**
			 * @brief Cast the element in a Array if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Array* ToArray(void) { return this; };
			virtual const ejson::Array* ToArray(void) const{ return this; };
			/**
			 * @brief Clear the Node
			 */
			virtual void Clear(void);
	};
};

#endif

