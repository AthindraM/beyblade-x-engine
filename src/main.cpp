#include <iostream>
#include <string>
#include <vector>

void createCombo(std::vector<std::string>& vec) {
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
	std::cout << "\nYour combo is:\n" << combo << '\n';

	std::cout << "\nWould you like to save your combo? (Y/n) ";
	char saveChoice {};
	std::cin >> saveChoice;
	if (saveChoice == 'Y' || saveChoice == 'y') {
		std::cout << "Your combo is saved!\n";
		vec.push_back(combo);
	}
}

void viewCombos(std::vector<std::string>& vec) {
	if (!vec.empty()) {
		std::cout << "\nSaved Combos:\n";
		for (std::string& str : vec)
			std::cout << str << '\n';
	}
	else
		std::cout << "\nNo saved combos.\n";
}

int main() {
	std::vector<std::string> savedCombos {};

	bool running {true};
	while (running) {
		std::cout << "\n[--- BEYBLADE X ENGINE ---]\n";
		std::cout << "===========================\n";
		std::cout << "1. Create Combo\n2. View Saved Combos\n3. Exit\n";
		std::cout << "===========================\n";
	
		int choice {};
		std::cin >> choice;
		switch (choice) {
			case 1: {
				createCombo(savedCombos);
				break;
			}
			case 2: {
				viewCombos(savedCombos);
				break;
			}
			case 3: {
				running = false;
				break;
			}
		}
	}
}
