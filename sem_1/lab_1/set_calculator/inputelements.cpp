#include "inputelements.h"
#include "ui_inputelements.h"

InputElements::InputElements(std::unordered_map<QString, QVector<int>*>& sets, QString setName, int size, QWidget *parent)
    : QDialog(parent), sets(sets), setName(setName), size(size)
    , ui(new Ui::InputElements)
{
    ui->setupUi(this);

    connect(ui->saveBtn, &QPushButton::clicked, this, &InputElements::save);
    connect(ui->backBtn, &QPushButton::clicked, this, &InputElements::close);

    ui->infoTextEdit->setReadOnly(true);
}

InputElements::~InputElements()
{
    delete ui;
}

void InputElements::save()
{
    QString input = ui->inputTextEdit->toPlainText();
    processInput(input);
}

bool InputElements::processInput(const QString& input)
{
    QStringList numberStrings = input.split(", "); // Разбиваем строку по запятым + пробелу
    if (numberStrings.size() != size)
    {
        qDebug() << "Количество чисел не соответствует размеру.";
        return false;
    }

    auto it = sets.find(setName);
    if (it != sets.end())
    {
        delete it->second;  // Освобождаем память от "множества", на которое указывает указатель
        QVector<int>* set = new QVector<int>(size);

        set->clear(); // Очищаем результат перед заполнением

        bool check;
        for (const QString& numStr : numberStrings)
        {
            int number = numStr.toInt(&check); // Преобразуем строку в int
            if (!check || number < -50 || number > 50)
            {
                qDebug() << "Число" << numStr << "либо не является целым числом, либо не в диапазоне -50 до 50";
                return false;
            }
            set->append(number);
        }
        it->second = set;
        return true;
    }
    else
    {
        qDebug() << "Нет множества с таким именем";
        return false;
    }
}
