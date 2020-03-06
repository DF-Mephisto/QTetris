#include "GameOver.h"

GameOver::GameOver(QWidget* parent) : QWidget(parent)
{
	int id = QFontDatabase::addApplicationFont(":/QTetris/tetris.ttf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	QFont font(family);

	QPixmap back(":/QTetris/gameover.jpg");
	background = new QLabel(this);
	background->setPixmap(back);
	background->move(0, 0);
	this->resize(back.size());

	text = new QLabel(this);
	text->setFont(font);
	text->setText(
		"<style>"
		"TEX{"
		"font-size: 30px;"
		"font-weight: bold;"
		"color: rgba(255, 255, 255, 0.8);"
		"}"
		"</style>"
		"<hr>"
		"<TEX>R - Restart</TEX>"
		"<br>"
		"<TEX>Esc - Exit</TEX>"
	);
	text->setAlignment(Qt::AlignCenter);
	text->setGeometry(0, height() - height() / 3, width(), height() / 3);
	QGraphicsDropShadowEffect* dse = new QGraphicsDropShadowEffect();
	dse->setBlurRadius(10);
	dse->setColor(QColor("#2EC1FF"));
	dse->setOffset(0);
	text->setGraphicsEffect(dse);
}

GameOver::~GameOver()
{
	
}

//SLOTS
void GameOver::resizeEvent(QResizeEvent* e)
{
	QSize size = e->size();
	background->setPixmap(QPixmap(":/QTetris/gameover.jpg").scaled(size));
	text->setGeometry(0, size.height() - size.height() / 3, size.width(), size.height() / 3);
}