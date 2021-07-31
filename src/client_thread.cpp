#include "client_thread.hpp"

#include <unistd.h>

#include <iostream>

#include "error.hpp"
#include "global.hpp"
#include "reply.hpp"

extern ThreadSafeMap<std::string, std::shared_ptr<Client>> active_users;
extern Server irc_server;

ClientThread::ClientThread(int fd, std::string& client_host) {
  fd_ = fd;
  command_reader_ = std::shared_ptr<CommandReader>(new CommandReader(fd));
  user_ = std::shared_ptr<Client>(new Client(client_host, fd));
}

ClientThread::~ClientThread() { close(fd_); }

void ClientThread::operator()() {
  Register();
  ListenForCommand();
}

void ClientThread::ListenForCommand() {
  while (IsReadyToReadCommand()) {
    auto command = command_reader_->Read();
    if (command == nullptr) {
      DestroyUser();
      return;
    } else {
      command->SendReply(user_);
    }
  }
  DestroyUser();
}

bool ClientThread::IsReadyToReadCommand() {
  struct timeval time_out;
  time_out.tv_sec = 5 * 60;  // 5 min
  time_out.tv_usec = 0;
  fd_set readfds;

  while (true) {
    FD_ZERO(&readfds);
    FD_SET(fd_, &readfds);
    int rv = select(fd_ + 1, &readfds, NULL, NULL, &time_out);
    if (rv == -1) {
      return false;
    } else if (rv == 0) {
      if (IsClientActive()) continue;
      return false;
    }
    return FD_ISSET(fd_, &readfds);
  }
}

bool ClientThread::IsClientActive() {
  // std::string ping_message = "!" + irc_server.GetHost() + " PING";
  // if (user_->Send(ping_message) == false) return false;
  return false;
}

void ClientThread::DestroyUser() {
  std::string quit_message = "!" + irc_server.GetHost() + " " + IrcError::Quit();
  user_->Send(quit_message);
  active_users.remove(user_->GetNick());
  while (user_.use_count() > 1) continue;
}

void ClientThread::Register() {
  user_->SetUserMode("ao");
  bool has_read_nick = false, has_read_user = false;
  while (has_read_nick == false || has_read_user == false) {
    auto [tmp1, tmp2] = HasReadNickAndUserCommand(has_read_nick, has_read_user);
    has_read_nick = tmp1;
    has_read_user = tmp2;
  }
  SendWelcomeMessage();
}

std::pair<bool, bool> ClientThread::HasReadNickAndUserCommand(
    bool has_read_nick, bool has_read_user) {
  auto command = command_reader_->Read();
  if (command->CommandName() == "NICK") {
    auto it = std::dynamic_pointer_cast<Nick>(command);
    it->SendReply(user_);
    has_read_nick = it->SetNickName(user_);
  } else if (command->CommandName() == "USER") {
    auto it = std::dynamic_pointer_cast<User>(command);
    it->SendReply(user_);
    has_read_user = it->SetUserAndFullName(user_);
  } else {
    std::string error_message =
        "!" + irc_server.GetHost() + " " + IrcError::NotRegistered();
    user_->Send(error_message);
  }
  return {has_read_nick, has_read_user};
}

void ClientThread::SendWelcomeMessage() {
  auto welcome_message =
      "!" + irc_server.GetHost() + " " +
      Welcome(user_->GetNick(), user_->GetUser(), user_->GetHost());
  auto yourhost_message =
      "!" + irc_server.GetHost() + " " +
      YourHost(irc_server.GetName(), irc_server.GetVersion());
  auto created_message =
      "!" + irc_server.GetHost() + " " + Created(irc_server.GetCreationDate());
  auto myinfo_message =
      "!" + irc_server.GetHost() + " " +
      MyInfo(irc_server.GetName(), irc_server.GetVersion(), "ao", "mtov");

  user_->Send(welcome_message);
  user_->Send(yourhost_message);
  user_->Send(created_message);
  user_->Send(myinfo_message);
}
