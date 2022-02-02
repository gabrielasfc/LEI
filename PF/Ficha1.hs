module Ficha1 where

import Data.Char

--1--
--a--
perimetro :: Float -> Float
perimetro r = 2 * pi * r;

--b--
dist :: (Double,Double) -> (Double,Double) -> Double
dist (a,b) (x,y) = sqrt $ (x-a)^2 + (y-b)^2

--c--
primUlt :: [a] -> (a,a)
primUlt l = (head l, last l)

--d--
multiplo :: Int -> Int -> Bool
multiplo m n = (mod m n == 0)

--e--
truncaImpar :: [a] -> [a]
truncaImpar [] = []
truncaImpar (h:t) | odd $ length (h:t) = t
                  | otherwise = (h:t)

--f--
max2 :: Int -> Int -> Int
max2 x y | x > y = x
         | otherwise = y

--g--
max3 :: Int -> Int -> Int -> Int
max3 x y z | x > z || y > z = max2 x y
           | y > x || z > x = max2 y z
           | otherwise = max2 x z


--2--
--a--
nRaizes :: Float -> Float -> Float -> Float
nRaizes a b c | delta == 0 = 1
              | delta < 0 = 0
              | otherwise = 2
                    where delta = b^2 - 4*a*c

--b--
raizes :: Float -> Float -> Float -> [Float]
raizes a b c | nRaizes a b c == 1 = [(-b) / 2*a]
             | nRaizes a b c == 0 = []
             | otherwise = [(-b - sqrt(delta)) / 2*a, (-b + sqrt(delta)) / 2*a]
                    where delta = b^2 - 4*a*c


--3--
type Hora = (Int,Int)

--a--
testaHora :: Hora -> Bool
testaHora (h,m) = h>=0 && h<24 && m>=0 && m<60

--b--
comparaHora :: Hora -> Hora -> Bool
comparaHora (h1,m1) (h2,m2) = h1>h2 || (h1==h2 && m1>m2)

--c--
horaToMin :: Hora -> Int
horaToMin (h,m) = h*60 + m

--d--
minToHora :: Int -> Hora
minToHora m = (div m 60, mod m 60)

--e--
difHoras :: Hora -> Hora -> Int
difHoras (h1,m1) (h2,m2) = abs $ (h2-h1)*60 + m2-m1

--f--
addMin :: Hora -> Int -> Hora
addMin (h,m) min = minToHora $ horaToMin(h,m) + min


--4--
data Hora2 = H Int Int deriving (Show,Eq)

--a--
testaHora2 :: Hora2 -> Bool
testaHora2 (H h m) = h>= 0 && h<24 && m>=0 && m<60

--b--
comparaHora2 :: Hora2 -> Hora2 -> Bool
comparaHora2 (H h1 m1) (H h2 m2) = h1>h2 || (h1==h2 && m1>m2)

--c--
horaToMin2 :: Hora2 -> Int
horaToMin2 (H h m) = h*60 + m

--d--
minToHora2 :: Int -> Hora2
minToHora2 m = H (div m 60) (mod m 60)

--e--
difHoras2 :: Hora2 -> Hora2 -> Int
difHoras2 (H h1 m1) (H h2 m2) = abs $ (h2-h1)*60 + m2-m1

--f--
addMin2 :: Hora2 -> Int -> Hora2
addMin2 (H h m) min = minToHora2 $ horaToMin2 (H h m) + min


--5--
data Semaforo = Verde | Amarelo | Vermelho deriving (Show,Eq)

--a--
next :: Semaforo -> Semaforo
next Verde = Amarelo
next Amarelo = Vermelho
next Vermelho = Verde

--b--
stop :: Semaforo -> Bool
stop s = s /= Verde

--c--
safe :: Semaforo -> Semaforo -> Bool
safe s1 s2 = s1==Vermelho || s2==Vermelho


--6--
data Ponto = Cartesiano Double Double 
           | Polar Double Double 
           deriving (Show,Eq)

--a--
posx :: Ponto -> Double
posx (Cartesiano x y) = abs x
posx (Polar d a) = abs $ cos a * d

--b--
posy :: Ponto -> Double
posy (Cartesiano x y) = abs y
posy (Polar d a) = abs $ sin a * d

--c--
raio :: Ponto -> Double
raio (Cartesiano x y) = sqrt $ x^2 + y^2
raio (Polar d a) = d

--d--
angulo :: Ponto -> Double
angulo (Cartesiano x y) = atan (x/y)
angulo (Polar d a) = a

--e--
dist6 :: Ponto -> Ponto -> Double
dist6 p1 p2 = sqrt $ (posx p2 - posx p1)^2 + (posy p2 - posy p1)^2


--7--
data Figura = Circulo Ponto Double
            | Rectangulo Ponto Ponto
            | Triangulo Ponto Ponto Ponto
            deriving (Show,Eq)

--a--
poligono :: Figura -> Bool
poligono (Circulo c r) = r>0
poligono (Rectangulo p1 p2) = posx p1 /= posx p2 && posy p1 /= posy p2
poligono (Triangulo p1 p2 p3) = (a < b+c && b < a+c && c < a+b)
                                    where a = dist6 p1 p2
                                          b = dist6 p2 p3
                                          c = dist6 p1 p3

--b--
vertices :: Figura -> [Ponto]
vertices (Circulo _ _) = []
vertices (Rectangulo p1 p2) = [p1, (Cartesiano (posx p1) (posy p2)), p2, (Cartesiano (posx p2) (posy p1))]
vertices (Triangulo p1 p2 p3) = [p1, p2, p3]

--c--
area :: Figura -> Double
area (Triangulo p1 p2 p3) = let a = dist6 p1 p2
                                b = dist6 p2 p3
                                c = dist6 p3 p1
                                s = (a+b+c) / 2 -- semi-perimetro
                            in sqrt (s*(s-a)*(s-b)*(s-c)) -- formula de Heron
area (Rectangulo p1 p2) = (abs (posx p2 - posx p1)) * (abs (posy p2 - posy p1))
area (Circulo _ r) = pi * r^2

--d--
perimetro7 :: Figura -> Double
perimetro7 (Circulo _ r) = 2*pi*r
perimetro7 (Rectangulo p1 p2) = (abs (posx p2 - posx p1))*2 + (abs (posy p2 - posy p1))*2
perimetro7 (Triangulo p1 p2 p3) = dist6 p1 p2 + dist6 p1 p3 + dist6 p2 p3


--8--
--a--
myIsLower :: Char -> Bool
myIsLower x = x >= 'a' && x <= 'z'

--b--
myIsDigit :: Char -> Bool
myIsDigit x = x >= '0' && x <= '9'

--c--
myIsAlpha :: Char -> Bool
myIsAlpha x = x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z'

--d--
myToUpper :: Char -> Char
myToUpper x | myIsLower x = chr $ (ord x) - 32
            | otherwise = x

--e--
myIntToDigit :: Int -> Char
myIntToDigit x = chr $ x + ord '0'

--f--
myDigitToInt :: Char -> Int
myDigitToInt x = ord x - ord '0'