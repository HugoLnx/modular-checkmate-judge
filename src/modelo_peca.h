#if ! defined( MODELO_PECA_ )
#define MODELO_PECA_
/***************************************************************************
*
*  M�dulo de defini��o: MPEC  Modelo de Pe�a
*
*  Arquivo gerado:              modelo_peca.h
*  Letras identificadoras:      MPEC
*
*	Autores:
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Manipula��o b�sica de modelo de pe�a
*
*  Descri��o do m�dulo
*     M�dulo respons�vel por manipular os elementos que comp�e um modelo de pe�a.
*
***************************************************************************/

#if defined( MODELO_PECA_OWN )
#define MODELO_PECA_EXT
#else
#define MODELO_PECA_EXT extern
#endif

#include "lista.h"

/***********************************************************************
*
*  Tipo de dados: MPEC Tipos de movimentos
*
*
*  Descri��o do tipo
*     Tipos de movimento da pela.
*
***********************************************************************/
typedef enum {
   ANDA = 0,
      /* Pe�a pode comer qualquer pe�a em seu caminho */

   VOA = 1
      /*`Pe�a s� pode comer se a pela estiver na �ltima casa
         de seu caminho */
} MPEC_tpTipoMovimento;



/***********************************************************************
*
*  Tipo de dados: MPEC Condi��es de retorno
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es exportadas.
*
***********************************************************************/
typedef enum {

   MPEC_CondRetOK,
   /* Executou correto */
      
   MPEC_CondRetFaltouMemoria,
   /* Faltou mem�ria ao alocar dados */

   MPEC_CondRetNaoAlterou,
   /* N�o foi possivel alterar a peca */

   MPEC_CondRetModeloNaoExiste
   /* Pe�a n�o existe */

} MPEC_tpCondRet ;


/* Tipo refer�ncia para um Modelo de Pe�a */
typedef struct MPEC_stModeloPeca* MPEC_tppModeloPeca;

/***********************************************************************
*
*  Fun��o: MPEC Criar modelo pe�a
*
*  Descri��o
*     Cria inst�ncia de um modelo pe�a.
*
*  Par�metros
*     ppModelo      - Refer�ncia para retornar a nova inst�ncia
*     nome          - nome do modelo
*     pPassos       - lista de passos do modelo
*     tipoMovimento - tipo de movimento do modelo
*
*  Condi��es de retorno
*     MPEC_CondRetOK
*     MPEC_CondRetFaltouMemoria
*
*  Retorno por refer�ncia
*     ppModelo - Retorna a nova inst�ncia.
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da lista para pPassos.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais do modelo de pe�a.
*
***********************************************************************/
MPEC_tpCondRet MPEC_CriarModeloPeca(MPEC_tppModeloPeca *ppModelo, char* nome, LIS_tppLista pPassos, MPEC_tpTipoMovimento tipoMovimento);

/***********************************************************************
*
*  Fun��o: MPEC Destruir modelo de pe�a
*
*  Descri��o
*     Destroi uma inst�ncia de modelo de pe�a.
*
*  Par�metros
*     ppModelo - Modelo que ser� destruido.
*
*  Condi��es de retorno
*     MPEC_CondRetOK
*
*  Retorno por refer�ncia
*     ppModelo retorna NULL.
*
*  Assertivas de entrada
*     Valem as assertivas estruturais do modelo de pe�a.
*
*  Assertivas de saida
*     ppModelo aponta para NULL.
*
***********************************************************************/
MPEC_tpCondRet MPEC_DestruirModeloPeca(MPEC_tppModeloPeca *ppModelo);

/***********************************************************************
*
*  Fun��o: MPEC Alterar modelo de pe�a
*
*  Descri��o
*     Altera os elementos do modelo de pe�a.
*
*  Par�metros
*     pModelo           - Modelo que ser� alterado.
*     novoNome          - novo nome do modelo
*     pPassos           - nova lista de passos do modelo
*     novoTipoMovimento - novo tipo de movimento do modelo
*
*  Condi��es de retorno
*     MPEC_CondRetOK
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do modelo de pe�a.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais do modelo de pe�a.
*
***********************************************************************/
MPEC_tpCondRet MPEC_AlterarModeloPeca(MPEC_tppModeloPeca pModelo, char *novoNome, LIS_tppLista pPassos, MPEC_tpTipoMovimento novoTipoMovimento);


