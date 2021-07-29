#ifndef IRC_SRC_TCP_WRITER_HPP_
#define IRC_SRC_TCP_WRITER_HPP_

#include <string>

class TcpWriter {
 public:
  void Write(int, std::string);
};

#endif  // IRC_SRC_TCP_WRITER_HPP_