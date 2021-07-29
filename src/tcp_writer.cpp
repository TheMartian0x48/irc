#include "tcp_writer.hpp"

#include <unistd.h>

#include "irc_exception.hpp"

void TcpWriter::Write(int file_descriptor, std::string message) {
  const char *ptr = message.data();
  int left = message.size();
  int written = 0, offset = 0;
  while (left > 0) {
    written = write(file_descriptor, ptr + offset, left);
    if (written < 0 && errno == EINTR) { // retry
      written = 0;
    } else if (written < 0) {
      throw IrcException(
          "Some error occured while writting to file descriptor " +
          std::to_string(file_descriptor));
    }
    offset += written;
    left -= written;
  }
}
