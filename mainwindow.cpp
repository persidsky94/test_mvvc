#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "squareitem.h"
#include "circleitem.h"
#include "redactorsmanager.h"
#include "gridscene.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	auto *redManager = new redactorsManager(this);
	this->ui->sceneW->layout()->addWidget(redManager->getWidget());
	auto scene = new GridScene(this);

	squareParams defaultParams;
	defaultParams.name = QString("square_name");
	defaultParams.x = 15;
	defaultParams.y = 15;
	defaultParams.density = 15;
	defaultParams.width = 15;

	circleParams defaultCircleParams;
	defaultCircleParams.name = QString("circle_name");
	defaultCircleParams.x = 0;
	defaultCircleParams.y = 0;
	defaultCircleParams.density = 15;
	defaultCircleParams.radius = 25;
	defaultCircleParams.originality = 2;

	auto square1 = new squareItem(defaultParams, this);
	auto square2 = new squareItem(defaultParams, this);
	auto circle1 = new circleItem(defaultCircleParams, this);
	auto circle2 = new circleItem(defaultCircleParams, this);
	scene->addItem(square1);
	scene->addItem(square2);
	scene->addItem(circle1);
	scene->addItem(circle2);
	ui->graphicsView->setScene(scene);
	QObject::connect(square1, &MoveItem::itemSelected, scene, &GridScene::on_sceneItemSelected);
	QObject::connect(square2, &MoveItem::itemSelected, scene, &GridScene::on_sceneItemSelected);
	QObject::connect(circle1, &MoveItem::itemSelected, scene, &GridScene::on_sceneItemSelected);
	QObject::connect(circle2, &MoveItem::itemSelected, scene, &GridScene::on_sceneItemSelected);
	QObject::connect(scene, &GridScene::sceneItemSelected, redManager, &redactorsManager::changeRedactedItem);

}

MainWindow::~MainWindow()
{
	delete ui;
}
