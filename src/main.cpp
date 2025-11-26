#include <iostream>
#include <string>

int main() {
	std::cout << "[--- BEYBLADE X ENGINE ---]\n";
	std::cout << "\nEnter the parts you want to combine:\n";
	std::cout << "Blade: ";
	
	std::string blade {};
	std::getline(std::cin >> std::ws, blade);

	std::cout << blade << std::endl;

}