/***********************************************************************
*
*  Fun��o: MPEC Obter nome
*
*  Descri��o
*     Recupera o nome do modelo de pe�a.
*
*  Par�metros
*     pModeloParm - Modelo que ser� usado.
*     pNome       - Refer�ncia que ser� usada para retornar o nome.
*
*  Condi��es de retorno
*     MPEC_CondRetOK
*     MPEC_CondRetModeloNaoExiste
*
*  Retorno por refer�ncia
*     pNome - Retorna o nome relacionado ao modelo.
*
*  Assertivas de entrada
*     - pNome � um ponteiro v�lido.
*
*  Assertivas de saida
*     - Modelo n�o muda.
*     - pNome aponta para o nome do modelo.
*
***********************************************************************/
MPEC_tpCondRet MPEC_ObterNome(MPEC_tppModeloPeca pModelo, char **pNome);

/***********************************************************************
*
*  Fun��o: MPEC Obter passos
*
*  Descri��o
*     Recupera os passos do modelo de pe�a.
*
*  Par�metros
*     pModeloParm - Modelo que ser� usado.
*     ppPassos       - Refer�ncia que ser� usada para retornar a lista de passos.
*
*  Condi��es de retorno
*     MPEC_CondRetOK
*     MPEC_CondRetModeloNaoExiste
*
*  Retorno por refer�ncia
*     pPassos - Retorna a lista de passos relacionada ao modelo.
*
*  Assertivas de entrada
*     - ppPassos � um ponteiro v�lido.
*
*  Assertivas de saida
*     - Modelo n�o muda.
*     - ppPassos aponta para a lista de passos do modelo.
*
***********************************************************************/
MPEC_tpCondRet MPEC_ObterPassos(MPEC_tppModeloPeca pModeloParm, LIS_tppLista *ppPassos);

/***********************************************************************
*
*  Fun��o: MPEC Obter tipo de movimento
*
*  Descri��o
*     Recupera os passos do modelo de pe�a.
*
*  Par�metros
*     pModeloParm - Modelo que ser� usado.
*     pTipo       - Refer�ncia que ser� usada para retornar o tipo.
*
*  Condi��es de retorno
*     MPEC_CondRetOK
*     MPEC_CondRetModeloNaoExiste
*
*  Retorno por refer�ncia
*     pTipo - Retorna o tipo relacionado ao modelo.
*
*  Assertivas de entrada
*     - pTipo � um ponteiro v�lido.
*
*  Assertivas de saida
*     - Modelo n�o muda.
*     - pTipo aponta para o tipo do modelo.
*
***********************************************************************/
MPEC_tpCondRet MPEC_ObterTipo(MPEC_tppModeloPeca pModeloParm, MPEC_tpTipoMovimento *pTipo);

/***********************************************************************
*
*  Fun��o: MPEC Salvar pe�a
*
*  Descri��o
*     Alimenta o arquivo com uma serializa��o em texto do modelo de pe�a.
*
*  Par�metros
*     pModeloPeca      - Modelo de pe�a que ser� usado.
*     pFile            - Arquivo que ser� incrementado.
*
*  Condi��es de retorno
*     MPEC_CondRetOK
*     MPEC_CondRetModeloNaoExiste
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do modelo de pe�a.
*     - Arquivo est� aberto em modo de escrita.
*
*  Assertivas de saida
*     - Modelo de pe�a n�o foi alterado.
*     - Arquivo cont�m uma serializa��o do modelo de pe�a no final.
*
***********************************************************************/
MPEC_tpCondRet MPEC_Salvar(MPEC_tppModeloPeca pModeloPeca, FILE *pFile);

/***********************************************************************
*
*  Fun��o: MPEC Salvar pe�a
*
*  Descri��o
*     Alimenta o arquivo com uma serializa��o em texto dos modelos de pe�a.
*
*  Par�metros
*     ppModelosPeca      - Modelos de pe�a que ser�o usados.
*     pFile              - Arquivo que ser� incrementado.
*
*  Condi��es de retorno
*     MPEC_CondRetOK
*     MPEC_CondRetModeloNaoExiste
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do modelo de pe�a.
*     - Valem as assertivas estruturais da lista.
*     - Arquivo est� aberto em modo de escrita.
*
*  Assertivas de saida
*     - Nenhum modelo de pe�a n�o foi alterado.
*     - Arquivo cont�m uma serializa��o dos modelos de pe�a no final.
*
***********************************************************************/
MPEC_tpCondRet MPEC_SalvarLista(LIS_tppLista ppModelosPeca, FILE *pFile);

#undef MODELO_PECA_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
