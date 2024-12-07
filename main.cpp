#include <fstream>
#include <iostream>
#include "LinkedList.h"

// Character struct
struct Character {

	std::string name;
	std::string species;
	int age;
	std::string description;

};

// Function prototypes
void menu(LinkedList<Character>& characterList, std::string file);
int inputValidation();
void clearScreen();
void loadCharacters(const std::string& file, LinkedList<Character>& characterList);
void printCharacters(const LinkedList<Character>& list);
void addCharacter(LinkedList<Character>& characterList);
void updateFile(const std::string& file, LinkedList<Character>& characterList, bool overwrite);

int main() {

	// Create character list.
	LinkedList<Character> characterList;

	std::string file = "characters.txt";

	// Load character menu.
	loadCharacters(file, characterList);

	// Display menu.
	menu(characterList, file);

}

void menu(LinkedList<Character>& characterList, std::string file) {

	while (true) {

		// Variable declaration
		std::string name;
		
		// Clear screen.
		clearScreen();

		// Display menu.
		std::cout << "Pyre v.1.0" << std::endl << std::endl;

		std::cout << "1. Display Characters" << std::endl
				  << "2. Add Character" << std::endl
				  << "3. Remove Character" << std::endl
				  << "4. About" << std::endl
	 			  << "5. Exit" << std::endl << std::endl;

		// Accept user input.
		int choice = inputValidation();
		clearScreen();

		switch (choice) {

		case 1:

			// Display characters.
			std::cout << "Characters" << std::endl << std::endl;

			if (characterList.empty())
				std::cout << "No characters found." << std::endl << std::endl;
			else
				printCharacters(characterList);

			// Return to the main menu.
			std::cout << "Press ENTER to return to the menu." << std::endl;
			std::cin.ignore();
			std::cin.get();
			break;

		case 2:

			// Refresh input buffer.
			std::cin.ignore();

			// Add a character.
			std::cout << "Add Character" << std::endl << std::endl;
			addCharacter(characterList);
			updateFile(file, characterList, false);

			// Return to the main menu.
			std::cout << "Press ENTER to return to the menu." << std::endl;
			std::cin.ignore();
			break;

		case 3:

			// Refresh input buffer.
			std::cin.ignore();

			// Remove a character
			std::cout << "Remove Character" << std::endl << std::endl
			          << "Please enter the name of the character you'd like to delete: ";
			std::getline(std::cin, name);

			if (characterList.deleteCharacter(name))
				std::cout << std::endl << "Character " << name << " successfully deleted." << std::endl << std::endl;
			else
				std::cout << std::endl << std::endl << "Character " << name << " not found." << std::endl << std::endl;

			// Update file.
			updateFile(file, characterList, true);

			// Return to the main menu.
			std::cout << "Press ENTER to return to the menu." << std::endl;
			std::cin.ignore();
			break;

		case 4:

			// Refresh input buffer.
			std::cin.ignore();

			// About page.
			std::cout << "Welcome to Pyre v.1.0." << std::endl << std::endl
				      << "Using this program, you will be able to build a catalog of the characters you've created," << std::endl
				      << "be it for a fantasy world of your own or a collaborative roleplaying experience with others." << std::endl << std::endl
				      << "To create a character, simply enter their name, species, age, and a short description. Your characters" << std::endl
				      << "will be safely stored in a file saved in this program's directory for you to view and remove at your leisure." << std::endl << std::endl
				      << "Happy creating!" << std::endl << std::endl
				      << "Created by: Johnathan Church" << std::endl
				      << "CSCI 2320: Data Structures" << std::endl
				      << "Project Advisor: Patricia Talley" << std::endl << std::endl;

			// Return to the main menu.
			std::cout << "Press ENTER to return to the menu." << std::endl;
			std::cin.ignore();
			break;

		case 5:

			// Exit
			std::cout << "Thank you for using Pyre." << std::endl;
			exit(0);

		default:

			// Refresh input buffer.
			std::cin.ignore();

			std::cout << "Please enter an integer 1-5 to make a selection." << std::endl << std::endl;

			// Return to the main menu.
			std::cout << "Press ENTER to return to the menu." << std::endl;
			std::cin.ignore();
			break;

		}

	}

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

// This function will print the attributes of each character in the list.
void printCharacters(const LinkedList<Character>& list) {

	list.traverse([](const Character& character) {

		std::cout << "--------------------------------" << std::endl << std::endl
			      << "Name: " << character.name << std::endl
		          << "Species: " << character.species << std::endl
		          << "Age: " << character.age << std::endl << std::endl
		          << "Description:" << std::endl << std::endl << character.description << std::endl << std::endl
			      << "--------------------------------" << std::endl << std::endl;

	});

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
	std::cin.ignore();
	std::getline(std::cin, newCharacter.description);

	// Add character to list.
	characterList.push_back(newCharacter);

	std::cout << std::endl << "Character " << newCharacter.name << " successfully added!" << std::endl << std::endl;

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