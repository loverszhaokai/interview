#include "qh_string.h"

#include <string.h>

namespace qh
{
    // TODO 将在这里写实现代码

    string::string()
        : data_(NULL), len_(0)
    {
    }

    string::string( const char* s )
    {
		if (!s) {
			data_ = NULL;
			len_ = 0;
		} else {
			data_ = strdup(s);
			len_ = strlen(data_);
		}
    }

    string::string( const char* s, size_t len )
    {
		if (!s || len == 0) {
			data_ = NULL;
			len_ = 0;
		} else {
			data_ = (char *)malloc((len + 1) * sizeof(char));

			memset(data_, 0, len + 1);
			strncpy(data_, s, len);

			len_ = strlen(data_);
		}
    }

    string::string( const string& rhs )
    {
		if (data_)
			free(data_);

		if (!rhs.data()) {
			data_ = NULL;
			len_ = rhs.size();
		} else {
			data_ = strdup(rhs.data());
			len_ = rhs.size();
		}
    }

    string& string::operator=( const string& rhs )
    {
		if (data_)
			free(data_);

		if (!rhs.data()) {
			data_ = NULL;
			len_ = rhs.size();
		} else {
			data_ = strdup(rhs.data());
			len_ = rhs.size();
		}

        return *this;
    }

    string::~string()
    {
		if (data_) {
			free(data_);
			data_ = NULL;
		}
		len_ = 0;
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        return data_;
    }

    const char* string::c_str() const
    {
        return data_;
    }

    char& string::operator[]( size_t index )
    {
        return data_[index];
    }

    const char& string::operator[]( size_t index ) const
    {
        return data_[index];
    }
}
