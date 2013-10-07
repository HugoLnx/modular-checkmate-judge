#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  Módulo de definição: GRA  Grafo direcionado
*
*  Arquivo gerado:              grafo.c
*  Letras identificadoras:      GRA
*
*	Autores:
*     - rc: Robert Corrêa
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data        Observações
*     1.0     hg & rc  06/out/13   Preparação do módulo para trabalhar com grafos direcionados.
*
*  Descrição do módulo
*     Implementa grafos direcionados com manipulação, ou seja, é possivel criar, inserir
*     vértices no grafo, conectá-los através de arestas direcionais além de destruir o grafo,
*     um vértice ou uma aresta, navegar através das arestas usando o nome da aresta ou do
*     vértice de destino como referência. É possível também marcar vértices como origem,
*     estes vértices poderão ser acessados à qualquer momento utilizando a função de navegação
*     para origens.
*
*     Podem existir n grafos em operação simultaneamente.
*     Os grafos possuem uma cabeça encapsulando o seu estado.
*
*     Cada grafo armazena dados genéricos.
*     Cada vétice do grafo possui uma referência para o valor.
*
***************************************************************************/
 
#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */

typedef struct GRA_stGrafo * GRA_tppGrafo ;

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

   GRA_CondRetOK,
      /* Concluiu corretamente */

   GRA_CondRetGrafoVazio,
      /* O grafo não contém elementos */

   GRA_CondRetGrafoNaoFoiCriado,
      /* O grafo não contém elementos */

   GRA_CondRetNaoAchou,
      /* Não encontrou o vértice/aresta procurado(a) */
      
   GRA_CondRetJaExiste,
      /* Nome do vértice ou aresta está repetido */

   GRA_CondRetFaltouMemoria,
      /* Faltou memória ao tentar alocar algo */
 
} GRA_tpCondRet ;



/***********************************************************************
*
*  Função: GRA Criar grafo
*
*  Descrição
*     Cria um grafo direcionado.
*
*  Parâmetros
*     ppGrafo           - Referência usada para retorno do grafo que será criado.
*     destruirValor     - Função que será utilizada para destruir o valor
                          e liberar seu espaço na memória.
*
*  Condições de retorno
*     - GRA_CondRetOK
*     - GRA_CondRetFaltouMemoria
* 
*  Retorno por referência
*     ppGrafo:
*       Se executou corretamente retorna o ponteiro para o grafo.
*       Este ponteiro será utilizado pelas funções que manipulem este grafo.
*       
*       Se ocorreu algum erro, por exemplo falta de memória, a função retornará NULL.
*       Não será dada mais informação quanto ao problema ocorrido.
*
*  Assertivas de entrada
*     <não tem>
*
*  Assertivas de saida
*     - Valem as assertivas estruturais do grafo direcionado.
*     - Ponteiros do corrente é nulo e as listas de origens e vértices estão vazias.
*     - Função de destruir será igual à passada por parâmetro.
*
***********************************************************************/
GRA_tpCondRet GRA_CriarGrafo(GRA_tppGrafo *ppGrafo, void (*destruirValor)(void *pValor));


/***********************************************************************
*
*  Função: GRA Destruir grafo
*
*  Descrição
*     Destrói o grafo fornecido.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*
*  Parâmetros
*     ppGrafo  - Referência do a ser destruido.
*
*  Condições de retorno
*     - GRA_CondRetOK
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do grafo direcionado.
*
*  Assertivas de saída
*     - A o grafo, seus vértices e suas arestas foram destruidos.
*
***********************************************************************/
GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo *ppGrafo);


/***********************************************************************
*
*  Função: GRA Inserir vértice
*
*  Descrição
*     Insere novo vértice no grafo.
*     Obs.: Nenhuma relação do novo vértice com qualquer outro vértice ou
*     aresta existente, para isso é necessário utilizar outras funções.
*
*  Parâmetros
*     pGrafoParm    - ponteiro para o grafo onde deve ser inserido o vértice
*     pNomeVertice  - nome do vértice à ser criado.
*     pValor        - ponteiro para valor do novo vértice.
*
*  Condições de retorno
*     GRA_CondRetOK
*     GRA_CondRetGrafoVazio
*     GRA_CondRetGrafoNaoFoiCriado
*     GRA_CondRetJaExiste
*     GRA_CondRetFaltouMemoria
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do grafo direcionado.
*
*  Assertivas de saída
*     - Valem as assertivas estruturais do grafo direcionado.
*     - Corrente apontará para o vértice inserido.
*     - Se já existe vértice com esse nome, nenhum vértice é adicionado e o
*       corrente permanece o mesmo.
*
***********************************************************************/
GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafoParm, char *pNomeVertice, void *pValor);


