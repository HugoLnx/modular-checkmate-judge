#if ! defined( PARTIDA_ )
#define PARTIDA_
/***************************************************************************
*
*  Módulo de definição: PAR  Partida
*
*  Arquivo gerado:              partida.h
*  Letras identificadoras:      PAR
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Manipulação das informações que compões uma partida.
*
*  Descrição do módulo
*     Módulo responsável por representar uma partida, que é composta de um set de
*     modelos de peça e um tabuleiro onde podem ser inseridas várias instâncias
*     de um desses modelos.
*
*     Em cada partida pode ter no máximo um rei aliado o modelo desta peça não
*     precisa ser criado, basta utilizar as funções especiais para manipulação
*     do rei.
*
***************************************************************************/
 
#if defined( PARTIDA_OWN )
   #define PARTIDA_EXT
#else
   #define PARTIDA_EXT extern
#endif

#include "lista.h"
#include "direcao.h"
#include "tabuleiro.h"
#include "peca.h"
#include "modelo_peca.h"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma <estrutura-manipulada> */
typedef struct PAR_stPartida* PAR_tppPartida;


/***********************************************************************
*
*  Tipo de dados: PAR Condições de retorno
*
*
*  Descrição do tipo
*     Condições de retorno das funções exportadas.
*
***********************************************************************/
   typedef enum {

         PAR_CondRetOK = 0,
               /* Executou correto */

         PAR_CondRetNaoEhCasa = 2,
               /* Não é nó na direção desejada */

         PAR_CondRetPartidaNaoExiste = 3,
               /* Partida não existe */

         PAR_CondRetFaltouMemoria = 5,
               /* Faltou memória ao alocar dados */

         PAR_CondRetPecaNaoEncontrada = 6,
               /* A peça buscada não foi encontrada */

         PAR_CondRetCasaJahTemPeca = 8,
               /* A casa já tem peça */

         PAR_CondRetPecaJaExiste = 9,
               /* Peça que tentou adicionar já existe */

         PAR_CondRetCaminhoErrado = 7
               /* caminho para salvar e/ou carregar é inválido */

   } PAR_tpCondRet;


/***********************************************************************/

/***********************************************************************
*
*  Função: PAR Criar partida
*
*  Descrição
*     Cria uma instância de partida.
*
*  Parâmetros
*     ppPartida      - Referência usada no retorno da nova instância.
*
*  Condições de retorno
*     PAR_CondRetOK
*     PAR_CondRetFaltouMemoria
*
*  Retorno por referência
*     ppPartida - Nova instância de partida.
*
*  Hipóteses
*     - ppPartida não apontará para nenhuma estrutura que necessite ser
*       tratada de forma alguma.
*
*  Assertivas de entrada
*     - ppPartida é um ponteiro válido.
*
*  Assertivas de saida
*     - ppPartida aponta para uma instância válida de partida.
*
***********************************************************************/
   PAR_tpCondRet PAR_CriarPartida(PAR_tppPartida *ppPartida);


/***********************************************************************
*
*  Função: PAR Inserir rei
*
*  Descrição
*     Insere um rei na casa atual.
*
*  Parâmetros
*     pPartida   - Partida que será usada como base.
*
*  Condições de retorno
*     PAR_CondRetOK
*     PAR_CondRetCasaJahTemPeca
*     PAR_CondRetFaltouMemoria
*     PAR_CondRetPartidaNaoExiste
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida válida.
*
*  Assertivas de saida
*     - pPartida aponta para uma Partida válida.
*     - Caso casa corrente não tivesse nenhuma peça, agora ela terá um rei
*       como peça, caso contrário ela continuará com a mesma peça.
*
***********************************************************************/
   PAR_tpCondRet PAR_InserirRei(PAR_tppPartida pPartida);


/***********************************************************************
*
*  Função: PAR Remover rei
*
*  Descrição
*     Remove o rei da partida, como ele é único, não importa a casa
*     em que ele se encontra.
*
*  Parâmetros
*     pAnalise   - PartidaAnalise que será usada como base.
*
*  Condições de retorno
*     PAR_CondRetOK
*     PAR_CondRetPecaNaoEncontrada
*     PAR_CondRetPartidaNaoExiste
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida válida.
*     - Partida tem um rei.
*
*  Assertivas de saida
*     - Partida continua valida.
*     - Partida não tem rei.
*
***********************************************************************/
   PAR_tpCondRet PAR_RemoverRei(PAR_tppPartida pPartida);
   

