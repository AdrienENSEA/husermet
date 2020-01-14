#include "ServiceException.h"
using namespace std;
using namespace server;

ServiceException::ServiceException (HttpStatus status, string msg) 
    : httpStatus(status),msg(msg) {    
}

HttpStatus const ServiceException::status ()  {
    return httpStatus;
}

const char* const ServiceException::what () noexcept(false) {
    return msg.c_str();
}
