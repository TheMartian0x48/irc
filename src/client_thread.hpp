#ifndef IRC_SRC_CLIENT_THREAD_HPP_
#define IRC_SRC_CLIENT_THREAD_HPP_

#include <sys/select.h>
#include <sys/time.h>

#include <memory>

#include "client.hpp"
#include "command.hpp"
#include "command_reader.hpp"

class ClientThread {
 private:
  int fd_;
  std::shared_ptr<Client> user_;
  std::shared_ptr<CommandReader> command_reader_;

 public:
  ClientThread(int, std::string&);
  ~ClientThread();
  void operator()();

 private:
  void Register();
  void ListenForCommand();
  void DestroyUser();
  bool IsReadyToReadCommand();
  bool IsClientActive();
  void SendWelcomeMessage();
  std::pair<bool, bool> HasReadNickAndUserCommand(bool, bool);
};

#endif  // IRC_SRC_CLIENT_THREAD_HPP_