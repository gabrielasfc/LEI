{-|
Module      : Tarefa5
Description : Movimentação dos fantasmas
Copyright   : Daniel Furtado <a97327@alunos.uminho.pt>;
              Gabriela Cunha <a97393@alunos.uminho.pt>

= Introdução

Na Tarefa 5 foi-nos atribuída a tarefa onde conseguíssemos implementar um comportamento eficiente nos Ghosts para que assim conseguíssemos tornar o jogo mais interativo.


= Objetivos

Para começar esta tarefa debatemos sobre várias alternativas para que os Ghosts se conseguissem movimentar independentemente, e com uma dificuldade acrescida para o Pacman conseguir fugir.

Começamos por dividir esta tarefa em várias partes para utilizar um método mais eficiente.

-Criar uma função na Tarefa2 para que assim os Ghosts se consigam mover e estender a função __play__ para a movimentação dos Ghosts.

-Fazer com que os Ghosts persigam o Pacman quando este esteja em modo Normal e os Ghosts estejam em modo Alive.

-Os Ghosts fugirem do Pacman quando este está em modo Mega e eles estejam no modo Dead.

-Última parte, juntar as duas funções.


= Decisões

Para começar o trabalho alteramos a Tarefa2:

-Criamos a função na qual os Ghosts também se movem, no entanto estes não podem ir para os Túneis.

-Como os Ghosts não podem atravessar os Túneis removemos essa opção.

- Aplicando por fim a função criada na função principal __play__.


Na segunda parte do nosso trabalho criámos uma função __'chaseMode'__ :

-O Ghost vai verificar se o Pacman está mais à esquerda ou à direita.

-Caso o Pacman eseja mais à direita e não esteja nenhuma __/Wall/__ à sua direita então ele irá mover-se para a direita. O mesmo acontece se o Pacman estiver mais à direita, o Ghost irá mover-se para a esquerda.

-Se houver uma parede na direção na qual o Ghost pretende ir então ele irá ver se o Pacman está em cima ou em baixo.

-Quando o Pacman estiver abaixo então o Ghost irá mover-se para baixo, por outro lado se o Pacman estiver mais em cima então mover-se-á para cima.

-Se o Ghost não conseguir concluir a jogada acima então terá que ir para a direção oposta.

-Quando tiver as mesmas coordenadas dos y's então irá na direção dos x's do Pacman, conseguindo assim caçar o Pacman.


Na próxima fase criamos a função __'scatterMode'__ para que o Ghost consiga fugir do Pacman quando este está em modo Mega:

-Tal como na função __chaseMode__ o Ghost irá verificar as coordenadas do Pacman.

-Caso o Pacman esteja em cima e o Ghost não possua nenhuma __/Wall/__ em baixo então irá mover-se para baixo, afastando-se assim do Pacman.

-Por outro lado se o Pacman estiver em baixo então o Ghost vai para a cima, se não houver nenhuma __/Wall/__ à em cima.

-Nos dois casos caso haja __/Wall/__ para a posição na qual o Ghost pretende ir então ele irá verificar se o Pacman está mais à esquerda ou direita e, assim, tomar a decisão correta.

-Se o Pacman estiver em cima o Ghost vai para baixo. Caso contrário irá para cima. Isto se não houver nehnuma __/Wall/__ a impedir o movimento.

-Caso haja alguma __/Wall/__ então irá tomar a orientação oposta.


Na última parte juntamos as duas funções:

-Para juntar as duas funções ordenamos as listas de Players, para que o Pacman fique sempre em primeiro da lista, comparando-o com os restantes Ghosts.

-Na função __'chaseMode'__ apenas estão os Ghosts de modo Alive, para que assim persigam o Pacman.

-Na função __'scatterMode'__ estão os Ghosts no modo Dead para que fujam quando estiverem nesse modo.


= Conclusão 

Nesta tarefa tivemos algumas dificuldades em escolher qual o melhor método para que os Ghosts persigam o Pacman, visto que existem muitas formas.

Um problema que houve foi quando o Ghost ao fugir fica preso na __/Wall/__, não conseguindo resolver esse problema.

-}

module Tarefa5 where 

