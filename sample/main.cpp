/** @file
 * @author Edouard DUPIN
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <test-debug/debug.h>
#include <etk/etk.h>
#include "read.h"
#include "write.h"

int main(int argc, const char *argv[]) {
	// the only one init for etk:
	etk::init(argc, argv);
	for (int32_t iii=0; iii<argc ; ++iii) {
		std::string data = argv[iii];
		if (    data == "-h"
		     || data == "--help") {
			TEST_PRINT("Help : ");
			TEST_PRINT("    ./xxx [options]");
			TEST_PRINT("        -h/--help: this help");
			exit(0);
		}
	}
	TEST_INFO("read [START] ***************************");
	appl::read();
	TEST_INFO("read [STOP ] ***************************");
	TEST_INFO("write [START] ***************************");
	appl::write();
	TEST_INFO("write [STOP ] ***************************");
	return 0;
}
