import math
from enum import Enum


class DispResult(Enum):
    CRASH = 1
    ADVANCE = 2
    FINISH = 3


# Example: nextInt(3) = 4
#          nextInt(2.5) = 3
def next_int(num):
    """
    Calcula o primeiro inteiro que é maior que um dado número
    :param num: Número
    :return: Primeiro inteiro à direita do número indicado
    """
    if int(num) == num:
        return num + 1
    else:
        return math.ceil(num)


# Example: lastInt(3) = 2
#          nextInt(2.5) = 2
def last_int(num):
    """
    Calcula o primeiro inteiro que é menor que um dado número
    :param num: Número
    :return: Primeiro inteiro à esquerda do número indicado
    """
    if int(num) == num:
        return num - 1
    else:
        return math.floor(num)


def calculate_next_border_position(current_pos, disp):
    """
    Calcula a borda da proxima posição
    :param current_pos: Posição Atual
    :param disp: Deslocamento
    :return: Posição de fronteira com a próxima posição
    """
    if disp[1] == 0:  # Horizontal displacement
        if disp[0] < 0:
            return last_int(current_pos[0]), current_pos[1]
        elif disp[0] > 0:
            return next_int(current_pos[0]), current_pos[1]

    elif disp[0] == 0:  # Vertical displacement
        if disp[1] < 0:
            return current_pos[0], last_int(current_pos[1])
        elif disp[1] > 0:
            return current_pos[0], next_int(current_pos[1])

    grad = disp[1] / disp[0]  # Gradient

    # Calculate next X value
    if disp[0] < 0:  # To the left
        next_value_horiz = last_int(current_pos[0])
    else:  # To the right
        next_value_horiz = next_int(current_pos[0])

    inc = next_value_horiz - current_pos[0]

    aux_pos = (current_pos[0] + inc, current_pos[1] + grad * inc)  # Calculate f(next_value_horiz)

    # Upward disp
    if disp[1] > 0 and aux_pos[1] > next_int(current_pos[1]):  # If f(next_value_horiz) is greater than upper limit of square
        x = (next_int(current_pos[1]) - current_pos[1] + current_pos[0] * grad) / grad  # Formula: x = (y-b+a*m)/m
        return x, next_int(current_pos[1])

    # Downward disp
    elif disp[1] < 0 and aux_pos[1] < last_int(current_pos[1]):  # If f(next_value_horiz) is less than upper limit of square
        x = (last_int(current_pos[1]) - current_pos[1] + current_pos[0] * grad) / grad  # Formula: x = (y-b+a*m)/m
        return x, last_int(current_pos[1])

    else:
        return aux_pos


# Get the object in that map position
def get_map_object(position, map):
    """
    Destaca o objeto numa posição no mapa
    :param position: Posição a verificar
    :param map: mapa
    :return: objeto nessa posição (ex: 'X' or '-')
    """
    map_position = (math.floor(position[0]), math.floor(position[1]))
    matrix_line = len(map) - map_position[1] - 1
    matrix_column = map_position[0]
    return map[matrix_line][matrix_column]


# Get middle position of the next square, given border_position and displacement
def get_middle_position(border_position, displ):
    """
    Obtem a posição intemédia de um quadrado dada posição da borda e o deslocamento
    :param border_position: Posição da borda
    :param displ: Deslocamento
    :return: Posição do meio do quadrado
    """
    if int(border_position[1]) == border_position[1] and int(border_position[0]) == border_position[0]: # Case (int, int)
        if displ[0] < 0 and displ[1] < 0:  # esquerda baixo
            return (border_position[0] - 0.5, border_position[1] - 0.5)  # Next position block

        elif displ[0] < 0 and displ[1] > 0:  # esquerda cima
            return (border_position[0] - 0.5, border_position[1] + 0.5)

        elif displ[0] > 0 and displ[1] < 0:  # direita baixo
            return (border_position[0] + 0.5, border_position[1] - 0.5)

        elif displ[0] > 0 and displ[1] > 0:  # direita cima
            return (border_position[0] + 0.5, border_position[1] + 0.5)

    if int(border_position[1]) == border_position[1]:  # Case (float, int)
        if displ[0] == 0:  # Vertical motion
            return border_position[0], border_position[1] + displ[1] / (abs(displ[1]) * 2)
        else:
            return math.floor(border_position[0]) + 0.5, border_position[1] + (displ[1] / (abs(displ[1]) * 2))
    else:  # Case (int, float)
        if displ[1] == 0:  # Horizontal motion
            return border_position[0] + displ[0] / (abs(displ[0]) * 2), border_position[1]
        else:
            return border_position[0] + (displ[0] / (abs(displ[0]) * 2)), math.floor(border_position[1]) + 0.5


