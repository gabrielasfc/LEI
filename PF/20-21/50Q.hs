module Q50 where


-- 1--
enumFromTo' :: Int -> Int -> [Int]
enumFromTo' a b | a<b = a:enumFromTo' (a+1) b
                | a==b = [a]
                | otherwise = a:enumFromTo' (a-1) b



--2--
enumFromThenTo' :: Int -> Int -> Int -> [Int]
enumFromThenTo' a b c | a<=c = a:enumFromThenTo' b (b+b-a) c
                      | otherwise = []



--3--
plusplus :: [a] -> [a] -> [a]
plusplus [] l = l
plusplus (h:t) l = h:plusplus t l



--4--
elemn :: [a] -> Int -> a
elemn (h:t) 0 = h
elemn (h:t) n = elemn t (n-1)



--5--
reverse' :: [a] -> [a]
reverse' [] =  []
reverse' (h:t) = reverse' t ++ [h]



--6--
take' :: Int -> [a] -> [a]
take' 0 (h:t) = []
take' n [] = []
take' n (h:t) = h:take' (n-1) t

 

--7--
drop' :: Int -> [a] -> [a]
drop' 0 (h:t) = (h:t)
drop' _ [] = []
drop' n (h:t) = drop' (n-1) t



--8--
zip' :: [a] -> [b] -> [(a,b)]
zip' [] _ = []
zip' _ [] = []
zip' (h1:t1) (h2:t2) = (h1,h2):zip' t1 t2



--9--
elem' :: Eq a => a -> [a] -> Bool
elem' _ [] = False
elem' n (h:t) | n==h = True
              | otherwise = elem' n t



--10--
replicate' :: Int -> a -> [a]
replicate' 0 _ = []
replicate' n a = a:replicate' (n-1) a



--11--
intersperse' :: a -> [a] -> [a]
intersperse' _ [] = []
intersperse' _ [x] = [x]
intersperse' a (h:t) = h:a:intersperse' a t



--12--
group' :: Eq a => [a] -> [[a]]
group' [] = []
group' l = aux12 l : group' restos
               where restos = drop (length (aux12 l)) l

aux12 :: Eq a => [a] -> [a]
aux12 [x] = [x]
aux12 (h:a:t) | h==a = h: aux12 (a:t)
              | otherwise = [h]



--13--
concat' :: [[a]] -> [a]
concat' [] = []
concat' (h:t) = h ++ concat' t



--14--
inits' :: [a] -> [[a]]
inits' [] = [[]]
inits' l = inits' (init l) ++ [l]



--15--
tails' :: [a] -> [[a]]
tails' [] = [[]]
tails' (h:t) = (h:t):tails' t 



--16--
isPrefixOf' :: Eq a => [a] -> [a] -> Bool
isPrefixOf' [] _ = True
isPrefixOf' (h1:t1) (h2:t2) | length (h1:t1) > length (h2:t2) = False
                            | h1==h2 = isPrefixOf' t1 t2
                            | otherwise = False



--17--
isSuffixOf' :: Eq a => [a] -> [a] -> Bool
isSuffixOf' [] _ = True
isSuffixOf' l1 l2 | length l1 > length l2 = False
                  | last l1 == last l2 = isSuffixOf' (init l1) (init l2)
                  | otherwise = False



--18--
isSubsequenceOf' :: Eq a => [a] -> [a] -> Bool
isSubsequenceOf' _ [] = False
isSubsequenceOf' [] _ = True
isSubsequenceOf' (h1:t1) (h2:t2) | h1==h2 = isSubsequenceOf' t1 t2
                                 | otherwise = isSubsequenceOf' (h1:t1) t2



--19--
elemIndices' :: Eq a => a -> [a] -> [Int]
elemIndices' _ [] = []
elemIndices' n (h:t) = aux19 0 n (h:t)

--auxiliar : acumulador
aux19 :: Eq a => Int -> a -> [a] -> [Int]
aux19 _ _ [] = []
aux19 acc n (h:t) | n==h = acc:(aux19 (acc+1) n t)
                  | otherwise = aux19 (acc+1) n t



