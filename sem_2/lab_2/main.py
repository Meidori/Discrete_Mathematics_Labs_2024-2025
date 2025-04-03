class Graph:
    def __init__(self, file_name):
        self.matrix = self.get_matrix(file_name)
        self.edges = []
        
        n = len(self.matrix)
        vertices = [chr(97 + i) for i in range(n)]
        for i in range(n):
            for j in range(n):
                if self.matrix[i][j] > 0:
                    self.edges.append((self.matrix[i][j], vertices[i], vertices[j]))


    def get_matrix(self, file_name):
        with open(file_name, "r") as file:
            return [list(map(int, line.split())) for line in file]


    def print_matrix(self):
        size = len(self.matrix)
        vertices = [chr(97 + i) for i in range(size)]  
        
        print(" ", " ".join(vertices))  
        for i, row in enumerate(self.matrix):
            print(vertices[i], " ".join(map(str, row)))


    def print_edges(self):
        for x in self.edges:
            print(x) 


    def __kruskal(self):
        sorted_edges = sorted(self.edges)
        n = len(self.matrix)
        dsu = DSU(n)
        self.mst = []    # Minimum Spanning Tree - Остов

        for weight, a, b in sorted_edges: 
            x, y = ord(a) - 97, ord(b) - 97
            if dsu.union(x, y):  # Если x и y в разных компонентах
                self.mst.append((weight, chr(97 + x), chr(97 + y)))  # Добавляем ребро в остовное дерево
                if len(self.mst) == n - 1:  # Если уже есть (n-1) рёбер, остовное дерево построено
                    break
        

    def get_mst(self):
        self.__kruskal()


    def print_mst(self):
        for x in self.mst:
            print(x)

        
class DSU:
    def __init__(self, n):
        self.parent = list(range(n))


    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]


    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        
        if root_x != root_y:
            self.parent[root_y] = root_x  # Просто присоединяем одно множество к другому
            return True  #  Объединение произошло
        return False  # Уже в одном множестве


def main():
    m = Graph("g24.txt")
    print("Введенная матрица смежности:")
    m.print_matrix()
    # print("Ребра графа:")
    # m.print_edges()

    m.get_mst()
    print("Минимальное остовное дерево:")
    m.print_mst()

    sum_of_mst = sum(item[0] for item in m.mst)
    print(f"Сумма весов остовного дерева: {sum_of_mst}")



if __name__ == "__main__":
    main()