module Ficha7 where

--1--
data ExpInt = Const Int
            | Simetrico ExpInt
            | Mais ExpInt ExpInt
            | Menos ExpInt ExpInt
            | Mult ExpInt ExpInt

--a--
calcula :: ExpInt -> Int
calcula (Const x) = x
calcula (Simetrico x) = (-1) * calcula x
calcula (Mais x y) = calcula x + calcula y
calcula (Menos x y) = calcula x - calcula y
calcula (Mult x y) = calcula x * calcula y

--b--
infixa :: ExpInt -> String
infixa (Const x) = show x
infixa (Simetrico x) = "-(" ++ infixa x ++ ")"
infixa (Mais x y) = "(" ++ infixa x ++ " + " ++ infixa y ++ ")"
infixa (Menos x y) = "(" ++ infixa x ++ " - " ++ infixa y ++ ")"
infixa (Mult x y) = "(" ++ infixa x ++ " * " ++ infixa y ++ ")"

--c--
posfixa :: ExpInt -> String
posfixa (Const x) = " " ++ show x
posfixa (Simetrico x) = posfixa x ++ " *(-1)"
posfixa (Mais x y) = posfixa x ++ posfixa y ++ " +"
posfixa (Menos x y) = posfixa x ++ posfixa y ++ " -"
posfixa (Mult x y) = posfixa x ++ posfixa y ++ " *"


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
soma (R r l) = r + sum (map soma l)

--b--
altura :: RTree a -> Int
altura (R _ []) = 1
altura (R r l) = 1 + maximum (map altura l)

--c--
prune :: Int -> RTree a -> RTree a
prune _ (R r []) = (R r [])
prune 0 (R r _) = (R r [])
prune n (R r l) = (R r (map (prune (n-1)) l))

--d--
mirror :: RTree a -> RTree a
mirror (R r l) = (R r (reverse (map mirror l)))

--e--
postorder :: RTree a -> [a]
postorder (R r []) = [r]
postorder (R r l) = concat (map postorder l) ++ [r]


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
listaLT (Tip r) = [r]
listaLT (Fork e d) = listaLT e ++ listaLT d

--c--
ltHeight :: LTree a -> Int
ltHeight (Tip r) = 1
ltHeight (Fork e d) = 1 + max (ltHeight e) (ltHeight d)


--4--
data FTree a b = Leaf b | No a (FTree a b) (FTree a b)

--a--
splitFTree :: FTree a b -> (BTree a, LTree b)
splitFTree (Leaf r) = (Empty, Tip r)
splitFTree (No r e d) = (Node r bt_e bt_d, Fork lt_e lt_d)
                                where (bt_e, lt_e) = splitFTree e
                                      (bt_d, lt_d) = splitFTree d

--b--
joinTrees :: BTree a -> LTree b -> Maybe (FTree a b)
joinTrees Empty (Tip r) = Just (Leaf r)
joinTrees (Node r bt_e bt_d) (Fork lt_e lt_d) = aux (new_e, new_d)
                                                    where new_e = joinTrees bt_e lt_e
                                                          new_d = joinTrees bt_d lt_d
                                                          aux (Just new_e, Just new_d) = Just (No r new_e new_d)
                                                          aux _ = Nothing