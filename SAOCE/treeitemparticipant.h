#ifndef TREEITEMPARTICIPANT_H
#define TREEITEMPARTICIPANT_H

#include <QList>
#include <QVariant>
#include <QVector>

class TreeItemParticipant
{
public:
    TreeItemParticipant(const QVector<QVariant> &data, TreeItemParticipant *parent = 0);
    ~TreeItemParticipant();
    TreeItemParticipant *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    TreeItemParticipant *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);

    bool equals(const TreeItemParticipant *);
private:
    QList<TreeItemParticipant*> childItems;
    QVector<QVariant> itemData;
    TreeItemParticipant *parentItem;
 };

#endif // TREEITEMPARTICIPANT_H
