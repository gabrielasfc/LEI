module Ficha7 where

data ExpInt = Const Int
            | Simetrico ExpInt
            | Mais ExpInt ExpInt
            | Menos ExpInt ExpInt
            | Mult ExpInt ExpInt deriving Show

ex1:: ExpInt
ex1 = Mais (Const 3) (Mult (Const 7) (Const 5))

--1--
--a--
calcula :: ExpInt -> Int
calcula (Const x) = x
calcula (Simetrico x) = -(calcula x)
calcula (Mais x y) = calcula x + calcula y
calcula (Menos x y) = calcula x - calcula y
calcula (Mult x y) = calcula x * calcula y


--b--
infixa :: ExpInt -> String
infixa (Const x) = show x
infixa (Simetrico x) = "- (" ++ infixa x ++ ")"
infixa (Mais x y) = "(" ++ infixa x ++ " + " ++ infixa y ++ ")"
infixa (Menos x y) = "(" ++ infixa x ++ " - " ++ infixa y ++ ")"
infixa (Mult x y) = "(" ++ infixa x ++ " * " ++ infixa y ++ ")"


--c--
posfixa :: ExpInt -> String
posfixa (Const x) = show x
posfixa (Simetrico x) = "- " ++ posfixa x
posfixa (Mais x y) = posfixa x ++ posfixa y ++ " + "
posfixa (Menos x y) = posfixa x ++ posfixa y ++ " - "
posfixa (Mult x y) = posfixa x ++ posfixa y ++ " * "



--2--
data RTree a = R a [RTree a]

rt :: RTree Int
rt = R 7 [ R 3 [ R 8 []]
         , R 4 [ R 1 [R 3 []] 
               , R 70 []
               , R 10 []
               , R 20 []
               ]
         , R 5 []
         ]

--a--
soma :: Num a => RTree a -> a
soma (R i l) = i + sum (map soma l)


--b--
altura :: RTree a -> Int
altura (R i []) = 1
altura (R i l) = 1 + maximum (map altura l)


--c--
prune :: Int -> RTree a -> RTree a
prune _ (R i []) = (R i [])
prune 0 (R i l) = (R i [])
prune x (R i l) = R i (map (prune (x-1)) l)


--d--
mirror :: (RTree a) -> (RTree a)
mirror (R i l) = R i (reverse (map mirror l))


--e--
postorder :: RTree a -> [a]
postorder (R i []) = [i]
postorder (R i l) = concat (map postorder l) ++ [i]



--3--
data BTree a = Empty | Node a (BTree a) (BTree a) 

data LTree a = Tip a | Fork (LTree a) (LTree a)

lt :: LTree Int
lt = Fork (Fork (Tip 8) 
                (Tip 9)) 
          (Fork (Tip 14)
                (Tip 12))



--a--
ltSum :: Num a => LTree a -> a
ltSum (Tip r) = r
ltSum (Fork e d) = ltSum e + ltSum d


--b--
listaLT :: LTree a -> [a]
listaLT (Tip x) = [x]
listaLT (Fork e d) = (listaLT e) ++ (listaLT d)


--c--
ltHeight :: LTree a -> Int
ltHeight (Tip x) = 0
ltHeight (Fork e d) = 1 + max (ltHeight e) (ltHeight d)


--4--
data FTree a b = Leaf b | No a (FTree a b) (FTree a b)

--a--
splitFTree :: FTree a b -> (BTree a, LTree b)
splitFTree (Leaf r) = (Empty, Tip r)
splitFTree (No r e d) = (Node r eb db , Fork el dl)
                            where (eb,el) = splitFTree e
                                  (db,dl) = splitFTree d


--b--
joinTrees :: BTree a -> LTree b -> Maybe (FTree a b)
joinTrees Empty (Tip r) = Just (Leaf r)
joinTrees _ (Fork e d) = Nothing
joinTrees (Node r eb db) (Fork el dl) =  aux (e,d)
                                           where e = (joinTrees eb el)
                                                 d = (joinTrees db dl)
                                                 aux (Just e, Just d) = Just (No r e d)
                                                 aux _ = Nothing