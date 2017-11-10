#include "circleitem.h"

circleItem::circleItem(circleParams params, QObject *parent)
	:MoveItem(parent),_params(params)
{
	connect(this, &circleItem::positionIsSet, this, &circleItem::on_positionIsSet);
	setParams(params);
}

circleItem::~circleItem(){}

int circleItem::getRadius() const
{
	return this->_params.radius;
}

QRectF circleItem::boundingRect() const
{
	auto rad = getRadius();
	return QRectF(-rad, -rad, 2*rad, 2*rad);
}

void circleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen = QPen(Qt::black);
	pen.setWidth(1);
	painter->setPen(pen);
	painter->setBrush(Qt::blue);
	auto rad = getRadius();
	painter->drawEllipse(QPoint(0,0), rad, rad);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

QString circleItem::getType()
{
	return QString("circle");
}

circleParams circleItem::getParams()
{
	return this->_params;
}

void circleItem::on_positionIsSet()
{
	auto params = _params;
	params.x = this->pos().toPoint().x();
	params.y = this->pos().toPoint().y();
	setParams(params);
}

void circleItem::setParams(circleParams params)
{
	auto prevBoundingRect = boundingRect();
	bool name_has_changed = 0;
	if (params.name != _params.name)
		name_has_changed = 1;
	_params = params;
	auto newCoordinates = QPointF(_params.x, _params.y);
	setPos(newCoordinates);
	auto curBoundingRect = boundingRect();
	if (name_has_changed)
		emit nameChanged(this);
	emit paramsChanged(_params);
	if (this->scene())
	{
		this->scene()->update(mapRectToScene(prevBoundingRect));
		this->scene()->update(mapRectToScene(curBoundingRect));
	}}
