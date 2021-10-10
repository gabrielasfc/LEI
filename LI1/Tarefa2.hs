{-|
Module      : Tarefa2
Description : Efetuar jogadas
Copyright   : Daniel Furtado <a97327@alunos.uminho.pt>;
              Gabriela Cunha <a97393@alunos.uminho.pt>

= Introdução

Nesta tarefa foi-nos proposta a implementação da função __'play'__ que faz as jogadas e move os jogadores.


= Objetivos e estratégias

Aplicamos uma função auxiliar para descobrir a peça para onde o jogador se quer mover.

Assim pudemos especificar cada caso particular e casos mais gerais e lógicos como o facto de um jogador não se poder mover para uma parede.

Em relação aos casos particulares, especificamos os seguintes casos:

-Comportamento do pacman ao comer as comidas (Ganha 5 pontos se comer comida pequena e se comer comida grande 10 pontos e altera o modo para Mega);

-Comportamento dos fantasmas quando o Pacman se encontra no modo Mega (devem reduzir a sua velocidade para metade da velocidade inicial e alterar o seu modo para Dead);

-Comportamento do jogador quando se encontra numa peça do túnel (deve-se mover para o lado oposto do corredor);

-Ocorrências se o pacman colidir com um fantasma se estiver em modo Mega (o fantasma morre e renasce para o centro da casa dos fantasmas e o Pacman ganha 10 pontos ao comer o fantasma);

-Substituição das peças por onde o pacman passa (as comidas devem desaparecer após o Pacman passar por elas).

Na 1ª fase do trabalho limitamos a função final apenas para jogadas do pacman.

Com a 2ª fase do trabalho fizemos várias alterações a esta tarefa, referidas no relatório da T4 e da T5.

Com a experimentação do jogo no Main percebemos também que o pacman conseguia entrar dentro da casa dos fantasmas, o que não era suposto, e acrescentamos essa restrição à nossa função.


= Conclusão

Ao concluir a função __'play'__, apesar da tarefa compilar no terminal, os testes na codeboard fornecida não coincidiam com o esperado e tínhamos ainda cerca de 10 erros em 13 possíveis da primeira vez que a testamos.

Estes inúmeros erros deviam-se ao facto de termos trocado as coordenadas, erro que corrijimos logo de seguida e reduzimos para apenas 3 erros.

Estes 3 erros foram mais difíceis de identificar mas atingimos o nosso objetivo e conseguimos concluir a tarefa com sucesso, passando a todos os testes.

-}

module Tarefa2 where 

import Types
import Tarefa1

-- | Retorna a peça respetiva às coordenadas dadas no Maze.
--
-- Esta função utiliza duas funções auxiliares: __'findpiece'__ and __'findcorr'__.
--
pieceMaze :: Coords -> Maze -> Piece
pieceMaze (x,y) m = findpiece (x,y) c
      where c = findcorr (x,y) m  


-- | Encontra a peça respetiva às coordenadas dadas no corredor 
-- 
findpiece :: Coords -> Corridor -> Piece
findpiece (x,0) c = head c
findpiece (x,y) c = findpiece (x,y-1) (tail c)


-- | Encontra o corredor no Maze com as coordenadas dadas
--  
findcorr :: Coords -> Maze -> Corridor
findcorr (0,y) m = head m
findcorr (x,y) m = findcorr (x-1,y) (tail m)


