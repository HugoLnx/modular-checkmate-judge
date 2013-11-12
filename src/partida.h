#if ! defined( PARTIDA_ )
#define PARTIDA_
/***************************************************************************
*
*  M�dulo de defini��o: PAR  Partida
*
*  Arquivo gerado:              partida.h
*  Letras identificadoras:      PAR
*
*	Autores:
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Manipula��o das informa��es que comp�es uma partida.
*
*  Descri��o do m�dulo
*     M�dulo respons�vel por representar uma partida, que � composta de um set de
*     modelos de pe�a e um tabuleiro onde podem ser inseridas v�rias inst�ncias
*     de um desses modelos.
*
*     Em cada partida pode ter no m�ximo um rei aliado o modelo desta pe�a n�o
*     precisa ser criado, basta utilizar as fun��es especiais para manipula��o
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

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma <estrutura-manipulada> */
typedef struct PAR_stPartida* PAR_tppPartida;


/***********************************************************************
*
*  Tipo de dados: PAR Condi��es de retorno
*
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es exportadas.
*
***********************************************************************/
   typedef enum {

         PAR_CondRetOK = 0,
               /* Executou correto */

         PAR_CondRetNaoEhCasa = 2,
               /* N�o � n� na dire��o desejada */

         PAR_CondRetPartidaNaoExiste = 3,
               /* Partida n�o existe */

         PAR_CondRetFaltouMemoria = 5,
               /* Faltou mem�ria ao alocar dados */

         PAR_CondRetPecaNaoEncontrada = 6,
               /* A pe�a buscada n�o foi encontrada */

         PAR_CondRetCasaJahTemPeca = 8,
               /* A casa j� tem pe�a */

         PAR_CondRetPecaJaExiste = 9,
               /* Pe�a que tentou adicionar j� existe */

         PAR_CondRetCaminhoErrado = 7
               /* caminho para salvar e/ou carregar � inv�lido */

   } PAR_tpCondRet;


/***********************************************************************/

/***********************************************************************
*
*  Fun��o: PAR Criar partida
*
*  Descri��o
*     Cria uma inst�ncia de partida.
*
*  Par�metros
*     ppPartida      - Refer�ncia usada no retorno da nova inst�ncia.
*
*  Condi��es de retorno
*     PAR_CondRetOK
*     PAR_CondRetFaltouMemoria
*
*  Retorno por refer�ncia
*     ppPartida - Nova inst�ncia de partida.
*
*  Hip�teses
*     - ppPartida n�o apontar� para nenhuma estrutura que necessite ser
*       tratada de forma alguma.
*
*  Assertivas de entrada
*     - ppPartida � um ponteiro v�lido.
*
*  Assertivas de saida
*     - ppPartida aponta para uma inst�ncia v�lida de partida.
*
***********************************************************************/
   PAR_tpCondRet PAR_CriarPartida(PAR_tppPartida *ppPartida);


/***********************************************************************
*
*  Fun��o: PAR Inserir rei
*
*  Descri��o
*     Insere um rei na casa atual.
*
*  Par�metros
*     pPartida   - Partida que ser� usada como base.
*
*  Condi��es de retorno
*     PAR_CondRetOK
*     PAR_CondRetCasaJahTemPeca
*     PAR_CondRetFaltouMemoria
*     PAR_CondRetPartidaNaoExiste
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida v�lida.
*
*  Assertivas de saida
*     - pPartida aponta para uma Partida v�lida.
*     - Caso casa corrente n�o tivesse nenhuma pe�a, agora ela ter� um rei
*       como pe�a, caso contr�rio ela continuar� com a mesma pe�a.
*
***********************************************************************/
   PAR_tpCondRet PAR_InserirRei(PAR_tppPartida pPartida);


/***********************************************************************
*
*  Fun��o: PAR Remover rei
*
*  Descri��o
*     Remove o rei da partida, como ele � �nico, n�o importa a casa
*     em que ele se encontra.
*
*  Par�metros
*     pAnalise   - PartidaAnalise que ser� usada como base.
*
*  Condi��es de retorno
*     PAR_CondRetOK
*     PAR_CondRetPecaNaoEncontrada
*     PAR_CondRetPartidaNaoExiste
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida v�lida.
*     - Partida tem um rei.
*
*  Assertivas de saida
*     - Partida continua valida.
*     - Partida n�o tem rei.
*
***********************************************************************/
   PAR_tpCondRet PAR_RemoverRei(PAR_tppPartida pPartida);
   

