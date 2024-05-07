/*
	Projeto realizado por: Rafael Costa
	Turma: PIPL0922
	Número: T0123399
	UFCD: 0809 - Programação em C/C++ - fundamentos
*/

#include<stdio.h>
#include<windows.h>
#include<ctype.h>
#include<conio.h>
#include<string.h>

//Enum para especificar as constantes dos estados dos navios
enum Estados {
	VAZIO,
	NAVIO,
	ATINGIDO,
	AGUA
};
	
struct Player {
	int id;
	int vitorias;
	char nome[25];
};

//Inicialização das variáveis globais
int op;
int coluna;
char linha;


int tabuleiroP1[10][10];
int tabuleiroP2[10][10];


int tabuleiroAtaqueP1[10][10];
int tabuleiroAtaqueP2[10][10];

char letra='A';
char nomePlayer[25];

//Funcao para inicializar o tabuleiro
void inicializarTabuleiro(int tabuleiro[10][10]) {
	for (int i=0; i<10; i++) {
		for (int j=0; i<10; i++) {
			tabuleiro[i][j] = VAZIO;
		}
	}
}

//Funcao para apresentar o tabuleiro de cada player
void tabuleiroBarcos(int tabuleiro[10][10], int playerId, char *nomeJogador) {
    printf("\t\t    Tabuleiro de Barcos do Player %d (%s)\n\n", playerId, nomeJogador);
    
    printf("\t");
    
    for (int l=1; l<=10; l++) {
        printf("  %d ", l);
    }
    
    printf("\n---------------------------------------------------\n");
    
    for (int i=0; i<10; i++) {
    	
        printf("%c\t", letra+i);
        
        for (int j=0; j<10; j++) {
            char c;
            switch (tabuleiro[i][j]) {
                case VAZIO:
                    c = 'O';
                    break;
                case NAVIO:
                    c = '#';
                    break;
                case AGUA:
                    c = '~';
                    break;
                case ATINGIDO:
                    c = 'X';
                    break;
                default:
                    c = '?';
            }
            printf("  %c ", c);
        }
        printf("\n");
    }
    printf("\n");
}

//Funcao do menu inicial
void menuInicial() {
    printf("    ____        __        ____             _   __                  __\n");
    printf("   / __ )____ _/ /_____ _/ / /_  ____ _   / | / /___ __   ______ _/ /\n");
    printf("  / __  / __ `/ __/ __ `/ / __ \\/ __ `/  /  |/ / __ `/ | / / __ `/ / \n");
    printf(" / /_/ / /_/ / /_/ /_/ / / / / / /_/ /  / /|  / /_/ /| |/ / /_/ / /  \n");
    printf("/_____/\\__,_/\\__/\\__,_/_/_/ /_/\\__,_/  /_/ |_/\\__,_/ |___/\\__,_/_/   \n");
    printf("                                                                     ");
    printf("\nBem vindo ao jogo da Batalha Naval\n[1] - Instrucoes\n[2] - Jogar\n[3] - Ver Historico de vitorias\n[4] - Sair\nOpcao: ");
    scanf("%d", &op);
}

