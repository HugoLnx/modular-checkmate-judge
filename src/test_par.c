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
#include    "mem_manager.h"
#include    "input_string_parser.h"

/* Tabela dos nomes dos comandos de teste relacionados ao m�dulo */

#define     CRIAR_PAR_CMD       "=criar"
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


#define     PARTIDAS_SIZE 10
#define     MAX_PASSOS_STR   50
#define     MAX_NOME_PECA    30
/*****  C�digo das fun��es exportadas pelo m�dulo  *****/
int IndiceDoValor(LIS_tppLista Valor);

static PAR_tppPartida Partidas[PARTIDAS_SIZE];

static int iPar = 0 ;

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

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      PAR_tpCondRet CondRetObtido   = PAR_CondRetOK ;
      PAR_tpCondRet CondRetEsperada = PAR_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      int IndiceValorEsperado = -1;
	  int IndiceValorObtido = -1;
	  int IndiceValorDado = -1;
	  
	  LIS_tppLista ValorObtido = NULL;

	  int Linhas = 0 ;
	  int Colunas = 0 ;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar PAR Criar matriz */

         if ( strcmp( ComandoTeste , CRIAR_PAR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            }

            CondRetObtido = PAR_CriarPartida(Partidas + iPar) ;

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

            CondRetObtido = PAR_DestruirPartida(Partidas + iPar) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o � poss�vel destruir uma matriz que n�o existe.") ;

         } 

		 
//      /* Testar PAR Ir para */
//
//		 else if ( strcmp( ComandoTeste , IR_PARA_CMD ) == 0 )
//         {
//            int iDirecao;
//			   NumLidos = LER_LerParametros("ii" , &iDirecao, &CondRetEsperada);
//            if (NumLidos != 2)
//            {
//               return TST_CondRetParm ;
//            }
//
//			   CondRetObtido = PAR_IrPara(Partidas[iPar], (DIR_tpDirecao) iDirecao);
//
//            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
//									"N�o foi poss�vel ir para essa direcao.") ;
//
//         }


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

			CondRetObtido = PAR_IrCasa(Partidas[iPar], nome) ;

         return TST_CompararInt( CondRetEsperada , CondRetObtido ,
								"N�o foi poss�vel ir para a casa.") ;

         }


//		/* Testar PAR Ir casa rei */
//
//		 else if (strcmp(ComandoTeste, IR_REI_CMD) == 0)
//       {
//           NumLidos = LER_LerParametros("i", &CondRetEsperada);
//           if (NumLidos != 1)
//           {
//              return TST_CondRetParm ;
//           }
//           
//           CondRetObtido = PAR_IrCasaRei(Partidas[iPar]) ;
//           
//           return TST_CompararInt( CondRetEsperada , CondRetObtido ,
//               "N�o foi poss�vel ir para a casa do rei.") ;
//
//       }


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
			CondRetObtido = PAR_CriarPeca(Partidas[iPar], nome, pPassos, tipo);

         return TST_CompararInt(CondRetEsperada, CondRetObtido,
								"N�o foi poss�vel criar a casa.");

       }

       /* Testar PAR Alterar peca*/

       else if ( strcmp( ComandoTeste , ALTERAR_PECA_CMD ) == 0 )
       {

          char *nomeAtual, *passosStr, *novoNome;
          int iTipoMovimento;
          MPEC_tpTipoMovimento tipo;
          LIS_tppLista pPassos;
          MEM_Alloc(sizeof(char)*MAX_NOME_PECA, (void**) &nomeAtual);
          MEM_Alloc(sizeof(char)*MAX_NOME_PECA, (void**) &novoNome);
          MEM_Alloc(sizeof(char)*MAX_PASSOS_STR, (void**) &passosStr);

          NumLidos = LER_LerParametros("sssii", nomeAtual, novoNome, passosStr, &iTipoMovimento, &CondRetEsperada) ;
          if (NumLidos != 5)
          {
             return TST_CondRetParm ;
          }

          ISP_LerPassos(passosStr, &pPassos);

          tipo = (MPEC_tpTipoMovimento) iTipoMovimento;
          CondRetObtido = PAR_AlterarPeca(Partidas[iPar], nomeAtual, novoNome, pPassos, tipo);

          return TST_CompararInt(CondRetEsperada, CondRetObtido,
             "N�o foi poss�vel criar a casa.");

       }


       
