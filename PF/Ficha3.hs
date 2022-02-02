module Ficha3 where

import Ficha1 as F1

--1--
type Etapa = (F1.Hora2,F1.Hora2)
type Viagem = [Etapa]

--a--
testaEtapa :: Etapa -> Bool
testaEtapa etapa@(H h1 m1, H h2 m2) = testaHora2 (H h1 m1) && testaHora2 (H h2 m2) && comparaHoraEt etapa

--true se a segunda for maior que a primeira
comparaHoraEt :: Etapa -> Bool
comparaHoraEt (H h1 m1, H h2 m2) = h1<h2 || (h1==h2 && m1<m2)

--b--
testaViagem :: Viagem -> Bool
testaViagem [] = False
testaViagem [e] = testaEtapa e
testaViagem ((h1,h2):(h3,h4):t) = testaEtapa (h1,h2) && testaEtapa (h3,h4) && testaEtapa (h2,h3) && testaViagem((h3,h4):t)

--c--
partidaChegada :: Viagem -> (F1.Hora2,F1.Hora2)
partidaChegada [(h1,h2)] = (h1,h2)
partidaChegada ((h1,h2):t) = (h1, snd(last t))

--d--
tempoViagem :: Viagem -> Int
tempoViagem [] = 0
tempoViagem (e:t) = tempoEtapa e + tempoViagem t

tempoEtapa :: Etapa -> Int
tempoEtapa (h1,h2) = horaToMin2 h2 - horaToMin2 h1

--e--
tempoEspera :: Viagem -> Int
tempoEspera [] = 0
tempoEspera [(h1,h2)] = 0
tempoEspera ((h1,h2):(h3,h4):t) = (horaToMin2 h3 - horaToMin2 h2) + tempoEspera ((h3,h4):t)

--f--
tempoTotal :: Viagem -> Int
tempoTotal [] = 0
tempoTotal v = tempoViagem v + tempoEspera v


--2--
type Poligonal = [F1.Ponto]

--a--
linhalength :: Poligonal -> Double
linhalength [] = 0
linhalength (p1:p2:t) = dist6 p1 p2 + linhalength (p2:t)

--b--
isLinhaFechada :: Poligonal -> Bool
isLinhaFechada [] = True
isLinhaFechada (h:t) | elem h t = True
                     | otherwise = isLinhaFechada t

--c--
triangula :: Poligonal -> [F1.Figura]
triangula [] = []
triangula [p] = []
triangula (p1:p2:p3:t) = (Triangulo p1 p2 p3) : triangula (p1:p3:t)

--d--
areaPol :: Poligonal -> Double
areaPol p = sum $ map (\fig -> area fig) (triangula p)

--e--
mover :: Poligonal -> Ponto -> Poligonal
mover pol p = undefined

--f--
zoom :: Double -> Poligonal -> Poligonal
zoom n [p1]= [p1]
zoom n (p1@(Cartesiano x y):p2@(Cartesiano a b):t) = p1 : zoom n ((Cartesiano (a*n) (b*n)):t)


--3--
data Contacto = Casa Integer
              | Trab Integer 
              | Tlm Integer 
              | Email String 
              deriving Show
type Agenda = [(Nome, [Contacto])]

--a--
acrescEmail :: Nome -> String -> Agenda -> Agenda
acrescEmail n e [] = [(n,[Email e])]
acrescEmail n e ((nome,c):t) | n==nome = (nome,c++[Email e]):t
                             | otherwise = acrescEmail n e t

--b--
verEmails :: Nome -> Agenda -> Maybe [String]
verEmails n [] = Nothing
verEmails n ((nome,c):t) | n==nome = Just (getEmails c)
                         | otherwise = verEmails n t

getEmails :: [Contacto] -> [String]
getEmails [] = []
getEmails ((Email e):t) = e : getEmails t
getEmails (_:t) = getEmails t

--c--
consTelefs :: [Contacto] -> [Integer]
consTelefs [] = []
consTelefs ((Tlm tlm):t) = tlm : consTelefs t
consTelefs ((Casa tlf_c):t) = tlf_c : consTelefs t
consTelefs ((Trab tlf_t):t) = tlf_t : consTelefs t
consTelefs (_:t) = consTelefs t