def calculate_disp_result(border_position, displ, map):
    """
    Calcula o resultado do deslocamento
    :param border_position: Posição da borda
    :param displ: Deslocamento
    :param map: mapa (matriz)
    :return: Posição (é sempre o centro de um quadrado)
    """
    if int(border_position[0]) == border_position[0] and int(border_position[1]) == border_position[1]:  # Esquina
        if displ[0] < 0 and displ[1] < 0:  # esquerda baixo
            first_point = (border_position[0] - 0.5, border_position[1] + 0.5)  # Can block displacement
            second_point = (border_position[0] + 0.5, border_position[1] - 0.5)  # Can block displacement
            third_point = (border_position[0] - 0.5, border_position[1] - 0.5)  # Next position block

        elif displ[0] < 0 and displ[1] > 0:  # esquerda cima
            first_point = (border_position[0] - 0.5, border_position[1] - 0.5)
            second_point = (border_position[0] + 0.5, border_position[1] + 0.5)
            third_point = (border_position[0] - 0.5, border_position[1] + 0.5)

        elif displ[0] > 0 and displ[1] < 0:  # direita baixo
            first_point = (border_position[0] + 0.5, border_position[1] + 0.5)
            second_point = (border_position[0] - 0.5, border_position[1] - 0.5)
            third_point = (border_position[0] + 0.5, border_position[1] - 0.5)

        elif displ[0] > 0 and displ[1] > 0:  # direita cima
            first_point = (border_position[0] - 0.5, border_position[1] + 0.5)
            second_point = (border_position[0] + 0.5, border_position[1] - 0.5)
            third_point = (border_position[0] + 0.5, border_position[1] + 0.5)

        obj_first_point = get_map_object(first_point, map)
        obj_second_point = get_map_object(second_point, map)
        obj_third_point = get_map_object(third_point, map)

        if obj_first_point == 'X' or obj_second_point == 'X' or obj_third_point == 'X' or obj_first_point == 'P' or obj_second_point == 'P' or obj_third_point == 'P':
            return DispResult.CRASH
        elif obj_third_point == 'F':
            return DispResult.FINISH
        else:
            return DispResult.ADVANCE

    # Case (int, float) or (float, int)
    middle_position = get_middle_position(border_position, displ)

    # Get object inside the square
    obj_in_square = get_map_object(middle_position, map)

    if obj_in_square == 'X':
        return DispResult.CRASH
    elif obj_in_square == 'F':
        return DispResult.FINISH
    else:
        return DispResult.ADVANCE


def calculate_stop_position(current_pos, disp, map):
    """
    Calcula a posição onde pára
    :param current_pos: Posição Atual
    :param disp: Deslocamento
    :param map: mapa
    :return: Posição e deslocamento
    """
    # Partindo da posição, até chegar à posição final, procura a próxima interseção com uma fronteira
    if disp == (0, 0):
        return current_pos, DispResult.ADVANCE

    i = 0

    while i < abs(disp[0]) + abs(disp[1]):
        current_pos = calculate_next_border_position(current_pos, disp)  # Calculate position when leaving the square
        displacement_result = calculate_disp_result(current_pos, disp, map)  # Calculate object in next Square or Squares
        is_int_x = int(current_pos[0]) == current_pos[0]
        is_int_y = int(current_pos[1]) == current_pos[1]

        if is_int_x and is_int_y and displacement_result == DispResult.CRASH:
            final_position = (
                current_pos[0] - (disp[0] / abs(disp[0])) * 0.5, current_pos[1] - (disp[1] / abs(disp[1])) * 0.5)
            return final_position, displacement_result

        elif is_int_x and is_int_y and displacement_result == DispResult.FINISH:
            final_position = (
                current_pos[0] + (disp[0] / abs(disp[0])) * 0.5, current_pos[1] + (disp[1] / abs(disp[1])) * 0.5)
            return final_position, displacement_result

        if displacement_result == DispResult.CRASH:
            final_position = get_middle_position(current_pos, (-1 * disp[0], -1 * disp[1])) # Return last position, before wall
            return final_position, displacement_result

        elif displacement_result == DispResult.FINISH:
            final_position = get_middle_position(current_pos, disp)
            return final_position, displacement_result

        if is_int_x and is_int_y:
            i += 1

        i += 1

    final_position = get_middle_position(current_pos, disp)
    displacement_result = DispResult.ADVANCE
    return final_position, displacement_result


def squares_visited(start_pos, disp):
    """
    Calcula as posições por onde passa ao efetuar um certo deslocamento
    :param start_pos: Posição inicial
    :param disp: Deslocamento
    :return: Lista das posições
    """
    squares_visited = list()

    i = 0
    current_pos = start_pos

    while i < abs(disp[0]) + abs(disp[1]):
        current_pos = calculate_next_border_position(current_pos, disp)  # Calculate position when leaving the square
        middle_pos = get_middle_position(current_pos, disp)
        squares_visited.insert(i, middle_pos)

        is_int_x = int(current_pos[0]) == current_pos[0]
        is_int_y = int(current_pos[1]) == current_pos[1]

        if is_int_x and is_int_y:
            i += 1
        i += 1

    return squares_visited
