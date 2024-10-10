#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include <QDialog>

namespace Ui {
class Conditional;
}

class Conditional : public QDialog
{
    Q_OBJECT

public:
    explicit Conditional(std::unordered_map<QString, QVector<int>*>& sets, QString setName, int size, QWidget *parent = nullptr);
    ~Conditional();

    void positive();
    void negative();
    void even();
    void odd();
    void multiplicity();
    void range();

private:
    Ui::Conditional *ui;

    std::unordered_map<QString, QVector<int>*>& sets;
    QString setName;
    int size;
};

#endif // CONDITIONAL_H
