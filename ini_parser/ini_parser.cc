#include "ini_parser.h"

#include <iostream>

using std::cout;
using std::endl;

namespace qh
{
INIParser::INIParser()
{
	kvalue.clear();
}

INIParser::~INIParser()
{
	kvalue.clear();
}

bool INIParser::Parse(const char* ini_data, size_t ini_data_len,
	const std::string& line_seperator, const std::string& key_value_seperator)
{
	int index = 0, pre_index = 0;
	std::string key, value;

	if (NULL == ini_data || ini_data_len == 0 ||
		line_seperator == key_value_seperator ||
		key_value_seperator == "")
		return false;

	char cnt_c;
	int ls_index = 0, ls_pos;
	int kvs_index = 0, kvs_pos;
	int key_pos = 0;
	bool find_ls = false, find_kvs = false;
	bool ret = false;

	while (index < ini_data_len) {

		cnt_c = ini_data[index];

		if (!find_kvs)
		if (key_value_seperator[kvs_index] == cnt_c) {
			kvs_index++;
			if (kvs_index == key_value_seperator.size()) {
				find_kvs = true;
				kvs_pos = index - kvs_index + 1;
			}
		} else {
			kvs_index = 0;
		}

		if (!find_ls)
		if (line_seperator.size() != 0 && line_seperator[ls_index] == cnt_c) {
			ls_index++;
			if (ls_index == line_seperator.size()) {
				find_ls = true;
				ls_pos = index - ls_index + 1;
			}
		} else {
			ls_index = 0;
		}

		if (find_ls && key_pos == ls_index) {

			key_pos = index + 1;
			ls_index = 0;
			find_ls = false;
			kvs_index = 0;
			find_kvs = false;

		} else if (find_ls && find_kvs) {

			key = std::string(ini_data + key_pos, kvs_pos - key_pos);
			value = std::string(ini_data + kvs_pos + key_value_seperator.size(),
				ls_pos - key_pos - key_value_seperator.size() - 1);

			kvalue[key] = value;
			ret = true;

			key_pos = index + 1;
			ls_index = 0;
			find_ls = false;
			kvs_index = 0;
			find_kvs = false;

		} else if (find_ls && !find_kvs) {

			key_pos = index + 1;
			ls_index = 0;
			find_ls = false;
			kvs_index = 0;
			find_kvs = false;

		}

		index++;
	}

	if (find_kvs) {
			key = std::string(ini_data + key_pos, kvs_pos - key_pos);
			value = std::string(ini_data + kvs_pos + key_value_seperator.size(),
				ini_data_len - key_pos - key_value_seperator.size() - 1);

			kvalue[key] = value;
			ret = true;
	}

	return ret;
}

const std::string& INIParser::Get(const std::string& key, bool* found)
{
	if (kvalue.find(key) != kvalue.end()) {
		if (found)
			*found = true;
		return kvalue[key];
	}

	if (found)
		*found = false;

	static std::string str = "";
	return str;
}

}
