#if ! defined( ANALISE_PARTIDA_ )
#define ANALISE_PARTIDA_

/***************************************************************************
*
*  Módulo de definição: APAR  Analise Partida
*
*  Arquivo gerado:              analise_partida.h
*  Letras identificadoras:      APAR
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Marcação sobre as casas que as peças podem chegar
*
*  Descrição do módulo
*     Permite obter uma analise detalhada sobre uma partida, em relação às casas
*     que as peças podem chegar, iinclusive as casas que as peças podem chegar.
*     O módulo utiliza a estrutura stPegada para marcar as casas que podem ser
*     alcançadas por outras peças.
*     Uma vez criada sua estrutura não pode ser alterada pelo cliente.
*
***************************************************************************/
 
#if defined( ANALISE_PARTIDA_OWN )
   #define ANALISE_PARTIDA_EXT
#else
   #define ANALISE_PARTIDA_EXT extern
#endif

#include "direcao.h"
#include "partida.h"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma Analise de Partida */
typedef struct APAR_stAnalise* APAR_tppAnalise;

/***********************************************************************
*
*  Tipo de dados: <abreviacao> <descricao-do-enum>
*
*
*  Descrição do tipo
*     <descricao do enum>
*
***********************************************************************/

   typedef enum {

         APAR_CondRetOK = 0,
               /* Executou correto */

         APAR_CondRetNaoEhCasa = 1,
               /* Não é casa na direção ou com o nome desejado */

         APAR_CondRetAnaliseNaoExiste = 2,
               /* Analise não existe */

         APAR_CondRetFaltouMemoria = 3
               /* Faltou memória ao alocar dados */

   } APAR_tpCondRet ;

/******************************************/

/***********************************************************************
*
*  Função: APAR Criar analise
*
*  Descrição
*     Cria uma instância da analise.
*
*  Parâmetros
*     ppAnalise - Referência que será usada para retornar a instância
*     pPartida  - Partida que será usada como base na análise.
*
*  Condições de retorno
*     APAR_CondRetOK
*     APAR_CondRetNaoEhCasa
*     APAR_CondRetFaltouMemoria
*
*  Retorno por referência
*     ppAnalise - Nova instancia de Analise.
*
*  Assertivas de entrada
*     - ppAnalise é um ponteiro válido
*     - Valem as assertivas estruturais da Partida para pPartida.
*
*  Assertivas de saida
*     - A estrutura apontada por pPartida não foi alterada.
*     - ppAnalise possui uma instância válida de Analise Partida.
*
***********************************************************************/
   APAR_tpCondRet APAR_CriarAnalise(APAR_tppAnalise *ppAnalise, PAR_tppPartida pPartida);


/***********************************************************************
*
*  Função: APAR Alguma pegada inimiga
*
*  Descrição
*     Verifica se alguma peça inimiga pode mover para
*     a casa corrente.
*
*  Parâmetros
*     pAnalise   - PartidaAnalise que será usada como base.
*     pResposta  - Referencia usada para retornar a resposta da função.
*
*  Condições de retorno
*     APAR_CondRetOK
*     APAR_CondRetAnaliseNaoExiste
*
*  Retorno por referência
*     pResposta   - Será 1 caso haja alguma peça inimiga que possa se mover
*                   para a casa corrente, e 0 caso contrário.
*
*  Assertivas de entrada
*     - pAnalise aponta para uma PartidaAnalise válida.
*     - pResposta é um ponteiro válido.
*
*  Assertivas de saida
*     - A instância referenciada por pAnalise não foi alterada.
*     - pResposta aponta para 0 ou 1.
*
***********************************************************************/
   APAR_tpCondRet APAR_AlgumaPegadaInimiga(APAR_tppAnalise pAnalise, int *pResposta);


