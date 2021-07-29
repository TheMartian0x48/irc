#include "tcp_reader.hpp"

#include <unistd.h>

#include "irc_exception.hpp"

TcpReader::TcpReader() { unread_message_ = {}; }

std::string TcpReader::Read(int fd) {
  std::string message = unread_message_;
  unread_message_.clear();
  while (true) {
    int nread = read(fd, buffer_, 512);
    if (nread <= 1) {
      throw IrcException(
          "Some error occured while reading from file descriptor " +
          std::to_string(fd));
    } 
    for (int i = 0; i < nread; i++) {
      if (i + 1 < nread && buffer_[i] == '\r' && buffer_[i + 1] == '\n') {
        for (int j = i + 2; j < nread; j++) {
          unread_message_.push_back(buffer_[j]);
        }
        return message;
      } else {
        message.push_back(buffer_[i]);
      }
    }
  }
  return {};
}
