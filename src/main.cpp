#include "database.h"

#include <iostream>
#include <limits>
#include <string>

void clearInput() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string inputString(const std::string &prompt) {
  std::cout << prompt;

  std::string value;
  std::getline(std::cin, value);

  return value;
}

int inputInt(const std::string &prompt) {
  while (true) {
    std::cout << prompt;

    int value;

    if (std::cin >> value) {
      clearInput();
      return value;
    }

    std::cout << "Invalid number. Try again.\n";

    std::cin.clear();
    clearInput();
  }
}

void pause() {
  std::cout << "\nPress ENTER to continue...";
  std::cin.get();
}

void createCombo(Database &db) {
  std::cout << "\n===== CREATE COMBO =====\n";

  std::string name = inputString("Combo name: ");

  std::string blade = inputString("Blade: ");

  std::string ratchet = inputString("Ratchet: ");

  std::string bit = inputString("Bit: ");

  int id = db.addCombo(name, blade, ratchet, bit);

  db.save();

  std::cout << "\nCombo created successfully!\n";
  std::cout << "Combo ID: " << id << '\n';
}

void listCombos(const Database &db) {
  std::cout << "\n===== ALL COMBOS =====\n";

  const auto &combos = db.getCombos();

  if (combos.empty()) {
    std::cout << "No combos found.\n";
    return;
  }

  for (const Combo &combo : combos) {
    combo.display();
  }
}

void viewCombo(Database &db) {
  int id = inputInt("\nEnter combo ID: ");

  const Combo *combo = db.getCombo(id);

  if (!combo) {
    std::cout << "Combo not found.\n";
    return;
  }

  combo->display();
}

void editCombo(Database &db) {
  std::cout << "\n===== EDIT COMBO =====\n";

  int id = inputInt("Combo ID: ");

  Combo *combo = db.getCombo(id);

  if (!combo) {
    std::cout << "Combo not found.\n";
    return;
  }

  combo->display();

  std::cout << "\nEnter new information.\n";

  std::string name = inputString("Name: ");

  std::string blade = inputString("Blade: ");

  std::string ratchet = inputString("Ratchet: ");

  std::string bit = inputString("Bit: ");

  db.updateCombo(id, name, blade, ratchet, bit);

  db.save();

  std::cout << "\nCombo updated successfully.\n";
}

void deleteCombo(Database &db) {
  std::cout << "\n===== DELETE COMBO =====\n";

  int id = inputInt("Combo ID: ");

  Combo *combo = db.getCombo(id);

  if (!combo) {
    std::cout << "Combo not found.\n";
    return;
  }

  combo->display();

  std::string confirmation = inputString("\nDelete this combo? (y/n): ");

  if (confirmation != "y" && confirmation != "Y") {
    std::cout << "Deletion cancelled.\n";
    return;
  }

  if (db.deleteCombo(id)) {
    db.save();
    std::cout << "Combo deleted.\n";
  }
}

bool comboExists(const Database &db, int comboId) {
  return db.getCombo(comboId) != nullptr;
}

void createDeck(Database &db) {
  std::cout << "\n===== CREATE DECK =====\n";

  if (db.getCombos().size() < 3) {
    std::cout << "You need at least 3 combos before "
              << "creating a deck.\n";

    return;
  }

  std::string name = inputString("Deck name: ");

  listCombos(db);

  int combo1 = inputInt("\nCombo 1 ID: ");

  int combo2 = inputInt("Combo 2 ID: ");

  int combo3 = inputInt("Combo 3 ID: ");

  if (!comboExists(db, combo1) || !comboExists(db, combo2) ||
      !comboExists(db, combo3)) {

    std::cout << "One or more combo IDs are invalid.\n";
    return;
  }

  int id = db.addDeck(name, combo1, combo2, combo3);

  db.save();

  std::cout << "\nDeck created successfully!\n";
  std::cout << "Deck ID: " << id << '\n';
}

void displayDeck(const Database &db, const Deck &deck) {
  std::cout << "\n";
  std::cout << "=================================\n";
  std::cout << "Deck ID: " << deck.getId() << '\n';
  std::cout << "Name:    " << deck.getName() << '\n';
  std::cout << "=================================\n";

  const auto &comboIds = deck.getComboIds();

  for (int i = 0; i < 3; ++i) {
    const Combo *combo = db.getCombo(comboIds[i]);

    std::cout << "\n--- Combo " << (i + 1) << " ---\n";

    if (combo) {
      combo->display();
    } else {
      std::cout << "Combo no longer exists.\n";
    }
  }
}

