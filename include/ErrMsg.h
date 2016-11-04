#ifndef ERRMSG_H
#define ERRMSG_H
#include <string>
#include <sstream>
#include <string.h>
#include <iostream>

class ErrMsg: public std::exception
{
public:
    ErrMsg(const std::string& msg, int err)
    {
	std::stringstream ss;
        ss << msg << " (errno=" << err << ":" << strerror(err) << ") ";
	m_msg = ss.str();
    }

    //! implement std::exception::what()
    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }

private:
    std::string m_msg;
};

#endif

