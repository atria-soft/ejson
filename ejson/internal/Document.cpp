/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <ejson/internal/Document.hpp>
#include <ejson/debug.hpp>
#include <etk/os/FSNode.hpp>

#include <ejson/internal/Object.hpp>
#include <ejson/internal/Array.hpp>
#include <ejson/internal/String.hpp>
#include <ejson/internal/Null.hpp>
#include <ejson/internal/Number.hpp>
#include <ejson/internal/Boolean.hpp>

ememory::SharedPtr<ejson::internal::Document> ejson::internal::Document::create() {
	return ememory::SharedPtr<ejson::internal::Document>(new ejson::internal::Document());
}

ejson::internal::Document::Document() :
  m_writeErrorWhenDetexted(true),
  m_comment(""),
  m_Line(""),
  m_filePos(0,0) {
	m_type = ejson::valueType::document;
}

bool ejson::internal::Document::iGenerate(std::string& _data, size_t _indent) const {
	ejson::internal::Object::iGenerate(_data, _indent+1);
	_data += "\n";
	return true;
}

bool ejson::internal::Document::parse(const std::string& _data) {
	EJSON_VERBOSE("Start parsing document (type: string) size=" << _data.size());
	clear();
	ejson::FilePos filePos(1,0);
	size_t parsePos = 0;
	return iParse(_data, parsePos, filePos, *this);
}

bool ejson::internal::Document::generate(std::string& _data) {
	_data = "";
	return iGenerate(_data,0);
}

bool ejson::internal::Document::load(const std::string& _file) {
	// Start loading the XML : 
	EJSON_VERBOSE("open file (xml) \"" << _file << "\"");
	clear();
	etk::FSNode tmpFile(_file);
	if (false == tmpFile.exist()) {
		EJSON_ERROR("File Does not exist : " << _file);
		return false;
	}
	int64_t fileSize = tmpFile.fileSize();
	if (0 == fileSize) {
		EJSON_ERROR("This file is empty : " << _file);
		return false;
	}
	if (false == tmpFile.fileOpenRead()) {
		EJSON_ERROR("Can not open (r) the file : " << _file);
		return false;
	}
	// allocate data
	std::vector<char> fileBuffer;
	fileBuffer.resize(fileSize+5, 0);
	// load data from the file :
	tmpFile.fileRead(&fileBuffer[0], 1, fileSize);
	// close the file:
	tmpFile.fileClose();
	
	std::string tmpDataUnicode(&fileBuffer[0]);
	// parse the data :
	bool ret = parse(tmpDataUnicode);
	//Display();
	return ret;
}

bool ejson::internal::Document::store(const std::string& _file) {
	std::string createData;
	if (false == generate(createData)) {
		EJSON_ERROR("Error while creating the XML : " << _file);
		return false;
	}
	etk::FSNode tmpFile(_file);
	if (false == tmpFile.fileOpenWrite()) {
		EJSON_ERROR("Can not open (w) the file : " << _file);
		return false;
	}
	if (tmpFile.fileWrite((char*)createData.c_str(), sizeof(char), createData.size()) != (int32_t)createData.size()) {
		EJSON_ERROR("Error while writing output XML file : " << _file);
		tmpFile.fileClose();
		return false;
	}
	tmpFile.fileClose();
	return true;
}


static std::string createPosPointer(const std::string& _line, size_t _pos) {
	std::string out;
	size_t iii;
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

bool ejson::internal::Document::iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) {
	EJSON_PARSE_ELEMENT("start parse : 'Document' ");
	bool haveMainNode=false;
	bool nodeParsed=false;
	for (size_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			drawElementParsed(_data[iii], _filePos);
		#endif
		ejson::FilePos tmpPos;
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
			ejson::internal::Object::iParse(_data, iii, _filePos, _doc);
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
			if (false == ejson::internal::Object::iParse(_data, iii, _filePos, _doc)) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Object sub parsing in error");
				_pos = iii;
				return false;
			}
		}
	}
	return true;
}


void ejson::internal::Document::setDisplayError(bool _value) {
	m_writeErrorWhenDetexted = _value;
}

bool ejson::internal::Document::getDisplayError() {
	return m_writeErrorWhenDetexted;
}

void ejson::internal::Document::displayError() {
	if (m_comment.size() == 0) {
		EJSON_INFO("No error detected ???");
		return;
	}
	EJSON_ERROR(m_filePos << " " << m_comment << "\n"
	           << m_Line << "\n"
	           << createPosPointer(m_Line, m_filePos.getCol()) );
	#ifdef ENABLE_CRITICAL_WHEN_ERROR
		EJSON_CRITICAL("detect error");
	#endif
}

void ejson::internal::Document::createError(const std::string& _data,
                                            size_t _pos,
                                            const ejson::FilePos& _filePos,
                                            const std::string& _comment) {
	m_comment = _comment;
	m_Line = etk::extract_line(_data, _pos);
	m_filePos = _filePos;
	if (m_writeErrorWhenDetexted == true) {
		displayError();
	}
}

