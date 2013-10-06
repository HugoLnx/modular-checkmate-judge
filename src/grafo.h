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
*     - LIS_CondRetOK
*     - LIS_CondRetFaltouMemoria
* 
*  Retorno por referência
*     ppLista:
*       Se executou corretamente retorna o ponteiro para a lista.
*       Este ponteiro será utilizado pelas funções que manipulem esta lista.
*       
*       Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*       a função retornará NULL.
*       Não será dada mais informação quanto ao problema ocorrido.
*
*  Assertivas de entrada
*     <não tem>
*
*  Assertivas de saida
*     - Valem as assertivas estruturais da lista duplamente encadeada com cabeça.
*     - Ponteiros do corrente, inicio e final da lista não nulos.
*     - Número de elementos é 0.
*     - Funções de destruir e comparar serão iguais às passadas por parâmetro.
*
***********************************************************************/
GRA_tpCondRet GRA_CriarGrafo(GRA_tppGrafo *ppGrafo, void (*destruirValor)(void *pValor));


GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo *ppGrafo);

/* Construir grafo */
GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafoParm, char *pNomeVertice, void *pValor);
/* Ao criar a aresta, lembrar de inserir a aresta entre os sucessores da origem, e o vertice entre os antecessores do destino */
GRA_tpCondRet GRA_InserirArestaDoCorrentePara(GRA_tppGrafo pGrafoParm, char *nomeAresta, char *nomeVerticeDestino);

/* Obter e alterar */
GRA_tpCondRet GRA_ObterValorCorrente(GRA_tppGrafo pGrafoParm, void **ppValor);
GRA_tpCondRet GRA_AlterarValorCorrente(GRA_tppGrafo pGrafoParm, void *pValor);

/* Outros */
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
