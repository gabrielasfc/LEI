module Ficha1 where

import Data.Char 



--1--
--a--
perimetro :: Float -> Float 
perimetro r = 2 * pi * r


--b--
dist :: (Double,Double) -> (Double,Double) -> Double
dist (x,y) (a,b) = sqrt ((x-a)^2 + (y-b)^2)


--c--
primUlt :: [a] -> (a,a)
primUlt l = (head l,last l)


--d--
multiplo :: Int -> Int -> Bool
multiplo m n = mod m n == 0


--e--
truncaImpar :: [a] -> [a]
truncaImpar (h:t) | odd (length (h:t)) = t
                  | otherwise = h:t


--f--
max2 :: Int -> Int -> Int
max2 a b | a>b = a
         | otherwise = b


--g--
max3 :: Int -> Int -> Int -> Int
max3 a b c | a>b || c>b = max2 a c
           | a>c || b>c = max2 a b
           | otherwise = max2 b c



--2--
--a--
nRaizes :: Float -> Float -> Float -> Float
nRaizes a b c | delta == 0 = 1
              | delta < 0 = 0
              | otherwise = 2
                 where delta = b^2 - 4*a*c


--b--
raizes :: Float -> Float -> Float -> [Float]
raizes a b c | nRaizes a b c == 1 = [-b/(2*a)]
             | nRaizes a b c == 2 = [ (-b-sqrt (delta)) / 2*a , (-b + sqrt (delta)) / 2*a]
             | otherwise = []
                 where delta = b^2 - 4*a*c



--3--
type Hora = (Int,Int)

--a--
testaHora :: Hora -> Bool
testaHora (h,m) = h>=0 && h<24 && m>=0 && m<60


--b--
comparaHora :: Hora -> Hora -> Bool
comparaHora (h1,m1) (h2,m2) | h1==h2 && m1>m2 = True
                            | h1>h2 = True
                            | otherwise = False


--c--
converteParaMin :: Hora -> Int
converteParaMin (h1,m1) = 60*h1 + m1


--d--
converteParaHora :: Int -> Hora
converteParaHora m = (div m 60,mod m 60)


--e--
diferencaHoras :: Hora -> Hora -> Int
diferencaHoras (h1,m1) (h2,m2) = abs $ converteParaMin (h2-h1,m2-m1)


--f--
addMin :: Hora -> Int -> Hora
addMin (h1,m1) m = converteParaHora $ (converteParaMin (h1,m1)) + m



--4--
data Hora2 = H Int Int deriving (Show,Eq)

--a--
testaHora2 :: Hora2 -> Bool
testaHora2 (H h m) = h>0 && h<24 && m>=0 && m<60


--b--
comparaHora2 :: Hora2 -> Hora2 -> Bool
comparaHora2 (H h1 m1) (H h2 m2) | h1==h2 && m1>m2 = True
                                 | h1>h2 = True
                                 | otherwise = False


--c--
converteParaMin2 :: Hora2 -> Int
converteParaMin2 (H h m) = 60*h + m


--d--
converteParaHora2 :: Int -> Hora2
converteParaHora2 m = H (div m 60) (mod m 60)


--e--
diferencaHoras2 :: Hora2 -> Hora2 -> Int
diferencaHoras2  (H h1 m1) (H h2 m2) = abs $ converteParaMin2 (H (h2-h1) (m2-m1))


--f--
addMin2 :: Hora2 -> Int -> Hora2
addMin2 (H h1 m1) m = converteParaHora2 $ (converteParaMin2 (H h1 m1)) + m



--5--
data Semaforo = Verde | Amarelo | Vermelho deriving (Show,Eq)

--a--
next :: Semaforo -> Semaforo
next Verde = Amarelo
next Amarelo = Vermelho
next Vermelho = Verde


--b--
stop :: Semaforo -> Bool
stop s | s==Verde = False
       | otherwise = True


--c--
safe :: Semaforo -> Semaforo -> Bool
safe s1 s2 = s1==Vermelho || s2==Vermelho



--6--
data Ponto = Cartesiano Double Double | Polar Double Double deriving (Show,Eq)

--a--
posx :: Ponto -> Double
posx (Cartesiano x y) = abs x
posx (Polar d a) = abs (cos a * d)


--b--
posy (Cartesiano x y) = abs y
posy (Polar d a) = abs (sin a * d)


--c--
raio :: Ponto -> Double
raio (Cartesiano x y) = sqrt (x^2 + y^2)
raio (Polar d a) = abs d


--d--
angulo :: Ponto -> Double
angulo (Cartesiano x y) | x>0 && y==0 = 0
                        | x<0 && y==0 = pi
                        | otherwise = if x<0 then pi + atan (y/x)
                                      else atan (y/x)
angulo (Polar d a) = a


--e--
distfig :: Ponto -> Ponto -> Double
distfig (Cartesiano x1 y1) (Cartesiano x2 y2) = sqrt $ (x2-x1)^2 + (y2-y1)^2
--distfig (Polar a1 d1) (Polar a2 d2)



--7--
data Figura = Circulo Ponto Double
            | Rectangulo Ponto Ponto
            | Triangulo Ponto Ponto Ponto deriving (Show,Eq)

--a--
poligono :: Figura -> Bool
poligono (Circulo c r) = r > 0
poligono (Rectangulo (Cartesiano x y) (Cartesiano a b)) = x/=a && y/=b
poligono (Triangulo (Cartesiano x y) (Cartesiano a b) (Cartesiano w z)) = x/=a && y/=b && x/=w && y/=z && a/=w && b/=z 


--b--
vertices :: Figura -> [Ponto]
vertices (Circulo _ r) = []
vertices (Rectangulo (Cartesiano x y) (Cartesiano a b)) = [(Cartesiano x y)] ++ [(Cartesiano a b)] ++ [(Cartesiano x b)] ++ [(Cartesiano a y)]
vertices (Triangulo (Cartesiano x y) (Cartesiano a b) (Cartesiano w z)) = [(Cartesiano x y)] ++ [(Cartesiano a b)] ++ [(Cartesiano w z)]


--c--
area :: Figura -> Double
area (Triangulo p1 p2 p3) = let a = distfig p1 p2
                                b = distfig p2 p3
                                c = distfig p3 p1 
                                s = (a+b+c) / 2 -- semi-perimetro
                            in sqrt (s*(s-a)*(s-b)*(s-c)) -- formula de Heron
area (Rectangulo (Cartesiano x y) (Cartesiano a b)) = abs (x-a) * abs (y-b)
area (Circulo c r) = pi * r^2


--d--
perimetrofig :: Figura -> Double
perimetrofig (Circulo _ r) = pi * 2*r
perimetrofig (Rectangulo (Cartesiano x y) (Cartesiano a b)) = (2 * (abs $ x-a)) + (2 * (abs $ y-b))
perimetrofig (Triangulo p1 p2 p3) = (distfig p1 p2) + (distfig p1 p3) + (distfig p2 p3)



--8--
--a--
isLower' :: Char -> Bool
isLower' x = x >= 'a' && x <= 'z'


--b--
isDigit' :: Char -> Bool
isDigit' x = x >= '0' && x <= '9'


--c--
isAlpha' :: Char -> Bool
isAlpha' x = x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z'


--d--
toUpper' :: Char -> Char
toUpper' x | (isLower x == True) = chr $ (ord x) + (ord 'A' - ord 'a')
           | otherwise = x


--e--
intToDigit' :: Int -> Char
intToDigit' n = chr (n + ord '0')


--f--
digitToInt' :: Char -> Int
digitToInt' x = ord x - ord '0'