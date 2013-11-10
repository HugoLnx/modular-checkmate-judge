/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTPAR.C
*  Letras identificadoras:      TPAR
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data     Observações
*       1.00   hg e nf  15/09/2013 Adaptação do módulo para manipular matrizes
*
*  $ED Descrição do módulo
*     Este mÇodulo contém as funções específicas para o teste do
*     módulo matriz. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo matriz:
*
*
*     "=criar"           - chama a função PAR_CriarMatriz( )
*     "=irPara"         - chama a função PAR_IrPara( )
*     "=atribuir" <Char> - chama a função PAR_AtribuirValorCorr(  )
*     "=destroi"         - chama a função PAR_DestruirMatriz( )
*     "=obter" <Char>    - chama a função PAR_ObterValorCorr( ) e compara
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

#include    "partida.h"
#include    "checkmate_judge.h"
#include    "mem_manager.h"

/* Tabela dos nomes dos comandos de teste relacionados ao módulo */

#define     CRIAR_APAR_CMD       "=criar"
#define     OBTER_VAL_CMD       "=obter"
#define     ATRIBUIR_VAL_CMD    "=atribuir"
#define     DESTROI_CMD         "=destruir"

#define     IR_PARA_CMD        "=irPara"
#define     IR_CASA_CMD        "=ircasa"
#define     CRIAR_PECA_CMD     "=criarPeca"
#define     ALTERAR_PECA_CMD   "=alterarPeca"
#define     INSERIR_PECA_CMD   "=inserirPeca"
#define     REMOVER_PECA_CMD   "=removerPeca"
#define     INSERIR_REI_CMD    "=inserirRei"
#define     REMOVER_REI_CMD    "=removerRei"
#define     IR_REI_CMD         "=ircasarei"
#define     PEGADA_INIMIGA_CMD "=pegadaInimiga?"
#define     EH_CHECKMATE_CMD   "=ehCheckmate?"
#define     CRIAR_PEG_CMD      "=criarPegadas"

#define     FIM_CMD         "=fim"


#define     ANALISES_SIZE 10
#define     MAX_PASSOS_STR   50
#define     MAX_NOME_PECA    30
/*****  Código das funções exportadas pelo módulo  *****/
static PAR_tppPartida pPartida = NULL;

