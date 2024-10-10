#include "setcalculator.h"
#include "./ui_setcalculator.h"

SetCalculator::SetCalculator(QWidget *parent)
    : QMainWindow(parent)
    , universum(101)    // инициализация вектора универсума
    , ui(new Ui::SetCalculator)
{
    ui->setupUi(this);

    ui->outputTextEdit->setReadOnly(true);
    ui->infoTextEdit->setReadOnly(true);
    ui->answerTextEdit->setReadOnly(true);

    connect(ui->addSetBtn, &QPushButton::clicked, this, &SetCalculator::add);
    connect(ui->delSetBtn, &QPushButton::clicked, this, &SetCalculator::del);
    connect(ui->editSetBtn, &QPushButton::clicked, this, &SetCalculator::edit);

    connect(ui->calcBtn, &QPushButton::clicked, this, &SetCalculator::calcByFormula);
    connect(ui->saveBtn, &QPushButton::clicked, this, &SetCalculator::save);

    // заполняем универсум числами от -50 до 50:
    for (int i = 0; i < universum.size(); ++i)
    {
        universum[i] = i - 50;
    }
}

SetCalculator::~SetCalculator()
{
    for (auto& pair : sets) {
        delete pair.second;
    }

    delete ui;
}

void SetCalculator::add()
{
    QString setName = ui->setNameTextEdit->toPlainText();
    if (sets.find(setName) != sets.end())
    {
        qDebug() << "Ключ уже существует";
    }
    else
    {
        QVector<int>* newSet = new QVector<int>;
        sets[setName] = newSet;
    }

    updateOutput();
}

void SetCalculator::del()
{
    QString setName = ui->setNameTextEdit->toPlainText();
    auto it = sets.find(setName);
    if (it != sets.end())
    {
        delete it->second;  // Освобождаем память от "множества", на которое указывает указатель
        sets.erase(it);    // Удаляем элемент из хэш-таблицы
    }
    else
    {
        qDebug() << "Нет множества с таким именем";
    }

    updateOutput();
}

void SetCalculator::edit()
{
    QString setName = ui->setNameTextEdit->toPlainText();
    auto it = sets.find(setName);
    if (it != sets.end())
    {
        EditSets editSetsWindow(sets, setName);
        editSetsWindow.setModal(true);
        editSetsWindow.exec();
    }
    else
    {
        qDebug() << "Нет множества с таким именем";
    }

    updateOutput();
}

void SetCalculator::updateOutput()
{
    ui->outputTextEdit->clear();
    QString output;
    for (auto& it : sets)
    {
        if (it.second->size() == 0)
        {
            output += it.first + " = ∅;\n";
        }
        else
        {
            output += it.first + " = {";
            QString set;
            for (const int& value : *it.second) {
                set.append(QString::number(value) + ", ");
            }
            if (!set.isEmpty()) {
                set.chop(2);
            }
            output += set + "};\n";
        }
    }

    ui->outputTextEdit->lineWrapMode();
    ui->outputTextEdit->setText(output);
}

QVector<int> SetCalculator::unionSets(const QVector<int>& set1, const QVector<int>& set2)
{
    QVector<int> result = set1;  // Копируем первое множество в результат

    // Проходим по каждому элементу второго множества
    for (const int& elem : set2)
    {
        // Если элемент не содержится в первом множестве или в результирующем векторе, добавляем его
        if (!result.contains(elem))
        {
            result.append(elem);
        }
    }

    return result;
}

QVector<int> SetCalculator::intersectionSets(const QVector<int>& set1, const QVector<int>& set2)
{
    QVector<int> result;
    QVector<int> tempSet2 = set2;  // Копируем второе множество, чтобы модифицировать его

    // Проходим по каждому элементу первого множества
    for (const int& elem : set1)
    {
        // Если элемент содержится во втором множестве
        if (tempSet2.contains(elem))
        {
            result.append(elem);  // Добавляем элемент в результат
            tempSet2.removeOne(elem);  // Удаляем его из второго множества, чтобы учесть повторения
        }
    }

    return result;
}