void listDecks(const Database &db) {
  std::cout << "\n===== ALL DECKS =====\n";

  const auto &decks = db.getDecks();

  if (decks.empty()) {
    std::cout << "No decks found.\n";
    return;
  }

  for (const Deck &deck : decks) {
    displayDeck(db, deck);
  }
}

void viewDeck(Database &db) {
  int id = inputInt("\nEnter deck ID: ");

  const Deck *deck = db.getDeck(id);

  if (!deck) {
    std::cout << "Deck not found.\n";
    return;
  }

  displayDeck(db, *deck);
}

void editDeck(Database &db) {
  std::cout << "\n===== EDIT DECK =====\n";

  int id = inputInt("Deck ID: ");

  Deck *deck = db.getDeck(id);

  if (!deck) {
    std::cout << "Deck not found.\n";
    return;
  }

  displayDeck(db, *deck);

  std::string name = inputString("\nNew deck name: ");

  listCombos(db);

  int combo1 = inputInt("\nNew Combo 1 ID: ");
  int combo2 = inputInt("New Combo 2 ID: ");
  int combo3 = inputInt("New Combo 3 ID: ");

  if (!comboExists(db, combo1) || !comboExists(db, combo2) ||
      !comboExists(db, combo3)) {

    std::cout << "One or more combo IDs are invalid.\n";
    return;
  }

  db.updateDeck(id, name, combo1, combo2, combo3);

  db.save();
  std::cout << "\nDeck updated successfully.\n";
}

void deleteDeck(Database &db) {
  std::cout << "\n===== DELETE DECK =====\n";

  int id = inputInt("Deck ID: ");

  Deck *deck = db.getDeck(id);

  if (!deck) {
    std::cout << "Deck not found.\n";
    return;
  }

  displayDeck(db, *deck);

  std::string confirmation = inputString("\nDelete this deck? (y/n): ");

  if (confirmation != "y" && confirmation != "Y") {

    std::cout << "Deletion cancelled.\n";
    return;
  }

  if (db.deleteDeck(id)) {
    db.save();
    std::cout << "Deck deleted.\n";
  }
}

void comboMenu(Database &db) {
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

    int choice = inputInt("\nChoice: ");

    switch (choice) {
    case 1:
      createCombo(db);
      pause();
      break;
    case 2:
      listCombos(db);
      pause();
      break;
    case 3:
      viewCombo(db);
      pause();
      break;
    case 4:
      editCombo(db);
      pause();
      break;
    case 5:
      deleteCombo(db);
      pause();
      break;
    case 0:
      return;
    default:
      std::cout << "Invalid choice.\n";
    }
  }
}

void deckMenu(Database &db) {
  while (true) {
    std::cout << "\n";
    std::cout << "============================\n";
    std::cout << "        DECK MANAGER\n";
    std::cout << "============================\n";

    std::cout << "1. Create deck\n";
    std::cout << "2. View all decks\n";
    std::cout << "3. View deck\n";
    std::cout << "4. Edit deck\n";
    std::cout << "5. Delete deck\n";
    std::cout << "0. Back\n";

    int choice = inputInt("\nChoice: ");

    switch (choice) {
    case 1:
      createDeck(db);
      pause();
      break;
    case 2:
      listDecks(db);
      pause();
      break;
    case 3:
      viewDeck(db);
      pause();
      break;
    case 4:
      editDeck(db);
      pause();
      break;
    case 5:
      deleteDeck(db);
      pause();
      break;
    case 0:
      return;
    default:
      std::cout << "Invalid choice.\n";
    }
  }
}

int main() {

  Database db;
  db.load();

  while (true) {
    std::cout << "\n";
    std::cout << "=================================\n";
    std::cout << "       BEYBLADE COMBO MANAGER\n";
    std::cout << "=================================\n";

    std::cout << "1. Manage Combos\n";
    std::cout << "2. Manage Decks\n";
    std::cout << "3. View Statistics\n";
    std::cout << "0. Exit\n";

    int choice = inputInt("\nChoice: ");

    switch (choice) {
    case 1:
      comboMenu(db);
      break;
    case 2:
      deckMenu(db);
      break;
    case 3:
      std::cout << "\n";
      std::cout << "Combos: " << db.getCombos().size() << '\n';
      std::cout << "Decks: " << db.getDecks().size() << '\n';
      pause();
      break;
    case 0:
      db.save();
      std::cout << "\nGoodbye!\n";
      return 0;
    default:
      std::cout << "Invalid choice. Try again.\n";
    }
  }
}