/***********************************************************************
*
*  Fun��o: PAR Ir casa rei
*
*  Descri��o
*     Muda corrente para apontar para a casa onde se encontra o rei.
*
*  Par�metros
*     pPartida       - Partida que ser� usada como base.
*
*  Condi��es de retorno
*     PAR_CondRetOK
*     PAR_CondRetPartidaNaoExiste
*     PAR_CondRetPecaNaoEncontrada
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida v�lida.
*
*  Assertivas de saida
*     - Caso a partida tenha rei, o corrente aponta para a casa onde
*       se encontra o rei, caso contr�rio permanece no mesmo local.
*
***********************************************************************/
   PAR_tpCondRet PAR_IrCasaRei(PAR_tppPartida pPartida);

/***********************************************************************
*
*  Fun��o: PAR Destruir partida
*
*  Descri��o da fun��o
*     Destroi a instancia de an�lise, liberando seu espa�o da mem�ria.
*
*  Par�metros
*     ppPartida - � o ponteiro para a an�lise que ser� destruida.
*                 Este par�metro � passado por refer�ncia.
*
*  Condi��es de retorno
*     PAR_CondRetOK
*     PAR_CondRetPartidaNaoExiste
*
*  Retorno por refer�ncia
*     ppPartida - retorno � NULL
*
*  Assertivas de entrada
*     - ppPartida � NULL ou aponta para uma Partida v�lida.
*
*  Assertivas de saida
*     - A instancia apontada por ppPartida � liberada da mem�ria.
*     - ppPartida aponta para NULL
*
***********************************************************************/
   PAR_tpCondRet PAR_DestruirPartida(PAR_tppPartida *ppPartida);


/***********************************************************************
*
*  Fun��o: PAR Ir casa
*
*  Descri��o
*     Muda corrente baseado no nome da casa.
*
*  Par�metros
*     pPartida - Partida que ser� usada como base.
*     nomeCasa - Nome de uma casa no tabuleiro da partida.
*
*  Condi��es de retorno
*     PAR_CondRetOK
*     PAR_CondRetNaoEhCasa
*     PAR_CondRetPartidaNaoExiste
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida v�lida.
*
*  Assertivas de saida
*     - O corrente de pPartida aponta para a casa com o nome igual ao passado
*       por par�metro, ou permanece o mesmo, caso n�o exista casa com este nome.
*
***********************************************************************/
   PAR_tpCondRet PAR_IrCasa(PAR_tppPartida pPartida, char *nomeCasa);


/***********************************************************************
*
*  Fun��o: PAR Criar peca
*
*  Descri��o
*     Cria uma pe�a para ser inserida posteriormente em uma casa.
*
*  Par�metros
*     pPartida       - Partida que ser� usada como base.
*     nome           - Nome da pe�a que est� sendo criada.
*     pPassos        - Lista de passos que a pe�a seguir�.
*     tipoMovimento  - Tipo de movimento da pe�a.
*
*  Condi��es de retorno
*     PAR_CondRetOK
*     PAR_CondRetPartidaNaoExiste
*     PAR_CondRetPecaJaExiste
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida v�lida.
*     - nome � uma string v�lida.
*     - Valem as assertivas estruturais da lista para pPassos.
*
*  Assertivas de saida
*     A organiza��o do tabuleiro da partida permanece a mesma.
*
***********************************************************************/
   PAR_tpCondRet PAR_CriarPeca(PAR_tppPartida pPartida, char *nome,
      LIS_tppLista pPassos, MPEC_tpTipoMovimento tipoMovimento);


/***********************************************************************
*
*  Fun��o: PAR Alterar peca
*
*  Descri��o
*     Modifica um modelo de pe�a.
*
*  Par�metros
*     pAnalise       - PartidaAnalise que ser� usada como base.
*     nomeAtual      - Nome atual da pe�a que est� sendo alterada.
*     nomeNovo       - Nome novo para pe�a.
*     pPassos        - Lista de passos que a pe�a seguir�.
*     tipoMovimento  - Tipo de movimento da pe�a.
*
*  Condi��es de retorno
*     PAR_CondRetOK
*     PAR_CondRetPartidaNaoExiste
*     PAR_CondRetPecaJaExiste
*     PAR_CondRetPecaNaoEncontrada
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida v�lida.
*     - Existe uma pe�a com o nome procurado.
*     - N�o existe pe�a com o nome novo.
*
*  Assertivas de saida
*     - N�o existir� mais uma pe�a com o nome antigo.
*     - Todas as pe�as que usavam o modelo antigo agora estar�o
*       usando o modelo novo.
*
***********************************************************************/
   PAR_tpCondRet PAR_AlterarPeca(PAR_tppPartida pPartida, char *nomeAtual, char* nomeNovo,
      LIS_tppLista pNovosPassos, MPEC_tpTipoMovimento novoTipoMovimento);


