#pragma once

#include <QtWidgets>

class ScaledLabel : public QLabel
{
	Q_OBJECT

public:
	ScaledLabel(QPixmap pix, QWidget* parent = 0);

protected:
	void resizeEvent(QResizeEvent* e) override;

private:
	QPixmap pix;
};