QVector<int> SetCalculator::differenceSets(const QVector<int>& set1, const QVector<int>& set2)
{
    QVector<int> result = set1;  // Копируем первое множество в результат
    QVector<int> tempSet2 = set2;  // Копируем второе множество для модификации

    // Проходим по каждому элементу второго множества
    for (const int& elem : tempSet2)
    {
        // Если элемент найден в первом множестве (в результирующем), удаляем его
        if (result.contains(elem))
        {
            result.removeOne(elem);  // Удаляем только одно вхождение элемента
        }
    }

    return result;
}

QVector<int> SetCalculator::symmetricSets(const QVector<int>& set1, const QVector<int>& set2)
{
    QVector<int> result = set1;  // Начинаем с копии первого множества
    QVector<int> tempSet2 = set2;  // Копируем второе множество

    // Для каждого элемента второго множества проверяем пересечение с первым
    for (const int& elem : set2)
    {
        if (result.contains(elem))
        {
            // Если элемент есть в первом множестве, удаляем его из обоих
            result.removeOne(elem);
            tempSet2.removeOne(elem);
        }
    }

    // После удаления общих элементов, добавляем оставшиеся элементы второго множества
    result += tempSet2;

    return result;
}

QVector<int> SetCalculator::complementSets(const QVector<int>& universalSet, const QVector<int>& subset)
{
    QVector<int> result;

    // Проходим по каждому элементу универсального множества
    for (const int& elem : universalSet)
    {
        // Если элемент не содержится в подмножестве, добавляем его в результат
        if (!subset.contains(elem))
        {
            result.append(elem);
        }
    }

    return result;
}

// Функция для обработки выражений и составления порядка действий
QVector<QString> SetCalculator::processExpression(QString input)
{
    QVector<QString> sequence;
    std::stack<int> check;
    int exprNumber = 0;
    int exprStart;

    for (int i = 0; i < input.size(); i++)
    {
        QChar ch = input[i];

        if (ch == '(')
        {
            check.push(i);
        }
        else if (ch == ')')
        {
            exprStart = check.top();
            check.pop();
            QString subExpr = input.mid(exprStart + 1, i - exprStart - 1);
            sequence.append(subExpr);

            input.replace(exprStart, i - exprStart + 1, QString::number(exprNumber));
            exprNumber++;
            // qDebug() << input;
            i = 0;
        }
        else if (ch == '!')
        {
            int setIndex;
            if (input[i + 1] == '[' && exprNumber != 0)
            {
                for (int j = i + 1; j < input.size(); j++)
                {
                    if (input[j] == ']')
                    {
                        setIndex = j;
                        break;
                    }
                }
                QString subExpr = input.mid(i, setIndex - i + 1);
                sequence.append(subExpr);
                input.replace(i, setIndex - i + 1, QString::number(exprNumber));
                exprNumber++;
                // qDebug() << input;
                i = 0;
            }
            else if (input[i + 1].isDigit())
            {
                for (int j = i + 1; j < input.size(); j++)
                {
                    if (input[j] == ' ' || input[j] == ')')
                    {
                        setIndex = j - 1;
                        break;
                    }
                }
                QString subExpr = input.mid(i, setIndex - i + 1);
                sequence.append(subExpr);
                input.replace(i, setIndex - i + 1, QString::number(exprNumber));
                exprNumber++;
                // qDebug() << input;
                i = 0;
            }
        }
    }
    sequence.append(input);
    return sequence;
}