//Funcao para colocar os barcos no tabuleiro
void porBarcos(int tabuleiro[10][10]) {
	int barcos=6;

	do {
		int direcao;
	    coluna = 0;
	    
	    switch (barcos) {
	    	case 1:
	    		printf("Onde quer colocar o barco de 5 posicoes (linha e coluna): ");
	    		getchar();
		    	linha = getchar();
				scanf("%d", &coluna);
				printf("Que direcao quer colocar (Horizontal: 1 | Vertical: 2): ");
				scanf("%d", &direcao);
				break;
			case 2:
				printf("Onde quer colocar o barco de 3 posicoes (linha e coluna): ");
		    	getchar();
		    	linha = getchar();
				scanf("%d", &coluna);
				printf("Que direcao quer colocar (Horizontal: 1 | Vertical: 2): ");
				scanf("%d", &direcao);
				break;
			case 3:
				printf("Onde quer colocar o barco de 2 posicoes (linha e coluna): ");
		    	getchar();
		    	linha = getchar();
				scanf("%d", &coluna);
				printf("Que direcao quer colocar (Horizontal: 1 | Vertical: 2): ");
				scanf("%d", &direcao);
				break;
			default:
				printf("Onde quer colocar os barcos (linha e coluna): ");
		    	getchar();
		    	linha = getchar();
				scanf("%d", &coluna);
				break;
		}
		
		if (isdigit(linha) || isalpha(coluna)) {
            printf("Nao e possivel colocar o barco nesta posicao!\n");
            MessageBeep(MB_ICONINFORMATION);
            // o MessageBeep serve para colocar um som do windows, o MB_ICONINFORMATION e uma variavel de som do proprio windows
		} else {
            if (islower(linha)) {
                linha = toupper(linha);
            }

            int linhaIndex = linha - 'A';
            int colunaIndex = coluna - 1;

            //Vai verificar se a posicao é valida
            if (linhaIndex < 0 || linhaIndex >= 10 || colunaIndex < 0 || colunaIndex >= 10) {
                printf("Nao e possivel colocar o barco nesta posicao!\n");
                MessageBeep(MB_ICONINFORMATION);
            } else if (tabuleiro[linhaIndex][colunaIndex] != VAZIO) {
                printf("Ja existe um barco ai\n");
            } else {
                tabuleiro[linhaIndex][colunaIndex] = NAVIO;
                
                switch(barcos) {
                	case 1:
                		// barco de 5 posicoes
	                	if (direcao == 1) { //Horizontal
	                		for (int i=0; i<5; i++) {
	                			if (linhaIndex < 0 || linhaIndex >= 10 || colunaIndex < 0 || colunaIndex+5 >= 10) {
	                				tabuleiro[linhaIndex][colunaIndex-i] = NAVIO;
	            				} else {
	            					tabuleiro[linhaIndex][colunaIndex+i] = NAVIO;
								}
							}
						} else if (direcao == 2) { // Vertical
							for (int i=0; i<5; i++) {
								if (linhaIndex < 0 || linhaIndex+5 >= 10 || colunaIndex < 0 || colunaIndex >= 10) {
	                				tabuleiro[linhaIndex-i][colunaIndex] = NAVIO;
	            				} else {
	            					tabuleiro[linhaIndex+i][colunaIndex] = NAVIO;
								}
							}
						}
						break;
					case 2:
						//barco de 3 posicoes
						if (direcao == 1) { //Horizontal
	                		for (int i=0; i<3; i++) {
		                		if (linhaIndex < 0 || linhaIndex >= 10 || colunaIndex < 0 || colunaIndex+3 >= 10) {
	                				tabuleiro[linhaIndex][colunaIndex-i] = NAVIO;
	            				} else {
	            					tabuleiro[linhaIndex][colunaIndex+i] = NAVIO;
								}
							}
						} else if (direcao == 2) { // Vertical
							for (int i=0; i<3; i++) {
		                		if (linhaIndex < 0 || linhaIndex+3 >= 10 || colunaIndex < 0 || colunaIndex >= 10) {
	                				tabuleiro[linhaIndex-i][colunaIndex] = NAVIO;
	            				} else {
	            					tabuleiro[linhaIndex+i][colunaIndex] = NAVIO;
								}
							}
						}
						break;
					case 3:
						//barco de 2 posicoes
						if (direcao == 1) { //Horizontal
	                		for (int i=0; i<2; i++) {
		                		if (linhaIndex < 0 || linhaIndex >= 10 || colunaIndex < 0 || colunaIndex+2 >= 10) {
	                				tabuleiro[linhaIndex][colunaIndex-i] = NAVIO;
	            				} else {
	            					tabuleiro[linhaIndex][colunaIndex+i] = NAVIO;
								}
							}
						} else if (direcao == 2) { // Vertical
							for (int i=0; i<2; i++) {
		                		if (linhaIndex+i < 0 || linhaIndex+2 >= 10 || colunaIndex < 0 || colunaIndex >= 10) {
	                				tabuleiro[linhaIndex-i][colunaIndex] = NAVIO;
	            				} else {
	            					tabuleiro[linhaIndex+i][colunaIndex] = NAVIO;
								}
							}
						}
						break;
					default:
						;
						break;
				}
                barcos--;
            }   
		}
	} while (barcos != 0);
}

