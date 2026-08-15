#pragma once

#include <array>
#include <string>

class Deck {
private:
  int id;
  std::string name;
  std::array<int, 3> comboIds;

public:
  Deck();
  Deck(int id, const std::string &name, int combo1, int combo2, int combo3);

  int getId() const;
  const std::string &getName() const;
  const std::array<int, 3> &getComboIds() const;

  void setName(const std::string &name);

  void setComboId(int index, int comboId);

  void display() const;

  std::string serialize() const;
  static Deck deserialize(const std::string &line);
};
