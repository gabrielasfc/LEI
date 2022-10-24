from grafo import Graph
from nodo import Node


def main():
    g = Graph()

    g.add_edge("elvas", "borba", 15)
    g.add_edge("borba", "estremoz", 15)
    g.add_edge("estremoz", "evora", 40)
    g.add_edge("evora", "montemor", 20)
    g.add_edge("montemor", "vendasnovas", 15)
    g.add_edge("vendasnovas", "lisboa", 50)
    g.add_edge("elvas", "arraiolos", 50)
    g.add_edge("arraiolos", "alcacer", 90)
    g.add_edge("alcacer", "palmela", 35)
    g.add_edge("palmela", "almada", 25)
    g.add_edge("palmela", "barreiro", 25)
    g.add_edge("barreiro", "palmela", 30)
    g.add_edge("almada", "lisboa", 15)
    g.add_edge("elvas", "alandroal", 40)
    g.add_edge("alandroal", "redondo", 25)
    g.add_edge("redondo", "monsaraz", 30)
    g.add_edge("monsaraz", "barreiro", 120)
    g.add_edge("barreiro", "baixadabanheira", 5)
    g.add_edge("baixadabanheira", "moita", 7)
    g.add_edge("moita", "alcochete", 20)
    g.add_edge("alcochete", "lisboa", 20)

    g.add_heur("elvas", 270)
    g.add_heur("borba", 250)
    g.add_heur("estremoz", 145)
    g.add_heur("evora", 95)
    g.add_heur("montemor", 70)
    g.add_heur("vendasnovas", 45)
    g.add_heur("arraiolos", 220)
    g.add_heur("alcacer", 140)
    g.add_heur("palmela", 85)
    g.add_heur("almada", 25)
    g.add_heur("alandroal", 180)
    g.add_heur("redondo", 170)
    g.add_heur("monsaraz", 120)
    g.add_heur("barreiro", 30)
    g.add_heur("baixadabanheira", 33)
    g.add_heur("moita", 35)
    g.add_heur("alcochete", 26)
    g.add_heur("lisboa", 0)

    opt = -1
    while opt != 0:
        print("---------------------")
        print("1... Print graph")
        print("2... Print nodes")
        print("3... Print edges")
        print("4... Draw graph")
        print("5... Greedy")
        print("6... A*")
        print("0... Exit")
        print("---------------------")

        opt = int(input("Option: "))
        if opt == 1:
            print(g)

        elif opt == 2:
            print(g.graph.keys())

        elif opt == 3:
            print(g.print_edges())

        elif opt == 4:
            g.draw()

        elif opt == 5:
            start = input("Initial node: ")
            end = input("Final node: ")
            print(g.greedy(start, end))

        elif opt == 6:
            start = input("Initial node: ")
            end = input("Final node: ")
            print(g.a_star(start, end))

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

