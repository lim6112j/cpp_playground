#include "Chatroom.hpp"

void Chatroom::broadcast(const string &origin, const string &message) {
  for (auto p : people)
    if (p->name != origin)
      p->receive(origin, message);
}
