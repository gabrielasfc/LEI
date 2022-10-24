import networkx as nx
import matplotlib.pyplot as plt

from nodo import Node


class Graph:
    def __init__(self, directed=False):
        self.nodes = [] #lista de nodos
        self.directed = directed
        self.graph = {} #armazenar nodos, arestas  e custos
        self.heur = {} #armazenar heurísticas

    def __str__(self):
        out = ""
        for key in self.graph.keys():
            out = out + "\nnode " + str(key) + ": " + str(self.graph[key])
        return out

    def add_edge(self, node1, node2, cost):
        n1 = Node(node1)
        n2 = Node(node2)

        if n1 not in self.nodes:
            self.nodes.append(n1)
            self.graph[node1] = set()
        else:
            n1 = self.get_node_by_name(node1)

        if n2 not in self.nodes:
            self.nodes.append(n2)
            self.graph[node2] = set()
        else:
            n2 = self.get_node_by_name(node2)

        self.graph[node1].add((node2, cost))

        #se o grafo for nao direcionado, colocar a aresta inversa
        if not self.directed:
            self.graph[node2].add((node1, cost))

    def get_node_by_name(self, name):
        search_node = Node(name)
        for node in self.nodes:
            if node == search_node:
                return node

        return None

    def get_arc_cost(self, node1, node2):
        total = 0
        adjs = self.graph[node1] #lista de arestas para aquele nodo
        for (node, cost) in adjs:
            if node == node2:
                total = cost

        return total

    def calc_path_cost(self, path):
        total = 0
        i = 0
        while i < len(path)-1:
             total += self.get_arc_cost(path[i], path[i+1])
             i += 1
        return total

    def add_heur(self, node, val):
            n = Node(node)
            if n in self.nodes:
                self.heur[node] = val

    def get_neighbours(self, node):
        adjs = []
        for (adj, cost) in self.graph[node]:
            adjs.append((adj, cost))

        return adjs

    def greedy(self, start, end):
        open_list = set([start]) #nodos visitados + vizinhos que ainda não foram todos visitados
        closed_list = set([]) #visitados

        parents = {}
        parents[start] = start

        print("route: ", end='')

        while len(open_list) > 0:
            n = next(iter(open_list))

            #encontra nodo com a menor heuristica
            for v in open_list:
                if self.heur[v] < self.heur[n]:
                    n = v

            print(n + " ", end='') #ver percurso

            #se o nodo corrente é o destino
            #reconstruir o caminho a partir desse nodo até ao start seguindo o antecessor
            if n == end:
                print()
                reconst_path = []

                while parents[n] != n:
                    reconst_path.append(n)
                    n = parents[n]

                reconst_path.append(start)

                reconst_path.reverse()

                return (reconst_path, self.calc_path_cost(reconst_path))

            #para todos os vizinhos  do nodo corrente
            for (adj, cost) in self.get_neighbours(n):
                # Se o nodo corrente nao esta na open nem na closed list
                # adiciona-lo à open_list e marcar o antecessor
                if adj not in open_list and adj not in closed_list:
                    open_list.add(adj)
                    parents[adj] = n

            # remover n da open_list e adiciona-lo à closed_list - todos os seus vizinhos já foram inspecionados
            open_list.remove(n)
            closed_list.add(n)

        print('Path does not exist!')
        return None

    def a_star(self, start, end):
        open_list = set([start]) #nodos visitados + vizinhos que ainda não foram todos visitados
        closed_list = set([]) #nodos visitados

        parents = {}
        parents[start] = start

        accmd_costs = {} #guardar custos acumulados
        accmd_costs[start] = 0

        print("route: ", end='')

        while len(open_list) > 0:
            n = next(iter(open_list))

            #encontra nodo com a menor heuristica
            for v in open_list:
                if accmd_costs[parents[v]] + self.get_arc_cost(parents[v], v) + self.heur[v] < accmd_costs[parents[n]] + self.get_arc_cost(parents[n], n) + self.heur[n]:
                    n = v

            print(n + " ", end='') #ver percurso

            #se o nodo corrente é o destino
            #reconstruir o caminho a partir desse nodo até ao start seguindo o antecessor
            if n == end:
                print()
                reconst_path = []

                while parents[n] != n:
                    reconst_path.append(n)
                    n = parents[n]

                reconst_path.append(start)

                reconst_path.reverse()

                return (reconst_path, self.calc_path_cost(reconst_path))

            accmd_costs[n] = accmd_costs[parents[n]] + self.get_arc_cost(parents[n], n)

            # para todos os vizinhos  do nodo corrente
            for (adj, cost) in self.get_neighbours(n):
                # Se o nodo corrente nao esta na open nem na closed list
                # adiciona-lo à open_list e marcar o antecessor
                if adj not in open_list and adj not in closed_list:
                    open_list.add(adj)
                    parents[adj] = n

            # remover n da open_list e adiciona-lo à closed_list - todos os seus vizinhos já foram inspecionados
            open_list.remove(n)
            closed_list.add(n)

        print('Path does not exist!')
        return None

    def print_edges(self):
        l = ""
        for node in self.graph.keys():
            for (adj, cost) in self.graph[node]:
                l = l + node + " -> " + adj + " cost:" + str(cost) + "\n"
        return l

    def draw(self):
        verts = self.nodes
        g = nx.Graph()

        #Converter para o formato usado pela biblioteca networkx
        for node in verts:
            n = node.getName()
            g.add_node(n)
            for (adj, cost) in self.graph[n]:
                l = (n, adj)
                g.add_edge(n, adj, cost)

        #desenhar o grafo
        pos = nx.spring_layout(g)
        nx.draw_networkx(g, pos, with_labels=True, font_weight='bold')
        labels = nx.get_edge_attributes(g, 'cost')
        nx.draw_networkx_edge_labels(g, pos, edge_labels=labels)

        plt.draw()
        plt.show()