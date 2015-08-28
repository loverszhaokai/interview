#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qh_string.h"

static const char *short_str = "This is a short string";
static const char *long_str = "This is a long string";

static bool is_equal(const qh::string &lhs, const qh::string &rhs)
{
	if (lhs.size() != rhs.size())
		return false;

	if (lhs.size() == 0) {
		if (lhs.data() == NULL && rhs.data() == NULL)
			return true;
		return false;
	}

	for (int i = 0; i < lhs.size(); i++)
	{
		if (lhs[i] != rhs[i])
			return false;
	}
	return true;
}

static void test_constructor()
{
	// Default constructor
	{
		qh::string qstr;

		assert(qstr.data() == NULL);
		assert(qstr.size() == 0);
	}

	// 1.1 Constructor
	{
		qh::string qstr(short_str);

		assert(qstr.data() != NULL);
		assert(strcmp(qstr.data(), short_str) == 0);
		assert(qstr.size() == strlen(short_str));
	}

	// 1.2 Constructor, NULL
	{
		qh::string qstr(NULL);

		assert(qstr.data() == NULL);
		assert(qstr.size() == 0);
	}

	// 2.1 Constructor
	{
		qh::string qstr(short_str, strlen(short_str));

		assert(qstr.data() != NULL);
		assert(strcmp(qstr.data(), short_str) == 0);
		assert(qstr.size() == strlen(short_str));
	}

	// 2.2 Constructor, less than the real length
	{
		qh::string qstr(short_str, 3);

		assert(qstr.data() != NULL);
		assert(strncmp(qstr.data(), short_str, 3) == 0);
		assert(qstr.size() == 3);
	}

	// 2.3 Constructor, greater than the real length
	{
		qh::string qstr(short_str, 30);

		assert(qstr.data() != NULL);
		assert(strcmp(qstr.data(), short_str) == 0);
		assert(qstr.size() == strlen(short_str));
	}

	// 2.4 Constructor, NULL
	{
		qh::string qstr(NULL, 16);

		assert(qstr.data() == NULL);
		assert(qstr.size() == 0);
	}

	// 3.1 Copy Constructor
	{
		qh::string qstr1;
		qh::string qstr2(qstr1);
		assert(is_equal(qstr1, qstr2));
	}

	// 3.2 Copy Constructor
	{
		qh::string qstr1(short_str);
		qh::string qstr2(qstr1);
		assert(is_equal(qstr1, qstr2));
	}

	// 3.3 Copy Constructor
	{
		qh::string qstr1(short_str);
		qh::string qstr2;
		assert(!is_equal(qstr1, qstr2));
	}

	// 4.1 Assign Constructor
	{
		qh::string qstr1;
		qh::string qstr2 = qstr1;
		assert(is_equal(qstr1, qstr2));
	}

	// 4.2 Assign Constructor
	{
		qh::string qstr1(short_str);
		qh::string qstr2 = qstr1;
		assert(is_equal(qstr1, qstr2));
	}
}

static void test_size()
{
	qh::string qstr1;
	qh::string qstr2(short_str);
	qh::string qstr3(long_str);

	assert(qstr1.size() == 0);
	assert(qstr2.size() == strlen(short_str));
	assert(qstr3.size() == strlen(long_str));

	// Swap qstr2 and qstr3
	qstr1 = qstr2;
	qstr2 = qstr3;
	qstr3 = qstr1;

	assert(qstr2.size() == strlen(long_str));
	assert(qstr3.size() == strlen(short_str));
}

static void test_data_and_c_str()
{
	qh::string qstr1(short_str);
	qh::string qstr2(long_str);

	assert(strcmp(qstr1.data(), qstr1.c_str()) == 0);
	assert(strcmp(qstr2.data(), qstr2.c_str()) == 0);

	assert(strcmp(qstr1.data(), short_str) == 0);
	assert(strcmp(qstr2.data(), long_str) == 0);

	assert(strcmp(qstr1.c_str(), short_str) == 0);
	assert(strcmp(qstr2.c_str(), long_str) == 0);
}

static void test_index()
{
	qh::string qstr(short_str);
	assert(strcmp(qstr.data(), short_str) == 0);

	char *astr = strdup(short_str);
	for (int i = 0; i < qstr.size(); i++)
	{
		astr[i] = 'A';
		qstr[i] = 'A';
	}

	assert(strcmp(qstr.data(), astr) == 0);
	free(astr);

	for (int i = 0; i < qstr.size(); i++)
	{
		qstr[i] = short_str[i];
	}
	assert(strcmp(qstr.data(), short_str) == 0);
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。

	test_constructor();
	test_size();
	test_data_and_c_str();
	test_index();

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

