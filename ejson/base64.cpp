/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#include <etk/types.h>
#include <ejson/base64.h>

static const std::string base64Elements = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const std::vector<uint8_t>& getReverseTable() {
	static std::vector<uint8_t> table;
	if (table.size() == 0) {
		table.resize(256,0);
		for (size_t iii=0; iii<base64Elements.size(); ++iii) {
			table[size_t(base64Elements[iii])] = iii;
		}
	}
	return table;
}



static bool isBase64(char _ccc) {
  return    isalnum(_ccc)
         || _ccc == '+'
         || _ccc == '/';
}

std::string ejson::base64::encode(const uint8_t* _data, int32_t _len) {
	std::string out;
	int32_t iii = 0;
	int32_t jjj = 0;
	uint8_t bit3[3];
	uint8_t bit4[4];
	// Pack 3 bytes in 4 bytes
	while (_len--) {
		bit3[iii++] = *(_data++);
		if (iii == 3) {
			iii = 0;
			bit4[0] = (bit3[0] & 0xfc) >> 2;
			bit4[1] = ((bit3[0] & 0x03) << 4) + ((bit3[1] & 0xf0) >> 4);
			bit4[2] = ((bit3[1] & 0x0f) << 2) + ((bit3[2] & 0xc0) >> 6);
			bit4[3] = bit3[2] & 0x3f;
			for(int32_t jjj=0; jjj<4 ; ++jjj) {
				out += base64Elements[bit4[jjj]];
			}
		}
	}
	// Residual packing ...
	if (iii != 0) {
		for(int32_t jjj=iii; jjj<3; ++jjj) {
			bit3[jjj] = 0;
		}
		bit4[0] = (bit3[0] & 0xfc) >> 2;
		bit4[1] = ((bit3[0] & 0x03) << 4) + ((bit3[1] & 0xf0) >> 4);
		bit4[2] = ((bit3[1] & 0x0f) << 2) + ((bit3[2] & 0xc0) >> 6);
		bit4[3] = bit3[2] & 0x3f;
		for (int32_t jjj=0; jjj<iii+1; ++jjj) {
			out += base64Elements[bit4[jjj]];
		}
		while (iii++ < 3) {
			out += '=';
		}
	}
	return out;
}

std::vector<uint8_t> ejson::base64::decode(const std::string& _data) {
	int32_t len = _data.size();
	int32_t iii = 0;
	int32_t id = 0;
	uint8_t bit4[4];
	uint8_t bit3[3];
	std::vector<uint8_t> out;
	const std::vector<uint8_t>& base64ElementsReverse = getReverseTable();
	while (    len--
	        && _data[id] != '='
	        && isBase64(_data[id]) == true) {
		bit4[iii++] = _data[id];
		id++;
		if (iii == 4) {
			iii = 0;
			for (int32_t jjj=0; jjj<4; ++jjj) {
				bit4[jjj] = base64ElementsReverse[bit4[jjj]];
			}
			bit3[0] = (bit4[0] << 2) + ((bit4[1] & 0x30) >> 4);
			bit3[1] = ((bit4[1] & 0xf) << 4) + ((bit4[2] & 0x3c) >> 2);
			bit3[2] = ((bit4[2] & 0x3) << 6) + bit4[3];
			for (int32_t jjj=0; jjj<3; ++jjj) {
				out.push_back(bit3[jjj]);
			}
		}
	}
	if (iii != 0) {
		for (int32_t jjj=iii; jjj<4; ++jjj) {
			bit4[jjj] = 0;
		}
		for (int32_t jjj = 0; jjj <4; ++jjj) {
			bit4[jjj] = base64ElementsReverse[bit4[jjj]];
		}
		bit3[0] = (bit4[0] << 2) + ((bit4[1] & 0x30) >> 4);
		bit3[1] = ((bit4[1] & 0xf) << 4) + ((bit4[2] & 0x3c) >> 2);
		bit3[2] = ((bit4[2] & 0x3) << 6) + bit4[3];
		for (int32_t jjj=0; jjj<iii-1; ++jjj) {
			out.push_back(bit3[jjj]);
		}
	}
	return out;
}