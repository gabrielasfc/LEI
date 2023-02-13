from node import Node
from graph import Graph
import position_calculator
import math


class Race:
    def __init__(self, matrix, start, end):
        """
        Construtor de uma corrida
        :param matrix: Matriz
        :param start: Posições iniciais
        :param end: Posições finais
        """
        self.matrix = matrix
        self.graph = Graph()
        self.start = list()
        self.end = list()
        self.player_algorithms = dict()

        for pos in start:
            self.start.append(Node(pos, (0, 0), False))

        for pos in end:
            self.end.append(Node(pos, (-1, -1), False))

    def __str__(self):
        """
        Devolve a representação em string do objeto Race
        :return: String
        """
        return str(self.matrix) + str(self.graph)

    @staticmethod
    def next_state(state, accel_pair, mat):
        """
        Calcula o próximo estado
        :param state: Estado atual
        :param accel_pair: Aceleração
        :param mat: Matriz
        :return: Nodo seguinte
        """
        disp = (state.vel[0] + accel_pair[0], state.vel[1] + accel_pair[1])

        (new_position, action) = position_calculator.calculate_stop_position(state.pos, disp, mat)

        new_vel = (state.vel[0] + accel_pair[0], state.vel[1] + accel_pair[1])

        if action == position_calculator.DispResult.CRASH:
            new_vel = (0, 0)

        is_crashed = False
        if action == position_calculator.DispResult.CRASH:
            is_crashed = True

        return Node(new_position, new_vel, is_crashed)

    def expand_state(self, state, mat):
        """
        Expande um dado estado em novos estados
        :param state: Estado atual
        :param mat: Matriz
        :return: Lista com os novos estados
        """
        nodes = list()
        found = False
        accelerations = [(1, 1), (1, -1), (1, 0), (-1, 1), (-1, -1), (0, -1), (-1, 0), (0, 0), (0, 1)]

        for end in self.end:
            if state.pos == end.pos:
                found = True

        if not found:
            for accel in accelerations:
                s = self.next_state(state, accel, mat), accel
                nodes.append(s)

        return nodes

    @staticmethod
    def calculate_shorter_distance(curr_state, pos_list):
        """
        Calcula a menor distância
        :param curr_state: Estado atual
        :param pos_list: Lista de posições
        :return: Menor distância
        """
        distance = math.inf

        for final_state in pos_list:
            temp = math.dist(curr_state.pos, final_state.pos)
            if temp < distance:
                distance = temp

        return distance

    def build_graph(self):
        """
        Constrói um grafo
        """
        states = set()
        visited = set()
        for start in self.start:
            states.add(start)
            visited.add(start)

        while states:
            state = states.pop()
            visited.add(state)
            expansion = self.expand_state(state, self.matrix)

            for e, accel in expansion:
                if e.crashed:
                    e.crashed = False
                    self.graph.add_edge(state, e, 25)
                else:
                    self.graph.add_edge(state, e, 1)

                if e not in visited:
                    states.add(e)

            self.graph.add_heuristic(state, Race.calculate_shorter_distance(state, self.end),
                                     "distance")  # distância às posiçoes finais
            self.graph.add_heuristic(state, -(math.sqrt(state.vel[0] ** 2 + state.vel[1] ** 2)),
                                     "velocity")  # velocidade atual

    def DFS_solution(self, initial_state, paths=dict()):
        """
        Aplica o algoritmo DFS
        :param initial_state: Estado inicial
        :param paths: Dicionário com os caminhos dos vários jogadores (multiplayer)
        :return: Caminho final, custo da solução e posições visitadas para debug
        """
        debug = list()
        visited = set()
        path, cost = self.graph.DFS(initial_state, self.end, visited, debug=debug, paths=paths)
        return path, cost, debug

    def BFS_solution(self, initial_state, paths=dict()):
        """
        Aplica o algoritmo BFS
        :param initial_state: Estado inicial
        :param paths: Dicionário com os caminhos dos vários jogadores (multiplayer)
        :return: Caminho final, custo da solução e posições visitadas para debug
        """
        path, cost, debug = self.graph.BFS(initial_state, self.end, paths)
        return path, cost, debug

    def uniform_cost_solution(self, initial_state, paths=dict()):
        """
        Aplica o algoritmo do Custo Uniforme
        :param initial_state: Estado inicial
        :param paths: Dicionário com os caminhos dos vários jogadores (multiplayer)
        :return: Caminho final, custo da solução e posições visitadas para debug
        """
        path, cost, debug = self.graph.uniform_cost(initial_state, self.end, paths)
        return path, cost, debug

    def a_star_solution(self, initial_state, type, paths=dict()):
        """
        Aplica o algoritmo A*
        :param initial_state: Estado inicial
        :param type: Tipo de heurística
        :param paths: Dicionário com os caminhos dos vários jogadores (multiplayer)
        :return: Caminho final, custo da solução e posições visitadas para debug
        """
        path, cost, debug = self.graph.a_star(initial_state, self.end, type, paths)
        return path, cost, debug

    def greedy_solution(self, initial_state, type, paths=dict()):
        """
        Aplica o algoritmo Greedy
        :param initial_state: Estado inicial
        :param type: Tipo de heurística
        :param paths: Dicionário com os caminhos dos vários jogadores (multiplayer)
        :return: Caminho final, custo da solução e posições visitadas para debug
        """
        path, cost, debug = self.graph.greedy(initial_state, self.end, type, paths)
        return path, cost, debug

    def multiplayer(self, heuristics):
        """
        Executa o modo multiplayer
        :param Lista de tuplos (índice do jogador, caminho percorrido (lista de nodos)) ordenada pelo tamanho do caminho percorrido,
               sendo a primeira posição da lista o tuplo com menor caminho
        """
        players = self.start
        paths = dict()
        costs = list()

        for i in range(len(players)):
            match self.player_algorithms[i]:
                case 0:
                    path, cost, debug = self.BFS_solution(players[i], paths)
                    paths[i] = path
                    costs.append(cost)
                case 1:
                    path, cost, debug = self.DFS_solution(players[i], paths)
                    paths[i] = path
                    costs.append(cost)
                case 2:
                    path, cost, debug = self.uniform_cost_solution(players[i], paths)
                    paths[i] = path
                    costs.append(cost)
                case 3:
                    path, cost, debug = self.a_star_solution(players[i], heuristics[i], paths)
                    paths[i] = path
                    costs.append(cost)
                case 4:
                    path, cost, debug = self.greedy_solution(players[i], heuristics[i], paths)
                    paths[i] = path
                    costs.append(cost)

        return sorted(paths.items(), key=lambda x: len(x[1])), costs