-- | Recebe um /Player/, uma /Orientação/ e um /Maze/ e devolve o Pacman com a nova /Orientação/ ou com novas /Coordenadas/.
--
-- -Se a /Orientação/ dada é a mesma que a do /Player/ então avança para a respetiva posição.
--
-- -Se a /Orientação/ dada é diferente da sua então altera a sua /Orientação/. 
--
-- -__ATENÇÂO__ : Se existe uma _Wall_ na posição que o /Player/ pretende ir, não se move.
--
movePacman :: Player -> Orientation -> Maze -> Player
movePacman (Pacman(PacState (i,(x,y),v,o,p,l) t m md)) orientation  a
                             | odd (length a)  && odd (length c)   && (x,y) == (x1-1,y1+1)  && o==D = switchMouth $ (Pacman(PacState (i,(x,y),v,R,p,l) t m md))
                             | odd (length a)  && odd (length c)   && (x,y) == (x1-1,y1)    && o==D = switchMouth $ (Pacman(PacState (i,(x,y),v,L,p,l) t m md))
                             | odd (length a)  && odd (length c)   && (x,y) == (x1-1,y1-1)  && o==D = switchMouth $ (Pacman(PacState (i,(x,y),v,L,p,l) t m md))
                             | odd (length a)  && odd (length c)   && (x,y) == (x1-1,y1+1)  && orientation == D = switchMouth $ (Pacman(PacState (i ,(x,y),v,R,p,l) t m md))
                             | odd (length a)  && odd (length c)   && (x,y) == (x1-1,y1-1)  && orientation == D = switchMouth $ (Pacman(PacState (i,(x,y),v,L,p,l) t m md))
                             | odd (length a)  && even (length c)  && (x,y) == (x1-1,y1)    && o==D = switchMouth $ (Pacman(PacState (i,(x,y),v,R,p,l) t m md))
                             | odd (length a)  && even (length c)  && (x,y) == (x1-1,y1-1)  && o==D = switchMouth $ (Pacman(PacState (i,(x,y),v,L,p,l) t m md))
                             | odd (length a)  && even (length c)  && (x,y) == (x1-1,y1-1)  && orientation == D = switchMouth $ (Pacman(PacState (i,(x,y),v,R,p,l) t m md))
                             | odd (length a)  && even (length c)  && (x,y) == (x1-1,y1)    && orientation == D = switchMouth $ (Pacman(PacState (i,(x,y),v,L,p,l) t m md))
                             | even (length a) && odd (length c)   && (x,y) == (x2-1,y2-1)  && o==D = switchMouth $ (Pacman(PacState (i,(x,y),v,L,p,l) t m md))
                             | even (length a) && odd (length c)   && (x,y) == (x2-1,y2)    && o==D = switchMouth $ (Pacman(PacState (i,(x,y),v,L,p,l) t m md))
                             | even (length a) && odd (length c)   && (x,y) == (x2-1,y2+1)  && o==D = switchMouth $ (Pacman(PacState (i,(x,y),v,R,p,l) t m md))
                             | even (length a) && odd (length c)   && (x,y) == (x2-1,y2-1)  && orientation==D = switchMouth $ (Pacman(PacState (i,(x,y),v,R,p,l) t m md))
                             | even (length a) && odd (length c)   && (x,y) == (x2-1,y2+1)  && orientation==D = switchMouth $ (Pacman(PacState (i,(x,y),v,L,p,l) t m md))
                             | even (length a) && even (length c)  && (x,y) == (x2-1,y2)    && o==D = switchMouth $ (Pacman(PacState (i,(x,y),v,R,p,l) t m md))
                             | even (length a) && even (length c)  && (x,y) == (x2-1,y2-1)  && o==D = switchMouth $ (Pacman(PacState (i,(x,y),v,L,p,l) t m md))
                             | even (length a) && even (length c)  && (x,y) == (x2-1,y2)    && orientation==D = switchMouth $ (Pacman(PacState (i,(x,y),v,R,p,l) t m md))
                             | even (length a) && even (length c)  && (x,y) == (x2-1,y2-1)  && orientation==D = switchMouth $ (Pacman(PacState (i,(x,y),v,L,p,l) t m md))
                             | (y==0) && (o==L) = switchMouth $ posTunnel (Pacman(PacState (i,(x,y),v,o,p,l) t m md)) a orientation
                             | (y==(length (head a))-1) && (o==R) = switchMouth $ posTunnel (Pacman(PacState (i,(x,y),v,o,p,l) t m md)) a orientation
                             | (o==L) && (orientation == L) && (pieceMaze (x,y-1) a /= Wall) = switchMouth $ (Pacman(PacState (i,(x,y-1),v,orientation,p,l) t m md))
                             | (o==L) && (orientation == L) && (pieceMaze (x,y-1) a == Wall) = switchMouth $ (Pacman(PacState (i,(x,y),v,orientation,p,l) t m md))
                             | (o==R) && (orientation == R) && (pieceMaze (x,y+1) a /= Wall) = switchMouth $ (Pacman(PacState (i,(x,y+1),v,orientation,p,l) t m md))
                             | (o==R) && (orientation == R) && (pieceMaze (x,y+1) a == Wall) = switchMouth $ (Pacman(PacState (i,(x,y),v,orientation,p,l) t m md))
                             | (o==U) && (orientation == U) && (pieceMaze (x-1,y) a /= Wall) = switchMouth $ (Pacman(PacState (i,(x-1,y),v,orientation,p,l) t m md))
                             | (o==U) && (orientation == U) && (pieceMaze (x-1,y) a == Wall) = switchMouth $ (Pacman(PacState (i,(x,y),v,orientation,p,l) t m md))
                             | (o==D) && (orientation == D) && (pieceMaze (x+1,y) a /= Wall) = switchMouth $ (Pacman(PacState (i,(x+1,y),v,orientation,p,l) t m md))
                             | (o==D) && (orientation == D) && (pieceMaze (x+1,y) a == Wall) = switchMouth $ (Pacman(PacState (i,(x,y),v,orientation,p,l) t m md))
                             | otherwise = switchMouth $ (Pacman(PacState (i,(x,y),v,orientation,p,l) t m md))
                                  where (x1,y1) = getmiddlecoordsodd a
                                        (x2,y2) = getmiddlecoordseven a
                                        (c:cs) = a


