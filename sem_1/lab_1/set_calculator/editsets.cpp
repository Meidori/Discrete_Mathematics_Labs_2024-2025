#include "editsets.h"
#include "ui_editsets.h"

EditSets::EditSets(std::unordered_map<QString, QVector<int>*>& sets, QString setName, QWidget *parent)
    : QDialog(parent), sets(sets), setName(setName)
    , ui(new Ui::EditSets)
{
    ui->setupUi(this);

    connect(ui->inputBtn, &QPushButton::clicked, this, &EditSets::input);
    connect(ui->randomBtn, &QPushButton::clicked, this, &EditSets::rand);
    connect(ui->conditionalBtn, &QPushButton::clicked, this, &EditSets::conditional);
    connect(ui->voidBtn, &QPushButton::clicked, this, &EditSets::clear);
    connect(ui->backBtn, &QPushButton::clicked, this, &EditSets::close);
}

EditSets::~EditSets()
{
    delete ui;
}

void EditSets::input()
{
    QString getSize = ui->sizeTextEdit->toPlainText();
    bool check;
    int size = getSize.toInt(&check);

    if (check)
    {
        if (size > 0)
        {
            InputElements inputWindow(sets, setName, size);
            inputWindow.setModal(true);
            inputWindow.exec();
        }
    }
    else
    {
        qDebug() << "Неверный формат для размера множества";
    }
}

void EditSets::rand()
{
    QString getSize = ui->sizeTextEdit->toPlainText();
    bool check;
    int size = getSize.toInt(&check);

    if (check)
    {
        if (size > 0 && size < 102)
        {
            auto it = sets.find(setName);
            if (it != sets.end())
            {
                QSet<int> generatedNumbers; // Используем QSet для уникальных значений

                while (generatedNumbers.size() < size) // Генерируем до достижения нужного размера
                {
                    int randomNumber = QRandomGenerator::global()->bounded(-50, 51); // генерируем число от -50 до 50
                    generatedNumbers.insert(randomNumber); // Добавляем в QSet
                }

                QVector<int>* newSet = new QVector<int>(generatedNumbers.begin(), generatedNumbers.end()); // Создаем QVector из QSet

                delete it->second; // Освобождаем старый набор
                it->second = newSet; // Устанавливаем новый набор
            }
        }
        else
        {
            qDebug() << "Размер множества должен быть больше 0 и не больше 101";
        }
    }
    else
    {
        qDebug() << "Неверный формат для размера множества";
    }
}

void EditSets::conditional()
{
    QString getSize = ui->sizeTextEdit->toPlainText();
    bool check;
    int size = getSize.toInt(&check);
    if (check)
    {
        if (size > 0)
        {
            Conditional conditionalWindow(sets, setName, size);
            conditionalWindow.setModal(true);
            conditionalWindow.exec();
        }
        else
        {
            qDebug() << "Размер множества должен быть больше 0";
        }
    }
    else
    {
        qDebug() << "Неверный формат для размера множества";
    }

}

void EditSets::clear()
{
    auto it = sets.find(setName);
    delete it->second;
    QVector<int>* newSet = new QVector<int>;
    it->second = newSet;
}
