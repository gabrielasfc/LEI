import networkx as nx
import matplotlib.pyplot as plt
import math

from nodo import Node
from queue import Queue


class Graph:
    def __init__(self, directed=False):
        self.nodes = [] #lista de nodos
        self.directed = directed
        self.graph = {} #armazenar nodos, arestas  e custos

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
        total = math.inf
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

    def DFS(self, start, end, i, path=[], visited=set()):
        path.append(start)
        visited.add(start)

        # ver percurso
        if i==0:
            print("route: ", end='')
        print(start + " ", end='')

        if start == end:
            total_cost = self.calc_path_cost(path)
            print()
            return (path, total_cost)

        for (adj, cost) in self.graph[start]:
            if adj not in visited:
                i += 1
                ret = self.DFS(adj, end, i, path, visited)
                if ret is not None:
                    return ret

        path.pop() #se nao encontrar, remover o que está no caminho
        return None

    def BFS(self, start, end):
        visited = set()
        q = Queue()

        q.put(start)
        visited.add(start)

        #garantir que o start node nao tem pais
        parents = dict()
        parents[start] = None

        print("route: ", end='')

        path_found = False
        while not q.empty() and path_found == False:
            node = q.get()

            print(node + " ", end='') #ver percurso

            if node == end:
                path_found = True
                print()
            else:
                for (adj, cost) in self.graph[node]:
                    if adj not in visited:
                        q.put(adj)
                        parents[adj] = node
                        visited.add(adj)

        #reconstruir o caminho
        path = []
        if path_found:
            path.append(end)
            while parents[end] is not None:
                path.append(parents[end])
                end = parents[end]
            path.reverse()

            total_cost = self.calc_path_cost(path)
            return (path, total_cost)

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