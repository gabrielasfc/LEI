from drawer import *
from parser import *
from race import Race

SIZE_X = 900 // 2
SIZE_Y = 600 // 2
input_rect = pygame.Rect(380, 200, 140, 32)

iman_img = pygame.image.load("../circuits/img/iman.png")
iman_img = pygame.transform.scale(iman_img, (200, 200))

bahrain_img = pygame.image.load("../circuits/img/bahrain.png")
bahrain_img = pygame.transform.scale(bahrain_img, (200, 200))

oval_img = pygame.image.load("../circuits/img/oval.png")
oval_img = pygame.transform.scale(oval_img, (200, 200))

vector_img = pygame.image.load("../circuits/img/vector.png")
vector_img = pygame.transform.scale(vector_img, (200, 200))

rect_img = pygame.image.load("../circuits/img/rect.png")
rect_img = pygame.transform.scale(rect_img, (350, 50))

snake_img = pygame.image.load("../circuits/img/snake.png")
snake_img = pygame.transform.scale(snake_img, (200, 200))


def main_menu(circuits):
    """
    Menu para escolher circuito
    :param circuits: Lista dos circuitos
    """
    index = 0
    v_index = 0

    while True:
        screen.fill("white")
        draw_text("CIRCUITO", font_titulo, "black", screen, x // 2, y // 6)

        button = pygame.Rect(SIZE_X - 112.5, SIZE_Y - 120, 225, 65)
        pygame.draw.rect(screen, (255, 204, 102), button, border_radius=15)
        draw_shadow_text(screen, circuits[index][0], 30, x // 2, y // 2 - 87.5, font="freesansbold.ttf")

        new_circuit = pygame.Rect(SIZE_X - 75, SIZE_Y - 30, 150, 40)
        pygame.draw.rect(screen, (255, 204, 102), new_circuit, border_radius=15)
        draw_shadow_text(screen, "Novo circuito", 18, x // 2, y // 2 - 12, font="freesansbold.ttf")

        if v_index == 0:
            pygame.draw.rect(screen, "black", button, width=2, border_radius=15)
            draw_shadow_text(screen, ">", 50, x // 2 + 135, y // 2 - 90.5, colour=(255, 179, 26), font="freesansbold.ttf")
            draw_shadow_text(screen, "<", 50, x // 2 - 140, y // 2 - 90.5, colour=(255, 179, 26), font="freesansbold.ttf")
        elif v_index == 1:
            pygame.draw.rect(screen, "black", new_circuit, width=2, border_radius=15)

        if index == 0:
            screen.blit(iman_img, (SIZE_X - 100, 350))
        elif index == 1:
            screen.blit(bahrain_img, (SIZE_X - 100, 350))
        elif index == 2:
            screen.blit(oval_img, (SIZE_X - 100, 350))
        elif index == 3:
            screen.blit(vector_img, (SIZE_X - 100, 350))
        elif index == 4:
            screen.blit(rect_img, (SIZE_X - 175, 400))
        elif index == 5:
            screen.blit(snake_img, (SIZE_X - 100, 350))

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_RETURN:
                    if v_index == 0:
                        matrix, start, end = parser(circuits[index][1])
                        race = Race(matrix, start, end)
                        race.build_graph()

                        menu_choose_mode(race)
                    elif v_index == 1:
                        menu_import_circuit(circuits)

                elif event.key == pygame.K_LEFT and v_index == 0:
                    index = loop_index_left(index, len(circuits))
                    circuit = circuits[index]
                elif event.key == pygame.K_RIGHT and v_index == 0:
                    index = loop_index_right(index, len(circuits))
                    circuit = circuits[index]
                elif event.key == pygame.K_UP:
                    v_index = loop_index_left(v_index, 2)
                elif event.key == pygame.K_DOWN:
                    v_index = loop_index_right(v_index, 2)

        pygame.display.update()
        clock.tick(60)


def parse_circuit(circuit):
    """
    Função auxiliar para obter nome do circuito
    :param circuit: Nome do ficheiro
    :return: Nome do circuito
    """
    return circuit.split(".")[0].capitalize()


def menu_import_circuit(circuits):
    """
    Menu para adicionar um novo circuito à lista de circuitos
    :param circuits: Lista de circuitos
    """
    running = True
    user_text = ''
    button = pygame.Rect(SIZE_X - 112.5, SIZE_Y - 120, 225, 35)
    while running:
        screen.fill("white")
        draw_text("IMPORTAR CIRCUITO", font_titulo, "black", screen, x // 2, y // 6)

        text = font_pequena_pequena.render(user_text, 1, "black")
        screen.blit(text, (button.x+5, button.y+7))

        pygame.draw.rect(screen, "gray", button, width=3)
        button.w = max(225, text.get_width() + 10)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_RETURN or event.key == pygame.K_ESCAPE:
                    circuits.append((parse_circuit(user_text), "../circuits/" + user_text))
                    running = False
                elif event.key == pygame.K_BACKSPACE:
                    user_text = user_text[:-1]
                else:
                    user_text += event.unicode

        pygame.display.update()
        clock.tick(60)


def menu_choose_mode(race):
    """
    Menu para escolher o modo de jogo
    :param race: Race
    """
    running = True
    index = 0
    modes = ["Singleplayer", "Multiplayer"]

    while running:
        screen.fill("white")
        draw_text("MODO DE JOGO", font_titulo, "black", screen, x // 2, y // 5)

        button = pygame.Rect(SIZE_X - 112.5, SIZE_Y - 120, 225, 65)
        pygame.draw.rect(screen, (255, 204, 102), button, border_radius=15)
        pygame.draw.rect(screen, "black", button, width=2, border_radius=15)
        draw_shadow_text(screen, modes[index], 30, x // 2, y // 2 - 87.5, font="freesansbold.ttf")

        draw_shadow_text(screen, ">", 50, x // 2 + 135, y // 2 - 90.5, colour=(255, 179, 26), font="freesansbold.ttf")
        draw_shadow_text(screen, "<", 50, x // 2 - 140, y // 2 - 90.5, colour=(255, 179, 26), font="freesansbold.ttf")

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_RETURN:
                    if index == 0:
                        menu_choose_algorithm(race)
                    else:
                        menu_multiplayer(race)

                elif event.key == pygame.K_LEFT:
                    index = loop_index_left(index, 2)

                elif event.key == pygame.K_RIGHT:
                    index = loop_index_right(index, 2)

                elif event.key == pygame.K_ESCAPE:
                    running = False

        pygame.display.update()
        clock.tick(60)


def alg_handler(integer):
    """
    Função auxiliar para indicar o algoritmo respetivo
    :param integer: Indíce
    :return: Algoritmo respetivo
    """
    if integer == 0:
        return "BFS"
    elif integer == 1:
        return "DFS"
    elif integer == 2:
        return "Custo Uniforme"
    elif integer == 3:
        return "A*"
    elif integer == 4:
        return "Greedy"


def heur_handler(integer):
    """
    Função auxiliar para indicar a heurística respetiva
    :param integer: Índice
    :return: Heurística respetiva
    """
    if integer == 0:
        return "distance"
    elif integer == 1:
        return "velocity"


def menu_multiplayer_algorithms(players):
    """
    Menu para escolher os algoritmos dos diversos jogadores
    :param players: Jogadores
    """
    indexes = dict()
    heuristics = ["distance", "velocity"]

    for i in range(len(players)):
        indexes[i] = (0, (0, 0))

    running = True
    index = 0
    vert_index = 0

    while running:
        screen.fill("white")
        draw_text("ALGORITMOS DE PROCURA", font_titulo, "black", screen, x//2, y//5)

        # Botão Player
        button_player = pygame.Rect(SIZE_X - 112.5, SIZE_Y - 120, 225, 65)
        pygame.draw.rect(screen, (255, 204, 102), button_player, border_radius=15)
        draw_shadow_text(screen, f"Jogador {index}", 30, x//2, y//2 - 87.5, font="freesansbold.ttf")

        # Botão Algoritmo
        button_alg = pygame.Rect(SIZE_X - 112.5, SIZE_Y - 32.5, 225, 65)
        pygame.draw.rect(screen, (255, 179, 26), button_alg, border_radius=15)
        draw_shadow_text(screen, alg_handler(indexes[index][0]), 30, x//2, y//2)

        if vert_index == 0:
            pygame.draw.rect(screen, "black", button_player, width=2, border_radius=15)

            draw_shadow_text(screen, ">", 50, x // 2 + 135, y // 2 - 90.5, colour=(255, 179, 26), font="freesansbold.ttf")
            draw_shadow_text(screen, "<", 50, x // 2 - 140, y // 2 - 90.5, colour=(255, 179, 26), font="freesansbold.ttf")

            if indexes[index][0] == 3:
                button_heuristic = pygame.Rect(SIZE_X - 112.5, SIZE_Y + 55, 225, 65)
                pygame.draw.rect(screen, (255, 179, 26), button_heuristic, border_radius=10)
                draw_shadow_text(screen, heur_handler(indexes[index][1][0]), 30, x // 2, SIZE_Y + 85, font="freesansbold.ttf")

            elif indexes[index][0] == 4:
                button_heuristic = pygame.Rect(SIZE_X - 112.5, SIZE_Y + 55, 225, 65)
                pygame.draw.rect(screen, (255, 179, 26), button_heuristic, border_radius=10)
                draw_shadow_text(screen, heur_handler(indexes[index][1][1]), 30, x // 2, SIZE_Y + 85, font="freesansbold.ttf")

        elif vert_index == 1:
            pygame.draw.rect(screen, (255, 179, 26), button_player, border_radius=15)
            draw_shadow_text(screen, f"Jogador {index}", 30, x // 2, y // 2 - 87.5, font="freesansbold.ttf")

            pygame.draw.rect(screen, (255, 204, 102), button_alg, border_radius=15)
            draw_shadow_text(screen, alg_handler(indexes[index][0]), 30, x // 2, y // 2)
            pygame.draw.rect(screen, "black", button_alg, width=2, border_radius=15)

            draw_shadow_text(screen, ">", 50, x // 2 + 135, y // 2 - 5.5, colour=(255, 179, 26), font="freesansbold.ttf")
            draw_shadow_text(screen, "<", 50, x // 2 - 140, y // 2 - 5.5, colour=(255, 179, 26), font="freesansbold.ttf")

            if indexes[index][0] == 3:
                button_heuristic = pygame.Rect(SIZE_X - 112.5, SIZE_Y + 55, 225, 65)
                pygame.draw.rect(screen, (255, 179, 26), button_heuristic, border_radius=10)
                draw_shadow_text(screen, heur_handler(indexes[index][1][0]), 30, x // 2, SIZE_Y + 85, font="freesansbold.ttf")

            elif indexes[index][0] == 4:
                button_heuristic = pygame.Rect(SIZE_X - 112.5, SIZE_Y + 55, 225, 65)
                pygame.draw.rect(screen, (255, 179, 26), button_heuristic, border_radius=10)
                draw_shadow_text(screen, heur_handler(indexes[index][1][1]), 30, x // 2, SIZE_Y + 85, font="freesansbold.ttf")

        elif vert_index == 2:
            pygame.draw.rect(screen, (255, 179, 26), button_player, border_radius=15)
            draw_shadow_text(screen, f"Jogador {index}", 30, x // 2, y // 2 - 87.5, font="freesansbold.ttf")

            pygame.draw.rect(screen, (255, 179, 26), button_alg, border_radius=15)
            draw_shadow_text(screen, alg_handler(indexes[index][0]), 30, x // 2, y // 2)

            button_heuristic = pygame.Rect(SIZE_X - 112.5, SIZE_Y + 55, 225, 65)
            pygame.draw.rect(screen, (255, 204, 102), button_heuristic, border_radius=10)
            pygame.draw.rect(screen, "black", button_heuristic, width=2, border_radius=10)

            draw_shadow_text(screen, ">", 50, x // 2 + 135, y // 2 + 80.5, colour=(255, 179, 26), font="freesansbold.ttf")
            draw_shadow_text(screen, "<", 50, x // 2 - 140, y // 2 + 80.5, colour=(255, 179, 26), font="freesansbold.ttf")

            if indexes[index][0] == 3:
                draw_shadow_text(screen, heur_handler(indexes[index][1][0]), 30, x // 2, SIZE_Y + 85, font="freesansbold.ttf")
            elif indexes[index][0] == 4:
                draw_shadow_text(screen, heur_handler(indexes[index][1][1]), 30, x // 2, SIZE_Y + 85, font="freesansbold.ttf")

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    if indexes[index][0] == 3 or indexes[index][0] == 4:
                        vert_index = loop_index_left(vert_index, 3)
                    else:
                        vert_index = loop_index_left(vert_index, 2)

                elif event.key == pygame.K_DOWN:
                    if indexes[index][0] == 3 or indexes[index][0] == 4:
                        vert_index = loop_index_right(vert_index, 3)
                    else:
                        vert_index = loop_index_left(vert_index, 2)

                elif event.key == pygame.K_LEFT:
                    if vert_index == 0:
                        index = loop_index_left(index, len(players))
                    elif vert_index == 1:
                        ind1, ind2 = indexes[index]
                        indexes[index] = (loop_index_left(indexes[index][0], 5), ind2)
                    elif vert_index == 2:
                        if indexes[index][0] == 3:
                            ind1, ind2 = indexes[index]
                            ind21, ind22 = ind2
                            ind21 = loop_index_left(ind21, 2)
                            indexes[index] = (ind1, (ind21, ind22))
                        elif indexes[index][0] == 4:
                            ind1, ind2 = indexes[index]
                            ind21, ind22 = ind2
                            ind22 = loop_index_left(ind22, 2)
                            indexes[index] = (ind1, (ind21, ind22))

                elif event.key == pygame.K_RIGHT:
                    if vert_index == 0:
                        index = loop_index_right(index, len(players))
                    elif vert_index == 1:
                        ind1, ind2 = indexes[index]
                        indexes[index] = (loop_index_right(indexes[index][0], 5), ind2)
                    elif vert_index == 2:
                        if indexes[index][0] == 3:
                            ind1, ind2 = indexes[index]
                            ind21, ind22 = ind2
                            ind21 = loop_index_right(ind21, 2)
                            indexes[index] = (ind1, (ind21, ind22))
                        elif indexes[index][0] == 4:
                            ind1, ind2 = indexes[index]
                            ind21, ind22 = ind2
                            ind22 = loop_index_right(ind22, 2)
                            indexes[index] = (ind1, (ind21, ind22))

                elif event.key == pygame.K_RETURN:
                    running = False

                elif event.key == pygame.K_ESCAPE:
                    running = False

        pygame.display.update()
        clock.tick(60)

    return indexes


def menu_multiplayer(race):
    """
    Menu multiplayer
    :param race: Race
    """
    heuristics = dict()

    indexes = menu_multiplayer_algorithms(race.start)

    for i in range(len(indexes.keys())):
        race.player_algorithms[i] = indexes[i][0]
        if race.player_algorithms[i] == 3:
            heuristics[i] = heur_handler(indexes[i][1][0])
        elif race.player_algorithms[i] == 4:
            heuristics[i] = heur_handler(indexes[i][1][1])

    paths, costs = race.multiplayer(heuristics)

    screen.fill("white")
    x_total = 450 - ((len(race.matrix[0]) // 2) * 16) - 16
    y_total = 300 - (len(race.matrix) // 2) * 16
    draw_circuit(race.matrix, x_total, y_total, 16)
    draw_paths(paths, race.matrix, costs)


def menu_choose_algorithm(race):
    """
    Menu para escolher algoritmo (singleplayer)
    :param race: Race
    """
    running = True
    vert_index = 0
    index_alg = 0
    index_greedy = 0
    index_a = 0
    algorithms = ["BFS", "DFS", "Custo Uniforme", "A*", "Greedy"]
    heuristics = ["distance", "velocity"]

    while running:
        screen.fill("white")
        draw_text("ALGORITMO DE PROCURA", font_titulo, "black", screen, x // 2, y // 5)

        button_alg = pygame.Rect(SIZE_X - 112.5, SIZE_Y - 120, 225, 65)

        if vert_index == 0:
            pygame.draw.rect(screen, (255, 204, 102), button_alg, border_radius=15)
            draw_shadow_text(screen, algorithms[index_alg], 20, x // 2, y // 2 - 87.5, font="freesansbold.ttf")
            pygame.draw.rect(screen, "black", button_alg, width=2, border_radius=15)

            draw_shadow_text(screen, ">", 50, x // 2 + 135, y // 2 - 90.5, colour=(255, 179, 26), font="freesansbold.ttf")
            draw_shadow_text(screen, "<", 50, x // 2 - 140, y // 2 - 90.5, colour=(255, 179, 26), font="freesansbold.ttf")

            if index_alg == 3:
                button_heuristic = pygame.Rect(SIZE_X - 112.5, SIZE_Y - 32.5, 225, 65)
                pygame.draw.rect(screen, (255, 179, 26), button_heuristic, border_radius=10)
                draw_shadow_text(screen, heuristics[index_a], 30, x // 2, y // 2, font="freesansbold.ttf")

            elif index_alg == 4:
                button_heuristic = pygame.Rect(SIZE_X - 112.5, SIZE_Y - 32.5, 225, 65)
                pygame.draw.rect(screen, (255, 179, 26), button_heuristic, border_radius=10)
                draw_shadow_text(screen, heuristics[index_greedy], 30, x // 2, y // 2, font="freesansbold.ttf")

        elif vert_index == 1:
            pygame.draw.rect(screen, (255, 179, 26), button_alg, border_radius=15)
            draw_shadow_text(screen, algorithms[index_alg], 20, x // 2, y // 2 - 87.5, font="freesansbold.ttf")

            button_heuristic = pygame.Rect(SIZE_X - 112.5, SIZE_Y - 32.5, 225, 65)
            pygame.draw.rect(screen, (255, 204, 102), button_heuristic, border_radius=10)
            pygame.draw.rect(screen, "black", button_heuristic, width=2, border_radius=15)

            draw_shadow_text(screen, ">", 50, x // 2 + 135, y // 2 - 5.5, colour=(255, 179, 26), font="freesansbold.ttf")
            draw_shadow_text(screen, "<", 50, x // 2 - 140, y // 2 - 5.5, colour=(255, 179, 26), font="freesansbold.ttf")

            if index_alg == 3:
                draw_shadow_text(screen, heuristics[index_a], 30, x // 2, y // 2, font="freesansbold.ttf")
            elif index_alg == 4:
                draw_shadow_text(screen, heuristics[index_greedy], 30, x // 2, y // 2, font="freesansbold.ttf")

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    if vert_index == 0:
                        index_alg = loop_index_left(index_alg, 5)
                    else:
                        if index_alg == 3:
                            index_a = loop_index_left(index_a, 2)
                        elif index_alg == 4:
                            index_greedy = loop_index_left(index_greedy, 2)

                elif event.key == pygame.K_RIGHT:
                    if vert_index == 0:
                        index_alg = loop_index_right(index_alg, 5)
                    else:
                        if index_alg == 3:
                            index_a = loop_index_right(index_a, 2)
                        elif index_alg == 4:
                            index_greedy = loop_index_right(index_greedy, 2)

                elif event.key == pygame.K_DOWN:
                    if index_alg == 3 or index_alg == 4:
                        vert_index = loop_index_right(vert_index, 2)

                elif event.key == pygame.K_UP:
                    if index_alg == 3 or index_alg == 4:
                        vert_index = loop_index_left(vert_index, 2)

                elif event.key == pygame.K_RETURN:
                    player_index = menu_choose_player(race)
                    player = race.start[player_index]
                    screen.fill("white")
                    x_total = 450 - ((len(race.matrix[0]) // 2) * 16) - 16
                    y_total = 300 - (len(race.matrix) // 2) * 16

                    if index_alg == 0:
                        path, cost, debug = race.BFS_solution(player)
                        draw_circuit(race.matrix, x_total, y_total, 16)
                        draw_paths([(player_index, path)], race.matrix, [cost], debug)

                    if index_alg == 1:
                        path, cost, debug = race.DFS_solution(player)
                        draw_circuit(race.matrix, x_total, y_total, 16)
                        draw_paths([(player_index, path)], race.matrix, [cost], debug)

                    if index_alg == 2:
                        path, cost, debug = race.uniform_cost_solution(player)
                        draw_circuit(race.matrix, x_total, y_total, 16)
                        draw_paths([(player_index, path)], race.matrix, [cost], debug)

                    if index_alg == 3:
                        path, cost, debug = race.a_star_solution(player, heuristics[index_a])
                        draw_circuit(race.matrix, x_total, y_total, 16)
                        draw_paths([(player_index, path)], race.matrix, [cost], debug)

                    if index_alg == 4:
                        path, cost, debug = race.greedy_solution(player, heuristics[index_greedy])
                        draw_circuit(race.matrix, x_total, y_total, 16)
                        draw_paths([(player_index, path)], race.matrix, [cost], debug)

                elif event.key == pygame.K_ESCAPE:
                    running = False

        pygame.display.update()
        clock.tick(60)


def menu_choose_player(race):
    """
    Menu para escolher jogador (singleplayer)
    :param race: Race
    :return: Índice do jogador
    """
    running = True
    index = 0
    while running:
        screen.fill("white")
        draw_text("Jogador", font_titulo, "black", screen, x // 2, y // 5)

        # Botão Player
        button_player = pygame.Rect(SIZE_X - 112.5, SIZE_Y - 120, 225, 65)
        pygame.draw.rect(screen, (255, 204, 102), button_player, border_radius=15)
        pygame.draw.rect(screen, "black", button_player, width=2, border_radius=15)
        draw_shadow_text(screen, f"Jogador {index}", 30, x // 2, y // 2 - 87.5, font="freesansbold.ttf")

        draw_shadow_text(screen, ">", 50, x // 2 + 135, y // 2 - 90.5, colour=(255, 179, 26), font="freesansbold.ttf")
        draw_shadow_text(screen, "<", 50, x // 2 - 140, y // 2 - 90.5, colour=(255, 179, 26), font="freesansbold.ttf")

        draw_circuit(race.matrix, 450 - ((len(race.matrix[0]) // 2) * 10) - 10, 280, 10, index)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    index = loop_index_left(index, len(race.start))
                elif event.key == pygame.K_RIGHT:
                    index = loop_index_right(index, len(race.start))
                elif event.key == pygame.K_RETURN or event.key == pygame.K_ESCAPE:
                    running = False

        pygame.display.update()
        clock.tick(60)

    return index