/***********************************************************************
*
*  Função: APAR Rei pode mover para corrente
*
*  Descrição
*     Verifica se o rei pode mover para a casa corrente.
*
*  Parâmetros
*     pAnalise   - PartidaAnalise que será usada como base.
*     pResposta  - Referencia usada para retornar a resposta da função.
*
*  Condições de retorno
*     APAR_CondRetOK
*     APAR_CondRetAnaliseNaoExiste
*
*  Retorno por referência
*     pResposta   - Será 1 caso o rei possa se mover
*                   para a casa corrente, e 0 caso contrário.
*
*  Assertivas de entrada
*     - pAnalise aponta para uma PartidaAnalise válida.
*     - pResposta é um ponteiro válido.
*
*  Assertivas de saida
*     - A instância referenciada por pAnalise não foi alterada.
*     - pResposta aponta para 0 ou 1.
*
***********************************************************************/
   APAR_tpCondRet APAR_ReiPodeMoverParaCorrente(APAR_tppAnalise pAnalise, int *pResposta);


/***********************************************************************
*
*  Função: APAR Ir casa rei
*
*  Descrição
*     Muda corrente para apontar para a casa onde se encontra o rei.
*
*  Parâmetros
*     pAnalise       - PartidaAnalise que será usada como base.
*
*  Condições de retorno
*     APAR_CondRetOK
*     APAR_CondRetAnaliseNaoExiste
*     APAR_CondRetNaoEhCasa
*
*  Assertivas de entrada
*     - pAnalise aponta para uma PartidaAnalise válida.
*
*  Assertivas de saida
*     - O corrente de pAnalise aponta para a casa onde se encontra o rei.
*
***********************************************************************/
   APAR_tpCondRet APAR_IrCasaRei(APAR_tppAnalise pAnalise);

/***********************************************************************
*
*  Função: APAR Destruir analise
*
*  Descrição da função
*     Destroi a instancia de análise, liberando seu espaço da memória.
*
*  Parâmetros
*     ppAnalise - é o ponteiro para a análise que será destruida.
*                 Este parâmetro é passado por referência.
*
*  Condições de retorno
*     APAR_CondRetOK
*     APAR_CondRetAnaliseNaoExiste
*
*  Retorno por referência
*     ppAnalise - retorno é NULL
*
*  Assertivas de entrada
*     - ppAnalise é NULL ou aponta para uma PartidaAnalise válida.
*
*  Assertivas de saida
*     - A instancia apontada por ppAnalise é liberada da memória.
*     - ppAnalise aponta para NULL
*
***********************************************************************/
   APAR_tpCondRet APAR_DestruirAnalise(APAR_tppAnalise *ppAnalise);


/***********************************************************************
*
*  Função: APAR Ir casa
*
*  Descrição
*     Muda corrente baseado no nome da casa.
*
*  Parâmetros
*     pAnalise - PartidaAnalise que será usada como base.
*     nomeCasa - Nome de uma casa no tabuleiro da partida.
*
*  Condições de retorno
*     APAR_CondRetOK
*     APAR_CondRetNaoEhCasa
*     APAR_CondRetAnaliseNaoExiste
*
*  Assertivas de entrada
*     - pAnalise aponta para uma PartidaAnalise válida.
*
*  Assertivas de saida
*     - O corrente de pAnalise aponta para a casa com o nome igual ao passado
*       por parâmetro, ou permanece o mesmo, caso não exista casa com este nome.
*
***********************************************************************/
   APAR_tpCondRet APAR_IrCasa(APAR_tppAnalise pAnalise, char *nomeCasa);


/***********************************************************************
*
*  Função: APAR Ir Para
*
*  Descrição
*     Muda corrente navegando para casa que está na direção passada por
*     parâmetro, tendo como base o corrente atual.
*
*  Parâmetros
*     pAnalise - PartidaAnalise que será usada como base.
*     direcao  - Direção que será seguida.
*
*  Condições de retorno
*     APAR_CondRetOK
*     APAR_CondRetNaoEhCasa
*     APAR_CondRetAnaliseNaoExiste
*
*  Assertivas de entrada
*     - pAnalise aponta para uma PartidaAnalise válida.
*
*  Assertivas de saida
*     - O corrente de pAnalise aponta para a casa na direção passada
*       por parâmetro, ou permanece o mesmo caso não exista casa nesta direção.
*
***********************************************************************/
   APAR_tpCondRet APAR_IrPara(APAR_tppAnalise pAnalise , DIR_tpDirecao direcao);

#undef ANALISE_PARTIDA_EXT

/********** Fim do módulo de definição: APAR Analise partida **********/

#else
#endif

