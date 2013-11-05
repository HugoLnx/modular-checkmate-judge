#if ! defined( DIRECAO_ )
#define DIRECAO_
/***************************************************************************
*
*   TODO! DOCUMENTACAO DO MODULO!
*
***************************************************************************/
 
#if defined( DIRECAO_OWN )
   #define DIRECAO_EXT
#else
   #define DIRECAO_EXT extern
#endif

#define TOTAL_DIRECOES 8

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

typedef enum {

      DIR_CondRetOK = 0 ,
            /* Executou correto */

      DIR_CondRetFaltouMemoria = 1 ,
            /* Faltou memória ao alocar dados */

      DIR_CondRetNaoPodeSeTornarString
} DIR_tpCondRet;


DIR_tpCondRet DIR_DirecaoOrientadaPara(DIR_tpDirecao direcao,
   DIR_tpDirecao orientacao, DIR_tpDirecao *dirRetorno);

DIR_tpCondRet DIR_DirecaoComoString(DIR_tpDirecao direcao, char **pRetornoStr);

#undef DIRECAO_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
