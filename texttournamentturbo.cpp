#include <iostream>
#include <string>
#include <fstream>
#include <random>
using namespace std;

void setupPlayerStats(string& name, int& str, int& def, int& armor, int& skill, int& wins);
void savePlayerStats(string name, int str, int def, int armor, int skill, int wins);
int main() {
	random_device rd;
	uniform_int_distribution<int> d6(1, 6);

	string p1Name;
	int p1Str;
	int p1Def;
	int p1Armor;
	int p1Skill;
	int p1Wins;

	string p2Name;
	int p2Str;
	int p2Def;
	int p2Armor;
	int p2Skill;
	int p2Wins;

	cout << endl << "SETTING UP PLAYER 1..." << endl << "?";
	setupPlayerStats(p1Name, p1Str, p1Def, p1Armor, p1Skill, p1Wins);

	cout << endl << "SETTING UP PLAYER 2..." << endl << "?";
	setupPlayerStats(p2Name, p2Str, p2Def, p2Armor, p2Skill, p2Wins);

	int p1Health = 20;
	int p2Health = 20;
	int turns = 0;

	cout << endl << "TIME FOR THE FIGHT!" << endl;
    cout << "Introducing the challengers" << endl;
    cout << p1Name << ": " << p1Wins << " Wins" << endl;
    cout << p2Name << ": " << p2Wins << " Wins" << endl;
    cout << "_________________________________" << endl << endl;

	while ((p1Health > 0) && (p2Health > 0) && (turns < 100)) {
		int attackRoll;
		int damageRoll;
		cout << "BEGIN ROUND " << turns + 1 << endl;
		attackRoll = p1Skill + d6(rd);

		if (attackRoll >= 3 + p2Def) {
			cout << p1Name << " hits " << p2Name << "..." << endl;
			damageRoll = p1Str + d6(rd) - p2Armor;
			if (damageRoll > 0) {
				p2Health -= damageRoll;
				cout << "..." << p2Name << " takes " << damageRoll << " damage!" << endl;
			}
			else {
				cout << "..." << p2Name << "'s armor blocks all the damage!" << endl;
			}
		}
		else {
			cout << p1Name << " swings at " << p2Name << "..." << endl;
			cout << "..." << p2Name << "'s defense blocks the hit!" << endl;
		}

		cout << "ROUND RESULTS..." << endl;
		cout << p1Name << "'s Health: " << p1Health << endl;
		cout << p2Name << "'s Health: " << p2Health << endl << endl;
		turns++;
	}

	cout << "_____________FIGHT COMPLETE____________" << endl;
	if (((p1Health > 0) && (p2Health > 0)) || ((p1Health <= 0) && (p2Health <= 0))) {
		cout << "The result is..." << endl;
		cout << "...the fight was so close that it ended in a DRAW!" << endl;
		cout << "What a great performance from both challengers!" << endl;
	}
	else if (p1Health > 0) {
		cout << "The result is..." << endl;
		cout << p1Name << " beats " << p2Name << " !" << endl;
		cout << "Congratulation!" <<endl;
		p1Wins++;
	}
	else {
		cout << "The result is..." << endl;
		cout << p2Name << " beats " << p1Name << " !" << endl;
		cout << "Congratulation!" <<endl;
		p2Wins++;
	}

	savePlayerStats(p1Name, p1Str, p1Def, p1Armor, p1Skill, p1Wins);
	savePlayerStats(p2Name, p2Str, p2Def, p2Armor, p2Skill, p2Wins);
}

void setupPlayerStats(string& name, int& str, int& def, int& armor, int& skill, int& wins) {
	fstream file;

	cout << "Name: ";
	getline(cin, name);
	if (name == "") {
		name = "No name";
	}
	string filename = name + ".txt";
	file.open(filename, ios::in);
	if (file.is_open()) {
		file >> str;
		file >> def;
		file >> armor;
		file >> skill;
		file >> wins;
		file.close();
	}
	else
	{
		bool accept = false;
	while (accept == false) 
	{
		int points = 20;
		cout << "You have " << points << " to assgin your character's stats (include strength, defense, armor, and skill). " << endl;

		cout << "Strength: " << endl;
		cin >> str;
		points -= str;
		cout << "You have " << points << "remain to assign your character." << endl;

		cout << "Defense: " << endl;
		cin >> def;
		points -= def;
		cout << "You have " << points << "remain to assign your character." << endl;

		cout << "Armor: " << endl;
		cin >> skill;
		points -= skill;
		cout << "You have " << points << "remain to assign your character." << endl;

		cout << "Skill: " << endl;
		cin >> str;
		points -= str;
		cout << "You have " << points << "remain to assign your character." << endl;
		cin.ignore();

		wins = 0;
		if (points >= 0) {
			cout << " Request is passed, " << name << " is created" << endl;
			accept = true;
		}
		else {
			cout << "You exceed the stats limit." << endl;
			cout << "Please try to create another character." << endl;
		}

	}
	}
}

void savePlayerStats(string name, int str, int def, int armor, int skill, int wins) {
	fstream file;
	string filename = name + ".txt";
	file.open(filename, ios::out);
	file << str << endl;
	file << def << endl;
	file << armor << endl;
	file << skill << endl;
	file << wins << endl;
	file.close();
}
