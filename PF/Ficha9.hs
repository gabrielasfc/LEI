module Ficha9 where

import System.Random
import Data.Char
import Data.List



--1--
bingo :: IO ()
bingo = do putStrLn "Bem-vindo ao Bingo!"
           bingoAux []

bingoAux :: [Int] -> IO ()
bingoAux l | length l == 90 = putStrLn "Acabou o jogo!"
           | otherwise = do n <- randomSemRep (1,90) l
                            getChar
                            putStr ("Saiu o número: ")
                            print n
                            let new_list = if elem n l then l
                                                       else n:l
                            bingoAux new_list

--verifica que o número a gerar ainda não foi gerado
randomSemRep :: (Int,Int) -> [Int] -> IO Int
randomSemRep intervalo l = do n <- randomRIO intervalo
                              if elem n l then randomSemRep intervalo l
                                          else return n



--b--
mastermind :: IO ()
mastermind = do putStrLn"Bem-vindo ao Mastermind!"
                key <- geraChave
                --print key
                t <- mastermindAux key 1
                putStr("\n")
                print ("Parabens! Encontrou a chave " ++ show key ++ " em " ++ show t ++ " tentativas!")


geraChave :: IO (Int,Int,Int,Int)
geraChave = do c1 <- randomRIO (0,9)
               c2 <- randomRIO (0,9)
               c3 <- randomRIO (0,9)
               c4 <- randomRIO (0,9)
               return (c1,c2,c3,c4)


adivinhaChave :: IO (Int,Int,Int,Int)
adivinhaChave = do print "Introduza os 4 digitos"
                   c1 <- getChar
                   c2 <- getChar
                   c3 <- getChar
                   c4 <- getChar
                   return (digitToInt c1, digitToInt c2, digitToInt c3, digitToInt c4)


mastermindAux :: (Int,Int,Int,Int) -> Int -> IO Int
mastermindAux (k1,k2,k3,k4) nr_tent = do let listaKey = [k1,k2,k3,k4]
                                         (a1,a2,a3,a4) <- adivinhaChave
                                         let acertados = 0 + (if k1 == a1 then 1 else 0) + (if k2 == a2 then 1 else 0) + (if k3 == a3 then 1 else 0) + (if k4 == a4 then 1 else 0)
                                         let posDif = 0 + (if k1 /= a1 && elem a1 (listaKey \\ [a2,a3,a4]) then 1 else 0) + 
                                                          (if k2 /= a2 && elem a2 (listaKey \\ [a3,a4]) then 1 else 0) +
                                                          (if k3 /= a3 && elem a3 (listaKey \\ [a4]) then 1 else 0) + 
                                                          (if k4 /= a4 && elem a4 (listaKey \\ []) then 1 else 0)
                                         if (acertados == 4) then return nr_tent 
                                                             else do putStr("\n")
                                                                     print $ "Tem " ++ show (acertados) ++ " no sitio certo e " ++ show (posDif) ++ " no sitio errado!"
                                                                     mastermindAux (k1,k2,k3,k4) (nr_tent+1)



--2--
data Aposta = Ap [Int] (Int,Int)

--a--
valida :: Aposta -> Bool
valida ap = tamanhoValido ap && dentroLimites ap && semRepetidos ap

tamanhoValido :: Aposta -> Bool
tamanhoValido (Ap nrs _) = length nrs == 5

dentroLimites :: Aposta -> Bool
dentroLimites (Ap nrs (e1,e2)) = e1>=1 && e1<=9 && e2>=1 && e2<=9 && length nrs == length(filter (\x -> x>=1 && x<=50) nrs)

semRepetidos :: Aposta -> Bool
semRepetidos (Ap [] _) = True
semRepetidos (Ap (h:t) (e1,e2)) | elem h t = False
                                | e1==e2 = False
                                | otherwise = semRepetidos (Ap t (e1,e2))


--b--
comuns :: Aposta -> Aposta -> (Int,Int)
comuns ap1 ap2 = (numerosCom ap1 ap2, estrelasCom ap1 ap2)


numerosCom :: Aposta -> Aposta -> Int
numerosCom (Ap [] _) _ = 0
numerosCom _ (Ap [] _) = 0
numerosCom (Ap (h:t) (e1,e2)) (Ap l (est1,est2)) | elem h l = 1 + numerosCom (Ap t (e1,e2)) (Ap l (est1,est2))
                                                 | otherwise = numerosCom (Ap t (e1,e2)) (Ap l (est1,est2))

