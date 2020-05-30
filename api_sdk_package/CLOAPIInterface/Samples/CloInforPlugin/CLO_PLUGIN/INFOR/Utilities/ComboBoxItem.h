#ifndef COMBOBOXITEM_H
#define COMBOBOXITEM_H

#include <QtGui>

class ComboBoxItem : public QComboBox
{
    Q_OBJECT

private:
    QTreeWidgetItem* item;
    int column;

public:
    ComboBoxItem(QTreeWidgetItem*, int);

public slots:
    void changeText(const QString& text);

};



#endif 