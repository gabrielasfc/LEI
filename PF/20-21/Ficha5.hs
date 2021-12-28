module Ficha5 where

import Data.List


--1--
--a--
any' :: (a -> Bool) -> [a] -> Bool
any' f [] = False
any' f (h:t) | f h = True
             | otherwise = any' f t


--b--
zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith' _ [] _ = []
zipWith' _ _ [] = []
zipWith' f (h1:t1) (h2:t2) = f h1 h2 : zipWith' f t1 t2


--c--
takeWhile' :: (a -> Bool) -> [a] -> [a]
takeWhile' _ [] = []
takeWhile' f (h:t) | f h = h : takeWhile' f t
                   | otherwise = []


--d--
dropWhile' :: (a -> Bool) -> [a] -> [a]
dropWhile' _ [] = []
dropWhile' f (h:t) | f h = dropWhile' f t
                   | otherwise = (h:t)


--e--
span p l = (takeWhile p l, dropWhile p l)

span' :: (a -> Bool) -> [a] -> ([a],[a])
span' f [] = ([],[])
span' f (h:t) | f h = (h:r,rs)
              | otherwise = (r,h:rs) 
                  where (r,rs) = span' f t


--f--
deleteby' :: (a -> a -> Bool) -> a -> [a] -> [a]
deleteby' _ _ [] = []
deleteby' f x (h:t) | f x h = deleteby' f x t
                    | otherwise = h : deleteby' f x t


--g--
sorton' :: Ord b => (a -> b) -> [a] -> [a]
sorton' _ [] = []
sorton' f (h:t) = insert' h (sorton' f t)
                     where insert' x [] = [x]
                           insert' x (h:t) | f x >= f h = h : insert' x t
                                           | otherwise = x:h:t



--2--
type Polinomio = [Monomio]
type Monomio = (Float, Int)

--a--
selgrau :: Int -> Polinomio -> Polinomio
selgrau g l = filter iguais l
                where iguais (x,y) = y==g


--b--
conta :: Int -> Polinomio -> Int
conta g l = length (selgrau g l)


--c--
grau :: Polinomio -> Int
grau l = undefined


--d--
deriv :: Polinomio -> Polinomio
deriv [] = []
deriv l = map derivaux l

derivaux :: Monomio -> Monomio
derivaux (h1,h2) = (h1 * fromIntegral h2,h2-1)


--e--
calcula :: Float -> Polinomio -> Float
calcula = undefined