estrelasCom :: Aposta -> Aposta -> Int
estrelasCom (Ap _ (e1,e2)) (Ap _ (est1,est2)) = (if e1==est1 then 1 else 0) + 
                                                (if e1==est2 then 1 else 0) +
                                                (if e2==est1 then 1 else 0) +
                                                (if e2==est2 then 1 else 0)


--c--
--i--
instance Eq Aposta where
    ap1==ap2 = comuns ap1 ap2 == (5,2)

--ii--
premio :: Aposta -> Aposta -> Maybe Int
premio ap1 ap2 | comuns ap1 ap2 == (0,0) = Nothing
               | comuns ap1 ap2 == (5,2) = Just 1
               | comuns ap1 ap2 == (5,1) = Just 2
               | comuns ap1 ap2 == (5,0) = Just 3
               | comuns ap1 ap2 == (4,2) = Just 4
               | comuns ap1 ap2 == (4,1) = Just 5
               | comuns ap1 ap2 == (5,0) = Just 6
               | comuns ap1 ap2 == (3,2) = Just 7
               | comuns ap1 ap2 == (2,2) = Just 8
               | comuns ap1 ap2 == (3,1) = Just 9
               | comuns ap1 ap2 == (3,0) = Just 10
               | comuns ap1 ap2 == (1,2) = Just 11
               | comuns ap1 ap2 == (2,1) = Just 12
               | comuns ap1 ap2 == (2,0) = Just 13


--d--
--i--
leAposta :: IO Aposta
leAposta = do putStrLn "Bem-vindo ao Euromilhoes!"
              putStrLn "Insira a sua aposta!"
              input <- getLine
              let nums = map read (words input)
              if (length nums /= 7) then do putStrLn "A aposta deve conter 7 numeros. Tente novamente."
                                            leAposta
                                     else do let [n1,n2,n3,n4,n5,e1,e2] = nums
                                             let aposta = Ap [n1,n2,n3,n4,n5] (e1,e2)
                                             if not (valida aposta) then do putStrLn "Aposta invalida. Tente novamente."
                                                                            leAposta
                                                                    else do putStrLn "Aposta registada. Obrigada!"
                                                                            return aposta 


--ii--
joga :: Aposta -> IO ()
joga key = do aposta <- leAposta
              let nr_premio = premio key aposta
              checkPremio nr_premio

checkPremio :: Maybe Int -> IO ()
checkPremio Nothing = putStrLn "Infelizmente nao obteve premio."
checkPremio (Just p) = putStrLn $ "Parabens! Ganhou o " ++ show p ++ " premio!"


--e--
geraChaveEM :: IO Aposta
geraChaveEM = do nums <- geraNums 5 []
                 ests@[e1,e2] <- geraEstrelas 2 []
                 return (Ap nums (e1,e2)) 


geraNums :: Int -> [Int] -> IO [Int]
geraNums 0 _ = return []
geraNums n nums = do x <- randomRIO (1,50)
                     if (elem x nums) then geraNums x nums
                                      else do new_num <- geraNums (n-1) nums
                                              return (x : new_num)

geraEstrelas :: Int -> [Int] -> IO [Int]
geraEstrelas 0 _ = return []
geraEstrelas n ests = do x <- randomRIO (1,9)
                         if (elem x ests) then geraEstrelas x ests
                                          else do new_est <- geraEstrelas (n-1) ests
                                                  return (x : new_est)


--f--
ciclo :: Aposta -> IO ()
ciclo key = do option <- menu
               if(option == 1) then do putStr "\n\n\n"
                                       joga key
                                 else if (option == 2) then do new_key <- geraChaveEM
                                                               ciclo new_key
                                                       else if (option == 0) then return ()
                                                                             else do putStrLn "\n\n\nIntroduza uma opcao valida!"
                                                                                     ciclo key

menu :: IO Int
menu = do putStrLn "\nApostar ........... 1\nGerar nova chave .. 2\n\nSair .............. 0"
          putStr "Opcao: "
          c <- getChar
          let opcao = digitToInt c
          return opcao

main :: IO ()
main = do key <- geraChaveEM
          ciclo key