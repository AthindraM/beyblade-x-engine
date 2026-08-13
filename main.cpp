#include <iostream>

int main() {
  std::cout << "[\n----Beyblade X Engine----]\n";
  std::cout << "===========================\n";

  while (true) {
    std::cout << "1. Manage Combos\n";
    std::cout << "2. Manage Decks\n";
    std::cout << "3. Exit\n";

    int choice{};
    std::cin >> choice;

    switch (choice) {
    case 1:
      break;
    case 2:
      break;
    case 3:
      return 0;
    default:
      std::cout << "Invalid option, try again.\n";
      break;
    }
  }
}
