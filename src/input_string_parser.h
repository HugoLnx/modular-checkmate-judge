#if ! defined( INPUT_STRING_PARSER_ )
#define INPUT_STRING_PARSER_
/***************************************************************************
*
*  M�dulo de defini��o: ISP  Input String Parser
*
*  Arquivo gerado:              input_string_parser.h
*  Letras identificadoras:      ISP
*
*	Autores:
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Parseia alguns tipos b�sicos
*
*  Descri��o do m�dulo
*     M�dulo respons�vel por parsear representa��es de string para as inst�ncias
*     das estruturas.
*
***************************************************************************/
 
#if defined( INPUT_STRING_PARSER_OWN )
   #define INPUT_STRING_PARSER_EXT
#else
   #define INPUT_STRING_PARSER_EXT extern
#endif

#include "lista.h"
#include "modelo_peca.h"

/***** Declara��es exportadas pelo m�dulo *****/


/***********************************************************************
*
*  Tipo de dados: ISP Condi��es de retorno
*
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es exportadas.
*
***********************************************************************/

typedef enum {

   ISP_CondRetOK,
      /* Concluiu corretamente */

   ISP_CondRetNaoReconhecido,
      /* A entrada n�o foi reconhecida */

   ISP_CondRetFaltouMemoria,
      /* Faltou mem�ria ao tentar alocar algo */
 
} ISP_tpCondRet;

/***********************************************************************
*
*  Fun��o: ISP Ler tipo movimento
*
*  Descri��o
*     Recebe uma representa��o string do tipo de movimento e
*     retorna o tipo correspondente.
*
*  Par�metros
*     tipoStr     - Representa��o string do tipo.
*     pTipo       - Refer�ncia usada para retornar o tipo correspondente.
*
*  Condi��es de retorno
*     ISP_CondRetOK
*     ISP_CondRetFaltouMemoria
*     ISP_CondRetNaoReconhecido
*
*  Retorno por refer�ncia
*     pTipo - retorna o tipo de movimento correspondente � string.
*
*  Assertivas de entrada
*     - pTipo � um ponteiro v�lido.
*     - tipoStr � uma representa��o reconhecida de tipo de movimento.
*
*  Assertivas de saida
*     - pTipo aponta para um tipo de movimento correspondente � string tipoStr.
*
***********************************************************************/
ISP_tpCondRet ISP_LerTipoMovimento(char *tipoStr, MPEC_tpTipoMovimento *pTipo);


/***********************************************************************
*
*  Fun��o: ISP Ler passos
*
*  Descri��o
*     Recebe uma representa��o string de uma lista de passos e
*     retorna a lista correspondente.
*
*  Par�metros
*     passosStr   - Representa��o string da lista de passos.
*     ppPassos    - Refer�ncia usada para retornar a lista correspondente.
*
*  Condi��es de retorno
*     ISP_CondRetOK
*     ISP_CondRetFaltouMemoria
*     ISP_CondRetNaoReconhecido
*
*  Retorno por refer�ncia
*     ppPassos - retorna a lista correspondente � string.
*
*  Assertivas de entrada
*     - ppPassos � um ponteiro v�lido.
*     - passosStr � uma representa��o reconhecida de lista de passos.
*
*  Assertivas de saida
*     - ppPassos aponta para a lista de passos correspondente � string passosStr.
*
***********************************************************************/
ISP_tpCondRet ISP_LerPassos(char *passosStr, LIS_tppLista *ppPassos);

/***********************************************************************/
#undef INPUT_STRING_PARSER_EXT

/********** Fim do m�dulo de defini��o: Input string parser **********/

#else
#endif