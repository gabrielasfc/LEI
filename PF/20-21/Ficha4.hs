module Ficha4 where
import Data.Char



--1--
--a--
l1A = [x | x <- [1..20] , mod x 2 == 0 , mod x 3 == 0] 

-- Números de 1 a 20 divisíveis por 2 e por 3 simultaneamente
-- [6,12,18]


--b--
l1B = [x | x <- [y | y <- [1..20], mod y 2 == 0], mod x 3 == 0]

-- A mesma coisa que lA


--c--
l1C = [(x,y) | x <- [0..20], y <- [0..20], x+y == 30]

-- Pares com cada componente de 0 a 20 tais que a soma dos 2 é 20
-- [(15,15), (14,16), (16,14), (13,17), (17,13), (12,18), (18,12), (11,19), (19,11), (10,20), (20,10)]


--d--
l1D = [sum [y | y <- [1..x], odd y] | x <- [1..10]]

--Sómatório dos números ímpares das listas [1] , [1,2] , [1,2,3] ... e por aí fora até 10
-- [1,1,4,4,9,9,16,16,25,25]



--2--
--a--
l2A = [1,2,4,8,16,32,64,128,256,512,1024]

l2A' = [ 2^x | x <- [1..10]]


--b--
l2B = [(1,5),(2,4),(3,3),(4,2),(5,1)]

l2B' = [(x,y) | x <- [1..5], y <- [1..5], x+y==6]


--c--
l2C = [[1],[1,2],[1,2,3],[1,2,3,4],[1,2,3,4,5]]

l2C' = [ [1..x] | x <- [1..5] ]


--d--
l2D = [[1],[1,1],[1,1,1],[1,1,1,1],[1,1,1,1,1]]

l2D' = [replicate n 1 | n <- [1..5]]


--e--
l2E = [1,2,6,24,120,720]

--l2E' = [product x y | y <- [1..x], x <- [1..6]]



--3--
digitAlpha :: String -> (String,String)
digitAlpha [] = ([],[])
digitAlpha s = (filter isDigit s, filter isDigit s)


--4--
nzp :: [Int] -> (Int,Int,Int)
nzp [] = (0,0,0)
nzp l = (length (filter (<0) l) , length (filter (==0) l) , length (filter (>0) l))


--5--
divMod :: Integral a => a -> a -> (a, a)
divMod x y = (divide x y , resto x y)

divide :: Integral a => a -> a -> a
divide x y | x<y = 0
           | otherwise = 1 + divide (x-y) y

resto :: Integral a => a -> a -> a
resto x y | x<y = x
          | otherwise = resto (x-y) y



--6--
fromDigits :: [Int] -> Int
fromDigits [] = 0
fromDigits (h:t) = h*10^(length t) + fromDigits t

--fromDigits [1,2,3,4] = 1 × 10^3 + 2 × 10^2 + 3 × 10^1 + 4 × 10^0
--                     = 4 + 10 × (3 + 10 × (2 + 10 × (1 + 10 × 0)))

myfromDigits :: [Int] -> Int
myfromDigits [] = 0
myfromDigits (h:t) = auxfd h (length t) + fromDigits t

auxfd :: Int -> Int -> Int
auxfd x 0 = x
auxfd x y = x * 10^y



--7--
maxSumInit :: (Num a, Ord a) => [a] -> a
maxSumInit l = maximum [sum m | m <- inits l]

inits :: [a] -> [[a]]
inits [] = [[]]
inits l = inits (init l) ++ [l]

maxSumInit' :: (Num a, Ord a) => [a] -> a
maxSumInit' = undefined



--8--
fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = fib (n-1) + fib (n-2)

--fib 3 = fib 2 + fib 1
--fib 2 = fib 1 + fib 0 = 1

myfib :: Int -> Int
myfib = undefined