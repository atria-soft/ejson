/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ETK_JSON_H__
#define __ETK_JSON_H__

#include <ejson/Value.h>
#include <vector>
#include <etk/types.h>
#include <ejson/String.h>
#include <ejson/Array.h>
#include <ejson/Object.h>

namespace ejson {
	class Document : public ejson::Object {
		public:
			/**
			 * @brief Constructor
			 */
			Document();
			static std::shared_ptr<Document> create();
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
			/**
			 * @brief Display the Document on console
			 */
			void display();
		private:
			bool m_writeErrorWhenDetexted;
			std::string m_comment;
			std::string m_Line;
			ejson::filePos m_filePos;
		public:
			void displayErrorWhenDetected() {
				m_writeErrorWhenDetexted=true;
			};
			void notDisplayErrorWhenDetected() {
				m_writeErrorWhenDetexted=false;
			};
			
			void createError(const std::string& _data, size_t _pos, const ejson::filePos& _filePos, const std::string& _comment);
			void displayError();
		public: // herited function:
			virtual bool iParse(const std::string& _data, size_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc);
			virtual bool iGenerate(std::string& _data, size_t _indent) const;
	};
};

#define EJSON_CREATE_ERROR(doc,data,pos,filePos,comment) \
	do { \
		JSON_ERROR(comment); \
		(doc).createError((data),(pos),(filePos),(comment)); \
	} while (0)

//__LINE__, __class__, __func__

#endif


