#pragma once
#include "ComboBoxItem.h"
#include "CLO_PLUGIN/INFOR/Utilities/Utility.h"
#include "CLOAPIInterface/CLOAPIInterface.h"

ComboBoxItem::ComboBoxItem(QTreeWidgetItem* item, int column)
{
    this->item = item;
    this->column = column;
}
/*
* Private Slot, which gets called in Connect statments
*/
void ComboBoxItem::changeText(const QString& text)
{
	Utility::CustomMessageBox("Combobox changeText ::" + text.toStdString());
}

