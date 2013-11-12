#if ! defined( MODELO_PECA_ )
#define MODELO_PECA_
/***************************************************************************
*
*  Módulo de definição: MPEC  Modelo de Peça
*
*  Arquivo gerado:              modelo_peca.h
*  Letras identificadoras:      MPEC
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Manipulação básica de modelo de peça
*
*  Descrição do módulo
*     Módulo responsável por manipular os elementos que compõe um modelo de peça.
*
***************************************************************************/

#if defined( MODELO_PECA_OWN )
#define MODELO_PECA_EXT
#else
#define MODELO_PECA_EXT extern
#endif

#include "lista.h"

/***********************************************************************
*
*  Tipo de dados: MPEC Tipos de movimentos
*
*
*  Descrição do tipo
*     Tipos de movimento da pela.
*
***********************************************************************/
typedef enum {
   ANDA = 0,
      /* Peça pode comer qualquer peça em seu caminho */

   VOA = 1
      /*`Peça só pode comer se a pela estiver na última casa
         de seu caminho */
} MPEC_tpTipoMovimento;



/***********************************************************************
*
*  Tipo de dados: MPEC Condições de retorno
*
*  Descrição do tipo
*     Condições de retorno das funções exportadas.
*
***********************************************************************/
typedef enum {

   MPEC_CondRetOK,
   /* Executou correto */
      
   MPEC_CondRetFaltouMemoria,
   /* Faltou memória ao alocar dados */

   MPEC_CondRetNaoAlterou,
   /* Não foi possivel alterar a peca */

   MPEC_CondRetModeloNaoExiste
   /* Peça não existe */

} MPEC_tpCondRet ;


/* Tipo referência para um Modelo de Peça */
typedef struct MPEC_stModeloPeca* MPEC_tppModeloPeca;

/***********************************************************************
*
*  Função: MPEC Criar modelo peça
*
*  Descrição
*     Cria instância de um modelo peça.
*
*  Parâmetros
*     ppModelo      - Referência para retornar a nova instância
*     nome          - nome do modelo
*     pPassos       - lista de passos do modelo
*     tipoMovimento - tipo de movimento do modelo
*
*  Condições de retorno
*     MPEC_CondRetOK
*     MPEC_CondRetFaltouMemoria
*
*  Retorno por referência
*     ppModelo - Retorna a nova instância.
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais da lista para pPassos.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais do modelo de peça.
*
***********************************************************************/
MPEC_tpCondRet MPEC_CriarModeloPeca(MPEC_tppModeloPeca *ppModelo, char* nome, LIS_tppLista pPassos, MPEC_tpTipoMovimento tipoMovimento);

/***********************************************************************
*
*  Função: MPEC Destruir modelo de peça
*
*  Descrição
*     Destroi uma instância de modelo de peça.
*
*  Parâmetros
*     ppModelo - Modelo que será destruido.
*
*  Condições de retorno
*     MPEC_CondRetOK
*
*  Retorno por referência
*     ppModelo retorna NULL.
*
*  Assertivas de entrada
*     Valem as assertivas estruturais do modelo de peça.
*
*  Assertivas de saida
*     ppModelo aponta para NULL.
*
***********************************************************************/
MPEC_tpCondRet MPEC_DestruirModeloPeca(MPEC_tppModeloPeca *ppModelo);

/***********************************************************************
*
*  Função: MPEC Alterar modelo de peça
*
*  Descrição
*     Altera os elementos do modelo de peça.
*
*  Parâmetros
*     pModelo           - Modelo que será alterado.
*     novoNome          - novo nome do modelo
*     pPassos           - nova lista de passos do modelo
*     novoTipoMovimento - novo tipo de movimento do modelo
*
*  Condições de retorno
*     MPEC_CondRetOK
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do modelo de peça.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais do modelo de peça.
*
***********************************************************************/
MPEC_tpCondRet MPEC_AlterarModeloPeca(MPEC_tppModeloPeca pModelo, char *novoNome, LIS_tppLista pPassos, MPEC_tpTipoMovimento novoTipoMovimento);


