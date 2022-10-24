from grafo import Graph
from nodo import Node


def main():
    g = Graph()

    g.add_edge("s", "e", 2)
    g.add_edge("s", "a", 2)
    g.add_edge("e", "f", 5)
    g.add_edge("a", "b", 2)
    g.add_edge("b", "c", 2)
    g.add_edge("c", "d", 3)
    g.add_edge("d", "t", 3)
    g.add_edge("g", "t", 2)
    g.add_edge("f", "g", 2)

    opt = -1
    while opt != 0:
        print("---------------------")
        print("1... Print graph")
        print("2... Print nodes")
        print("3... Print edges")
        print("4... Draw graph")
        print("5... DFS")
        print("6... BFS")
        print("0... Exit")
        print("---------------------")

        opt = int(input("Option: "))
        if opt == 1:
            print(g)

        elif opt == 2:
            print(g.m_graph.keys())

        elif opt == 3:
            print(g.print_edges())

        elif opt == 4:
            g.draw()

        elif opt == 5:
            start = input("Initial node: ")
            end = input("Final node: ")
            print(g.DFS(start, end, 0, [], set()))

        elif opt == 6:
            start = input("Initial node: ")
            end = input("Final node: ")
            print(g.BFS(start, end))

        elif opt == 0:
            exit()

        else:
            print("\nInvalid Option")
            exit()

        if input("\n0... Back ") != '0':
            print("Invalid Option")
            exit()


if __name__ == "__main__":
    main()