/***********************************************************************
*
*  Função: PAR Ir casa rei
*
*  Descrição
*     Muda corrente para apontar para a casa onde se encontra o rei.
*
*  Parâmetros
*     pPartida       - Partida que será usada como base.
*
*  Condições de retorno
*     PAR_CondRetOK
*     PAR_CondRetPartidaNaoExiste
*     PAR_CondRetPecaNaoEncontrada
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida válida.
*
*  Assertivas de saida
*     - Caso a partida tenha rei, o corrente aponta para a casa onde
*       se encontra o rei, caso contrário permanece no mesmo local.
*
***********************************************************************/
   PAR_tpCondRet PAR_IrCasaRei(PAR_tppPartida pPartida);

/***********************************************************************
*
*  Função: PAR Destruir partida
*
*  Descrição da função
*     Destroi a instancia de análise, liberando seu espaço da memória.
*
*  Parâmetros
*     ppPartida - é o ponteiro para a análise que será destruida.
*                 Este parâmetro é passado por referência.
*
*  Condições de retorno
*     PAR_CondRetOK
*     PAR_CondRetPartidaNaoExiste
*
*  Retorno por referência
*     ppPartida - retorno é NULL
*
*  Assertivas de entrada
*     - ppPartida é NULL ou aponta para uma Partida válida.
*
*  Assertivas de saida
*     - A instancia apontada por ppPartida é liberada da memória.
*     - ppPartida aponta para NULL
*
***********************************************************************/
   PAR_tpCondRet PAR_DestruirPartida(PAR_tppPartida *ppPartida);


/***********************************************************************
*
*  Função: PAR Ir casa
*
*  Descrição
*     Muda corrente baseado no nome da casa.
*
*  Parâmetros
*     pPartida - Partida que será usada como base.
*     nomeCasa - Nome de uma casa no tabuleiro da partida.
*
*  Condições de retorno
*     PAR_CondRetOK
*     PAR_CondRetNaoEhCasa
*     PAR_CondRetPartidaNaoExiste
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida válida.
*
*  Assertivas de saida
*     - O corrente de pPartida aponta para a casa com o nome igual ao passado
*       por parâmetro, ou permanece o mesmo, caso não exista casa com este nome.
*
***********************************************************************/
   PAR_tpCondRet PAR_IrCasa(PAR_tppPartida pPartida, char *nomeCasa);


/***********************************************************************
*
*  Função: PAR Criar peca
*
*  Descrição
*     Cria uma peça para ser inserida posteriormente em uma casa.
*
*  Parâmetros
*     pPartida       - Partida que será usada como base.
*     nome           - Nome da peça que está sendo criada.
*     pPassos        - Lista de passos que a peça seguirá.
*     tipoMovimento  - Tipo de movimento da peça.
*
*  Condições de retorno
*     PAR_CondRetOK
*     PAR_CondRetPartidaNaoExiste
*     PAR_CondRetPecaJaExiste
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida válida.
*     - nome é uma string válida.
*     - Valem as assertivas estruturais da lista para pPassos.
*
*  Assertivas de saida
*     A organização do tabuleiro da partida permanece a mesma.
*
***********************************************************************/
   PAR_tpCondRet PAR_CriarPeca(PAR_tppPartida pPartida, char *nome,
      LIS_tppLista pPassos, MPEC_tpTipoMovimento tipoMovimento);


/***********************************************************************
*
*  Função: PAR Alterar peca
*
*  Descrição
*     Modifica um modelo de peça.
*
*  Parâmetros
*     pAnalise       - PartidaAnalise que será usada como base.
*     nomeAtual      - Nome atual da peça que está sendo alterada.
*     nomeNovo       - Nome novo para peça.
*     pPassos        - Lista de passos que a peça seguirá.
*     tipoMovimento  - Tipo de movimento da peça.
*
*  Condições de retorno
*     PAR_CondRetOK
*     PAR_CondRetPartidaNaoExiste
*     PAR_CondRetPecaJaExiste
*     PAR_CondRetPecaNaoEncontrada
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida válida.
*     - Existe uma peça com o nome procurado.
*     - Não existe peça com o nome novo.
*
*  Assertivas de saida
*     - Não existirá mais uma peça com o nome antigo.
*     - Todas as peças que usavam o modelo antigo agora estarão
*       usando o modelo novo.
*
***********************************************************************/
   PAR_tpCondRet PAR_AlterarPeca(PAR_tppPartida pPartida, char *nomeAtual, char* nomeNovo,
      LIS_tppLista pNovosPassos, MPEC_tpTipoMovimento novoTipoMovimento);


