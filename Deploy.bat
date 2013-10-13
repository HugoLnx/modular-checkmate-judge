
rmdir /s /q entrega

REM *********************Cria estrutira de diretórios*********************

mkdir INF1301-Trab2-HGRC
mkdir INF1301-Trab2-HGRC\ferramentas
                  
mkdir INF1301-Trab2-HGRC\TRAB2-1
mkdir INF1301-Trab2-HGRC\TRAB2-1\src
mkdir INF1301-Trab2-HGRC\TRAB2-1\scripts
mkdir INF1301-Trab2-HGRC\TRAB2-1\lib
mkdir INF1301-Trab2-HGRC\TRAB2-1\src
mkdir INF1301-Trab2-HGRC\TRAB2-1\batches
mkdir INF1301-Trab2-HGRC\TRAB2-1\executavel
mkdir INF1301-Trab2-HGRC\TRAB2-1\src
mkdir INF1301-Trab2-HGRC\TRAB2-1\src\definicao
mkdir INF1301-Trab2-HGRC\TRAB2-1\src\implementacao
                  
mkdir INF1301-Trab2-HGRC\TRAB2-2
mkdir INF1301-Trab2-HGRC\TRAB2-2\src
mkdir INF1301-Trab2-HGRC\TRAB2-2\scripts
mkdir INF1301-Trab2-HGRC\TRAB2-2\lib
mkdir INF1301-Trab2-HGRC\TRAB2-2\src
mkdir INF1301-Trab2-HGRC\TRAB2-2\batches
mkdir INF1301-Trab2-HGRC\TRAB2-2\executavel
mkdir INF1301-Trab2-HGRC\TRAB2-2\src
mkdir INF1301-Trab2-HGRC\TRAB2-2\src\definicao
mkdir INF1301-Trab2-HGRC\TRAB2-2\src\implementacao
                  
mkdir INF1301-Trab2-HGRC\TRAB2-3
mkdir INF1301-Trab2-HGRC\TRAB2-3\src
mkdir INF1301-Trab2-HGRC\TRAB2-3\scripts
mkdir INF1301-Trab2-HGRC\TRAB2-3\lib
mkdir INF1301-Trab2-HGRC\TRAB2-3\src
mkdir INF1301-Trab2-HGRC\TRAB2-3\batches
mkdir INF1301-Trab2-HGRC\TRAB2-3\executavel
mkdir INF1301-Trab2-HGRC\TRAB2-3\src
mkdir INF1301-Trab2-HGRC\TRAB2-3\src\definicao
mkdir INF1301-Trab2-HGRC\TRAB2-3\src\implementacao

mkdir INF1301-Trab2-HGRC\relatorios

REM *********************Adiciona ferramentas*********************

copy ferramentas\compilebanner.exe INF1301-Trab2-HGRC\ferramentas
copy ferramentas\exbestat.exe INF1301-Trab2-HGRC\ferramentas

REM *********************Adicinada executaveis*********************

copy Release\lista.exe INF1301-Trab2-HGRC\TRAB2-1\executavel
rename INF1301-Trab2-HGRC\TRAB2-1\executavel\lista.exe TRAB2-1.EXE

copy Release\conteudo.exe INF1301-Trab2-HGRC\TRAB2-2\executavel
rename INF1301-Trab2-HGRC\TRAB2-2\executavel\conteudo.exe TRAB2-2.EXE

copy Release\grafo.exe INF1301-Trab2-HGRC\TRAB2-3\executavel
rename INF1301-Trab2-HGRC\TRAB2-3\executavel\grafo.exe TRAB2-3.EXE

REM *********************Adiciona libs*********************

copy src\ArcaboucoTeste.lib INF1301-Trab2-HGRC\TRAB2-1\lib
copy src\ArcaboucoTeste.lib INF1301-Trab2-HGRC\TRAB2-2\lib
copy src\ArcaboucoTeste.lib INF1301-Trab2-HGRC\TRAB2-3\lib

REM *********************Adiciona scripts*********************

copy src\teste_lista.script INF1301-Trab2-HGRC\TRAB2-1\scripts
copy src\teste_conteudo.script INF1301-Trab2-HGRC\TRAB2-2\scripts
copy src\teste_grafo.script INF1301-Trab2-HGRC\TRAB2-3\scripts

REM *********************Adiciona modulo de definicao*********************

copy src\lista.h INF1301-Trab2-HGRC\TRAB2-1\src\definicao
copy src\conteudo.h INF1301-Trab2-HGRC\TRAB2-2\src\definicao
copy src\grafo.h INF1301-Trab2-HGRC\TRAB2-3\src\definicao

REM *********************Adiciona modulo de implementacao*********************

copy src\lista.c INF1301-Trab2-HGRC\TRAB2-1\src\implementacao
copy src\test_lis.c INF1301-Trab2-HGRC\TRAB2-1\src\implementacao
copy src\conteudo.c INF1301-Trab2-HGRC\TRAB2-2\src\implementacao
copy src\test_con.c INF1301-Trab2-HGRC\TRAB2-2\src\implementacao
copy src\grafo.c INF1301-Trab2-HGRC\TRAB2-3\src\implementacao
copy src\test_gra.c INF1301-Trab2-HGRC\TRAB2-3\src\implementacao

REM *********************Adiciona bathces*********************

copy batches\TestaLista.bat INF1301-Trab2-HGRC\TRAB2-1\batches
copy batches\LimpaTudo.bat INF1301-Trab2-HGRC\TRAB2-1\batches
copy batches\TestaConteudo.bat INF1301-Trab2-HGRC\TRAB2-2\batches
copy batches\LimpaTudo.bat INF1301-Trab2-HGRC\TRAB2-2\batches
copy batches\TestaGrafo.bat INF1301-Trab2-HGRC\TRAB2-3\batches
copy batches\LimpaTudo.bat INF1301-Trab2-HGRC\TRAB2-3\batches

copy batches\TestaTudo.bat INF1301-Trab2-HGRC
copy batches\LimpaTudo.bat INF1301-Trab2-HGRC

REM *********************Adiciona relatorios*********************

copy Documentos\hugo.relatorio INF1301-Trab2-HGRC\relatorios
rename INF1301-Trab2-HGRC\relatorios\hugo.relatorio RELATORIO-HUGO.TXT

copy Documentos\robert.relatorio INF1301-Trab2-HGRC\relatorios
rename INF1301-Trab2-HGRC\relatorios\robert.relatorio RELATORIO-ROBERT.TXT

REM *********************Adiciona Leia-me*********************

copy LEIA-ME.txt INF1301-Trab2-HGRC\

del INF1301-Trab2-HGRC.zip

ferramentas\7za a -tzip INF1301-Trab2-HGRC.rar INF1301-Trab2-HGRC

rmdir /s /q INF1301-Trab2-HGRC
