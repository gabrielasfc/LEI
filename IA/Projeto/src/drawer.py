import time
import pygame
from pygame.locals import *

pygame.init()
pygame.display.set_caption('Vector Race')
x = 900
y = 600
screen = pygame.display.set_mode((x, y))
clock = pygame.time.Clock()
font_titulo = pygame.font.Font('freesansbold.ttf', 40)
font_pequena_pequena = pygame.font.Font('freesansbold.ttf', 18)
font_custo = pygame.font.Font('freesansbold.ttf', 14)


def loop_index_left(index, len):
    """
    Função auxiliar que devolve o novo índice ao ir para a esquerda
    :param index: Índice atual
    :param len: Comprimento da lista
    :return: Novo índice
    """
    if index - 1 == -1:
        return len - 1
    else:
        return index - 1


def loop_index_right(index, len):
    """
    Função auxiliar que devolve o novo índice ao ir para a direita
    :param index: Índice atual
    :param len: Comprimento da lista
    :return: Novo índice
    """
    if index + 1 == len:
        return 0
    else:
        return index+1


def draw_text(text, font, color, surface, x, y):
    """
    Desenha o texto
    """
    textobj = font.render(text, 1, color)
    textrect = textobj.get_rect()
    textrect.center = (x, y)
    surface.blit(textobj, textrect)


