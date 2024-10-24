class IdentityMatrix:
    def __init__(self):
        self.matrix = []

        self.options = {
            1: "Ввод матрицы с клавиатуры",
            2: "Ввод матрицы с файла",      
            3: "Вывод матрицы",
            4: "Вывод свойств матрицы бинарных отношений",
            0: "Выход"
        }

        self.attitudes = {
            "Рефлексивность":       False,
            "Антирефлексивность":   False,
            "Симметричность":       False,
            "Антисимметричность":   False,
            "Ассиметричность":      False,
            "Транзитивность":       False,
            "Нетранзитивность":     False,
            "Полнота":              False,
            "Неполнота":            False
        }


    def display_menu(self):
        print("==========МЕНЮ==========")
        for key, value in self.options.items():
            print(f"{key}: {value}")


    def handle_selection(self, choice):
        if choice == 1:
            self.read_matrix_from_user()
        elif choice == 2:
            self.read_matrix_from_file()
        elif choice == 3:
            self.print_matrix()
        elif choice == 4:
            self.get_attitudes()
        elif choice == 0:
            print("Выход...")
        else:
            print("Неверный код операции, повторите попытку.")


    def run(self):
        while True:
            self.display_menu()
            try:
                choice = int(input("Выберите операцию: "))
                if choice == 0:
                    self.handle_selection(choice)
                    break
                self.handle_selection(choice)
            except ValueError:
                continue


    def read_matrix_from_user(self):
        self.matrix = []
        print("Введите матрицу:")
        get = str
        while(get != "q"):
            get = input()
            row = get.split()
            row = [int(num) for num in row]
            self.matrix.append(row)

    
    def read_matrix_from_file(self):
        self.matrix = []
        file_name = str(input("Введите название файла: ")) 
        with open(file_name, 'r') as file:
            for line in file:
                row = line.split()
                row = [int(num) for num in row]
                self.matrix.append(row)
        

    def print_matrix(self):
        for row in self.matrix:
            print(row)


    def __is_reflexive(self, size):
        for i in range(size):
            if self.matrix[i][i] != 1:
                return False
        return True


    def __is_antireflexive(self, size):
        for i in range(size):
            if self.matrix[i][i] != 0:
                return False
        return True


    def __is_symmetric(self, size):
        for i in range(size):
            for j in range(i, size):
                if self.matrix[i][j] != self.matrix[j][i]:
                    return False
        return True


    def __is_antisymmetric(self, size):
        for i in range(size):
            for j in range(size):
                if i != j and self.matrix[i][j] == 1 and self.matrix[j][i] == 1:
                    return False
        return True


    def __is_asymmetric(self, size):
        for i in range(size):
            for j in range(size):
                if self.matrix[i][j] == 1 and (self.matrix[j][i] == 1 or self.matrix[i][i] == 1):
                    return False
        return True


    def __is_transitive(self, size):
        for i in range(size):
            for j in range(size):
                if self.matrix[i][j] == 1:
                    for k in range(size):
                        if self.matrix[j][k] == 1 and self.matrix[i][k] == 0:
                            return False
        return True


    def __is_complete(self, size):
        for i in range(size):
            for j in range(size):
                if i != j and self.matrix[i][j] == 0 and self.matrix[j][i] == 0:
                    return False
        return True


    def get_attitudes(self):
        size = len(self.matrix)
        if size == 0:
            print("Матрица пустая.")
            return
        elif not all(len(row) == size for row in self.matrix):
            print("Матрица не квадратная")
            return

        reflexive = self.__is_reflexive(size)
        antireflexive = self.__is_antireflexive(size)
        symmetric = self.__is_symmetric(size)
        antisymmetric = self.__is_antisymmetric(size)
        asymmetric = self.__is_asymmetric(size)
        transitive = self.__is_transitive(size)
        complete = self.__is_complete(size)

        self.attitudes["Рефлексивность"] = reflexive
        self.attitudes["Антирефлексивность"] = antireflexive
        self.attitudes["Симметричность"] = symmetric
        self.attitudes["Антисимметричность"] = antisymmetric
        self.attitudes["Ассиметричность"] = asymmetric
        self.attitudes["Транзитивность"] = transitive
        self.attitudes["Нетранзитивность"] = not transitive
        self.attitudes["Полнота"] = complete
        self.attitudes["Неполнота"] = not complete

        attitudes_with_true_values = [key for key in self.attitudes if self.attitudes[key]]
        print("Свойства:")
        print(attitudes_with_true_values)



def main():
    matrix = IdentityMatrix()
    matrix.run()


if __name__ == "__main__":
    main()
