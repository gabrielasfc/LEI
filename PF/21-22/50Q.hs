module Q50 where

--1--
myenumFromTo :: Int -> Int -> [Int]
myenumFromTo a b | a < b = a : myenumFromTo (a+1) b
                 | a == b = [a]
                 | otherwise = a : myenumFromTo (a-1) b


--2--
myenumFromThenTo :: Int -> Int -> Int -> [Int]
myenumFromThenTo a b c | a < c = crescente a b c
                       | a > c = decrescente a b c
                       | otherwise = [a]

crescente :: Int -> Int -> Int -> [Int]
crescente a b c | a <= c = a : crescente (a+b) b c
                | otherwise = []

decrescente :: Int -> Int -> Int -> [Int]
decrescente a b c | a >= c = a : decrescente (a-b) b c
                  | otherwise = []


--3--
concatena :: [a] -> [a] -> [a]
concatena [] l = l
concatena (h:t) l = h : concatena t l


--4--
elem_pos :: [a] -> Int -> a
elem_pos (h:t) 0 = h
elem_pos (h:t) x = elem_pos t (x-1)


--5--
myreverse :: [a] -> [a]
myreverse [] = []
myreverse (h:t) = myreverse t ++ [h]


--6--
mytake :: Int -> [a] -> [a]
mytake _ [] = []
mytake 0 _ = []
mytake x (h:t) = h : mytake (x-1) t


--7--
mydrop :: Int -> [a] -> [a]
mydrop _ [] = []
mydrop 0 l = l
mydrop x (h:t) = mydrop (x-1) t


--8--
myzip :: [a] -> [b] -> [(a,b)]
myzip [] _ = []
myzip _ [] = []
myzip (x:xs) (y:ys) = (x,y) : myzip xs ys


--9--
myreplicate :: Int -> a -> [a]
myreplicate 0 _ = []
myreplicate x n = n : replicate (x-1) n


--10--
myintersperse :: a -> [a] -> [a]
myintersperse _ [] = []
myintersperse _ [x] = [x]
myintersperse x (h:t) = h : x : myintersperse x t


--11--
mygroup :: Eq a => [a] -> [[a]]
mygroup [] = []
mygroup l = agrupaiguais l : mygroup resto
                    where resto = mydrop (mylength $ agrupaiguais l) l --tira os elementos que já agrupamos
                    
--devolve uma lista com a head e os elementos seguidos iguais
--fazemos para os 1os elementos e depois sempre para a head do resto (resto vai sempre dando update)
agrupaiguais :: Eq a => [a] -> [a]
agrupaiguais [x] = [x]
agrupaiguais (h:a:t) | h == a = h : agrupaiguais (a:t)
                     | otherwise = [h]

mylength :: [a] -> Int
mylength [] = 0
mylength (h:t) = 1 + mylength t


--12--
myconcat :: [[a]] -> [a]
myconcat [] = []
myconcat (h:t) = h ++ concat t


--13--
myinits :: [a] -> [[a]]
myinits [] = []
myinits [x] = [[],[x]]
myinits l = (myinits (myinit l)) ++ [l]

myinit :: [a] -> [a]
myinit [] = []
myinit [x] = []
myinit (h:t) = h : myinit t


--14--
mytails :: [a] -> [[a]]
mytails [] = []
mytails [x] = [[x],[]]
mytails (h:t) = (h:t) : mytails t


--15--
heads :: [[a]] -> [a]
heads [] = []
heads ([]:t) = heads t
heads (h:t) = (myhead h) : heads t

myhead :: [a] -> a
myhead (h:t) = h


--16--
total :: [[a]] -> Int
total [] = 0
total (h:t) = mylength h + total t


--17--
fun :: [(a,b,c)] -> [(a,c)]
fun [] = []
fun ((a,_,c):t) = (a,c) : fun t


--18--
cola :: [(String,b,c)] -> String
cola [] = []
cola ((s,b,c):t) = s ++ cola t


--19--
idade :: Int -> Int -> [(String,Int)] -> [String]
idade _ _ [] = []
idade ano_atual i ((s,nasc):t) | ano_atual - nasc >= i = s : idade ano_atual i t
                               | otherwise = idade ano_atual i t


--20--
powerEnumFrom :: Int -> Int -> [Int]
powerEnumFrom _ 1 = [1]
powerEnumFrom x e | e > 1 = (powerEnumFrom x (e-1)) ++ [x^(e-1)]
                  | otherwise = []


--21--
isPrime :: Int -> Bool
isPrime x | x >= 2 = prime x 2
          | otherwise = False