-- | A função recebe um /Player/, uma /Orientação/, um /Maze/ e devolve o /Ghost/ com uma nova /Orientação/ ou novas  /Coordenadas/. 
--
moveGhost :: Player -> Orientation -> Maze -> Player
moveGhost (Ghost(GhoState (i,(x,y),v,o,p,l) md )) orientation a
                             | (o==L) && (orientation == L) && (pieceMaze (x,y-1) a /= Wall) = (Ghost(GhoState (i,(x,y-1),v,o,p,l) md))
                             | (o==L) && (orientation == L) && (pieceMaze (x,y-1) a == Wall) = (Ghost(GhoState (i,(x,y),v,o,p,l) md))
                             | (o==R) && (orientation == R) && (pieceMaze (x,y+1) a /= Wall) = (Ghost(GhoState (i,(x,y+1),v,o,p,l) md))
                             | (o==R) && (orientation == R) && (pieceMaze (x,y+1) a == Wall) = (Ghost(GhoState (i,(x,y),v,o,p,l) md))
                             | (o==U) && (orientation == U) && (pieceMaze (x-1,y) a /= Wall) = (Ghost(GhoState (i,(x-1,y),v,o,p,l) md))
                             | (o==U) && (orientation == U) && (pieceMaze (x-1,y) a == Wall) = (Ghost(GhoState (i,(x,y),v,o,p,l) md))
                             | (o==D) && (orientation == D) && (pieceMaze (x+1,y) a /= Wall) = (Ghost(GhoState (i,(x+1,y),v,o,p,l) md))
                             | (o==D) && (orientation == D) && (pieceMaze (x+1,y) a == Wall) = (Ghost(GhoState (i,(x,y),v,o,p,l) md))
                             | otherwise = (Ghost(GhoState (i,(x,y),v,orientation,p,l) md))


-- ! Aplica as alterações aos /Ghosts/ quando o Pacman está em modo Mega.
--
-- -Todos os Ghosts devem alterar a sua velocidade para metade e os modo para Dead se estiverem em modo Alive. 
--
-- -Na transição quando o MegaTime acaba e os Ghosts estão em modo Dead, a sua velocidade aumenta para o dobro e o seu modo atualiza para Alive. 
--
megaPacg :: Player -> [Player] -> [Player]
megaPacg (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md)) [] = []
megaPacg (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md)) ((Ghost(GhoState (id,(x2,y2),vel,ori,pt,lv) mode)):xs)
                    | md==Normal && mode==Dead = (Ghost(GhoState (id,(x2,y2),1,ori,pt,lv) Alive)): megaPacg (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md)) xs
                    | md==Mega && t==10 = (Ghost(GhoState (id,(x2,y2),0.5,ori,pt,lv) Dead)): megaPacg (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md)) xs
                    | otherwise = ((Ghost(GhoState (id,(x2,y2),vel,ori,pt,lv) mode)):xs)


