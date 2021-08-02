#ifndef IRC_SRC_ERROR_HPP_
#define IRC_SRC_ERROR_HPP_

#include <string>

/*******************************************************
See RFC 2812 section 5.2
Except for Quit() function, implementation follow
RFC with any modification
*******************************************************/

namespace IrcError {
std::string NoSuchNick(const std::string &);
std::string NoSuchServer(const std::string &);
std::string NoRecipient(const std::string &);
std::string NoTextToSend();
std::string UnknownCommand(const std::string &);
std::string NoMotd();
std::string NoNickNameGiven();
std::string ErroneusNickName(const std::string &);
std::string NickNameInUse(const std::string &);
std::string NotRegistered();
std::string NeedMoreParams(const std::string &);
std::string AlreadyRegistred();
// Todo
std::string Quit();
}
#endif  // IRC_SRC_ERROR_HPP_
