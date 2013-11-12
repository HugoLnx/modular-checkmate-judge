#if !defined(PASSO_)
#define PASSO_
/***************************************************************************
*
*  M�dulo de defini��o: PAS  Passo
*
*  Arquivo gerado:              passo.h
*  Letras identificadoras:      PAS
*
*	Autores:
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Manipula��o b�sica de passo
*
*  Descri��o do m�dulo
*     M�dulo respons�vel por manipular a estrutura Passo.
*
***************************************************************************/
 
#if defined( PASSO_OWN )
   #define PASSO_EXT
#else
   #define PASSO_EXT extern
#endif

#include "lista.h"
#include "direcao.h"

/* Tipo refer�ncia para um Passo */
typedef struct PAS_stPasso* PAS_tppPasso;


/***********************************************************************
*
*  Tipo de dados: PAS Condi��es de retorno
*
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es exportadas.
*
***********************************************************************/
   typedef enum {

         PAS_CondRetOK = 0,
               /* Executou correto */

         PAS_CondRetPassoNaoExiste = 3,
               /* Passo n�o existe */

         PAS_CondRetFaltouMemoria = 5
               /* Faltou mem�ria ao alocar dados */

   } PAS_tpCondRet;


/***********************************************************************
*
*  Fun��o: PAS Criar passo
*
*  Descri��o
*     Cria uma inst�ncia de passo.
*
*  Par�metros
*     ppPasso     - Refer�ncia para retorno da nova inst�ncia.
*     direcao     - Dire��o do passo
*     quantidade  - Quantidade de locomo��o deste passo.
*
*  Condi��es de retorno
*     PAS_CondRetOK
*     PAS_CondRetFaltaMemoria
*
*  Retorno por refer�ncia
*     ppPasso - Retorna a nova inst�ncia.
*
*  Assertivas de entrada
*     - ppPasso � um ponteiro v�lido.
*
*  Assertivas de saida
*     - ppPasso aponta para um passo.
*
***********************************************************************/
   PAS_tpCondRet PAS_CriarPasso(PAS_tppPasso *ppPasso, DIR_tpDirecao direcao, int quantidade);


/***********************************************************************
*
*  Fun��o: PAS Destruir passo
*
*  Descri��o
*     Destruir inst�ncia de passo.
*
*  Par�metros
*     ppPasso   - Refer�ncia para o passo � ser destruido.
*
*  Condi��es de retorno
*     PAS_CondRetOK
*
*  Retorno por refer�ncia
*     ppPasso retorna NULL
*
*  Assertivas de entrada
*     ppPasso � NULL ou aponta para um passo v�lido.
*
*  Assertivas de saida
*     ppPasso aponta para NULL.
*
***********************************************************************/
   PAS_tpCondRet PAS_DestruirPasso(PAS_tppPasso *ppPasso);


/***********************************************************************
*
*  Fun��o: PAS Comparar passos
*
*  Descri��o
*     Compara dois passos e verifica se s�o iguais.
*
*  Par�metros
*     pPasso1, pPasso2 - Passos � serem comparados
*     pResposta        - Refer�ncia � ser usada para retornar a resposta.
*
*  Condi��es de retorno
*     PAS_CondRetOK
*     PAS_CondRetPassoNaoExiste
*
*  Retorno por refer�ncia
*     pResposta - Retorna 1 caso os passos sejam iguais e 0 caso contr�rio.
*
*  Assertivas de entrada
*     - pResposta � um ponteiro v�lido.
*
*  Assertivas de saida
*     - pResposta aponta para 1 caso sejam iguais e 0 caso n�o sejam.
*
***********************************************************************/
   PAS_tpCondRet PAS_CompararPassos(PAS_tppPasso pPasso1, PAS_tppPasso pPasso2, int *pResposta);



/***********************************************************************
*
*  Fun��o: PAS Obter quantidade
*
*  Descri��o
*     Recupera a quantidade de locomo��o do passo.
*
*  Par�metros
*     pPassoParm - Passo que ser� usado.
*     pQuantidade - Refer�ncia que ser� usada para retornar a quantidade.
*
*  Condi��es de retorno
*     PAS_CondRetOK
*     PAS_CondRetPassoNaoExiste
*
*  Retorno por refer�ncia
*     pQuantidade - Retorna a quantidade relacionada � pe�a.
*
*  Assertivas de entrada
*     - pQuantidade � um ponteiro v�lido.
*
*  Assertivas de saida
*     - Passo n�o muda.
*     - pQuantidade aponta para um n�mero representando a quantidade
*       relativa ao passo.
*
***********************************************************************/
   PAS_tpCondRet PAS_ObterQuantidade(PAS_tppPasso pPassoParm, int *pQuantidade);


/***********************************************************************
*
*  Fun��o: PAS Obter dire��o
*
*  Descri��o
*     Recupera a dire��o do passo.
*
*  Par�metros
*     pPassoParm - Passo que ser� usado.
*     pDirecao - Refer�ncia que ser� usada para retornar a dire��o.
*
*  Condi��es de retorno
*     PAS_CondRetOK
*     PAS_CondRetPassoNaoExiste
*
*  Retorno por refer�ncia
*     pDire��o - Retorna a dire��o relacionada � pe�a.
*
*  Assertivas de entrada
*     - pDire��o � um ponteiro v�lido.
*
*  Assertivas de saida
*     - Passo n�o muda.
*     - pDire��o aponta para um n�mero representando a quantidade
*       relativa ao passo.
*
***********************************************************************/
   PAS_tpCondRet PAS_ObterDirecao(PAS_tppPasso pPassoParm, DIR_tpDirecao *pDirecao);


/***********************************************************************
*
*  Fun��o: PAS � infinito
*
*  Descri��o
*     Verifica se a quantidade de locomo��o do passo � "infinita", ou seja,
*     at� algum obstaculo externo ocorrer.
*
*  Par�metros
*     pPassoParm  - Passo que ser� usado.
*     pEhInfinito - Refer�ncia que ser� usada para retornar a resposta.
*
*  Condi��es de retorno
*     PAS_CondRetOK
*     PAS_CondRetPassoNaoExiste
*
*  Retorno por refer�ncia
*     pEhInfinito - Retorna 1 caso a quantidade seja infinita e 0 caso contr�rio.
*
*  Assertivas de entrada
*     - pEhInfinito � um ponteiro v�lido.
*
*  Assertivas de saida
*     - Passo n�o muda.
*     - pEhInfinito aponta para 1 caso a quantidade seja infinita e 0 caso contr�rio.
*
***********************************************************************/
   PAS_tpCondRet PAS_EhInfinito(PAS_tppPasso pPassoParm, int *pEhInfinito);


/***********************************************************************
*
*  Fun��o: PAS Salvar passo
*
*  Descri��o
*     Alimenta o arquivo com uma serializa��o em texto do passo.
*
*  Par�metros
*     pPasso     - Passo que ser� usado.
*     pFile      - Arquivo que ser� incrementado.
*
*  Condi��es de retorno
*     PAS_CondRetOK
*     PAS_CondRetPassoNaoExiste
*
*  Assertivas de entrada
*     - Arquivo est� aberto em modo de escrita.
*
*  Assertivas de saida
*     - Passo n�o foi alterado.
*     - Arquivo cont�m uma serializa��o do passo no final.
*
***********************************************************************/
   PAS_tpCondRet PAS_Salvar(LIS_tppLista ppPassos, FILE* pFile);


#undef PASSO_EXT

/********** Fim do m�dulo de defini��o: M�dulo Passo **********/

#else
#endif
