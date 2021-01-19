module Ficha3 where



--1--
data Hora = H Int Int deriving Show
type Etapa = (Hora,Hora)
type Viagem = [Etapa]

--a--
testaEtapa :: Etapa -> Bool
testaEtapa (H h1 m1 , H h2 m2) = horaValida (H h1 m1) && 
                                 horaValida (H h2 m2) && 
                                 (h1<h2 || (h1==h2 && m2>m1))


horaValida :: Hora -> Bool
horaValida (H h m) = h>=0 && h<24 && m>=0 && m<60


--b--
testaViagem :: Viagem -> Bool
testaViagem [] = False
testaViagem [e] = testaEtapa e
testaViagem ((h1,h2):(h3,h4):t) = testaEtapa (h1,h2) && 
                                  testaEtapa (h3,h4) &&
                                  testaEtapa (h2,h3) &&
                                  testaViagem ((h3,h4):t)


--c--
partidachegada :: Viagem -> (Hora,Hora)
partidachegada [(h1,h2)] = (h1,h2)
partidachegada ((h1,h2):t) = (h1, snd (last t))


--d--
tempoViagem :: Viagem -> Int
tempoViagem [] = 0
tempoViagem (e:es) = tempoEtapa e + tempoViagem es
                         where tempoEtapa (h1,h2) = horasParaMin h2 - horasParaMin h1


horasParaMin :: Hora -> Int
horasParaMin (H h m) = h*60 + m


--e--
tempoEspera :: Viagem -> Int
tempoEspera [] = 0
tempoEspera [e] = 0
tempoEspera ((H h1 m1, H h2 m2) : (H h3 m3, H h4 m4) : t) = calculatempo (H h2 m2,H h3 m3) + tempoEspera ((H h3 m3,H h4 m4):t)


calculatempo :: (Hora,Hora) -> Int
calculatempo (H h1 m1, H h2 m2) = horasParaMin (H h2 m2) - (horasParaMin (H h1 m1))


--f--
tempototal :: Viagem -> Int
tempototal [] = 0
tempototal v = tempoViagem v + tempoEspera v



--2--
data Ponto = Cartesiano Double Double | Polar Double Double deriving (Show,Eq)

type Poligonal = [Ponto]

data Figura = Circulo Ponto Double
            | Rectangulo Ponto Ponto
            | Triangulo Ponto Ponto Ponto deriving (Show,Eq)

--a--
compLinha :: Poligonal -> Double
compLinha [] = 0
compLinha (p1:p2:ps) = dist p1 p2 + compLinha (p2:ps)


dist :: Ponto -> Ponto -> Double
dist (Cartesiano x y) (Cartesiano a b) = sqrt $ (x-a)^2 + (y-b)^2


--b--
isLinhaFechada :: Poligonal -> Bool
isLinhaFechada [] = False
isLinhaFechada (h:t) | elem h t = True
                     | otherwise = isLinhaFechada t


--c--
triangula :: Poligonal -> [Figura]
triangula [] = []
triangula [p1] = []
triangula (p1:p2:p3:ps) = (Triangulo p1 p2 p3) : triangula (p1:p3:ps)


--d--
area :: Figura -> Double 
area = undefined


--e--
mover :: Poligonal -> Ponto -> Poligonal
mover linhap p = p:linhap


--f--
zoom :: Double -> Poligonal -> Poligonal
zoom n [p1]= [p1]
zoom n ((Cartesiano x y):(Cartesiano a b):t) = (Cartesiano x y) : zoom n ((Cartesiano (a*n) (b*n)):t)



--3--
data Contacto = Casa Integer
              | Trab Integer
              | Tlm Integer
              | Email String deriving Show
type Nome = String
type Agenda = [(Nome, [Contacto])]

--a--
acrescEmail :: Nome -> String -> Agenda -> Agenda
acrescEmail n e [] = [(n,[Email e])]
acrescEmail n e ((x,y):t) | n==x = (n,y++[Email e]):t
                          | otherwise = acrescEmail n e t


--b--
verEmails :: Nome -> Agenda -> Maybe [String]
verEmails n [] = Nothing
verEmails n ((x,y):t) | n==x = Just (selectEmail y)
                      | otherwise = verEmails n t

selectEmail :: [Contacto] -> [String]
selectEmail [] = []
selectEmail ((Email e):t) = e:selectEmail t
selectEmail (_:t) = selectEmail t


