module Ficha5 where

--1--
--a--
myAny :: (a -> Bool) -> [a] -> Bool
myAny f [] = False
myAny f (h:t) | f h = True
              | otherwise = myAny f t

--b--
myZipWith :: (a->b->c) -> [a] -> [b] -> [c]
myZipWith _ [] _ = []
myZipWith _ _ [] = []
myZipWith f (h1:t1) (h2:t2) = f h1 h2 : myZipWith f t1 t2

--c--
myTakeWhile :: (a->Bool) -> [a] -> [a]
myTakeWhile _ [] = []
myTakeWhile f (h:t) | f h = h : myTakeWhile f t
                    | otherwise = []

--d--
myDropWhile :: (a->Bool) -> [a] -> [a]
myDropWhile _ [] = []
myDropWhile f (h:t) | f h = myDropWhile f t
                    | otherwise = (h:t)

--e--
mySpan :: (a->Bool) -> [a] -> ([a],[a])
mySpan _ [] = ([],[])
mySpan f l@(h:t) | f h = (h:a, b)
                 | otherwise = ([], l)
                        where (a,b) = mySpan f t

--f--
myDeleteBy :: (a -> a -> Bool) -> a -> [a] -> [a]
myDeleteBy _ _ [] = []
myDeleteBy f x (h:t) | f x h = t
                     | otherwise = h : myDeleteBy f x t

--g--
mySortOn :: Ord b => (a -> b) -> [a] -> [a]
mySortOn _ [] = []
mySortOn f (h:t) = insert h (mySortOn f t)
                     where insert x [] = [x]
                           insert x (h:t) | f x >= f h = h : insert x t
                                          | otherwise = x:h:t


mySortOn2 :: Ord b => (a -> b) -> [a] -> [a]
mySortOn2 _ [] = []
mySortOn2 _ [x] = [x]
mySortOn2 f (h:t) | f h <= minimum (map f t) = h : mySortOn2 f t
                  | otherwise = mySortOn2 f (t ++ [h])


--2--
type Polinomio = [Monomio]
type Monomio = (Float,Int)

--a--
selgrau :: Int -> Polinomio -> Polinomio
selgrau g p = filter (\(c,e) -> e==g) p

--b--
conta ::Int -> Polinomio -> Int
conta g p = sum $ map (\(c,e) -> if e==g then 1 else 0) p

--c--
grau :: Polinomio -> Int
grau p = maximum $ map snd p

--d--
deriv :: Polinomio -> Polinomio
deriv p = let p1 = map (\(c,e) -> (c*(fromIntegral e), e-1)) p
          in filter (\(c,e) -> c/=0) p1

--e--
calcula :: Float -> Polinomio -> Float
calcula x p = sum $ map (\(c,e) -> c*(x^e)) p

--f--
simp :: Polinomio -> Polinomio
simp p = filter (\(c,e) -> c/=0) p

--g--
mult :: Monomio -> Polinomio -> Polinomio
mult (x,y) p = map (\(c,e) -> (c*x, e+y)) p

--h--
ordena :: Polinomio -> Polinomio
ordena p = mySortOn snd p

--i--
normaliza :: Polinomio -> Polinomio
normaliza p = undefined

--j--
soma :: Polinomio -> Polinomio -> Polinomio
soma p1 p2 = undefined

--k--
produto :: Polinomio -> Polinomio -> Polinomio
produto p1 p2 = undefined

--l--
equiv :: Polinomio -> Polinomio -> Bool
equiv p1 p2 = undefined


--3--
type Mat a = [[a]]

--a--
dimOK :: Mat a -> Bool
dimOK [] = True
dimOK [l] = True
dimOK (l1:l2:t) = length l1 == length l2 && dimOK (l2:t)

dimOK2 :: Mat a -> Bool
dimOK2 (h:t) = all (\x -> length h == length x) t

--b--
dimMat :: Mat a -> (Int,Int)
dimMat [[]] = (0,0)
dimMat [] = (0,0)
dimMat m = (length m, length $ head m)

--c--
addMat :: Num a => Mat a -> Mat a -> Mat a
addMat [] [] = []
addMat (l1:t1) (l2:t2) = (zipWith (+) l1 l2) : addMat t1 t2

--d--
transpose :: Mat a -> Mat a
transpose ([]:_) = []
transpose m = (map head m) : transpose (map tail m)

--e--
multMat :: Num a => Mat a -> Mat a -> Mat a
multMat = undefined

--f--
zipWMat :: (a -> b -> c) -> Mat a -> Mat b -> Mat c
zipWMat _ [] _ = []
zipWMat _ _ [] = []
zipWMat f (l1:t1) (l2:t2) = (zipWith f l1 l2) : zipWMat f t1 t2

--g--
triSup :: (Eq a, Num a) => Mat a -> Bool
triSup m = undefined

--h--
rotateLeft :: Mat a -> Mat a
rotateLeft m = undefined