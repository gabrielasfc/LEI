{-|
Module      : Tarefa3
Description : Compactar labirinto
Copyright   : Daniel Furtado <a97327@alunos.uminho.pt>;
              Gabriela Cunha <a97393@alunos.uminho.pt>

= Introdução

Nesta tarefa compactamos o labirinto, tornando-o numa lista de instruções de modo a facilitar a leitura.


= Objetivos e estratégias 

No início da tarefa pensamos em primeiro elaborar o que está dentro da "Instruct", ou seja, colocar tudo em pares de inteiros e peças e só depois focar na parte do "Repeat", que acontece quando há corredores iguais.

Em relação ao que está dentro da instrução __/Instruct/__ :

- Agrupamos as peças iguais e seguidas de modo a tornar o labirinto em pares em que a primeira componente é o nº de peças seguidas iguais e a segunda a respetiva peça;

Para a realização de função utilizamos 2 funções auxiliares:

 1. Uma para transformar o corredor em formato (1,Peça);

 2. Outra que verifica se a peça a seguir é igual à anterior e se isto acontecer soma as primeiras componentes dos pares e mantém a segunda;
 
Já em relação à instrução __/Repeat/__ :

Pretendemos comparar os corredores dos labirintos um a um para saber se deveríamos usar o __/Repeat/__ caso já existisse um igual e ainda saber o índice da primeira vez que o corredor aparecia.

Assim sendo, utilizamos uma função que recebia 2 mazes iguais e comparava cada corredor do 1º Maze com todos do segundo e guardava o índice no 2º Maze da primeira vez que aparecesse um corredor igual ao corredor dado;

Para esta função recorremos a uma função auxiliar que dado um corredor devolvia a posição do corredor no Maze.

Com as funções terminandas, pudemos então juntar as funções e aplicar as instruções na função __'instructMaze'__.

Na função principal utilizamos a função __'instructMaze'__ para aplicar as instruções e as funções __'mazeToTuple'__ e __'corridorIndex'__ para transformar o Maze dado nos tuplos pretendidos inicialmente e obter os índices dos corredores.


= Conclusão

Apesar desta tarefa ser rápida e mais simples em relação às 2 anteriores, foi bastante útil para simplificar os nossos testes e exemplos e tornar o nosso código mais "limpo".

Concluímos também que nos ajudou a perceber o quão facilita às vezes recorrer a funções auxiliares e acumuladores porque foi algo bastante usado ao longo da tarefa e que ajudou imenso.

-}


module Tarefa3 where

import Types
import Tarefa1
import Tarefa2


{-| Converte um corredor para uma lista de tuplos (Integer,Piece).

__Exemplo :__

 @
 corridorToTuple [Wall,Empty,Wall,Wall,Food Big] = [(1,Wall),(1,Empty),(1,Wall),(1,Wall),(1,Food Big)]
 @
 -}
corridorToTuple :: Corridor -> [(Int,Piece)]
corridorToTuple [] = []
corridorToTuple (Food Little : t) = (1,Food Little) : corridorToTuple t
corridorToTuple (Food Big : t) = (1,Food Big) : corridorToTuple t
corridorToTuple (Wall : t) = (1,Wall) : corridorToTuple t
corridorToTuple (Empty : t) = (1,Empty) : corridorToTuple t   



{-| Converte um labirinto numa lista de corredor no tipo (Integer,Piece).

Utiliza as funções __'corridorToTuple'__ and __'gatherPieces'__. 

Devolve já um labirinto onde os corredores são listas de tuplos e as peças seguidas estão juntas.
-}
mazeToTuple :: Maze -> [[(Int, Piece)]]
mazeToTuple [] = []
mazeToTuple (h:t) = gatherPieces (corridorToTuple h) : mazeToTuple t



{- | A função __gatherPieces__ junta tuplos seguidos se a peça for a mesma.
 
__Exemplo :__

@
gatherPieces [(1,Wall),(1,Empty),(1,Wall),(1,Wall),(1,Food Big)] = [(1,Wall),(1,Empty),(2,Wall),(1,Food Big)].
@
-}
gatherPieces :: [(Int,Piece)] -> [(Int,Piece)]
gatherPieces [] = []
gatherPieces [x] = [x]
gatherPieces ((x,y):(a,b):t) | y==b = gatherPieces ((x+a,y):t)
                             | otherwise = (x,y):gatherPieces ((a,b):t)



{- | A função __corridorIndex__ recebe um corredor e um labirinto e devolve a posição do corredor no labirinto.

Usamos um acumulador para ajudar a contar a posição. O acumulador começa sempre em __0__. 
 -}
corridorIndex :: Int -> Corridor -> Maze -> Int
corridorIndex i c (h:t) | c==h = i
                        | otherwise = corridorIndex (i+1) c t



{- | A função __mazeIndex__ recebe __2__ labirintos e compara cada corredor do primeiro Maze com todos do segundo.
 
-Quando o corredor do 1º Maze é igual ao do 2º, a função guarda o índice do corredor no 2º Maze e aplica a função ao próximo corredor do 1º Maze. 

-Como comparamos labirintos iguais, a função verifica qual é o índice da 1ª vez que cada corredor do 1º maze aparece no 2º e guarda os índices numa lista.

-Na função voltamos a recorrer a um acumulador.

__Exemplo :__

@
mazeIndex 0 [[Wall,Wall],[Wall,Food Big],[Wall,Food Big],[Wall,Wall],[Empty,Empty]] [[Wall,Wall],[Wall,Food Big],[Wall,Food Big],[Wall,Wall],[Empty,Empty]] = [0,1,1,0,4]
@
-}
mazeIndex :: Int -> Maze -> Maze -> [Int]
mazeIndex  _ [] _ = []
mazeIndex c m1 m2 | elem (head m1) m2 = (corridorIndex c (head m1) m2) : mazeIndex c (drop 1 m1) m2
                  | otherwise = c : mazeIndex c (drop 1 m1) m2



{- | Recebe uma lista de números e um labirinto em tuplos e retorna a lista de corredores com __Instruct__ e __Repeat__.
 
Voltamos a usar um acumulador.

__Exemplo :__

@
instructMaze 0 [0,1,1,0,4] [[(2,Wall)],[(1,Wall),(1,Food Big)],[(1,Wall),(1,Food Big)],[(2,Wall)],[(2,Empty)]] = [Instruct [(2,#)],Instruct [(1,#),(1,o)],Repeat 1,Repeat 0,Instruct [(2, )]]
@
-}
instructMaze :: Int -> [Int] -> [[(Int,Piece)]] -> Instructions
instructMaze _ _ [] = []
instructMaze c (h:t) m | c==h = Instruct (head m) : instructMaze (c+1) t (tail m)
                       | otherwise = Repeat h : instructMaze (c+1) t (tail m) 



{- | Função principal que compacta o maze.

Recebe um Maze e retorna o Maze com as peças agrupadas em corredores com __Instruct__ e __Repeat__.

 __Exemplo :__

@
compactMaze [[Wall,Wall],[Wall,Food Big],[Wall,Food Big],[Wall,Wall],[Empty,Empty]] = [Instruct [(2,#)],Instruct [(1,#),(1,o)],Repeat 1,Repeat 0,Instruct [(2, )]]
@
-}
compactMaze :: Maze  -> Instructions
compactMaze m = let tp =  mazeToTuple m
                    c = corridorIndex 0 (head m) m
                    mi = mazeIndex 0 m m 
                in instructMaze 0 mi tp