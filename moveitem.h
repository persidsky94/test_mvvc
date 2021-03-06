#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <algorithm>

class MoveItem : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	explicit MoveItem(QObject *parent = 0);
	~MoveItem();
	virtual QString getType() = 0;
	virtual QString getName() = 0;
//	virtual void setPos(const QPointF &pos){((QGraphicsItem *)this)->setPos(pos); emit positionIsSet();}

signals:
	void itemSelected(MoveItem *);
	void itemDragged(MoveItem *);
	void positionIsSet();
	void nameChanged(MoveItem *);

private:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	virtual QPointF calculateValidCoordinates(QPointF mousePosition);

public slots:

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MOVEITEM_H
