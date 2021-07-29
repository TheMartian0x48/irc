#include "irc_exception.hpp"

IrcException::IrcException(std::string error) {
  error_ = error;
}

const char* IrcException::what() const noexcept {
  return error_.c_str();
}