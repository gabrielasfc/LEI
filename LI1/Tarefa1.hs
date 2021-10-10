{-|
Module      : Tarefa1
Description : Gerar labirintos
Copyright   : Daniel Furtado <a97327@alunos.uminho.pt>;
              Gabriela Cunha <a97393@alunos.uminho.pt>

= Introdução

Nesta primeira tarefa, foi-nos proposto __gerar labirintos__ com o túnel, a casa dos fantasmas e a parede lateral incluídos através de uma __/seed/__ gerada aleatoriamente.


= Objetivos e estratégias 

Para a realização da tarefa dividimo-la em 4 partes: 

-As funções auxiliares do Generator para a tarefa, maioritariamente de conversões;

-As funções para gerar o túnel e a parede lateral;

-As funções para gerar a casa dos fantasmas;

-Juntar todas as partes na função final __'generateMaze'__.


= Conclusão 

Para testarmos as funções acabamos por fazer uma função auxiliar que nos dá a preview, sendo mais fácil e rápido identificar se elas conseguiam obter os resultados esperados e saber onde corrigir, caso necessário.

Ao implementar estas funções cumprimos o objetivo e conseguimos gerar labirintos válidos, isto é, com a faixa central a formar um túnel, com todos os corredores com o mesmo comprimento, com a casa dos fantasmas localizada no centro e rodeado de peças Wall (exceto no túnel).

-}


module Tarefa1 where

import System.Random
import Types


-- | Converte um Integer para Piece.
--
-- -A função apenas deve receber números entre __0__ e __99__.
--
convertsPiece :: Int -> Piece
convertsPiece n | n == 3 = Food Big
                | n >= 0 && n < 70 = Food Little
                | n >= 70 && n <= 99 = Wall



-- | Dada uma seed dá uma lista de n inteiros gerados aleatoriamente.
-- 
generateRandoms :: Int -> Int -> [Int]
generateRandoms n seed = let gen = mkStdGen seed -- cria um gerador aleatório
                             in take n $ randomRs (0,99) gen -- pega apenas nos primeiros n elementos de uma série infinita de números aleatórios entre 0-9



-- | Converte uma lista de inteiros numa lista de peças.
--
numbersToPieces :: [Int] -> Corridor
numbersToPieces [] = []
numbersToPieces (h:t) = convertsPiece h : numbersToPieces t



-- | Dado um inteiro e uma lista de peças devolve um Maze
--
listToMaze :: Int -> Corridor -> Maze
listToMaze x [] = []
listToMaze w l = take w l : listToMaze w (drop w l)



-- | Função que nos dá a preview.
--
display :: Maze -> IO ()
display m = putStrLn $ printMaze m



-- | Devolve as paredes de cima e de baixo.
--
updownWall :: Int -> Corridor
updownWall x =  replicate x Wall



-- | Coloca as paredes de cima e de baixo no labirinto.
--
updownmaze :: Maze -> Maze
updownmaze (h:t) = a ++ (h:t) ++ a
       where a = [updownWall (length h)]



-- | Devolve as paredes da esquerda e da direita.
--
sideWall :: Maze -> Maze
sideWall [] = []
sideWall (h:t) = (latcorridor h: sideWall t) 
      where latcorridor c = [Wall] ++ c ++ [Wall]



-- | Encontra e substitui o corredor central no labirinto.
-- 
replace :: Int -> Corridor -> Maze -> Maze
replace 0 c (m:ms) = c : ms
replace i c (m:ms) = m : replace (i-1) c ms



-- | Converte um corredor em um corredor com peças Empty nos 2 extremidades.
--
toTunnel :: Corridor -> Corridor
toTunnel c = [Empty] ++ (tail (init c)) ++ [Empty]



-- | Distingue se o labirinto tem altura par ou ímpar.
--
-- Usa as auxiliares __'oddTunnel'__ e __'evenTunnel'__.
--
addTunnel :: Int -> Maze -> Maze
addTunnel h m | mod h 2 == 1 = oddTunnel h mid m
              | mod h 2 == 0 = evenTunnel h mid m
       where mid = div h 2



