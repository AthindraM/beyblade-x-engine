#include "Combo.h"

#include <iostream>
#include <sstream>
#include <vector>

Combo::Combo() : id(0), name(""), blade(""), ratchet(""), bit("") {}

Combo::Combo(int id, const std::string &comboName, const std::string &blade,
             const std::string &ratchet, const std::string &bit)
    : id(id), name(name), blade(blade), ratchet(ratchet), bit(bit) {}

int Combo::getId() const { return id; }

const std::string &Combo::getComboName() const { return comboName; }

const std::string &Combo::getBlade() const { return blade; }

const std::string &Combo::getRatchet() const { return ratchet; }

const std::string &Combo::getBit() const { return bit; }

void Combo::setComboName(const std::string &comboName) {
  this->comboName = comboName;
}

void Combo::setBlade(const std::string &blade) { this->blade = blade; }

void Combo::setRatchet(const std::string &ratchet) { this->ratchet = ratchet; }

void Combo::setBit(const std::string &bit) { this->bit = bit; }

void Combo::display() const {
  std::cout << "\n";
  std::cout << "ID:      " << id << '\n';
  std::cout << "Combo Name:    " << comboName << '\n';
  std::cout << "Blade:   " << blade << '\n';
  std::cout << "Ratchet: " << ratchet << '\n';
  std::cout << "Bit:     " << bit << '\n';
}

std::string Combo::serialize() const {
  std::ostringstream output;

  output << id << '|' << comboName << '|' << blade << '|' << ratchet << '|'
         << bit;

  return output.str();
}

Combo Combo::deserialize(const std::string &line) {
  std::stringstream stream(line);

  std::string idString;
  std::string comboName;
  std::string blade;
  std::string ratchet;
  std::string bit;

  std::getline(stream, idString, '|');
  std::getline(stream, comboName, '|');
  std::getline(stream, blade, '|');
  std::getline(stream, ratchet, '|');
  std::getline(stream, bit, '|');

  int id = std::stoi(idString);

  return Combo(id, comboName, blade, ratchet, bit);
}
