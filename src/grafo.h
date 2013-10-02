#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  Módulo de definição: <abreviação>  <estrutura manipulada pelo módulo>
*
*  Arquivo gerado:              <nome-do-arquivo>.h
*  Letras identificadoras:      <abreviação>
*
*	Autores:
*     - <nick>: <nome>
*     - <nick>: <nome>
*
*  Histórico de evolução:
*     Versão  Autor    Data        Observações
*     1       <nick>   <data>      <observações>
*
*  Descrição do módulo
*     <descrição do módulo>
*
***************************************************************************/
 
#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */

typedef struct GRA_estGrafo * GRA_tppGrafo ;


/***********************************************************************
*
*  Tipo de dados: GRA Condições de retorno
*
*
*  Descrição do tipo
*     Condições de retorno das funções do grafo
*
***********************************************************************/

typedef enum {

	GRA_CondRetOK ,
		/* Concluiu corretamente */

	GRA_CondRetGrafoVazia ,
		/* A grafo não contém elementos */

	GRA_CondRetNaoAchou ,
		/* Não encontrou o valor procurado */

	GRA_CondRetFaltouMemoria
		/* Faltou memória ao tentar alocar algo */

} GRA_tpCondRet ;



/***********************************************************************
*
*  Função: <abreviacao do modulo> <nome da funcao por extenso>
*
*  Descrição
*     <descricao da função>
*
*  Parâmetros
*     <param 1>      - <explicação sobre parametro 1>
*     <parametro 2>  - <explicação sobre parametro 2>
*
*  Retorno
*     <descricao do retorno, listar os possíveis tpCondRet>
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saida
*     <assertivas de saida>
*
***********************************************************************/
void GRA_FuncaoQualquer() ;



/***********************************************************************/
#undef GRAFO_EXT

/********** Fim do módulo de definição: GRA Grafo direcionado **********/

#else
#endif
