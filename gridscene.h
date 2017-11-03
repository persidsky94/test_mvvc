#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QPointF>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "moveitem.h"

class GridScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit GridScene(qreal x, qreal y, qreal w, qreal h);
	explicit GridScene(QObject *parent);
	~GridScene(){}

	void on_sceneItemSelected(MoveItem *);

signals:
	void mouseAt(QPointF);
	void sceneItemSelected(MoveItem *);

private:
	void setBackgroundGrid();
	void drawBackground(QPainter *painter, const QRectF &rect);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRIDSCENE_H