prime :: Int -> Int -> Bool
prime n m | m * m > n = True
          | mod n m == 0 = False
          | otherwise = prime n (m+1)


--22--
myisPrefixOf :: Eq a => [a] -> [a] -> Bool
myisPrefixOf [] [] = True
myisPrefixOf [] _ = True
myisPrefixOf _ [] = False
myisPrefixOf (x:xs) (y:ys) = (x == y) && (myisPrefixOf xs ys)


--23--
myisSuffixOf :: Eq a => [a] -> [a] -> Bool
myisSuffixOf [] [] = True
myisSuffixOf [] _ = True
myisSuffixOf _ [] = False
myisSuffixOf l (h:t) | l == (h:t) = True
                     | otherwise = myisSuffixOf l t


--24--
myisSubsequenceOf :: Eq a => [a] -> [a] -> Bool
myisSubsequenceOf [] [] = True
myisSubsequenceOf [] _ = True
myisSubsequenceOf _ [] = False
myisSubsequenceOf (x:xs) (y:ys) | x == y = myisSubsequenceOf xs ys
                                | otherwise = myisSubsequenceOf (x:xs) ys


--25--
myelemIndices :: Eq a => a -> [a] -> [Int]
myelemIndices _ [] = []
myelemIndices x (h:t) = aux25 0 x (h:t)

--precisamos de um contador das posições para as meter na lista final
aux25 :: Eq a => Int -> a -> [a] -> [Int]
aux25 _ _ [] = []
aux25 pos x (h:t) | x == h = pos : (aux25 (pos+1) x t)
                  | otherwise = aux25 (pos+1) x t


--26--
mynub :: Eq a => [a] -> [a]
mynub [] = []
mynub l = colocanaorepetidos l []

--pega na lista e coloca os elementos não repetidos numa nova lista
colocanaorepetidos :: Eq a => [a] -> [a] -> [a]
colocanaorepetidos [] l  = l
colocanaorepetidos (h:t) l | myelem h l = colocanaorepetidos t l
                           | otherwise = colocanaorepetidos t (l++[h])

myelem :: Eq a => a -> [a] -> Bool
myelem _ [] = False
myelem x (h:t) | x == h = True
               | otherwise = myelem x t


--27--
mydelete :: Eq a => a -> [a] -> [a]
mydelete _ [] = []
mydelete x (h:t) | x == h = t
                 | otherwise = h : mydelete x t


--28--
delete_lists :: Eq a => [a] -> [a] -> [a]
delete_lists l [] = l
delete_lists [] _ = []
delete_lists (x:xs) (y:ys) | myelem y (x:xs) = delete_lists xs ys
                           | otherwise = x : delete_lists xs (y:ys)


--29--
myunion :: Eq a => [a] -> [a] -> [a]
myunion l [] = l
myunion [] l = l
myunion l (h:t) | myelem h l = myunion l t
                | otherwise = myunion (l++[h]) t


--30--
myintersect :: Eq a => [a] -> [a] -> [a]
myintersect [] _ = []
myintersect _ [] = []
myintersect (x:xs) (y:ys) | myelem x (y:ys) = x : myintersect xs (y:ys)
                          | otherwise = myintersect xs (y:ys)


--31--
myinsert :: Ord a => a -> [a] -> [a]
myinsert x [] = [x]
myinsert x (h:t) | x < h = x:h:t
                 | otherwise = h : myinsert x t


--32--
myunwords :: [String] -> String
myunwords [] = []
myunwords [s] = s
myunwords (h:t) = h ++ " " ++ myunwords t


--33--
myunlines :: [String] -> String
myunlines [] = []
myunlines [s] = s ++ "\n"
myunlines (h:t) = h ++ "\n" ++ myunlines t


--34--
pMaior :: Ord a => [a] -> Int
pMaior l = aux34 l 0

--contar posição
aux34 :: Ord a => [a] -> Int -> Int
aux34 (h:t) pos | h == maximo(h:t) = pos
                | otherwise = aux34 t (pos+1) 

maximo :: Ord a => [a] -> a
maximo [x] = x
maximo (h:a:t) | h > a = maximo (h:t)
               | otherwise = maximo (a:t)


--35--
mylookup :: Eq a => a -> [(a,b)] -> Maybe b
mylookup _ [] = Nothing
mylookup x ((a,b):t) | x == a = Just b
                     | otherwise = mylookup x t


--36--
preCrescente :: Ord a => [a] -> [a]
preCrescente [] = []
preCrescente [x] = [x]
preCrescente (h:a:t) | h > a = [h]
                     | otherwise = h : preCrescente (a:t)


--37--
iSort :: Ord a => [a] -> [a]
iSort [] = []
iSort [x] = [x]
iSort (h:t) = myinsert h (iSort t)