--20--
nub' :: Eq a => [a] -> [a]
nub' [] = []
nub' l | elem (last l) (init l) = nub' (init l)
       | otherwise = (nub' (init l)) ++ [last l]



--21--
delete':: Eq a => a -> [a] -> [a]
delete' _ [] = []
delete' n (h:t) | n==h = t
                | otherwise = h:delete' n t



--22-- 
deleteList ::  Eq a => [a] -> [a] -> [a]
deleteList [] _ = []
deleteList l [] = l
deleteList l (h:t) = deleteList (delete' h l) t



--23--
union' :: Eq a => [a] -> [a] -> [a]
union' [] l = l
union' l [] = l
union' l (h:t) | elem h t==True = union' l t
               | otherwise = union' (l ++ [h]) t



--24--
intersect' :: Eq a => [a] -> [a] -> [a]
intersect' _ [] = []
intersect' [] _ = []
intersect' (h1:t1) (h2:t2) | elem' h1 (h2:t2) = h1:(intersect' t1 (h2:t2)) 
                           | otherwise = intersect' t1 (h2:t2)



--25--
insert' :: Ord a => a -> [a] -> [a]
insert' n [] = [n]
insert' n (h:t) | h<=n = h:insert' n t
                | otherwise = n:(h:t)



--26--
unwords' :: [String] -> String
unwords' [] = []
unwords' [x] = x
unwords' (h:t) = h ++ " " ++ unwords' t



--27--
unlines' :: [String] -> String
unlines' [] = []
unlines' [x] = x ++ "\n"
unlines' (h:t) = h ++ "\n" ++ unlines' t



--28--
pMaior :: Ord a => [a] -> Int
pMaior [x] = 0
pMaior l = aux28 l 0

--funçao aux maior
aux28 :: Ord a => [a]-> Int -> Int
aux28 (h:t) p | h==(maximum (h:t)) = p
              | otherwise = aux28 t (p+1)



--29--
temRepetidos :: Eq a => [a] -> Bool
temRepetidos [] = False
temRepetidos (h:t) | (elem h t == True) = True
                   | otherwise = temRepetidos t



--30--
algarismos :: [Char] -> [Char]
algarismos [] = []
algarismos (h:t) | h>='0' && h<='9' = h:algarismos t
                 | otherwise = algarismos t



--31--
posImpares :: [a] -> [a]
posImpares [] = []
posImpares [x] = []
posImpares (h:x:t) = x:posImpares t



--32--
posPares :: [a] -> [a]
posPares [] = []
posPares [x] = [x]
posPares (h:x:t) = h:posPares t



--33--
isSorted :: Ord a => [a] -> Bool
isSorted [] = True
isSorted [x] = True
isSorted (h:a:t) | h<=a = isSorted (a:t)
                 | otherwise = False



--34--
iSort :: Ord a => [a] -> [a]
iSort [] = []
iSort [x] = [x]
iSort (h:t) = insert' h (iSort t)



--35- 
menor :: String -> String -> Bool
menor "" "" = False
menor "" _ = True
menor _ "" = False
menor (h1:t1) (h2:t2) | h1<h2 = True
                      | h1>h2 = False
                      | otherwise = menor t1 t2



--36-- 
elemMSet :: Eq a => a -> [(a,Int)] -> Bool
elemMSet _ [] = False
elemMSet a ((x,y):t) | a==x = True
                     | otherwise = elemMSet a t



--37--
lengthMSet :: [(a,Int)] -> Int
lengthMSet [] = 0
lengthMSet ((x,y):t) = y + lengthMSet t



--38--
converteMSet:: [(a,Int)] -> [a]
converteMSet [] = []
converteMSet ((x,y):t) | y==0 = converteMSet t
                       | otherwise = x:converteMSet ((x,y-1):t)



--39--
insereMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
insereMSet a [] = [(a,1)]
insereMSet a ((x,y):t) | a==x = (a, y+1):t
                       | otherwise = (x,y):insereMSet a t



--40--
removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet a [] = []
removeMSet a ((x,y):t) | a==x && y==1 = t
                       | a==x && y>1 = (a,y-1):t
                       | otherwise = (x,y):removeMSet a t



--41--
constroiMSet :: Ord a => [a] -> [(a,Int)]
constroiMSet [] = []
constroiMSet (h:t) = (h,1 + length (filter (==h) t)) : constroiMSet (filter (/=h) t)



--42--
partEithers :: [Either a b] -> ([a],[b])
partEithers [] = ([],[])
partEithers l = (lefts l, rights l)

lefts :: [Either a b] -> [a] 
lefts [] = []
lefts (Left a:t) = a : lefts t
lefts (Right b:t) = lefts t

rights :: [Either a b] -> [b]
rights [] = []
rights (Right b:t) = b : rights t
rights (Left a:t) = rights t



--43--
catMaybes :: [Maybe a] -> [a]
catMaybes [] = []
catMaybes (Just a :t) = a:catMaybes t
catMaybes (Nothing:t) = catMaybes t



--44--
data Movimento = Norte | Sul | Este | Oeste
                 deriving Show

posicao :: (Int,Int) -> [Movimento] -> (Int,Int)
posicao (x,y) [] = (x,y)
posicao (x,y) (Norte:t) = posicao (x,y+1) t
posicao (x,y) (Sul:t) = posicao (x,y-1) t
posicao (x,y) (Oeste:t) = posicao (x-1,y) t
posicao (x,y) (Este:t) = posicao (x+1,y) t



--45--
caminho :: (Int,Int) -> (Int,Int) -> [Movimento]
caminho (x,y) (a,b) | x<a = Este : caminho (x+1,y) (a,b)
                    | x>a = Oeste : caminho (x-1,y) (a,b)
                    | y>b = Sul : caminho (x,y-1) (a,b)
                    | y<b = Norte : caminho (x,y+1) (a,b)
                    | ( x==a && y==b ) = []



--46--
vertical :: [Movimento] -> Bool
vertical [] = False
vertical [Norte] = True
vertical [Sul] = True
vertical (Norte:t) = vertical t
vertical (Sul:t) = vertical t
vertical (Oeste:t) = False
vertical (Este:t) = False



--47--
data Posicao = Pos Int Int
               deriving Show

maisCentral :: [Posicao] -> Posicao
maisCentral [Pos x y] = Pos x y
maisCentral ((Pos x y) : (Pos a b) : t) | (x^2 + y^2) < (a^2 + b^2) = maisCentral ((Pos x y) : t)
                                        | otherwise = maisCentral ((Pos a b) : t)



--48--
vizinhos :: Posicao -> [Posicao] -> [Posicao]
vizinhos _ [] = []
vizinhos (Pos x y) ((Pos a b):t) | a==(x+1) && b==y = (Pos a b): vizinhos (Pos x y) t
                                 | a==(x-1) && b==y = (Pos a b): vizinhos (Pos x y) t
                                 | a==x && b==(y-1) = (Pos a b): vizinhos (Pos x y) t
                                 | a==x && b==(y+1) = (Pos a b): vizinhos (Pos x y) t
                                 | otherwise = vizinhos (Pos x y) t



--49--
mesmaOrdenada :: [Posicao] -> Bool
mesmaOrdenada [] = False
mesmaOrdenada [x] = True
mesmaOrdenada ((Pos x y) : (Pos a b) : t) | y==b = mesmaOrdenada ((Pos x y) : t)
                                          | otherwise = False 



--50--
data Semaforo = Verde | Amarelo | Vermelho
                deriving Show

interseccaoOK :: [Semaforo] -> Bool
interseccaoOK l | (length (removeVermelho l)) < 2 = True
                | otherwise = False

--aux: recebe semaforos e guarda aqueles que nao sao vermelhos
removeVermelho :: [Semaforo] -> [Semaforo]
removeVermelho [] = []
removeVermelho (Vermelho:t) = removeVermelho t
ŕemoveVermelho (h:t) = h: removeVermelho t