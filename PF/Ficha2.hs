module Ficha2 where

import Data.Char

--1--
--a--
{-
funA [2,3,5,1]
    = 4 + funA [3,5,1]
    = 4 + 9 + funA [5,1]
    = 13 + 25 + funA [1]
    = 38 + 1 + funA [] = 39 + 0 = 39
-}

--b--
{-
funB [8,5,12]
    = 8 : funB [5,12]
    = 8 : funB [12]
    = 8 : 12 : [] = [8,12]
-}

--c--
{-
funC [1,2,3,4,5]
    = funC [3,4,5]
    = funC [5] = [5]
-}

--d--
{-
funD "otrec"
    = g [] "otrec"
    = g "o" "trec"
    = g "to" "rec"
    = g "rto" "ec"
    = g "erto" "c"
    = g "certo" [] = "certo"
-}


--2--
--a-
dobros :: [Float] -> [Float]
dobros [] = []
dobros (h:t) = (2*h) : dobros t

--b-
numOcorre :: Char -> String -> Int
numOcorre _ [] = 0
numOcorre c (h:t) | c==h = 1 + numOcorre c t
                  | otherwise = numOcorre c t

--c--
positivos :: [Int] -> Bool
positivos [] = False
positivos [x] = x>0
positivos (h:t) | h < 0 = False
                | otherwise = positivos t

--d--
soPos :: [Int] -> [Int]
soPos [] = []
soPos (h:t) | h>0 = h : soPos t
            | otherwise = soPos t

--e--
somaNeg :: [Int] -> Int
somaNeg [] = 0
somaNeg (h:t) | h<0 = h + somaNeg t
              | otherwise = somaNeg t

--f--
tresUlt :: [a] -> [a]
tresUlt l@(h:t) | length l <= 3 = l
                | otherwise = tresUlt t

--g--
segundos :: [(a,b)] -> [b]
segundos [] = []
segundos ((a,b):t) = b : segundos t

--h--
nosPrimeiros :: (Eq a) => a -> [(a,b)] -> Bool
nosPrimeiros _ [] = False
nosPrimeiros x ((a,b):t) | x==a = True
                         | otherwise = nosPrimeiros x t

--i--
sumTriplos :: (Num a, Num b, Num c) => [(a,b,c)] -> (a,b,c)
sumTriplos [] = (0,0,0)
sumTriplos [x] = x
sumTriplos ((a,b,c):(x,y,z):t) = sumTriplos ((a+x,b+y,c+z):t)


--3--
--a--
soDigitos :: [Char] -> [Char]
soDigitos [] = []
soDigitos (h:t) | isDigit h = h : soDigitos t
                | otherwise = soDigitos t

--b--
minusculas :: [Char] -> Int
minusculas [] = 0
minusculas (h:t) | isLower h = 1 + minusculas t
                 | otherwise = minusculas t

--c--
nums :: String -> [Int]
nums [] = []
nums (h:t) | isDigit h = digitToInt h : nums t
           | otherwise = nums t


--4--
type Polinomio = [Monomio]
type Monomio = (Float,Int)

--a--
conta :: Int -> Polinomio -> Int
conta _ [] = 0
conta g ((_,e):t) | g==e = 1 + conta g t
                  | otherwise = conta g t

--b--
grau :: Polinomio -> Int
grau p = maximum $ recolhegraus p

recolhegraus :: Polinomio -> [Int]
recolhegraus [] = []
recolhegraus ((c,e):t) = e : recolhegraus t

--c--
selgrau :: Int -> Polinomio -> Polinomio
selgrau _ [] = []
selgrau g ((c,e):t) | e==g = (c,e) : selgrau g t
                    | otherwise = selgrau g t

--d--
deriv :: Polinomio -> Polinomio
deriv [] = []
deriv ((c,e):t) | e==0 = (0,0) : deriv t
                | otherwise = (c * (fromIntegral e), e-1) : deriv t

--e--
calcula :: Float -> Polinomio -> Float
calcula x [] = 0
calcula x ((c,e):t) = c * (x^e) + calcula x t

--f--
simp :: Polinomio -> Polinomio
simp [] = []
simp ((c,e):t) | c==0 = simp t
               | otherwise = (c,e):t

--g--
mult :: Monomio -> Polinomio -> Polinomio
mult _ [] = []
mult (x,y) ((c,e):t) = (x*c, y+e) : mult (x,y) t

--h--
normaliza :: Polinomio -> Polinomio
normaliza [] = []
normaliza [(c,e)] = [(c,e)]
normaliza ((c1,e1):(c2,e2):t) | e1==e2 = normaliza ((c1+c2,e1):t)
                              | conta e1 t == 0 && e1/=e2 = (c1,e1) : normaliza ((c2,e2):t) -- ^ se não há elementos com o grau do primeiro na tail
                              | otherwise = normaliza $ (c1,e1):t ++ [(c2,e2)] -- ^ se há elementos de grau igual ao primeiro na tail

--i--
soma :: Polinomio -> Polinomio -> Polinomio
soma [] [] = []
soma p [] = p
soma [] p = p
soma p1 p2 = normaliza (p1 ++ p2)

--j--
produto :: Polinomio -> Polinomio -> Polinomio
produto [] _ = []
produto _ [] = []
produto (h:t) p2 = normaliza $ mult h p2 ++ produto t p2

--k--
ordena :: Polinomio -> Polinomio
ordena [] = []
ordena (h:t) = (ordena menores) ++ [h] ++ (ordena maiores)
                    where menores = filter (< h) t
                          maiores = filter (>= h) t

--i--
equiv :: Polinomio -> Polinomio -> Bool
equiv [] [] = True
equiv p1 p2 = ordena (simp (normaliza p1)) == ordena (simp (normaliza p2))