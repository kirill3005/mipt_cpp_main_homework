#include <cstring>
#include <iomanip>
#include <iostream>

constexpr int cCommandNameLength = 32;

using Operation = bool (*)(long long& balance);

bool Deposit(long long& balance) {
  long long amount;
  std::cin >> amount;
  if (amount <= 0) {
    return false;
  }
  balance += amount;
  return true;
}

bool Withdraw(long long& balance) {
  long long amount;
  std::cin >> amount;
  if (amount <= 0 || amount > balance) {
    return false;
  }
  balance -= amount;
  return true;
}

bool PrintBalance(long long& balance) {
  std::cout << balance << '\n';
  return true;
}

bool ResetBalance(long long& balance) {
  balance = 0;
  return true;
}

bool DoubleBalance(long long& balance) {
  balance *= 2;
  return true;
}

struct Command {
  const char* name;
  Operation operation;
};

constexpr Command cCommands[] = {
    {"deposit", Deposit},      {"withdraw", Withdraw},
    {"balance", PrintBalance}, {"reset", ResetBalance},
    {"double", DoubleBalance},
};

constexpr int cCommandsCount =
    static_cast<int>(sizeof(cCommands) / sizeof(cCommands[0]));

int main() {
  long long balance = 0;
  char command_name[cCommandNameLength];

  while (std::cin >> std::setw(cCommandNameLength) >> command_name) {
    if (std::strcmp(command_name, "stop") == 0) {
      break;
    }

    bool is_successful = false;
    for (int i = 0; i < cCommandsCount; ++i) {
      if (std::strcmp(command_name, cCommands[i].name) == 0) {
        is_successful = cCommands[i].operation(balance);
        break;
      }
    }

    if (!is_successful) {
      std::cout << "error\n";
    }
  }
}
