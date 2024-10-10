#include "conditional.h"
#include "ui_conditional.h"

Conditional::Conditional(std::unordered_map<QString, QVector<int>*>& sets, QString setName, int size, QWidget *parent)
    : QDialog(parent), sets(sets), setName(setName), size(size)
    , ui(new Ui::Conditional)
{
    ui->setupUi(this);

    connect(ui->positiveBtn, &QPushButton::clicked, this, &Conditional::positive);
    connect(ui->negativeBtn, &QPushButton::clicked, this, &Conditional::negative);
    connect(ui->evenBtn, &QPushButton::clicked, this, &Conditional::even);
    connect(ui->oddBtn, &QPushButton::clicked, this, &Conditional::odd);
    connect(ui->multiplicityBtn, &QPushButton::clicked, this, &Conditional::multiplicity);
    connect(ui->rangeBtn, &QPushButton::clicked, this, &Conditional::range);
    connect(ui->backBtn, &QPushButton::clicked, this, &Conditional::close);
}

Conditional::~Conditional()
{
    delete ui;
}

void Conditional::positive()
{
    bool check;
    QString strx = ui->getxTextEdit->toPlainText();
    int x = strx.toInt(&check);
    if (check && (x > 0 || x < 51))
    {
        auto it = sets.find(setName);
        if (it != sets.end())
        {
            QVector<int>* set = new QVector<int>(size);
            set->clear();
            int value = x;
            for (int i = 0; i < size; i++)
            {
                set->append(value++);
                if (value == 51)
                {
                    qDebug() << "Неверный размер";
                    return;
                }
            }

            delete it->second;  // Освобождаем память от "множества", на которое указывает указатель
            it->second = set;
        }
    }
    else
    {
        qDebug() << "Неверное число x";
    }
}

void Conditional::negative()
{
    bool check;
    QString strx = ui->getxTextEdit->toPlainText();
    int x = strx.toInt(&check);
    if (check && (x < 0 || x > -51))
    {
        auto it = sets.find(setName);
        if (it != sets.end())
        {
            QVector<int>* set = new QVector<int>(size);
            set->clear();
            int value = x;
            for (int i = 0; i < size; i++)
            {
                set->append(value++);
                if (value == 0)
                {
                    qDebug() << "Неверный размер";
                    return;
                }
            }

            delete it->second;  // Освобождаем память от "множества", на которое указывает указатель
            it->second = set;
        }
    }
    else
    {
        qDebug() << "Неверное число x";
    }
}

void Conditional::even()
{
    bool check;
    QString strx = ui->getxTextEdit->toPlainText();
    int x = strx.toInt(&check);
    if (check && x % 2 == 0)
    {
        auto it = sets.find(setName);
        if (it != sets.end())
        {
            QVector<int>* set = new QVector<int>(size);
            set->clear();
            int value = x;
            for (int i = 0; i < size; i++)
            {
                set->append(value);
                value += 2;
                if (value == 52)
                {
                    qDebug() << "Неверный размер";
                    return;
                }
            }

            delete it->second;  // Освобождаем память от "множества", на которое указывает указатель
            it->second = set;
        }
    }
    else
    {
        qDebug() << "Неверное число x";
    }
}

void Conditional::odd()
{
    bool check;
    QString strx = ui->getxTextEdit->toPlainText();
    int x = strx.toInt(&check);
    if (check && x % 2 != 0)
    {
        auto it = sets.find(setName);
        if (it != sets.end())
        {
            QVector<int>* set = new QVector<int>(size);
            set->clear();
            int value = x;
            for (int i = 0; i < size; i++)
            {
                if (value != 0)
                {
                    set->append(value);
                }
                value += 2;
                if (value == 51)
                {
                    qDebug() << "Неверный размер";
                    return;
                }
            }

            delete it->second;  // Освобождаем память от "множества", на которое указывает указатель
            it->second = set;
        }
    }
    else
    {
        qDebug() << "Неверное число x";
    }

}

void Conditional::multiplicity()
{
    bool checky;
    QString stry = ui->getyTextEdit->toPlainText();
    int y = stry.toInt(&checky);

    bool checkx;
    QString strx = ui->getxTextEdit->toPlainText();
    int x = strx.toInt(&checkx);

    if (checkx && checky)
    {
        auto it = sets.find(setName);
        if (it != sets.end())
        {
            QVector<int>* set = new QVector<int>(size);
            set->clear();
            int value = x;
            for (int i = 0; i < size; )
            {
                if (value % y == 0)
                {
                    set->append(value);
                    i++;
                }
                if (++value == 51)
                {
                    qDebug() << "Неверный размер";
                    return;
                }
            }

            delete it->second;  // Освобождаем память от "множества", на которое указывает указатель
            it->second = set;
        }
    }
    else
    {
        qDebug() << "Неверное число x или y";
    }
}

void Conditional::range()
{
    bool checky;
    QString stry = ui->getyTextEdit->toPlainText();
    int y = stry.toInt(&checky);

    bool checkx;
    QString strx = ui->getxTextEdit->toPlainText();
    int x = strx.toInt(&checkx);

    if (checkx && checky && x < y && x > -51 && y < 51)
    {
        auto it = sets.find(setName);
        if (it != sets.end())
        {
            QVector<int>* set = new QVector<int>(size);
            set->clear();
            int value = x;
            for (int i = 0; i <= y - x; i++)
            {
                set->append(value);
                if (++value == 51)
                {
                    qDebug() << "Неверный размер";
                    return;
                }
            }

            delete it->second;  // Освобождаем память от "множества", на которое указывает указатель
            it->second = set;
        }
    }
    else
    {
        qDebug() << "Неверное число x или y";
    }
}
