module Ficha8 where


--1--
data Frac = F Integer Integer

--a--
normaliza :: Frac -> Frac
normaliza (F x y) = F a b 
                      where n = mdc x y
                            a = s * (div (abs x) n)
                            b = (div (abs y) n)
                            s = if (x*y)>0 then 1 
                                           else (-1)

mdc :: Integer -> Integer -> Integer
mdc x y | x==y = x
        | x<y = mdc x (y-x)
        | otherwise = mdc (x-y) x


--b--
instance Eq Frac where
    (==) (F x y) (F a b) = (x*b) == (y*a)


--c--
instance Ord Frac where
    (<=) (F x y) (F a b) = (x*b) <= (y*a)


--d--
instance Show Frac where
    show (F x y) = (show x) ++ "/" ++ (show y)


--e--
instance Num Frac where
     (+) (F x y) (F a b) = normaliza (F (x*b + y*a) (y*b))
     (-) (F x y) (F a b) = normaliza (F (x*b - y*a) (y*b))
     (*) (F x y) (F a b) = normaliza (F (x*a) (y*b))
     negate (F x y) = (F (-x) y)
     abs (F x y) = (F (abs x) (abs y))
     fromInteger x = (F x 1)
     signum (F x y) | (x>0 && y>0) || (x<0 && y<0) = 1
                    | x==0 = 0
                    | otherwise = -1


--f--
maiordobro :: Frac -> [Frac] -> [Frac]
maiordobro _ [] = []
maiordobro f l = filter (>2*f) l



--2--
data Exp a = Const a
           | Simetrico (Exp a)
           | Mais (Exp a) (Exp a)
           | Menos (Exp a) (Exp a)
           | Mult (Exp a) (Exp a)

calcula :: (Eq a, Num a) => Exp a -> a
calcula (Const i) = i
calcula (Simetrico e) = (-1) * (calcula e)
calcula (Mais e1 e2) = calcula e1 + calcula e2
calcula (Menos e1 e2) = calcula e1 - calcula e2
calcula (Mult e1 e2) = calcula e1 * calcula e2

--a--
instance (Show a) => Show (Exp a) where
    show e = infixa e

infixa :: (Show a) => Exp a -> String
infixa (Const i) = show i
infixa (Simetrico e) = "(- " ++ infixa e ++ ")"
infixa (Mais e d) = "(" ++ infixa e ++ " + " ++ infixa d ++ ")"
infixa (Menos e d) = "(" ++ infixa e ++ " - " ++ infixa d ++ ")"
infixa (Mult e d) = "(" ++ infixa e ++ " * " ++ infixa d ++ ")"


--b--
instance (Eq a,Num a) => Eq (Exp a) where
    (==) e1 e2 = (calcula e1) == (calcula e2)


--c--
instance (Num a, Eq a) => Num (Exp a) where
    (+) e1 e2 = Const (calcula e1 + calcula e2)
    (-) e1 e2 = Const (calcula e1 - calcula e2)
    (*) e1 e2 = Const (calcula e1 * calcula e2)
    negate e = Const (calcula (Simetrico e))
    abs e = Const (abs (calcula e))
    signum e = Const (signum (calcula e))
    fromInteger x = Const (fromInteger x)



--3--
data Movimento = Credito Float | Debito Float
data Dat = D Int Int Int
data Extracto = Ext Float [(Dat, String, Movimento)]

--a--
instance Ord Dat where
    (<=)(D d1 m1 a1) (D d2 m2 a2) = (d1,m1,a1) <= (d2,m2,a2)


--b--
instance Show Dat where
    show (D d m a) = show d ++ "/" ++ show m ++ "/" ++ show a

instance Eq Dat where
    (==) (D d1 m1 a1) (D d2 m2 a2) = (d1,m1,a1) == (d2,m2,a2)


--c--
ordena :: Extracto -> Extracto
ordena (Ext s m) = Ext s (sorton' (\(d,s,m) -> d) m)

sorton' :: Ord b => (a -> b) -> [a] -> [a]
sorton' _ [] = []
sorton' f (h:t) = insert' h (sorton' f t)
                     where insert' x [] = [x]
                           insert' x (h:t) | f x >= f h = h : insert' x t
                                           | otherwise = x:h:t


--d--
instance Show Movimento where
    show (Credito x) = show x
    show (Debito x) = show x

instance Eq Movimento where
    (==) (Credito x) (Credito y) = x==y
    (==) (Debito x) (Debito y) = x==y

instance Show Extracto where
    show (Ext s m) = undefined