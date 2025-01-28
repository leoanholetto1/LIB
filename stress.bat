@echo off
setlocal enabledelayedexpansion

REM Definir a variável P
set P=uri

REM Compilar os arquivos diretamente com g++
g++ %P%.cpp -o %P%.exe || goto :error
g++ %P%2.cpp -o %P%2.exe || goto :error
g++ gen.cpp -o gen.exe || goto :error

REM Início do loop
set i=1
:loop
REM Gerar entrada usando gen
gen.exe %i% > in

REM Executar o programa principal e a segunda implementação
%P%.exe < in > out
%P%2.exe < in > out2

REM Comparar os arquivos out e out2
fc /b out out2 > nul
if not errorlevel 1 goto :continue

REM Em caso de diferença, exibir os detalhes
echo ======================================================================
echo TESTE FALHOU NA ITERACAO: %i%
echo ----------------------------------------------------------------------
type in
echo ----------------------------------------------------------------------
type out
echo ----------------------------------------------------------------------
type out2
echo ======================================================================

REM Excluir os arquivos criados
del in
del out
del out2

goto :end

:continue
REM Separador visual para cada teste que passou
echo [TESTE %i% OK]
echo ----------------------------------------------------------------------

REM Excluir os arquivos criados, mesmo se o teste passar
del in
del out
del out2

set /a i+=1
goto :loop

:error
echo Ocorreu um erro na compilacao.
goto :end

:end

echo Script finalizado.
exit /b
