#ifndef REDACTORSMANAGER_H
#define REDACTORSMANAGER_H

#include <moveitem.h>
#include <squareredactor.h>
#include <circleredactor.h>

class redactorsManager: public QObject
{
	Q_OBJECT
public:
	redactorsManager(QWidget *parent);
	QWidget *getWidget(){return _widget;}

	void changeRedactedItem(MoveItem *newItem);

private:
	MoveItem *redactedItem;
	QWidget *_widget;
	squareRedactor *squareRed;
	circleRedactor *circleRed;

	void unbindRedactedItem();
	void bindRedactedItem();
	void setRedactedItem(MoveItem *newItem);
	void hideActiveRedactor();
	void showActiveRedactor();
};

#endif // REDACTORSMANAGER_H
