#pragma once

#include <string>
#include <map>
#include <vector>
#include <QWidget>
#include <QRadioButton>
#include "../include/pupitre.hpp"

class PupitreWindow : public QWidget {
	Q_OBJECT
public:
	PupitreWindow(std::vector<Pupitre> pupitres);
	void start();

signals:
	void pupitreChosen(Pupitre p);

private:
	std::vector<Pupitre> pupitres;
	std::vector<QRadioButton*> buttons;

	void choosePupitre();
};
