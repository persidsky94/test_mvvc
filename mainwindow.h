#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "squareitem.h"
#include "circleitem.h"
#include "redactorsmanager.h"
#include "itemlistmanager.h"
#include "gridscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

signals:
	//for item list manager
	void itemAddedToScene(MoveItem *);

private:
	Ui::MainWindow *ui;

	GridScene * _scene = NULL;
	redactorsManager *_redManager = NULL;
	itemListManager *_listManager = NULL;
	squareParams _defaultSquareParams;
	circleParams _defaultCircleParams;

	void addNewSquareItem(squareParams params);
	void addNewCircleItem(circleParams params);
	void addItemToScene(MoveItem *item);
	void bindSceneAndRedactorsManager();
	void bindSceneAndItemListManager();
	void bindSelfAndItemListManager();
	void bindItemToScene(MoveItem *item);
	void bindActions();
	void setDefaultSquareParams();
	void setDefaultCircleParams();

	void on_actionAddSquare_triggered();
	void on_actionAddCircle_triggered();
};

#endif // MAINWINDOW_H
