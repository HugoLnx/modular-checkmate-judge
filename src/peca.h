#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  Módulo de definição: PEC  Peça
*
*  Arquivo gerado:              peca.h
*  Letras identificadoras:      PEC
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Funções para manipulação da peça.
*
*  Descrição do módulo
*     Módulo responsável pela manipulação das estruturas que compões uma peça.
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
*  Tipo de dados: PEC Time da peça
*
*
*  Descrição do tipo
*     Define qual o time que a peça estará participando.
*
***********************************************************************/

typedef enum {
   ALIADA = 0,
   INIMIGA = 1
} PEC_tpTimePeca;


/***********************************************************************
*
*  Tipo de dados: PEC Condições de retorno
*
*
*  Descrição do tipo
*     Condições de retorno das funções exportadas.
*
***********************************************************************/
typedef enum {

   PEC_CondRetOK,
   /* Executou correto */
      
   PEC_CondRetFaltouMemoria,
   /* Faltou memória ao alocar dados */

   PEC_CondRetNaoAlterou,
   /* Não foi possivel alterar a peca */

   PEC_CondRetPecaNaoExiste
   /* Peça não existe */

} PEC_tpCondRet;


/* Tipo referência para uma Peça */
typedef struct PEC_stPeca* PEC_tppPeca;

/***********************************************************************
*
*  Função: PEC Criar peça
*
*  Descrição
*     Cria instância de peça.
*
*  Parâmetros
*     ppPeca         - Referência para retornar a nova instância.
*     pModelo        - Modelo da peça.
*     time           - Time da peça.
*
*  Condições de retorno
*     PEC_CondRetOK
*     PEC_CondRetFaltouMemoria
*
*  Retorno por referência
*     ppPeca - retorna a nova instância criada.
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do modelo peça.
*     - ppPeca é um ponteiro válido.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais da Peça.
*
***********************************************************************/
PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca *ppPeca, MPEC_tppModeloPeca pModelo, PEC_tpTimePeca time);


/***********************************************************************
*
*  Função: PEC Destruir peça
*
*  Descrição
*     Destroi instância de peça.
*
*  Parâmetros
*     ppPeca         - Referência para peça.
*
*  Condições de retorno
*     PEC_CondRetOK
*
*  Retorno por referência
*     ppPeca - Retorna NULL
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da peça.
*
*  Assertivas de saida
*     - Peça foi liberada da memória.
*     - ppPeca aponta para NULL.
*
***********************************************************************/
PEC_tpCondRet PEC_DestruirPeca(PEC_tppPeca *ppPeca);


/***********************************************************************
*
*  Função: PEC Criar rei
*
*  Descrição
*     Cria uma instância de peça especial, o rei.
*
*  Parâmetros
*     ppPeca - Referência usada para retornar a nova instância.
*
*  Condições de retorno
*     PEC_CondRetOK
*     PEC_CondRetFaltouMemoria
*
*  Retorno por referência
*     ppPeca - retorna a nova instância criada.
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do modelo peça.
*     - ppPeca é um ponteiro válido.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais da Peça.
*     - Peça tem modelo NULL.
*
***********************************************************************/
PEC_tpCondRet PEC_CriarRei(PEC_tppPeca *ppPeca);

/***********************************************************************
*
*  Função: PEC Destruir rei
*
*  Descrição
*     Destroi instância de rei.
*
*  Parâmetros
*     ppPeca         - Referência para a peça.
*
*  Condições de retorno
*     PEC_CondRetOK
*
*  Retorno por referência
*     ppPeca - Retorna NULL
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da peça.
*     - Peça tem modelo NULL
*
*  Assertivas de saida
*     - Peça foi liberada da memória.
*     - ppPeca aponta para NULL.
*
***********************************************************************/
PEC_tpCondRet PEC_DestruirRei(PEC_tppPeca *ppPeca);


/***********************************************************************
*
*  Função: PEC Alterar modelo peça
*
*  Descrição
*     <descricao da função>
*
*  Parâmetros
*     pPeca       - Peça que será alterada.
*     pNovoModelo - Modelo que será adicionado à peça.
*
*  Condições de retorno
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da peça.
*     - Valem as assertivas estruturais do modelo peça.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais da Peça.
*
***********************************************************************/
PEC_tpCondRet PEC_AlterarModeloPeca(PEC_tppPeca pPeca, MPEC_tppModeloPeca pNovoModelo);


/***********************************************************************
*
*  Função: PEC É o rei
*
*  Descrição
*     Verifica se peça é rei.
*
*  Parâmetros
*     pPecaParm    - Peça que será verificada.
*     ehRei        - Referência usada para retornar a resposta.
*
*  Condições de retorno
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
*  Retorno por referência
*     ehRei - Será 1 caso seja rei e 0 caso não seja.
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da peça.
*     - ehRei é um ponteiro válido.
*
*  Assertivas de saida
*     - Peça não é alterada.
*     - ehRei é 1 caso seja rei e 0 caso não seja.
*
***********************************************************************/
PEC_tpCondRet PEC_EhORei(PEC_tppPeca pPecaParm, int *ehRei);

/***********************************************************************
*
*  Função: PEC Obter modelo
*
*  Descrição
*     Recupera o modelo da peça;
*
*  Parâmetros
*     pPecaParm    - Peça que será usada.
*     ppModelo     - Referência usada para retornar o modelo.
*
*  Condições de retorno
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
*  Retorno por referência
*     ppModelo - retorna o modelo da peça.
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da peça.
*
*  Assertivas de saida
*     - Peça não é alterada.
*     - Valem as assertivas estruturais do modelo.
*
***********************************************************************/
PEC_tpCondRet PEC_ObterModelo(PEC_tppPeca pPecaParm, MPEC_tppModeloPeca *ppModelo);


/***********************************************************************
*
*  Função: PEC Obter time
*
*  Descrição
*     Recupera o modelo da peça;
*
*  Parâmetros
*     pPecaParm    - Peça que será usada.
*     pTime        - Referência usada para retornar o time.
*
*  Condições de retorno
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
*  Retorno por referência
*     pTime - retorna o time da peça.
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da peça.
*
*  Assertivas de saida
*     - Peça não é alterada.
*
***********************************************************************/
PEC_tpCondRet PEC_ObterTime(PEC_tppPeca pPecaParm, PEC_tpTimePeca *pTime);


/***********************************************************************
*
*  Função: PEC Salvar peça
*
*  Descrição
*     Alimenta o arquivo com uma serialização em texto da peça.
*
*  Parâmetros
*     pPeca      - Peça que será usada.
*     pFile      - Arquivo que será incrementado.
*
*  Condições de retorno
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da peça.
*     - Arquivo está aberto em modo de escrita.
*
*  Assertivas de saida
*     - Peça não foi alterada.
*     - Arquivo contém uma serialização da peça no final.
*
***********************************************************************/
PEC_tpCondRet PEC_SalvarPeca(PEC_tppPeca pPeca, FILE* pFile);


#undef PECA_EXT

/********** Fim do módulo de definição: Módulo Peça **********/

#else
#endif