/***********************************************************************
*
*  Fun��o: PAR Inserir pe�a
*
*  Descri��o
*     Insere uma pe�a inst�ncia de um modelo de pe�a pr�-determinado em
*     na casa corrente da partida.
*
*  Par�metros
*     pPartida   - Partida que ser� usada como base.
*     nome       - Nome do modelo de pe�a que ser� instanciado.
*     time       - Time da pe�a.
*
*  Condi��es de retorno
*     PAR_CondRetOK
*     PAR_CondRetPartidaNaoExiste
*     PAR_CondRetPecaJaExiste
*     PAR_CondRetPecaNaoEncontrada
*     PAR_CondRetFaltouMemoria
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida v�lida.
*     - Existe uma pe�a com o nome procurado.
*     - Casa corrente n�o possui pe�a.
*
*  Assertivas de saida
*     - Casa corrente possuir� uma inst�ncia do modelo
*       com o nome escolhido.
*
***********************************************************************/
   PAR_tpCondRet PAR_InserirPeca(PAR_tppPartida pPartida, char *nome, PEC_tpTimePeca time);


/***********************************************************************
*
*  Fun��o: PAR Remover pe�a
*
*  Descri��o
*     Remove pe�a da casa corrente.
*
*  Par�metros
*     pAnalise   - PartidaAnalise que ser� usada como base.
*
*  Condi��es de retorno
*     PAR_CondRetOK
*     PAR_CondRetPecaNaoEncontrada
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida v�lida.
*     - Casa corrente possui pe�a.
*
*  Assertivas de saida
*     - Partida n�o tem pe�a na casa corrente.
*
***********************************************************************/
   PAR_tpCondRet PAR_RemoverPeca(PAR_tppPartida pPartida);


/***********************************************************************
*
*  Fun��o: PAR Obter pe�a
*
*  Descri��o
*     Recupera a pe�a da casa corrente.
*
*  Par�metros
*     pAnalise   - PartidaAnalise que ser� usada como base.
*     ppPeca     - Refer�ncia utilizada para retornar a pe�a.
*
*  Condi��es de retorno
*     PAR_CondRetOK
*     PAR_CondRetPecaNaoEncontrada
*
*  Retorno por refer�ncia
*     ppPeca - Retorna a pe�a existente na casa corrente.
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida v�lida.
*     - Casa corrente tem pe�a.
*
*  Assertivas de saida
*     - Partida n�o � alterada.
*     - ppPeca aponta para pe�a presente na casa corrente.
*
***********************************************************************/
   PAR_tpCondRet PAR_ObterPeca(PAR_tppPartida pPartida, PEC_tppPeca *ppPeca);


/***********************************************************************
*
*  Fun��o: PAR Salvar
*
*  Descri��o
*     Salva uma vers�o serializada da partida em um arquivo texto.
*
*  Par�metros
*     pPartida   - Partida que ser� usada como base.
*     caminho    - caminho do arquivo que ser� criado.
*
*  Condi��es de retorno
*     PAR_CondRetOK
*     PAR_CondRetCaminhoErrado
*
*  Assertivas de entrada
*     - pPartida aponta para uma Partida v�lida.
*     - Caminho aponta para um arquivo inexistente em um diret�rio existente.
*
*  Assertivas de saida
*     - Partida n�o � alterada.
*     - � criado um arquivo com a partida serializada no caminho especificado.
*
***********************************************************************/
   PAR_tpCondRet PAR_Salvar(PAR_tppPartida pPartida, char *caminho);


/***********************************************************************
*
*  Fun��o: PAR Carregar
*
*  Descri��o
*     L� um arquivo de partida serializada e cria uma inst�ncia
*     de partida baseado no conte�do do arquivo.
*
*  Par�metros
*     ppPartida   - Refer�ncia para retorno da nova partida.
*     caminho    - Caminho para o arquivo que ser� carregado.
*
*  Condi��es de retorno
*     PAR_CondRetOK
*     PAR_CondRetCaminhoErrado
*     PAR_CondRetFaltouMemoria
*
*  Retorno por refer�ncia
*     ppPartida - Inst�ncia de partida baseada no arquivo texto.
*
*  Assertivas de entrada
*     - ppPartida � um ponteiro v�lido.
*     - Caminho aponta para um arquivo inexistente em um diret�rio existente.
*
*  Assertivas de saida
*     - � criada uma partida de acordo com o conte�do do arquivo texto.
*
***********************************************************************/
   PAR_tpCondRet PAR_Carregar(PAR_tppPartida ppPartida, char *caminho);

#undef PARTIDA_EXT

/********** Fim do m�dulo de defini��o: PAR <nome-do-m�dulo> **********/

#else
#endif
