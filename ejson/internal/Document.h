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
		class Document : public ejson::internal::Object {
			public:
				/**
				 * @brief Constructor
				 */
				Document();
				static ememory::SharedPtr<Document> create();
				/**
				 * @brief Destructor
				 */
				virtual ~Document();
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
				bool m_writeErrorWhenDetexted;
				std::string m_comment;
				std::string m_Line;
				ejson::FilePos m_filePos;
			public:
				void displayErrorWhenDetected() {
					m_writeErrorWhenDetexted=true;
				};
				void notDisplayErrorWhenDetected() {
					m_writeErrorWhenDetexted=false;
				};
				
				void createError(const std::string& _data, size_t _pos, const ejson::FilePos& _filePos, const std::string& _comment);
				void displayError();
			public: // herited function:
				virtual bool iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc);
				virtual bool iGenerate(std::string& _data, size_t _indent) const;
		};
	}
}

#define EJSON_CREATE_ERROR(doc,data,pos,filePos,comment) \
	do { \
		EJSON_ERROR(comment); \
		(doc).createError((data),(pos),(filePos),(comment)); \
	} while (0)