import Types
import Tarefa1
import Tarefa2

-- | Função final que recebe uma State com as listas ordenadas de ambas as funções finais.
--
ghostPlay :: State -> [Play]
ghostPlay (State maze p lvl) = scatterMode1' (State maze ([pacman p] ++ deadGhost (ghosts p)) lvl) ++ chaseMode1' (State maze ([pacman p] ++ aliveGhost (ghosts p)) lvl)



-- | Função final na qual o Ghost respetivo ao ID recebido produz uma jogada para perseguir o Pacman.
--
chaseMode :: State -> Int -> Play
chaseMode st@(State maze ((Pacman(PacState (i,(x,y),v,o,p,l) t m md)):(Ghost (GhoState (i',(x',y'),v',o',p',l') md')):players) lvl) id
           | (x',y') == getmiddlecoordseven maze || (x',y') == getmiddlecoordsodd maze || (x'+1,y') == getmiddlecoordseven maze || (x'+1,y') == getmiddlecoordsodd maze = (Move i' U) 
           | (id == i') && (y < y') && (pieceMaze (x',y'-1) maze /= Wall) = (Move i' L)
           | (id == i') && (y < y') && (pieceMaze (x',y'-1) maze == Wall) && (x >= x') && (pieceMaze (x'+1,y') maze /= Wall) = (Move i' D)
           | (id == i') && (y < y') && (pieceMaze (x',y'-1) maze == Wall) && (x >= x') && (pieceMaze (x'+1,y') maze == Wall) = (Move i' U)
           | (id == i') && (y < y') && (pieceMaze (x',y'-1) maze == Wall) && (x < x') && (pieceMaze (x'-1,y') maze /= Wall) = (Move i' U)
           | (id == i') && (y < y') && (pieceMaze (x',y'-1) maze == Wall) && (x < x') && (pieceMaze (x'-1,y') maze == Wall) = (Move i' D)
           | (id == i') && (y > y') && (pieceMaze (x',y'+1) maze /= Wall) = (Move i' R)
           | (id == i') && (y > y') && (pieceMaze (x',y'+1) maze == Wall) && (x >= x') && (pieceMaze (x'+1,y') maze /= Wall) = (Move i' D)
           | (id == i') && (y > y') && (pieceMaze (x',y'+1) maze == Wall) && (x >= x') && (pieceMaze (x'+1,y') maze == Wall) = (Move i' U)
           | (id == i') && (y > y') && (pieceMaze (x',y'+1) maze == Wall) && (x < x') && (pieceMaze (x'-1,y') maze /= Wall) = (Move i' U)
           | (id == i') && (y > y') && (pieceMaze (x',y'-1) maze == Wall) && (x < x') && (pieceMaze (x'-1,y') maze == Wall) = (Move i' D)
           | (id == i') && (y == y') && (x > x') = (Move i' D)
           | (id == i') && (y == y') && (x < x') = (Move i' U) 
           | otherwise = (Move i' o')



-- | Função final na qual o Ghost respetivo ao ID recebido produz uma jogada para fugir do Pacman.
--
scatterMode :: State -> Int -> Play
scatterMode (State maze ((Pacman(PacState (i,(x,y),v,o,p,l) t m md)):(Ghost (GhoState (i',(x',y'),v',o',p',l') md')):players) lvl) id
           | (x',y') == getmiddlecoordseven maze || (x',y') == getmiddlecoordsodd maze || (x'+1,y') == getmiddlecoordseven maze || (x'+1,y') == getmiddlecoordsodd maze = (Move i' U)
           | (id == i') && (x' < x) && (pieceMaze (x'-1,y') maze /= Wall) = (Move i' U)
           | (id == i') && (x' < x) && (pieceMaze (x'-1,y') maze == Wall) && (y >= y') && (pieceMaze (x',y'-1) maze /= Wall) = (Move i' L)
           | (id == i') && (x' < x) && (pieceMaze (x'-1,y') maze == Wall) && (y >= y') && (pieceMaze (x',y'-1) maze == Wall) = (Move i' R)
           | (id == i') && (x' < x) && (pieceMaze (x'-1,y') maze == Wall) && (y < y') && (pieceMaze (x',y'-1) maze /= Wall) = (Move i' R)
           | (id == i') && (x' < x) && (pieceMaze (x'-1,y') maze == Wall) && (y < y') && (pieceMaze (x',y'-1) maze == Wall) = (Move i' L)
           | (id == i') && (x' > x) && (pieceMaze (x'+1,y') maze /= Wall) = (Move i' D)
           | (id == i') && (x' > x) && (pieceMaze (x'+1,y') maze == Wall) && (y <= y') && (pieceMaze (x',y'+1) maze /= Wall) = (Move i' R)
           | (id == i') && (x' > x) && (pieceMaze (x'+1,y') maze == Wall) && (y <= y') && (pieceMaze (x',y'+1) maze == Wall) = (Move i' L)
           | (id == i') && (x' > x) && (pieceMaze (x'+1,y') maze == Wall) && (y > y') && (pieceMaze (x',y'-1) maze /= Wall) = (Move i' L)
           | (id == i') && (x' > x) && (pieceMaze (x'+1,y') maze == Wall) && (y > y') && (pieceMaze (x',y'-1) maze == Wall) = (Move i' R)
           | (id == i') && (x' == x) && (y < y') && (pieceMaze (x',y'+1) maze /= Wall) = (Move i' R)
           | (id == i') && (x' == x) && (y < y') && (pieceMaze (x',y'+1) maze == Wall) && (pieceMaze (x'+1,y') maze /= Wall) = (Move i' D)
           | (id == i') && (x' == x) && (y < y') && (pieceMaze (x',y'+1) maze == Wall) && (pieceMaze (x'+1,y') maze == Wall) = (Move i' U)
           | (id == i') && (x' == x) && (y > y') && (pieceMaze (x',y'-1) maze /= Wall) = (Move i' L)
           | (id == i') && (x' == x) && (y > y') && (pieceMaze (x',y'-1) maze == Wall) && (pieceMaze (x'+1,y') maze /= Wall) = (Move i' D)
           | (id == i') && (x' == x) && (y > y') && (pieceMaze (x',y'-1) maze == Wall) && (pieceMaze (x'+1,y') maze == Wall) = (Move i' U)
           | otherwise = (Move i' o')




-- | Ordena a lista do State na função chaseMode.
--
chaseMode' :: State -> Int -> Play
chaseMode' (State maze p lvl) id = chaseMode (State maze (ordenaLista p) lvl) id


-- | Ordena a lista do State na função chaseMode.
--
scatterMode' :: State -> Int -> Play
scatterMode' (State maze p lvl) id = scatterMode (State maze (ordenaLista p) lvl) id 

 

-- | Aplica a função scatterMode' a todos os Ghosts na lista de Players do State.
--
scatterMode1 :: State -> [Play]
scatterMode1 (State maze [p] lvl) = []
scatterMode1 (State maze (pacman:(Ghost (GhoState (i',(x',y'),v',o',p',l') md')):players) lvl) = scatterMode' (State maze (pacman:(Ghost (GhoState (i',(x',y'),v',o',p',l') md')):players) lvl) i' : (scatterMode1 (State maze (pacman:players) lvl))

-- | Usa a função scatterMode1 com a lista ordenada do State.
--
scatterMode1' :: State -> [Play]
scatterMode1' (State maze p lvl) = scatterMode1 (State maze (ordenaLista p) lvl)



-- | Aplica a função chaseMode' a todos os Ghosts na lista de Players do State.
--
chaseMode1 :: State -> [Play]
chaseMode1 (State maze [p] lvl) = []
chaseMode1 (State maze (pacman:(Ghost (GhoState (i',(x',y'),v',o',p',l') md')):players) lvl) = chaseMode' (State maze (pacman:(Ghost (GhoState (i',(x',y'),v',o',p',l') md')):players) lvl) i' : (chaseMode1 (State maze (pacman:players) lvl))

-- | Usa a função chaseMode1 com a lista ordenada do State.
--
chaseMode1' :: State -> [Play]
chaseMode1' (State maze p lvl) = chaseMode1 (State maze (ordenaLista p) lvl)




