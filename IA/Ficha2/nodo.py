class Node:
    def __init__(self, name):
        self.name = str(name)
        #Posteriormente colocar o objeto que o nodo vai referenciar...

    def __str__(self):
        return "node " + self.name

    #Devolve representação 'oficial' do objeto, neste caso particular pode ser igual a __str__
    def __repr__(self):
        return "node " + self.name

    def get_name(self):
        return self.name

    def set_name(self, name):
        self.name = name

    #2 nodos são iguais se os nomes forem iguais
    def __eq__(self, other):
        return self.name == other.name

    #Devolve o hash de um nodo. Ao implementar o método __eq__
    #torna-se também necessário definir __hash__. Caso
    #contrário o objeto torna-se unhashable
    def __hash__(self):
        return hash(self.name)
