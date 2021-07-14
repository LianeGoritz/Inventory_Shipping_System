#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>

class invalid_argument_error: public std::runtime_error {
 public:
  invalid_argument_error(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

#endif // EXCEPTIONS_H
