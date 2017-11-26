//
// Created by steven athouel on 16/11/2017.
//

#include <string>
#include <map>
using namespace std;

#ifndef FANFARESIMULATOR_INSTRUMENT_HPP
#define FANFARESIMULATOR_INSTRUMENT_HPP

class Instrument {
protected:
	map <string, string> instruments;

public:
	//la liste des instruments choisis est repr�sent�e par un dictionnaire 
	//{instrument1 : NULL (ou username si instrument occup�), instrument2 : NULL...}

	//fonction qui va r�cuperer le nom de l'instrument choisi par username
	std::string getInstrument(std::string username, , map<string, string> listeInstru);

	//fonction qui va s�lectionner l'instrument instru_choisi pour l'username, et rendre instru_choisi indisponible
	void setInstru(std::string instru_choisi, std::string username, , map<string, string> listeInstru);

	//fonction qui rend instru libre � nouveau
	void unsetInstru(std::string instru, , map<string, string> listeInstru);

	//fonction qui initialise tous les instruments disponibles
	map<string, string> initInstru();

	//fonction qui renvoie tous les instruments disponibles
	map<string, string> getAvailableInstru(map<string, string> listeInstru);

};


#endif //FANFARESIMULATOR_INSTRUMENT_HPP
