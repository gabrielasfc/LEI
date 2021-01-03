module Ficha2 where

import Data.Char



--1--
--a--
funA :: [Double] -> Double 
funA [] = 0 
funA (y:ys) = y^2 + (funA ys)

{-
Faz a soma de todos os elementos da lista elevados ao quadrado
Eleva a head da lista ao quadrado e soma o resultado de voltar a aplicar a função à tail, pegando na head da tail
E assim sucessivamente

funA [2,3,5,1]
   = 4 + funA [3,5,1]
   = 4 + 9 + funA [5,1]
   = 13 + 25 + funA [1]
   = 38 + 1 + funA [] = 39 + 0 = 39
-}


--b--
funB :: [Int] -> [Int]
funB [] = []
funB (h:t) = if (mod h 2)==0 then h : (funB t)
             else (funB t)

{-
A função devolve a lista de inteiros recebida e devolve uma lista apenas com os números pares
Se a head for par então ele devolve a head e volta a aplicar a função à tail
Se a head for ímpar então ele apenas aplica a função à tail

funB [8,5,12]
   = 8 : funB [5,12]
   = 8 : funB [12]
   = 8 : 12 : [] = [8,12]
-}


--c--
funC (x:y:t) = funC t
funC [x] = []
funC [] = []

{-
A função remove todos os elementos de uma lista
Recebe uma lista e remove os 2 primeiros elementos e aplica a função sobre a tail
Se receber uma lista vazia ou apenas com um elemento devolve uma lista vazia

funC [1,2,3,4,5]
   = funC [3,4,5]
   = funC [5] = []
-}


--d--
funD l = g [] l
g l [] = l
g l (h:t) = g (h:l) t

{-
Recebe uma lista de caracteres e devolve-a invertida

funD "otrec"
   = g [] "otrec"
   = g o:[] "trec"
   = g t:o:[] "rec"
   = g r:t:o:[] "ec"
   = g e:r:t:o:[] "c"
   = g c:e:r:t:o:[] []
   = g "certo" 
-}



--2--
--a--
dobros :: [Float] -> [Float]
dobros [] = []
dobros (h:t) = 2*h : dobros t


--b--
numOcorre :: Char -> String -> Int
numOcorre x [] = 0
numOcorre x (h:t) | x==h = 1 + (numOcorre x t)
                  | otherwise = numOcorre x t


--c--
positivos :: [Int] -> Bool
positivos [] = False
positivos (h:t) | h>0 = True
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
tresUlt l | length l <= 3 = l
          | otherwise = drop (length l -3) l


--g--
segundos :: [(a,b)] -> [b]
segundos [] = []
segundos ((_,y):t) = y : segundos t


--h--
nosPrimeiros :: (Eq a) => a -> [(a,b)] -> Bool
nosPrimeiros _ [] = False
nosPrimeiros x ((a,b):t) | x==a = True
                         | otherwise = nosPrimeiros x t


--i--
sumTriplos :: (Num a, Num b, Num c) => [(a,b,c)] -> (a,b,c)
sumTriplos [] = (0,0,0)
sumTriplos [(a,b,c)] = (a,b,c)
sumTriplos ((a,b,c):(x,y,z):t) =  sumTriplos ((a+x,b+y,c+z):t)



--3--
--a--
soDigitos :: [Char] -> [Char]
soDigitos [] = []
soDigitos (h:t) | h>='0' && h<'9' = h : soDigitos t


--b--
minusculas :: [Char] -> Int
minusculas [] = 0
minusculas (h:t) | h>='a' && h<='z' = 1 + minusculas t
                 | otherwise = minusculas t


--c--
nums :: String -> [Int]
nums [] = []
nums (h:t) | h>='0' && h<='9' = digitToInt h : nums t
           | otherwise = nums t



--4--
type Polinomio = [Monomio]
type Monomio = (Float,Int) -- ^ (coeficiente,expoente)

--a--
conta :: Int -> Polinomio -> Int
conta _ [] = 0
conta g ((c,e):t) | g==e = 1 + conta g t
                  | otherwise = conta g t


--b--
grau :: Polinomio -> Int
grau [] = 0
grau [(c,e)] = e
grau ((x,y):(a,b):t) | y>b = grau ((x,y):t)
                     | otherwise = grau ((a,b):t)


--c--
selgrau :: Int -> Polinomio -> Polinomio
selgrau _ [] = []
selgrau g ((c,e):t) | g==e = (c,e) : selgrau g t
                    | otherwise = selgrau g t


--d--
deriv :: Polinomio -> Polinomio
deriv [] = []
deriv ((c,e):t) | e==0 = (0,0) : deriv t
                | otherwise = (c * (fromIntegral e) , e-1) : deriv t


--e--
calcula :: Float -> Polinomio -> Float
calcula x [] = 0
calcula x ((c,e):t) = c * (x^e) + calcula x t


--f--
simp :: Polinomio -> Polinomio
simp [] = []
simp ((c,e):t) | e==0 = simp t
               | otherwise = (c,e) : simp t


--g--
mult :: Monomio -> Polinomio -> Polinomio
mult _ [] = []
mult (a,b) ((c,e):t) = (a*c,b+e) : mult (a,b) t


--h--
normaliza :: Polinomio -> Polinomio
normaliza [] = []
normaliza [(c,e)] = [(c,e)]
normaliza ((x,y):(a,b):t) | y==b = normaliza ((x+a,y):t)
                          | conta y t == 0 && y/=b = (x,y) : normaliza ((a,b):t) -- ^ se há elementos com o grau do primeiro na tail
                          | otherwise = normaliza $ (x,y):t ++ [(a,b)] -- ^ se não há elementos de grau igual ao segundo na tail


--i--
soma :: Polinomio -> Polinomio -> Polinomio
soma [] [] = []
soma p [] = p
soma [] p = p
soma p1 p2 = normaliza (p1 ++ p2)


--j--
produto :: Polinomio -> Polinomio -> Polinomio
produto [] [] = []
produto p [] = []
produto [] p = []
produto (h:t) p2 = produtoaux h p2 ++ produto t p2


produtoaux :: Monomio -> Polinomio -> Polinomio
produtoaux _ [] = []
produtoaux (x,y) ((a,b):t) = ( x*a , y+b) : produtoaux (x,y) t


--k--
ordena :: Polinomio -> Polinomio
ordena [] = []
ordena (h:t) = (ordena menores) ++ [h] ++ (ordena maiores)
    where menores = filter (< h) t
          maiores = filter (>= h) t


--l--
equiv :: Polinomio -> Polinomio -> Bool
equiv p1 p2 = ordena (normaliza p1) == ordena (normaliza p2)