--c--
consTelefs :: [Contacto] -> [Integer]
consTelefs [] = []
consTelefs ((Casa c):t) = c:consTelefs t
consTelefs ((Trab trab):t) = trab:consTelefs t
consTelefs ((Tlm telem):t) = telem:consTelefs t
consTelefs (_:t) = consTelefs t


--d--
casa :: Nome -> Agenda -> Maybe Integer
casa n [] = Nothing
casa n ((x,y):t) | n==x = Just (selectCasa y)
                 | otherwise = casa n t

selectCasa :: [Contacto] -> Integer
selectCasa ((Casa c):t) = c
selectCasa (_:t) = selectCasa t



--4--
type Dia = Int
type Mes = Int
type Ano = Int
--type Nome = String
data Data = D Dia Mes Ano deriving Show
type TabDN = [(Nome,Data)]

--a--
procura :: Nome -> TabDN -> Maybe Data
procura _ [] = Nothing
procura x ((n,d):t) | x==n = Just d
                    | otherwise = procura x t


--b--
idade :: Data -> Nome -> TabDN -> Maybe Int
idade _ _ [] = Nothing
idade (D d m a) n ((p,D d1 m1 a1):t) | n==p = Just $ calculaidade (D d m a) (D d1 m1 a1)
                                     | otherwise = idade (D d m a) n t


calculaidade :: Data -> Data -> Int
calculaidade (D d1 m1 a1) (D d2 m2 a2) | m1>m2 = a1-a2
                                       | m1<m2 = a1-a2-1
                                       | otherwise = if d1>=d2 then a1-a2 
                                                               else a1-a2-1


--c--
anterior :: Data -> Data -> Bool
anterior (D d1 m1 a1) (D d2 m2 a2) | a2>a1 = True
                                   | a2==a1 && m2>m1 = True
                                   | a2==a1 && m2==m1 && d2>d1 = True
                                   | otherwise = False


--d--
ordena :: TabDN -> TabDN
ordena [] = []
ordena (h:t) = auxord h (ordena t)

auxord :: (Nome,Data) -> TabDN -> TabDN
auxord (n, D d m a) [] = [(n, D d m a)]
auxord (n, D d1 m1 a1) ((n2, D d2 m2 a2):t) | anterior (D d1 m1 a1) (D d2 m2 a2) = ((n, D d1 m1 a1):(n2, D d2 m2 a2):t)
                                            | otherwise = (n2, D d2 m2 a2) : auxord (n, D d1 m1 a1) t


--e--
porIdade:: Data -> TabDN -> [(Nome,Int)]
porIdade _ [] = []
porIdade (D d m a) l = (n,idade): porIdade (D d m a) ls
                            where ((n, D d2 m2 a2) : ls) = ordena l
                                  idade = calculaidade (D d m a) (D d2 m2 a2)



--5--
data Movimento = Credito Float | Debito Float deriving Show

data DataE = DE Int Int Int deriving Show

data Extracto = Ext Float [(DataE, String, Movimento)] deriving Show


--a--
extValor :: Extracto -> Float -> [Movimento]
extValor (Ext s []) _ = []
extValor (Ext s ((DE d m a, info, Debito v):t)) n  | n<=v = Debito v : extValor (Ext s t) n
                                                   | otherwise = extValor (Ext s t) n
extValor (Ext s ((DE d m a, info, Credito v):t)) n | n<=v = Credito v : extValor (Ext s t) n 
                                                   | otherwise = extValor (Ext s t) n 


--b--
filtro :: Extracto -> [String] -> [(DataE,Movimento)]
filtro (Ext s []) _ = []
filtro (Ext s ((d, info, m):t)) [] = []
filtro (Ext s ((d, info, m):t)) i | elem info i = (d,m) : filtro (Ext s t) i
                                  | otherwise = filtro (Ext s t) i


--c--
creDeb :: Extracto -> (Float,Float)
creDeb (Ext s []) = (0,0)
creDeb (Ext s l) = (creds l , -debs l)


creds :: [(DataE,String,Movimento)] -> Float
creds ((d, info, Credito v):t) = v + creds t
creds ((d, info, Debito v):t) = creds t

debs :: [(DataE,String,Movimento)] -> Float
debs ((d, info, Debito v):t) = v + debs t
debs ((d, info, Credito v):t) = debs t


--d--
saldo :: Extracto -> Float
saldo (Ext s []) = s
saldo (Ext s ((d, info, Credito v):t)) = s+v + (saldo (Ext (s+v) t))
saldo (Ext s ((d, info, Debito v):t)) = s-v + (saldo (Ext (s-v) t))