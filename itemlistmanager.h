#ifndef ITEMLISTMANAGER_H
#define ITEMLISTMANAGER_H

#include <QObject>
#include <QListWidget>
#include <QPushButton>
#include <moveitem.h>

class itemListManager : public QObject
{
	Q_OBJECT
public:
	explicit itemListManager(QWidget *parent);
	QWidget *getWidget(){return _widget;}

signals:
	//for scene manager
	void itemInListSelected(MoveItem *sceneItemFromList);
	void deleteSceneItem(MoveItem *itemToDelete);
	void selectSceneItem(MoveItem *itemToSelect);

public slots:
	void on_itemAddedToScene(MoveItem *sceneItem);
	void on_itemOnSceneSelected(MoveItem *sceneItem);
	void on_itemOnSceneDeleted(MoveItem *sceneItem);
	void on_sceneItemNameChanged(MoveItem *sceneItem);

	//internal
	void on_deleteButtonClicked();
	void on_listItemSelected(QListWidgetItem *listItem);

private:
	MoveItem *selectedItem;
	QWidget *_widget;
	QListWidget *_listWidget;
	QPushButton *_deleteButton;
	const static int sceneItemPtrRole = 1;

	void bindDeleteButtonFunction();
	void bindItemFromListSelection();
	QListWidgetItem *findItemBySceneItemPointer(MoveItem *sceneItem);
	MoveItem *getSceneItemFromListItem(QListWidgetItem *listItem);

};

#endif // ITEMLISTMANAGER_H
