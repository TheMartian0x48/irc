#ifndef IRC_SRC_REPLY_HPP_
#define IRC_SRC_REPLY_HPP_

#include <string>

/***********************************************************
See RFC 2812 section 5
Every replies implementated here follow the RFC rule
without any modification
***********************************************************/
std::string Welcome(const std::string &nick, const std::string &user,
                    const std::string &host);
std::string YourHost(const std::string &server_name,
                     const std::string &version);
std::string Created(const std::string &date);
std::string MyInfo(const std::string &server_name, const std::string &version,
                   const std::string &user_mode,
                   const std::string &channel_mode);
std::string LUserClient(const std::string &user_count,
                        const std::string &service_count,
                        const std::string &server_count);
std::string LUserOp(const std::string &operator_count);
std::string LUserUnknown(const std::string &unknown_count);
std::string LUserChannels(const std::string &channel_count);
std::string LUserMe(const std::string &client_count,
                    const std::string &server_count);
std::string WhoIsUser(const std::string &nick, const std::string &user,
                      const std::string &host, const std::string &real_name);
std::string WhoIsServer(const std::string &nick, const std::string &server,
                        const std::string &server_info);
std::string EndOfWhoIs(const std::string &nick);

#endif // define IRC_SRC_REPLY_HPP_