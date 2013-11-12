#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  M�dulo de defini��o: PEC  Pe�a
*
*  Arquivo gerado:              peca.h
*  Letras identificadoras:      PEC
*
*	Autores:
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Fun��es para manipula��o da pe�a.
*
*  Descri��o do m�dulo
*     M�dulo respons�vel pela manipula��o das estruturas que comp�es uma pe�a.
*
***************************************************************************/

#if defined( PECA_OWN )
#define PECA_EXT
#else
#define PECA_EXT extern
#endif

#include "lista.h"
#include "modelo_peca.h"


/***********************************************************************
*
*  Tipo de dados: PEC Time da pe�a
*
*
*  Descri��o do tipo
*     Define qual o time que a pe�a estar� participando.
*
***********************************************************************/

typedef enum {
   ALIADA = 0,
   INIMIGA = 1
} PEC_tpTimePeca;


/***********************************************************************
*
*  Tipo de dados: PEC Condi��es de retorno
*
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es exportadas.
*
***********************************************************************/
typedef enum {

   PEC_CondRetOK,
   /* Executou correto */
      
   PEC_CondRetFaltouMemoria,
   /* Faltou mem�ria ao alocar dados */

   PEC_CondRetNaoAlterou,
   /* N�o foi possivel alterar a peca */

   PEC_CondRetPecaNaoExiste
   /* Pe�a n�o existe */

} PEC_tpCondRet;


/* Tipo refer�ncia para uma Pe�a */
typedef struct PEC_stPeca* PEC_tppPeca;

/***********************************************************************
*
*  Fun��o: PEC Criar pe�a
*
*  Descri��o
*     Cria inst�ncia de pe�a.
*
*  Par�metros
*     ppPeca         - Refer�ncia para retornar a nova inst�ncia.
*     pModelo        - Modelo da pe�a.
*     time           - Time da pe�a.
*
*  Condi��es de retorno
*     PEC_CondRetOK
*     PEC_CondRetFaltouMemoria
*
*  Retorno por refer�ncia
*     ppPeca - retorna a nova inst�ncia criada.
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do modelo pe�a.
*     - ppPeca � um ponteiro v�lido.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais da Pe�a.
*
***********************************************************************/
PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca *ppPeca, MPEC_tppModeloPeca pModelo, PEC_tpTimePeca time);


/***********************************************************************
*
*  Fun��o: PEC Destruir pe�a
*
*  Descri��o
*     Destroi inst�ncia de pe�a.
*
*  Par�metros
*     ppPeca         - Refer�ncia para pe�a.
*
*  Condi��es de retorno
*     PEC_CondRetOK
*
*  Retorno por refer�ncia
*     ppPeca - Retorna NULL
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da pe�a.
*
*  Assertivas de saida
*     - Pe�a foi liberada da mem�ria.
*     - ppPeca aponta para NULL.
*
***********************************************************************/
PEC_tpCondRet PEC_DestruirPeca(PEC_tppPeca *ppPeca);


/***********************************************************************
*
*  Fun��o: PEC Criar rei
*
*  Descri��o
*     Cria uma inst�ncia de pe�a especial, o rei.
*
*  Par�metros
*     ppPeca - Refer�ncia usada para retornar a nova inst�ncia.
*
*  Condi��es de retorno
*     PEC_CondRetOK
*     PEC_CondRetFaltouMemoria
*
*  Retorno por refer�ncia
*     ppPeca - retorna a nova inst�ncia criada.
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do modelo pe�a.
*     - ppPeca � um ponteiro v�lido.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais da Pe�a.
*     - Pe�a tem modelo NULL.
*
***********************************************************************/
PEC_tpCondRet PEC_CriarRei(PEC_tppPeca *ppPeca);