/***********************************************************************
*
*  Função: PAR Inserir peça
*
*  Descrição
*     Insere uma peça instância de um modelo de peça pré-determinado em
*     na casa corrente da partida.
*
*  Parâmetros
*     pPartida   - Partida que será usada como base.
*     nome       - Nome do modelo de peça que será instanciado.
*     time       - Time da peça.
*
*  Condições de retorno
*     PAR_CondRetOK
*     PAR_CondRetPartidaNaoExiste
*     PAR_CondRetPecaJaExiste
*     PAR_CondRetPecaNaoEncontrada
*     PAR_CondRetFaltouMemoria
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida válida.
*     - Existe uma peça com o nome procurado.
*     - Casa corrente não possui peça.
*
*  Assertivas de saida
*     - Casa corrente possuirá uma instância do modelo
*       com o nome escolhido.
*
***********************************************************************/
   PAR_tpCondRet PAR_InserirPeca(PAR_tppPartida pPartida, char *nome, PEC_tpTimePeca time);


/***********************************************************************
*
*  Função: PAR Remover peça
*
*  Descrição
*     Remove peça da casa corrente.
*
*  Parâmetros
*     pAnalise   - PartidaAnalise que será usada como base.
*
*  Condições de retorno
*     PAR_CondRetOK
*     PAR_CondRetPecaNaoEncontrada
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida válida.
*     - Casa corrente possui peça.
*
*  Assertivas de saida
*     - Partida não tem peça na casa corrente.
*
***********************************************************************/
   PAR_tpCondRet PAR_RemoverPeca(PAR_tppPartida pPartida);


/***********************************************************************
*
*  Função: PAR Obter peça
*
*  Descrição
*     Recupera a peça da casa corrente.
*
*  Parâmetros
*     pAnalise   - PartidaAnalise que será usada como base.
*     ppPeca     - Referência utilizada para retornar a peça.
*
*  Condições de retorno
*     PAR_CondRetOK
*     PAR_CondRetPecaNaoEncontrada
*
*  Retorno por referência
*     ppPeca - Retorna a peça existente na casa corrente.
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida válida.
*     - Casa corrente tem peça.
*
*  Assertivas de saida
*     - Partida não é alterada.
*     - ppPeca aponta para peça presente na casa corrente.
*
***********************************************************************/
   PAR_tpCondRet PAR_ObterPeca(PAR_tppPartida pPartida, PEC_tppPeca *ppPeca);


/***********************************************************************
*
*  Função: PAR Salvar
*
*  Descrição
*     Salva uma versão serializada da partida em um arquivo texto.
*
*  Parâmetros
*     pPartida   - Partida que será usada como base.
*     caminho    - caminho do arquivo que será criado.
*
*  Condições de retorno
*     PAR_CondRetOK
*     PAR_CondRetCaminhoErrado
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida válida.
*     - Caminho aponta para um arquivo inexistente em um diretório existente.
*
*  Assertivas de saida
*     - Partida não é alterada.
*     - É criado um arquivo com a partida serializada no caminho especificado.
*
***********************************************************************/
   PAR_tpCondRet PAR_Salvar(PAR_tppPartida pPartida, char *caminho);


/***********************************************************************
*
*  Função: PAR Carregar
*
*  Descrição
*     Lê um arquivo de partida serializada e cria uma instância
*     de partida baseado no conteúdo do arquivo.
*
*  Parâmetros
*     ppPartida   - Referência para retorno da nova partida.
*     caminho    - Caminho para o arquivo que será carregado.
*
*  Condições de retorno
*     PAR_CondRetOK
*     PAR_CondRetCaminhoErrado
*     PAR_CondRetFaltouMemoria
*
*  Retorno por referência
*     ppPartida - Instância de partida baseada no arquivo texto.
*
*  Assertivas de entrada
*     - ppPartida é um ponteiro válido.
*     - Caminho aponta para um arquivo inexistente em um diretório existente.
*
*  Assertivas de saida
*     - É criada uma partida de acordo com o conteúdo do arquivo texto.
*
***********************************************************************/
   PAR_tpCondRet PAR_Carregar(PAR_tppPartida ppPartida, char *caminho);

#undef PARTIDA_EXT

/********** Fim do módulo de definição: PAR <nome-do-módulo> **********/

#else
#endif