//		/* Testar PAR Inserir peca*/
//
//		 else if (strcmp( ComandoTeste, INSERIR_PECA_CMD) == 0 )
//       {
//         char *nome;
//         int iTime;
//         PAR_tpTimePeca time;
//         LIS_tppLista pPassos;
//         MEM_Alloc(sizeof(char)*MAX_NOME_PECA, (void**) &nome);
//
//			NumLidos = LER_LerParametros("sii", nome, &iTime, &CondRetEsperada) ;
//         if (NumLidos != 3)
//         {
//            return TST_CondRetParm ;
//         }
//
//         time = (PAR_tpTimePeca) iTime;
//         CondRetObtido = PAR_InserirPeca(Partidas[iPar], nome, time);
//
//         return TST_CompararInt(CondRetEsperada, CondRetObtido,
//								"N�o foi poss�vel inserir a pe�a.");
//
//       }
//       
//       
//		/* Testar PAR Remover peca*/
//
//		 else if (strcmp( ComandoTeste, REMOVER_PECA_CMD) == 0 )
//       {
//			NumLidos = LER_LerParametros("i", &CondRetEsperada) ;
//         if (NumLidos != 1)
//         {
//            return TST_CondRetParm ;
//         }
//
//         CondRetObtido = PAR_RemoverPeca(Partidas[iPar]);
//
//         return TST_CompararInt(CondRetEsperada, CondRetObtido,
//								"N�o foi poss�vel remover a pe�a.");
//
//       }
//       
//       
//		/* Testar PAR Remover rei*/
//
//		 else if (strcmp( ComandoTeste, REMOVER_REI_CMD) == 0 )
//       {
//			NumLidos = LER_LerParametros("i", &CondRetEsperada) ;
//         if (NumLidos != 1)
//         {
//            return TST_CondRetParm ;
//         }
//
//         CondRetObtido = PAR_RemoverRei(Partidas[iPar]);
//
//         return TST_CompararInt(CondRetEsperada, CondRetObtido,
//								"N�o foi poss�vel remover o rei.");
//
//       }
//       
//       
//		/* Testar PAR Copiar tabuleiro */
//
//		 else if (strcmp( ComandoTeste, COPIAR_PAR_CMD) == 0 )
//       {
//          int iCopia;
//			 NumLidos = LER_LerParametros("ii", &iCopia, &CondRetEsperada) ;
//          if (NumLidos != 2)
//          {
//             return TST_CondRetParm ;
//          }
//          
//          CondRetObtido = PAR_CopiarTabuleiro(Partidas[iPar], &Partidas[iCopia]);
//          
//          return TST_CompararInt(CondRetEsperada, CondRetObtido,
//								"N�o foi poss�vel copiar o tabuleiro.");
//
//       }
//       
//       
//       
//		/* Testar PAR Criar pegadas */
//
//		 else if (strcmp( ComandoTeste, CRIAR_PEG_CMD) == 0 )
//       {
//			 NumLidos = LER_LerParametros("i", &CondRetEsperada) ;
//          if (NumLidos != 1)
//          {
//             return TST_CondRetParm ;
//          }
//          
//          CondRetObtido = PAR_CriarPegadas(Partidas[iPar]);
//          
//          return TST_CompararInt(CondRetEsperada, CondRetObtido,
//								"N�o foi poss�vel criar as pegadas.");
//
//       }
//
//
//		/* Testar PAR Inserir rei */
//
//		 else if (strcmp( ComandoTeste, INSERIR_REI_CMD) == 0 )
//       {
//			 NumLidos = LER_LerParametros("i", &CondRetEsperada) ;
//          
//          if (NumLidos != 1)
//          {
//             return TST_CondRetParm ;
//          }
//          
//          CondRetObtido = PAR_InserirRei(Partidas[iPar]);
//          
//          return TST_CompararInt(CondRetEsperada, CondRetObtido,
//								"N�o foi poss�vel inserir o rei.");
//
//       }
//
//
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
//          CondRetObtido = PAR_AlgumaPegadaInimiga(Partidas[iPar], &respostaObtida);
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
//          CondRetObtido = PAR_EhCheckmate(Partidas[iPar], &respostaObtida);
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
                               &iPar ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			if ( iPar < 0 || iPar > PARTIDAS_SIZE - 1 )
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