def draw_shadow_text(screen, text, size, x, y, colour=(255,255,255), drop_colour=(77, 77, 77), font=None):
    """
    Desenha texto com sombra
    """
    dropshadow_offset = 1 + (size // 15)
    text_font = pygame.font.Font(font, size)

    # make the drop-shadow
    text_bitmap = text_font.render(text, True, drop_colour)
    text_rect = text_bitmap.get_rect()
    text_rect.center = (x+dropshadow_offset, y+dropshadow_offset)
    screen.blit(text_bitmap, text_rect)

    # make the overlay text
    text_bitmap = text_font.render(text, True, colour)
    text_rect = text_bitmap.get_rect()
    text_rect.center = (x, y)
    screen.blit(text_bitmap, text_rect)


def draw_circuit(matrix, x_total, y_total, pixel, player=-1):
    """
    Desenha o circuito
    """
    x_draw = x_total
    y_draw = y_total
    walls = list()
    finish = list()
    start = list()
    players = list()
    track = list()

    for row in matrix:
        for col in row:
            if col == "X":
                walls.append(pygame.Rect(x_draw, y_draw, pixel, pixel))
            elif col == "P":
                start.append(pygame.Rect(x_draw, y_draw, pixel, pixel))
                players.append((x_draw + (pixel//2) + 0.5, y_draw + (pixel//2) + 0.5))
            elif col == "F":
                finish.append(pygame.Rect(x_draw, y_draw, pixel, pixel))
            elif col == "-":
                track.append(pygame.Rect(x_draw, y_draw, pixel, pixel))
            x_draw += pixel
        y_draw += pixel
        x_draw = x_total

    for w in walls:
        pygame.draw.rect(screen, "white", w)

    for f in finish:
        pygame.draw.rect(screen, (255, 0, 0), f)
    for t in track:
        pygame.draw.rect(screen, (41, 41, 61), t)

    for s in start:
        pygame.draw.rect(screen, (51, 204, 51), s)

    if player != -1:
        pygame.draw.rect(screen, (255, 153, 0), start[player])


def draw_debug_frame(matrix, debug, index):
    """
    Desenha um frame do modo debug
    """
    x_total = 450 - ((len(matrix[0]) // 2) * 16) - 16
    y_total = 300 - (len(matrix) // 2) * 16

    curr_pos = debug[index]
    curr_pos = (x_total + curr_pos[0] * 16, y_total + len(matrix) * 16 - curr_pos[1] * 16)
    pygame.draw.circle(screen, "darkorange", curr_pos, 5)


def draw_debug(matrix, debug):
    """
    Simulação para o modo debug
    """
    running = True
    index = 0
    x_total = 450 - ((len(matrix[0]) // 2) * 16) - 16
    y_total = 300 - (len(matrix) // 2) * 16
    screen.fill("white")
    draw_circuit(matrix, x_total, y_total, 16)
    draw_text("DEBUG", font_titulo, "black", screen, x // 2, y // 10)
    while running:
        keys = pygame.key.get_pressed()

        if keys[K_LEFT]:
            index = loop_index_left(index, len(debug))
            screen.fill("white")
            draw_circuit(matrix, x_total, y_total, 16)
            draw_text("DEBUG", font_titulo, "black", screen, x // 2, y // 10)
            draw_debug_frame(matrix, debug, index)
        elif keys[K_RIGHT]:
            index = loop_index_right(index, len(debug))
            screen.fill("white")
            draw_circuit(matrix, x_total, y_total, 16)
            draw_text("DEBUG", font_titulo, "black", screen, x // 2, y // 10)
            draw_debug_frame(matrix, debug, index)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    index = loop_index_left(index, len(debug))
                    screen.fill("white")
                    draw_circuit(matrix, x_total, y_total, 16)
                    draw_text("DEBUG", font_titulo, "black", screen, x // 2, y // 10)
                    draw_debug_frame(matrix, debug, index)
                elif event.key == pygame.K_RIGHT:
                    index = loop_index_right(index, len(debug))
                    screen.fill("white")
                    draw_circuit(matrix, x_total, y_total, 16)
                    draw_text("DEBUG", font_titulo, "black", screen, x // 2, y // 10)
                    draw_debug_frame(matrix, debug, index)
                elif event.key == pygame.K_ESCAPE:
                    screen.fill("white")
                    draw_circuit(matrix, x_total, y_total, 16)
                    running = False

        pygame.display.update()
        clock.tick(30)


def draw_final_path(path, matrix, x_total, y_total, cost, color):
    """
    Desenha o caminho final
    """
    for i in range(len(path[1])):
        final_pos = path[1][i].pos
        final_pos = (x_total + final_pos[0] * 16, y_total + len(matrix) * 16 - final_pos[1] * 16)
        if i > 0:
            start_pos = path[1][i - 1].pos
            start_pos = (x_total + start_pos[0] * 16, y_total + len(matrix) * 16 - start_pos[1] * 16)
            pygame.draw.circle(screen, color, start_pos, 5)
            pygame.draw.line(screen, color, start_pos, final_pos, 2)
        pygame.draw.circle(screen, color, final_pos, 5)

    draw_text(f"J {path[0]} : Custo {cost}", font_custo, color, screen, 60, 30 + 20*path[0])


def draw_until_frame(paths, matrix, x_total, y_total, index, costs):
    """
    Desenha o caminho até uma determinada iteração
    """
    colors = ['darkorange', 'darkviolet', 'royalblue', 'turquoise', 'seagreen', 'pink', 'saddlebrown', 'palegreen',
          'maroon', (230, 0, 230), (255, 255, 0), (153, 51, 0), (204, 179, 255), (51, 102, 0), (255, 255, 255)]
    for j in range(len(paths)):
        if index + 1 < len(paths[j][1]):
            for i in range(index+1):
                final_pos = paths[j][1][i].pos
                final_pos = (x_total + final_pos[0] * 16, y_total + len(matrix) * 16 - final_pos[1] * 16)
                if i > 0:
                    start_pos = paths[j][1][i - 1].pos
                    start_pos = (x_total + start_pos[0] * 16, y_total + len(matrix) * 16 - start_pos[1] * 16)
                    pygame.draw.circle(screen, colors[j], start_pos, 5)
                    pygame.draw.line(screen, colors[j], start_pos, final_pos, 2)

                pygame.draw.circle(screen, colors[j], final_pos, 5)
        else:
            draw_final_path(paths[j], matrix, x_total, y_total, costs[j], colors[j])


def draw_paths(paths, matrix, costs, debug=[]):
    """
    Simulação
    """
    x_total = 450 - ((len(matrix[0]) // 2) * 16) - 16
    y_total = 300 - (len(matrix) // 2) * 16
    max_len = len(paths[0])

    for path in paths:
        if len(path[1]) > max_len:
            max_len = len(path[1])

    i = 1
    index = 0
    running = True
    while running:
        time.sleep(0.15)
        keys = pygame.key.get_pressed()

        if keys[K_LEFT]:
            index = loop_index_left(index, max_len)
            draw_circuit(matrix, x_total, y_total, 16)
            draw_until_frame(paths, matrix, x_total, y_total, index, costs)
        elif keys[K_RIGHT]:
            index = loop_index_right(index, max_len)
            draw_circuit(matrix, x_total, y_total, 16)
            draw_until_frame(paths, matrix, x_total, y_total, index, costs)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    index = loop_index_left(index, max_len)
                    draw_circuit(matrix, x_total, y_total, 16)
                    draw_until_frame(paths, matrix, x_total, y_total, index, costs)
                elif event.key == pygame.K_RIGHT:
                    index = loop_index_right(index, max_len)
                    draw_circuit(matrix,  x_total, y_total, 16)
                    draw_until_frame(paths, matrix, x_total, y_total, index, costs)
                elif event.key == pygame.K_d and len(paths) == 1:
                    draw_debug(matrix, debug)
                elif event.key == pygame.K_ESCAPE:
                    running = False

        clock.tick(60)
        pygame.display.update()
        i += 1