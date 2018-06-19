/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <ememory/memory.hpp>
#include <ejson/FilePos.hpp>
#include <ejson/valueType.hpp>

/**
 * @brief ejson namespace containing all function for JSON interpretor
 */
namespace ejson {
	//#define ENABLE_DISPLAY_PARSED_ELEMENT
	#if 1
		#define EJSON_PARSE_ELEMENT EJSON_VERBOSE
	#else
		#define EJSON_PARSE_ELEMENT EJSON_DEBUG
	#endif
	#if 1
		#define EJSON_PARSE_ATTRIBUTE EJSON_VERBOSE
	#else
		#define EJSON_PARSE_ATTRIBUTE EJSON_DEBUG
	#endif
	/**
	 * @brief ejson internal data implementation (not for external user).
	 */
	namespace internal {
		class Document;
		class Array;
		class Object;
		class Boolean;
		class Null;
		class Number;
		class String;
		/**
		 * @brief Basic main object of all json data.
		 */
		class Value : public ememory::EnableSharedFromThis<Value> {
			protected:
				enum ejson::valueType m_type; //!< Type of the element
			public:
				/**
				 * @brief Get Value type
				 * @return Type of the object
				 */
				enum ejson::valueType getType() const;
			protected:
				/**
				 * @brief basic element of a xml structure
				 */
				Value() :
				  m_type(ejson::valueType::Unknow) {
					m_type = ejson::valueType::Value;
				};
			public:
				/**
				 * @brief Virtualize destructor
				 */
				virtual ~Value();
			public:
				/**
				 * @brief parse the Current node [pure VIRUAL]
				 * @param[in] _data data string to parse.
				 * @param[in,out] _pos position in the string to start parse, return the position end of parsing.
				 * @param[in,out] _filePos Position in the file (in X/Y)
				 * @param[in,out] _doc Reference on the main document
				 * @return false if an error occured.
				 */
				virtual bool iParse(const etk::String& _data,
				                    size_t& _pos,
				                    ejson::FilePos& _filePos,
				                    ejson::internal::Document& _doc) = 0;
				/**
				 * @brief generate a string with the tree of the json
				 * @param[in,out] _data string where to add the elements
				 * @param[in] _indent current indentation of the file
				 * @return false if an error occured.
				 */
				virtual bool iGenerate(etk::String& _data,
				                       size_t _indent) const = 0;
				/**
				 * @brief generate a string with the tree of the json (not human readable ==> for computer transfer)
				 * @param[in,out] _data string where to add the elements
				 * @return false if an error occured.
				 */
				virtual void iMachineGenerate(etk::String& _data) const = 0;
				/**
				 * @brief Display the Document on console
				 */
				void display() const;
			protected:
				/**
				 * @brief add indentation of the string input.
				 * @param[in,out] _data String where the indentation is done.
				 * @param[in] _indent Number of tab to add at the string.
				 */
				void addIndent(etk::String& _data, int32_t _indent) const;
				/**
				 * @brief Display the cuurent element that is curently parse.
				 * @param[in] _val Char that is parsed.
				 * @param[in] _filePos Position of the char in the file.
				 */
				void drawElementParsed(char32_t _val, const ejson::FilePos& _filePos) const;
				/**
				 * @brief check if an name (for object named) (not : !"#$%&'()*+,/;<=>?@[\]^`{|}~ \\n\\t\\r).
				 * @param[in] _val Value to check the conformity.
				 * @return true The element char is considerable as a string
				 * @return false The element char is NOT considerable as a string
				 */
				bool checkString(char32_t _val) const;
				/**
				 * @brief check if an number -+.0123456789e).
				 * @param[in] _val Value to check the conformity.
				 * @return true The element char is considerable as a number
				 * @return false The element char is NOT considerable as a number
				 */
				bool checkNumber(char32_t _val) const;
				/**
				 * @brief count the number of white char in the string from the specify position (stop at the first element that is not a white char)
				 * @param[in] _data Data to parse.
				 * @param[in] _pos Start position in the string.
				 * @param[out] _filePos new poistion of te file to add.
				 * @return number of white element.
				 */
				int32_t countWhiteChar(const etk::String& _data, size_t _pos, ejson::FilePos& _filePos) const;
			public:
				/**
				 * @brief clear the Node
				 */
				virtual void clear();
				/**
				 * @brief Tranfert all element in the element set in parameter
				 * @param[in,out] _obj move all parameter in the selected element
				 * @return true if transfer is done corectly
				 * @note all element is remove from the curent element.
				 */
				virtual bool transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj);
				/**
				 * @brief Copy the curent node and all the child in the curent one.
				 * @return null in an error occured, the pointer on the element otherwise
				 */
				virtual ememory::SharedPtr<ejson::internal::Value> clone() const;
			protected:
				/**
				 * @brief check if the current element is white or not : '\\t' '\\n' '\\r' ' '
				 * @param[in] _val Char value to check
				 * @return tue if it is white char
				 */
				static bool isWhiteChar(char32_t _val);
		};
	}
}

#include <ejson/internal/Array.hpp>
#include <ejson/internal/Boolean.hpp>
#include <ejson/internal/Null.hpp>
#include <ejson/internal/Number.hpp>
#include <ejson/internal/Object.hpp>
#include <ejson/internal/String.hpp>
#include <ejson/internal/Document.hpp>

