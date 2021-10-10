{-|
Module      : Tarefa6
Description : Implementação do Bot
Copyright   : Daniel Furtado <a97327@alunos.uminho.pt>;
              Gabriela Cunha <a97393@alunos.uminho.pt>

= Introdução

Na Tarefa 6, foi-nos atribuído fazer um __Bot__ que conseguisse jogar Pacman automaticamente.

Ao longo do jogo o Bot vai reagir de maneiras diferentes dependendo do seu modo e também de vários aspetos.


= Objetivos

No início desta tarefa debatemos sobre como iríamos interpretar o enunciado e escolher a melhor forma para que o Pacman conseguisse completar o jogo ainda vivo.

Ponderamos criar um bot mais primitivo em que apenas fugia. No entanto, desse modo, o jogo ficava demasiado simples, não tendo assim muita diversidade de jogadas e decisões.

Então tentamos fazer um Bot com um pouco mais de complexidade.

Para conseguir organizar a tarefa dividimo-la em partes:

-Quando o Bot está em modo Mega, onde vai perseguir os Ghosts que estavam apenas no modo Dead.

-Quando o Bot não possui nenhum Ghost por perto, podendo assim "caçar" as peças, nomeadamente "comida", e assim ganhar pontos e também ter uma maior diversidade de jogadas.

-Quando um Ghost se aproxima do Bot, ele deve ter como seu principal objetivo "fugir" do Ghost mais próximo e assim continuar no jogo.

-Última parte, juntar as duas funções.


= Decisões

Na primeira fase criamos a função __'catchGhost'__ que faz com que o Bot persiga os Ghosts.

-O nosso Bot apenas irá perseguir os Ghosts que estão no modo Dead, através da função __'allDead'__.

-Então o Bot irá comparar a sua posição com a do Ghost.

-Caso o Ghost esteja à sua direita e se não houver nenhuma __/Wall/__ á sua direita, ele irá movimentar-se para a direita, tentando assim obter a mesma coordenada que o Ghost.

-O mesmo acontece quando o Ghost está à sua esquerda, caso não tenha nenhuma parede à sua esquerda então ele irá mover-se para a esquerda.

-No entanto se tiver uma __/Wall/__ na coordenada para a qual o Bot se pretende mover então ele averiguará se o Ghost está acima ou abaixo.

-Dependendo da situação, estando o Ghost acima então ele irá mover-se para cima não tendo nenhuma __/Wall/__ em cima, isto é, ele mover-se-á para cima quando a coordenada em cima esteja livre.

-Por outro lado quando o Ghost está em baixo ele irá movimentar-se para baixo se na coordenada em baixo não esteja uma __/Wall/__.

-Em ambas as situações caso haja uma parede então ele terá que optar por tomar a direção contrária, ou seja, se estiver uma __/Wall/__ em cima irá para baixo, caso haja uma __/Wall/__ em baixo então o Bot irá para cima.

-Quando o Bot conseguir atingir a mesma coordenada dos y's então irá procurar obter a mesma coordenada dos x's do Ghost, movimentando-se para cima ou para baixo, dependendo da posição do Ghost.


Na fase seguindo optamos por criar uma função a __'escapeGhost'__ que recebe apenas Ghosts no modo Alive, onde o Bot, dependendo da sua distância ao Ghost mais próximo, irá averiguar se pode procurar pela "comida" mais próxima ou fugir do Ghost.

-O nosso Bot irá procurar pela comida mais próxima caso o Ghost esteja a uma distância radial de __6__, ou seja, se o Ghost estiver distante do Bot, ele pode procurar a comida mais próxima com a ajuda da função '__proxFood'__'.

-Caso a comida esteja á sua direita e não haja __/Wall/__ irá mover-se para a direita. O mesmo acontece se a comida estiver à esquerda, ele mover-se-á para a esquerda.

-Se tiver uma __/Wall/__ na direção na qual o Bot se move quando procura comida, se a comida estiver acima e não houver uma __/Wall/__ acima move-se para cima, senão move-se para baixo.

-O mesmo acontece quando a comida está para baixo, se não estiver uma __/Wall/__ ele move-se para baixo, por outro lado terá que se mover para cima.


Na terceira fase da Tarefa decidimos colocar quando o Pacman terá que "fugir" dos Ghosts, visto que este método de procura está bastante relacionado com a distância do Bot ao Ghost mais próximo.

-Do mesmo modo que o Bot faz para caçar o Ghost, neste caso ele faz o contrário.

-Caso o Bot esteja mais para a direita então irá mover-se para a direita até bater contra uma __/Wall/__.

-Quando colidir com a __/Wall/__ irá determinar se o Ghost está mais acima ou abaixo e irá decidir conforme a sua posição. Se o Ghost estiver em cima, mover-se-á para baixo, caso contrário mover-se-á para cima.

-Quando colide com uma __/Wall/__ em baixo ou em cima irá também determinar se o Ghost está mais à esquerda ou direita.

-Quando estiver na situação acima e o Ghost estiver mais à esquerda então move-se para a direita, senão move-se para a esquerda.

-Uma estratégia para tornar o jogo mais interativo e divertido, foi colocar o Bot a passar no túnel quando está a uma distância inferior a __5__ do Ghost mais próximo.


Na última parte do Trabalho decidimos juntar as funções __'escapeGhost''__ e __'catchGhost''__ utilizando-as alternadamente.

-Caso o Bot esteja em modo Mega utilizamos a função 'catchGhost''.

-Por outro lado, se estiver em modo Normal utilizamos a função 'escapeGhost'' 


= Conclusão 

Nesta tarefa tivemos algumas dificuldades em escolher qual o melhor método a utilizar, visto que existem inúmeros métodos, uns melhores que os outros.

Na nossa situação pensamos que o nosso método, apesar de não ser o mais eficiente, consegue atingir os objetivos e jogar fluidamente.

Alguns dos nossos problemas nesta Tarefa também passaram pela decisão que o Bot deve tomar quando está num canto, ou quando o Bot está no lado oposto ao Ghost.

-}


