import math
from tabulate import tabulate
import itertools


def get_vector():
    vector = str(input("Введите новый вектор: "))
    return vector


def is_power_of_two(n):
    return n > 0 and (n & (n - 1)) == 0


def get_truth_table(vector):
    size = len(vector)
    if not is_power_of_two(size):
        print("Длина вектора не является степенью двойки")
        return

    variables = "xyzwvutsrqponmlkjihgfedcba"
    columns = []
    quantity = int(math.log2(size))
    auxiliary = 1
    for i in range(quantity):
        auxiliary *= 2
        tmp = [variables[i]]
        flag = True
        for j in range(auxiliary):
            flag = not(flag)
            for k in range(size // auxiliary):
                if flag:
                    tmp.append(1)
                else:
                    tmp.append(0)
        columns.append(tmp)

    tmp = [int(x) for x in vector]
    tmp.insert(0, "F")
    columns.append(tmp)
    return columns


def get_PDNF(table):
    size = len(table)
    true_rows = []
    for i in range(1, len(table[size - 1])):
        if table[size - 1][i] == 1:
            column_values = [row[i] for row in table[:-1]]
            true_rows.append(column_values)

    return true_rows


def get_PCNF(table):
    size = len(table)
    false_rows = []
    for i in range(1, len(table[size - 1])):
        if table[size - 1][i] == 0:
            column_values = [row[i] for row in table[:-1]]
            false_rows.append(column_values)

    return false_rows


def index_of_difference(tuple1, tuple2):
    if len(tuple1) != len(tuple2):
        return None 
    
    if tuple1.count(-1) != tuple2.count(-1):
        return None
    
    difference_index = -1
    differences = 0

    for i, (a, b) in enumerate(zip(tuple1, tuple2)):
        if a != b:
            differences += 1
            if differences > 1:
                return None
            difference_index = i 

    return difference_index if differences == 1 else None 


def get_implicants(PDNF):
    implicants = dict()
    for x in PDNF:
        implicants[tuple(x)] = [tuple(x)]

    keys = list(implicants.keys())
    i = 0
    while i < len(keys):
        j = 0
        while j < len(keys):
            index = index_of_difference(keys[i], keys[j])
            if index != None:
                if index == 0:
                    new_key = tuple([-1]) + keys[i][1:] 
                elif index > 0:
                    new_key = keys[i][:index] + tuple([-1]) + keys[i][index+1:]

                if new_key not in keys:
                    keys.append(new_key)
                if new_key not in implicants:
                    implicants[new_key] = []
        
                new_values = [keys[i], keys[j]] + implicants[keys[i]] + implicants[keys[j]]
                for x in new_values:
                    if x not in implicants[new_key]:
                        implicants[new_key].append(x)
            
            j += 1
        i += 1 

    values = implicants.values()
    flattened_list = [item for sublist in values for item in sublist]

    for d in flattened_list:
        if d in implicants.keys():
            if flattened_list.count(d) == 1 and -1 not in d:
                continue
            del implicants[d]

    for k, v in implicants.items():
        new_value = []
        for x in v:
            if -1 not in x:
                new_value.append(x)
        implicants[k]= new_value
    
    return implicants


def get_matrix(implicants, PDNF):
    data = []
    for k, v in implicants.items():
        line = [k]        
        for i in range(len(PDNF)):
            if tuple(PDNF[i]) in v:
                line.append(1)
            else:
                line.append(0)
        data.append(line)

    return data


def find_minimal_coverings(matrix):
    num_columns = len(matrix[0])

    ones_positions = []
    for i in range(len(matrix)):
        for j in range(num_columns):
            if matrix[i][j] == 1:
                ones_positions.append(j)

    def covers(implicants, ones_positions):
        covered = set()
        for i in implicants:
            for j in range(num_columns):
                if matrix[i][j] == 1:
                    covered.add(j)
        return covered == set(ones_positions)

    minimal_coverings = []

    for r in range(1, len(matrix) + 1):  
        for comb in itertools.combinations(range(len(matrix)), r):
            if covers(comb, ones_positions):
                if not any(set(comb).issubset(set(existing)) for existing in minimal_coverings):
                    minimal_coverings.append(set(comb))
    
    return minimal_coverings


def print_PDNF(PDNF, table):
    expression = ""

    for x in PDNF:
        tmp = "("
        for i in range(len(x)):
            if x[i] == 0:
                tmp += f"¬{table[i][0]} ∧ "
            elif x[i] == 1:
                tmp += f"{table[i][0]} ∧ "
        expression += f"{tmp[:-3]}) ∨ "

    print(expression[:-3])


def print_PCNF(PCNF, table):
    expression = ""

    for x in PCNF:
        tmp = "("
        for i in range(len(x)):
            if x[i] == 0:
                tmp += f"{table[i][0]} ∨ "
            elif x[i] == 1:
                tmp += f"¬{table[i][0]} ∨ "
        expression += f"{tmp[:-3]}) ∧ "

    print(expression[:-3])


def print_truth_table(table):
    for elements in zip(*table):
        print(" ".join(map(str, elements)))


def print_implicant_matrix(implicants, PDNF, table):
    headers = ["  "]
    for x in PDNF:
        header = ""
        for i in range(len(x)):
            if x[i] == 0:
                header += f"¬{table[i][0]} "
            elif x[i] == 1:
                header += f"{table[i][0]} "
        headers.append(header)

    data = []
    for k, v in implicants.items():
        line = []
        name = ""
        for i in range(len(x)):
            if k[i] == 0:
                name += f"¬{table[i][0]} "
            elif k[i] == 1:
                name += f"{table[i][0]} "
        line.append(name)
        
        for i in range(len(PDNF)):
            if tuple(PDNF[i]) in v:
                line.append(" + ")
            else:
                line.append("   ")
        data.append(line)

    print(tabulate(data, headers=headers, tablefmt="grid"))


def print_minimal_coverings(matrix, minimal_coverings, table):
    lengths = []
    for x in minimal_coverings:
        lengths.append(len(x))
    
    answer = []
    for i in range(len(minimal_coverings)):
        minimal_coverings_strings = []
        if len(minimal_coverings[i]) == min(lengths):
            for x in minimal_coverings[i]:
                minimal_coverings_string = ""
                for j in range(len(matrix[x][0])):
                    if matrix[x][0][j] == 0:
                        minimal_coverings_string += f"¬{table[j][0]}"
                    elif matrix[x][0][j] == 1:
                        minimal_coverings_string += f"{table[j][0]}"
                minimal_coverings_strings.append(minimal_coverings_string)
        
        result = " ∨ ".join(map(str, minimal_coverings_strings))
        if result != "":
            answer.append(result)
    
    print("\n".join(answer))


def menu():
    vector = str(input("Введите вектор: "))
    if vector.count("0") == len(vector):
        print("Функция всегда ложна")
        return

    truth_table = get_truth_table(vector)
    PDNF = get_PDNF(truth_table)   # СДНФ
    PCNF = get_PCNF(truth_table)   # СКНФ
    implicants = get_implicants(PDNF)
    choice = 1
    matrix = get_matrix(implicants, PDNF)
    implicant_matrix = [row[1:] for row in matrix]
    minimal_coverings = find_minimal_coverings(implicant_matrix)

    while (choice != 0):
        print("=====MENU=====")
        print("1. Ввести новый вектор")
        print("2. Вывести таблицу истинности")
        print("3. Вывести СДНФ")
        print("4. Вывести СКНФ")
        print("5. Вывести матрицу импликантности") 
        print("6. Вывести короткие покрытия") 
        
        choice = int(input())
        if (choice == 1):
            vector = get_vector()
            if vector.count("0") == len(vector):
                print("Функция всегда ложна")
                return
            truth_table = get_truth_table(vector)
            PDNF = get_PDNF(truth_table)
            PCNF = get_PCNF(truth_table)
            implicants = get_implicants(PDNF)
            matrix = get_matrix(implicants, PDNF)
            implicant_matrix = [row[1:] for row in matrix]
            minimal_coverings = find_minimal_coverings(implicant_matrix)
        
        elif (choice == 2):
            print_truth_table(truth_table)
        
        elif (choice == 3):
            print_PDNF(PDNF, truth_table)
        
        elif (choice == 4):
            print_PCNF(PCNF, truth_table)
        
        elif (choice == 5):
            print_implicant_matrix(implicants, PDNF, truth_table)

        elif (choice == 6):
            print_minimal_coverings(matrix, minimal_coverings, truth_table)


def main():
    menu()


if __name__ == "__main__":
    main()
