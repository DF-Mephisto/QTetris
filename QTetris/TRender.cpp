#include "TRender.h"

TRender::TRender(int blockSize, TLogic* logic, QWidget* parent) : QFrame(parent)
{
	this->blockSize = blockSize;
	this->logic = logic;
}

void TRender::redraw()
{
	repaint();
}

QColor TRender::getColor(BlockColor type)
{
	QColor color;

	switch (type)
	{
	case nocolor:
		color = QColor(125, 125, 125, 125);
		break;

	case red:
		color = Qt::red;
		break;

	case yellow:
		color = Qt::yellow;
		break;

	case orange:
		color = Qt::darkYellow;
		break;

	case purple:
		color = Qt::magenta;
		break;

	case green:
		color = Qt::darkGreen;
		break;

	case blue:
		color = Qt::blue;
		break;

	case cyan:
		color = Qt::cyan;
		break;

	case white:
		color = Qt::white;
		break;
	}

	return color;
}

void TRender::paintEvent(QPaintEvent* e)
{
	BlockColor** level = logic->getLevel();
	int width = logic->getWidth();
	int height = logic->getHeight();
	int x;
	int y;

	QPainter paint;
	paint.begin(this);
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			x = j * blockSize;
			y = i * blockSize;
			QColor color = getColor(level[i][j]);

			paint.setPen(Qt::NoPen);

			if (level[i][j] == nocolor)
			{
				paint.setBrush(QBrush(color));
				paint.drawRect(x, y, blockSize, blockSize);
			}
			else
			{
				QPolygon darkSide;
				darkSide << QPoint(x, y) << QPoint(x, y + blockSize) << QPoint(x + blockSize, y + blockSize);
				paint.setBrush(QBrush(color.darker()));
				paint.drawPolygon(darkSide);

				QPolygon lightSide;
				lightSide << QPoint(x, y) << QPoint(x + blockSize, y) << QPoint(x + blockSize, y + blockSize);
				paint.setBrush(QBrush(color.lighter()));
				paint.drawPolygon(lightSide);

				paint.setBrush(QBrush(color));
				int border = blockSize / 10;
				paint.drawRect(x + border, y + border, blockSize - border * 2, blockSize - border * 2);
			}
		}
	}

	paint.end();
}