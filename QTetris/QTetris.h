#pragma once

#include <QtWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "TRender.h"
#include "TLogic.h"
#include "GameOver.h"
#include "InfoBox.h"

class QTetris : public QWidget
{
	Q_OBJECT

public:
	QTetris(QWidget *parent = Q_NULLPTR);

public slots:
	void processOver();

protected:
	void closeEvent(QCloseEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;

private:
	void loadMusic();

private:
	TRender* render;
	TLogic* logic;

	bool overKeys;
	GameOver* over;

	InfoBox* info;

	QLabel* background;
	QLabel* border;

	QMediaPlayer player;
	QMediaPlaylist playlist;

	const int blockSize = 30;
	const int gameHeight = 20;
	const int gameWidth = 10;

signals:
	void setKey(int);
	void gameOver();
	void exit();
};
