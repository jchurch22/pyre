// Libraries / Classes
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include "LinkedList.h"

// Function prototypes
void menu(LinkedList<Character> characterList, std::string file);
int inputValidation();
void clearScreen();
void loadCharacters(const std::string& file, LinkedList<Character>& characterList);
void addCharacter(LinkedList<Character>& characterList);
void updateFile(const std::string& file, LinkedList<Character>& characterList, bool overwrite);

// Character struct
struct Character {

	std::string name;
	std::string species;
	int age;
	std::string description;

};

int main() {

	// Create character list.
	LinkedList<Character> characterList;

	std::string file = "characters.txt";

	// Display menu.
	menu(characterList, file);

}

// Function to display the menu and handle user choices
void menu(LinkedList<Character>& characterList, std::string file) {

	int choice;

	// Display menu.
	std::cout << "Pyre v.1.0" << std::endl << std::endl;

	std::cout << "1. Display Characters" << std::endl
		      << "2. Add Character" << std::endl
		      << "3. Remove Character" << std::endl
		      << "4. About" << std::endl
		      << "5. Exit" << std::endl << std::endl;

}

// Input validation function: Ensures the user does not enter anything other than an integer for certain prompts.
int inputValidation() {

	int input;
	bool valid = false;

	do {

		// Receives user input.
		std::cin >> input;

		// If the user enters a value that cannot be stored inside an int variable, such as a string, it will catch the fail state.
		if (std::cin.fail() || input < 0) {

			// Prompt the user for valid input.
			std::cout << "\nPlease enter a positive number to proceed!\n";
			std::cin.clear();	// Clears the fail state.
			std::cin.ignore();	// Clears cin so new input can be received.
		
		}
		else {

			// If the user enters a value that can be stored inside an int variable, their input is valid and input can be returned.
			valid = true;

		}

	} while (!valid);

	return input;

}

// This function can be used to clear the screen, and is universal across operating systems.
void clearScreen() {

#if defined(_WIN32) || defined(_WIN64)

	system("cls");

#else

	system("clear");

#endif

}

// This function will load the LinkedList in the main method with characters from a file.
void loadCharacters(const std::string& file, LinkedList<Character>& characterList) {

	std::ifstream characterFile(file);

	// Check for file errors.
	if (!characterFile.is_open()) {

		std::cerr << "Error opening file: " << file << std::endl;
		return;

	}

	// This variable represents each line of the file.
	std::string line;

	while (std::getline(characterFile, line)) {

		std::istringstream stream(line);
		Character character;
		stream >> character.name >> character.species >> character.age;

		// The rest of the line will represent the character's description.
		std::getline(stream, character.description);

		// Add the character to the list.
		characterList.push_back(character);

	}

	characterFile.close();

}

// This function will add a character to the file.
void addCharacter(LinkedList<Character>& characterList) {
	
	Character newCharacter;

	// Prompt the user for each character attribute.
	std::cout << "Enter character name: ";
	std::getline(std::cin, newCharacter.name);

	std::cout << std::endl << "Enter character species: ";
	std::getline(std::cin, newCharacter.species);

	std::cout << std::endl << "Enter character age: ";
	newCharacter.age = inputValidation();

	std::cout << std::endl << "Enter character description: " << std::endl << std::endl;
	std::getline(std::cin, newCharacter.description);

	// Add character to list.
	characterList.push_back(newCharacter);

	std::cout << std::endl << std::endl << newCharacter.name << " added." << std::endl;

}

// The file should be updated after an character is removed or added.
void updateFile(const std::string& file, LinkedList<Character>& characterList, bool overwrite) {

	// Opening the file in truncate mode allows it to overwrite an existing file.
	std::ofstream characterFile;

	if (overwrite) {

		characterFile.open(file, std::ios::trunc);

	}
	else {

		characterFile.open(file, std::ios::app);

	}

	// Check for file errors.
	if (!characterFile.is_open()) {

		std::cerr << "Error opening file: " << file << std::endl;
		return;

	}

	// Rewrite file with new addition / removal
	if (overwrite) {
		
		characterList.traverse([&characterFile](const Character& character) {

			characterFile << character.name << " "
					      << character.species << " "
					      << character.age << " "
					      << character.description << std::endl;

		});

	}
	else {

		const Character& character = characterList.back();
		characterFile << character.name << " "
					  << character.species << " "
					  << character.age << " "
					  << character.description << std::endl;

	}

	characterFile.close();

}