-- | Atualiza o tempo Mega se o Pacman está em modo Mega.
-- 
megaPacp :: Player -> Player
megaPacp (Pacman(PacState (i,(x,y),v,o,p,l) t m md)) | (md==Mega) && (t>0) = (Pacman(PacState (i,(x,y),v,o,p,l) (t-0.25) m md))
                                                     | (md==Mega) && (t<=0) = (Pacman(PacState (i,(x,y),v,o,p,l) t m Normal))
                                                     | otherwise = (Pacman(PacState (i,(x,y),v,o,p,l) t m md))



-- | Função que muda o estado da boca do Pacman.
--
switchMouth :: Player -> Player
switchMouth (Pacman(PacState (i,(x,y),v,o,p,l) t m md)) | m==Open = (Pacman(PacState (i,(x,y),v,o,p,l) t Closed md))
                                                        | m==Closed = (Pacman(PacState (i,(x,y),v,o,p,l) t Open md))
switchMouth (Ghost(GhoState (i,(x,y),v,o,p,l) md)) = (Ghost(GhoState (i,(x,y),v,o,p,l) md))


-- | Aplica as alterações quando o Pacman colide com um Ghost (mesmas /Coordenadas/).
--
-- -Quando o Pacman them mais de __1 vida__ e o Ghost está em modo __Alive__ o Pacman perde __1__ vida. 
--
-- -Quando o Pacman tem __0 vidas__ e o modo do Ghost é __Alive__ o Pacman muda o seu modo para __Dying__-
--
posGhost :: Player -> [Player] -> Player
posGhost (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md)) []  = (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md))
posGhost (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md)) ((Ghost(GhoState (id,(x2,y2),vel,ori,pt,lv) mode)):xs)
                                          | x1==x2 && y1==y2 && l==0 && mode==Alive = (Pacman(PacState (i,(x1,y1),v,o,p,l) t m Dying))
                                          | x1==x2 && y1==y2 && l>0  && mode==Alive = (Pacman(PacState (i,(x1,y1),v,o,p,(l-1)) t m md)) 
                                          | x1==x2 && y1==y2 && l>=0 && mode==Dead  = (Pacman(PacState (i,(x1,y1),v,o,p+10,l) t m Mega))
                                          | otherwise                               = posGhost (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md)) xs    


-- | Altera a pontuação do Pacman quando está nas mesmas /Coordenadas/ que alguma /Food/.
--
-- -Quando o Pacman está nas mesmas /Coordenadas/ que uma __Food Little__ Pacman ganha __1__ ponto.
-- 
-- -Quando o Pacman está nas mesmas /Coordenadas/ que uma __Food Big__ ganha __5__ pontos. 
--
-- Esta função usa a função: __'pieceMaze'__
--
posFood :: Player -> Maze -> Player
posFood (Pacman(PacState (i,(x,y),v,o,p,l) t m md)) a 
                    | b == Food Little = Pacman(PacState (i,(x,y),v,o,(p+1),l) t m md)
                    | b == Food Big    = Pacman(PacState (i,(x,y),v,o,(p+5),l) 10.25 m Mega)   
                    | otherwise = Pacman(PacState (i,(x,y),v,o,p,l) t m md)
         where b = pieceMaze (x,y) a


-- | Move o Pacman para o outro lado do tunel quando entra no lado contrário no tunel.
--
posTunnel :: Player -> Maze -> Orientation -> Player
posTunnel (Pacman(PacState (i,(x,y),v,o,p,l) t m md)) (h:hs) orientation
                            | (y==0) && (o==L) && (orientation==L) = (Pacman(PacState (i,(x,((length h)-1)),v,o,p,l) t m md))
                            | (y==((length h)-1)) && (o==R) && (orientation==R) = (Pacman(PacState (i,(x,0),v,o,p,l) t m md))
                            | otherwise = (Pacman(PacState (i,(x,y),v,orientation,p,l) t m md))


