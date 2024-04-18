#include<stdio.h>
#include<windows.h>
#include<ctype.h>
#include<conio.h>

enum Estados {
	VAZIO,
	NAVIO,
	ATINGIDO,
	AGUA
};

struct Player {
	int id;
};

int op;

int tabuleiroP1[10][10];
int tabuleiroP2[10][10];

int tabuleiroAtaqueP1[10][10];
int tabuleiroAtaqueP2[10][10];

char letra='A';

//Funcao para inicializar o tabuleiro
void inicializarTabuleiro(int tabuleiro[10][10]) {
	for (int i=0; i<10; i++) {
		for (int j=0; i<10; i++) {
			tabuleiro[i][j] = VAZIO;
		}
	}
}

//Funcao para apresentar o tabuleiro de cada player
void tabuleiroBarcos(int tabuleiro[10][10], int playerId) {
    printf("\t\t    Tabuleiro de Barcos do Player %d\n\n", playerId);
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
    printf("\nBem vindo ao jogo da Batalha Naval\n[1] - Instrucoes\n[2] - Jogar\n[3] - Sair\nOpcao: ");
    scanf("%d", &op);
}

//Funcao para colocar os barcos no tabuleiro
void porBarcos(int tabuleiro[10][10]) {
	char linha;
	int coluna, barcos=6;

	do {
	    coluna = 0;
		printf("Onde que colocar os barcos (linha e coluna): ");
		getchar();
        linha = getche();
		scanf("%d", &coluna);

		if (isdigit(linha) || isalpha(coluna)) {
            printf("Errado!\n");
		} else {
            if (islower(linha)) {
                linha = toupper(linha);
            }

            int linhaIndex = linha - 'A';
            int colunaIndex = coluna - 1;

            //Vai verificar se a posicao é valida
            if (linhaIndex < 0 || linhaIndex >= 10 || colunaIndex < 0 || colunaIndex >= 10) {
                printf("Nao e possivel colocar o barco nesta posicao!\n");
            } else if (tabuleiro[linhaIndex][colunaIndex] != VAZIO) {
                printf("Ja existe um barco ai\n");
            } else {
                tabuleiro[linhaIndex][colunaIndex] = NAVIO;
                barcos--;
            }
		}

	} while (barcos != 0);
}

//Verifica se já existe algo nessa posição do tabuleiro
void verificarJogada(int tabuleiro[10][10], int linhaIndex, int colunaIndex, int tabuleiroAtaque[10][10]) {
    if (tabuleiro[linhaIndex][colunaIndex] == NAVIO) {
        printf("Acertou um navio!\n");
        tabuleiro[linhaIndex][colunaIndex] = ATINGIDO;
        tabuleiroAtaque[linhaIndex][colunaIndex] = ATINGIDO;
    } else if (tabuleiro[linhaIndex][colunaIndex] == VAZIO) {
        printf("Agua!\n");
        tabuleiro[linhaIndex][colunaIndex] = AGUA;
        tabuleiroAtaque[linhaIndex][colunaIndex] = AGUA;
    } else if (tabuleiro[linhaIndex][colunaIndex] == ATINGIDO || tabuleiro[linhaIndex][colunaIndex] == AGUA) {
        printf("Jogada Repetida.\n");
    }
}

//Funcao para realizar a jogada do jogador
void jogada(int tabuleiro[10][10], int playerId, int tabuleiroAtaque[10][10]) {
    char linha;
    int coluna;

    printf("Jogada do Player %d (linha e coluna): ", playerId);
    getchar();
    scanf("%c%d", &linha, &coluna);

    if (islower(linha)) {
        linha = toupper(linha);
    }

    int linhaIndex = linha - 'A';
    int colunaIndex = coluna-1;

    if (linhaIndex < 0 || linhaIndex >= 10 || colunaIndex < 0 || colunaIndex >= 10) {
        printf("Jogada fora do tabuleiro.\n");
        return;
    }

    verificarJogada(tabuleiro, linhaIndex, colunaIndex, tabuleiroAtaque);
    Sleep(3000);
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
				printf("Instrucoes");
				Sleep(3000);
				system("cls");
				break;
			case 2:
				system("cls");

                tabuleiroBarcos(tabuleiroP1, player1.id);
                porBarcos(tabuleiroP1);
                system("cls");

                tabuleiroBarcos(tabuleiroP2, player2.id);
                porBarcos(tabuleiroP2);
                system("cls");

                while (1) {
                    tabuleiroBarcos(tabuleiroP2, player2.id);
                    tabuleiroBarcos(tabuleiroAtaqueP1, player1.id);
                    jogada(tabuleiroP1, player2.id, tabuleiroAtaqueP1);
                    system("cls");
                    tabuleiroBarcos(tabuleiroP1, player1.id);
                    if (checaVencedor(tabuleiroP1)) {
                        printf("Player %d venceu!\n", player2.id);
                        break;
                    }

                    tabuleiroBarcos(tabuleiroAtaqueP2, player2.id);
                    jogada(tabuleiroP2, player1.id, tabuleiroAtaqueP2);
                    system("cls");
                    tabuleiroBarcos(tabuleiroP2, player2.id);
                    if (checaVencedor(tabuleiroP2)) {
                        printf("Player %d venceu!\n", player1.id);
                        break;
                    }
                }


                Sleep(6000);
                system("cls");
				break;
			case 3:
				printf("Obrigado por ter jogado!");
				Sleep(2500);
				break;
			default:
				printf("Opcao invalida!");
				break;
		}
	} while (op != 3);
}
