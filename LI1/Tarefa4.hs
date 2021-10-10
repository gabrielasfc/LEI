{-|
Module      : Tarefa4
Description : Reagir à passagem do tempo
Copyright   : Daniel Furtado <a97327@alunos.uminho.pt>;
              Gabriela Cunha <a97393@alunos.uminho.pt>

= Introdução

Na primeira tarefa da 2ª fase do trabalho, foi-nos proposto fazer com que o jogo reagisse à passagem do tempo com ajuda da biblioteca __/NCurses/__.


= Objetivos e estratégias 

No início da tarefa procuramos entender primeiramente o que era pretendido no enunciado e conhecer os novos conceitos de step, delay, delta, pois foi algo com que nunca trabalhamos previamente.

Assim, começamos por desenvolver as 4 funções presentes no módulo /Main/ e as alterações relativas à Tarefa 2, pois neste momento passamos a trabalhar já com o tempo relativo ao modo Mega.

Depois de concluírmos as funções do /Main/, fizemos a função __switchMouth__ e apicámo-la na Tarefa 2, pois o Pacman deve alternar a sua boca entre /Open/ e /Closed/ por cada step.

Em seguida, alteramos a nossa função da Tarefa 2 relativa ao modo Mega do Pacman e acabamos por dividi-la em 2 partes: a __megaPacg__ que explica o comportamento dos ghosts face ao modo Mega e a __megaPacp__ que explica o comportamento do pacman.

Foi estabelecido que o tempoMega durava 10s e que o delay default era de 0,25s . 

Assim, tivemos de estabelecer na função __megaPacp__ quando o fantasma devia voltar ao modo /Normal/, sendo que o tempoMega começava nos 10s e em cada step perdia 0,25s dos 10s.

Quando chegamos ao fim de todas estas alterações, começamos a trabalhar na função principal desta tarefa,__passTime__ e começamos apenas por criar uma função auxiliar para atualizar os /states/ com as jogadas do pacman.

Conseguimos testar a função no Main e corrigimos alguns bugs na função __updateControlledPlayer__ no /Main/ (se mantivessemos a tecla premida o pacman andava mais rápido e tínhamos de clicar sempre na tecla para que ele se movesse).

Aí percebemos que os fantasmas continuavam no mesmo sítio pois ainda não tínhamos gerado uma __play__ relativa a eles e focamo-nos na Tarefa5, relativa ao movimentos dos ghosts.

Mais tarde, começamos a juntar as funções da Tarefa5 a esta tarefa e atualizamos a nossa função auxiliar para __'univPlay'__ , uma função universal pois passou a efetuar também jogadas dos ghosts e começou a utilizar os __/steps/__ e a atualizar os __/states/__ do jogo, isto é, começou a englobar tudo.

Já na Tarefa6, voltamos a dar um update nesta Tarefa4 pois queríamos testar o /bot/, e deixamos em comentário uma opção das 2 funções de modo a testar o __bot__.


= Conclusão

Esta tarefa, apesar de não ter muito código no ficheiro, foi uma tarefa bastante complicada e trabalhosa, visto que trabalha com várias tarefas (T2, T5 e ainda T6).

Foi também através desta tarefa que detetamos vários erros em tarefas anteriores e também nas seguintes.

Concluíndo, foi uma tarefa que exigiu muita atenção precisamente por termos de mexer com outras tarefas.

-}


module Tarefa4 where 

import Types
import Tarefa2
import Tarefa5
import Tarefa6

defaultDelayTime = 250 -- 250 ms


------------------------------------------------------------------PLAYER------------------------------------------------------------------------------
-- | Função auxiliar que determina se o Player deve atualizar a sua posição de acordo com o Step e com o seu modo.
--
univPlay :: Int -> State -> [Player] -> [Play] -> State
univPlay _ state [] _ = state
univPlay step state (Pacman(PacState (i,(x1,y1),v,o,p,l) t m Dying):ps) _    = state 
univPlay step state (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md):ps) lp      = univPlay step (play (Move i o) state) ps lp
univPlay step state (Ghost(GhoState (id,(x2,y2),vel,ori,pt,lv) Dead):ps) lp  | even step = univPlay step (play (idghost lp id) state) ps lp --ghost só progride de 2 em 2 iterações
                                                                             | otherwise = univPlay step state ps lp
univPlay step state (Ghost(GhoState (id,(x2,y2),vel,ori,pt,lv) Alive):ps) lp = univPlay step (play (idghost lp id) state) ps lp


-- | Função que apenas retorna a jogada do Ghost com o id correspondente. 
--
idghost :: [Play] -> Int -> Play
idghost ((Move id o):t) i | id==i = Move id o
                          | otherwise = idghost t i


-- | Função final que altera o State do jogo.
--
passTime :: Int  -> State -> State
passTime step (State m ps l) = univPlay step (State m ps l) ps (ghostPlay (State m ps l))


------------------------------------------------------------------BOT--------------------------------------------------------------------------------

---- | Função auxiliar que determina se o Player deve atualizar a sua posição de acordo com o Step e com o seu modo.
--
--univPlay :: Int -> State -> [Player] -> [Play] -> Maybe Play -> State
--univPlay _ state [] _ _ = state
--univPlay step state (Pacman(PacState (i,(x1,y1),v,o,p,l) t m Dying):ps) _ _       = state 
--univPlay step state (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md):ps) lp Nothing   = univPlay step (play (Move i o) state) ps lp Nothing
--univPlay step state (Pacman(PacState (i,(x1,y1),v,o,p,l) t m md):ps) lp (Just pp) = univPlay step (play pp state) ps lp (Just pp)
--univPlay step state (Ghost(GhoState (id,(x2,y2),vel,ori,pt,lv) Dead):ps) lp pp    | even step = univPlay step (play (idghost lp id) state) ps lp pp --ghost só progride de 2 em 2 iterações
--                                                                                  | otherwise = univPlay step state ps lp pp
--univPlay step state (Ghost(GhoState (id,(x2,y2),vel,ori,pt,lv) Alive):ps) lp pp   = univPlay step (play (idghost lp id) state) ps lp pp
--
--
--
---- | Função que apenas retorna a jogada do Ghost com o id correspondente. 
--
--idghost :: [Play] -> Int -> Play
--idghost ((Move id o):t) i | id==i = Move id o
--                          | otherwise = idghost t i
--
--
--
---- | Função final que altera o State do jogo.
--
--passTime :: Int  -> State -> State
--passTime step (State m ps l) = univPlay step (State m ps l) ps (ghostPlay (State m ps l)) (bot (getPlayerID $ pacman ps) (State m ps l)) 