-- | Substitui a comida, quando o Pacman tem as mesmas /Coordenadas/ que a comida, por um espaço.
--
-- Esta função usa 2 auxiliares funções: __'pieceMaze'__ e __'replaceElemInMaze'__.
--
replacePiece :: Player -> Maze -> Maze
replacePiece (Pacman(PacState (i,(x,y),v,o,p,l) t m md)) maze 
                    | b == Food Big    =  replaceElemInMaze (x,y) Empty maze
                    | b == Food Little = replaceElemInMaze (x,y) Empty maze 
                    | otherwise =  maze 
         where b = pieceMaze (x,y) maze


-- | Descreve para onde os Ghosts vão após serem comidos pelo Pacman.
--
-- -Se o Ghost estiver no modo Dead então ele vai para a casa dos Fantasmas.
--
-- -A casa varia caso a altura seja par ou ímpar.
--
-- Esta função usa 2 auxiliares funções: __'getmiddlecoordsodd'__ e __'getmiddlecoordseven'__.
--
ghostDie :: Player -> [Player] -> Maze -> [Player]
ghostDie (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md)) [] maze = []
ghostDie (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md)) ((Ghost(GhoState (id,(x2,y2),vel,ori,pt,lv) mode)):hs) maze
                     | x1==x2 && y1==y2 && mode==Dead && odd1==True  = (Ghost(GhoState (id,middle1,vel,ori,pt,lv) Alive)): ghostDie (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md)) hs maze
                     | x1==x2 && y1==y2 && mode==Dead && odd1==False = (Ghost(GhoState (id,middle2,vel,ori,pt,lv) Alive)): ghostDie (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md)) hs maze
                     | otherwise = (Ghost(GhoState (id,(x2,y2),vel,ori,pt,lv) mode)): ghostDie (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md)) hs maze
                where middle1 = getmiddlecoordsodd maze
                      middle2 = getmiddlecoordseven maze
                      odd1 = odd (length maze)


-- | Encontra onde é o meio do Maze quando a altura do Maze é __ímpar__.
--
getmiddlecoordsodd :: Maze -> Coords
getmiddlecoordsodd (h:t) = (div(length (h:t)) 2,(div (length h) 2))   


-- | Encontra onde se situa o meio do Maze quando a altura é __par__. 
getmiddlecoordseven :: Maze -> Coords
getmiddlecoordseven (h:t) = ((div(length (h:t)) 2)-1,(div (length h) 2))


-- | Reúne todos os Ghosts da lista de Players.
--
ghosts :: [Player] -> [Player]
ghosts [] = []
ghosts ((Pacman(PacState (i,(x,y),v,o,p,l) t m md)):hs) = ghosts hs
ghosts ((Ghost(GhoState (i,(x,y),v,o,p,l) md)):hs) = ((Ghost(GhoState (i,(x,y),v,o,p,l) md)): ghosts hs)


-- | Encontra o Pacman na lista de jogadores.
--
pacman :: [Player] -> Player
pacman [] = error "PACMAN NOT FOUND"
pacman ((Pacman(PacState (i,(x,y),v,o,p,l) t m md)):hs) = (Pacman(PacState (i,(x,y),v,o,p,l) t m md))
pacman ((Ghost(GhoState (i,(x,y),v,o,p,l) md)):hs)      = pacman hs


-- | Função que recebe um id do Ghost e a lista de Players e apenas move o Ghost com o respetivo id. 
--
moveGhosts :: [Player] -> Orientation -> Maze -> Int -> [Player]
moveGhosts [] _ _ _ = []
moveGhosts (p:pls) o mz id | id == (getPlayerID p) =   (moveGhost p o mz):moveGhosts pls o mz id
                           | otherwise = (p:moveGhosts pls o mz id) 


-- | Função principal que aplica uma __Play__ dado um __Move__ e um __State__.
--
play :: Play -> State -> State
play (Move id o) (State maze players lvl) 
     | id == (getPlayerID (pacman players)) =
            let a = (pacman (players))
                b = (movePacman a o maze)
                c = (replacePiece b maze)
                d = (ghosts players)
                e = (posFood b maze)
                e2 = (megaPacp e) 
                d2 = (megaPacg e2 d)
                f = (posGhost e2 d2)
                g = (megaPacg e2 d2)
                h = (ghostDie e2 g maze)
            in State c (f:h) lvl
     | otherwise = 
            let t = (moveGhosts players o maze id)
            in State maze t lvl

