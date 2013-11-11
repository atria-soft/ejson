/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <vector>
#include <etk/UString.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"ejson::test"

class testCheck {
	public:
		std::u32string m_ref;
		std::u32string m_input;
		int32_t m_errorPos; // -1 : no error , 1 : parsing error, 2 generation error, 3 comparaison error ????
		testCheck(void) {};
		void set(const std::u32string& _ref, int32_t _pos, const std::u32string& _input) {
			m_ref = _ref;
			m_input = _input;
			m_errorPos = _pos;
		}
};

std::vector<testCheck> l_list;

void init(void) {
	std::u32string reference;
	std::u32string input;
	testCheck check;
	
	//  == ====================================================
	check.set("test ejson::Doc", -2, "");
	l_list.push_back(check);
	//  == ====================================================
	reference = "{\n}\n";
	check.set(reference,
	          -1,
	          "{}\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          -1,
	          "{    \t\r   }\n");
	l_list.push_back(check);
	//  == ====================================================
	check.set("test ejson::null", -2, "");
	l_list.push_back(check);
	// ------------------------------------------------------
	reference = "{\n\t\"tmpElement\": null\n}\n";
	check.set(reference,
	          -1,
	          "{ tmpElement:null }\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          -1,
	          "{ \t\ntmpElement:null \t\n }\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          -1,
	          "tmpElement:null\n");
	l_list.push_back(check);
	//  == ====================================================
	check.set("test ejson::boolean", -2, "");
	l_list.push_back(check);
	// ------------------------------------------------------
	reference = "{\n\t\"tmpElement\": true\n}\n";
	check.set(reference,
	          -1,
	          "{ tmpElement:true }\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          -1,
	          "{ \t\ntmpElement:true \t\n }\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          -1,
	          "tmpElement:true\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	reference = "{\n\t\"tmpElement\": false\n}\n";
	check.set(reference,
	          -1,
	          "{ tmpElement:false }\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          -1,
	          "{ \t\ntmpElement:false \t\n }\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          -1,
	          "tmpElement:false\n");
	l_list.push_back(check);
	//  == ====================================================
	check.set("test ejson::number", -2, "");
	l_list.push_back(check);
	// ------------------------------------------------------
	reference = "{\n\t\"tmpElement\": 956256\n}\n";
	check.set(reference,
	          -1,
	          "{ tmpElement:956256 }\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          -1,
	          "{ \t\ntmpElement:956256 \t\n }\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          -1,
	          "tmpElement:956256\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("{\n\t\"tmpElement\": 956256\n}\n",
	          -1,
	          "{tmpElement:956256}\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("{\n\t\"tmpElement\": -956256\n}\n",
	          -1,
	          "{tmpElement:-956256}\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("{\n\t\"tmpElement\": -956256\n}\n",
	          -1,
	          "{tmpElement:-956256}\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("{\n\t\"tmpElement\": -956.256\n}\n",
	          -1,
	          "{tmpElement:-956.256}\n");
	l_list.push_back(check);
	/*
	// ------------------------------------------------------
	check.set("{\n\t\"tmpElement\": -956956544454621184\n}\n",
	          -1,
	          "{tmpElement:-956956544454621354.256}\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("{\n\t\"tmpElement\": 0.000002\n}\n",
	          -1,
	          "{tmpElement:+.000001565464}\n");
	l_list.push_back(check);
	*/
	
	
	//  == ====================================================
	check.set("test ejson::all", -2, "");
	l_list.push_back(check);
	//  == ====================================================
	reference = "{\n"
	            "	\"menu\": {\n"
	            "		\"id\": \"file\",\n"
	            "		\"value\": \"File\",\n"
	            "		\"popup\": {\n"
	            "			\"menuitem\": { \"value\": \"Close\", \"onclick\": \"CloseDoc()\" }\n"
	            "		}\n"
	            "	}\n"
	            "}\n";
	check.set(reference,
	          -1,
	          reference);
	l_list.push_back(check);
	// ------------------------------------------------------
	reference = "{\n"
	            "	\"menu\": {\n"
	            "		\"id\": \"file\",\n"
	            "		\"value\": \"File\",\n"
	            "		\"popup\": {\n"
	            "			\"menuitem\": [\n"
	            "				{ \"value\": \"Close\", \"onclick\": \"CloseDoc()\" },\n"
	            "				{ \"value\": \"New\", \"onclick\": \"CreateNewDoc()\" },\n"
	            "				{ \"value\": \"Open\", \"onclick\": \"OpenDoc()\" },\n"
	            "				{ \"value\": \"Close\", \"onclick\": \"CloseDoc()\" }\n"
	            "			]\n"
	            "		}\n"
	            "	}\n"
	            "}\n";
	check.set(reference,
	          -1,
	          reference);
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          -1,
	            "{\n"
	            "	menu: {\n"
	            "		id: \"file\",\n"
	            "		value: \"File\",\n"
	            "		popup: {\n"
	            "			menuitem: [\n"
	            "				{\n"
	            "					value: \"Close\",\n"
	            "					onclick: \"CloseDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					value: \"New\",\n"
	            "					onclick: \"CreateNewDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					value: \"Open\",\n"
	            "					onclick: \"OpenDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					value: \"Close\",\n"
	            "					onclick: \"CloseDoc()\"\n"
	            "				}\n"
	            "			]\n"
	            "		}\n"
	            "	}\n"
	            "}\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          -1,
	            "menu: {\n"
	            "	id: \"file\",\n"
	            "	value: \"File\",\n"
	            "	popup: {\n"
	            "		menuitem: [\n"
	            "			{\n"
	            "				value: \"Close\",\n"
	            "				onclick: \"CloseDoc()\"\n"
	            "			},\n"
	            "			{\n"
	            "				value: \"New\",\n"
	            "				onclick: \"CreateNewDoc()\"\n"
	            "			},\n"
	            "			{\n"
	            "				value: \"Open\",\n"
	            "				onclick: \"OpenDoc()\"\n"
	            "			},\n"
	            "			{\n"
	            "				value: \"Close\",\n"
	            "				onclick: \"CloseDoc()\"\n"
	            "			}\n"
	            "		]\n"
	            "	}\n"
	            "}\n");
	l_list.push_back(check);
	
//////////////////////////////////////////////////////////////////////////
	reference = "{\n"
	            "	\"glossary\": {\n"
	            "		\"title\": \"example glossary\",\n"
	            "		\"GlossDiv\": {\n"
	            "			\"title\": \"S\",\n"
	            "			\"GlossList\": {\n"
	            "				\"GlossEntry\": {\n"
	            "					\"ID\": \"SGML\",\n"
	            "					\"SortAs\": \"SGML\",\n"
	            "					\"GlossTerm\": \"Standard Generalized Markup Language\",\n"
	            "					\"Acronym\": \"SGML\",\n"
	            "					\"Abbrev\": \"ISO 8879:1986\",\n"
	            "					\"GlossDef\": {\n"
	            "						\"para\": \"A meta-markup language, used to create markup languages such as DocBook.\",\n"
	            "						\"GlossSeeAlso\": [ \"GML\", \"XML\" ]\n"
	            "					},\n"
	            "					\"GlossSee\": \"markup\"\n"
	            "				}\n"
	            "			}\n"
	            "		}\n"
	            "	}\n"
	            "}\n";
	check.set(reference,
	          -1,
	          reference);
	l_list.push_back(check);
	// ------------------------------------------------------
	reference = "{\n"
	            "	\"menu\": {\n"
	            "		\"id\": \"file\",\n"
	            "		\"value\": \"File\",\n"
	            "		\"popup\": {\n"
	            "			\"menuitem\": [\n"
	            "				{ \"value\": \"New\", \"onclick\": \"CreateNewDoc()\" },\n"
	            "				{ \"value\": \"Open\", \"onclick\": \"OpenDoc()\" },\n"
	            "				{ \"value\": \"Close\", \"onclick\": \"CloseDoc()\" }\n"
	            "			]\n"
	            "		}\n"
	            "	}\n"
	            "}\n";
	check.set(reference,
	          -1,
	          reference);
	l_list.push_back(check);
	// ------------------------------------------------------
	reference = "{\n"
	            "	\"widget\": {\n"
	            "		\"debug\": \"on\",\n"
	            "		\"window\": {\n"
	            "			\"title\": \"Sample Konfabulator Widget\",\n"
	            "			\"name\": \"main_window\",\n"
	            "			\"width\": 500,\n"
	            "			\"height\": 500\n"
	            "		},\n"
	            "		\"image\": {\n"
	            "			\"src\": \"Images/Sun.png\",\n"
	            "			\"name\": \"sun1\",\n"
	            "			\"hOffset\": 250,\n"
	            "			\"vOffset\": 250,\n"
	            "			\"alignment\": \"center\"\n"
	            "		},\n"
	            "		\"text\": {\n"
	            "			\"data\": \"Click Here\",\n"
	            "			\"size\": 36,\n"
	            "			\"style\": \"bold\",\n"
	            "			\"name\": \"text1\",\n"
	            "			\"hOffset\": 250,\n"
	            "			\"vOffset\": 100,\n"
	            "			\"alignment\": \"center\",\n"
	            "			\"onMouseUp\": \"sun1.opacity = (sun1.opacity / 100) * 90;\"\n"
	            "		}\n"
	            "	}\n"
	            "}\n";
	check.set(reference,
	          -1,
	          reference);
	l_list.push_back(check);
	// ------------------------------------------------------
	reference = "{\n"
	            "	\"web-app\": {\n"
	            "		\"servlet\": [\n"
	            "			{\n"
	            "				\"servlet-name\": \"cofaxCDS\",\n"
	            "				\"servlet-class\": \"org.cofax.cds.CDSServlet\",\n"
	            "				\"init-param\": {\n"
	            "					\"configGlossary:installationAt\": \"Philadelphia, PA\",\n"
	            "					\"configGlossary:adminEmail\": \"ksm@pobox.com\",\n"
	            "					\"configGlossary:poweredBy\": \"Cofax\",\n"
	            "					\"configGlossary:poweredByIcon\": \"/images/cofax.gif\",\n"
	            "					\"configGlossary:staticPath\": \"/content/static\",\n"
	            "					\"templateProcessorClass\": \"org.cofax.WysiwygTemplate\",\n"
	            "					\"templateLoaderClass\": \"org.cofax.FilesTemplateLoader\",\n"
	            "					\"templatePath\": \"templates\",\n"
	            "					\"templateOverridePath\": \"\",\n"
	            "					\"defaultListTemplate\": \"listTemplate.htm\",\n"
	            "					\"defaultFileTemplate\": \"articleTemplate.htm\",\n"
	            "					\"useJSP\": false,\n"
	            "					\"jspListTemplate\": \"listTemplate.jsp\",\n"
	            "					\"jspFileTemplate\": \"articleTemplate.jsp\",\n"
	            "					\"cachePackageTagsTrack\": 200,\n"
	            "					\"cachePackageTagsStore\": 200,\n"
	            "					\"cachePackageTagsRefresh\": 60,\n"
	            "					\"cacheTemplatesTrack\": 100,\n"
	            "					\"cacheTemplatesStore\": 50,\n"
	            "					\"cacheTemplatesRefresh\": 15,\n"
	            "					\"cachePagesTrack\": 200,\n"
	            "					\"cachePagesStore\": 100,\n"
	            "					\"cachePagesRefresh\": 10,\n"
	            "					\"cachePagesDirtyRead\": 10,\n"
	            "					\"searchEngineListTemplate\": \"forSearchEnginesList.htm\",\n"
	            "					\"searchEngineFileTemplate\": \"forSearchEngines.htm\",\n"
	            "					\"searchEngineRobotsDb\": \"WEB-INF/robots.db\",\n"
	            "					\"useDataStore\": true,\n"
	            "					\"dataStoreClass\": \"org.cofax.SqlDataStore\",\n"
	            "					\"redirectionClass\": \"org.cofax.SqlRedirection\",\n"
	            "					\"dataStoreName\": \"cofax\",\n"
	            "					\"dataStoreDriver\": \"com.microsoft.jdbc.sqlserver.SQLServerDriver\",\n"
	            "					\"dataStoreUrl\": \"jdbc:microsoft:sqlserver://LOCALHOST:1433;DatabaseName=goon\",\n"
	            "					\"dataStoreUser\": \"sa\",\n"
	            "					\"dataStorePassword\": \"dataStoreTestQuery\",\n"
	            "					\"dataStoreTestQuery\": \"SET NOCOUNT ON;select test='test';\",\n"
	            "					\"dataStoreLogFile\": \"/usr/local/tomcat/logs/datastore.log\",\n"
	            "					\"dataStoreInitConns\": 10,\n"
	            "					\"dataStoreMaxConns\": 100,\n"
	            "					\"dataStoreConnUsageLimit\": 100,\n"
	            "					\"dataStoreLogLevel\": \"debug\",\n"
	            "					\"maxUrlLength\": 500\n"
	            "				}\n"
	            "			},\n"
	            "			{\n"
	            "				\"servlet-name\": \"cofaxEmail\",\n"
	            "				\"servlet-class\": \"org.cofax.cds.EmailServlet\",\n"
	            "				\"init-param\": { \"mailHost\": \"mail1\", \"mailHostOverride\": \"mail2\" }\n"
	            "			},\n"
	            "			{\n"
	            "				\"servlet-name\": \"cofaxAdmin\",\n"
	            "				\"servlet-class\": \"org.cofax.cds.AdminServlet\"\n"
	            "			},\n"
	            "			{ \"servlet-name\": \"fileServlet\", \"servlet-class\": \"org.cofax.cds.FileServlet\" },\n"
	            "			{\n"
	            "				\"servlet-name\": \"cofaxTools\",\n"
	            "				\"servlet-class\": \"org.cofax.cms.CofaxToolsServlet\",\n"
	            "				\"init-param\": {\n"
	            "					\"templatePath\": \"toolstemplates/\",\n"
	            "					\"log\": 1,\n"
	            "					\"logLocation\": \"/usr/local/tomcat/logs/CofaxTools.log\",\n"
	            "					\"logMaxSize\": \"\",\n"
	            "					\"dataLog\": 1,\n"
	            "					\"dataLogLocation\": \"/usr/local/tomcat/logs/dataLog.log\",\n"
	            "					\"dataLogMaxSize\": \"\",\n"
	            "					\"removePageCache\": \"/content/admin/remove?cache=pages&id=\",\n"
	            "					\"removeTemplateCache\": \"/content/admin/remove?cache=templates&id=\",\n"
	            "					\"fileTransferFolder\": \"/usr/local/tomcat/webapps/content/fileTransferFolder\",\n"
	            "					\"lookInContext\": 1,\n"
	            "					\"adminGroupID\": 4,\n"
	            "					\"betaServer\": true\n"
	            "				}\n"
	            "			}\n"
	            "		],\n"
	            "		\"servlet-mapping\": {\n"
	            "			\"cofaxCDS\": \"/\",\n"
	            "			\"cofaxEmail\": \"/cofaxutil/aemail/*\",\n"
	            "			\"cofaxAdmin\": \"/admin/*\",\n"
	            "			\"fileServlet\": \"/static/*\",\n"
	            "			\"cofaxTools\": \"/tools/*\"\n"
	            "		},\n"
	            "		\"taglib\": { \"taglib-uri\": \"cofax.tld\", \"taglib-location\": \"/WEB-INF/tlds/cofax.tld\" }\n"
	            "	}\n"
	            "}\n";
	check.set(reference,
	          -1,
	          reference);
	l_list.push_back(check);
	// ------------------------------------------------------
	reference = "{\n"
	            "	\"menu\": {\n"
	            "		\"header\": \"SVG Viewer\",\n"
	            "		\"items\": [\n"
	            "			{ \"id\": \"Open\" },\n"
	            "			{ \"id\": \"OpenNew\", \"label\": \"Open New\" },\n"
	            "			null,\n"
	            "			{ \"id\": \"ZoomIn\", \"label\": \"Zoom In\" },\n"
	            "			{ \"id\": \"ZoomOut\", \"label\": \"Zoom Out\" },\n"
	            "			{ \"id\": \"OriginalView\", \"label\": \"Original View\" },\n"
	            "			null,\n"
	            "			{ \"id\": \"Quality\" },\n"
	            "			{ \"id\": \"Pause\" },\n"
	            "			{ \"id\": \"Mute\" },\n"
	            "			null,\n"
	            "			{ \"id\": \"Find\", \"label\": \"Find...\" },\n"
	            "			{ \"id\": \"FindAgain\", \"label\": \"Find Again\" },\n"
	            "			{ \"id\": \"Copy\" },\n"
	            "			{ \"id\": \"CopyAgain\", \"label\": \"Copy Again\" },\n"
	            "			{ \"id\": \"CopySVG\", \"label\": \"Copy SVG\" },\n"
	            "			{ \"id\": \"ViewSVG\", \"label\": \"View SVG\" },\n"
	            "			{ \"id\": \"ViewSource\", \"label\": \"View Source\" },\n"
	            "			{ \"id\": \"SaveAs\", \"label\": \"Save As\" },\n"
	            "			null,\n"
	            "			{ \"id\": \"Help\" },\n"
	            "			{ \"id\": \"About\", \"label\": \"About Adobe CVG Viewer...\" }\n"
	            "		]\n"
	            "	}\n"
	            "}\n";
	check.set(reference,
	          -1,
	          reference);
	l_list.push_back(check);
	// ------------------------------------------------------
}

int main(int argc, const char *argv[]) {
	debug::setGeneralLevel(etk::logLevelVerbose);
	init();
	int32_t countError = 0;
	int32_t countSeparator = 0;
	int32_t sectionID = 0;
	for (int32_t iii=0 ; iii<l_list.size() ; iii++) {
		int32_t jjj= iii-countSeparator+1;
		if (l_list[iii].m_errorPos == -2) {
			countSeparator++;
			sectionID = 0;
			JSON_INFO("-------------------------------------------------------------");
			JSON_INFO("-- " << l_list[iii].m_ref);
			JSON_INFO("-------------------------------------------------------------");
			continue;
		}
		sectionID++;
		ejson::Document doc;
		std::u32string out("");
		//JSON_DEBUG("parse : \n" << l_list[iii].m_input);
		if (false == doc.parse(l_list[iii].m_input)) {
			if (l_list[iii].m_errorPos == 1) {
				JSON_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } Parsing in error (correct result)");
			} else {
				JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Parsing might be OK");
				JSON_ERROR("parse : \n" << l_list[iii].m_input);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos == 1) {
			JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Parsing might be in error ...");
			JSON_ERROR("parse : \n" << l_list[iii].m_input);
			doc.display();
			countError++;
			continue;
		}
		if (false == doc.generate(out)) {
			if (l_list[iii].m_errorPos == 2) {
				JSON_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } generate in error (correct result)");
			} else {
				JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } generate output might be OK");
				JSON_ERROR("generate : \n" << out);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos == 2) {
			JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Generating might be in error ...");
			countError++;
			continue;
		}
		if (l_list[iii].m_ref != out) {
			if (l_list[iii].m_errorPos == 3) {
				JSON_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } Result in error (normal case)");
			} else {
				JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } different output");
				std::vector<std::u32string> tmpout = out.split('\n');
				std::vector<std::u32string> tmpref = l_list[iii].m_ref.split('\n');
				//JSON_ERROR("generate : \n" << out);
				//JSON_ERROR("reference : \n" << l_list[iii].m_ref);
				for (int32_t jjj=0; jjj<tmpout.size() || jjj<tmpref.size(); ++jjj) {
					if (jjj<tmpref.size()) {
						JSON_INFO("[" << jjj << "] " << tmpref[jjj] );
					}
					if (jjj<tmpout.size()) {
						if (jjj>=tmpref.size() || tmpref[jjj] != tmpout[jjj]) {
							JSON_ERROR("[" << jjj << "] " << tmpout[jjj] );
						}
					}
				}
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos == 3) {
			JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR} checking result might be in error...");
			std::vector<std::u32string> tmpout = out.split('\n');
			std::vector<std::u32string> tmpref = l_list[iii].m_ref.split('\n');
			//JSON_ERROR("generate : \n" << out);
			//JSON_ERROR("reference : \n" << l_list[iii].m_ref);
			for (int32_t jjj=0; jjj<tmpout.size() || jjj<tmpref.size(); ++jjj) {
				if (jjj<tmpref.size()) {
					JSON_INFO("[" << jjj << "] " << tmpref[jjj] );
				}
				if (jjj<tmpout.size()) {
					if (jjj>=tmpref.size() || tmpref[jjj] != tmpout[jjj]) {
						JSON_ERROR("[" << jjj << "] " << tmpout[jjj] );
					}
				}
			}
			countError++;
			continue;
		}
		JSON_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  }");
	}
	if (countError>0) {
		JSON_ERROR("[TEST] produce " << countError << " error on " << l_list.size()-countSeparator << " test");
	} else {
		JSON_INFO("[TEST] produce " << countError << " error on " << l_list.size()-countSeparator << " test");
	}
	return 0;
}

