#ifndef EDITSETS_H
#define EDITSETS_H

#include <QDialog>
#include <QVector>
#include <QSet>
#include <QRandomGenerator>
#include <unordered_map>

#include "inputelements.h"
#include "conditional.h"

namespace Ui {
class EditSets;
}

class EditSets : public QDialog
{
    Q_OBJECT

public:
    explicit EditSets(std::unordered_map<QString, QVector<int>*>& sets, QString setName, QWidget *parent = nullptr);
    ~EditSets();

    void input();
    void conditional();
    void rand();
    void clear();

private:
    Ui::EditSets *ui;

    std::unordered_map<QString, QVector<int>*>& sets;
    QString setName;
};

#endif // EDITSETS_H