--d--
casa :: Nome -> Agenda -> Maybe Integer
casa _ [] = Nothing
casa n ((nome,c):t) | n==nome = Just (getCasa c)
                    | otherwise = casa n t

getCasa :: [Contacto] -> Integer
getCasa ((Casa c):t) = c
getCasa (_:t) = getCasa t


--4--
type Dia = Int
type Mes = Int
type Ano = Int
type Nome = String
data Data = D Dia Mes Ano deriving Show
type TabDN = [(Nome,Data)]

--a--
procura :: Nome -> TabDN -> Maybe Data
procura _ [] = Nothing
procura n ((nome,d):t) | n==nome = Just d
                       | otherwise = procura n t

--b--
idade :: Data -> Nome -> TabDN -> Maybe Int
idade _ _ [] = Nothing
idade curr n ((nome,d):t) | n==nome = Just $ calculaIdade curr d
                          | otherwise = idade curr n t

--1ª data atual, 2ª data nasc
calculaIdade :: Data -> Data -> Int
calculaIdade (D curr_d curr_m curr_a) (D nasc_d nasc_m nasc_a) | curr_m > nasc_m = curr_a - nasc_a
                                                               | curr_m < nasc_m = curr_a - nasc_a - 1 
                                                               | otherwise = if curr_d >= nasc_d then curr_a - nasc_a 
                                                                                                 else curr_a - nasc_a - 1
--c--
--true se a 1ª data for antes
anterior :: Data -> Data -> Bool
anterior (D d1 m1 a1) (D d2 m2 a2) = (a1<a2) || (a1==a2 && m1<m2) || (a1==a2 && m1==m2 && d1<d2)

--d--
ordena :: TabDN -> TabDN
ordena [] = []
ordena ((n,d):t) = insertOrd (n,d) (ordena t)

--insere na tabela por datas (ordem crescente)
insertOrd :: (Nome,Data) -> TabDN -> TabDN
insertOrd (n,d) [] = [(n,d)]
insertOrd (n,d) ((nome,dt):t) | anterior d dt = (n,d) : insertOrd (nome,dt) t
                              | otherwise = (nome,dt) : insertOrd (n,d) t

--e--
porIdade :: Data -> TabDN -> [(Nome,Int)]
porIdade _ [] = []
porIdade d tab = let ((n,dt):t) = reverse $ ordena tab 
                     idade = calculaIdade d dt
                 in (n,idade) : porIdade d t


--5--
data Movimento = Credito Float 
               | Debito Float
               deriving Show
data Extracto = Ext Float [(Data, String, Movimento)] deriving Show

--a--
extValor :: Extracto -> Float -> [Movimento]
extValor (Ext _ []) _ = []
extValor (Ext s ((_,_,Debito v):t)) n  | v>=n = Debito v : extValor (Ext s t) n
                                       | otherwise = extValor (Ext s t) n
extValor (Ext s ((_,_,Credito v):t)) n | v>=n = Credito v : extValor (Ext s t) n
                                       | otherwise = extValor (Ext s t) n

--b--
filtro :: Extracto -> [String] -> [(Data,Movimento)]
filtro (Ext _ []) _ = []
filtro (Ext _ ((_,_,_):t)) [] = []
filtro (Ext s ((d,i,m):t)) info | elem i info = (d,m) : filtro (Ext s t) info
                                | otherwise = filtro (Ext s t) info

--c--
creDeb :: Extracto -> (Float,Float)
creDeb (Ext _ []) = (0,0)
creDeb (Ext _ l) = (somaCreds l, somaDebs l)

somaCreds :: [(Data,String,Movimento)] -> Float
somaCreds ((_,_,Credito v):t) = v + somaCreds t
somaCreds ((_,_,Debito v):t) = somaCreds t

somaDebs :: [(Data,String,Movimento)] -> Float
somaDebs ((_,_,Debito v):t) = v + somaDebs t 
somaDebs ((_,_,Credito v):t) = somaDebs t

--d--
saldo :: Extracto -> Float
saldo ext@(Ext s_inic l) = s_inic + creds - debs
                            where (creds,debs) = creDeb ext