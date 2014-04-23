#include <QStringList>

#include "treeitemparticipant.h"

TreeItemParticipant::TreeItemParticipant(const QVector<QVariant> &data, TreeItemParticipant *parent)
{
    parentItem = parent;
    itemData = data;
}

TreeItemParticipant::~TreeItemParticipant()
{
    qDeleteAll(childItems);
}

TreeItemParticipant *TreeItemParticipant::child(int number)
{
    return childItems.value(number);
}

int TreeItemParticipant::childCount() const
{
    return childItems.count();
}

int TreeItemParticipant::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItemParticipant*>(this));

    return 0;
}

int TreeItemParticipant::columnCount() const
{
    return itemData.count();
}

QVariant TreeItemParticipant::data(int column) const
{
    return itemData.value(column);
}

bool TreeItemParticipant::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
    {
        QVector<QVariant> data(columns);
        TreeItemParticipant *item = new TreeItemParticipant(data, this);
        childItems.insert(position, item);
    }

    return true;
}

bool TreeItemParticipant::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach (TreeItemParticipant *child, childItems)
        child->insertColumns(position, columns);

    return true;
}

TreeItemParticipant *TreeItemParticipant::parent()
{
    return parentItem;
}

bool TreeItemParticipant::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}

bool TreeItemParticipant::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    foreach (TreeItemParticipant *child, childItems)
        child->removeColumns(position, columns);

    return true;
}

bool TreeItemParticipant::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}

bool TreeItemParticipant::equals(const TreeItemParticipant *other)
{
    return (itemData == other->itemData);
}
