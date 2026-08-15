#pragma once

#include "combo.h"
#include "deck.h"

#include <string>
#include <vector>

class Database {
private:
  void initializeFiles();
  std::vector<Combo> combos;
  std::vector<Deck> decks;

  int nextComboId;
  int nextDeckId;

  std::string comboFile;
  std::string deckFile;

public:
  Database(const std::string &comboFile = "data/combos.txt",
           const std::string &deckFile = "data/decks.txt");

  void load();
  void save() const;

  // Combo operations
  int addCombo(const std::string &name, const std::string &blade,
               const std::string &ratchet, const std::string &bit);

  Combo *getCombo(int id);
  const Combo *getCombo(int id) const;

  const std::vector<Combo> &getCombos() const;

  bool updateCombo(int id, const std::string &name, const std::string &blade,
                   const std::string &ratchet, const std::string &bit);

  bool deleteCombo(int id);

  // Deck operations
  int addDeck(const std::string &name, int combo1, int combo2, int combo3);

  Deck *getDeck(int id);
  const Deck *getDeck(int id) const;

  const std::vector<Deck> &getDecks() const;

  bool updateDeck(int id, const std::string &name, int combo1, int combo2,
                  int combo3);

  bool deleteDeck(int id);
};
