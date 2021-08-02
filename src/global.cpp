#include "global.hpp"

Server irc_server = Server(std::string("v1.0"), std::string("what password?"),
                           std::string("what info?"));

ThreadSafeMap active_users =
    ThreadSafeMap();