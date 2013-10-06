#if ! defined( CONTEUDO_ )
#define CONTEUDO_
/***************************************************************************
*
*  Módulo de definição: CON  Conteúdo do módulo
*
*  Arquivo gerado:              conteudo.h
*  Letras identificadoras:      CON
*
*	Autores:
*     - Hugo Roque: hg
*     - Robert Corrêa: rc
*
*  Histórico de evolução:
*     Versão  Autor    Data        Observações
*     1.0     rc       02/out/13   Criação do módulo e as operações básicas.
*     1.1     hg       05/out/13   Checagem de erros caso o conteúdo não tenha sido criado.
*
*  Descrição do módulo
*     Módulo extremamente simples que representa o conteúdo utilizado pelo grafo.
*
***************************************************************************/

#if defined( CONTEUDO_OWN )
#define CONTEUDO_EXT
#else
#define CONTEUDO_EXT extern
#endif


/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um conteudo */

typedef struct CON_stConteudo * CON_tppConteudo;


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

	CON_CondRetConteudoNaoExiste ,
	    /* Conteúdo não foi criado */

	CON_CondRetFaltouMemoria
	    /* Faltou memória ao tentar alocar algo */

} CON_tpCondRet ;


/***********************************************************************
*
*  Função: CON Criar conteudo
*
*  Descrição
*     Cria uma instância da estrutura.
*
*  Parâmetros
*     ppConteudo - Referência usada para retorno do conteúdo que será criado.
*     pValor     - Valor que será atribuido à estrutura.
*
*  Condições de retorno
*     - CON_CondRetOK
*     - CON_CondRetFaltouMemoria
* 
*  Retorno por referência
*     Ponteiro para o conteúdo que será criado.
*
*  Assertivas de entrada
*     - ppConteudo não contém um Conteúdo criado anteriormente.
*
*  Assertivas de saida
*     - Será um conteúdo com valor igual ao passado por parâmetro.
*
***********************************************************************/
CON_tpCondRet CON_CriarConteudo(CON_tppConteudo *ppConteudo, char *pValor);

/***********************************************************************
*
*  Função: CON Destruir conteúdo
*
*  Descrição
*     Destroi uma instância da estrutura liberando seu espaço na memória.
*
*  Parâmetros
*     ppConteudo - Referência para o ponteiro do conteúdo à ser destruido.
*     pValor     - Valor que será atribuido à estrutura.
*
*  Condições de retorno
*     - CON_CondRetOK
* 
*  Retorno por referência
*     Referência para NULL.
*
*  Assertivas de entrada
*     - ppConteudo referencia para uma instância da estrutura CON_stConteudo.
*
*  Assertivas de saida
*     - A referência será sempre nula.
*     - O conteúdo e seu valor foram liberados da memória
*
***********************************************************************/
CON_tpCondRet CON_DestruirConteudo(CON_tppConteudo *ppConteudo);

/***********************************************************************
*
*  Função: CON Obter valor do conteúdo
*
*  Descrição
*     Recupera o valor da instância de conteúdo
*
*  Parâmetros
*     pConteudoParm  - Referência para o conteúdo.
*     ppValor        - Referência usada para retorno do valor.
*
*  Condições de retorno
*     - CON_CondRetOK
*     - CON_CondRetConteudoNaoExiste
* 
*  Retorno por referência
*     ppValor   - Valor do conteúdo.
*
*  Assertivas de entrada
*     <não tem>
*
*  Assertivas de saida
*     - Será retornado o valor do conteúdo.
*
***********************************************************************/
CON_tpCondRet CON_ObterValorDoConteudo(CON_tppConteudo pConteudoParm, char **ppValor);

/***********************************************************************
*
*  Função: CON Alterar valor do conteúdo
*
*  Descrição
*     Substitui o valor da instância de conteúdo por uma nova.
*
*  Parâmetros
*     pConteudoParm  - Referência para o conteúdo.
*     pValor         - Referência para o novo valor do conteúdo.
*
*  Condições de retorno
*     - CON_CondRetOK
*     - CON_CondRetConteudoNaoExiste
* 
*  Retorno por referência
*     <não tem>
*
*  Assertivas de entrada
*     <não tem>
*
*  Assertivas de saida
*     - Só o valor do conteúdo será alterado.
*
***********************************************************************/
CON_tpCondRet CON_AlterarValorDoConteudo(CON_tppConteudo pConteudoParm, char *pValor);

/********** Fim do módulo de definição: CON Conteudo **********/

#endif