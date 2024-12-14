from tabulate import tabulate
import math


vectors = []


def is_save_0(vector):
    if vector[0] == "0":
        return True
    return False


def is_save_1(vector):
    if vector[-1] == "1":
        return True
    return False


def is_self_referential(vector):
    length = len(vector)
    for i in range(length // 2):
        if vector[i] == vector[length - 1 - i]:
            return False    
    return True


def is_monotone(vector):
    for i in range(len(vector)):
        for j in range(len(vector)):
            if (i & j) == i:
                if vector[i] > vector[j]:
                    return False
    return True


def is_linear(vector: str):
    length = len(vector)
    num_variables = int(math.log2(length))

    if num_variables < 1 or length != (1 << num_variables):
        return False

    c0 = int(vector[0])

    if num_variables == 2:
        cy = c0 ^ int(vector[1])
        cx = c0 ^ int(vector[2])
        cxy = c0 ^ cx ^ cy ^ int(vector[3])
        return cxy == 0

    elif num_variables == 3:
        cz = c0 ^ int(vector[1])
        cy = c0 ^ int(vector[2])
        cx = c0 ^ int(vector[4])
        cxy = c0 ^ cx ^ cy ^ int(vector[6])
        cxz = c0 ^ cx ^ cz ^ int(vector[5])
        czy = c0 ^ cz ^ cy ^ int(vector[3])
        cxyz = c0 ^ cx ^ cy ^ cz ^ int(vector[7])
        return cxy == 0 and cxz == 0 and czy == 0 and cxyz == 0

    elif num_variables == 4:
        cx = c0 ^ int(vector[1])
        cy = c0 ^ int(vector[2])
        cz = c0 ^ int(vector[4])
        cw = c0 ^ int(vector[8])
        cxz = c0 ^ cx ^ cz ^ int(vector[5])
        cxy = c0 ^ cx ^ cy ^ int(vector[6])
        czy = c0 ^ cz ^ cy ^ int(vector[3])
        cxyz = c0 ^ cx ^ cy ^ cz ^ int(vector[7])
        cwz = c0 ^ cw ^ cz ^ int(vector[9])
        cxwz = c0 ^ cw ^ cx ^ cz ^ int(vector[10])
        return cxy == 0 and cxz == 0 and czy == 0 and cxyz == 0 and cwz == 0 and cxwz == 0

    return False


def is_binary_string(s):
    return set(s).issubset({'0', '1'})


def is_power_of_two_length(s):
    n = len(s)
    return n > 0 and (n & (n - 1)) == 0


def is_complete():
    classes = []
    for x in vectors:
        vector_properties = [is_save_0(x), is_save_1(x), is_self_referential(x), is_monotone(x), is_linear(x)]
        classes.append(vector_properties)

    columns_have_false = all(any(not row[col] for row in classes) for col in range(len(classes[0])))
    if columns_have_false:
        return True
    else:
        return False


def menu():
    expression_number = int(input("Введите количество выражений: "))
    global vectors
    for _ in range(expression_number):
        vector = input("Введите вектор: ")
        if is_binary_string(vector) and is_power_of_two_length(vector) and vector not in vectors:
            vectors.append(vector)
        else:
            return "Неверный формат ввода вектора"

    choice = 1
    while(choice != 0):
        print("Menu:")
        print("1. Ввести новую систему")
        print("2. Вывести таблицу классов")
        print("3. Проверка на полноту")
        print("0. Выход")
        choice = int(input())

        if choice == 1:
            expression_number = int(input("Введите количество выражений: "))
            vectors = []
            for _ in range(expression_number):
                vector = input("Введите вектор: ")
                if is_binary_string(vector) and is_power_of_two_length(vector) and vector not in vectors:
                    vectors.append(vector)
                else:
                    return "Неверный формат ввода вектора"

        if choice == 2:
            data = [[x, is_save_0(x), is_save_1(x), is_self_referential(x), is_monotone(x), is_linear(x)] for x in vectors]
            headers = [" ", "T0", "T1", "S", "M", "L"]
            print(tabulate(data, headers=headers, tablefmt='grid'))

        if choice == 3:
            if is_complete():
                print("Система полная")
            else:
                print("Система неполная")
    
    return "Выход..."


def main():
    print(menu())


if __name__ == "__main__":
    main()