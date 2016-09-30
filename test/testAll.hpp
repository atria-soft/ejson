/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include "testCommon.hpp"
#include <gtest/gtest.h>

TEST(TestAll, testBaseObject) {
	std::string base = "{\n"
	                   "	\"menu\": {\n"
	                   "		\"id\": \"file\",\n"
	                   "		\"value\": \"File\",\n"
	                   "		\"popup\": {\n"
	                   "			\"menuitem\": { \"value\": \"Close\", \"onclick\": \"CloseDoc()\" }\n"
	                   "		}\n"
	                   "	}\n"
	                   "}\n";
	localTest(base, base, -1);
}

static std::string refOutputAll(   "{\n"
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
                                   "}\n");
TEST(TestAll, testList) {
	localTest(refOutputAll, refOutputAll, -1);
}

TEST(TestAll, testIndentedList) {
	localTest(refOutputAll,
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
	           "}\n",
	          -1);
}

TEST(TestAll, testIndentedListWithNoBasicObject) {
	localTest(refOutputAll,
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
	            "}\n",
	           -1);
}




TEST(TestAll, testGeneric1) {
	std::string base = "{\n"
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
	localTest(base, base, -1);
}

TEST(TestAll, testGeneric2) {
	std::string base = "{\n"
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
	localTest(base, base, -1);
}
TEST(TestAll, testGeneric3) {
	std::string base = "{\n"
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
	localTest(base, base, -1);
}


TEST(TestAll, testGeneric4) {
	std::string base = "{\n"
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
	localTest(base, base, -1);
}


TEST(TestAll, testGeneric5) {
	std::string base = "{\n"
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
	localTest(base, base, -1);
}


