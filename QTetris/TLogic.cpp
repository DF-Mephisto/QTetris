#include "TLogic.h"

TLogic::TLogic(int width, int height, QObject* parent) : QThread(parent)
{
	this->width = width;
	this->height = height;

	level = new BlockColor*[height];
	for (int i = 0; i < height; i++)
		level[i] = new BlockColor[width];

	gen.seed(QDateTime::currentMSecsSinceEpoch());
}

TLogic::~TLogic()
{
	for (int i = 0; i < height; i++)
		delete[] level[i];
	delete[] level;
}

void TLogic::clearLevel()
{
	gameOver = false;

	curLevel = 0;
	score = 0;
	emit levelChanged(curLevel);
	emit scoreChanged(score);

	delay = 50;
	com = idle;
	makeLevel();
}

void TLogic::makeLevel()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			level[i][j] = nocolor;
		}
	}
}


void TLogic::run()
{
	clearLevel();

	Block curBlock = getBlock();
	QPoint pos = getStartPos(curBlock);

	while (!gameOver)
	{
		if (!testDownClash(curBlock, pos))
		{
			QPoint newPos(pos.x(), pos.y() + 1);
			moveBlock(curBlock, pos, newPos);
			pos = newPos;
			emit redraw();
		}
		else
		{
			if (pos.y() < 0)
			{
				gameOver = true;
				emit over();
				break;
			}

			testLines(pos.y());

			curBlock = getBlock();
			pos = getStartPos(curBlock);
			com = idle;
			continue;
		}

		//USER INPUT HANDLING
		for (int i = 0; i < delay; i++)
		{
			QThread::msleep(20);

			if (com == down)
			{
				com = idle;
				break;
			}
			else if (com == left || com == right)
			{
				if (!testSideClash(curBlock, pos, com))
				{
					QPoint newPos(pos.x() + com, pos.y());
					moveBlock(curBlock, pos, newPos);
					pos = newPos;
					emit redraw();
				}
			}
			else if (com == rotate)
			{
				if (testRotate(curBlock, pos))
				{
					rotateBlock(curBlock, pos);
					emit redraw();
				}
			}

			com = idle;
		}
		
	}
}

Block TLogic::getBlock()
{
	vector<Block> blocks = Registry::getRegistry();

	Block res = blocks[gen() % blocks.size()];
	return res;
}

QPoint TLogic::getStartPos(Block& block)
{
	char** matr = block.getBlock();
	QPoint pos(width / 2 - 1, 0);

	for (int i = 3; i >= 0; i--)
		for (int j = 0; j < 4; j++)
			if (matr[i][j])
			{
				pos.setY(0 - i - 1);
				return pos;
			}

	return pos;
}

bool TLogic::testDownClash(Block& block, QPoint pos)
{
	char** matr = block.getBlock();
	int x = pos.x();
	int y = pos.y() + 1;

	if (y > height - 1) return true;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (matr[j][i])
			{
				if (y + j < 0) break;

				if (y + j > height - 1 || level[y + j][x + i] != nocolor) return true;
				break;
			}
		}
	}

	return false;
}

bool TLogic::testSideClash(Block& block, QPoint pos, command dir)
{
	char** matr = block.getBlock();
	int x = pos.x() + dir;
	int y = pos.y();

	if (x < 0 || x > width - 1) return true;

	int startDir = dir == left ? 0 : 3;

	for (int i = 0; i < 4; i++)
	{
		for (int j = startDir; dir == left ? j < 4 : j >= 0; j -= dir)
		{
			if (matr[i][j])
			{
				if (x + j > width - 1 || x + j < 0) return true;

				if (y + i < 0) break;

				if (level[y + i][x + j] != nocolor) return true;
				break;
			}
		}
	}

	return false;
}

