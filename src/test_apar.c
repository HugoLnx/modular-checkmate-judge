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
#include    "lista.h"

#include    "generico.h"
#include    "lerparm.h"

#include    "partida.h"
#include    "analise_partida.h"
#include    "mem_manager.h"
#include    "input_string_parser.h"

/* Tabela dos nomes dos comandos de teste relacionados ao m�dulo */

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

/* Tabela dos nomes dos comandos de teste espec�ficos do teste */
#define     VALIDAR_EST_PAR_CMD "=validarEstrutura"
#define     SELECIONAR_CMD       "=selecionar"


#define     ANALISES_SIZE 10
#define     MAX_PASSOS_STR   50
#define     MAX_NOME_PECA    30
/*****  C�digo das fun��es exportadas pelo m�dulo  *****/
static APAR_tppAnalise Analises[ANALISES_SIZE];
static PAR_tppPartida pPartida = NULL;

static int iAna = 0;

/***********************************************************************
*
*  $FC Fun��o: TPAR Efetuar opera��es de teste espec�ficas para matriz
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     matriz sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
   {

      APAR_tpCondRet CondRetObtido   = APAR_CondRetOK ;
      APAR_tpCondRet CondRetEsperada = APAR_CondRetFaltouMemoria ;
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

      /* Testar PAR Criar matriz */

         if ( strcmp( ComandoTeste , CRIAR_APAR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            }

            CondRetObtido = APAR_CriarAnalise(Analises + iAna, pPartida) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar partida." ) ;

         }


      /* Testar PAR Destruir matriz */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            }

            CondRetObtido = APAR_DestruirAnalise(Analises + iAna) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o � poss�vel destruir uma matriz que n�o existe.") ;

         } 

		 
      /* Testar PAR Ir para */

		 else if ( strcmp( ComandoTeste , IR_PARA_CMD ) == 0 )
         {
            int iDirecao;
			   NumLidos = LER_LerParametros("ii" , &iDirecao, &CondRetEsperada);
            if (NumLidos != 2)
            {
               return TST_CondRetParm ;
            }

			   CondRetObtido = APAR_IrPara(Analises[iAna], (DIR_tpDirecao) iDirecao);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para essa direcao.") ;

         }


		/* Testar PAR Ir casa */

		 else if ( strcmp( ComandoTeste , IR_CASA_CMD ) == 0 )
       {

         char *nome;
         MEM_Alloc(sizeof(char)*3, (void**) &nome);

			NumLidos = LER_LerParametros( "si", nome, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            }

			CondRetObtido = APAR_IrCasa(Analises[iAna], nome) ;

         return TST_CompararInt( CondRetEsperada , CondRetObtido ,
								"N�o foi poss�vel ir para a casa.") ;

         }


		/* Testar PAR Ir casa rei */

		 else if (strcmp(ComandoTeste, IR_REI_CMD) == 0)
       {
           NumLidos = LER_LerParametros("i", &CondRetEsperada);
           if (NumLidos != 1)
           {
              return TST_CondRetParm ;
           }
           
           CondRetObtido = APAR_IrCasaRei(Analises[iAna]) ;
           
           return TST_CompararInt( CondRetEsperada , CondRetObtido ,
               "N�o foi poss�vel ir para a casa do rei.") ;

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
								"N�o foi poss�vel criar a casa.");

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
								"N�o foi poss�vel inserir a pe�a.");

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
								"N�o foi poss�vel remover a pe�a.");

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
								"N�o foi poss�vel remover o rei.");

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
								"N�o foi poss�vel inserir o rei.");

       }


//		/* Testar PAR Alguma pegada inimiga*/
//
//		 else if (strcmp( ComandoTeste, PEGADA_INIMIGA_CMD) == 0 )
//       {
//          int respostaEsperada, respostaObtida;
//          TST_tpCondRet condRet;
//			 NumLidos = LER_LerParametros("ii", &respostaEsperada, &CondRetEsperada) ;
//          
//          if (NumLidos != 2)
//          {
//             return TST_CondRetParm ;
//          }
//          
//          CondRetObtido = PAR_AlgumaPegadaInimiga(Analises[iAna], &respostaObtida);
//          
//          condRet = TST_CompararInt(CondRetEsperada, CondRetObtido,
//                     "N�o foi poss�vel verificar se existe alguma pegada inimiga.");
//
//          if (condRet != TST_CondRetOK)
//          {
//             return condRet;
//          }
//
//          return TST_CompararInt(respostaEsperada, respostaObtida,
//                     "Foi obtida uma resposta diferente da esperada");
//
//       }
//       
//
//		/* Testar PAR Eh checkmate*/
//
//		 else if (strcmp( ComandoTeste, EH_CHECKMATE_CMD) == 0 )
//       {
//          int respostaEsperada, respostaObtida;
//          TST_tpCondRet condRet;
//			 NumLidos = LER_LerParametros("ii", &respostaEsperada, &CondRetEsperada) ;
//          
//          if (NumLidos != 2)
//          {
//             return TST_CondRetParm ;
//          }
//          
//          CondRetObtido = PAR_EhCheckmate(Analises[iAna], &respostaObtida);
//          
//          condRet = TST_CompararInt(CondRetEsperada, CondRetObtido,
//                     "N�o foi poss�vel verificar se eh checkmate.");
//
//          if (condRet != TST_CondRetOK)
//          {
//             return condRet;
//          }
//
//          return TST_CompararInt(respostaEsperada, respostaObtida,
//                     "Foi obtida uma resposta diferente da esperada para a verifica��o de checkmate");
//
//       }



      /* Testar Selecionar indice na array de matrizes */

         else if ( strcmp( ComandoTeste , SELECIONAR_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                               &iAna ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			if ( iAna < 0 || iAna > ANALISES_SIZE - 1 )
			{
				TST_NotificarFalha("S� � poss�vel fazer sele��o nos indices de 0 � 9") ;
				return TST_CondRetErro ;
			} /* if */

			return TST_CondRetOK ;

         }


      /* Testar Finalizar teste */

         else if ( strcmp( ComandoTeste , FIM_CMD ) == 0 )
         {
            MEM_LiberarTodaMemoriaAlocada();
            return TST_CondRetOK;
         }

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TPAR Efetuar opera��es de teste espec�ficas para matriz */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
