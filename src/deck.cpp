#include "Deck.h"

#include <iostream>
#include <sstream>

Deck::Deck() : id(0), name(""), comboIds{0, 0, 0} {}

Deck::Deck(int id, const std::string &name, int combo1, int combo2, int combo3)
    : id(id), name(name), comboIds{combo1, combo2, combo3} {}

int Deck::getId() const { return id; }

const std::string &Deck::getName() const { return name; }

const std::array<int, 3> &Deck::getComboIds() const { return comboIds; }

void Deck::setName(const std::string &name) { this->name = name; }

void Deck::setComboId(int index, int comboId) {
  if (index >= 0 && index < 3) {
    comboIds[index] = comboId;
  }
}

void Deck::display() const {
  std::cout << "\n";
  std::cout << "ID:   " << id << '\n';
  std::cout << "Name: " << name << '\n';

  for (int i = 0; i < 3; ++i) {
    std::cout << "Combo " << (i + 1) << ": " << comboIds[i] << '\n';
  }
}

std::string Deck::serialize() const {
  std::ostringstream output;

  output << id << '|' << name << '|' << comboIds[0] << '|' << comboIds[1] << '|'
         << comboIds[2];

  return output.str();
}

Deck Deck::deserialize(const std::string &line) {
  std::stringstream stream(line);

  std::string idString;
  std::string name;
  std::string combo1;
  std::string combo2;
  std::string combo3;

  std::getline(stream, idString, '|');
  std::getline(stream, name, '|');
  std::getline(stream, combo1, '|');
  std::getline(stream, combo2, '|');
  std::getline(stream, combo3, '|');

  return Deck(std::stoi(idString), name, std::stoi(combo1), std::stoi(combo2),
              std::stoi(combo3));
}
