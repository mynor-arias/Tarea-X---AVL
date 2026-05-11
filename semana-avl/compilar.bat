@echo off
echo Compilando proyecto AVL...
g++ -std=c++17 -Wall src/main.cpp src/AVL.cpp -o ranking.exe
if %errorlevel% == 0 (
    echo.
    echo Compilacion exitosa. Ejecutando...
    echo.
    ranking.exe
) else (
    echo.
    echo ERROR: Verifica que g++ este instalado.
    echo Descargalo desde: https://www.mingw-w64.org/
    pause
)
