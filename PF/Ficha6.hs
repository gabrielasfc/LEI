module Ficha6 where

data BTree a = Empty 
             | Node a (BTree a) (BTree a)
             deriving Show

treeEx :: BTree Int
treeEx = Node 7 (Node 5 (Node 4 Empty Empty)
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
prune 0 (Node _ _ _) = Empty
prune nvl (Node r e d) = (Node r (prune (nvl-1) e) (prune (nvl-1) d))

--e--
path :: [Bool] -> BTree a -> [a]
path _ Empty = []
path [] (Node r e d) = [r]
path (True:t) (Node r e d) = r : path t d
path (False:t) (Node r e d) = r : path t e

--f--
mirror :: BTree a -> BTree a
mirror Empty = Empty
mirror (Node r e d) = Node r (mirror d) (mirror e)

--g--
zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c
zipWithBT _ _ Empty = Empty
zipWithBT _ Empty _ = Empty
zipWithBT f (Node r1 e1 d1) (Node r2 e2 d2) = Node (f r1 r2) new_esq new_dir
                                                    where new_esq = zipWithBT f e1 e2
                                                          new_dir = zipWithBT f d1 d2

--h--
unzipBT :: BTree (a,b,c) -> (BTree a, BTree b, BTree c)
unzipBT Empty = (Empty,Empty,Empty)
unzipBT (Node (r1,r2,r3) e d) = (Node r1 e1 d1, Node r2 e2 d2, Node r3 e3 d3)
                                    where (e1, e2, e3) = unzipBT e
                                          (d1, d2, d3) = unzipBT d


--2--
--a--
minimo :: Ord a => BTree a -> a
minimo (Node r Empty _) = r
minimo (Node r e d) = minimo e

--b--
semMinimo :: Ord a => BTree a -> BTree a
semMinimo (Node r Empty d) = d
semMinimo (Node r e d) = Node r (semMinimo e) d

--c--
minSmin :: Ord a => BTree a -> (a, BTree a)
minSmin (Node r Empty d) = (r,d)
minSmin (Node r e d) = (minimo e, Node r (semMinimo e) d)

--d--
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
                              --passamos o menor elemento da direita para a raíz
                              --e o lado direito é atualizado (removendo esse mínimo)


--3--
type Aluno = (Numero,Nome,Regime,Classificacao)
type Numero = Int
type Nome = String
data Regime = ORD | TE | MEL deriving Show
data Classificacao = Aprov Int | Rep | Faltou deriving Show
type Turma = BTree Aluno -- árvore binária de procura (ordenada por número)

turmaEx :: Turma
turmaEx = Node (8,"Gabs",MEL,Aprov 16)
               (Node (5,"Corvas",TE,Rep)
                     (Node (4,"Cacao",ORD,Aprov 20) Empty Empty)
                     (Node (6,"Edu",ORD,Aprov 12) Empty Empty))
               (Node (13,"Ze",TE,Faltou)
                     (Node (9,"Rike",ORD,Faltou) Empty Empty)
                     (Node (17,"Jo",ORD,Aprov 17) Empty Empty))


--a--
inscNum :: Numero -> Turma -> Bool
inscNum _ Empty = False
inscNum n (Node (num,_,_,_) e d) | n==num = True
                                 | n<num = inscNum n e
                                 | otherwise = inscNum n d

--b--
inscNome :: Nome -> Turma -> Bool
inscNome _ Empty = False
inscNome n (Node (_,nome,_,_) e d) | n==nome = True
                                   | otherwise = inscNome n e || inscNome n d

--c--
trabEst :: Turma -> [(Numero,Nome)]
trabEst Empty = []
trabEst (Node (num,nome,TE,_) e d) = trabEst e ++ [(num,nome)] ++ trabEst d
trabEst (Node _ e d) = trabEst e ++ trabEst d

--d--
nota :: Numero -> Turma -> Maybe Classificacao
nota _ Empty = Nothing
nota n (Node (num,_,_,c) e d) | n==num = Just c
                              | n<num = nota n e
                              | otherwise = nota n d

--e--
percFaltas :: Turma -> Float
percFaltas Empty = 0
percFaltas t = 100 * (contaFaltas t / fromIntegral (contaNodos t))

contaFaltas :: Turma -> Float
contaFaltas Empty = 0
contaFaltas (Node (_,_,_,Faltou) e d) = 1 + contaFaltas e + contaFaltas d
contaFaltas (Node _ e d) = contaFaltas e + contaFaltas d

--f--
mediaAprov :: Turma -> Float
mediaAprov Empty = 0
mediaAprov t = notasTotal t / contaAprovados t

notasTotal :: Turma -> Float
notasTotal Empty = 0
notasTotal (Node (_,_,_,Aprov nota) e d) = (fromIntegral nota) + notasTotal e + notasTotal d
notasTotal (Node _ e d) = notasTotal e + notasTotal d

contaAprovados :: Turma -> Float
contaAprovados Empty = 0
contaAprovados (Node (_,_,_,Aprov _) e d) = 1 + contaAprovados e + contaAprovados d
contaAprovados (Node _ e d) = contaAprovados e + contaAprovados d

--g--
aprovAv :: Turma -> Float
aprovAv Empty = 0
aprovAv t = 100 * (numAprov / numAv)
                  where (numAprov, numAv) = conta t

--devolve nr de aprovados na 1ª componente e nr de avaliados na 2ª
--se faltar não é avaliado
conta :: Turma -> (Float,Float)
conta Empty = (0,0)
conta (Node (_,_,_,Aprov n) e d) =  (1 + fst(conta e) + fst(conta d) , 1 + snd(conta e) + snd(conta d))
conta (Node (_,_,_,Rep) e d) = (fst(conta e) + fst(conta d) , 1 + snd(conta e) + snd(conta d))
conta (Node _ e d) = (fst(conta e) + fst(conta d) , snd(conta e) + snd(conta d))