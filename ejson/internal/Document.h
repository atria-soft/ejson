/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <ejson/internal/Value.h>
#include <vector>
#include <etk/types.h>
#include <ejson/internal/String.h>
#include <ejson/internal/Array.h>
#include <ejson/internal/Object.h>

namespace ejson {
	namespace internal {
		/**
		 * @brief ejson Document internal data implementation.
		 */
		class Document : public ejson::internal::Object {
			public:
				/**
				 * @brief Constructor
				 */
				Document();
				/**
				 * @brief Create factory on the ejson::internal::Document
				 * @return A SharedPtr on the Document value
				 */
				static ememory::SharedPtr<Document> create();
			public:
				/**
				 * @brief parse a string that contain an XML
				 * @param[in] _data Data to parse
				 * @return false : An error occured
				 * @return true : Parsing is OK
				 */
				bool parse(const std::string& _data);
				/**
				 * @brief generate a string that contain the created XML
				 * @param[out] _data Data where the xml is stored
				 * @return false : An error occured
				 * @return true : Parsing is OK
				 */
				bool generate(std::string& _data);
				/**
				 * @brief Load the file that might contain the xml
				 * @param[in] _file Filename of the xml (compatible with etk FSNode naming)
				 * @return false : An error occured
				 * @return true : Parsing is OK
				 */
				bool load(const std::string& _file);
				/**
				 * @brief Store the Xml in the file
				 * @param[in] _file Filename of the xml (compatible with etk FSNode naming)
				 * @return false : An error occured
				 * @return true : Parsing is OK
				 */
				bool store(const std::string& _file);
			private:
				bool m_writeErrorWhenDetexted; //!< Flag to know if we need to display error when they are detected
				std::string m_comment; //!< Error comment
				std::string m_Line; //!< Line with the error
				ejson::FilePos m_filePos; //!< Position in the file of the error
			public:
				/**
				 * @brief Set the display of the error when detected.
				 * @param[in] _value true: display error, false not display error (get it at end)
				 */
				void setDisplayError(bool _value);
				/**
				 * @brief Get the display of the error status.
				 * @return true Display error
				 * @return false Does not display error (get it at end)
				 */
				bool getDisplayError();
				/**
				 * @brief Display error detected.
				 */
				void displayError();
				/**
				 * @brief When parsing a subParser create an error that might be write later
				 * @param[in] _data Wall File or stream
				 * @param[in] _pos Position in the file (in nb char)
				 * @param[in] _filePos Position in x/y in the file
				 * @param[in] _comment Help coment
				 */
				void createError(const std::string& _data,
				                 size_t _pos,
				                 const ejson::FilePos& _filePos,
				                 const std::string& _comment);
			public:
				bool iParse(const std::string& _data,
				            size_t& _pos,
				            ejson::FilePos& _filePos,
				            ejson::internal::Document& _doc) override;
				bool iGenerate(std::string& _data, size_t _indent) const override;
		};
	}
}

/**
 * @brief Automatic create error on the basic Document object
 * @param[in] doc Document reference
 * @param[in] data main string parsed
 * @param[in] pos Position in the file
 * @param[in] filePos position in linre row in the file
 * @param[in] comment Comment of the error find
 */
#define EJSON_CREATE_ERROR(doc,data,pos,filePos,comment) \
	do { \
		EJSON_ERROR(comment); \
		(doc).createError((data),(pos),(filePos),(comment)); \
	} while (0)




