#if ! defined( CONTEUDO_ )
#define CONTEUDO_
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
 
#if defined( CONTEUDO_OWN )
   #define CONTEUDO_EXT
#else
   #define CONTEUDO_EXT extern
#endif


/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um conteudo */

typedef struct CON_tpConteudo * CON_tppConteudo;


/***********************************************************************
*
*  Tipo de dados: CON Condições de retorno
*
*
*  Descrição do tipo
*     Condições de retorno das funções do conteudo
*
***********************************************************************/

typedef enum {

	CON_CondRetOK ,
		/* Concluiu corretamente */

	CON_CondRetGrafoVazia ,
		/* A grafo não contém elementos */

	CON_CondRetNaoAchou ,
		/* Não encontrou o valor procurado */

	CON_CondRetFaltouMemoria
		/* Faltou memória ao tentar alocar algo */

} CON_tpCondRet ;


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

CON_tpCondRet CON_CriarConteudo(CON_tppConteudo *ppConteudo, char *pValor);
CON_tpCondRet CON_DestruirConteudo(CON_tppConteudo *ppConteudo);
CON_tpCondRet CON_ObterValorDoConteudo(CON_tppConteudo ppConteudo, char **ppValor);
CON_tpCondRet CON_AlterarValorDoConteudo(CON_tppConteudo *ppConteudo, char *pValor);

/********** Fim do módulo de definição: CON Conteudo **********/

#endif