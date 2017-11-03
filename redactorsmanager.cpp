#include <stdio.h>
#include <iostream>
#include <QHBoxLayout>
#include "redactorsmanager.h"
#include "squareitem.h"
#include "circleitem.h"

redactorsManager::redactorsManager(QWidget *parent)
{
	_widget = new QWidget(parent);
	redactedItem = NULL;
	squareRed = new squareRedactor(this->getWidget());
	circleRed = new circleRedactor(this->getWidget());
	auto layout = new QHBoxLayout;
	layout->addWidget(squareRed);
	layout->addWidget(circleRed);
	squareRed->hide();
	circleRed->hide();
	_widget->setLayout(layout);
}

void redactorsManager::changeRedactedItem(MoveItem *newItem)
{
	unbindRedactedItem();
	hideActiveRedactor();
	setRedactedItem(newItem);
	bindRedactedItem();
	showActiveRedactor();
}

void redactorsManager::setRedactedItem(MoveItem *newItem)
{
	redactedItem = newItem;
}

void redactorsManager::hideActiveRedactor()
{
	if (redactedItem)
	{
		if (redactedItem->getType() == QString("square"))
		{
			squareRed->hide();
		}
		else if(redactedItem->getType() == QString("circle"))
		{
			circleRed->hide();
		}
		else
		{
			std::cout << "Unknown MoveItem type selected" << std::endl;
		}
	}
}

void redactorsManager::showActiveRedactor()
{
	if (redactedItem)
	{
		if (redactedItem->getType() == QString("square"))
		{
			squareRed->show();
		}
		else if(redactedItem->getType() == QString("circle"))
		{
			circleRed->show();
		}
		else
		{
			std::cout << "Unknown MoveItem type selected" << std::endl;
		}
	}
}

void redactorsManager::unbindRedactedItem()
{
	if (redactedItem)
	{
		if (redactedItem->getType() == QString("square"))
		{
			QObject::disconnect(this->squareRed, 0, 0, 0);
		}
		else if(redactedItem->getType() == QString("circle"))
		{
			QObject::disconnect(this->circleRed, 0, 0, 0);
		}
		else
		{
			std::cout << "Unknown MoveItem type selected" << std::endl;
		}
	}
}

void redactorsManager::bindRedactedItem()
{
	if (redactedItem)
	{
		if (redactedItem->getType() == QString("square"))
		{
			squareItem *sqrItem = dynamic_cast<squareItem *>(redactedItem);
			QObject::connect(sqrItem, &squareItem::paramsChanged, squareRed, &squareRedactor::initWithParams);
			QObject::connect(squareRed, &squareRedactor::setParams, sqrItem, &squareItem::setParams);
			squareRed->initWithParams(sqrItem->getParams());
		}
		else if(redactedItem->getType() == QString("circle"))
		{
			circleItem *crclItem = dynamic_cast<circleItem *>(redactedItem);
			QObject::connect(crclItem, &circleItem::paramsChanged, circleRed, &circleRedactor::initWithParams);
			QObject::connect(circleRed, &circleRedactor::setParams, crclItem, &circleItem::setParams);
			circleRed->initWithParams(crclItem->getParams());
		}
		else
		{
			std::cout << "Unknown MoveItem type selected" << std::endl;
		}
	}
	else
	{
		std::cout << "Couldn't bind redacted item because no item is redacted" << std::endl;
	}
}
