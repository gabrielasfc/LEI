class Node:
    def __init__(self, pos, vel, crashed):
        """
        Construtor de um nodo
        :param pos: Posição
        :param vel: Velocidade
        :param crashed: Bool a verificar se embateu
        """
        self.pos = pos
        self.vel = vel
        self.crashed = crashed

    def __str__(self):
        """
        Devolve a representação em string do objeto Node
        :return: String
        """
        return "Position =" + str(self.pos) + " | Velocity=" + str(self.vel) + " | Is_Crashed : " + str(self.crashed)

    def __eq__(self, other):
        """
        Verifica se o objeto é igual ao objeto passado como argumento
        :param other: Nodo a comparar
        :return: True caso sejam iguais, False caso contrário
        """
        return self.pos == other.pos and self.vel == other.vel and self.crashed == other.crashed

    def __hash__(self):
        """
        Devolve o hash value do objeto
        :return: Hash value
        """
        return hash((self.pos, self.vel))

    @staticmethod
    def calculate_displacement(pos1, pos2):
        """
        Calcula o deslocamento entre duas posições
        :param pos1: Posição A
        :param pos2: Posição B
        :return: Deslocamento no eixo do x e y
        """
        dispx = pos2[0] - pos1[0]
        dispy = pos2[1] - pos1[1]
        return dispx, dispy