bool TLogic::testRotate(Block& block, QPoint pos)
{
	Block tempBlock = block;
	tempBlock.rotateBy90();

	char** matr = block.getBlock();
	char** tempMatr = tempBlock.getBlock();
	int x = pos.x();
	int y = pos.y();

	for (int i = 0; i < 4; i++)
	{
		if (y + i < 0) continue;

		for (int j = 0; j < 4; j++)
		{
			if (tempMatr[i][j] && !matr[i][j])
			{
				if (x + j < 0 || x + j > width - 1 || y + i > height - 1 || level[y + i][x + j] != nocolor) return false;
			}
		}
	}

	return true;
}

void TLogic::moveBlock(Block& block, QPoint oldPos, QPoint newPos)
{
	char** matr = block.getBlock();

	for (int i = 0; i < 4; i++)
	{
		if (oldPos.y() + i < 0) continue;

		for (int j = 0; j < 4; j++)
			if (matr[i][j]) level[oldPos.y() + i][oldPos.x() + j] = nocolor;
	}

	for (int i = 0; i < 4; i++)
	{
		if (newPos.y() + i < 0) continue;

		for (int j = 0; j < 4; j++)
			if (matr[i][j]) level[newPos.y() + i][newPos.x() + j] = block.getColor();
	}
}

void TLogic::rotateBlock(Block& block, QPoint pos)
{
	char** matr = block.getBlock();

	for (int i = 0; i < 4; i++)
	{
		if (pos.y() + i < 0) continue;

		for (int j = 0; j < 4; j++)
			if (matr[i][j]) level[pos.y() + i][pos.x() + j] = nocolor;
	}

	block.rotateBy90();

	for (int i = 0; i < 4; i++)
	{
		if (pos.y() + i < 0) continue;

		for (int j = 0; j < 4; j++)
			if (matr[i][j]) level[pos.y() + i][pos.x() + j] = block.getColor();
	}
}

void TLogic::testLines(int line)
{
	bool shouldRemove;
	int completedLines = 0;

	for (int i = 0; i < 4; i++)
	{
		if (line + i < 0 || line + i > height - 1) continue;

		shouldRemove = true;

		for (int j = 0; j < width; j++)
		{
			if (level[line + i][j] != nocolor) continue;

			shouldRemove = false;
			break;
		}

		if (shouldRemove)
		{
			completedLines++;
			processLine(line + i);
		}
	}

	if (completedLines)
	{
		emit scoreChanged(score += completedLines * scorePerLine * completedLines);
		testLevel();
	}
}

void TLogic::processLine(int line)
{
	BlockColor* lineColors = new BlockColor[width];
	for (int i = 0; i < width; i++) lineColors[i] = level[line][i];

	bool whitey = true;

	for (int j = 0; j < 6; j++)
	{
		if (whitey) for (int i = 0; i < width; i++) level[line][i] = white;
		else for (int i = 0; i < width; i++) level[line][i] = lineColors[i];

		whitey = !whitey;

		emit redraw();
		QThread::msleep(100);
	}

	removeLine(line);

	delete lineColors;
}

void TLogic::removeLine(int line)
{
	for (int i = line; i > 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			level[i][j] = level[i - 1][j];
		}
	}

	for (int i = 0; i < width; i++) level[0][i] = nocolor;
	emit redraw();
}

void TLogic::testLevel()
{
	if (score >= scoreLimit + scoreLimit * curLevel && delay > 5)
	{
		delay -= 5;
		curLevel++;
		emit levelChanged(curLevel);
	}
}

//SLOTS
void TLogic::getKey(int k)
{
	switch (k)
	{
		case Qt::Key_Down:
			com = down;
			break;

		case Qt::Key_Left:
			com = left;
			break;

		case Qt::Key_Right:
			com = right;
			break;

		case Qt::Key_Space:
			com = rotate;
			break;
	}
}

void TLogic::setGameOver()
{
	gameOver = true;
}

//GETTERS SETTERS
int TLogic::getWidth()
{
	return width;
}

int TLogic::getHeight()
{
	return height;
}

BlockColor** TLogic::getLevel()
{
	return level;
}