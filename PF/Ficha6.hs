module Ficha6 where


data BTree a = Empty | Node a (BTree a) (BTree a) deriving Show

aex :: BTree Int
aex = Node 7 (Node 5 (Node 4 Empty Empty)
                     (Node 8 Empty Empty))
             (Node 3 Empty
                     (Node 1 Empty Empty))


--1--
--a--
altura :: BTree a -> Int
altura Empty = 0
altura (Node r e d) = 1 + max (altura e) (altura d)


--b--
contaNodos :: BTree a -> Int
contaNodos Empty = 0
contaNodos (Node r e d) = 1 + contaNodos e + contaNodos d


--c--
folhas :: BTree a -> Int
folhas Empty = 0
folhas (Node r Empty Empty) = 1
folhas (Node r e d) = folhas e + folhas d


--d--
prune :: Int -> BTree a -> BTree a
prune _ Empty = Empty
prune 0 (Node r e d) = Empty
prune x (Node r e d) = (Node r (prune (x-1) e) (prune (x-1) d))


--e--
path :: [Bool] -> BTree a -> [a]
path _ Empty = []
path [] (Node r e d) = [r]
path (True:t) (Node r e d) = (r:path t d)
path (False:t) (Node r e d) = (r:path t e)


--f--
mirror :: BTree a -> BTree a
mirror Empty = Empty
mirror (Node r e d) = Node r (mirror d) (mirror e)


--g--
zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c
zipWithBT _ _ Empty = Empty
zipWithBT _ Empty _ = Empty
zipWithBT f (Node r1 e1 d1) (Node r2 e2 d2) = Node (f r1 r2) newe newd
                                                   where newe = zipWithBT f e1 e2
                                                         newd = zipWithBT f d1 d2


--h--
unzipBT :: BTree (a,b,c) -> (BTree a, BTree b, BTree c)
unzipBT Empty = (Empty,Empty,Empty)
unzipBT (Node (r1,r2,r3) e d) = (Node r1 e1 d1, Node r2 e2 d2, Node r3 e3 d3)
                                    where (e1, e2, e3) = unzipBT e
                                          (d1, d2, d3) = unzipBT d



--2--
abpex :: BTree Int
abpex = Node 7 (Node 5 (Node 4 Empty Empty)
                       (Node 6 Empty Empty))
               (Node 13 Empty Empty)

abpex2 :: BTree Int
abpex2 = Node 5 Empty
                (Node 7 (Node 6 Empty Empty)
                        (Node 8 Empty Empty))

--a--
--Numa árvore binária de procura à esquerda está sempre um valor menor que o nodo e à direita um maior
minimo :: Ord a => BTree a -> a
minimo (Node r Empty _) = r
minimo (Node r e d) = minimo e


--b--
semMinimo :: Ord a => BTree a -> BTree a
semMinimo (Node r Empty d) = d
semMinimo (Node r e d) = (Node r (semMinimo e) d)


--c--
minSmin :: Ord a => BTree a -> (a,BTree a)
minSmin (Node r Empty d) = (r, d)
minSmin (Node r e d) = (minimo e, Node r (semMinimo e) d)


--d--
remove :: Ord a => a -> BTree a -> BTree a
remove = undefined



--3--
type Aluno = (Numero, Nome, Regime, Classificacao)
type Numero = Int
type Nome = String
data Regime = ORD | TE | MEL deriving Show
data Classificacao = Aprov Int | Rep | Faltou deriving Show
type Turma = BTree Aluno -- árvore binŕia de procura (ordenada por número)


turmaex :: Turma
turmaex = Node (6,"Eduardo",ORD,Aprov 12)
               (Node (5,"Corvas",TE,Rep)
                     (Node (4,"Cacao",ORD,Aprov 20) Empty Empty)
                     (Node (8,"Gabriela",TE,Aprov 16) Empty Empty))
               (Node (13,"Maria Joao",TE,Aprov 17) Empty Empty)
--a--
inscNum :: Numero -> Turma -> Bool
inscNum num Empty = False
inscNum num (Node (nr,n,reg,c) e d) | num==nr = True
                                    | num < nr = inscNum num e
                                    | num > nr = inscNum num d


--b--
inscNome :: Nome -> Turma -> Bool
inscNome _ Empty = False
inscNome name  (Node (nr,n,_,_) e d) | name==n = True
                                     | otherwise = inscNome name e || inscNome name d


--c--
trabEst :: Turma -> [(Numero,Nome)]
trabEst Empty = [] 
trabEst (Node (nr,n,TE,c) e d) = (nr,n) : (trabEst e ++ trabEst d)
trabEst (Node (ne,n,reg,c) e d) = (trabEst e ++ trabEst d)


--d--
nota :: Numero -> Turma -> Maybe Classificacao
nota _ Empty = Nothing
nota num (Node (nr,_,_,c) e d) | num==nr = Just c
                               | num < nr = nota num e
                               | otherwise = nota num d


--e--
percFaltas :: Turma -> Float
percFaltas Empty = 0
percFaltas t = (nfaltas t) / fromIntegral (contaNodos t)

nfaltas :: Turma -> Float
nfaltas Empty = 0
nfaltas (Node (n,nr,reg,Faltou) e d) = 1 + nfaltas e + nfaltas d
nfaltas (Node (n,nr,reg,c) e d) = nfaltas e + nfaltas d


--f--
mediaAprov :: Turma -> Float
mediaAprov t = (notastotal t) / aprov t

aprov :: Turma -> Float
aprov Empty = 0
aprov (Node (_,_,_,Aprov x) e d) = 1 + aprov e + aprov d
aprov (Node (_,_,_,c) e d) = aprov e + aprov d

notastotal :: Turma -> Float
notastotal Empty = 0
notastotal (Node (_,_,_,Aprov x) e d) = (fromIntegral x) + notastotal e + notastotal d
notastotal (Node (_,_,_,c) e d) = notastotal e + notastotal d


--g--
aprovAv :: Turma -> Float
aprovAv Empty = 0
aprovAv t = (aprov t) / (fromIntegral $ contaNodos t)