module Tarefa6 where 

import Types
import Tarefa1
import Tarefa2
import Tarefa3
import Tarefa5


-- | Esta função faz com que o bot consiga escapar dos Ghosts atribuindo jogadas dependendo do seu State.
--
escapeGhost :: State -> Maybe Play
escapeGhost st@(State maze pl@(pac@(Pacman(PacState (i,(x,y),v,o,p,l) t m md)):players) lvl)
                                              | (dist < 5.0) && ((x,y) == ((div (length maze) 2),(length (head maze) -2))) = Just (Move i R)
                                              | (dist < 5.0) && ((x,y) == ((div (length maze) 2) ,(length (head maze) -1))) = Just (Move i R)
                                              | (dist < 5.0) && ((x,y) == ((div (length maze) 2), 1)) = Just (Move i L)
                                              | (dist < 5.0) && ((x,y) == ((div (length maze) 2), 0)) = Just (Move i L)                               
                                              | (dist > 6.0) && (y > d) && (pieceMaze (x,y-1) maze /= Wall) && (o == L) = Nothing
                                              | (dist > 6.0) && (y > d) && (pieceMaze (x,y-1) maze /= Wall) && (o /= L) = Just (Move i L)
                                              | (dist > 6.0) && (y > d) && (pieceMaze (x,y-1) maze == Wall) && (x >= c) && (pieceMaze (x-1,y) maze /= Wall) = Just (Move i U) 
                                              | (dist > 6.0) && (y > d) && (pieceMaze (x,y-1) maze == Wall) && (x >= c) && (pieceMaze (x-1,y) maze == Wall) = Just (Move i D)
                                              | (dist > 6.0) && (y > d) && (pieceMaze (x,y-1) maze == Wall) && (x <  c) && (pieceMaze (x+1,y) maze /= Wall) = Just (Move i D)
                                              | (dist > 6.0) && (y > d) && (pieceMaze (x,y-1) maze == Wall) && (x <  c) && (pieceMaze (x+1,y) maze == Wall) = Just (Move i U)
                                              | (dist > 6.0) && (y < d) && (pieceMaze (x,y+1) maze /= Wall) && (o == R) = Nothing
                                              | (dist > 6.0) && (y < d) && (pieceMaze (x,y+1) maze /= Wall) && (o /= R) = Just (Move i R)
                                              | (dist > 6.0) && (y < d) && (pieceMaze (x,y+1) maze == Wall) && (x >= c) && (pieceMaze (x-1,y) maze /= Wall) = Just (Move i U)
                                              | (dist > 6.0) && (y < d) && (pieceMaze (x,y+1) maze == Wall) && (x >= c) && (pieceMaze (x-1,y) maze == Wall) = Just (Move i D)
                                              | (dist > 6.0) && (y < d) && (pieceMaze (x,y+1) maze == Wall) && (x <  c) && (pieceMaze (x+1,y) maze /= Wall) = Just (Move i D)
                                              | (dist > 6.0) && (y < d) && (pieceMaze (x,y+1) maze == Wall) && (x <  c) && (pieceMaze (x+1,y) maze == Wall) = Just (Move i U)
                                              | (dist > 6.0) && (y == d) && (x > c) && (pieceMaze (x-1,y) maze /= Wall) = Just (Move i U)
                                              | (dist > 6.0) && (y == d) && (x < c) && (pieceMaze (x+1,y) maze /= Wall) = Just (Move i D)
                                              | (dist > 6.0) && (y == d) && (x == c) = Nothing
                                              | (pieceMaze (x+1,y) maze == Wall) && (o == D) && (y >= b) && (pieceMaze (x,y+1) maze /= Wall) = Just (Move i R)
                                              | (pieceMaze (x+1,y) maze == Wall) && (o == D) && (y >= b) && (pieceMaze (x,y+1) maze == Wall) = Just (Move i L)
                                              | (pieceMaze (x+1,y) maze == Wall) && (o == D) && (y <  b) && (pieceMaze (x,y-1) maze /= Wall) = Just (Move i L)
                                              | (pieceMaze (x+1,y) maze == Wall) && (o == D) && (y <  b) && (pieceMaze (x,y-1) maze == Wall) = Just (Move i R)
                                              | (pieceMaze (x,y-1) maze == Wall) && (o == L) && (x >= a) && (pieceMaze (x+1,y) maze /= Wall) = Just (Move i D)
                                              | (pieceMaze (x,y-1) maze == Wall) && (o == L) && (x >= a) && (pieceMaze (x+1,y) maze == Wall) = Just (Move i U)
                                              | (pieceMaze (x,y-1) maze == Wall) && (o == L) && (x <  a) && (pieceMaze (x-1,y) maze /= Wall) = Just (Move i U)
                                              | (pieceMaze (x,y-1) maze == Wall) && (o == L) && (x <  a) && (pieceMaze (x-1,y) maze == Wall) = Just (Move i D)
                                              | (pieceMaze (x-1,y) maze == Wall) && (o == U) && (y >= b) && (pieceMaze (x,y+1) maze /= Wall) = Just (Move i R)
                                              | (pieceMaze (x-1,y) maze == Wall) && (o == U) && (y >= b) && (pieceMaze (x,y+1) maze == Wall) = Just (Move i L)                                              
                                              | (pieceMaze (x-1,y) maze == Wall) && (o == U) && (y <  b) && (pieceMaze (x,y-1) maze /= Wall) = Just (Move i L)
                                              | (pieceMaze (x-1,y) maze == Wall) && (o == U) && (y <  b) && (pieceMaze (x,y-1) maze == Wall) = Just (Move i R)
                                              | (pieceMaze (x,y+1) maze == Wall) && (o == R) && (x >= a) && (pieceMaze (x+1,y) maze /= Wall) = Just (Move i D)
                                              | (pieceMaze (x,y+1) maze == Wall) && (o == R) && (x >= a) && (pieceMaze (x+1,y) maze == Wall) = Just (Move i U)
                                              | (pieceMaze (x,y+1) maze == Wall) && (o == R) && (x <  a) && (pieceMaze (x-1,y) maze /= Wall) = Just (Move i L)
                                              | (pieceMaze (x,y+1) maze == Wall) && (o == R) && (x <  a) && (pieceMaze (x-1,y) maze /= Wall) = Just (Move i R)
                                              | (dist < 10.0) && (o == (opposite ori)) = Just (Move i (opposite o))
                                              | (y == b) && (x == a) = Nothing
                                              | otherwise = Nothing
                           where (a,b) = proxGhost' pl
                                 (c,d) = proxFood' pac maze
                                 dist  = distancePac' (x,y) (a,b)
                                 ori   = proxGhostO' pl


