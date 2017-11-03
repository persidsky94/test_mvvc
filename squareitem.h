#ifndef SQUAREITEM_H
#define SQUAREITEM_H

#include <moveitem.h>
#include <squareparams.h>

class squareItem: public MoveItem
{
	Q_OBJECT
public:
	explicit squareItem(squareParams params, QObject *parent);
	~squareItem();
	squareParams getParams();
	void setParams(squareParams params);

signals:
	void paramsChanged(squareParams params);

private:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QString getType();
	void on_positionIsSet();

	int getSide() const;

	squareParams _params;
};

#endif // SQUAREITEM_H
