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
	m_filePos(0,0)
{
	
}

ejson::Document::~Document(void)
{

}

bool ejson::Document::IGenerate(etk::UString& _data, int32_t _indent) const
{
	ejson::Object::IGenerate(_data, _indent+1);
	_data += "\n";
	return true;
}

bool ejson::Document::Parse(const etk::UString& _data)
{
	JSON_VERBOSE("Start parsing document (type: string) size=" << _data.Size());
	Clear();
	ejson::filePos filePos(1,0);
	int32_t parsePos = 0;
	return IParse(_data, parsePos, filePos, *this);
}

bool ejson::Document::Generate(etk::UString& _data)
{
	_data = "";
	return IGenerate(_data,0);
}

bool ejson::Document::Load(const etk::UString& _file)
{
	// Start loading the XML : 
	JSON_VERBOSE("open file (xml) \"" << _file << "\"");
	Clear();
	etk::FSNode tmpFile(_file);
	if (false == tmpFile.Exist()) {
		JSON_ERROR("File Does not exist : " << _file);
		return false;
	}
	int64_t fileSize = tmpFile.FileSize();
	if (0==fileSize) {
		JSON_ERROR("This file is empty : " << _file);
		return false;
	}
	if (false == tmpFile.FileOpenRead()) {
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
	tmpFile.FileRead(fileBuffer, 1, fileSize);
	// close the file:
	tmpFile.FileClose();
	
	// convert in UTF8 :
	etk::UString tmpDataUnicode(fileBuffer, unicode::EDN_CHARSET_UTF8);
	// remove temporary buffer:
	delete(fileBuffer);
	// parse the data :
	bool ret = Parse(tmpDataUnicode);
	//Display();
	return ret;
}

bool ejson::Document::Store(const etk::UString& _file)
{
	etk::UString createData;
	if (false == Generate(createData)) {
		JSON_ERROR("Error while creating the XML : " << _file);
		return false;
	}
	etk::FSNode tmpFile(_file);
	if (false == tmpFile.FileOpenWrite()) {
		JSON_ERROR("Can not open (w) the file : " << _file);
		return false;
	}
	etk::Char endTable = createData.c_str();
	if (tmpFile.FileWrite(endTable, sizeof(char), endTable.Size()) != endTable.Size()) {
		JSON_ERROR("Error while writing output XML file : " << _file);
		tmpFile.FileClose();
		return false;
	}
	tmpFile.FileClose();
	return true;
}

void ejson::Document::Display(void)
{
	etk::UString tmpp;
	IGenerate(tmpp, 0);
	JSON_INFO("Generated JSON : \n" << tmpp);
}

static etk::UString CreatePosPointer(const etk::UString& _line, int32_t _pos)
{
	etk::UString out;
	int32_t iii;
	for (iii=0; iii<_pos && iii<_line.Size(); iii++) {
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

void ejson::Document::DisplayError(void)
{
	if (m_comment.Size()==0) {
		JSON_ERROR("No error detected ???");
		return;
	}
	JSON_ERROR(m_filePos << " " << m_comment << "\n"
	           << m_Line << "\n"
	           << CreatePosPointer(m_Line, m_filePos.GetCol()) );
	#ifdef ENABLE_CRITICAL_WHEN_ERROR
		JSON_CRITICAL("detect error");
	#endif
}

void ejson::Document::CreateError(const etk::UString& _data, int32_t _pos, const ejson::filePos& _filePos, const etk::UString& _comment)
{
	m_comment = _comment;
	m_Line = _data.ExtractLine(_pos);
	m_filePos = _filePos;
	if (true==m_writeErrorWhenDetexted) {
		DisplayError();
	}
}

bool ejson::Document::IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc)
{
	JSON_PARSE_ELEMENT("start parse : 'Document' ");
	bool haveMainNode=false;
	bool nodeParsed=false;
	for (int32_t iii=_pos; iii<_data.Size(); iii++) {
		_filePos.Check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			DrawElementParsed(_data[iii], _filePos);
		#endif
		ejson::filePos tmpPos;
		if(    _data[iii]==' '
		    || _data[iii]=='\t'
		    || _data[iii]=='\n'
		    || _data[iii]=='\r') {
			// white space ==> nothing to do ...
		} else if (_data[iii]=='{') {
			if (nodeParsed==true) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "element already parsed");
				_pos=iii;
			}
			// find a main object:
			// ==> generic sub parsing
			iii++;
			haveMainNode=true;
			nodeParsed=true;
			ejson::Object::IParse(_data, iii, _filePos, _doc);
		} else if(_data[iii]=='}') {
			_pos=iii; // ==> return the end element type ==> usefull to check end and check if adding element is needed
			if (haveMainNode==true) {
				// find end of value:
				return true;
			} else {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "find } but never start !!!");
				return false;
			}
		} else {
			if (nodeParsed==true) {
				_pos=iii;
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "element already parsed");
				return false;
			}
			nodeParsed=true;
			// this might not have the '{' start element !!!
			if (false==ejson::Object::IParse(_data, iii, _filePos, _doc)) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Object sub parsing in error");
				_pos = iii;
				return false;
			}
		}
	}
	return true;
}