//Verifica se já existe algo nessa posição do tabuleiro
void verificarJogada(int tabuleiro[10][10], int linhaIndex, int colunaIndex, int tabuleiroAtaque[10][10]) {
    if (linhaIndex < 0 || linhaIndex >= 10 || colunaIndex < 0 || colunaIndex >= 10) {
        printf("Jogada fora do tabuleiro.\n");
        MessageBeep(MB_ICONINFORMATION);
    } else if (tabuleiro[linhaIndex][colunaIndex] == NAVIO) {
        printf("\033[0;31mAcertou um navio!\n");
        tabuleiro[linhaIndex][colunaIndex] = ATINGIDO;
        tabuleiroAtaque[linhaIndex][colunaIndex] = ATINGIDO;
    } else if (tabuleiro[linhaIndex][colunaIndex] == VAZIO) {
        printf("\033[0;34mAgua!\n");
        tabuleiro[linhaIndex][colunaIndex] = AGUA;
        tabuleiroAtaque[linhaIndex][colunaIndex] = AGUA;
    } else if (tabuleiro[linhaIndex][colunaIndex] == ATINGIDO || tabuleiro[linhaIndex][colunaIndex] == AGUA) {
        printf("\033[0;33mJogada Repetida.\n");
    }
    
    //reseta a cor do terminal
    printf("\033[0m");
}

//Funcao para realizar a jogada do jogador
void jogada(int tabuleiro[10][10], int playerId, int tabuleiroAtaque[10][10]) {
    coluna = 0;
	printf("Jogada do Player %d (linha e coluna): ", playerId);
	getchar();
    linha = getchar();
	scanf("%d", &coluna);
	
	if (isdigit(linha) || isalpha(coluna)) {
        printf("Nao e possivel colocar o barco nesta posicao!\n");
        MessageBeep(MB_ICONINFORMATION);
        Sleep(1500);
	} else {
        if (islower(linha)) {
            linha = toupper(linha);
        }

        int linhaIndex = linha - 'A';
        int colunaIndex = coluna - 1;
        
        verificarJogada(tabuleiro, linhaIndex, colunaIndex, tabuleiroAtaque);
    	Sleep(3000);
	}
}

int checaVencedor(int tabuleiro[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (tabuleiro[i][j] == NAVIO) {
                // Se ainda houver um navio não atingido, o jogo continua
                return 0;
            }
        }
    }
    // Se não houver mais navios não atingidos, o jogador perdeu
    return 1;
}

void jogador1(char *nomeJogador) {
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t   ___                       _              __  \n");
	printf("\t\t\t\t  |_  |                     | |            /  | \n");
	printf("\t\t\t\t    | | ___   __ _  __ _  __| | ___  _ __  `| | \n");
	printf("\t\t\t\t    | |/ _ \\ / _` |/ _` |/ _` |/ _ \\| '__|  | | \n");
	printf("\t\t\t\t/\\__/ / (_) | (_| | (_| | (_| | (_) | |    _| |_\n");
	printf("\t\t\t\t\\____/ \\___/ \\__, |\\__,_|\\__,_|\\___/|_|    \\___/\n");
	printf("\t\t\t\t              __/ |                             \n");
	printf("\t\t\t\t             |___/                              \n");
	
	printf("\n*%s*", nomeJogador);
	
	Sleep(2500);
	system("cls");
}

