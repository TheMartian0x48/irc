#include "command_reader.hpp"

CommandReader::CommandReader(int fd) {
  fd_ = fd;
  command_parser_ = CommandParser();
  tcp_reader_ = TcpReader();
}

std::shared_ptr<Command> CommandReader::Read() {
  auto message = tcp_reader_.Read(fd_);
  auto [prefix, command, parameter] = command_parser_.Parse(message);
  return CreateCommand(prefix, command, parameter);
}

std::shared_ptr<Command> CommandReader::CreateCommand(
    std::string &prefix, std::string &command,
    std::vector<std::string> &parameter) {
  if (command == "Nick") {
    return std::shared_ptr<Command>(
        new Nick(std::move(prefix), std::move(parameter)));
  } else if (command == "USER") {
    return std::shared_ptr<Command>(
        new User(std::move(prefix), std::move(parameter)));
  } else if (command == "QUIT") {
    return nullptr;
  } else if (command == "PRIVMSG") {
    return std::shared_ptr<Command>(
        new Privmsg(std::move(prefix), std::move(parameter)));
  } else if (command == "NOTICE") {
    return std::shared_ptr<Command>(
        new Notice(std::move(prefix), std::move(parameter)));
  } else if (command == "PING") {
    return std::shared_ptr<Command>(
        new Ping(std::move(prefix), std::move(parameter)));
  } else if (command == "PONG") {
    return std::shared_ptr<Command>(
        new Pong(std::move(prefix), std::move(parameter)));
  } else if (command == "MOTD") {
    return std::shared_ptr<Command>(
        new Motd(std::move(prefix), std::move(parameter)));
  } else if (command == "LUSERS") {
    return std::shared_ptr<Command>(
        new Lusers(std::move(prefix), std::move(parameter)));
  } else if (command == "WHOIS") {
    return std::shared_ptr<Command>(
        new Whois(std::move(prefix), std::move(parameter)));
  }
  return std::shared_ptr<Command>(
      new Unknown(std::move(command), std::move(parameter)));
}
