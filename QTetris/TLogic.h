#pragma once

#include <QtWidgets>
#include <random>

#include "BlockColor.h"
#include "Block.h"

class TLogic : public QThread
{
	Q_OBJECT

	enum command
	{
		left = -1, right = 1, down, rotate, idle
	};

public:
	TLogic(int width, int height, QObject* parent = 0);
	~TLogic();

	BlockColor** getLevel();
	int getWidth();
	int getHeight();

	void run() override;

private:
	void makeLevel();
	void clearLevel();
	Block getBlock();
	QPoint getStartPos(Block& block);
	bool testDownClash(Block& block, QPoint pos);
	bool testSideClash(Block& block, QPoint pos, command dir);
	bool testRotate(Block& block, QPoint pos);
	void moveBlock(Block& block, QPoint oldPos, QPoint newPos);
	void rotateBlock(Block& block, QPoint pos);
	void testLines(int line);
	void processLine(int line);
	void removeLine(int line);
	void testLevel();

private:
	int width;
	int height;
	int score;
	int curLevel;
	int delay;
	bool gameOver;

	BlockColor** level;
	command com;
	std::mt19937 gen;

	const int scorePerLine = 10;
	const int scoreLimit = 330;

public slots:
	void setGameOver();
	void getKey(int k);

signals:
	void redraw();
	void over();
	void scoreChanged(int);
	void levelChanged(int);
};