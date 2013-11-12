#if ! defined( INPUT_STRING_PARSER_ )
#define INPUT_STRING_PARSER_
/***************************************************************************
*
*  Módulo de definição: ISP  Input String Parser
*
*  Arquivo gerado:              input_string_parser.h
*  Letras identificadoras:      ISP
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Parseia alguns tipos básicos
*
*  Descrição do módulo
*     Módulo responsável por parsear representações de string para as instâncias
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

/***** Declarações exportadas pelo módulo *****/


/***********************************************************************
*
*  Tipo de dados: ISP Condições de retorno
*
*
*  Descrição do tipo
*     Condições de retorno das funções exportadas.
*
***********************************************************************/

typedef enum {

   ISP_CondRetOK,
      /* Concluiu corretamente */

   ISP_CondRetNaoReconhecido,
      /* A entrada não foi reconhecida */

   ISP_CondRetFaltouMemoria,
      /* Faltou memória ao tentar alocar algo */
 
} ISP_tpCondRet;

/***********************************************************************
*
*  Função: ISP Ler tipo movimento
*
*  Descrição
*     Recebe uma representação string do tipo de movimento e
*     retorna o tipo correspondente.
*
*  Parâmetros
*     tipoStr     - Representação string do tipo.
*     pTipo       - Referência usada para retornar o tipo correspondente.
*
*  Condições de retorno
*     ISP_CondRetOK
*     ISP_CondRetFaltouMemoria
*     ISP_CondRetNaoReconhecido
*
*  Retorno por referência
*     pTipo - retorna o tipo de movimento correspondente à string.
*
*  Assertivas de entrada
*     - pTipo é um ponteiro válido.
*     - tipoStr é uma representação reconhecida de tipo de movimento.
*
*  Assertivas de saida
*     - pTipo aponta para um tipo de movimento correspondente à string tipoStr.
*
***********************************************************************/
ISP_tpCondRet ISP_LerTipoMovimento(char *tipoStr, MPEC_tpTipoMovimento *pTipo);


/***********************************************************************
*
*  Função: ISP Ler passos
*
*  Descrição
*     Recebe uma representação string de uma lista de passos e
*     retorna a lista correspondente.
*
*  Parâmetros
*     passosStr   - Representação string da lista de passos.
*     ppPassos    - Referência usada para retornar a lista correspondente.
*
*  Condições de retorno
*     ISP_CondRetOK
*     ISP_CondRetFaltouMemoria
*     ISP_CondRetNaoReconhecido
*
*  Retorno por referência
*     ppPassos - retorna a lista correspondente à string.
*
*  Assertivas de entrada
*     - ppPassos é um ponteiro válido.
*     - passosStr é uma representação reconhecida de lista de passos.
*
*  Assertivas de saida
*     - ppPassos aponta para a lista de passos correspondente à string passosStr.
*
***********************************************************************/
ISP_tpCondRet ISP_LerPassos(char *passosStr, LIS_tppLista *ppPassos);

/***********************************************************************/
#undef INPUT_STRING_PARSER_EXT

/********** Fim do módulo de definição: Input string parser **********/

#else
#endif