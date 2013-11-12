#if !defined(PASSO_)
#define PASSO_
/***************************************************************************
*
*  Módulo de definição: PAS  Passo
*
*  Arquivo gerado:              passo.h
*  Letras identificadoras:      PAS
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Manipulação básica de passo
*
*  Descrição do módulo
*     Módulo responsável por manipular a estrutura Passo.
*
***************************************************************************/
 
#if defined( PASSO_OWN )
   #define PASSO_EXT
#else
   #define PASSO_EXT extern
#endif

#include "lista.h"
#include "direcao.h"

/* Tipo referência para um Passo */
typedef struct PAS_stPasso* PAS_tppPasso;


/***********************************************************************
*
*  Tipo de dados: PAS Condições de retorno
*
*
*  Descrição do tipo
*     Condições de retorno das funções exportadas.
*
***********************************************************************/
   typedef enum {

         PAS_CondRetOK = 0,
               /* Executou correto */

         PAS_CondRetPassoNaoExiste = 3,
               /* Passo não existe */

         PAS_CondRetFaltouMemoria = 5
               /* Faltou memória ao alocar dados */

   } PAS_tpCondRet;


/***********************************************************************
*
*  Função: PAS Criar passo
*
*  Descrição
*     Cria uma instância de passo.
*
*  Parâmetros
*     ppPasso     - Referência para retorno da nova instância.
*     direcao     - Direção do passo
*     quantidade  - Quantidade de locomoção deste passo.
*
*  Condições de retorno
*     PAS_CondRetOK
*     PAS_CondRetFaltaMemoria
*
*  Retorno por referência
*     ppPasso - Retorna a nova instância.
*
*  Assertivas de entrada
*     - ppPasso é um ponteiro válido.
*
*  Assertivas de saida
*     - ppPasso aponta para um passo.
*
***********************************************************************/
   PAS_tpCondRet PAS_CriarPasso(PAS_tppPasso *ppPasso, DIR_tpDirecao direcao, int quantidade);


/***********************************************************************
*
*  Função: PAS Destruir passo
*
*  Descrição
*     Destruir instância de passo.
*
*  Parâmetros
*     ppPasso   - Referência para o passo à ser destruido.
*
*  Condições de retorno
*     PAS_CondRetOK
*
*  Retorno por referência
*     ppPasso retorna NULL
*
*  Assertivas de entrada
*     ppPasso é NULL ou aponta para um passo válido.
*
*  Assertivas de saida
*     ppPasso aponta para NULL.
*
***********************************************************************/
   PAS_tpCondRet PAS_DestruirPasso(PAS_tppPasso *ppPasso);


/***********************************************************************
*
*  Função: PAS Comparar passos
*
*  Descrição
*     Compara dois passos e verifica se são iguais.
*
*  Parâmetros
*     pPasso1, pPasso2 - Passos à serem comparados
*     pResposta        - Referência à ser usada para retornar a resposta.
*
*  Condições de retorno
*     PAS_CondRetOK
*     PAS_CondRetPassoNaoExiste
*
*  Retorno por referência
*     pResposta - Retorna 1 caso os passos sejam iguais e 0 caso contrário.
*
*  Assertivas de entrada
*     - pResposta é um ponteiro válido.
*
*  Assertivas de saida
*     - pResposta aponta para 1 caso sejam iguais e 0 caso não sejam.
*
***********************************************************************/
   PAS_tpCondRet PAS_CompararPassos(PAS_tppPasso pPasso1, PAS_tppPasso pPasso2, int *pResposta);



/***********************************************************************
*
*  Função: PAS Obter quantidade
*
*  Descrição
*     Recupera a quantidade de locomoção do passo.
*
*  Parâmetros
*     pPassoParm - Passo que será usado.
*     pQuantidade - Referência que será usada para retornar a quantidade.
*
*  Condições de retorno
*     PAS_CondRetOK
*     PAS_CondRetPassoNaoExiste
*
*  Retorno por referência
*     pQuantidade - Retorna a quantidade relacionada à peça.
*
*  Assertivas de entrada
*     - pQuantidade é um ponteiro válido.
*
*  Assertivas de saida
*     - Passo não muda.
*     - pQuantidade aponta para um número representando a quantidade
*       relativa ao passo.
*
***********************************************************************/
   PAS_tpCondRet PAS_ObterQuantidade(PAS_tppPasso pPassoParm, int *pQuantidade);


/***********************************************************************
*
*  Função: PAS Obter direção
*
*  Descrição
*     Recupera a direção do passo.
*
*  Parâmetros
*     pPassoParm - Passo que será usado.
*     pDirecao - Referência que será usada para retornar a direção.
*
*  Condições de retorno
*     PAS_CondRetOK
*     PAS_CondRetPassoNaoExiste
*
*  Retorno por referência
*     pDireção - Retorna a direção relacionada à peça.
*
*  Assertivas de entrada
*     - pDireção é um ponteiro válido.
*
*  Assertivas de saida
*     - Passo não muda.
*     - pDireção aponta para um número representando a quantidade
*       relativa ao passo.
*
***********************************************************************/
   PAS_tpCondRet PAS_ObterDirecao(PAS_tppPasso pPassoParm, DIR_tpDirecao *pDirecao);


/***********************************************************************
*
*  Função: PAS É infinito
*
*  Descrição
*     Verifica se a quantidade de locomoção do passo é "infinita", ou seja,
*     até algum obstaculo externo ocorrer.
*
*  Parâmetros
*     pPassoParm  - Passo que será usado.
*     pEhInfinito - Referência que será usada para retornar a resposta.
*
*  Condições de retorno
*     PAS_CondRetOK
*     PAS_CondRetPassoNaoExiste
*
*  Retorno por referência
*     pEhInfinito - Retorna 1 caso a quantidade seja infinita e 0 caso contrário.
*
*  Assertivas de entrada
*     - pEhInfinito é um ponteiro válido.
*
*  Assertivas de saida
*     - Passo não muda.
*     - pEhInfinito aponta para 1 caso a quantidade seja infinita e 0 caso contrário.
*
***********************************************************************/
   PAS_tpCondRet PAS_EhInfinito(PAS_tppPasso pPassoParm, int *pEhInfinito);


/***********************************************************************
*
*  Função: PAS Salvar passo
*
*  Descrição
*     Alimenta o arquivo com uma serialização em texto do passo.
*
*  Parâmetros
*     pPasso     - Passo que será usado.
*     pFile      - Arquivo que será incrementado.
*
*  Condições de retorno
*     PAS_CondRetOK
*     PAS_CondRetPassoNaoExiste
*
*  Assertivas de entrada
*     - Arquivo está aberto em modo de escrita.
*
*  Assertivas de saida
*     - Passo não foi alterado.
*     - Arquivo contém uma serialização do passo no final.
*
***********************************************************************/
   PAS_tpCondRet PAS_Salvar(LIS_tppLista ppPassos, FILE* pFile);


#undef PASSO_EXT

/********** Fim do módulo de definição: Módulo Passo **********/

#else
#endif
