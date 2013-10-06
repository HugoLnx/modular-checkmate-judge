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
*     ppConteudo - Refer�ncia usada para retorno do conte�do que ser� criado.
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
*     - ppConteudo n�o cont�m um Conte�do criado anteriormente.
*
*  Assertivas de saida
*     - Ser� um conte�do com valor igual ao passado por par�metro.
*
***********************************************************************/
CON_tpCondRet CON_CriarConteudo(CON_tppConteudo *ppConteudo, char *pValor);

/***********************************************************************
*
*  Fun��o: CON Destruir conte�do
*
*  Descri��o
*     Destroi uma inst�ncia da estrutura liberando seu espa�o na mem�ria.
*
*  Par�metros
*     ppConteudo - Refer�ncia para o ponteiro do conte�do � ser destruido.
*     pValor     - Valor que ser� atribuido � estrutura.
*
*  Condi��es de retorno
*     - CON_CondRetOK
* 
*  Retorno por refer�ncia
*     Refer�ncia para NULL.
*
*  Assertivas de entrada
*     - ppConteudo referencia para uma inst�ncia da estrutura CON_stConteudo.
*
*  Assertivas de saida
*     - A refer�ncia ser� sempre nula.
*     - O conte�do e seu valor foram liberados da mem�ria
*
***********************************************************************/
CON_tpCondRet CON_DestruirConteudo(CON_tppConteudo *ppConteudo);

/***********************************************************************
*
*  Fun��o: CON Obter valor do conte�do
*
*  Descri��o
*     Recupera o valor da inst�ncia de conte�do
*
*  Par�metros
*     pConteudoParm  - Refer�ncia para o conte�do.
*     ppValor        - Refer�ncia usada para retorno do valor.
*
*  Condi��es de retorno
*     - CON_CondRetOK
*     - CON_CondRetConteudoNaoExiste
* 
*  Retorno por refer�ncia
*     ppValor   - Valor do conte�do.
*
*  Assertivas de entrada
*     <n�o tem>
*
*  Assertivas de saida
*     - Ser� retornado o valor do conte�do.
*
***********************************************************************/
CON_tpCondRet CON_ObterValorDoConteudo(CON_tppConteudo pConteudoParm, char **ppValor);

/***********************************************************************
*
*  Fun��o: CON Alterar valor do conte�do
*
*  Descri��o
*     Substitui o valor da inst�ncia de conte�do por uma nova.
*
*  Par�metros
*     pConteudoParm  - Refer�ncia para o conte�do.
*     pValor         - Refer�ncia para o novo valor do conte�do.
*
*  Condi��es de retorno
*     - CON_CondRetOK
*     - CON_CondRetConteudoNaoExiste
* 
*  Retorno por refer�ncia
*     <n�o tem>
*
*  Assertivas de entrada
*     <n�o tem>
*
*  Assertivas de saida
*     - S� o valor do conte�do ser� alterado.
*
***********************************************************************/
CON_tpCondRet CON_AlterarValorDoConteudo(CON_tppConteudo pConteudoParm, char *pValor);

/********** Fim do m�dulo de defini��o: CON Conteudo **********/

#endif