void jogador2(char *nomeJogador) {
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t   ___                       _              _____ \n");
	printf("\t\t\t\t  |_  |                     | |            / __  \\\n");
	printf("\t\t\t\t    | | ___   __ _  __ _  __| | ___  _ __  `' / /'\n");
	printf("\t\t\t\t    | |/ _ \\ / _` |/ _` |/ _` |/ _ \\| '__|   / /  \n");
	printf("\t\t\t\t/\\__/ / (_) | (_| | (_| | (_| | (_) | |    ./ /___\n");
	printf("\t\t\t\t\\____/ \\___/ \\__, |\\__,_|\\__,_|\\___/|_|    \\_____/\n");
	printf("\t\t\t\t              __/ |                               \n");
	printf("\t\t\t\t             |___/                                \n");
	
	printf("\n*%s*", nomeJogador);
	
	Sleep(2500);
	system("cls");
}


int main() {
	struct Player player1;
	struct Player player2;

	player1.id = 1;
	player2.id = 2;

	inicializarTabuleiro(tabuleiroP1);
	inicializarTabuleiro(tabuleiroP2);

	inicializarTabuleiro(tabuleiroAtaqueP1);
    inicializarTabuleiro(tabuleiroAtaqueP2);

	do {
		menuInicial();
		switch (op) {
			case 1:
				system("cls");
				printf("Bem-vindo ao jogo da Batalha Naval!\nEsta prestes a embarcar numa batalha emocionante no mar.\nO objetivo deste jogo e destruir todas as embarcacoes do seu inimigo!");
				printf("\nLegenda:\n");
				printf("Vazio: O\nNavio: #\nAgua: ~\nNavio Atingido: X");
				Sleep(8000);
				system("cls");
				break;
			case 2:
				system("cls");
				
				printf("Nome do player 1: ");
				scanf("%s", &nomePlayer);
				strcpy(player1.nome, nomePlayer);
				
				printf("\nNome do player 2: ");
				scanf("%s", &nomePlayer);
				strcpy(player2.nome, nomePlayer);
				
				jogador1(player1.nome);
				tabuleiroBarcos(tabuleiroP1, player1.id, player1.nome);
                porBarcos(tabuleiroP1);
                system("cls");
	
				jogador2(player2.nome);
                tabuleiroBarcos(tabuleiroP2, player2.id, player2.nome);
                porBarcos(tabuleiroP2);
                system("cls");

                while (1) {
                	jogador1(player1.nome);
                	
                	tabuleiroBarcos(tabuleiroP1, player1.id, player1.nome);
                	tabuleiroBarcos(tabuleiroAtaqueP2, player2.id, player2.nome);
                	jogada(tabuleiroP2, player1.id, tabuleiroAtaqueP2);
                	system("cls");
                	if (checaVencedor(tabuleiroP2)) {
                        printf("Player %d (%s) venceu!\n", player1.id, player1.nome);
                        MessageBeep(MB_ICONWARNING);
                        player1.vitorias += 1;
                        break;
                    }
                	
                	jogador2(player2.nome);
                	
                    tabuleiroBarcos(tabuleiroP2, player2.id, player2.nome);
                    tabuleiroBarcos(tabuleiroAtaqueP1, player1.id, player1.nome);
                    jogada(tabuleiroP1, player2.id, tabuleiroAtaqueP1);
                    system("cls");
                    if (checaVencedor(tabuleiroP1)) {
                        printf("Player %d (%s) venceu!\n", player2.id, player2.nome);
                        MessageBeep(MB_ICONWARNING);
                        player2.vitorias += 1;
                        break;
                    }
            	}
                Sleep(5000);
                system("cls");
				break;
			case 3:
				if (player1.vitorias == 1) {
					printf("\nO jogador 1 (%s) venceu: %d vez", player1.nome, player1.vitorias);
				} else {
					printf("\nO jogador 1 (%s) venceu: %d vezes", player1.nome, player1.vitorias);
				}
				
				if (player2.vitorias == 1) {
					printf("\nO jogador 2 (%s) venceu: %d vez", player2.nome, player2.vitorias);
				} else {
					printf("\nO jogador 2 (%s) venceu: %d vezes", player2.nome, player2.vitorias);
				}	
				Sleep(3000);
				system("cls");
				break;
			case 4:
				printf("Obrigado por ter jogado!");
				Sleep(2500);
				break;
			default:
				printf("Opcao invalida!");
				Sleep(1000);
				system("cls");
				break;
		}
	} while (op != 4);
}