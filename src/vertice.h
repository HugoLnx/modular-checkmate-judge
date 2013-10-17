#if ! defined( VERTICE_ )
#define VERTICE_
/***************************************************************************
*
*  Módulo de definição: VER  Conteúdo do módulo
*
*  Arquivo gerado:              vertice.h
*  Letras identificadoras:      VER
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

#if defined( VERTICE_OWN )
#define VERTICE_EXT
#else
#define VERTICE_EXT extern
#endif


/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um conteudo */

typedef struct VER_stConteudo * VER_tppConteudo;


/***********************************************************************
*
*  Tipo de dados: VER Condições de retorno
*
*
*  Descrição do tipo
*     Condições de retorno das funções do conteudo
*
***********************************************************************/

typedef enum {

	VER_CondRetOK,
	    /* Concluiu corretamente */

	VER_CondRetConteudoNaoExiste,
	    /* Conteúdo não foi criado */

	VER_CondRetFaltouMemoria
	    /* Faltou memória ao tentar alocar algo */

} VER_tpCondRet;


/***********************************************************************
*
*  Função: VER Criar conteudo
*
*  Descrição
*     Cria uma instância da estrutura.
*
*  Parâmetros
*     ppConteudo - Referência usada para retorno do conteúdo que será criado.
*     pValor     - Valor que será atribuido à estrutura.
*
*  Condições de retorno
*     - VER_CondRetOK
*     - VER_CondRetFaltouMemoria
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
VER_tpCondRet VER_CriarConteudo(VER_tppConteudo *ppConteudo, char *pValor);

/***********************************************************************
*
*  Função: VER Destruir conteúdo
*
*  Descrição
*     Destroi uma instância da estrutura liberando seu espaço na memória.
*
*  Parâmetros
*     ppConteudo - Referência para o ponteiro do conteúdo à ser destruido.
*     pValor     - Valor que será atribuido à estrutura.
*
*  Condições de retorno
*     - VER_CondRetOK
* 
*  Retorno por referência
*     Referência para NULL.
*
*  Assertivas de entrada
*     - ppConteudo referencia para uma instância da estrutura VER_stConteudo.
*
*  Assertivas de saida
*     - A referência será sempre nula.
*     - O conteúdo e seu valor foram liberados da memória
*
***********************************************************************/
VER_tpCondRet VER_DestruirConteudo(VER_tppConteudo *ppConteudo);

/***********************************************************************
*
*  Função: VER Obter valor do conteúdo
*
*  Descrição
*     Recupera o valor da instância de conteúdo
*
*  Parâmetros
*     pConteudoParm  - Referência para o conteúdo.
*     ppValor        - Referência usada para retorno do valor.
*
*  Condições de retorno
*     - VER_CondRetOK
*     - VER_CondRetConteudoNaoExiste
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
VER_tpCondRet VER_ObterValorDoConteudo(VER_tppConteudo pConteudoParm, char **ppValor);

/***********************************************************************
*
*  Função: VER Alterar valor do conteúdo
*
*  Descrição
*     Substitui o valor da instância de conteúdo por uma nova.
*
*  Parâmetros
*     pConteudoParm  - Referência para o conteúdo.
*     pValor         - Referência para o novo valor do conteúdo.
*
*  Condições de retorno
*     - VER_CondRetOK
*     - VER_CondRetConteudoNaoExiste
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
VER_tpCondRet VER_AlterarValorDoConteudo(VER_tppConteudo pConteudoParm, char *pValor);

/********** Fim do módulo de definição: VER Conteudo **********/

#endif