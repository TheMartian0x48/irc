#include "command.hpp"

#include <cctype>
#include <fstream>

#include "error.hpp"
#include "global.hpp"
#include "reply.hpp"

extern ThreadSafeMap active_users;

bool IsSpecialCharacter(char ch) {
  return (ch >= 0x5B && ch <= 0x60) || (ch >= 0x7B && ch <= 0x7D);
}

bool IsValidNick(const std::string &nick) {
  int n = nick.size();
  bool valid = (n > 0 && n <= 9) && (IsSpecialCharacter(nick[0]) ||
                                     islower(nick[0]) || isupper(nick[0]));
  for (const char &ch : nick) {
    valid = valid && (islower(ch) || isupper(ch) || isdigit(ch) ||
                      IsSpecialCharacter(ch));
    if (valid == false) return false;
  }
  return true;
}

Command::Command(std::string &&prefix, std::string &&command_name,
                 std::vector<std::string> &&parameter) {
  prefix_ = prefix;
  command_name_ = command_name;
  parameter_ = parameter;
}

Command::Command(std::string &&command_name,
                 std::vector<std::string> &&parameter) {
  parameter_ = parameter;
  command_name_ = command_name;
}

std::string Command::CommandName() { return command_name_; }
/**************************************************************************
            NICK Command
**************************************************************************/

std::pair<bool, std::string> Nick::Validate() {
  if (parameter_.empty()) {
    // no nick given, return NONICKNAMEGIVEN error
    return {false, IrcError::NoNickNameGiven()};
  } else if (IsValidNick(parameter_.front()) == false) {
    // invalid nickname, return ERRONEUSNICKNAME error
    return {false, IrcError::ErroneusNickName(parameter_.front())};
  } else if (active_users.find(parameter_.front()) != nullptr) {
    // check if nick is present or not
    // depend on global shared memory active_users
    // return NICKNAMEINUSE
    return {false, IrcError::NickNameInUse(parameter_.front())};
  }
  return {true, {}};
}

void Nick::SendReply(std::shared_ptr<Client> client) {
  auto is_valid = Validate();
  if (is_valid.first == false) {
    std::string error_message =
        ":" + irc_server.GetHost() + " " + is_valid.second;
    client->Send(error_message);
    return;
  }
  client->SetNick(parameter_.front());
}

bool Nick::SetNickName(std::shared_ptr<Client> client) {
  if (Validate().first == false) return false;
  client->SetNick(parameter_.front());
  return true;
}

/**************************************************************************
            USER Command
**************************************************************************/

std::pair<bool, std::string> User::Validate() {
  if (parameter_.size() != 4) {
    return {false, IrcError::NeedMoreParams(std::string("USER"))};
  }
  // TODO : check for error ALREADYREGISTRED
  return {true, {}};
}

void User::SendReply(std::shared_ptr<Client> client) {
  auto is_valid = Validate();
  if (is_valid.first == false) {
    std::string error_message =
        ":" + irc_server.GetHost() + " " + is_valid.second;
    client->Send(error_message);
  }
}

bool User::SetUserAndFullName(std::shared_ptr<Client> client) {
  if (Validate().first == false) return false;
  client->SetUser(parameter_.front());
  client->SetFullName(parameter_.back());
  return true;
}
/**************************************************************************
            QUIT Command
**************************************************************************/

std::pair<bool, std::string> Quit::Validate() {
  // always send error message
  return {false, IrcError::Quit()};
}

void Quit::SendReply(std::shared_ptr<Client> client) {
  auto is_valid = Validate();
  std::string tmp = ":" + irc_server.GetHost() + " " + is_valid.second;
  client->Send(tmp);
}

/**************************************************************************
            PRIVMSG Command
**************************************************************************/

std::pair<bool, std::string> Privmsg::Validate() {
  if (parameter_.empty()) {
    return {false, IrcError::NoRecipient(std::string("PRIVMSG"))};
  } else if (active_users.find(parameter_.front()) == nullptr) {
    return {false, IrcError::NoSuchNick(parameter_.front())};
  } else if (parameter_.size() < 2) {
    return {false, IrcError::NoTextToSend()};
  }
  return {true, {}};
}

void Privmsg::SendReply(std::shared_ptr<Client> client) {
  auto is_valid = Validate();
  if (is_valid.first == false) {
    std::string error_message = ":" + irc_server.GetHost() + is_valid.second;
    client->Send(error_message);
    return;
  }
  auto receiver = active_users.find(parameter_.front());
  if (receiver == nullptr) {
    std::string tmp = ":" + irc_server.GetHost() + " " +
                      IrcError::NoRecipient(std::string("PRIVMSG"));
    client->Send(tmp);
    return;
  }
  std::string msg =
      ":" + client->GetFullClientId() + " PRIVMSG :" + parameter_.back();
  receiver->Send(msg);
}

