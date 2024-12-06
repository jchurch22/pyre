// Libraries / Classes
#include <iostream>
#include <string>
#include "Character.h"

// Constructors
Character::Character() {

	name = "New Character";
	species = "Species";
	age = 0;
	description = "New Character Description";

}
Character::Character(std::string name, std::string species, int age) {

	this->name = name;
	this->species = species;
	this->age = age;

}

// Setters / Getters
void Character::setName(std::string name) {

	this->name = name;

}
void Character::setSpecies(std::string species) {

	this->species = species;

}
void Character::setAge(int age) {

	this->age = age;

}
void Character::setDescription() {

	// Define description variable.
	std::string description;

	// Prompt the user to fill the description.
	std::cout << "Please enter a brief description of " << name << ":\n\n";
	std::cin >> description;

	// Set description.
	this->description = description;

}

std::string Character::getName() {

	return name;

}
std::string Character::getSpecies() {

	return species;

}
int Character::getAge() {

	return age;

}
std::string Character::getDescription() {

	return description;

}