#include "itemlistmanager.h"
#include <QVBoxLayout>



itemListManager::itemListManager(QWidget *parent)
{
	_widget = new QWidget(parent);
	_listWidget = new QListWidget();
	_deleteButton = new QPushButton(QString("delete"));
	auto layout = new QVBoxLayout;
	layout->addWidget(_listWidget);
	layout->addWidget(_deleteButton);
	_listWidget->show();
	_widget->setLayout(layout);
	bindDeleteButtonFunction();
	bindItemFromListSelection();
}

void itemListManager::on_itemAddedToScene(MoveItem *sceneItem)
{
	auto listItem = new QListWidgetItem();
	listItem->setText(sceneItem->getName());
	QVariant listItemData = qVariantFromValue((void *) sceneItem);
	listItem->setData(sceneItemPtrRole, listItemData);
	_listWidget->insertItem(0, listItem);
}

QListWidgetItem *itemListManager::findItemBySceneItemPointer(MoveItem *sceneItem)
{
	auto listItemsNumber = _listWidget->count();
	QListWidgetItem *listItem = NULL;
	for (int i=0; i<listItemsNumber; ++i)
	{
		listItem = _listWidget->item(i);
		auto sceneItemFromListItem = getSceneItemFromListItem(listItem);
		if (sceneItemFromListItem == sceneItem)
			return listItem;
	}
	return NULL;
}

MoveItem *itemListManager::getSceneItemFromListItem(QListWidgetItem *listItem)
{
	return (MoveItem *)(listItem->data(sceneItemPtrRole).value<void *>());
}

void itemListManager::on_itemOnSceneSelected(MoveItem *sceneItem)
{
	auto listItem = findItemBySceneItemPointer(sceneItem);
	_listWidget->setCurrentItem(listItem);
	listItem->setSelected(1);
}

void itemListManager::on_itemOnSceneDeleted(MoveItem *sceneItem)
{
	auto listItem = findItemBySceneItemPointer(sceneItem);
	auto row =_listWidget->row(listItem);
	auto removedItem = _listWidget->takeItem(row);
	//free removedItem; //not safe?
}

void itemListManager::on_sceneItemNameChanged(MoveItem *sceneItem)
{
	auto listItem = findItemBySceneItemPointer(sceneItem);
	listItem->setText(sceneItem->getName());
}

void itemListManager::on_deleteButtonClicked()
{
	auto listItem = _listWidget->currentItem();
	auto sceneItem = getSceneItemFromListItem(listItem);
	emit deleteSceneItem(sceneItem);
}

void itemListManager::on_listItemSelected(QListWidgetItem *listItem)
{
	auto sceneItem = getSceneItemFromListItem(listItem);
	emit selectSceneItem(sceneItem);
}

void itemListManager::bindDeleteButtonFunction()
{
	QObject::connect(_deleteButton, &QPushButton::clicked, this, &itemListManager::on_deleteButtonClicked);
}
void itemListManager::bindItemFromListSelection()
{
	QObject::connect(_listWidget, &QListWidget::itemClicked, this, &itemListManager::on_listItemSelected);
}
