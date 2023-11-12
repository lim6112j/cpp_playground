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
  bool withdraw(int amount) {
    if (balance - amount >= overdraft_limit) {
      balance -= amount;
      cout << "withdraw " << amount << ", balance is now " << balance << endl;
      return true;
    }
    return false;
  }
  friend ostream &operator<<(ostream &os, BankAccount ba) {
    os << "balance : " << ba.balance << "\n";
    return os;
  }
};
struct Command {
  bool succeeded;
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
      succeeded = true;
      break;
    case withdraw:
      succeeded = account.withdraw(amount);
      break;
    default:
      break;
    }
  }
  void undo() override {
    if (!succeeded)
      return;
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
struct CompositeBankAccontCommand : vector<BankAccoutCommand>, Command {
  CompositeBankAccontCommand(const initializer_list<BankAccoutCommand> &items)
      : vector(items) {}
  void call() override {
    for (auto &cmd : *this) {
      cmd.call();
    }
  }
  void undo() override {
    for (auto it = rbegin(); it != rend(); it++)
      it->undo();
  }
};
struct DependentCompositeAccountCommand : CompositeBankAccontCommand {
  DependentCompositeAccountCommand(
      const initializer_list<BankAccoutCommand> &items)
      : CompositeBankAccontCommand(items) {}
  void call() override {
    for (auto &cmd : *this) {
      cmd.call();
      if (!cmd.succeeded)
        break;
    }
  }
};
struct MoneyTransferCommand : CompositeBankAccontCommand {
  MoneyTransferCommand(BankAccount &from, BankAccount &to, int amount)
      : CompositeBankAccontCommand{
            BankAccoutCommand(from, BankAccoutCommand::withdraw, amount),
            BankAccoutCommand(to, BankAccoutCommand::deposit, amount)} {}
};
struct MoneyTransferCommand2 : DependentCompositeAccountCommand {
  MoneyTransferCommand2(BankAccount &from, BankAccount &to, int amount)
      : DependentCompositeAccountCommand{
            BankAccoutCommand(from, BankAccoutCommand::withdraw, amount),
            BankAccoutCommand(to, BankAccoutCommand::deposit, amount)} {}
};
int main(int argc, char *argv[]) {
  BankAccount ba1;
  BankAccount ba2;
  ba1.deposit(1000);
  MoneyTransferCommand2 mtc{ba1, ba2, 100};
  mtc.call();
  cout << "ba1 : " << ba1 << "ba2 : " << ba2 << endl;
  mtc.undo();
  cout << "ba1 : " << ba1 << "ba2 : " << ba2 << endl;
  return 0;
}
