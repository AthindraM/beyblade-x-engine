#include <iostream>
#include <string>

void createCombo() {
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
}

void viewCombos() { std::cout << "\ncoming soon!\n"; }

int main() {
	bool running {true};
	while (running) {
		std::cout << "\n[--- BEYBLADE X ENGINE ---]\n";
		std::cout << "1. Create Combo\n2. View Saved Combos\n3. Exit\n";
	
		int choice {};
		std::cin >> choice;
		switch (choice) {
			case 1: {
				createCombo();
				break;
			}
			case 2: {
				viewCombos();
				break;
			}
			case 3: {
				running = false;
				break;
			}
		}
	}
}
