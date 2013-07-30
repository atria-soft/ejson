/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_JSON_VALUE_H__
#define __ETK_JSON_VALUE_H__

#include <etk/types.h>
#include <etk/UString.h>
#include <etk/math/Vector2D.h>

namespace exml
{
	#if 1
		#define EXML_PARSE_ELEMENT EXML_VERBOSE
	#else
		#define EXML_PARSE_ELEMENT EXML_DEBUG
	#endif
	#if 1
		#define EXML_PARSE_ATTRIBUTE EXML_VERBOSE
	#else
		#define EXML_PARSE_ATTRIBUTE EXML_DEBUG
	#endif
	class Document;
	class Attribute;
	class Comment;
	class Declaration;
	class Element;
	class Text;
	
	typedef enum {
		typeUnknow, //!< might be an error ...
		typeValue, //!< XXXXXX:*
		typeDocument, //!< all the file main access
		typeArray, //!< [...]
		typeNull, //!< the 'null'
		typeNumber,  //!< the 216516.211651e+5454
		typeObject, //!< the { ... }
	} nodeType_te;
	
	class filePos
	{
		private:
			int32_t m_col;
			int32_t m_line;
		public:
			filePos(void) : m_col(0),m_line(0) { };
			filePos(int32_t _line, int32_t _col) : m_col(_col),m_line(_line) { };
			~filePos(void) { };
			filePos& operator ++(void) { m_col++; return *this; };
			filePos& operator --(void) { m_col--; if(m_col<0) { m_col=0;} return *this; };
			const filePos& operator +=(const filePos& _obj)
			{
				if (_obj.m_line==0) {
					m_col += _obj.m_col;
				} else {
					m_col = _obj.m_col;
					m_line += _obj.m_line;
				}
				return *this;
			};
			const filePos& operator +=(int32_t _col)
			{
				m_col += _col;
				return *this;
			};
			const filePos& operator= (const filePos& _obj )
			{
				m_col = _obj.m_col;
				m_line = _obj.m_line;
				return *this;
			}
			void NewLine(void) { m_col=0; m_line++; };
			bool Check(const etk::UniChar& _val)
			{
				m_col++;
				if (_val=='\n') {
					NewLine();
					return true;
				}
				return false;
			}
			void Set(int32_t _line, int32_t _col)
			{
				m_col = _col;
				m_line = _line;
			}
			void Clear(void)
			{
				m_col = 0;
				m_line = 0;
			}
			int32_t GetCol(void) const { return m_col; };
			int32_t GetLine(void) const { return m_line; };
	};
	etk::CCout& operator <<(etk::CCout& _os, const filePos& _obj);
	
	class Value
	{
		public:
			/**
			 * @brief basic element of a xml structure
			 */
			Value(void) : m_pos(0,0) { };
			/**
			 * @brief basic element of a xml structure
			 * @param[in] value of the value
			 */
			Value(const etk::UString& _value);
			/**
			 * @brief destructor
			 */
			virtual ~Value(void) { };
		public:
			/**
			 * @brief Parse the Current node [pure VIRUAL]
			 * @param[in] _data data string to parse.
			 * @param[in,out] _pos position in the string to start parse, return the position end of parsing.
			 * @param[in] _caseSensitive Request a parsion of element that is not case sensitive (all element is in low case)
			 * @param[in,out] file parsing position (line x col x)
			 * @return false if an error occured.
			 */
			virtual bool IParse(const etk::UString& _data, int32_t& _pos, exml::filePos& _filePos, ejson::Document& _doc) = 0;
			/**
			 * @brief Generate a string with the tree of the xml
			 * @param[in,out] _data string where to add the elements
			 * @param[in] current indentation of the file
			 * @return false if an error occured.
			 */
			virtual bool IGenerate(etk::UString& _data, int32_t _indent) const { return true; };
		protected:
			etk::UString m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
		public:
			/**
			 * @brief Set the value of the node.
			 * @param[in] _value New value of the node.
			 */
			virtual void SetValue(etk::UString _value) { m_value = _value; };
			/**
			 * @brief Get the current element Value.
			 * @return the reference of the string value.
			 */
			virtual const etk::UString& GetValue(void) const { return m_value; };
		public:
			/**
			 * @brief Get the node type.
			 * @return the type of the Node.
			 */
			virtual nodeType_te GetType(void) const { return typeValue; };
		protected:
			/**
			 * @brief Add indentation of the string input.
			 * @param[in,out] _data String where the indentation is done.
			 * @param[in] _indent Number of tab to add at the string.
			 */
			void AddIndent(etk::UString& _data, int32_t _indent) const;
			/**
			 * @brief Display the cuurent element that is curently parse.
			 * @param[in] _val Char that is parsed.
			 * @param[in] _filePos Position of the char in the file.
			 */
			void DrawElementParsed(const etk::UniChar& _val, const exml::filePos& _filePos) const;
			/**
			 * @brief count the number of white char in the string from the specify position (stop at the first element that is not a white char)
			 * @param[in] _data Data to parse.
			 * @param[in] _pos Start position in the string.
			 * @param[out] _filePos new poistion of te file to add.
			 * @return number of white element.
			 */
			int32_t CountWhiteChar(const etk::UString& _data, int32_t _pos, exml::filePos& _filePos) const;
		public:
			/**
			 * @brief Cast the element in a Document if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Document* ToDocument(void) { return NULL; };
			virtual const ejson::Document* ToDocument(void) const { return NULL; };
			/**
			 * @brief Cast the element in a Array if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Array* ToArray(void) { return NULL; };
			virtual const ejson::Array* ToArray(void) const{ return NULL; };
			/**
			 * @brief Cast the element in a Object if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Object* ToObject(void) { return NULL; };
			virtual const ejson::Object* ToObject(void) const{ return NULL; };
			/**
			 * @brief Cast the element in a Boolean if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Boolean* ToBoolean(void) { return NULL; };
			virtual const ejson::Boolean* ToBoolean(void) const{ return NULL; };
			/**
			 * @brief Cast the element in a Null if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Null* ToNull(void) { return NULL; };
			virtual const ejson::Null* ToNull(void) const{ return NULL; };
			/**
			 * @brief Cast the element in a Number if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Number* ToNumber(void) { return NULL; };
			virtual const ejson::Number* ToNumber(void) const{ return NULL; };
			
			/**
			 * @brief Check if the node is a ejson::Document
			 * @return true if the node is a ejson::Document
			 */
			bool IsDocument(void) const { return GetType()==ejson::typeDocument; };
			/**
			 * @brief Check if the node is a ejson::Array
			 * @return true if the node is a ejson::Array
			 */
			bool IsArray(void) const { return GetType()==ejson::typeArray; };
			/**
			 * @brief Check if the node is a ejson::Object
			 * @return true if the node is a ejson::Object
			 */
			bool IsObject(void) const { return GetType()==ejson::typeObject; };
			/**
			 * @brief Check if the node is a ejson::Boolean
			 * @return true if the node is a ejson::Boolean
			 */
			bool IsBoolean(void) const { return GetType()==ejson::typeBoolean; };
			/**
			 * @brief Check if the node is a ejson::Null
			 * @return true if the node is a ejson::Null
			 */
			bool IsNull(void) const { return GetType()==ejson::typeNull; };
			/**
			 * @brief Check if the node is a ejson::Number
			 * @return true if the node is a ejson::Number
			 */
			bool IsNumber(void) const { return GetType()==ejson::typeNumber; };
			
			/**
			 * @brief Clear the Node
			 */
			virtual void Clear(void);
	};
};

#endif

