/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/Debug.h>
#include <etk/Vector.h>
#include <etk/UString.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"ejson::test"

class testCheck
{
	public:
		etk::UString m_ref;
		etk::UString m_input;
		int32_t m_errorPos; // -1 : no error , 1 : parsing error, 2 generation error, 3 comparaison error ????
		testCheck(void) {};
		void Set(const etk::UString& _ref, int32_t _pos, const etk::UString& _input)
		{
			m_ref = _ref;
			m_input = _input;
			m_errorPos = _pos;
		}
};

etk::Vector<testCheck> l_list;

void Init(void)
{
	etk::UString reference;
	etk::UString input;
	testCheck check;
	
	// ======================================================
	check.Set("test ejson::Doc", -2, "");
	l_list.PushBack(check);
	// ======================================================
	reference = "{\n}\n";
	check.Set(reference,
	          -1,
	          "{}\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "{    \t\r   }\n");
	l_list.PushBack(check);
	// ======================================================
	check.Set("test ejson::null", -2, "");
	l_list.PushBack(check);
	// ------------------------------------------------------
	reference = "{\n\t\"tmpElement\": null\n}\n";
	check.Set(reference,
	          -1,
	          "{ tmpElement:null }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "{ \t\ntmpElement:null \t\n }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "tmpElement:null\n");
	l_list.PushBack(check);
	// ======================================================
	check.Set("test ejson::boolean", -2, "");
	l_list.PushBack(check);
	// ------------------------------------------------------
	reference = "{\n\t\"tmpElement\": true\n}\n";
	check.Set(reference,
	          -1,
	          "{ tmpElement:true }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "{ \t\ntmpElement:true \t\n }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "tmpElement:true\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	reference = "{\n\t\"tmpElement\": false\n}\n";
	check.Set(reference,
	          -1,
	          "{ tmpElement:false }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "{ \t\ntmpElement:false \t\n }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "tmpElement:false\n");
	l_list.PushBack(check);
	// ======================================================
	check.Set("test ejson::number", -2, "");
	l_list.PushBack(check);
	// ------------------------------------------------------
	reference = "{\n\t\"tmpElement\": 956256.000000\n}\n";
	check.Set(reference,
	          -1,
	          "{ tmpElement:956256 }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "{ \t\ntmpElement:956256 \t\n }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "tmpElement:956256\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("{\n\t\"tmpElement\": 956256.000000\n}\n",
	          -1,
	          "{tmpElement:956256}\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("{\n\t\"tmpElement\": -956256.000000\n}\n",
	          -1,
	          "{tmpElement:-956256}\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("{\n\t\"tmpElement\": -956256.000000\n}\n",
	          -1,
	          "{tmpElement:-956256}\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("{\n\t\"tmpElement\": -956.256000\n}\n",
	          -1,
	          "{tmpElement:-956.256}\n");
	l_list.PushBack(check);
	
	
	
	// ======================================================
	check.Set("test ejson::all", -2, "");
	l_list.PushBack(check);
	// ======================================================
	reference = "{\n"
	            "	\"menu\": {\n"
	            "		\"id\": \"file\",\n"
	            "		\"value\": \"File\",\n"
	            "		\"popup\": {\n"
	            "			\"menuitem\": {\n"
	            "				\"value\": \"Close\",\n"
	            "				\"onclick\": \"CloseDoc()\"\n"
	            "			}\n"
	            "		}\n"
	            "	}\n"
	            "}\n";
	check.Set(reference,
	          -1,
	          reference);
	l_list.PushBack(check);
	// ------------------------------------------------------
	reference = "{\n"
	            "	\"menu\": {\n"
	            "		\"id\": \"file\",\n"
	            "		\"value\": \"File\",\n"
	            "		\"popup\": {\n"
	            "			\"menuitem\": [\n"
	            "				{\n"
	            "					\"value\": \"Close\",\n"
	            "					\"onclick\": \"CloseDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					\"value\": \"New\",\n"
	            "					\"onclick\": \"CreateNewDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					\"value\": \"Open\",\n"
	            "					\"onclick\": \"OpenDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					\"value\": \"Close\",\n"
	            "					\"onclick\": \"CloseDoc()\"\n"
	            "				}\n"
	            "			]\n"
	            "		}\n"
	            "	}\n"
	            "}\n";
	check.Set(reference,
	          -1,
	          reference);
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
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
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
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
	l_list.PushBack(check);
	
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
	            "						\"GlossSeeAlso\": [\n"
	            "							\"GML\",\n"
	            "							\"XML\"\n"
	            "						]\n"
	            "					},\n"
	            "					\"GlossSee\": \"markup\"\n"
	            "				}\n"
	            "			}\n"
	            "		}\n"
	            "	}\n"
	            "}\n";
	check.Set(reference,
	          -1,
	          reference);
	l_list.PushBack(check);
	// ------------------------------------------------------
	reference = "{\n"
	            "	\"menu\": {\n"
	            "		\"id\": \"file\",\n"
	            "		\"value\": \"File\",\n"
	            "		\"popup\": {\n"
	            "			\"menuitem\": [\n"
	            "				{\n"
	            "					\"value\": \"New\",\n"
	            "					\"onclick\": \"CreateNewDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					\"value\": \"Open\",\n"
	            "					\"onclick\": \"OpenDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					\"value\": \"Close\",\n"
	            "					\"onclick\": \"CloseDoc()\"\n"
	            "				}\n"
	            "			]\n"
	            "		}\n"
	            "	}\n"
	            "}\n";
	check.Set(reference,
	          -1,
	          reference);
	l_list.PushBack(check);
	// ------------------------------------------------------


//////////////////////////////////////////////////////////////////////////

	reference = "{\n"
	            "	\"widget\": {\n"
	            "		\"debug\": \"on\",\n"
	            "		\"window\": {\n"
	            "			\"title\": \"Sample Konfabulator Widget\",\n"
	            "			\"name\": \"main_window\",\n"
	            "			\"width\": 500.000000,\n"
	            "			\"height\": 500.000000\n"
	            "		},\n"
	            "		\"image\": {\n"
	            "			\"src\": \"Images/Sun.png\",\n"
	            "			\"name\": \"sun1\",\n"
	            "			\"hOffset\": 250.000000,\n"
	            "			\"vOffset\": 250.000000,\n"
	            "			\"alignment\": \"center\"\n"
	            "		},\n"
	            "		\"text\": {\n"
	            "			\"data\": \"Click Here\",\n"
	            "			\"size\": 36.000000,\n"
	            "			\"style\": \"bold\",\n"
	            "			\"name\": \"text1\",\n"
	            "			\"hOffset\": 250.000000,\n"
	            "			\"vOffset\": 100.000000,\n"
	            "			\"alignment\": \"center\",\n"
	            "			\"onMouseUp\": \"sun1.opacity = (sun1.opacity / 100) * 90;\"\n"
	            "		}\n"
	            "	}\n"
	            "}\n";
	check.Set(reference,
	          -1,
	          reference);
	l_list.PushBack(check);
	// ------------------------------------------------------


//////////////////////////////////////////////////////////////////////////
/*
	reference = "{\n"
	            "\"web-app\": {\n"
	            "	\"servlet\": [\n"
	            "		{\n"
	            "			\"servlet-name\": \"cofaxCDS\",\n"
	            "			\"servlet-class\": \"org.cofax.cds.CDSServlet\",\n"
	            "			\"init-param\": {\n"
	            "				\"configGlossary:installationAt\": \"Philadelphia, PA\",\n"
	            "				\"configGlossary:adminEmail\": \"ksm@pobox.com\",\n"
	            "				\"configGlossary:poweredBy\": \"Cofax\",\n"
	            "				\"configGlossary:poweredByIcon\": \"/images/cofax.gif\",\n"
	            "				\"configGlossary:staticPath\": \"/content/static\",\n"
	            "				\"templateProcessorClass\": \"org.cofax.WysiwygTemplate\",\n"
	            "				\"templateLoaderClass\": \"org.cofax.FilesTemplateLoader\",\n"
	            "				\"templatePath\": \"templates\",\n"
	            "				\"templateOverridePath\": \"\",\n"
	            "				\"defaultListTemplate\": \"listTemplate.htm\",\n"
	            "				\"defaultFileTemplate\": \"articleTemplate.htm\",\n"
	            "				\"useJSP\": false,\n"
	            "				\"jspListTemplate\": \"listTemplate.jsp\",\n"
	            "				\"jspFileTemplate\": \"articleTemplate.jsp\",\n"
	            "				\"cachePackageTagsTrack\": 200,\n"
	            "				\"cachePackageTagsStore\": 200,\n"
	            "				\"cachePackageTagsRefresh\": 60,\n"
	            "				\"cacheTemplatesTrack\": 100,\n"
	            "				\"cacheTemplatesStore\": 50,\n"
	            "				\"cacheTemplatesRefresh\": 15,\n"
	            "				\"cachePagesTrack\": 200,\n"
	            "				\"cachePagesStore\": 100,\n"
	            "				\"cachePagesRefresh\": 10,\n"
	            "				\"cachePagesDirtyRead\": 10,\n"
	            "				\"searchEngineListTemplate\": \"forSearchEnginesList.htm\",\n"
	            "				\"searchEngineFileTemplate\": \"forSearchEngines.htm\",\n"
	            "				\"searchEngineRobotsDb\": \"WEB-INF/robots.db\",\n"
	            "				\"useDataStore\": true,\n"
	            "				\"dataStoreClass\": \"org.cofax.SqlDataStore\",\n"
	            "				\"redirectionClass\": \"org.cofax.SqlRedirection\",\n"
	            "				\"dataStoreName\": \"cofax\",\n"
	            "				\"dataStoreDriver\": \"com.microsoft.jdbc.sqlserver.SQLServerDriver\",\n"
	            "				\"dataStoreUrl\": \"jdbc:microsoft:sqlserver://LOCALHOST:1433;DatabaseName=goon\",\n"
	            "				\"dataStoreUser\": \"sa\",\n"
	            "				\"dataStorePassword\": \"dataStoreTestQuery\",\n"
	            "				\"dataStoreTestQuery\": \"SET NOCOUNT ON;select test='test';\",\n"
	            "				\"dataStoreLogFile\": \"/usr/local/tomcat/logs/datastore.log\",\n"
	            "				\"dataStoreInitConns\": 10,\n"
	            "				\"dataStoreMaxConns\": 100,\n"
	            "				\"dataStoreConnUsageLimit\": 100,\n"
	            "				\"dataStoreLogLevel\": \"debug\",\n"
	            "				\"maxUrlLength\": 500\n"
	            "			}\n"
	            "		},\n"
	            "		{\n"
	            "			\"servlet-name\": \"cofaxEmail\",\n"
	            "			\"servlet-class\": \"org.cofax.cds.EmailServlet\",\n"
	            "			\"init-param\": {\n"
	            "			\"mailHost\": \"mail1\",\n"
	            "			\"mailHostOverride\": \"mail2\"}},\n"
	            "		{\n"
	            "			\"servlet-name\": \"cofaxAdmin\",\n"
	            "			\"servlet-class\": \"org.cofax.cds.AdminServlet\"},\n"
	            " \n"
	            "		{\n"
	            "			\"servlet-name\": \"fileServlet\",\n"
	            "			\"servlet-class\": \"org.cofax.cds.FileServlet\"},\n"
	            "		{\n"
	            "			\"servlet-name\": \"cofaxTools\",\n"
	            "			\"servlet-class\": \"org.cofax.cms.CofaxToolsServlet\",\n"
	            "			\"init-param\": {\n"
	            "				\"templatePath\": \"toolstemplates/\",\n"
	            "				\"log\": 1,\n"
	            "				\"logLocation\": \"/usr/local/tomcat/logs/CofaxTools.log\",\n"
	            "				\"logMaxSize\": \"\",\n"
	            "				\"dataLog\": 1,\n"
	            "				\"dataLogLocation\": \"/usr/local/tomcat/logs/dataLog.log\",\n"
	            "				\"dataLogMaxSize\": \"\",\n"
	            "				\"removePageCache\": \"/content/admin/remove?cache=pages&id=\",\n"
	            "				\"removeTemplateCache\": \"/content/admin/remove?cache=templates&id=\",\n"
	            "				\"fileTransferFolder\": \"/usr/local/tomcat/webapps/content/fileTransferFolder\",\n"
	            "				\"lookInContext\": 1,\n"
	            "				\"adminGroupID\": 4,\n"
	            "				\"betaServer\": true}}],\n"
	            "	\"servlet-mapping\": {\n"
	            "		\"cofaxCDS\": \"/\",\n"
	            "		\"cofaxEmail\": \"/cofaxutil/aemail/*\",\n"
	            "		\"cofaxAdmin\": \"/admin/*\",\n"
	            "		\"fileServlet\": \"/static/*\",\n"
	            "		\"cofaxTools\": \"/tools/*\"},\n"
	            " \n"
	            "	\"taglib\": {\n"
	            "		\"taglib-uri\": \"cofax.tld\",\n"
	            "		\"taglib-location\": \"/WEB-INF/tlds/cofax.tld\"}}}\n"
	            "		\n"
	            "";
	check.Set(reference,
	          -1,
	          reference);
	l_list.PushBack(check);
	// ------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
*/

	reference = "{\n"
	            "\"menu\": {\n"
	            "    \"header\": \"SVG Viewer\",\n"
	            "    \"items\": [\n"
	            "        {\"id\": \"Open\"},\n"
	            "        {\"id\": \"OpenNew\", \"label\": \"Open New\"},\n"
	            "        null,\n"
	            "        {\"id\": \"ZoomIn\", \"label\": \"Zoom In\"},\n"
	            "        {\"id\": \"ZoomOut\", \"label\": \"Zoom Out\"},\n"
	            "        {\"id\": \"OriginalView\", \"label\": \"Original View\"},\n"
	            "        null,\n"
	            "        {\"id\": \"Quality\"},\n"
	            "        {\"id\": \"Pause\"},\n"
	            "        {\"id\": \"Mute\"},\n"
	            "        null,\n"
	            "        {\"id\": \"Find\", \"label\": \"Find...\"},\n"
	            "        {\"id\": \"FindAgain\", \"label\": \"Find Again\"},\n"
	            "        {\"id\": \"Copy\"},\n"
	            "        {\"id\": \"CopyAgain\", \"label\": \"Copy Again\"},\n"
	            "        {\"id\": \"CopySVG\", \"label\": \"Copy SVG\"},\n"
	            "        {\"id\": \"ViewSVG\", \"label\": \"View SVG\"},\n"
	            "        {\"id\": \"ViewSource\", \"label\": \"View Source\"},\n"
	            "        {\"id\": \"SaveAs\", \"label\": \"Save As\"},\n"
	            "        null,\n"
	            "        {\"id\": \"Help\"},\n"
	            "        {\"id\": \"About\", \"label\": \"About Adobe CVG Viewer...\"}\n"
	            "    ]\n"
	            "}}\n";
	check.Set(reference,
	          -1,
	          reference);
	l_list.PushBack(check);
	// ------------------------------------------------------
//////////////////////////////////////////////////////////////////////////


}

int main(int argc, const char *argv[])
{
	GeneralDebugSetLevel(etk::LOG_LEVEL_VERBOSE);
	Init();
	int32_t countError = 0;
	int32_t countSeparator = 0;
	int32_t sectionID = 0;
	for (int32_t iii=0 ; iii<l_list.Size() ; iii++) {
		int32_t jjj= iii-countSeparator+1;
		if (l_list[iii].m_errorPos==-2) {
			countSeparator++;
			sectionID = 0;
			JSON_INFO("-------------------------------------------------------------");
			JSON_INFO("-- " << l_list[iii].m_ref);
			JSON_INFO("-------------------------------------------------------------");
			continue;
		}
		sectionID++;
		ejson::Document doc;
		etk::UString out("");
		//JSON_DEBUG("parse : \n" << l_list[iii].m_input);
		if (false==doc.Parse(l_list[iii].m_input)) {
			if (l_list[iii].m_errorPos==1) {
				JSON_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } Parsing in error (correct result)");
			} else {
				JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Parsing might be OK");
				JSON_ERROR("parse : \n" << l_list[iii].m_input);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos==1) {
			JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Parsing might be in error ...");
			JSON_ERROR("parse : \n" << l_list[iii].m_input);
			doc.Display();
			countError++;
			continue;
		}
		if (false == doc.Generate(out)) {
			if (l_list[iii].m_errorPos==2) {
				JSON_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } generate in error (correct result)");
			} else {
				JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Generate output might be OK");
				JSON_ERROR("generate : \n" << out);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos==2) {
			JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Generating might be in error ...");
			countError++;
			continue;
		}
		if (l_list[iii].m_ref != out) {
			if (l_list[iii].m_errorPos==3) {
				JSON_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } Result in error (normal case)");
			} else {
				JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } different output");
				JSON_ERROR("generate : \n" << out);
				JSON_ERROR("reference : \n" << l_list[iii].m_ref);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos==3) {
			JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR} checking result might be in error...");
			JSON_ERROR("generate : \n" << out);
			JSON_ERROR("reference : \n" << l_list[iii].m_ref);
			countError++;
			continue;
		}
		JSON_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  }");
	}
	if (countError>0) {
		JSON_ERROR("[TEST] produce " << countError << " error on " << l_list.Size()-countSeparator << " test");
	} else {
		JSON_INFO("[TEST] produce " << countError << " error on " << l_list.Size()-countSeparator << " test");
	}
	return 0;
}