-- | A função determina de uma lista de Players qual o Ghost mais próximo do Pacman dando as suas coordenadas.
--
proxGhost :: [Player] -> Coords
proxGhost (pac:(Ghost (GhoState (i',(x',y'),v',o',p',l') md')):[]) = (x',y')
proxGhost ((Pacman(PacState (i,(x,y),v,o,p,l) t m md)):(Ghost (GhoState (i',(x',y'),v',o',p',l') md')):(Ghost (GhoState (i'',(x'',y''),v'',o'',p'',l'') md'')):players)
                        | ((y - y')^2 + (x-x')^2) <= ((y - y'')^2 + (x-x'')^2) = proxGhost   ((Pacman(PacState (i,(x,y),v,o,p,l) t m md)):(Ghost (GhoState (i',(x',y'),v',o',p',l') md')):players)
                        | otherwise = proxGhost ((Pacman(PacState (i,(x,y),v,o,p,l) t m md)):(Ghost (GhoState (i'',(x'',y''),v'',o'',p'',l'') md'')):players)

-- | Chama a função proxGhost com a lista de Players ordenada.
--
proxGhost' :: [Player] -> Coords
proxGhost' p = proxGhost (ordenaLista p) 



-- | A função calcula a distância entre duas coordenadas ao quadrado.
--
distancePac :: Coords -> Coords -> Int
distancePac (x,y) (a,b) = ((x-a)^2 + (y-b)^2) 

-- | Transforma o valor obtido na distancePac na distância entre as duas coordenadas.
--
distancePac' :: Coords -> Coords -> Float
distancePac' (x,y) (a,b) = sqrt (fromIntegral r)
   where r = distancePac (x,y) (a,b) 



-- | Obtém uma lista com todas as coordenadas das comidas no Maze.
--
coordsFood :: Maze ->  Coords -> [Coords] 
coordsFood [] (x,y) = []
coordsFood ([]:c) (x,y) = coordsFood c (x+1,0)  
coordsFood ((p:ps):c) (x,y) | (p == Food Big) || (p == Food Little) = (x,y) : coordsFood (ps:c) (x,y+1)
                            | otherwise = coordsFood ((ps):c) (x,y+1)

-- | Utiliza o contador na função coordsFood. 
--
coordsFood' :: Maze -> [Coords]
coordsFood' m = coordsFood m (0,0)



-- | Determina qual a coordenada mais próxima do Pacman.
--
proxFood :: Player -> [Coords] -> Coords
proxFood player [x] = x
proxFood (Pacman(PacState (i,(x,y),v,o,p,l) t m md)) ((x',y'):(x'',y''):coords) | (x-x')^2 + (y-y')^2 <= ((x-x'')^2 + (y-y'')^2) = proxFood (Pacman(PacState (i,(x,y),v,o,p,l) t m md)) ((x',y'):coords)
                                                                                | otherwise = proxFood (Pacman(PacState (i,(x,y),v,o,p,l) t m md)) ((x'',y''):coords) 

-- | Obtém a coordenada de comida, mais próxima do Pacman.
--  
proxFood' :: Player -> Maze -> Coords
proxFood' p m = proxFood p (coordsFood' m) 



-- | A função retorna a orientação do Ghost mais próximo do Pacman.
-- 
proxGhostO :: [Player] -> Orientation
proxGhostO (pac:(Ghost (GhoState (i',(x',y'),v',o',p',l') md')):[]) = o'
proxGhostO ((Pacman(PacState (i,(x,y),v,o,p,l) t m md)):(Ghost (GhoState (i',(x',y'),v',o',p',l') md')):(Ghost (GhoState (i'',(x'',y''),v'',o'',p'',l'') md'')):players)
                        | ((y - y')^2 + (x-x')^2) <= ((y - y'')^2 + (x-x'')^2) = proxGhostO   ((Pacman(PacState (i,(x,y),v,o,p,l) t m md)):(Ghost (GhoState (i',(x',y'),v',o',p',l') md')):players)
                        | otherwise = proxGhostO ((Pacman(PacState (i,(x,y),v,o,p,l) t m md)):(Ghost (GhoState (i'',(x'',y''),v'',o'',p'',l'') md'')):players)

-- | Tem o mesmo resultado que a proxGhostO mas com a lista de Player ordenada.
-- 
proxGhostO' :: [Player] -> Orientation
proxGhostO' p = proxGhostO (ordenaLista p)




-- | Esta função faz com que o bot consiga perseguir os Ghosts atribuindo jogadas dependendo do seu State.
--
catchGhost :: State -> Coords -> Maybe Play
catchGhost st@(State maze ((Pacman(PacState (i,(x,y),v,o,p,l) t m md)):all@((Ghost (GhoState (i',(x1,y1),v',o',p',l') md')):players)) lvl) (x',y')
                                           |  (allDead all) && (y > y') && (o == L) && (pieceMaze (x,y-1) maze /= Wall) = Nothing
                                           |  (allDead all) && (y > y') && (o /= L) && (pieceMaze (x,y-1) maze /= Wall) = Just (Move i L)
                                           |  (allDead all) && (y > y') && (pieceMaze (x,y-1) maze == Wall) && (x>=x') && (pieceMaze (x-1,y) maze /= Wall) = Just (Move i U)
                                           |  (allDead all) && (y > y') && (pieceMaze (x,y-1) maze == Wall) && (x>=x') && (pieceMaze (x-1,y) maze == Wall) = Just (Move i D)
                                           |  (allDead all) && (y > y') && (pieceMaze (x,y-1) maze == Wall) && (x< x') && (pieceMaze (x+1,y) maze /= Wall) = Just (Move i D)
                                           |  (allDead all) && (y > y') && (pieceMaze (x,y-1) maze == Wall) && (x< x') && (pieceMaze (x+1,y) maze == Wall) = Just (Move i U)
                                           |  (allDead all) && (y < y') && (o == R) && (pieceMaze (x,y+1) maze /= Wall) = Nothing
                                           |  (allDead all) && (y < y') && (o /= R) && (pieceMaze (x,y+1) maze /= Wall) = Just (Move i R)
                                           |  (allDead all) && (y < y') && (pieceMaze (x,y+1) maze == Wall) && (x>=x') && (pieceMaze (x-1,y) maze /= Wall) = Just (Move i U)
                                           |  (allDead all) && (y < y') && (pieceMaze (x,y+1) maze == Wall) && (x>=x') && (pieceMaze (x-1,y) maze == Wall) = Just (Move i D)
                                           |  (allDead all) && (y < y') && (pieceMaze (x,y+1) maze == Wall) && (x< x') && (pieceMaze (x+1,y) maze /= Wall) = Just (Move i D)
                                           |  (allDead all) && (y < y') && (pieceMaze (x,y+1) maze == Wall) && (x< x') && (pieceMaze (x+1,y) maze == Wall) = Just (Move i U)
                                           |  (allDead all) && (y == y') && (x > x') = Just (Move i U)
                                           |  (allDead all) && (y == y') && (x < x') = Just (Move i D)
                                           | otherwise = escapeGhost st


-- | Verifica se todos os Ghosts da lista estão em modo Dead.
--
allDead  :: [Player] -> Bool
allDead [] = True
allDead ((Ghost (GhoState (i',(x1,y1),v',o',p',l') md')):pls) | md' == Dead = allDead pls
                                                              | otherwise = False 






-- | Função final na qual o Pacman foge dos Ghosts recebendo uma lista ordenada de Players no State.
--
escapeGhost' :: State -> Maybe Play
escapeGhost' (State maze p lvl) = escapeGhost (State maze (ordenaLista p) lvl)



-- | Função final na qual o Pacman persegue os Ghosts recebendo uma lista ordenada de Players no State.
--
catchGhost' :: State -> Maybe Play
catchGhost' (State maze p lvl)  = catchGhost (State maze (ordenaLista p) lvl) (proxGhost' p) 


-- | Aplica uma jogada ao bot dependendo do seu modo.
--
bot' :: Int -> State -> Maybe Play
bot' id st@(State maze ((Pacman(PacState (i,(x,y),v,o,p,l) t m md)):players) lvl) | (id == i) && (md == Mega) = catchGhost' st
                                                                                  | (id == i) && (md == Normal) = escapeGhost' st



-- | Função final do bot que recebe uma lista ordenada de Players no estado.
--
bot :: Int -> State -> Maybe Play
bot id (State maze p lvl) = bot' id (State maze (ordenaLista p) lvl)
