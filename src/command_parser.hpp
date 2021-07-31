#ifndef IRC_SRC_PARSER_HPP
#define IRC_SRC_PARSER_HPP

#include <string>
#include <vector>

// Todo : implement parser

class CommandParser {
 public:
  static std::tuple<std::string, std::string, std::vector<std::string>> Parse(
      const std::string&);
};

#endif  // IRC_SRC_PARSER_HPP