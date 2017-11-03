#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "squareitem.h"
#include "circleitem.h"
#include "redactorsmanager.h"
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

private:
	Ui::MainWindow *ui;

	GridScene * _scene = NULL;
	redactorsManager *_redManager = NULL;
	squareParams _defaultSquareParams;
	circleParams _defaultCircleParams;

	void addNewSquareItem(squareParams params);
	void addNewCircleItem(circleParams params);
	void addItemToScene(MoveItem *item);
	void bindSceneAndRedactorsManager();
	void bindItemToScene(MoveItem *item);
	void bindActions();
	void setDefaultSquareParams();
	void setDefaultCircleParams();

	void on_actionAddSquare_triggered();
	void on_actionAddCircle_triggered();
};

#endif // MAINWINDOW_H
