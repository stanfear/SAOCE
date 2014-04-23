#include "participantslist.h"
#include <iostream>

bool ParticipantsList::Add(Participant* part)
{
    std::clog << "Participants List : Attempt to add Participants " << part->ToString();
    if(_list->contains(part))
    {
        std::clog << " ... Failed (participant already in the list)\n";
        return false;
    }
    else
    {
        _list->append(part);
        std::clog << " ... Succeded\n";
        return true;
    }
}





ParticipantsList::ParticipantsList(const QStringList &headers, const QString &/*data*/,
                     QObject *parent)
    : QAbstractItemModel(parent)
{
    _list = new QList<Participant*> ();
    std::clog << "Participants List : Instantiating\n";

    _rootData.clear();
    foreach (QString header, headers)
        _rootData << header;

    rootItem = new TreeItemParticipant(_rootData);
}

ParticipantsList::~ParticipantsList()
{
    delete rootItem;

    std::clog << "Participants List : Start clearing data (" << _list->count() << " elements to wipe)\n";
    for( int i=_list->count()-1; i>=0; i--)
    {
        delete _list->at(i);
        _list->removeAt(i);
    }
    delete _list;
    std::clog << "Participants List : End clearing data\n";
}


int ParticipantsList::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
}

QVariant ParticipantsList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItemParticipant *item = getItem(index);

    return item->data(index.column());
}

Qt::ItemFlags ParticipantsList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

TreeItemParticipant *ParticipantsList::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItemParticipant *item = static_cast<TreeItemParticipant*>(index.internalPointer());
        if (item) return item;
    }
    return rootItem;
}

QVariant ParticipantsList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex ParticipantsList::index(int row, int column, const QModelIndex &parent) const
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

bool ParticipantsList::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool ParticipantsList::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItemParticipant *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

QModelIndex ParticipantsList::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItemParticipant *childItem = getItem(index);
    TreeItemParticipant *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool ParticipantsList::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool ParticipantsList::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItemParticipant *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

int ParticipantsList::rowCount(const QModelIndex &parent) const
{
    TreeItemParticipant *parentItem = getItem(parent);

    return parentItem->childCount();
}

bool ParticipantsList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItemParticipant *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool ParticipantsList::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}


void ParticipantsList::UpdateDataFromScratch()
{
    //vider la liste
    delete rootItem;
    rootItem = new TreeItemParticipant(_rootData);

    for( int i= 0 ; i < this->_list->count(); i++)
    {
        Participant *part = this->_list->at(i);
        QVector<QVariant> data;
        data << part->GetFullName();
        data << part->GetAvailablesPlacesCount();


        rootItem->insertChildren(rootItem->childCount(), 1, rootItem->columnCount());
        for (int column = 0; column < data.size(); ++column)
            rootItem->child(rootItem->childCount() - 1)->setData(column, data[column]);

        TreeItemParticipant *parent = rootItem->child(rootItem->childCount() - 1);

        for (int j = 0 ; j < part->GetDipsonibilitiesCount(); j++)
        {
            parent->insertChildren(parent->childCount(), 1, 1);
            parent->child(parent->childCount() - 1)->setData(0, part->GetDisponnibilityString(j));
        }
    }
}


void ParticipantsList::RemoveParticipant(QModelIndex index)
{
    if(getItem(index)->parent()->equals(rootItem))
    this->_list->removeAt(index.row());
}