void SetCalculator::calcByFormula()
{
    QString expression = ui->inputTextEdit->toPlainText();
    QVector<QString> sequence = processExpression(expression);

    for (const QString& i : sequence)
    {
        qDebug() << i;
    }

    QVector<QVector<int>> results;
    for (const QString& i : sequence)
    {
        if (i[0] == '!')
        {
            if (i[1] == '[')
            {
                QString key = i.mid(2, -1);
                key.chop(1);

                const auto it = sets.find(key); // Ищем элемент по ключу

                if (it != sets.end())
                { // Проверяем, найден ли элемент
                    const QVector<int>& value = *it->second; // Получаем значение по итератору
                    results.append(complementSets(universum, value)); // Передаем по ссылке
                }
                else
                {
                    // Обработка случая, когда элемент не найден
                    qDebug() << "Элемент не найден, при вычеслении по формуле. Ошибка в формуле! (1)";
                    return;
                }
            }
            else if (i[1].isDigit())
            {
                QString prevValue = i.mid(1, -1);
                results.append(complementSets(universum, results[prevValue.toInt()]));
            }
        }
        else if (!i[0].isDigit() && !i.back().isDigit())
        {
            // Регулярное выражение для поиска содержимого в квадратных скобках и знака x
            QRegularExpression regex(R"(\[([^\]]*)\]\s+([visd])\s+\[([^\]]*)\])");
            QRegularExpressionMatch match = regex.match(i);
            qDebug() << match;

            if (match.hasMatch())
            {
                QString firstPart = match.captured(1);  // Содержимое первых квадратных скобок
                QString xChar = match.captured(2);      // Символ x
                QString secondPart = match.captured(3); // Содержимое вторых квадратных скобок

                // qDebug() << "First Part:" << firstPart;
                // qDebug() << "X Character:" << xChar;
                // qDebug() << "Second Part:" << secondPart;

                const auto it1 = sets.find(firstPart); // Ищем элемент по ключу
                const auto it2 = sets.find(secondPart); // Ищем элемент по ключу

                if (it1 != sets.end() && it2 != sets.end())
                { // Проверяем, найден ли элемент
                    const QVector<int>& firstSet = *it1->second; // Получаем значение по итератору
                    const QVector<int>& secondSet = *it2->second; // Получаем значение по итератору

                    if (xChar == 'v')
                    {
                        results.append(unionSets(firstSet, secondSet));
                    }
                    else if (xChar == 'i')
                    {
                        results.append(intersectionSets(firstSet, secondSet));
                    }
                    else if (xChar == 'd')
                    {
                        results.append(differenceSets(firstSet, secondSet));
                    }
                    else if (xChar == 's')
                    {
                        results.append(symmetricSets(firstSet, secondSet));
                    }
                    else
                    {
                        qDebug() << "Неверное действие над множествами";
                        return;
                    }
                }
                else
                {
                    // Обработка случая, когда элемент не найден
                    qDebug() << "Элемент не найден, при вычеслении по формуле. Ошибка в формуле! (2)";
                    return;
                }
            }
            else
            {
                qDebug() << i << "Элемент не найден, при вычеслении по формуле. Ошибка в формуле! (3)";
                return;
            }
        }
        else if (!i[0].isDigit() && i.back().isDigit())
        {
            QRegularExpression regex(R"(\[([^\]]*)\]\s+([visd])\s+(\d))");
            QRegularExpressionMatch match = regex.match(i);
            qDebug() << match;

            if (match.hasMatch())
            {
                QString firstPart = match.captured(1); // Операция
                QString xChar = match.captured(2);     // Символ операции
                QString secondNumber = match.captured(3); // Число

                const auto it1 = sets.find(firstPart); // Ищем множество по ключу

                if (it1 != sets.end())
                {
                    const QVector<int>& firstSet = *it1->second; // Получаем множество
                    if (xChar == 'v')
                    {
                        results.append(unionSets(firstSet, results[secondNumber.toInt()]));
                    }
                    else if (xChar == 'i')
                    {
                        results.append(intersectionSets(firstSet, results[secondNumber.toInt()]));
                    }
                    else if (xChar == 'd')
                    {
                        results.append(differenceSets(firstSet, results[secondNumber.toInt()]));
                    }
                    else if (xChar == 's')
                    {
                        results.append(symmetricSets(firstSet, results[secondNumber.toInt()]));
                    }
                    else
                    {
                        qDebug() << "Неверное действие над множествами";
                        return;
                    }
                }
                else
                {
                    qDebug() << "Элемент не найден, при вычеслении по формуле. Ошибка в формуле! (4)";
                    return;
                }
            }
            else
            {
                qDebug() << "Элемент не найден, при вычеслении по формуле. Ошибка в формуле! (5)";
                return;
            }
        }
        else if (i[0].isDigit() && !i.back().isDigit()) // исправлено условие
        {
            QRegularExpression regex(R"((\d)\s+([visd])\s+\[([^\]]*)\])");
            QRegularExpressionMatch match = regex.match(i);
            qDebug() << match;

            if (match.hasMatch())
            {
                QString firstNumber = match.captured(1); // Первое число
                QString xChar = match.captured(2);       // Символ операции
                QString secondPart = match.captured(3);  // Множество

                const auto it2 = sets.find(secondPart); // Ищем множество по ключу

                if (it2 != sets.end())
                {
                    const QVector<int>& secondSet = *it2->second; // Получаем множество
                    if (xChar == 'v')
                    {
                        results.append(unionSets(results[firstNumber.toInt()], secondSet));
                    }
                    else if (xChar == 'i')
                    {
                        results.append(intersectionSets(results[firstNumber.toInt()], secondSet));
                    }
                    else if (xChar == 'd')
                    {
                        results.append(differenceSets(results[firstNumber.toInt()], secondSet));
                    }
                    else if (xChar == 's')
                    {
                        results.append(symmetricSets(results[firstNumber.toInt()], secondSet));
                    }
                    else
                    {
                        qDebug() << "Неверное действие над множествами";
                        return;
                    }
                }
                else
                {
                    qDebug() << "Элемент не найден, при вычеслении по формуле. Ошибка в формуле! (6)";
                    return;
                }
            }
            else
            {
                qDebug() << "Элемент не найден, при вычеслении по формуле. Ошибка в формуле! (7)";
                return;
            }
        }
        else if (i[0].isDigit() && i.back().isDigit())
        {
            QRegularExpression regex(R"(\s*(\d+)\s+(\w)\s+(\d+)\s*)");
            QRegularExpressionMatch match = regex.match(i);

            if (match.hasMatch())
            {
                QString firstNumber = match.captured(1); // Первое число (y)
                QString xChar = match.captured(2);       // Символ (x)
                QString secondNumber = match.captured(3); // Второе число (y)

                // qDebug() << "First Number:" << firstNumber;
                // qDebug() << "X Character:" << xChar;
                // qDebug() << "Second Number:" << secondNumber;

                if (xChar == 'v')
                {
                    results.append(unionSets(results[firstNumber.toInt()], results[secondNumber.toInt()]));
                }
                else if (xChar == 'i')
                {
                    results.append(intersectionSets(results[firstNumber.toInt()], results[secondNumber.toInt()]));
                }
                else if (xChar == 'd')
                {
                    results.append(differenceSets(results[firstNumber.toInt()], results[secondNumber.toInt()]));
                }
                else if (xChar == 's')
                {
                    results.append(symmetricSets(results[firstNumber.toInt()], results[secondNumber.toInt()]));
                }
                else
                {
                    qDebug() << "Неверное действие над множествами";
                    return;
                }
            }
            else
            {
                qDebug() << i << "Элемент не найден, при вычеслении по формуле. Ошибка в формуле! (8)";
                return;
            }
        }
    }

    /*
    for (const auto& res : results)
    {
        qDebug() << res;
    }
    */

    QString answer;
    for (int i = 0; i < results[results.size() - 1].size(); i++)
    {
        answer += QString::number(results[results.size() - 1][i]) + ", ";
    }
    answer.chop(2);
    ui->answerTextEdit->setText(answer);
}

void SetCalculator::save()
{
    QString setName = ui->setNameTextEdit->toPlainText();
    QString input = ui->answerTextEdit->toPlainText();
    QStringList numberStrings = input.split(", "); // Разбиваем строку по запятым + пробелу

    auto it = sets.find(setName);
    if (it != sets.end())
    {
        delete it->second;  // Освобождаем память от "множества", на которое указывает указатель
        QVector<int>* set = new QVector<int>;

        set->clear(); // Очищаем результат перед заполнением

        bool check;
        for (const QString& numStr : numberStrings)
        {
            int number = numStr.toInt(&check); // Преобразуем строку в int
            if (!check || number < -50 || number > 50)
            {
                qDebug() << "Число" << numStr << "либо не является целым числом, либо не в диапазоне -50 до 50";
                return;
            }
            set->append(number);
        }
        it->second = set;
    }
    else
    {
        add();
        save();
    }
    updateOutput();
}
