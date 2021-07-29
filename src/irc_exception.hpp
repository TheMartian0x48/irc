#ifndef IRC_SRC_IRC_EXCEPTION_HPP
#define IRC_SRC_IRC_EXCEPTION_HPP

#include <exception>
#include <string>

class IrcException : public std::exception {
 private:
  std::string error_{};

 public:
  IrcException(std::string);
  const char* what() const noexcept override;
};

#endif  // IRC_SRC_IRC_EXCEPTION_HPP