/***********************************************************************
*
*  Função: GRA Inserir aresta do corrente para outro vértice
*
*  Descrição
*     Insere nova aresta cuja origem é o vértice corrente e o destino será o vértice
*     com o nome apontado.
*
*  Parâmetros
*     pGrafoParm           - ponteiro para o grafo onde deve ser inserido a aresta
*     pNomeAresta          - nome da aresta à ser criada.
*     pNomeVerticeDestino  - nome do vértice cuja a aresta apontará.
*
*  Condições de retorno
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*     GRA_CondRetGrafoVazio
*     GRA_CondRetGrafoNaoFoiCriado
*     GRA_CondRetJaExiste
*     GRA_CondRetNaoAchou
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do grafo direcionado.
*
*  Assertivas de saída
*     - Valem as assertivas estruturais do grafo direcionado.
*
***********************************************************************/
GRA_tpCondRet GRA_InserirArestaDoCorrentePara(GRA_tppGrafo pGrafoParm, char *nomeAresta, char *nomeVerticeDestino);


/***********************************************************************
*
*  Função: GRA Obter o valor contido no vértice corrente
*
*  Descrição
*     Obtem o valor contido no vértice corrente do grafo
*
*  Parâmetros
*     pGrafoParm - ponteiro para o grafo de onde se quer o valor
*     ppValor    - ponteiro que terá o valor obtido.
*
*  Condições de retorno
*     GRA_CondRetOK
*     GRA_CondRetGrafoVazio
*     GRA_CondRetGrafoNaoFoiCriado
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do grafo direcionado.
*
*  Assertivas de saída
*     - Valem as assertivas estruturais do grafo direcionado.
*     - O valor retornado será o valor do vértice corrente do grafo.
*
***********************************************************************/
GRA_tpCondRet GRA_ObterValorCorrente(GRA_tppGrafo pGrafoParm, void **ppValor);


/***********************************************************************
*
*  Função: GRA Alterar o valor contido no vértice corrente
*
*  Descrição
*     Substitui o valor contido no vértice corrente do grafo
*     Obs.: A função não destroi o antigo valor.
*
*  Parâmetros
*     pGrafoParm - ponteiro para o grafo de onde se quer o valor
*     pValor     - ponteiro para o novo valor.
*
*  Condições de retorno
*     GRA_CondRetOK
*     GRA_CondRetGrafoVazio
*     GRA_CondRetGrafoNaoFoiCriado
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do grafo direcionado.
*
*  Assertivas de saída
*     - Valem as assertivas estruturais do grafo direcionado.
*     - O valor do vértice corrente será o valor do vértice passado por parâmetro.
*
***********************************************************************/
GRA_tpCondRet GRA_AlterarValorCorrente(GRA_tppGrafo pGrafoParm, void *pValor);


/***********************************************************************
*
*  Função: GRA Tornar o vértice corrente uma origem
*
*  Descrição
*     Torna o vértice corrente uma origem.
*
*  Parâmetros
*     pGrafoParm - ponteiro para o grafo de onde se quer o valor
*
*  Condições de retorno
*     GRA_CondRetOK
*     GRA_CondRetGrafoVazio
*     GRA_CondRetGrafoNaoFoiCriado
*     GRA_CondRetJaExiste
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do grafo direcionado.
*
*  Assertivas de saída
*     - Valem as assertivas estruturais do grafo direcionado.
*     - Vértice corrente é adicionado à lista de origens.
*
***********************************************************************/
GRA_tpCondRet GRA_TornarCorrenteUmaOrigem(GRA_tppGrafo pGrafoParm);

/* Navegaçao */
GRA_tpCondRet GRA_IrParaVerticeAdjacente(GRA_tppGrafo pGrafoParm, char *nomeDaAresta);
GRA_tpCondRet GRA_SeguirPelaAresta(GRA_tppGrafo pGrafoParm, char *nomeAresta);
GRA_tpCondRet GRA_IrParaAOrigem(GRA_tppGrafo pGrafoParm, char *nomeVertice);

/* Destruir grafo */
GRA_tpCondRet GRA_DestruirVerticeCorrente(GRA_tppGrafo pGrafoParm);
GRA_tpCondRet GRA_DestruirArestaAdjacente(GRA_tppGrafo pGrafoParm, char *pNomeAresta);

/***********************************************************************/
#undef GRAFO_EXT

/********** Fim do módulo de definição: GRA Grafo direcionado **********/

#else
#endif
