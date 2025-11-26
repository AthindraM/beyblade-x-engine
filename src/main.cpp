#include <iostream>
#include <string>

int main() {
	std::cout << "[--- BEYBLADE X ENGINE ---]\n";

	std::cout << "\nEnter the parts you want to combine:\n";

	std::cout << "Blade: ";
	std::string blade {};
	std::getline(std::cin >> std::ws, blade);

	std::cout << "Ratchet: ";
	std::string ratchet {};
	std::getline(std::cin >> std::ws, ratchet);
	
	std::cout << "Bit: ";
	std::string bit {};
	std::getline(std::cin >> std::ws, bit);
	
	std::string combo {blade + ' ' + ratchet + bit};
	std::cout << "Your combo is:\n" << combo << '\n';
}
