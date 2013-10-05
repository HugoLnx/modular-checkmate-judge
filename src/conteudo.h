#if ! defined( CONTEUDO_ )
#define CONTEUDO_
/***************************************************************************
*
*  M�dulo de defini��o: CON  Conte�do do m�dulo
*
*  Arquivo gerado:              conteudo.h
*  Letras identificadoras:      CON
*
*	Autores:
*     - Hugo Roque: hg
*     - Robert Corr�a: rc
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data        Observa��es
*     1.0     rc       02/out/13   Cria��o do m�dulo e as opera��es b�sicas.
*     1.1     hg       05/out/13   Checagem de erros caso o conte�do n�o tenha sido criado.
*
*  Descri��o do m�dulo
*     M�dulo extremamente simples que representa o conte�do utilizado pelo grafo.
*
***************************************************************************/
 
#if defined( CONTEUDO_OWN )
   #define CONTEUDO_EXT
#else
   #define CONTEUDO_EXT extern
#endif


/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um conteudo */

typedef struct CON_stConteudo * CON_tppConteudo;


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

	CON_CondRetConteudoNaoExiste ,
		/* Conte�do n�o foi criado */

	CON_CondRetFaltouMemoria
		/* Faltou mem�ria ao tentar alocar algo */

} CON_tpCondRet ;


/***********************************************************************
*
*  Fun��o: CON Criar conteudo
*
*  Descri��o
*     Cria uma inst�ncia da estrutura.
*
*  Par�metros
*     ppConteudo - Refer�ncia para o ponteiro do conte�do que ser� criado.
*     pValor     - Valor que ser� atribuido � estrutura.
*
*  Condi��es de retorno
*     - CON_CondRetOK
*     - CON_CondRetFaltouMemoria
* 
*  Retorno por refer�ncia
*     Ponteiro para o conte�do que ser� criado.
*
*  Assertivas de entrada
*     ppConteudo n�o cont�m um Conte�do criado anteriormente.
*
*  Assertivas de saida
*     <assertivas de saida>
*
*  Requisitos
*     <lista de requisitos>
*
*  Hip�teses
*     N�o � necess�rio validar se ppConteudo cont�m j� um conte�do
*     pois s� � permitido passar um ppConteudo sem conte�do.
*
*  Restri��es
*     <lista de restri��es>
*
***********************************************************************/
CON_tpCondRet CON_CriarConteudo(CON_tppConteudo *ppConteudo, char *pValor);
CON_tpCondRet CON_DestruirConteudo(CON_tppConteudo *ppConteudo);
CON_tpCondRet CON_ObterValorDoConteudo(CON_tppConteudo pConteudoParm, char **ppValor);
CON_tpCondRet CON_AlterarValorDoConteudo(CON_tppConteudo pConteudoParm, char *pValor);

/********** Fim do m�dulo de defini��o: CON Conteudo **********/

#endif