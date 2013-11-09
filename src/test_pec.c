/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTPAR.C
*  Letras identificadoras:      TPAR
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*       1.00   hg e nf  15/09/2013 Adapta��o do m�dulo para manipular matrizes
*
*  $ED Descri��o do m�dulo
*     Este m�odulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo matriz. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo matriz:
*
*
*     "=criar"           - chama a fun��o PAR_CriarMatriz( )
*     "=irPara"         - chama a fun��o PAR_IrPara( )
*     "=atribuir" <Char> - chama a fun��o PAR_AtribuirValorCorr(  )
*     "=destroi"         - chama a fun��o PAR_DestruirMatriz( )
*     "=obter" <Char>    - chama a fun��o PAR_ObterValorCorr( ) e compara
*                          o valor retornado com o valor <Char>
*=alterarPeca  nomeAtual   novoNome   novosPassos   novoTipoMovimento   condRet
*
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include "peca.h"
#include "mem_manager.h"

/* Tabela dos nomes dos comandos de teste relacionados ao m�dulo */

#define     CRIAR_PEC_CMD       "=criar"
// #define     OBTER_VAL_CMD       "=obter"
// #define     ATRIBUIR_VAL_CMD    "=atribuir"
// #define     DESTROI_CMD         "=destruir"
// 
// #define     IR_PARA_CMD        "=irPara"
// #define     IR_CASA_CMD        "=ircasa"
// #define     CRIAR_PECA_CMD     "=criarPeca"
// #define     ALTERAR_PECA_CMD   "=alterarPeca"
// #define     INSERIR_PECA_CMD   "=inserirPeca"
// #define     REMOVER_PECA_CMD   "=removerPeca"
// #define     INSERIR_REI_CMD    "=inserirRei"
// #define     REMOVER_REI_CMD    "=removerRei"
// #define     IR_REI_CMD         "=ircasarei"
// #define     PEGADA_INIMIGA_CMD "=pegadaInimiga?"
// #define     EH_CHECKMATE_CMD   "=ehCheckmate?"
// #define     CRIAR_PEG_CMD      "=criarPegadas"
// 
// #define     FIM_CMD         "=fim"
// 
// /* Tabela dos nomes dos comandos de teste espec�ficos do teste */
// #define     VALIDAR_EST_PAR_CMD "=validarEstrutura"
// #define     SELECIONAR_CMD       "=selecionar"


// #define     PARTIDAS_SIZE 10
// #define     MAX_PASSOS_STR   50
// #define     MAX_NOME_PECA    30
/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

//static PAR_tppPartida Partidas[PARTIDAS_SIZE];

static PEC_tppPeca ppPeca = NULL;

//static int iPar = 0 ;


TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{

   PEC_tpCondRet CondRetObtido;
   PEC_tpCondRet CondRetEsperada;
   
   int IndiceValorEsperado = -1;
   int IndiceValorObtido = -1;
   int IndiceValorDado = -1;

   int NumLidos = -1;

   // Testar cria��o de pe�a

   if ( strcmp( ComandoTeste , CRIAR_PEC_CMD ) == 0 )
   {
      char *pNomePeca, *pPassos, *nome;
      PEC_tpTipoMovimento tipoMovimento;

      MEM_Alloc(sizeof(char)*20,(void**)&pNomePeca);
      MEM_Alloc(sizeof(char)*20,(void**)&nome);
      MEM_Alloc(sizeof(char)*50,(void**)&pPassos);

      NumLidos = LER_LerParametros( "ssii" , pNomePeca, pPassos, &tipoMovimento, &CondRetEsperada ) ;
      if ( NumLidos != 4 )
      {
         return TST_CondRetParm ;
      }

      CondRetObtido = PEC_CriarPeca(&ppPeca,pNomePeca,pPassos,tipoMovimento);

      return TST_CompararInt( CondRetEsperada , CondRetObtido ,
         "Nao foi possivel criar peca.") ;

   } 

   return TST_CondRetNaoConhec ;

} /* Fim fun��o: TPAR Efetuar opera��es de teste espec�ficas para matriz */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
