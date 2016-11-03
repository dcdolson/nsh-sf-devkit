#ifndef ERRMSG_H
#define ERRMSG_H
#include <string>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

class ErrMsg
{
public:
    ErrMsg(const std::string& msg, int err):
	m_msg(msg),
	m_errno(err)
    {
    }
    ErrMsg operator+(const std::string& rhs) const
    {
        return ErrMsg(m_msg + rhs, m_errno);
    }
    void Dump(FILE* f) const
    {
        fprintf(f, "Fatal error (errno=%d): '%s'\n%s\n", m_errno, m_msg.c_str(), strerror(m_errno));
    }
private:
    const std::string m_msg;
    const int         m_errno;
};

#endif