/***********************************************************************
*
*  $FC Função: TPAR Efetuar operações de teste específicas para matriz
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     matriz sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
   {

      JUD_tpCondRet CondRetObtido   = JUD_CondRetOK ;
      JUD_tpCondRet CondRetEsperada = JUD_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      int IndiceValorEsperado = -1;
	   int IndiceValorObtido = -1;
	   int IndiceValorDado = -1;

      int  NumLidos = -1;

      TST_tpCondRet Ret;

      if (pPartida == NULL)
      {
         PAR_CriarPartida(&pPartida);
      }
		/* Testar PAR Eh checkmate*/

		 if (strcmp( ComandoTeste, EH_CHECKMATE_CMD) == 0 )
       {
          int respostaEsperada, respostaObtida;
          TST_tpCondRet condRet;
			 NumLidos = LER_LerParametros("ii", &respostaEsperada, &CondRetEsperada) ;
          
          if (NumLidos != 2)
          {
             return TST_CondRetParm ;
          }
          
          CondRetObtido = JUD_EhCheckmate(pPartida, &respostaObtida);
          
          condRet = TST_CompararInt(CondRetEsperada, CondRetObtido,
                     "Não foi possível verificar se eh checkmate.");

          if (condRet != TST_CondRetOK)
          {
             return condRet;
          }

          return TST_CompararInt(respostaEsperada, respostaObtida,
                     "Foi obtida uma resposta diferente da esperada para a verificação de checkmate");

       }

		/* Testar PAR Criar peca*/

		 else if ( strcmp( ComandoTeste , CRIAR_PECA_CMD ) == 0 )
       {

         char *nome, *passosStr;
         int iTipoMovimento;
         MPEC_tpTipoMovimento tipo;
         LIS_tppLista pPassos;
         MEM_Alloc(sizeof(char)*MAX_NOME_PECA, (void**) &nome);
         MEM_Alloc(sizeof(char)*MAX_PASSOS_STR, (void**) &passosStr);

			NumLidos = LER_LerParametros("ssii", nome, passosStr, &iTipoMovimento, &CondRetEsperada) ;
         if (NumLidos != 4)
         {
            return TST_CondRetParm ;
         }

         ISP_LerPassos(passosStr, &pPassos);

         tipo = (MPEC_tpTipoMovimento) iTipoMovimento;
			CondRetObtido = PAR_CriarPeca(pPartida, nome, pPassos, tipo);

         return TST_CompararInt(CondRetEsperada, CondRetObtido,
								"Não foi possível criar a casa.");

       }


		/* Testar PAR Inserir peca*/

		 else if (strcmp( ComandoTeste, INSERIR_PECA_CMD) == 0 )
       {
         char *nomeCasa, *nomeModelo;
         int iTime;
         PEC_tpTimePeca time;
         LIS_tppLista pPassos;
         MEM_Alloc(sizeof(char)*MAX_NOME_PECA, (void**) &nomeModelo);
         MEM_Alloc(sizeof(char)*MAX_NOME_PECA, (void**) &nomeCasa);

			NumLidos = LER_LerParametros("ssii", nomeCasa, nomeModelo, &iTime, &CondRetEsperada) ;
         if (NumLidos != 4)
         {
            return TST_CondRetParm ;
         }

         time = (PEC_tpTimePeca) iTime;
         PAR_IrCasa(pPartida, nomeCasa);
         CondRetObtido = PAR_InserirPeca(pPartida, nomeModelo, time);

         return TST_CompararInt(CondRetEsperada, CondRetObtido,
								"Não foi possível inserir a peça.");

       }
       
       
		/* Testar PAR Remover peca*/

		 else if (strcmp( ComandoTeste, REMOVER_PECA_CMD) == 0 )
       {
         char *nomeCasa;
         MEM_Alloc(sizeof(char)*MAX_NOME_PECA, &nomeCasa);
			NumLidos = LER_LerParametros("si", nomeCasa, &CondRetEsperada) ;
         if (NumLidos != 2)
         {
            return TST_CondRetParm ;
         }

         PAR_IrCasa(pPartida, nomeCasa);
         CondRetObtido = PAR_RemoverPeca(pPartida);

         return TST_CompararInt(CondRetEsperada, CondRetObtido,
								"Não foi possível remover a peça.");

       }
       
       
		/* Testar PAR Remover rei*/

		 else if (strcmp( ComandoTeste, REMOVER_REI_CMD) == 0 )
       {
			NumLidos = LER_LerParametros("i", &CondRetEsperada) ;
         if (NumLidos != 1)
         {
            return TST_CondRetParm ;
         }

         CondRetObtido = PAR_RemoverRei(pPartida);

         return TST_CompararInt(CondRetEsperada, CondRetObtido,
								"Não foi possível remover o rei.");

       }
       

		/* Testar PAR Inserir rei */

		 else if (strcmp( ComandoTeste, INSERIR_REI_CMD) == 0 )
       {
          char *nomeCasa;
          MEM_Alloc(sizeof(char)*MAX_NOME_PECA, (void **) &nomeCasa);
			 NumLidos = LER_LerParametros("si", nomeCasa, &CondRetEsperada) ;
          
          if (NumLidos != 2)
          {
             return TST_CondRetParm ;
          }
          
          PAR_IrCasa(pPartida, nomeCasa);
          CondRetObtido = PAR_InserirRei(pPartida);
          
          return TST_CompararInt(CondRetEsperada, CondRetObtido,
								"Não foi possível inserir o rei.");

       }


      /* Testar Finalizar teste */

         else if ( strcmp( ComandoTeste , FIM_CMD ) == 0 )
         {
            MEM_LiberarTodaMemoriaAlocada();
            return TST_CondRetOK;
         }

      return TST_CondRetNaoConhec ;

   } /* Fim função: TPAR Efetuar operações de teste específicas para matriz */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
