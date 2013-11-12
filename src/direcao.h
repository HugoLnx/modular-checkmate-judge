#if ! defined( DIRECAO_ )
#define DIRECAO_
/***************************************************************************
*
*  Módulo de definição: DIR  Direção
*
*  Arquivo gerado:              direcao.h
*  Letras identificadoras:      DIR
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Manipulação básica de direção
*
*  Descrição do módulo
*     Módulo responsável por operações com direção.
*
***************************************************************************/
 
#if defined( DIRECAO_OWN )
   #define DIRECAO_EXT
#else
   #define DIRECAO_EXT extern
#endif

#define TOTAL_DIRECOES 8

/***********************************************************************
*
*  Tipo de dados: DIR Direções
*
*
*  Descrição do tipo
*     Representação de todas as direções disponíveis.
*
***********************************************************************/
typedef enum {
   NORTE    = 0,

   NORDESTE = 1,

   ESTE     = 2,

   SUDESTE  = 3,  

   SUL      = 4,
   
   SUDOESTE = 5,

   OESTE    = 6,

   NOROESTE = 7
} DIR_tpDirecao;


/***********************************************************************
*
*  Tipo de dados: DIR Condições de retorno
*
*
*  Descrição do tipo
*     Condições de retorno das funções exportadas.
*
***********************************************************************/
typedef enum {

      DIR_CondRetOK = 0 ,
            /* Executou correto */

      DIR_CondRetFaltouMemoria = 1 ,
            /* Faltou memória ao alocar dados */

      DIR_CondRetNaoPodeSeTornarString
} DIR_tpCondRet;


/***********************************************************************
*
*  Função: DIR Direção orientada para
*
*  Descrição
*     Mudar orientação da direção do padrão NORTE para
*     alguma outra direção qualquer.
*
*  Parâmetros
*     direcao     - Direção base.
*     orientacao  - Direção da orientação.
*     dirRetorno - Referência para retornar a direção resultante.
*
*  Condições de retorno
*     DIR_CondRetOK;
*
*  Retorno por referência
*     dirRetorno - Retorna uma nova direção que é resultado da direção base
*                   orientada para a direção da orientação.
*
*  Assertivas de entrada
*     - dirRetorno é um ponteiro válido.
*
*  Assertivas de saida
*     - dirRetorno aponta para a direção resultante.
*
***********************************************************************/
DIR_tpCondRet DIR_DirecaoOrientadaPara(DIR_tpDirecao direcao,
   DIR_tpDirecao orientacao, DIR_tpDirecao *dirRetorno);


/***********************************************************************
*
*  Função: DIR Direção como string
*
*  Descrição
*     Cria uma versão string da direção.
*
*  Parâmetros
*     direcao     - Direção á ser convertida.
*     pRetornoStr - Referência para retornar a string representando a direção.
*
*  Condições de retorno
*     DIR_CondRetOK
*     DIR_CondRetFaltouMemoria
*     DIR_CondRetNaoPodeSeTornarString
*
*  Retorno por referência
*     pRetornoStr - Retorna uma string caso seja possível fazer a conversão.
*
*  Assertivas de entrada
*     - direção está entre um dos 8 pontos cardeais.
*     - pRetornoStr é um ponteiro válido.
*
*  Assertivas de saida
*     - pRetornoStr aponta para uma string que representa a direção.
*
***********************************************************************/
DIR_tpCondRet DIR_DirecaoComoString(DIR_tpDirecao direcao, char **pRetornoStr);

#undef DIRECAO_EXT

/********** Fim do módulo de definição: Módulo Direção **********/

#else
#endif
