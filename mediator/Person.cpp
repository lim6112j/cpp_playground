#include "Person.hpp"
Person::Person(const string &name) {}
void Person::say(const string &message) const {}
void Person::pm(const string &who, const string &message) const {}
void Person::receive(const string &origin, const string &message) const {}
bool Person::operator==(const Person &rhs) const { return name == rhs.name; }
bool Person::operator!=(const Person &rhs) const { return name != rhs.name; }
