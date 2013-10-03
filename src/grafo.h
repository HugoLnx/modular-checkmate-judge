#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  Módulo de definição: <abreviação>  <estrutura manipulada pelo módulo>
*
*  Arquivo gerado:              <nome-do-arquivo>.h
*  Letras identificadoras:      <abreviação>
*
*	Autores:
*     - <nick>: <nome>
*     - <nick>: <nome>
*
*  Histórico de evolução:
*     Versão  Autor    Data        Observações
*     1       <nick>   <data>      <observações>
*
*  Descrição do módulo
*     <descrição do módulo>
*
***************************************************************************/
 
#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */

typedef struct GRA_stGrafo * GRA_tppGrafo ;


/***********************************************************************
*
*  Tipo de dados: GRA Condições de retorno
*
*
*  Descrição do tipo
*     Condições de retorno das funções do grafo
*
***********************************************************************/

typedef enum {

	GRA_CondRetOK ,
		/* Concluiu corretamente */

	GRA_CondRetGrafoVazia ,
		/* A grafo não contém elementos */

	GRA_CondRetNaoAchou ,
		/* Não encontrou o valor procurado */

	GRA_CondRetFaltouMemoria
		/* Faltou memória ao tentar alocar algo */

} GRA_tpCondRet ;



/***********************************************************************
*
*  Função: <abreviacao do modulo> <nome da funcao por extenso>
*
*  Descrição
*     <descricao da função>
*
*  Parâmetros
*     <param 1>      - <explicação sobre parametro 1>
*     <parametro 2>  - <explicação sobre parametro 2>
*
*  Retorno
*     <descricao do retorno, listar os possíveis tpCondRet>
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

/* Navegaçao */
GRA_tpCondRet GRA_IrParaVerticeAdjacente(GRA_tppGrafo pGrafo, char *nomeVertice);
GRA_tpCondRet GRA_SeguirPelaAresta(GRA_tppGrafo pGrafo, char *nomeAresta);
GRA_tpCondRet GRA_IrParaAOrigem(GRA_tppGrafo pGrafo, char *nomeVertice);

/* Obter e alterar */
GRA_tpCondRet GRA_ObterConteudoCorrente(GRA_tppGrafo pGrafo, void **ppValor);
GRA_tpCondRet GRA_AlterarConteudoCorrente(GRA_tppGrafo pGrafo, void *pValor);

/***********************************************************************/
#undef GRAFO_EXT

/********** Fim do módulo de definição: GRA Grafo direcionado **********/

#else
#endif