/***********************************************************************
*
*  Função: MPEC Obter nome
*
*  Descrição
*     Recupera o nome do modelo de peça.
*
*  Parâmetros
*     pModeloParm - Modelo que será usado.
*     pNome       - Referência que será usada para retornar o nome.
*
*  Condições de retorno
*     MPEC_CondRetOK
*     MPEC_CondRetModeloNaoExiste
*
*  Retorno por referência
*     pNome - Retorna o nome relacionado ao modelo.
*
*  Assertivas de entrada
*     - pNome é um ponteiro válido.
*
*  Assertivas de saida
*     - Modelo não muda.
*     - pNome aponta para o nome do modelo.
*
***********************************************************************/
MPEC_tpCondRet MPEC_ObterNome(MPEC_tppModeloPeca pModelo, char **pNome);

/***********************************************************************
*
*  Função: MPEC Obter passos
*
*  Descrição
*     Recupera os passos do modelo de peça.
*
*  Parâmetros
*     pModeloParm - Modelo que será usado.
*     ppPassos       - Referência que será usada para retornar a lista de passos.
*
*  Condições de retorno
*     MPEC_CondRetOK
*     MPEC_CondRetModeloNaoExiste
*
*  Retorno por referência
*     pPassos - Retorna a lista de passos relacionada ao modelo.
*
*  Assertivas de entrada
*     - ppPassos é um ponteiro válido.
*
*  Assertivas de saida
*     - Modelo não muda.
*     - ppPassos aponta para a lista de passos do modelo.
*
***********************************************************************/
MPEC_tpCondRet MPEC_ObterPassos(MPEC_tppModeloPeca pModeloParm, LIS_tppLista *ppPassos);

/***********************************************************************
*
*  Função: MPEC Obter tipo de movimento
*
*  Descrição
*     Recupera os passos do modelo de peça.
*
*  Parâmetros
*     pModeloParm - Modelo que será usado.
*     pTipo       - Referência que será usada para retornar o tipo.
*
*  Condições de retorno
*     MPEC_CondRetOK
*     MPEC_CondRetModeloNaoExiste
*
*  Retorno por referência
*     pTipo - Retorna o tipo relacionado ao modelo.
*
*  Assertivas de entrada
*     - pTipo é um ponteiro válido.
*
*  Assertivas de saida
*     - Modelo não muda.
*     - pTipo aponta para o tipo do modelo.
*
***********************************************************************/
MPEC_tpCondRet MPEC_ObterTipo(MPEC_tppModeloPeca pModeloParm, MPEC_tpTipoMovimento *pTipo);

/***********************************************************************
*
*  Função: MPEC Salvar peça
*
*  Descrição
*     Alimenta o arquivo com uma serialização em texto do modelo de peça.
*
*  Parâmetros
*     pModeloPeca      - Modelo de peça que será usado.
*     pFile            - Arquivo que será incrementado.
*
*  Condições de retorno
*     MPEC_CondRetOK
*     MPEC_CondRetModeloNaoExiste
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do modelo de peça.
*     - Arquivo está aberto em modo de escrita.
*
*  Assertivas de saida
*     - Modelo de peça não foi alterado.
*     - Arquivo contém uma serialização do modelo de peça no final.
*
***********************************************************************/
MPEC_tpCondRet MPEC_Salvar(MPEC_tppModeloPeca pModeloPeca, FILE *pFile);

/***********************************************************************
*
*  Função: MPEC Salvar peça
*
*  Descrição
*     Alimenta o arquivo com uma serialização em texto dos modelos de peça.
*
*  Parâmetros
*     ppModelosPeca      - Modelos de peça que serão usados.
*     pFile              - Arquivo que será incrementado.
*
*  Condições de retorno
*     MPEC_CondRetOK
*     MPEC_CondRetModeloNaoExiste
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do modelo de peça.
*     - Valem as assertivas estruturais da lista.
*     - Arquivo está aberto em modo de escrita.
*
*  Assertivas de saida
*     - Nenhum modelo de peça não foi alterado.
*     - Arquivo contém uma serialização dos modelos de peça no final.
*
***********************************************************************/
MPEC_tpCondRet MPEC_SalvarLista(LIS_tppLista ppModelosPeca, FILE *pFile);

#undef MODELO_PECA_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
