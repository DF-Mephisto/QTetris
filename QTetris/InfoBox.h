#pragma once

#include <QtWidgets>

#include "ScaledLabel.h"

class InfoBox : public QWidget
{
	Q_OBJECT

public:
	InfoBox(QWidget* parent = 0);

public slots:
	void setScore(int score);
	void setLevel(int level);

private:
	ScaledLabel* logo;
	QLabel* scoreLabel;
	QLabel* score;
	QLabel* levelLabel;
	QLabel* level;
	
	QVBoxLayout* layout;
};
