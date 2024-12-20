@echo off

REM
g++ uri.cpp -o programa 

REM Redireciona a entrada para o programa a partir do arquivo in.txt
< in.txt programa > out.txt

REM Compara o arquivo de saída com o arquivo de referência
fc out.txt out_ref.txt > nul

if errorlevel 1 (
    echo Arquivos sao diferentes.
) else (
    echo Arquivos sao iguais.
)

REM Limpa os arquivos intermediários
del programa out.txt

pause
