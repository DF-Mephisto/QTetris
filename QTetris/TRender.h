#pragma once
#include <QtWidgets>

#include "BlockColor.h"
#include "TLogic.h"

class TRender : public QFrame
{
	Q_OBJECT

public:
	TRender(int blockSize, TLogic* logic, QWidget* parent = 0);

protected:
	void paintEvent(QPaintEvent* e) override;

public slots:
	void redraw();

private:
	QColor getColor(BlockColor type);

private:
	int blockSize;

	TLogic* logic;

};