#include "Database.h"

#include <fstream>
#include <iostream>

Database::Database(const std::string &comboFile, const std::string &deckFile)
    : nextComboId(1), nextDeckId(1), comboFile(comboFile), deckFile(deckFile) {}

void Database::load() {
  combos.clear();
  decks.clear();

  nextComboId = 1;
  nextDeckId = 1;

  // Load combos
  {
    std::ifstream file(comboFile);

    if (file) {
      std::string line;

      while (std::getline(file, line)) {
        if (line.empty()) {
          continue;
        }

        try {
          Combo combo = Combo::deserialize(line);

          combos.push_back(combo);

          if (combo.getId() >= nextComboId) {
            nextComboId = combo.getId() + 1;
          }
        } catch (...) {
          std::cerr << "Warning: Could not load combo.\n";
        }
      }
    }
  }

  // Load decks
  {
    std::ifstream file(deckFile);

    if (file) {
      std::string line;

      while (std::getline(file, line)) {
        if (line.empty()) {
          continue;
        }

        try {
          Deck deck = Deck::deserialize(line);

          decks.push_back(deck);

          if (deck.getId() >= nextDeckId) {
            nextDeckId = deck.getId() + 1;
          }
        } catch (...) {
          std::cerr << "Warning: Could not load deck.\n";
        }
      }
    }
  }
}

void Database::save() const {
  {
    std::ofstream file(comboFile);

    if (!file) {
      std::cerr << "Could not save combos.\n";
      return;
    }

    for (const Combo &combo : combos) {
      file << combo.serialize() << '\n';
    }
  }

  {
    std::ofstream file(deckFile);

    if (!file) {
      std::cerr << "Could not save decks.\n";
      return;
    }

    for (const Deck &deck : decks) {
      file << deck.serialize() << '\n';
    }
  }
}

// ============================================================
// COMBOS
// ============================================================

int Database::addCombo(const std::string &name, const std::string &blade,
                       const std::string &ratchet, const std::string &bit) {
  int id = nextComboId++;

  combos.emplace_back(id, name, blade, ratchet, bit);

  return id;
}

Combo *Database::getCombo(int id) {
  for (Combo &combo : combos) {
    if (combo.getId() == id) {
      return &combo;
    }
  }

  return nullptr;
}

const Combo *Database::getCombo(int id) const {
  for (const Combo &combo : combos) {
    if (combo.getId() == id) {
      return &combo;
    }
  }

  return nullptr;
}

const std::vector<Combo> &Database::getCombos() const { return combos; }

bool Database::updateCombo(int id, const std::string &name,
                           const std::string &blade, const std::string &ratchet,
                           const std::string &bit) {
  Combo *combo = getCombo(id);

  if (!combo) {
    return false;
  }

  combo->setName(name);
  combo->setBlade(blade);
  combo->setRatchet(ratchet);
  combo->setBit(bit);

  return true;
}

bool Database::deleteCombo(int id) {
  for (auto it = combos.begin(); it != combos.end(); ++it) {
    if (it->getId() == id) {
      combos.erase(it);
      return true;
    }
  }

  return false;
}

// ============================================================
// DECKS
// ============================================================

int Database::addDeck(const std::string &name, int combo1, int combo2,
                      int combo3) {
  int id = nextDeckId++;

  decks.emplace_back(id, name, combo1, combo2, combo3);

  return id;
}

Deck *Database::getDeck(int id) {
  for (Deck &deck : decks) {
    if (deck.getId() == id) {
      return &deck;
    }
  }

  return nullptr;
}

const Deck *Database::getDeck(int id) const {
  for (const Deck &deck : decks) {
    if (deck.getId() == id) {
      return &deck;
    }
  }

  return nullptr;
}

const std::vector<Deck> &Database::getDecks() const { return decks; }

bool Database::updateDeck(int id, const std::string &name, int combo1,
                          int combo2, int combo3) {
  Deck *deck = getDeck(id);

  if (!deck) {
    return false;
  }

  deck->setName(name);
  deck->setComboId(0, combo1);
  deck->setComboId(1, combo2);
  deck->setComboId(2, combo3);

  return true;
}

bool Database::deleteDeck(int id) {
  for (auto it = decks.begin(); it != decks.end(); ++it) {
    if (it->getId() == id) {
      decks.erase(it);
      return true;
    }
  }

  return false;
}
