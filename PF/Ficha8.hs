module Ficha8 where

--1--
data Frac = F Integer Integer

--a--
normaliza :: Frac -> Frac
normaliza (F num denom) | signum num == signum denom && signum num == (-1) = (F (div ((-1)*num) c) (div ((-1)*denom) c))
                        | signum num /= signum denom && signum num == 1 = (F (div num c) (div ((-1)*denom) c))  
                        | otherwise = (F (div num c) (div denom c))
                                where c = mdc num denom 

mdc :: Integer -> Integer -> Integer
mdc x y | x==y = x
        | x<y = mdc x (y-x)
        | otherwise = mdc (x-y) x

--b--
instance Eq Frac where
    f1==f2 = num==num2 && denom==denom2
                where (F num denom) = normaliza f1
                      (F num2 denom2) = normaliza f2

--c--
instance Ord Frac where
    compare (F num1 denom1) (F num2 denom2) | (fromIntegral num1 / fromIntegral denom1) == (fromIntegral num2 / fromIntegral denom2) = EQ
                                            | (fromIntegral num1 / fromIntegral denom1) < (fromIntegral num2 / fromIntegral denom2) = LT
                                            | otherwise = GT

--d--
instance Show Frac where
    show (F num denom) = show num ++ "/" ++ show denom

--e--
somaFrac :: Frac -> Frac -> Frac
somaFrac (F num1 denom1) (F num2 denom2) | denom1 == denom2 = normaliza $ (F (num1+num2) denom1)
                                         | otherwise = normaliza $ somaFrac (F (num1*denom2) (denom1*denom2)) (F (num2*denom1) (denom1*denom2))

subtraiFrac :: Frac -> Frac -> Frac
subtraiFrac (F num1 denom1) (F num2 denom2) | denom1 == denom2 = normaliza $ (F (num1-num2) denom1)
                                            | otherwise = normaliza $ subtraiFrac (F (num1*denom2) (denom1*denom2)) (F (num2*denom1) (denom1*denom2))

multFrac :: Frac -> Frac -> Frac
multFrac (F num1 denom1) (F num2 denom2) = normaliza $ (F (num1*num2) (denom1*denom2))

negateFrac :: Frac -> Frac
negateFrac (F num denom) = (F ((-1)*num) denom)

absFrac :: Frac -> Frac
absFrac (F num denom) = (F (abs num) (abs denom))

sinalFrac :: Frac -> Frac
sinalFrac (F num denom) | signum num == signum denom = (F 1 1)
                        | otherwise = (F (-1) 1)

fromIntegerFrac :: Integer -> Frac
fromIntegerFrac x = (F x 1)

instance Num Frac where
    (+) = somaFrac
    (*) = somaFrac
    (-) = subtraiFrac
    negate = negateFrac
    abs = absFrac
    signum = sinalFrac
    fromInteger = fromIntegerFrac

--f--
select :: Frac -> [Frac] -> [Frac]
select _ [] = []
select f (h:t) | h > 2*f = h : select f t
               | otherwise = select f t


--2--
data Exp a = Const a
           | Simetrico (Exp a)
           | Mais (Exp a) (Exp a)
           | Menos (Exp a) (Exp a)
           | Mult (Exp a) (Exp a)

--a--
showExp :: Show a => Exp a -> String
showExp (Const x) = show x
showExp (Simetrico x) = "-(" ++ showExp x ++ ")"
showExp (Mais x y) = "(" ++ showExp x ++ " + " ++ showExp y ++ ")"
showExp (Menos x y) = "(" ++ showExp x ++ " - " ++ showExp y ++ ")"
showExp (Mult x y) = "(" ++ showExp x ++ " * " ++ showExp y ++ ")"

instance Show a => Show (Exp a) where
    show = showExp

--b--
calcula :: Num a => Exp a -> a
calcula (Const x) = x
calcula (Simetrico x) = (-1) * calcula x
calcula (Mais x y) = calcula x + calcula y
calcula (Menos x y) = calcula x - calcula y
calcula (Mult x y) = calcula x * calcula y

