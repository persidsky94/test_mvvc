#include "squareitem.h"

squareItem::squareItem(squareParams params, QObject *parent)
	:MoveItem(parent), _params(params)
{
	connect(this, &squareItem::positionIsSet, this, &squareItem::on_positionIsSet);
	setParams(params);
}

squareItem::~squareItem(){}

int squareItem::getSide() const
{
	return this->_params.width;
}

QRectF squareItem::boundingRect() const
{
	auto side = getSide();
	return QRectF(-side/2, -side/2, side, side);
}

void squareItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen = QPen(Qt::black);
	pen.setWidth(1);
	painter->setPen(pen);
	painter->setBrush(Qt::red);
	painter->drawRect(boundingRect());
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

QString squareItem::getType()
{
	return QString("square");
}

squareParams squareItem::getParams()
{
	return this->_params;
}

void squareItem::on_positionIsSet()
{
	auto params = _params;
	params.x = this->pos().toPoint().x();
	params.y = this->pos().toPoint().y();
	setParams(params);
}

void squareItem::setParams(squareParams params)
{
	auto prevBoundingRect = boundingRect();
	_params = params;
	auto newCoordinates = QPointF(_params.x, _params.y);
	setPos(newCoordinates);
	auto curBoundingRect = boundingRect();
	emit paramsChanged(_params);
	if (this->scene())
	{
		this->scene()->update(mapRectToScene(prevBoundingRect));
		this->scene()->update(mapRectToScene(curBoundingRect));
	}
}
