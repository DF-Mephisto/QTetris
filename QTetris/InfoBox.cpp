#include "InfoBox.h"

InfoBox::InfoBox(QWidget* parent) : QWidget(parent)
{
	logo = new ScaledLabel(QPixmap(":/QTetris/tetlogo.png"));

	int id = QFontDatabase::addApplicationFont(":/QTetris/tetris.ttf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	QFont font(family);

	QString labelStyle = "font-size: 30px; font-weight: bold; color: rgba(255, 255, 255, 0.8);";
	QGraphicsDropShadowEffect* dse = new QGraphicsDropShadowEffect();
	dse->setBlurRadius(10);
	dse->setColor(QColor("#2EC1FF"));
	dse->setOffset(0);

	scoreLabel = new QLabel("score:");
	scoreLabel->setFont(font);
	scoreLabel->setAlignment(Qt::AlignCenter);
	scoreLabel->setStyleSheet(labelStyle);
	scoreLabel->setGraphicsEffect(dse);

	levelLabel = new QLabel("level:");
	levelLabel->setFont(font);
	levelLabel->setAlignment(Qt::AlignCenter);
	levelLabel->setStyleSheet(labelStyle);
	levelLabel->setGraphicsEffect(dse);

	QString counterStyle = "font-size: 25px; font-weight: bold; background-color: rgba(255, 255, 255, 0.7); border: 3px solid black;";
	score = new QLabel("0");
	score->setFont(font);
	score->setAlignment(Qt::AlignCenter);
	score->setStyleSheet(counterStyle);

	level = new QLabel("0");
	level->setFont(font);
	level->setAlignment(Qt::AlignCenter);
	level->setStyleSheet(counterStyle);
	
	layout = new QVBoxLayout();
	layout->addWidget(logo);
	layout->addWidget(scoreLabel);
	layout->insertSpacing(2, -20);
	layout->addWidget(score);
	layout->addWidget(levelLabel);
	layout->insertSpacing(5, -20);
	layout->addWidget(level);
	this->setLayout(layout);
}

//SLOTS
void InfoBox::setScore(int score)
{
	this->score->setText(QString::number(score));
}

void InfoBox::setLevel(int level)
{
	this->level->setText(QString::number(level));
}