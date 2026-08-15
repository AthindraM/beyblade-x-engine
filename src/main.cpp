#include <iostream>

void comboMenu() {
  while (true) {
    std::cout << "\n";
    std::cout << "============================\n";
    std::cout << "       COMBO MANAGER\n";
    std::cout << "============================\n";

    std::cout << "1. Create combo\n";
    std::cout << "2. View all combos\n";
    std::cout << "3. View combo\n";
    std::cout << "4. Edit combo\n";
    std::cout << "5. Delete combo\n";
    std::cout << "0. Back\n";

    int choice{};
    std::cin >> choice;

    switch (choice) {
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 0:
      return;
    default:
      std::cout << "Invalid choice.\n";
    }
  }
}

int main() {
  while (true) {
    std::cout << "[\n----Beyblade X Engine----]\n";
    std::cout << "===========================\n";
    std::cout << "1. Manage Combos\n";
    std::cout << "2. Manage Decks\n";
    std::cout << "3. Exit\n";

    int choice{};
    std::cin >> choice;

    switch (choice) {
    case 1:
      comboMenu();
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
