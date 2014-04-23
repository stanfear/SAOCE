#include "associationlist.h"
#include <QPair>
#include <QList>
#include <iostream>
#include <QtGui>
#include "AssociationList.h"

double AssociationList::GetGeneralCost()
{
    double Cost = 0;
    return Cost;
}

bool AssociationList::IsSolutionValide()
{
    return true;
}

int AssociationList::CountDriversAssociation(Participant* participant)
{
    int nb = 0;
    for( int i=this->_list->count()-1; i>=0; i--)
    {
        Association *assoc = this->_list->at(i);
        if(assoc->GetDriver() == participant)
            nb ++;
    }
    return nb;
}




AssociationList::AssociationList(const QStringList &headers, const QString &/*data*/,
                     QObject *parent)
    : QAbstractItemModel(parent)
{
    _list = new QList<Association*> ();
    std::clog << "Association List : Instantiating\n";


    _rootData.clear();
    foreach (QString header, headers)
        _rootData << header;

    rootItem = new TreeItemParticipant(_rootData);
}

AssociationList::~AssociationList()
{
    delete rootItem;

    std::clog << "Association List : Start clearing data (" << _list->count() << " elements to wipe)\n";
    for( int i=_list->count()-1; i>=0; i--)
    {
        delete _list->at(i);
        _list->removeAt(i);
    }
    delete _list;
    std::clog << "Association List : End clearing data\n";
}


int AssociationList::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
}

QVariant AssociationList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItemParticipant *item = getItem(index);

    return item->data(index.column());
}

Qt::ItemFlags AssociationList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

TreeItemParticipant *AssociationList::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItemParticipant *item = static_cast<TreeItemParticipant*>(index.internalPointer());
        if (item) return item;
    }
    return rootItem;
}

QVariant AssociationList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex AssociationList::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    TreeItemParticipant *parentItem = getItem(parent);

    TreeItemParticipant *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

bool AssociationList::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool AssociationList::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItemParticipant *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

QModelIndex AssociationList::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItemParticipant *childItem = getItem(index);
    TreeItemParticipant *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool AssociationList::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool AssociationList::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItemParticipant *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

int AssociationList::rowCount(const QModelIndex &parent) const
{
    TreeItemParticipant *parentItem = getItem(parent);

    return parentItem->childCount();
}

bool AssociationList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItemParticipant *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool AssociationList::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}


void AssociationList::UpdateDataFromScratch()
{
    QList<Participant*> alreadyShownedParticipants;
    Participant* currentParticipant;

    //vider la liste
    delete rootItem;
    rootItem = new TreeItemParticipant(_rootData);

    for( int i=this->_list->count()-1; i>=0; i--)
    {
        Association *assoc = this->_list->at(i);
        if(!alreadyShownedParticipants.contains(assoc->GetDriver()))
        {
            currentParticipant = assoc->GetDriver();
            QVector<QVariant> data;
            data << currentParticipant->GetFullName();
            data << currentParticipant->GetDisponnibilityString(0);

            rootItem->insertChildren(rootItem->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < data.size(); ++column)
                rootItem->child(rootItem->childCount() - 1)->setData(column, data[column]);

            TreeItemParticipant *parent = rootItem->child(rootItem->childCount() - 1);

            for( int j=i; j>=0; j--)
            {
                assoc = this->_list->at(j);
                if(assoc->GetDriver() == currentParticipant)
                {
                    parent->insertChildren(parent->childCount(), 1, 1);
                    parent->child(parent->childCount() - 1)->setData(0, assoc->GetPassenger()->GetFullName());
                }
            }
            alreadyShownedParticipants << currentParticipant;
        }
    }
}


