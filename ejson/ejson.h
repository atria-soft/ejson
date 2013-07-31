/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_JSON_H__
#define __ETK_JSON_H__

#include <ejson/Value.h>
#include <etk/unicode.h>
#include <etk/Vector.h>
#include <etk/UString.h>

namespace ejson
{
	class Document : public ejson::Value
	{
		public:
			/**
			 * @brief Constructor
			 */
			Document(void);
			/**
			 * @brief Destructor
			 */
			virtual ~Document(void);
		public:
			/**
			 * @brief Parse a string that contain an XML
			 * @param[in] _data Data to parse
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool Parse(const etk::UString& _data);
			/**
			 * @brief Generate a string that contain the created XML
			 * @param[out] _data Data where the xml is stored
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool Generate(etk::UString& _data);
			/**
			 * @brief Load the file that might contain the xml
			 * @param[in] _file Filename of the xml (compatible with etk FSNode naming)
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool Load(const etk::UString& _file);
			/**
			 * @brief Store the Xml in the file
			 * @param[in] _file Filename of the xml (compatible with etk FSNode naming)
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool Store(const etk::UString& _file);
			/**
			 * @brief Display the Document on console
			 */
			void Display(void);
		private:
			ejson::Value* m_subElement; //!< only element that contain the json document:
		public:
			// TODO : sdfsdfsdf
		private:
			bool m_writeErrorWhenDetexted;
			etk::UString m_comment;
			etk::UString m_Line;
			ejson::filePos m_filePos;
		public:
			void DisplayErrorWhenDetected(void) { m_writeErrorWhenDetexted=true; };
			void NotDisplayErrorWhenDetected(void) { m_writeErrorWhenDetexted=false; };
			
			void CreateError(const etk::UString& _data, int32_t _pos, const ejson::filePos& _filePos, const etk::UString& _comment);
			void DisplayError(void);
		public: // herited function:
			virtual nodeType_te GetType(void) const { return typeDocument; };
			bool IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc);
			bool IGenerate(etk::UString& _data, int32_t _indent) const;
			virtual ejson::Document* ToDocument(void) { return this; };
			virtual const ejson::Document* ToDocument(void) const { return this; };
	};
};

#define EJSON_CREATE_ERROR(doc,data,pos,filePos,comment) \
	do { \
		JSON_ERROR(comment); \
		(doc).CreateError((data),(pos),(filePos),(comment)); \
	} while (0)

//__LINE__, __class__, __func__

#endif


