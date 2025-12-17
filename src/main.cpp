#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cctype>

void listSavedDecks() {
	std::cout << "\nSaved Decks:\n";
	int count {1};
	for (const auto& deck : std::filesystem::directory_iterator("saved_decks")) {
		if (deck.is_regular_file() && deck.path().extension() == ".txt")
			std::cout << count++ << ". " << deck.path().filename() << '\n';
	}
}

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

void exportCombo(std::vector<std::string>& vec, std::string filename) {
	std::filesystem::path filepath = std::filesystem::path("saved_decks") / std::filesystem::path(filename + ".txt");
	std::ofstream outf{ filepath.string() };
	
	if (!outf) {
		std::cerr << "\n---ERROR---\n| " << filepath << " couldn't be generated!\n-----------\n";
		return;
	}
	for (const auto& str : vec)
		outf << str << '\n';

	std::cout << "\nCombo exported! (" << filepath.filename() << ")\n";
}

void viewCombos(std::vector<std::string>& vec) {
	if (vec.empty())
		std::cout << "\nNo saved combos.\n";
	else {
		std::cout << "\nCurrent Saved Combos:\n";
		int count {1};
		for (const auto& str : vec) {
			std::cout << count << ". " << str << '\n';
			count++;
		}
	}

	listSavedDecks();

	std::cout << "\n|[E]xport saved combos | [S]elect a deck | [B]ack\n";
	char inputChoice {};
	std::cin >> inputChoice;
	std::cin.ignore(1000, '\n');

	switch (std::toupper(inputChoice)){
		case 'E': {
			std::cout << "\nWhat would you like this deck to be called?\n";
			std::string exportFilename{};
			std::getline(std::cin >> std::ws, exportFilename);

			exportCombo(vec, exportFilename);
			break;
		}
		case 'S':
			std::cout << "\nSorry, this feature is coming soon!\n";
			break;
		case 'B':
			return;
	}
}

int main() {

	std::filesystem::create_directories("saved_decks");
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
