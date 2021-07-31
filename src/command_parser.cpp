#include "command_parser.hpp"

#include <tuple>

std::tuple<std::string, std::string, std::vector<std::string>>
CommandParser::Parse(const std::string& message) {
  std::string prefix;
  std::string command;
  std::vector<std::string> parameter;

  int n = message.size(), i = 0;
  if (message[i] == ':') {
    i++;
    while (i < n && isspace(message[i]) == false) {
      prefix += message[i++];
    }
    i++;
  }
  while (i < n && isspace(message[i]) == false) {
    command += message[i++];
  }

  std::string tmp;
  for (++i; i < n; i++) {
    if (isspace(message[i]) == true) {
      if (tmp.empty() == false) {
        parameter.push_back(tmp);
        tmp.clear();
      }
    } else if (message[i] == ':') {
      if (tmp.empty() == false) {
        parameter.push_back(tmp);
        tmp.clear();
      }
      for (++i; i < n; i++) {
        tmp += message[i];
      }
      parameter.push_back(tmp);
      tmp.clear();
    }
  }
  return std::make_tuple(prefix, command, parameter);
}