instance (Num a, Eq a) => Eq (Exp a) where
    x == y = calcula x == calcula y

--c--
somaExp :: Num a => Exp a -> Exp a -> Exp a
somaExp x y = Const (calcula x + calcula y)

multExp :: Num a => Exp a -> Exp a -> Exp a
multExp x y = Const (calcula x * calcula y)

subtraiExp :: Num a => Exp a -> Exp a -> Exp a
subtraiExp x y = Const (calcula x - calcula y)

negateExp :: Num a => Exp a -> Exp a
negateExp x = Const ((-1) * (calcula x))

absExp :: Num a => Exp a -> Exp a
absExp x = Const (abs $ calcula x)

signumExp :: Num a => Exp a -> Exp a
signumExp x = Const (signum $ calcula x)

fromIntegerExp :: Num a => Integer -> Exp a
fromIntegerExp x = Const (fromInteger x)

instance Num a => Num (Exp a) where
    (+) = somaExp
    (*) = multExp
    (-) = subtraiExp
    negate = negateExp
    abs = absExp
    signum = signumExp
    fromInteger = fromIntegerExp


--3--
data Movimento = Credito Float | Debito Float
data Data = D Int Int Int
data Extracto = Ext Float [(Data, String, Movimento)]

--a--
instance Eq Data where
    (D a1 m1 d1) == (D a2 m2 d2) = a1==a2 && m2==m1 && d1==d2

instance Ord Data where
    compare (D a1 m1 d1) (D a2 m2 d2) | a1<a2 || (a1==a2 && m1<m2) || (a1==a2 && m1==m2 && d1<d2) = LT
                                      | a1==a2 && m1==m2 && d1==d2 = EQ
                                      | otherwise = GT

--b--
instance Show Data where
    show (D a m d) = show a ++ "/" ++ show m ++ "/" ++ show d

--c--
extEx = Ext 300 [(D 2010 4 5,"DEPOSITO",Credito 2000)
                ,(D 2010 8 10,"COMPRA",Debito 37.5)
                ,(D 2010 9 1,"LEV",Debito 60)
                ,(D 2011 1 7,"JUROS",Credito 100)
                ,(D 2011 1 22,"ANUIDADE",Debito 8)]

ordena :: Extracto -> Extracto
ordena (Ext s m) = Ext s (mySortOn (\(d,s,m) -> d) m)

mySortOn :: Ord b => (a -> b) -> [a] -> [a]
mySortOn _ [] = []
mySortOn _ [x] = [x]
mySortOn f (h:t) | f h < minimum (map f t) = h : mySortOn f t
                 | otherwise = mySortOn f (t ++ [h])

--d--
convertToStr :: (Data, String, Movimento) -> String
convertToStr (d,s,Credito v) = show d ++ replicate (11 - length (show d)) ' ' ++ s ++ replicate (12 - length s) ' ' ++ show v ++ "\n"
convertToStr (d,s,Debito v) = show d ++ replicate (11 - length (show d)) ' ' ++ s ++ replicate (22 - length s) ' ' ++ show v ++ "\n"

--calcula o dinheiro perdido/ganho com os movimentos
movimentos :: Extracto -> Float
movimentos (Ext s []) = 0
movimentos (Ext s ((d, info, Credito v):t)) = v + movimentos (Ext s t)
movimentos (Ext s ((d, info, Debito v):t)) = -v + movimentos (Ext s t)

instance Show Extracto where
    show ext = "Saldo anterior: " ++ show s ++ "\n" ++
               "---------------------------------------\n" ++
               "Data       Descricao   Credito   Debito\n" ++
               "---------------------------------------\n" ++
               concat (map convertToStr mov) ++
               "---------------------------------------\n" ++
               "Saldo Atual: " ++ show (movimentos (Ext s mov) + s)
                            where (Ext s mov) = ordena ext