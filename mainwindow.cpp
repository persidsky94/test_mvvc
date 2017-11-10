#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QDialogButtonBox>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	bindActions();
	setDefaultSquareParams();
	setDefaultCircleParams();
	_listManager = new itemListManager(this);
	_redManager = new redactorsManager(this);
	_scene = new GridScene(this);
	bindSceneAndRedactorsManager();
	bindSceneAndItemListManager();
	bindSelfAndItemListManager();
	this->ui->sceneW->layout()->addWidget(_listManager->getWidget());
	this->ui->sceneW->layout()->addWidget(_redManager->getWidget());
	ui->graphicsView->setScene(_scene);
}

void MainWindow::addNewSquareItem(squareParams params)
{
	auto square = new squareItem(params, this);
	addItemToScene(square);
	square->itemSelected(square);
}

void MainWindow::addNewCircleItem(circleParams params)
{
	auto circle = new circleItem(params, this);
	addItemToScene(circle);
	circle->itemSelected(circle);
}

void MainWindow::addItemToScene(MoveItem *item)
{
	_scene->addItem(item);
	bindItemToScene(item);
	emit itemAddedToScene(item);
}

void MainWindow::bindItemToScene(MoveItem *item)
{
	QObject::connect(item, &MoveItem::itemSelected, _scene, &GridScene::on_sceneItemSelected);
	QObject::connect(item, &MoveItem::nameChanged, _scene, &GridScene::on_itemNameChanged);
}

void MainWindow::bindSceneAndRedactorsManager()
{
	QObject::connect(_scene, &GridScene::sceneItemSelected, _redManager, &redactorsManager::changeRedactedItem);
}
void MainWindow::bindSelfAndItemListManager()
{
	QObject::connect(this, &MainWindow::itemAddedToScene, _listManager, &itemListManager::on_itemAddedToScene);
}

void MainWindow::bindSceneAndItemListManager()
{
	QObject::connect(_scene, &GridScene::sceneItemNameChanged, _listManager, &itemListManager::on_sceneItemNameChanged);
	QObject::connect(_scene, &GridScene::sceneItemSelected, _listManager, &itemListManager::on_itemOnSceneSelected);
	QObject::connect(_scene, &GridScene::sceneItemDeleted, _listManager, &itemListManager::on_itemOnSceneDeleted);
	QObject::connect(_listManager, &itemListManager::selectSceneItem, _scene, &GridScene::on_selectSceneItem);
	QObject::connect(_listManager, &itemListManager::deleteSceneItem, _scene, &GridScene::on_deleteSceneItem);
}

void MainWindow::setDefaultSquareParams()
{
	squareParams defaultParams;
	defaultParams.name = QString("square_name");
	defaultParams.x = 0;
	defaultParams.y = 0;
	defaultParams.density = 15;
	defaultParams.width = 15;
	_defaultSquareParams = defaultParams;
}

void MainWindow::setDefaultCircleParams()
{
	circleParams defaultCircleParams;
	defaultCircleParams.name = QString("circle_name");
	defaultCircleParams.x = 0;
	defaultCircleParams.y = 0;
	defaultCircleParams.density = 15;
	defaultCircleParams.radius = 25;
	defaultCircleParams.originality = 2;
	_defaultCircleParams = defaultCircleParams;
}

void MainWindow::on_actionAddSquare_triggered()
{
	auto dialog = new QDialog;
	auto layout = new QVBoxLayout(dialog);
	auto initRedactor = new squareRedactor(dialog);
	initRedactor->initWithParams(_defaultSquareParams);
	initRedactor->show();
	auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);
	layout->addWidget(initRedactor);
	layout->addWidget(buttonBox);
	connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
	if (dialog->exec())
	{
		auto params = initRedactor->constructParams();
		addNewSquareItem(params);
	}
	delete dialog;
}

void MainWindow::on_actionAddCircle_triggered()
{
	auto dialog = new QDialog;
	auto layout = new QVBoxLayout(dialog);
	auto initRedactor = new circleRedactor(dialog);
	initRedactor->initWithParams(_defaultCircleParams);
	initRedactor->show();
	auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);
	layout->addWidget(initRedactor);
	layout->addWidget(buttonBox);
	connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
	if (dialog->exec())
	{
		auto params = initRedactor->constructParams();
		addNewCircleItem(params);
	}
	delete dialog;
}

void MainWindow::bindActions()
{
	connect(this->ui->actionAddSquare, &QAction::triggered, this, &MainWindow::on_actionAddSquare_triggered);
	connect(this->ui->actionAddCircle, &QAction::triggered, this, &MainWindow::on_actionAddCircle_triggered);
}

MainWindow::~MainWindow()
{
	delete ui;
}
