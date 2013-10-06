#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  M�dulo de defini��o: GRA  Grafo direcionado
*
*  Arquivo gerado:              grafo.c
*  Letras identificadoras:      GRA
*
*	Autores:
*     - rc: Robert Corr�a
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data        Observa��es
*     1.0     hg & rc  06/out/13   Prepara��o do m�dulo para trabalhar com grafos direcionados.
*
*  Descri��o do m�dulo
*     Implementa grafos direcionados com manipula��o, ou seja, � possivel criar, inserir
*     v�rtices no grafo, conect�-los atrav�s de arestas direcionais al�m de destruir o grafo,
*     um v�rtice ou uma aresta, navegar atrav�s das arestas usando o nome da aresta ou do
*     v�rtice de destino como refer�ncia. � poss�vel tamb�m marcar v�rtices como origem,
*     estes v�rtices poder�o ser acessados � qualquer momento utilizando a fun��o de navega��o
*     para origens.
*
*     Podem existir n grafos em opera��o simultaneamente.
*     Os grafos possuem uma cabe�a encapsulando o seu estado.
*
*     Cada grafo armazena dados gen�ricos.
*     Cada v�tice do grafo possui uma refer�ncia para o valor.
*
***************************************************************************/
 
#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um grafo */

typedef struct GRA_stGrafo * GRA_tppGrafo ;

/***********************************************************************
*
*  Tipo de dados: GRA Condi��es de retorno
*
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es do grafo
*
***********************************************************************/

typedef enum {

   GRA_CondRetOK,
      /* Concluiu corretamente */

   GRA_CondRetGrafoVazio,
      /* O grafo n�o cont�m elementos */

   GRA_CondRetGrafoNaoFoiCriado,
      /* O grafo n�o cont�m elementos */

   GRA_CondRetNaoAchou,
      /* N�o encontrou o v�rtice/aresta procurado(a) */

   GRA_CondRetFaltouMemoria,
      /* Faltou mem�ria ao tentar alocar algo */
 
} GRA_tpCondRet ;



/***********************************************************************
*
*  Fun��o: <abreviacao do modulo> <nome da funcao por extenso>
*
*  Descri��o
*     <descricao da fun��o>
*
*  Par�metros
*     <param 1>      - <explica��o sobre parametro 1>
*     <parametro 2>  - <explica��o sobre parametro 2>
*
*  Condi��es de retorno
*     <listar os poss�veis tpCondRet>
*
*  Retorno por refer�ncia
*     <descri��o do retorno>
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saida
*     <assertivas de saida>
*
***********************************************************************/

GRA_tpCondRet GRA_CriarGrafo(GRA_tppGrafo *ppGrafo, void (*DestruirConteudo)(void *pConteudo));
GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo *ppGrafo);

/* Construir grafo */
GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafoParm, char *pNomeVertice, void *pValor);
/* Ao criar a aresta, lembrar de inserir a aresta entre os sucessores da origem, e o vertice entre os antecessores do destino */
GRA_tpCondRet GRA_InserirArestaDoCorrentePara(GRA_tppGrafo pGrafoParm, char *nomeAresta, char *nomeVerticeDestino);

/* Obter e alterar */
GRA_tpCondRet GRA_ObterConteudoCorrente(GRA_tppGrafo pGrafoParm, void **ppValor);
GRA_tpCondRet GRA_AlterarConteudoCorrente(GRA_tppGrafo pGrafoParm, void *pValor);

/* Outros */
GRA_tpCondRet GRA_TornarCorrenteUmaOrigem(GRA_tppGrafo pGrafoParm);

/* Navega�ao */
GRA_tpCondRet GRA_IrParaVerticeAdjacente(GRA_tppGrafo pGrafoParm, char *nomeDaAresta);
GRA_tpCondRet GRA_SeguirPelaAresta(GRA_tppGrafo pGrafoParm, char *nomeAresta);
GRA_tpCondRet GRA_IrParaAOrigem(GRA_tppGrafo pGrafoParm, char *nomeVertice);

/* Destruir grafo */
GRA_tpCondRet GRA_DestruirVerticeCorrente(GRA_tppGrafo pGrafoParm);
GRA_tpCondRet GRA_DestruirArestaAdjacente(GRA_tppGrafo pGrafoParm, char *pNomeAresta);

/***********************************************************************/
#undef GRAFO_EXT

/********** Fim do m�dulo de defini��o: GRA Grafo direcionado **********/

#else
#endif
