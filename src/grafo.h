#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  M�dulo de defini��o: <abrevia��o>  <estrutura manipulada pelo m�dulo>
*
*  Arquivo gerado:              <nome-do-arquivo>.h
*  Letras identificadoras:      <abrevia��o>
*
*	Autores:
*     - <nick>: <nome>
*     - <nick>: <nome>
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data        Observa��es
*     1       <nick>   <data>      <observa��es>
*
*  Descri��o do m�dulo
*     <descri��o do m�dulo>
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

	GRA_CondRetOK ,
		/* Concluiu corretamente */

	GRA_CondRetGrafoVazia ,
		/* A grafo n�o cont�m elementos */

	GRA_CondRetNaoAchou ,
		/* N�o encontrou o valor procurado */

	GRA_CondRetFaltouMemoria
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
*  Retorno
*     <descricao do retorno, listar os poss�veis tpCondRet>
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saida
*     <assertivas de saida>
*
***********************************************************************/

GRA_tpCondRet GRA_CriarGrafo(GRA_tppGrafo *ppGrafo,
	void (*DestruirConteudo)(void *pConteudo))
GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo *ppGrafo);


/* Construir grafo */
GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo, char *pNomeVertice, void *pValor);
/* Ao criar a aresta, lembrar de inserir a aresta entre os sucessores da origem, e o vertice entre os antecessores do destino */
GRA_tpCondRet GRA_InserirArestaDoCorrentePara(GRA_tppGrafo pGrafo, char *nomeAresta, char *nomeVerticeDestino)

/* Destruir grafo */
GRA_tpCondRet GRA_DestruirVerticeCorrente(GRA_tppGrafo pGrafo);
GRA_tpCondRet GRA_DestruirArestaAdjacente(GRA_tppGrafo pGrafo, char *pNomeAresta);

/* Outros */
GRA_tpCondRet GRA_TornarCorrenteUmaOrigem(GRA_tppGrafo pGrafo);

/* Navega�ao */
GRA_tpCondRet GRA_IrParaVerticeAdjacente(GRA_tppGrafo pGrafo, char *nomeVertice);
GRA_tpCondRet GRA_SeguirPelaAresta(GRA_tppGrafo pGrafo, char *nomeAresta);
GRA_tpCondRet GRA_IrParaAOrigem(GRA_tppGrafo pGrafo, char *nomeVertice);

/* Obter e alterar */
GRA_tpCondRet GRA_ObterConteudoCorrente(GRA_tppGrafo pGrafo, void **ppValor);
GRA_tpCondRet GRA_AlterarConteudoCorrente(GRA_tppGrafo pGrafo, void *pValor);

/***********************************************************************/
#undef GRAFO_EXT

/********** Fim do m�dulo de defini��o: GRA Grafo direcionado **********/

#else
#endif