--38--
menor :: String -> String -> Bool
menor [] [] = False
menor [] _ = True
menor _ [] = False
menor (x:xs) (y:ys) | mylength (x:xs) < mylength (y:ys) = True
                    | (x:xs) == (y:ys) = False
                    | mylength (x:xs) == mylength (y:ys) = aux38 (x:xs) (y:ys)
                    | otherwise = False

--ver pela ordem do alfabeto caso tenham o mesmo comprimento
aux38 :: String -> String -> Bool
aux38 [] [] = True
aux38 (x:xs) (y:ys) | x <= y = aux38 xs ys
                    | otherwise = False


--39--
elemMSet :: Eq a => a -> [(a,Int)] -> Bool
elemMSet _ [] = False
elemMSet x ((a,b):t) | x == a = True
                     | otherwise = elemMSet x t


--40--
converteMSet :: [(a,Int)] -> [a]
converteMSet [] = []
converteMSet ((a,b):t) = (myreplicate b a) ++ converteMSet t


--41--
insereMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
insereMSet x [] = [(x,1)]
insereMSet x ((a,b):t) | x == a = (a,b+1) : t
                       | otherwise = (a,b) : insereMSet x t


--42--
removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet _ [] = []
removeMSet x ((a,b):t) | (x == a) && (b == 1) = t
                       | x == a = (a,b-1) : t
                       | otherwise = (a,b) : removeMSet x t


--43--
constroiMSet :: Ord a => [a] -> [(a,Int)]
constroiMSet [] = []
constroiMSet (h:t) = (h, 1 + mylength(filter (==h) t)) : constroiMSet (filter (/=h) t)


--44--
partitionEithers :: [Either a b] -> ([a],[b])
partitionEithers [] = ([],[])
partitionEithers l = (lefts l, rights l)

lefts :: [Either a b] -> [a]
lefts [] = []
lefts ((Left a):t) = a : lefts t
lefts ((Right b):t) = lefts t

rights :: [Either a b] -> [b]
rights [] = []
rights ((Left a):t) = rights t
rights ((Right b):t) = b : rights t


--45--
catMaybes :: [Maybe a] -> [a]
catMaybes [] = []
catMaybes ((Just a):t) = a : catMaybes t
catMaybes (Nothing:t) = catMaybes t


--46--
data Movimento = Norte | Sul | Este | Oeste
               deriving Show

caminho :: (Int,Int) -> (Int,Int) -> [Movimento]
caminho (x,y) (a,b) | x < a = Este : caminho (x+1,y) (a,b)
                    | x > a = Oeste : caminho (x-1,y) (a,b)
                    | y > b = Sul : caminho (x,y-1) (a,b)
                    | y < b = Norte : caminho (x,y+1) (a,b)
                    | (x == a) && (y == b) = []


--47--
hasLoops :: (Int,Int) -> [Movimento] -> Bool
hasLoops (x,y) [] = False
hasLoops (x,y) m | (x == a) && (y == b) = True
                 | otherwise = hasLoops (x,y) (myinit m)
                        where (a,b) = posicao (x,y) m

posicao :: (Int,Int) -> [Movimento] -> (Int,Int)
posicao (x,y) [] = (x,y)
posicao (x,y) (Este:t) = posicao (x+1,y) t
posicao (x,y) (Oeste:t) = posicao (x-1,y) t
posicao (x,y) (Sul:t) = posicao (x,y-1) t
posicao (x,y) (Norte:t) = posicao (x,y+1) t


--48--
type Ponto = (Float,Float)
data Rectangulo = Rect Ponto Ponto

contaQuadrados :: [Rectangulo] -> Int
contaQuadrados [] = 0
contaQuadrados (h:t) | isQuadrado h = 1 + contaQuadrados t
                     | otherwise = contaQuadrados t

isQuadrado :: Rectangulo -> Bool
isQuadrado (Rect (x,y) (a,b)) = abs(x-a) == abs(y-b)


--49--
areaTotal :: [Rectangulo] -> Float
areaTotal [] = 0
areaTotal (h:t) = areaRect h + areaTotal t

areaRect :: Rectangulo -> Float
areaRect (Rect (x,y) (a,b)) = abs(x-a) * abs(y-b)


--50--
data Equipamento = Bom | Razoavel | Avariado
                 deriving Show

naoReparar :: [Equipamento] -> Int
naoReparar [] = 0
naoReparar (Bom:t) = 1 + naoReparar t
naoReparar (Razoavel:t) = 1 + naoReparar t
naoReparar (Avariado:t) = naoReparar t