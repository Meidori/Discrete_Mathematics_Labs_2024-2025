#ifndef INPUTELEMENTS_H
#define INPUTELEMENTS_H

#include <QDialog>

namespace Ui {
class InputElements;
}

class InputElements : public QDialog
{
    Q_OBJECT

public:
    explicit InputElements(std::unordered_map<QString, QVector<int>*>& sets, QString setName, int size, QWidget *parent = nullptr);
    ~InputElements();

    void save();
    bool processInput(const QString& input);

private:
    Ui::InputElements *ui;

    std::unordered_map<QString, QVector<int>*>& sets;
    QString setName;
    int size;
};

#endif // INPUTELEMENTS_H
