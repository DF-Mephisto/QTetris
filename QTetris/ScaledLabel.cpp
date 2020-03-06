#include "ScaledLabel.h"

ScaledLabel::ScaledLabel(QPixmap pix, QWidget* parent) : QLabel(parent)
{
	this->pix = pix;
	setPixmap(this->pix.scaled(width(), height(), Qt::KeepAspectRatio));
}

//EVENTS
void ScaledLabel::resizeEvent(QResizeEvent* e)
{
	QLabel::resizeEvent(e);

	setPixmap(pix.scaled(e->size(), Qt::KeepAspectRatio));
}