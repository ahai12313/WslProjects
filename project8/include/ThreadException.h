#ifndef THREAD_EXCEPTION_H
#define THREAD_EXCEPTION_H

#include <stdexcept>
#include <string>

class ThreadException : public std::exception {
public:
    explicit ThreadException(const std::string &msg) 
        : m_msg("Thread Error: " + msg) {} 

    const char* what() const noexcept override {
        return m_msg.c_str();
    }

private:
    std::string m_msg;    
};

#endif