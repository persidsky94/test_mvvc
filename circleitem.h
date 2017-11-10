#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include <moveitem.h>
#include <circleparams.h>

class circleItem: public MoveItem
{
	Q_OBJECT
public:
	explicit circleItem(circleParams params, QObject *parent);
	~circleItem();
	circleParams getParams();
	void setParams(circleParams params);
	QString getName() {return getParams().name;}

signals:
	void paramsChanged(circleParams params);

private:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QString getType();
	void on_positionIsSet();

	int getRadius() const;

	circleParams _params;
};

#endif // CIRCLEITEM_H
