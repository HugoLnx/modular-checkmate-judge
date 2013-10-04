#if ! defined( CONTEUDO_ )
#define CONTEUDO_
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
 
#if defined( CONTEUDO_OWN )
   #define CONTEUDO_EXT
#else
   #define CONTEUDO_EXT extern
#endif


/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um conteudo */

typedef struct CON_tpConteudo * CON_tppConteudo;


/***********************************************************************
*
*  Tipo de dados: CON Condi��es de retorno
*
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es do conteudo
*
***********************************************************************/

typedef enum {

	CON_CondRetOK ,
		/* Concluiu corretamente */

	CON_CondRetGrafoVazia ,
		/* A grafo n�o cont�m elementos */

	CON_CondRetNaoAchou ,
		/* N�o encontrou o valor procurado */

	CON_CondRetFaltouMemoria
		/* Faltou mem�ria ao tentar alocar algo */

} CON_tpCondRet ;


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

CON_tpCondRet CON_CriarConteudo(CON_tppConteudo *ppConteudo, char *pValor);
CON_tpCondRet CON_DestruirConteudo(CON_tppConteudo *ppConteudo);
CON_tpCondRet CON_ObterValorDoConteudo(CON_tppConteudo ppConteudo, char **ppValor);
CON_tpCondRet CON_AlterarValorDoConteudo(CON_tppConteudo *ppConteudo, char *pValor);

/********** Fim do m�dulo de defini��o: CON Conteudo **********/

#endif