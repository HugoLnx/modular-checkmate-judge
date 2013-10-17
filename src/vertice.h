#if ! defined( VERTICE_ )
#define VERTICE_
/***************************************************************************
*
*  M�dulo de defini��o: VER  Conte�do do m�dulo
*
*  Arquivo gerado:              vertice.h
*  Letras identificadoras:      VER
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

#if defined( VERTICE_OWN )
#define VERTICE_EXT
#else
#define VERTICE_EXT extern
#endif


/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um conteudo */

typedef struct VER_stConteudo * VER_tppConteudo;


/***********************************************************************
*
*  Tipo de dados: VER Condi��es de retorno
*
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es do conteudo
*
***********************************************************************/

typedef enum {

	VER_CondRetOK,
	    /* Concluiu corretamente */

	VER_CondRetConteudoNaoExiste,
	    /* Conte�do n�o foi criado */

	VER_CondRetFaltouMemoria
	    /* Faltou mem�ria ao tentar alocar algo */

} VER_tpCondRet;


/***********************************************************************
*
*  Fun��o: VER Criar conteudo
*
*  Descri��o
*     Cria uma inst�ncia da estrutura.
*
*  Par�metros
*     ppConteudo - Refer�ncia usada para retorno do conte�do que ser� criado.
*     pValor     - Valor que ser� atribuido � estrutura.
*
*  Condi��es de retorno
*     - VER_CondRetOK
*     - VER_CondRetFaltouMemoria
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
VER_tpCondRet VER_CriarConteudo(VER_tppConteudo *ppConteudo, char *pValor);

/***********************************************************************
*
*  Fun��o: VER Destruir conte�do
*
*  Descri��o
*     Destroi uma inst�ncia da estrutura liberando seu espa�o na mem�ria.
*
*  Par�metros
*     ppConteudo - Refer�ncia para o ponteiro do conte�do � ser destruido.
*     pValor     - Valor que ser� atribuido � estrutura.
*
*  Condi��es de retorno
*     - VER_CondRetOK
* 
*  Retorno por refer�ncia
*     Refer�ncia para NULL.
*
*  Assertivas de entrada
*     - ppConteudo referencia para uma inst�ncia da estrutura VER_stConteudo.
*
*  Assertivas de saida
*     - A refer�ncia ser� sempre nula.
*     - O conte�do e seu valor foram liberados da mem�ria
*
***********************************************************************/
VER_tpCondRet VER_DestruirConteudo(VER_tppConteudo *ppConteudo);

/***********************************************************************
*
*  Fun��o: VER Obter valor do conte�do
*
*  Descri��o
*     Recupera o valor da inst�ncia de conte�do
*
*  Par�metros
*     pConteudoParm  - Refer�ncia para o conte�do.
*     ppValor        - Refer�ncia usada para retorno do valor.
*
*  Condi��es de retorno
*     - VER_CondRetOK
*     - VER_CondRetConteudoNaoExiste
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
VER_tpCondRet VER_ObterValorDoConteudo(VER_tppConteudo pConteudoParm, char **ppValor);

/***********************************************************************
*
*  Fun��o: VER Alterar valor do conte�do
*
*  Descri��o
*     Substitui o valor da inst�ncia de conte�do por uma nova.
*
*  Par�metros
*     pConteudoParm  - Refer�ncia para o conte�do.
*     pValor         - Refer�ncia para o novo valor do conte�do.
*
*  Condi��es de retorno
*     - VER_CondRetOK
*     - VER_CondRetConteudoNaoExiste
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
VER_tpCondRet VER_AlterarValorDoConteudo(VER_tppConteudo pConteudoParm, char *pValor);

/********** Fim do m�dulo de defini��o: VER Conteudo **********/

#endif