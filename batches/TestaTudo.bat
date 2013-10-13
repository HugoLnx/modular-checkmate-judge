REM executa os testes dos módulos LISTA, CONTEUDO e GRAFO

mkdir resultadosDosTestes



TRAB2-1\executavel\TRAB2-1.EXE      /sTRAB2-1\scripts\teste_lista.script      /lresultadosDosTestes\teste_lista.log       /aresultadosDosTestes\estatisticas

TRAB2-2\executavel\TRAB2-2.EXE      /sTRAB2-2\scripts\teste_conteudo.script     /lresultadosDosTestes\teste_conteudo.log     /aresultadosDosTestes\estatisticas

TRAB2-3\executavel\TRAB2-3.EXE      /sTRAB2-3\scripts\teste_grafo.script     /lresultadosDosTestes\teste_grafo.log     /aresultadosDosTestes\estatisticas

ferramentas\CompileBanner     /c"Estatisticas acumuladas"
ferramentas\exbestat          /eresultadosDosTestes\estatisticas

PAUSE


