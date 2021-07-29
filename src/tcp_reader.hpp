#ifndef IRC_SRC_TCP_READER_HPP_
#define IRC_SRC_TCP_READER_HPP_

#include <string>

class TcpReader {
 private:
  char buffer_[520];
  std::string unread_message_;
 public:
  TcpReader();
  std::string Read(int);
};
#endif  // IRC_SRC_TCP_READER_HPP_