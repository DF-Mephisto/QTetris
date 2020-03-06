#pragma once

#include <QtWidgets>

class GameOver : public QWidget
{
	Q_OBJECT

public:
	GameOver(QWidget* parent = 0);
	~GameOver();

protected:
	void resizeEvent(QResizeEvent* e) override;
	
private:
	QLabel* background;
	QLabel* text;
};