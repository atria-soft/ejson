/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <ejson/ejson.h>
#include <ejson/debug.h>
#include <etk/os/FSNode.h>

#include <ejson/Object.h>
#include <ejson/Array.h>
#include <ejson/String.h>
#include <ejson/Null.h>
#include <ejson/Number.h>
#include <ejson/Boolean.h>

#undef __class__
#define __class__	"Document"

ejson::Document::Document(void) : 
    m_writeErrorWhenDetexted(true),
    m_comment(""),
    m_Line(""),
    m_filePos(0,0) {
	
}

ejson::Document::~Document(void) {
	
}

bool ejson::Document::iGenerate(std::string& _data, int32_t _indent) const {
	ejson::Object::iGenerate(_data, _indent+1);
	_data += "\n";
	return true;
}

bool ejson::Document::parse(const std::string& _data) {
	JSON_VERBOSE("Start parsing document (type: string) size=" << _data.size());
	clear();
	ejson::filePos filePos(1,0);
	int32_t parsePos = 0;
	return iParse(_data, parsePos, filePos, *this);
}

bool ejson::Document::generate(std::string& _data) {
	_data = "";
	return iGenerate(_data,0);
}

bool ejson::Document::load(const std::string& _file) {
	// Start loading the XML : 
	JSON_VERBOSE("open file (xml) \"" << _file << "\"");
	clear();
	etk::FSNode tmpFile(_file);
	if (false == tmpFile.exist()) {
		JSON_ERROR("File Does not exist : " << _file);
		return false;
	}
	int64_t fileSize = tmpFile.fileSize();
	if (0 == fileSize) {
		JSON_ERROR("This file is empty : " << _file);
		return false;
	}
	if (false == tmpFile.fileOpenRead()) {
		JSON_ERROR("Can not open (r) the file : " << _file);
		return false;
	}
	// allocate data
	char * fileBuffer = new char[fileSize+5];
	if (NULL == fileBuffer) {
		JSON_ERROR("Error Memory allocation size=" << fileSize);
		return false;
	}
	// TODO :  change this ... get the charset from the Declaration element ...
	memset(fileBuffer, 0, (fileSize+5)*sizeof(char));
	// load data from the file :
	tmpFile.fileRead(fileBuffer, 1, fileSize);
	// close the file:
	tmpFile.fileClose();
	
	std::string tmpDataUnicode(fileBuffer);
	// remove temporary buffer:
	delete(fileBuffer);
	// parse the data :
	bool ret = parse(tmpDataUnicode);
	//Display();
	return ret;
}

bool ejson::Document::store(const std::string& _file) {
	std::string createData;
	if (false == generate(createData)) {
		JSON_ERROR("Error while creating the XML : " << _file);
		return false;
	}
	etk::FSNode tmpFile(_file);
	if (false == tmpFile.fileOpenWrite()) {
		JSON_ERROR("Can not open (w) the file : " << _file);
		return false;
	}
	if (tmpFile.fileWrite((char*)createData.c_str(), sizeof(char), createData.size()) != createData.size()) {
		JSON_ERROR("Error while writing output XML file : " << _file);
		tmpFile.fileClose();
		return false;
	}
	tmpFile.fileClose();
	return true;
}

void ejson::Document::display(void) {
	std::string tmpp;
	iGenerate(tmpp, 0);
	JSON_INFO("Generated JSON : \n" << tmpp);
}

static std::string createPosPointer(const std::string& _line, int32_t _pos) {
	std::string out;
	int32_t iii;
	for (iii=0; iii<_pos && iii<_line.size(); iii++) {
		if (_line[iii] == '\t') {
			out += "\t";
		} else {
			out += " ";
		}
	}
	for (; iii<_pos; iii++) {
		out += " ";
	}
	out += "^";
	return out;
}

void ejson::Document::displayError(void) {
	if (m_comment.size() == 0) {
		JSON_ERROR("No error detected ???");
		return;
	}
	JSON_ERROR(m_filePos << " " << m_comment << "\n"
	           << m_Line << "\n"
	           << createPosPointer(m_Line, m_filePos.getCol()) );
	#ifdef ENABLE_CRITICAL_WHEN_ERROR
		JSON_CRITICAL("detect error");
	#endif
}

void ejson::Document::createError(const std::string& _data, int32_t _pos, const ejson::filePos& _filePos, const std::string& _comment) {
	m_comment = _comment;
	m_Line = extract_line(_data, _pos);
	m_filePos = _filePos;
	if (true == m_writeErrorWhenDetexted) {
		displayError();
	}
}

bool ejson::Document::iParse(const std::string& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc) {
	JSON_PARSE_ELEMENT("start parse : 'Document' ");
	bool haveMainNode=false;
	bool nodeParsed=false;
	for (int32_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			drawElementParsed(_data[iii], _filePos);
		#endif
		ejson::filePos tmpPos;
		if(    _data[iii] == ' '
		    || _data[iii] == '\t'
		    || _data[iii] == '\n'
		    || _data[iii] == '\r') {
			// white space  == > nothing to do ...
		} else if (_data[iii] == '{') {
			if (nodeParsed == true) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "element already parsed");
				_pos=iii;
			}
			// find a main object:
			//  == > generic sub parsing
			iii++;
			haveMainNode=true;
			nodeParsed=true;
			ejson::Object::iParse(_data, iii, _filePos, _doc);
		} else if(_data[iii] == '}') {
			_pos=iii; //  == > return the end element type ==> usefull to check end and check if adding element is needed
			if (haveMainNode == true) {
				// find end of value:
				return true;
			} else {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "find } but never start !!!");
				return false;
			}
		} else {
			if (nodeParsed == true) {
				_pos=iii;
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "element already parsed");
				return false;
			}
			nodeParsed=true;
			// this might not have the '{' start element !!!
			if (false == ejson::Object::iParse(_data, iii, _filePos, _doc)) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Object sub parsing in error");
				_pos = iii;
				return false;
			}
		}
	}
	return true;
}

