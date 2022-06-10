#include <iostream>
#include <ostream>
#include <vector>

using namespace std;
struct BankAccount {
  int balance{0};
  int overdraft_limit{-500};
  void deposit(int amount) {
    balance += amount;
    cout << "deposited " << amount << ", balance is now " << balance << endl;
  }
  void withdraw(int amount) {
    if (balance - amount >= overdraft_limit)
      balance -= amount;
    cout << "withdraw " << amount << ", balance is now " << balance << endl;
  }
  friend ostream &operator<<(ostream &os, BankAccount ba) {
    os << ba.balance;
    return os;
  }
};
struct Command {
  virtual void call() = 0;
  virtual void undo() = 0;
};
struct BankAccoutCommand : Command {
  BankAccount &account;
  enum Action { deposit, withdraw } action;
  int amount;
  BankAccoutCommand(BankAccount &account, Action action, int amount)
      : account(account), action(action), amount(amount) {}
  void call() override {
    switch (action) {
    case deposit:
      account.deposit(amount);
      break;
    case withdraw:
      account.withdraw(amount);
      break;
    default:
      break;
    }
  }
  void undo() override {
    switch (action) {
    case deposit:
      account.withdraw(amount);
      break;
    case withdraw:
      account.deposit(amount);
      break;
    }
  }
};
int main(int argc, char *argv[]) {
  BankAccount bankAccout;
  vector<BankAccoutCommand> commands{
      BankAccoutCommand(bankAccout, BankAccoutCommand::withdraw, 200),
      BankAccoutCommand(bankAccout, BankAccoutCommand::deposit, 100)};
  cout << bankAccout << endl;
  for (auto &cmd : commands)
    cmd.call();
  cout << bankAccout << " commands size : " << commands.size() << endl;
  return 0;
}
