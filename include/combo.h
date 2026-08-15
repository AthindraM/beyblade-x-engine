#pragma once
#include <iostream>
#include <string>

class Combo {
private:
  int id{};
  std::string comboName{};
  std::string blade{};
  std::string ratchet{};
  std::string bit{};

public:
  Combo();
  Combo(int id, const std::string &name, const std::string &blade,
        const std::string &ratchet, const std::string &bit);

  int getID() const;
  const std::string &getComboName() const;
  const std::string &getBlade() const;
  const std::string &getRatchet() const;
  const std::string &getBit() const;

  void setComboName(const std::string &comboName);
  void setBlade(const std::string &blade);
  void setRatchet(const std::string &ratchet);
  void setBit(const std::string &bit);

  void display() const;

  std::string serialize() const;
  static Combo deserialize(const std::string &line);
};