-- | Se a altura for par muda os __2__  corredores centrais para túnel.
-- 
-- Encontra os 2 corredores centrais e depois coloca as peças Empty nas extremidades de cada um.
--
evenTunnel :: Int -> Int -> Maze -> Maze
evenTunnel h mid m =
     let midCor = m !! mid 
         midCor1 = m !! mid
         withTunnel = toTunnel midCor
         withTunnel1 = toTunnel midCor1
         x = replace (mid -1) withTunnel1 m 
     in replace mid withTunnel x 



-- | Se a altura for ímpar muda o corredor central para túnel.
--
-- Encontra o corredor central e depois coloca as peças Empty em cada extremidade.
--
oddTunnel :: Int -> Int -> Maze -> Maze
oddTunnel h mid m =
      let midCor = m !! mid 
          withTunnel = toTunnel midCor
      in replace mid withTunnel m



-- | Constrói a casa dos fantasmas ímpar ou par de acordo com a largura do labirinto.
-- 
-- Usa a auxiliar __'find5middle'__ e as que dão a estrutura da casa (__'evenHouse'__ and __'oddHouse'__).
--
addHouse :: Int -> Maze -> Maze
addHouse w m | mod w 2 == 1 = find5middle 0 (length m) m oddHouse
             | mod w 2 == 0 = find5middle 0 (length m) m evenHouse



-- | Seleciona os 5 corredores centrais para colocar a casa.
-- 
-- Encontra o corredor onde a casa deve começar e substitui corredor por corredor o labirinto original pelo labirinto com a casa
-- 
-- Usa a auxiliar __'placeHouse'__.
--
find5middle :: Int -- ^ acumulador
            -> Int -- ^ altura do maze
            -> Maze -- ^ maze
            -> Maze -- ^ maze com a casa (5 corredores)
            -> Maze 
find5middle _ _ [] _ = []
find5middle _ _ (h:t) [] = (h:t)
find5middle c h (h1:t1) (h2:t2) | (c>=(div h 2) - a) && (c<=(div h 2) + a) = placeHouse 0 (length h1) h1 h2:find5middle (c+1) h t1 t2
                                | c<(div h 2) - a = h1:find5middle (c+1) h t1 (h2:t2)
                                | otherwise = find5middle (c+1) h (h1:t1) []
                                         where a | (odd h == True) = 2
                                                 | otherwise = 3



-- | Coloca o corredor da casa num corredor do labirinto original.
-- 
-- Encontra a posição no corredor onde a casa deve começar e substitui peça por peça o corredor original pelo corredor com a casa.
--
placeHouse :: Int -- ^ acumulador
           -> Int -- ^ largura do maze 
           -> Corridor -- ^ corredor do maze
           -> Corridor -- ^ corredor da casa
           -> Corridor 
placeHouse _ _ [] _ = []
placeHouse c lgth (h1:t1) (h2:t2) | c>=((div lgth 2)-5) && c<=((div lgth 2)+b) = h2:placeHouse (c+1) lgth t1 t2
                                  | c<(div lgth 2)-5 = h1:placeHouse (c+1) lgth t1 (h2:t2)
                                  | otherwise = [h2] ++ t1
                                         where b | (odd lgth == True) = 4
                                                 | otherwise = 3



-- | Estrutura da casa ímpar.
--
oddHouse :: Maze
oddHouse = [
              [Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty],
              [Empty, Wall, Wall, Wall, Empty, Empty, Empty, Wall, Wall, Wall, Empty],
              [Empty, Wall, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Wall, Empty],
              [Empty, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Empty],
              [Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty]
           ]



-- | Estrutura da casa par.
--
evenHouse :: Maze
evenHouse = [
              [Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty],
              [Empty, Wall, Wall, Wall, Empty, Empty, Wall, Wall, Wall, Empty],
              [Empty, Wall, Empty, Empty, Empty, Empty, Empty, Empty, Wall, Empty],
              [Empty, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Empty],
              [Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty]
            ]



-- | Função principal que gera o labirinto.
--
generateMaze :: Int -- ^ largura do maze
             -> Int -- ^ altura do maze
             -> Int  -- ^ seed
             -> Maze
generateMaze l a s = 
     let nr = (l-2) * (a-2) 
         randoms = generateRandoms nr s
         pieces  = numbersToPieces randoms
         m = listToMaze (l-2) pieces
         withWalls = sideWall m
         e = updownmaze withWalls
         x = addTunnel a e
         y = addHouse l x
     in y