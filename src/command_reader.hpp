#ifndef IRC_SRC_IRC_COMMAND_READER_HPP
#define IRC_SRC_IRC_COMMAND_READER_HPP

#include "command.hpp"
#include "command_parser.hpp"
#include "tcp_reader.hpp"

class CommandReader {
 private:
  int fd_;
  CommandParser command_parser_;
  TcpReader tcp_reader_;

 public:
  explicit CommandReader(int);
  std::shared_ptr<Command> Read();

 private:
  std::shared_ptr<Command> CreateCommand(std::string &, std::string &,
                                         std::vector<std::string> &);
};

#endif  // IRC_SRC_IRC_COMMAND_READER_HPP