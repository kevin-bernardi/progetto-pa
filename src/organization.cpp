/*
 * organization.cpp
 *
 *  Created on: 29 set 2022
 *      Author: Kevin
 */

#include <iostream>
#include <vector>
#include "organization.hpp"

Organization::Organization(std::string name, std::vector<Organization*> *db){
	this->name = name;
	this->coach = NULL;
	db->push_back(this);
}

Organization::~Organization(){
	std::cout << "Distr. Organization" << std::endl;
}

std::string Organization::getName(){
	return name;
}

void Organization::print(){
	std::cout << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "TEAM " << name << std::endl;
	std::cout << std::endl;
	std::cout << "Players" << std::endl;

	if(players.size() > 0){
		// print player list
		for (std::vector<Player*>::iterator i = players.begin(); i != players.end(); ++i) {
			std::cout << (*i)->toString() << std::endl;
		}

	} else {
		std::cout << "NO PLAYERS" << std::endl;
	}


	std::cout << std::endl;
			std::cout << "Coach" << std::endl;

	if (coach != NULL) {

		std::cout << coach->toString() << std::endl;

	} else {
		std::cout << "NO COACH" << std::endl;
	}

	std::cout << "--------------------" << std::endl;

}

// coach methods
Coach* Organization::getCoach(){
	return coach;
}

void Organization::setCoach(Coach* c){
	if(c->hasTeam()){
		throw std::runtime_error("Can't add a coach who is still a part of another team!");
		return;
	}
	coach = c;
	c->setTeam(name);
}

void Organization::removeCoach(){
	coach->unsetTeam();
	coach = NULL;
}

bool Organization::hasCoach(){
	return coach != NULL;
}


// players methods+
void Organization::addPlayer(Player* pl){
	if(pl->hasTeam()){
		throw "Can't add a player who is still a part of another team!";
		return;
	}

	players.push_back(pl);
	pl->setTeam(name);
}

void Organization::removePlayer(std::string nn) {

	int index = 0;
	bool found = false;

	// find the index of the player to remove
	for (std::vector<Player*>::iterator i = players.begin(); i != players.end(); ++i) {

		if ((*i)->getNickname() == nn) {
			found = true;
			break;
		}

		index++;
	}

	if(found == true){
		players.at(index)->unsetTeam();
		// remove the player from the vector
		players.erase(players.begin() + index);
		return;
	}

	throw std::runtime_error("Player to remove don't found!") ;


}

Player* Organization::getPlayer(std::string nn) {

	// find the index of the player to remove
	for (std::vector<Player*>::iterator i = players.begin(); i != players.end(); ++i) {

		if ((*i)->getNickname() == nn) {
			return *i;
		}
	}


	throw "Player don't found!";
}

Player* Organization::getBestPlayer(){

	double maxAvgKD = 0;
	int maxIndex = 0;
	int index = 0;

	for (std::vector<Player*>::iterator i = players.begin(); i != players.end(); ++i) {

		if((*i)->getAvgKD() > maxAvgKD){
			maxAvgKD = (*i)->getAvgKD();
			maxIndex = index;
		}

		index++;
	}

	return players.at(maxIndex);
}

bool Organization::hasPlayer(std::string nn) {

	// find the index of the player to remove
	for (std::vector<Player*>::iterator i = players.begin(); i != players.end(); ++i) {

		if ((*i)->getNickname() == nn) {
			return true;
		}
	}

	return false;
}







