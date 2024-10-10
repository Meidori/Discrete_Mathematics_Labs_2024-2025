#ifndef SETCALCULATOR_H
#define SETCALCULATOR_H

#include <QMainWindow>
#include <QRegularExpression>
#include <unordered_map>
#include <stack>

#include "editsets.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SetCalculator;
}
QT_END_NAMESPACE

class SetCalculator : public QMainWindow
{
    Q_OBJECT

public:
    SetCalculator(QWidget *parent = nullptr);
    ~SetCalculator();

    void add();
    void del();
    void edit();
    void updateOutput();

    QVector<int> unionSets(const QVector<int>& set1, const QVector<int>& set2);
    QVector<int> intersectionSets(const QVector<int>& set1, const QVector<int>& set2);
    QVector<int> differenceSets(const QVector<int>& set1, const QVector<int>& set2);
    QVector<int> symmetricSets(const QVector<int>& set1, const QVector<int>& set2);
    QVector<int> complementSets(const QVector<int>& universalSet, const QVector<int>& subset);

    void calcByFormula();
    QVector<QString> processExpression(QString input);
    void save();

private:
    Ui::SetCalculator *ui;
    QVector<int> universum;
    std::unordered_map<QString, QVector<int>*> sets;

};
#endif // SETCALCULATOR_H
