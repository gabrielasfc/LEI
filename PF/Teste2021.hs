module Teste2021 where

--1--
mydelete :: Eq a => a -> [a] -> [a]
mydelete _ [] = []
mydelete x (h:t) | x==h = t
                 | otherwise = h : mydelete x t

deleteLists :: Eq a => [a] -> [a] -> [a]
deleteLists [] _ = []
deleteLists l [] = l
deleteLists l (h:t) = deleteLists (mydelete h l) t


--2--
type MSet a = [(a,Int)]
--a--
removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet a ((x,y):t) | a==x && y==1 = t
                       | a==x = (x,y-1):t
                       | otherwise = (x,y) : removeMSet a t

--b--
calcula :: MSet a -> ([a],Int)
calcula l = foldr (\(x,y) a -> (x : fst a, y + snd a)) ([] , 0) l

--sem 1 só travessia e a juntar os repetidos
calcula2 :: Eq a => MSet a -> ([a],Int)
calcula2 l = (map fst (simpMSet l), sum (map snd (simpMSet l)))

contaMSet :: Eq a => a -> [(a,Int)] -> Int
contaMSet a [] = 0
contaMSet a ((x,y):t) | a==x = y + contaMSet a t
                      | otherwise = contaMSet a t

simpMSet :: Eq a => [(a,Int)] -> MSet a
simpMSet [] = []
simpMSet ((x,y):t) = (x, y + contaMSet x t) : simpMSet (removeMSet x t)

--3--
partes :: String -> Char -> [String]
partes [] _ = []
partes str@(h:t) c | h == c = partes t c
                   | otherwise = (takeWhile (/=c) str) : partes (dropWhile (/=c) str) c


--4--
data BTree a = Empty | Node a (BTree a) (BTree a)

--a--
remove :: Ord a => a -> BTree a -> BTree a
remove _ Empty = Empty
remove x (Node r e d) | r>x = Node r (remove x e) d
                      | r<x = Node r e (remove x d)
                      | otherwise = removeAux x (Node r e d)

removeAux :: Ord a => a -> BTree a -> BTree a
removeAux _ (Node _ Empty d) = d
removeAux _ (Node _ e Empty) = e
removeAux x (Node r e d) = Node new_r e new_d 
                              where (new_r, new_d) = minSmin d

minimo :: Ord a => BTree a -> a
minimo (Node r Empty _) = r
minimo (Node r e d) = minimo e

semMinimo :: Ord a => BTree a -> BTree a
semMinimo (Node r Empty d) = d
semMinimo (Node r e d) = Node r (semMinimo e) d

minSmin :: Ord a => BTree a -> (a, BTree a)
minSmin (Node r Empty d) = (r,d)
minSmin (Node r e d) = (minimo e, Node r (semMinimo e) d)

--b--
instance Show a => Show (BTree a) where
    show Empty = "*"
    show (Node r e d) = "(" ++ show e ++ "<-" ++ (show r) ++ "->" ++ show d ++ ")"


--5--
mySortOn :: Ord b => (a -> b) -> [a] -> [a]
mySortOn _ [] = []
mySortOn _ [x] = [x]
mySortOn f (h:t) | f h <= minimum (map f t) = h : mySortOn f t
                 | otherwise = mySortOn f (t++[h])


--6--
data FileSystem = File Nome | Dir Nome [FileSystem]
type Nome = String

--a--
fichs :: FileSystem -> [Nome]
fichs (File n) = [n]
fichs (Dir n l) = concat $ map fichs l

--b--
dirFiles :: FileSystem -> [Nome] -> Maybe [Nome]
dirFiles f [] = Nothing
dirFiles (File _) _ = Nothing
dirFiles (Dir n l) [z] | n == z = Just (getNomes l) 
                       | otherwise = Nothing
dirFiles (Dir n l) (h:t) | n /= h = Nothing
                         | otherwise = Just $ concat (aux rf)
                                                where rf = [dirFiles f t | f <- l]

aux :: [Maybe a] -> [a]
aux [] = [] 
aux (Nothing :t) = aux t
aux ((Just x):t) = x : aux t

getNomes :: [FileSystem] -> [Nome] 
getNomes [] = [] 
getNomes ((Dir n l):t) = getNomes t
getNomes ((File n):t) = n : getNomes t

--c--
listaFich :: FileSystem -> IO ()
listaFich f = do putStrLn "Indique a diretoria"
                 path <- getLine
                 if (dirFiles f (partes path '/')) == Nothing then putStr "A diretoria indicada não existe."
                                                              else putStrLn (unwords $ func $ dirFiles f (partes path '/'))

func :: Maybe a -> a
func (Just a) = a                                                             