/***********************************************************************
*
*  Fun��o: PEC Destruir rei
*
*  Descri��o
*     Destroi inst�ncia de rei.
*
*  Par�metros
*     ppPeca         - Refer�ncia para a pe�a.
*
*  Condi��es de retorno
*     PEC_CondRetOK
*
*  Retorno por refer�ncia
*     ppPeca - Retorna NULL
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da pe�a.
*     - Pe�a tem modelo NULL
*
*  Assertivas de saida
*     - Pe�a foi liberada da mem�ria.
*     - ppPeca aponta para NULL.
*
***********************************************************************/
PEC_tpCondRet PEC_DestruirRei(PEC_tppPeca *ppPeca);


/***********************************************************************
*
*  Fun��o: PEC Alterar modelo pe�a
*
*  Descri��o
*     <descricao da fun��o>
*
*  Par�metros
*     pPeca       - Pe�a que ser� alterada.
*     pNovoModelo - Modelo que ser� adicionado � pe�a.
*
*  Condi��es de retorno
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da pe�a.
*     - Valem as assertivas estruturais do modelo pe�a.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais da Pe�a.
*
***********************************************************************/
PEC_tpCondRet PEC_AlterarModeloPeca(PEC_tppPeca pPeca, MPEC_tppModeloPeca pNovoModelo);


/***********************************************************************
*
*  Fun��o: PEC � o rei
*
*  Descri��o
*     Verifica se pe�a � rei.
*
*  Par�metros
*     pPecaParm    - Pe�a que ser� verificada.
*     ehRei        - Refer�ncia usada para retornar a resposta.
*
*  Condi��es de retorno
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
*  Retorno por refer�ncia
*     ehRei - Ser� 1 caso seja rei e 0 caso n�o seja.
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da pe�a.
*     - ehRei � um ponteiro v�lido.
*
*  Assertivas de saida
*     - Pe�a n�o � alterada.
*     - ehRei � 1 caso seja rei e 0 caso n�o seja.
*
***********************************************************************/
PEC_tpCondRet PEC_EhORei(PEC_tppPeca pPecaParm, int *ehRei);

/***********************************************************************
*
*  Fun��o: PEC Obter modelo
*
*  Descri��o
*     Recupera o modelo da pe�a;
*
*  Par�metros
*     pPecaParm    - Pe�a que ser� usada.
*     ppModelo     - Refer�ncia usada para retornar o modelo.
*
*  Condi��es de retorno
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
*  Retorno por refer�ncia
*     ppModelo - retorna o modelo da pe�a.
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da pe�a.
*
*  Assertivas de saida
*     - Pe�a n�o � alterada.
*     - Valem as assertivas estruturais do modelo.
*
***********************************************************************/
PEC_tpCondRet PEC_ObterModelo(PEC_tppPeca pPecaParm, MPEC_tppModeloPeca *ppModelo);


/***********************************************************************
*
*  Fun��o: PEC Obter time
*
*  Descri��o
*     Recupera o modelo da pe�a;
*
*  Par�metros
*     pPecaParm    - Pe�a que ser� usada.
*     pTime        - Refer�ncia usada para retornar o time.
*
*  Condi��es de retorno
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
*  Retorno por refer�ncia
*     pTime - retorna o time da pe�a.
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da pe�a.
*
*  Assertivas de saida
*     - Pe�a n�o � alterada.
*
***********************************************************************/
PEC_tpCondRet PEC_ObterTime(PEC_tppPeca pPecaParm, PEC_tpTimePeca *pTime);


/***********************************************************************
*
*  Fun��o: PEC Salvar pe�a
*
*  Descri��o
*     Alimenta o arquivo com uma serializa��o em texto da pe�a.
*
*  Par�metros
*     pPeca      - Pe�a que ser� usada.
*     pFile      - Arquivo que ser� incrementado.
*
*  Condi��es de retorno
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da pe�a.
*     - Arquivo est� aberto em modo de escrita.
*
*  Assertivas de saida
*     - Pe�a n�o foi alterada.
*     - Arquivo cont�m uma serializa��o da pe�a no final.
*
***********************************************************************/
PEC_tpCondRet PEC_SalvarPeca(PEC_tppPeca pPeca, FILE* pFile);


#undef PECA_EXT

/********** Fim do m�dulo de defini��o: M�dulo Pe�a **********/

#else
#endif
