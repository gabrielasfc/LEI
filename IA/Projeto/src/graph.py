from queue import Queue
from position_calculator import *
from node import Node
from collections import deque
from copy import deepcopy


class Graph:
    def __init__(self):
        """
        Construtor de um grafo
        """
        self.nodes = set()  # lista com os nodos do grafo
        self.graph = dict()  # dicionario do grafo
        self.h1 = dict()  # heurística da distância até a posição final
        self.h2 = dict()  # heurística da velocidade

    def __str__(self):
        """
        Devolve a representação em string do objeto Graph
        :return: String
        """
        string = ""
        for key in self.graph.keys():
            string = string + str(key) + ": \n"

            for edge in self.graph[key]:
                string += "     " + str(edge) + "\n"

        return string

    def add_edge(self, node1, node2, cost):
        """
        Adiciona uma aresta entre os nodos passados como argumento
        :param node1: Primeiro nodo
        :param node2: Segundo nodo
        :param cost: Custo da aresta
        """
        if node1 not in self.nodes:
            self.nodes.add(node1)
            self.graph[node1] = set()

        if node2 not in self.nodes:
            self.nodes.add(node2)
            self.graph[node2] = set()

        self.graph[node1].add((node2, cost))

    def add_heuristic(self, node, value, type):
        """
        Adiciona uma heurística
        :param node: Nodo ao qual será adicionada
        :param value: Valor da heurística
        :param type: Tipo da heurística
        """
        if type == "distance":
            heuristic = self.h1
        elif type == "velocity":
            heuristic = self.h2

        if node in self.nodes:
            heuristic[node] = value

    def get_neighbours(self, node):
        """
        Obtém a vizinhança de um nodo
        :param node: Nodo
        :return: Lista de nodos vizinhos
        """
        neighbours = []

        for (adj, cost) in self.graph[node]:
            neighbours.append((adj, cost))

        return neighbours

    def get_arc_cost(self, node1, node2):
        """
        Obtém o custo de uma aresta entre 2 nodos dados, caso exista
        :param node1: Primeiro nodo
        :param node2: Segundo nodo
        :return: Custo da aresta
        """
        total = 0
        adjs = self.graph[node1]  # lista de arestas para aquele nodo

        for (node, cost) in adjs:
            if node == node2:
                total = cost

        return total

    def calc_path_cost(self, path):
        """
        Calcula o custo de um caminho
        :param path: Caminho
        :return: Custo do caminho
        """
        total = 0
        i = 0

        while i < len(path) - 1:
            total += self.get_arc_cost(path[i], path[i + 1])
            i += 1

        return total

    @staticmethod
    def print_path(path, cost):
        """
        Imprime o custo e os nodos de um caminho
        :param path: Caminho
        :param cost: Custo
        """
        counter = 1
        res = ""

        for node in path:
            res += "Node " + str(counter) + " : " + str(node) + "\n"
            counter += 1

        print(res)
        print(f"Custo: {cost}\n")

    def print_nodes(self):
        """
        Imprime os nodos de um grafo
        """
        nodes = ""

        for node in self.nodes:
            nodes += str(node) + "\n"

        print(nodes)

    def print_edges(self):
        """
        Imrime as arestas de um grafo
        """
        edges = ""

        for node in self.graph.keys():
            for (adj, cost) in self.graph[node]:
                edges += str(node) + "   ->   " + str(adj) + "    cost:" + str(cost) + "\n"

        print(edges)

    def print_heuristics(self, type):
        """
        Imprime as heurísticas de um grafo
        :param type: Tipo da heurística
        """
        if type == "distance":
            heuristic = self.h1
        elif type == "velocity":
            heuristic = self.h2

        heuristics = ""

        for key in heuristic.keys():
            heuristics += str(key) + " | " + str(heuristic[key]) + "\n"

        print(heuristics)

    @staticmethod
    def node_in_other_paths(start_node, final_node, iteration_number, paths):
        """
        Verifica se há colisão entre jogadores
        Dado um nodo inicial e um nodo final, verifica-se se o deslocamento embate numa posição onde tenha estado algum jogador na iteração dada
        :param start_node: Nodo inicial
        :param final_node: Nodo final
        :param iteration_number: Iteração
        :param paths: Dicionário com os caminhos dos vários jogadores
        :return: True em caso afirmativo, caso contrário False
        """
        if len(paths.values()) < 1:
            return False

        disp = Node.calculate_displacement(start_node.pos, final_node.pos)
        disp_squares = squares_visited(start_node.pos, disp)

        for list in paths.values():
            for square in disp_squares:
                if len(list) > iteration_number and list[iteration_number].pos == square:
                    return True

        return False

    def DFS(self, start, end, visited, debug=list(), paths=dict(), iter_number=0):
        """
        Algoritmo "Depth-First-Search"
        :param start: Posição inicial
        :param end: Posições finais
        :param visited: Nodos visitados
        :param debug: Posições visitadas (debug)
        :param paths: Dicionário com os caminhos dos vários jogadores (multiplayer)
        :param iter_number: Número de iteração (multiplayer)
        :return: Caminho final, custo da solução e lista de posições visitadas para debug atualizada
        """
        visited.add(start)
        debug.append(start.pos)  # debug

        for state in end:
            if state.pos == start.pos:
                return [start], 0

        for adj, cost in self.graph[start]:
            if adj not in visited and not Graph.node_in_other_paths(start, adj, iter_number, paths):
                ret = self.DFS(adj, end, visited, debug, paths, iter_number + 1)
                if ret is not None:
                    p, c = ret
                    return [start] + p, c + cost

        return None

    def BFS(self, start, end, paths=dict()):
        """
        Algoritmo "Breadth-First-Search"
        :param start: Posição inicial
        :param end: Posições finais
        :param paths: Dicionário com os caminhos dos vários jogadores (multiplayer)
        :return: Caminho final, custo da solução e posições visitadas para debug
        """
        debug = [start]  # debug
        visited = {start}
        q = Queue()

        q.put(start)

        # garantir que o start node nao tem pais
        parents = dict()
        parents[start] = None

        level = dict()
        level[start] = 0

        path_found = False
        remains_same_spot = []
        while not q.empty() and not path_found:
            node = q.get()
            debug.append(node.pos)  # debug

            for state in end:
                if node.pos == state.pos:
                    path_found = True

            if not path_found:
                for (adj, cost) in self.graph[node]:
                    i = level[node] + 1
                    if adj not in visited and not Graph.node_in_other_paths(node, adj, i, paths):
                        q.put(adj)
                        parents[adj] = node
                        level[adj] = i
                        visited.add(adj)

                if q.empty():
                    i = level[node] + 1
                    for (adj, cost) in self.graph[node]:
                        if adj == node:
                            remains_same_spot.append(adj)
                            q.put(adj)
                            level[adj] = i
                            visited.add(adj)
                            break

        # reconstruir o caminho
        path = []
        if path_found:
            path.append(node)
            while parents[node] is not None:
                if node in remains_same_spot:
                    path.append(node)
                path.append(parents[node])
                node = parents[node]

            if node in remains_same_spot:
                path.append(node)

            path.reverse()

            total_cost = self.calc_path_cost(path)
            return path, total_cost, debug

    def uniform_cost(self, start, end, paths=dict()):
        """
        Algoritmo do Custo Uniforme
        :param start: Posição inicial
        :param end: Posições finais
        :param paths: Dicionário com os caminhos dos vários jogadores (multiplayer)
        :return: Caminho final, custo da solução e posições visitadas para debug
        """
        level = {start: 0}

        open_list = {start}  # nodos visitados + vizinhos que ainda não foram todos visitados
        closed_list = set()  # nodos visitados
        parents = {start: start}  # mantém o antecessor de um nodo
        costs = {start: 0}

        debug = [start.pos]  # debug
        remains_same_spot = []

        while len(open_list) > 0:
            n = None

            # encontra nodo com a menor heuristica
            for node in open_list:
                if n is None or costs[node] < costs[n]:
                    n = node

            debug.append(n.pos)  # debug

            # se o nodo corrente é o destino
            # reconstruir o caminho a partir desse nodo até ao start seguindo o antecessor
            for state in end:
                if state.pos == n.pos:
                    reconst_path = []

                    while parents[n] != n:
                        if n in remains_same_spot:
                            reconst_path.append(n)
                        reconst_path.append(n)
                        n = parents[n]

                    if n in remains_same_spot:
                        reconst_path.append(n)

                    reconst_path.append(start)
                    reconst_path.reverse()

                    return reconst_path, self.calc_path_cost(reconst_path), debug

            for adj, cost in self.graph[n]:
                i = level[n] + 1
                if adj not in open_list and adj not in closed_list and not Graph.node_in_other_paths(n, adj, i, paths):
                    open_list.add(adj)
                    parents[adj] = n
                    level[adj] = i
                    costs[adj] = costs[n] + cost

                if len(open_list) == 1:
                    for adj, cost in self.graph[n]:
                        if adj == node:
                            remains_same_spot.append(adj)
                            open_list.add(adj)
                            level[adj] = i
                            costs[adj] = costs[n] + cost
                            break


            # remover n da open_list e adiciona-lo à closed_list - todos os seus vizinhos já foram inspecionados
            open_list.remove(n)
            closed_list.add(n)

        return None

    def greedy(self, start, end, type, paths=dict()):
        """
        Algoritmo "Greedy"
        :param start: Posição inicial
        :param end: Posições finais
        :param type: Tipo de heurística
        :param paths: Dicionário com os caminhos dos vários jogadores (multiplayer)
        :return: Caminho final, custo da solução e posições visitadas para debug
        """
        if type == "distance":
            heuristic = self.h1
        elif type == "velocity":
            heuristic = self.h2

        level = dict()
        level[start] = 0

        open_list = {start}  # nodos visitados + vizinhos que ainda não foram todos visitados
        closed_list = set()  # nodos visitados
        parents = {start: start}  # mantém o antecessor de um nodo

        debug = [start.pos]  # debug
        remains_same_spot = []

        while len(open_list) > 0:
            n = None

            # encontra nodo com a menor heuristica
            for node in open_list:
                if n is None or (heuristic[node] < heuristic[n]):
                    n = node

            debug.append(n.pos)  # debug

            # se o nodo corrente é o destino
            # reconstruir o caminho a partir desse nodo até ao start seguindo o antecessor
            for state in end:
                if state.pos == n.pos:
                    reconst_path = []

                    while parents[n] != n:
                        if n in remains_same_spot:
                            reconst_path.append(n)
                        reconst_path.append(n)
                        n = parents[n]

                    if n in remains_same_spot:
                        reconst_path.append(n)

                    reconst_path.append(start)
                    reconst_path.reverse()

                    return reconst_path, self.calc_path_cost(reconst_path), debug

            # para todos os vizinhos do nodo corrente
            for (adj, cost) in self.graph[n]:
                i = level[n] + 1
                if adj not in open_list and adj not in closed_list and not Graph.node_in_other_paths(n, adj, i, paths):
                    open_list.add(adj)
                    parents[adj] = n
                    level[adj] = i

                if len(open_list) == 1:
                    for adj, cost in self.graph[n]:
                        if adj == node:
                            remains_same_spot.append(adj)
                            open_list.add(adj)
                            level[adj] = i
                            break

            # remover n da open_list e adiciona-lo à closed_list - todos os seus vizinhos já foram inspecionados
            open_list.remove(n)
            closed_list.add(n)

        return None

    def a_star(self, start, end, type, paths=dict()):
        """
        Algoritmo "A*"
        :param start: Posição inicial
        :param end: Posições finais
        :param type: Tipo de heurística
        :param paths: Dicionário com os caminhos dos vários jogadores (multiplayer)
        :return: Caminho final, custo da solução e posições visitadas para debug
        """
        if type == "distance":
            heuristic = self.h1
        elif type == "velocity":
            heuristic = self.h2

        level = {start: 0}

        open_list = {start}  # nodos visitados + vizinhos que ainda não foram todos visitados
        closed_list = set()  # nodos visitados
        parents = {start: start}  # mantém o antecessor de um nodo
        costs = {start: 0}

        debug = [start.pos]  # debug
        remains_same_spot = []

        while len(open_list) > 0:
            n = None

            # encontra nodo com a menor heuristica
            for node in open_list:
                if n is None or (heuristic[node] + costs[node]) < (heuristic[n] + costs[n]):
                    n = node

            debug.append(n.pos)  # debug

            # se o nodo corrente é o destino
            # reconstruir o caminho a partir desse nodo até ao start seguindo o antecessor
            for state in end:
                if state.pos == n.pos:
                    reconst_path = []

                    while parents[n] != n:
                        if n in remains_same_spot:
                            reconst_path.append(n)
                        reconst_path.append(n)
                        n = parents[n]
                    if n in remains_same_spot:
                        reconst_path.append(n)

                    reconst_path.append(start)
                    reconst_path.reverse()

                    return reconst_path, self.calc_path_cost(reconst_path), debug
            for adj, cost in self.graph[n]:
                i = level[n] + 1
                if adj not in open_list and adj not in closed_list and not Graph.node_in_other_paths(n, adj, i, paths):
                    open_list.add(adj)
                    parents[adj] = n
                    level[adj] = i
                    costs[adj] = costs[n] + cost
                if len(open_list) == 1:
                    for adj, cost in self.graph[n]:
                        if adj == node:
                            remains_same_spot.append(adj)
                            open_list.add(adj)
                            level[adj] = i
                            costs[adj] = costs[n] + cost
                            break

            # remover n da open_list e adiciona-lo à closed_list - todos os seus vizinhos já foram inspecionados
            open_list.remove(n)
            closed_list.add(n)

        return None
