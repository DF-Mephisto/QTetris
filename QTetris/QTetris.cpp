#include "QTetris.h"

QTetris::QTetris(QWidget *parent): QWidget(parent)
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
	setFixedSize(blockSize * gameWidth * 2, blockSize * gameHeight);
	background = new QLabel(this);
	background->setPixmap(QPixmap(":/QTetris/back.jpg").scaled(width(), height()));

	logic = new TLogic(gameWidth, gameHeight, this);
	render = new TRender(blockSize, logic, this);
	render->setGeometry(0, 0, gameWidth * blockSize, gameHeight * blockSize);

	over = new GameOver(this);
	over->resize(width() - width() / 5, height() - height() / 5);
	over->move(width() / 2 - over->width() / 2, height() / 2 - over->height() / 2);
	over->hide();
	overKeys = false;

	info = new InfoBox(this);
	info->setGeometry(width() / 2 + 1, 0, width() / 2, height());

	border = new QLabel(this);
	border->setStyleSheet("background-color: black;");
	border->setGeometry(width() / 2, 0, 3, height());

	connect(logic, SIGNAL(redraw()), render, SLOT(redraw()));
	connect(logic, SIGNAL(over()), this, SLOT(processOver()));
	connect(logic, SIGNAL(levelChanged(int)), info, SLOT(setLevel(int)));
	connect(logic, SIGNAL(scoreChanged(int)), info, SLOT(setScore(int)));
	connect(this, SIGNAL(gameOver()), logic, SLOT(setGameOver()));
	connect(this, SIGNAL(setKey(int)), logic, SLOT(getKey(int)));
	connect(this, SIGNAL(exit()), QApplication::instance(), SLOT(quit()));

	logic->start();
	loadMusic();
}

void QTetris::loadMusic()
{
	playlist.addMedia(QUrl("qrc:/QTetris/theme.mp3"));
	playlist.setPlaybackMode(QMediaPlaylist::Loop);

	player.setPlaylist(&playlist);
	player.play();
}

//SLOTS
void QTetris::processOver()
{
	over->show();
	over->raise();
	overKeys = true;
}

//EVENTS
void QTetris::keyPressEvent(QKeyEvent *event)
{
	switch (int k = event->key())
	{
		case Qt::Key_Down:
		case Qt::Key_Right:
		case Qt::Key_Left:
		case Qt::Key_Space:
		{
			emit setKey(k);
			break;
		}

		case Qt::Key_Escape:
		{
			if (overKeys)
			{
				emit exit();
			}
			break;
		}

		case Qt::Key_R:
		case 1050:
		{
			if (overKeys)
			{
				overKeys = false;
				over->hide();
				logic->start();
			}
			break;
		}

		default:
			QWidget::keyPressEvent(event);
			break;
	}
}

void QTetris::closeEvent(QCloseEvent *event)
{
	emit gameOver();
	logic->wait();
}