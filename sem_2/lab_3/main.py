def get_matrix(file_name):
    with open(file_name, "r") as file:
        return [list(map(int, line.split())) for line in file]


def print_matrix(matrix):
    for row in matrix:
        print(' '.join(f'{elem:3}' for elem in row))
    print()


def shimbell(matrix, steps, mode='min'):
    size = len(matrix)
    result = [row[:] for row in matrix]

    for step in range(steps - 1):
        new_result = [[0 for _ in range(size)] for _ in range(size)]
        for i in range(size):
            for j in range(size):
                candidates = []
                for k in range(size):
                    a = result[i][k]
                    b = matrix[k][j]
                    if a != 0 and b != 0:
                        candidates.append(a + b)
                if candidates:
                    new_result[i][j] = min(candidates) if mode == 'min' else max(candidates)
                else:
                    new_result[i][j] = 0
        result = new_result
    return result 


matrix = get_matrix("g42.txt")
print("Введена матрица:")
print_matrix(matrix) 
mode = input("Введите (max/min): ")
steps = int(input("Введите количество переходов: "))
result = shimbell(matrix, steps, mode)
print(f"\nРезультат после {steps} переходов (поиск: {mode}):")
print_matrix(result)
