/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <ememory/memory.h>
#include <ejson/FilePos.h>
#include <ejson/valueType.h>

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
	namespace internal {
		class Document;
		class Array;
		class Object;
		class Boolean;
		class Null;
		class Number;
		class String;
		/**
		 * @brief Basic main object of all json elements.
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
				  m_type(ejson::valueType::unknow) {
					m_type = ejson::valueType::value;
				};
				/**
				 * @brief Virtualize destructor
				 */
				virtual ~Value();
			public:
				/**
				 * @brief parse the Current node [pure VIRUAL]
				 * @param[in] _data data string to parse.
				 * @param[in,out] _pos position in the string to start parse, return the position end of parsing.
				 * @param[in] _caseSensitive Request a parsion of element that is not case sensitive (all element is in low case)
				 * @param[in,out] file parsing position (line x col x)
				 * @return false if an error occured.
				 */
				virtual bool iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) = 0;
				/**
				 * @brief generate a string with the tree of the xml
				 * @param[in,out] _data string where to add the elements
				 * @param[in] current indentation of the file
				 * @return false if an error occured.
				 */
				virtual bool iGenerate(std::string& _data, size_t _indent) const = 0;
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
				void addIndent(std::string& _data, size_t _indent) const;
				/**
				 * @brief Display the cuurent element that is curently parse.
				 * @param[in] _val Char that is parsed.
				 * @param[in] _filePos Position of the char in the file.
				 */
				void drawElementParsed(char32_t _val, const ejson::FilePos& _filePos) const;
				/**
				 * @brief check if an name (for object named) (not : !"#$%&'()*+,/;<=>?@[\]^`{|}~ \n\t\r).
				 * @param[in] _val Value to check the conformity.
				 */
				bool checkString(char32_t _val) const;
				/**
				 * @brief check if an number -+.0123456789e).
				 * @param[in] _val Value to check the conformity.
				 */
				bool checkNumber(char32_t _val) const;
				/**
				 * @brief count the number of white char in the string from the specify position (stop at the first element that is not a white char)
				 * @param[in] _data Data to parse.
				 * @param[in] _pos Start position in the string.
				 * @param[out] _filePos new poistion of te file to add.
				 * @return number of white element.
				 */
				int32_t countWhiteChar(const std::string& _data, size_t _pos, ejson::FilePos& _filePos) const;
			public:
				/**
				 * @brief Cast the element in a Value if it is possible.
				 * @return pointer on the class or nullptr.
				 */
				ememory::SharedPtr<ejson::internal::Value> toValue();
				/**
				 * @brief Cast the element in a Value if it is possible.
				 * @return CONST pointer on the class or nullptr.
				 */
				const ememory::SharedPtr<const ejson::internal::Value> toValue() const;
				/**
				 * @brief Cast the element in a Document if it is possible.
				 * @return pointer on the class or nullptr.
				 */
				ememory::SharedPtr<ejson::internal::Document> toDocument();
				/**
				 * @brief Cast the element in a Document if it is possible.
				 * @return CONST pointer on the class or nullptr.
				 */
				const ememory::SharedPtr<const ejson::internal::Document> toDocument() const;
				/**
				 * @brief Cast the element in a Array if it is possible.
				 * @return pointer on the class or nullptr.
				 */
				ememory::SharedPtr<ejson::internal::Array> toArray();
				/**
				 * @brief Cast the element in a Array if it is possible.
				 * @return CONST pointer on the class or nullptr.
				 */
				const ememory::SharedPtr<const ejson::internal::Array> toArray() const;
				/**
				 * @brief Cast the element in a Object if it is possible.
				 * @return pointer on the class or nullptr.
				 */
				ememory::SharedPtr<ejson::internal::Object> toObject();
				/**
				 * @brief Cast the element in a Object if it is possible.
				 * @return CONST pointer on the class or nullptr.
				 */
				const ememory::SharedPtr<const ejson::internal::Object> toObject() const;
				/**
				 * @brief Cast the element in a String if it is possible.
				 * @return pointer on the class or nullptr.
				 */
				ememory::SharedPtr<ejson::internal::String> toString();
				/**
				 * @brief Cast the element in a String if it is possible.
				 * @return CONST pointer on the class or nullptr.
				 */
				const ememory::SharedPtr<const ejson::internal::String> toString() const;
				/**
				 * @brief Cast the element in a Number if it is possible.
				 * @return pointer on the class or nullptr.
				 */
				ememory::SharedPtr<ejson::internal::Number> toNumber();
				/**
				 * @brief Cast the element in a Number if it is possible.
				 * @return CONST pointer on the class or nullptr.
				 */
				const ememory::SharedPtr<const ejson::internal::Number> toNumber() const;
				/**
				 * @brief Cast the element in a Boolean if it is possible.
				 * @return pointer on the class or nullptr.
				 */
				ememory::SharedPtr<ejson::internal::Boolean> toBoolean();
				/**
				 * @brief Cast the element in a Boolean if it is possible.
				 * @return CONST pointer on the class or nullptr.
				 */
				const ememory::SharedPtr<const ejson::internal::Boolean> toBoolean() const;
				/**
				 * @brief Cast the element in a Null if it is possible.
				 * @return pointer on the class or nullptr.
				 */
				ememory::SharedPtr<ejson::internal::Null> toNull();
				/**
				 * @brief Cast the element in a Null if it is possible.
				 * @return CONST pointer on the class or nullptr.
				 */
				const ememory::SharedPtr<const ejson::internal::Null> toNull() const;
				
				/**
				 * @brief check if the node is a ejson::internal::Document
				 * @return true if the node is a ejson::internal::Document
				 */
				bool isDocument() const;
				/**
				 * @brief check if the node is a ejson::internal::Array
				 * @return true if the node is a ejson::internal::Array
				 */
				bool isArray() const;
				/**
				 * @brief check if the node is a ejson::internal::Object
				 * @return true if the node is a ejson::internal::Object
				 */
				bool isObject() const;
				/**
				 * @brief check if the node is a ejson::internal::String
				 * @return true if the node is a ejson::internal::String
				 */
				bool isString() const;
				/**
				 * @brief check if the node is a ejson::internal::Number
				 * @return true if the node is a ejson::internal::Number
				 */
				bool isNumber() const;
				/**
				 * @brief check if the node is a ejson::internal::Boolean
				 * @return true if the node is a ejson::internal::Boolean
				 */
				bool isBoolean() const;
				/**
				 * @brief check if the node is a ejson::internal::Null
				 * @return true if the node is a ejson::internal::Null
				 */
				bool isNull() const;
				
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
				 * @return nullptr in an error occured, the pointer on the element otherwise
				 */
				virtual ememory::SharedPtr<ejson::internal::Value> clone() const;
			protected:
				/**
				 * @brief check if the current element is white or not : '\t' '\n' '\r' ' '
				 * @return tue if it is white char
				 */
				static bool isWhiteChar(char32_t _val);
		};
	}
}

#include <ejson/internal/Array.h>
#include <ejson/internal/Boolean.h>
#include <ejson/internal/Null.h>
#include <ejson/internal/Number.h>
#include <ejson/internal/Object.h>
#include <ejson/internal/String.h>
#include <ejson/internal/Document.h>

