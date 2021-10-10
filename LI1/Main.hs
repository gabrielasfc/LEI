module Main where

import Data.Time.Clock.POSIX
import Control.Monad.IO.Class
import UI.NCurses
import Types
import FileUtils
import Tarefa2
import Tarefa4
import Tarefa5
import Tarefa6



loadManager :: Manager
loadManager = ( Manager (loadMaze "maps/1.txt") 0 0 0 0 defaultDelayTime )


updateControlledPlayer :: Key -> Manager -> Manager 
updateControlledPlayer k (Manager (State m ps l) pid step bf dlt dly) | k==KeyLeftArrow  = Manager (State m (rotatePlayer pid ps L) l) pid step bf dlt dly
                                                                      | k==KeyRightArrow = Manager (State m (rotatePlayer pid ps R) l) pid step bf dlt dly
                                                                      | k==KeyUpArrow    = Manager (State m (rotatePlayer pid ps U) l) pid step bf dlt dly
                                                                      | k==KeyDownArrow  = Manager (State m (rotatePlayer pid ps D) l) pid step bf dlt dly


changeOrientation :: Player -> Orientation -> Player
changeOrientation (Pacman(PacState (i,(y,x),v,o,p,l) t m md)) orientation = (Pacman(PacState (i,(y,x),v,orientation,p,l) t m md))
changeOrientation (Ghost(GhoState (i,(y,x),v,o,p,l) md)) orientation = (Ghost (GhoState (i,(y,x),v,orientation,p,l) md))


rotatePlayer :: Int -> [Player] -> Orientation -> [Player]
rotatePlayer _ [] _ = []
rotatePlayer id (p:ps) o | id == getPlayerID p = (changeOrientation p o):ps
                         | otherwise = p:(rotatePlayer id ps o)



updateScreen :: Window  -> ColorID -> Manager -> Curses ()
updateScreen w a man =
                  do
                    updateWindow w $ do
                      clear
                      setColor a
                      moveCursor 0 0 
                      drawString $ show (state man)
                    render
     
currentTime :: IO Integer
currentTime = fmap ( round . (* 1000) ) getPOSIXTime

updateTime :: Integer -> Manager -> Manager
updateTime now (Manager state pid step bf dlt dly) = Manager state pid step bf (now-bf) dly

resetTimer :: Integer -> Manager -> Manager
resetTimer now (Manager state pid step bf dlt dly) = (Manager state pid step now 0 dly)

nextFrame :: Integer -> Manager -> Manager
nextFrame now (Manager state pid step bf dlt dly) = resetTimer now (Manager (passTime step state) pid (step+1) bf dlt dly)


loop :: Window -> Manager -> Curses ()
loop w man@(Manager s pid step bf delt del ) = do 
  color_schema <- newColorID ColorBlue ColorWhite  10
  now <- liftIO  currentTime
  updateScreen w  color_schema man
  if ( delt > del )
    then loop w $ nextFrame now man
    else do
          ev <- getEvent w $ Just 0
          case ev of
                Nothing -> loop w (updateTime now man)
                Just (EventSpecialKey arrow ) -> loop w $ updateControlledPlayer arrow (updateTime now man)
                Just ev' ->
                  if (ev' == EventCharacter 'q')
                    then return ()
                    else loop w (updateTime now man)

main :: IO ()
main =
  runCurses $ do
    setEcho False
    setCursorMode CursorInvisible
    w <- defaultWindow
    loop w loadManager