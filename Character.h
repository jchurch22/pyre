#pragma once

// Libraries / Classes
#include <string>

class Character {

private:	// Attributes

	std::string name;
	std::string species;
	int age;
	std::string description;

public:

	// Constructors
	Character();
	Character(std::string name, std::string species, int age);

	// Setters / Getters
	void setName(std::string name);
	void setSpecies(std::string species);
	void setAge(int age);
	void setDescription();
	std::string getName();
	std::string getSpecies();
	int getAge();
	std::string getDescription();

};