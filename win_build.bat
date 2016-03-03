set h=%TIME:~0,2%
set m=%TIME:~3,2%
set dd=%DATE:~0,2%
set mm=%DATE:~3,2%
set yyyy=%DATE:~6,4%
set cdt=%h%_%m%_%s%T%dd%-%mm%-%yyyy%
C:\MinGW\bin\g++ -o "bin\Game_Main_Windows_%cdt%.exe" "src\main.cpp"
PAUSE