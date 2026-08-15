#include "Combo.h"

#include <iostream>
#include <sstream>
#include <vector>

Combo::Combo() : id(0), name(""), blade(""), ratchet(""), bit("") {}

Combo::Combo(int id, const std::string &name, const std::string &blade,
             const std::string &ratchet, const std::string &bit)
    : id(id), name(name), blade(blade), ratchet(ratchet), bit(bit) {}

int Combo::getId() const { return id; }

const std::string &Combo::name() const { return name; }

const std::string &Combo::getBlade() const { return blade; }

const std::string &Combo::getRatchet() const { return ratchet; }

const std::string &Combo::getBit() const { return bit; }

void Combo::name(const std::string &name) { this->name = name; }

void Combo::setBlade(const std::string &blade) { this->blade = blade; }

void Combo::setRatchet(const std::string &ratchet) { this->ratchet = ratchet; }

void Combo::setBit(const std::string &bit) { this->bit = bit; }

void Combo::display() const {
  std::cout << "\n";
  std::cout << "ID:      " << id << '\n';
  std::cout << "Combo Name:    " << name << '\n';
  std::cout << "Blade:   " << blade << '\n';
  std::cout << "Ratchet: " << ratchet << '\n';
  std::cout << "Bit:     " << bit << '\n';
}

std::string Combo::serialize() const {
  std::ostringstream output;

  output << id << '|' << name << '|' << blade << '|' << ratchet << '|' << bit;

  return output.str();
}

Combo Combo::deserialize(const std::string &line) {
  std::stringstream stream(line);

  std::string idString;
  std::string name;
  std::string blade;
  std::string ratchet;
  std::string bit;

  std::getline(stream, idString, '|');
  std::getline(stream, name, '|');
  std::getline(stream, blade, '|');
  std::getline(stream, ratchet, '|');
  std::getline(stream, bit, '|');

  int id = std::stoi(idString);

  return Combo(id, name, blade, ratchet, bit);
}
