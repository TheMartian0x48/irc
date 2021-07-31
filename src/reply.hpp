#ifndef IRC_SRC_REPLY_HPP_
#define IRC_SRC_REPLY_HPP_

#include <string>

/***********************************************************
See RFC 2812 section 5
Every replies implementated here follow the RFC rule
without any modification
***********************************************************/
std::string Welcome(const std::string &nick, const std::string &user,
                    const std::string &host) {
  return {"001 Welcon to the Internet Relay Network " + nick + "!" + user +
          "@" + host + "\r\n"};
}

std::string YourHost(const std::string &server_name,
                     const std::string &version) {
  return {"002 Your host is " + server_name + ", running version " + version +
          "\r\n"};
}

std::string Created(const std::string &date) {
  return {"003 This server was created " + date + "\r\n"};
}

std::string MyInfo(const std::string &server_name, const std::string &version,
                   const std::string &user_mode,
                   const std::string &channel_mode) {
  return {"004 " + server_name + " " + version + " " + user_mode + " " +
          channel_mode + "\r\n"};
}

std::string LUserClient(const std::string &user_count,
                        const std::string &service_count,
                        const std::string &server_count) {
  return {"251 :There are " + user_count + " users and " + service_count +
          " services on " + server_count + " servers\r\n"};
}

std::string LUserOp(const std::string &operator_count) {
  return {"252 " + operator_count + " :operator(s) online\r\n"};
}

std::string LUserUnknown(const std::string &unknown_count) {
  return {"253 " + unknown_count + " :unknown connection(s)\r\n"};
}

std::string LUserChannels(const std::string &channel_count) {
  return {"254 " + channel_count + " :channels formed\r\n"};
}

std::string LUserMe(const std::string &client_count,
                    const std::string &server_count) {
  return {"255 :I have " + client_count + " clients and " + server_count +
          " servers\r\n"};
}

std::string WhoIsUser(const std::string &nick, const std::string &user,
                      const std::string &host, const std::string &real_name) {
  return {"311 " + nick + " " + user + " " + host + " * :" + real_name +
          "\r\n"};
}

std::string WhoIsServer(const std::string &nick, const std::string &server,
                        const std::string &server_info) {
  return {"312 " + nick + " " + server + " :" + server_info + "\r\n"};
}

std::string EndOfWhoIs(const std::string &nick) {
  return {"318 " + nick + " :End of WHOIS list\r\n"};
}

#endif  // IRC_SRC_REPLY_HPP_