/**************************************************************************
            NOTICE Command
**************************************************************************/

std::pair<bool, std::string> Notice::Validate() {
  if (parameter_.empty()) {
    return {false, {}};
  } else if (active_users.find(parameter_.front()) == nullptr) {
    return {false, {}};
  } else if (parameter_.size() < 2) {
    return {false, {}};
  }
  return {true, {}};
}

void Notice::SendReply(std::shared_ptr<Client> client) {
  auto is_valid = Validate();
  if (is_valid.first == false) {
    return;
  }
  auto receiver = active_users.find(parameter_.front());
  if (receiver == nullptr) {
    return;
  }
  std::string msg =
      ":" + client->GetFullClientId() + " NOTICE :" + parameter_.back();
  receiver->Send(msg);
}

/**************************************************************************
            PING Command
**************************************************************************/

std::pair<bool, std::string> Ping::Validate() { return {true, {}}; }

void Ping::SendReply(std::shared_ptr<Client> client) {
  auto server_host = irc_server.GetHost();
  std::string reply_msg = ":" + server_host + " PONG " + server_host + "\r\n";
  client->Send(reply_msg);
}

/**************************************************************************
            PONG Command
**************************************************************************/

std::pair<bool, std::string> Pong::Validate() { return {true, {}}; }

void Pong::SendReply(std::shared_ptr<Client> client) {}

/**************************************************************************
            MOTD Command
**************************************************************************/

std::pair<bool, std::string> Motd::Validate() { return {true, {}}; }

void Motd::SendReply(std::shared_ptr<Client> client) {
  const std::string motd_fie = "motd.txt";
  // don't send MOTD message for now
  std::string tmp = ":" + irc_server.GetHost() + " " + IrcError::NoMotd();
  client->Send(tmp);
}

/**************************************************************************
            LUSERS Command
**************************************************************************/

std::pair<bool, std::string> Lusers::Validate() { return {true, {}}; }

void Lusers::SendReply(std::shared_ptr<Client> client) {
  std::string server_host = irc_server.GetHost();
  std::string user_count = std::to_string(active_users.size());
  std::string service_count = "0", server_count = "1";
  std::string oprator_online = "0", unknown_count = "0";
  std::string channel_count = "0";

  auto reply_msg = ":" + server_host + " " +
                   LUserClient(user_count, service_count, server_count);
  client->Send(reply_msg);

  reply_msg = ":" + server_host + " " + LUserOp(oprator_online);
  client->Send(reply_msg);

  reply_msg = ":" + server_host + " " + LUserUnknown(unknown_count);
  client->Send(reply_msg);

  reply_msg = ":" + server_host + " " + LUserChannels(channel_count);
  client->Send(reply_msg);

  reply_msg = ":" + server_host + " " + LUserMe(user_count, server_count);
  client->Send(reply_msg);
}

/**************************************************************************
            WHOIS Command
**************************************************************************/

std::pair<bool, std::string> Whois::Validate() {
  if (parameter_.empty()) {
    return {false, {}};
  } else if (IsValidNick(parameter_.front()) == false) {
    return {false, {IrcError::NoSuchNick(parameter_.front())}};
  }
  return {true, {}};
}

void Whois::SendReply(std::shared_ptr<Client> client) {
  auto is_valid = Validate();
  if (is_valid.first) {
    if (is_valid.second.empty() == false) {
      std::string error_msg =
          ":" + irc_server.GetHost() + " " + is_valid.second;
      client->Send(error_msg);
    }
    return;
  }
  if (parameter_.size() != 1) return;
  auto queried_user = active_users.find(parameter_.front());

  if (queried_user == nullptr) {
    std::string error_msg = ":" + irc_server.GetHost() + " " +
                            IrcError::NoSuchNick(parameter_.front());
    client->Send(error_msg);
    return;
  }

  auto server_host = irc_server.GetHost();
  std::string reply_msg =
      ":" + server_host + " " +
      WhoIsUser(queried_user->GetNick(), queried_user->GetUser(),
                queried_user->GetHost(), queried_user->GetFullName());
  client->Send(reply_msg);

  reply_msg =
      ":" + server_host + " " +
      WhoIsServer(queried_user->GetNick(), server_host, irc_server.GetInfo());
  client->Send(reply_msg);

  reply_msg = ":" + server_host + " " + EndOfWhoIs(parameter_.front());
  client->Send(reply_msg);
}

/**************************************************************************
            UNKNOWN Command (only send no such commend exit error)
**************************************************************************/

std::pair<bool, std::string> Unknown::Validate() { return {false, {}}; }

void Unknown::SendReply(std::shared_ptr<Client> client) {
  std::string error_msg =
      ":" + irc_server.GetHost() + " " + IrcError::UnknownCommand(prefix_);
}
