module Ficha4 where

import Data.Char

--1--
digitAlpha :: String -> (String,String)
digitAlpha l = separa l ([],[])

separa :: String -> (String,String) -> (String,String)
separa [] (l,d) = (l,d)
separa (h:t) (l,d) | isDigit h = separa t (l,d++[h])
                   | isAlpha h = separa t (l++[h],d)
                   | otherwise = separa t (l,d)


--2--
nzp :: [Int] -> (Int,Int,Int)
nzp l = conta l (0,0,0)

conta :: [Int] -> (Int,Int,Int) -> (Int,Int,Int)
conta [] (menor,ig,maior) = (menor,ig,maior)
conta (h:t) (menor,ig,maior) | h<0 = conta t (menor+1, ig, maior)
                             | h==0 = conta t (menor, ig+1, maior)
                             | h>0 = conta t (menor, ig, maior+1)


--3--
mydivMod :: Integral a => a -> a -> (a,a)
mydivMod x y | x < y = (0,x)
             | otherwise = (1+l1, l2)
                where (l1,l2) = (x-y,y)


--4--
fromDigits :: [Int] -> Int
fromDigits [] = 0
fromDigits l@(h:t) = fromDigAux l (length t)

fromDigAux :: [Int] -> Int -> Int
fromDigAux [x] _ = x
fromDigAux (h:t) exp = h*(10^exp) + fromDigAux t (exp-1)


--5--
maxSumInit :: (Num a, Ord a) => [a] -> a
maxSumInit l = maxSumInitAux l 0 0

maxSumInitAux :: (Num a, Ord a) => [a] -> a -> a -> a
maxSumInitAux [] max sum = max
maxSumInitAux (h:t) max sum | (sum+h) > max = maxSumInitAux t (sum+h) (sum+h) --atualizar o max
                            | otherwise = maxSumInitAux t max (sum+h)


--6--
fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = fibAux n 0 1

fibAux :: Int -> Int -> Int -> Int
fibAux 0 elem_n prox = elem_n
fibAux n elem_n prox = fibAux (n-1) prox (elem_n + prox)


--7--
intToStr :: Integer -> String
intToStr = undefined


--8--
--a--
a8 = [x | x <- [1..20], mod x 2 == 0, mod x 3 == 0]
--Números entre 1 e 20 divisíveis por 2 e 3
--[6,12,18]

--b--
b8 = [x | x <- [y | y <- [1..20], mod y 2 == 0], mod x 3 == 0]
--Números entre 1 e 20 divisíveis por 2 e 3
--[6,12,18]

--c--
c8 = [(x,y) | x <- [0..20], y <- [0..20], x+y == 30]
--Tuples com cada componente de 0 a 20, tal que a soma das 2 seja 30
--[(10,20),(11,19),(12,18),(13,17),(14,16),(15,15),(16,14),(17,13),(18,12),(19,11),(20,10)]

--d--
d8 = [sum [y | y <- [1..x], odd y] | x <- [1..10]]
--Somatório dos números ímpares das listas [1] , [1,2] , [1,2,3] ... até 10
--[1,1,4,4,9,9,16,16,25,25]


--9--
--a--
--[1,2,4,8,16,32,64,128,256,512,1024]
a9 = [2^x | x <- [1..10]]

--b--
--[(1,5),(2,4),(3,3),(4,2),(5,1)]
b9 = [(x,y) | x <- [1..5], y <- [1..5], x+y == 6]

--c--
--[[1],[1,2],[1,2,3],[1,2,3,4],[1,2,3,4,5]]
c9 = [[1..x] | x <- [1..5]]

--d--
--[[1],[1,1],[1,1,1],[1,1,1,1],[1,1,1,1,1]]
d9 = [replicate n 1 | n <- [1..5]]

--e--
--[1,2,6,24,120,720]
factorial :: Int -> Int
factorial 0 = 1
factorial n = n * factorial (n-1)

e9 = [factorial x | x <- [1..6]]