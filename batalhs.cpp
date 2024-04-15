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
char letra='A';

void inicializarTabuleiro(int tabuleiro[10][10]) {
	for (int i=0; i<10; i++) {
		for (int j=0; i<10; i++) {
			tabuleiro[i][j] = VAZIO;
		}
	}
}

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
                default:
                    c = '?';
            }
            printf("  %c ", c);
        }
        printf("\n");
    }
    printf("\n");
}

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

void porBarcos(int tabuleiro[10][10]) {
	char linha;
	int coluna, barcos=6;
	
	do {
		printf("Onde que colocar os barcos (linha e coluna): ");
		getchar();
		scanf("%c%d", &linha, &coluna);
		
		if (islower(linha)) {
			linha = toupper(linha);
		}
		
		int linhaIndex = linha - 'A';
		int colunaIndex = coluna - 1;
		
		if (linhaIndex < 0 || linhaIndex >= 10 || colunaIndex < 0 || colunaIndex >= 10) {
			printf("Nao e possivel colocar o barco nesta posicao!\n");
		} else if (tabuleiro[linhaIndex][colunaIndex] != VAZIO) {
			printf("Ja existe um barco ai\n");
		} else {
			tabuleiro[linhaIndex][colunaIndex] = NAVIO;
			barcos--;
		}
	} while (barcos != 0);
}

void jogada(int tabuleiro[10][10]) {
	char linha;
	int coluna;
	
	printf("Jogada (linha e coluna): ");
	getchar();
	scanf("%c%d", &linha, &coluna);
	
	if (islower(linha)) {
		linha = toupper(linha);
	}
	
	int linhaIndex = linha - 'A';
	int colunaIndex = coluna-1;
	
	if (linhaIndex < 0 || linhaIndex > 10 || colunaIndex < 0 || colunaIndex > 10) {
		printf("Jogada fora do tabuleiro.\n");
		return;
	}
	
	if (tabuleiro[linhaIndex][colunaIndex] != VAZIO) {
		printf("Jogada Repetida.\n");
		return;
	} 
	
	if (tabuleiro[linhaIndex][colunaIndex] == NAVIO) {
		printf("Acertou um navio!\n");
		tabuleiro[linhaIndex][colunaIndex] = ATINGIDO;
	}
	
	if (tabuleiro[linhaIndex][colunaIndex] == VAZIO) {
		printf("Agua!\n");
		tabuleiro[linhaIndex][colunaIndex] = AGUA;
	}
	
}

int main() {
	struct Player player1;
	struct Player player2;
	
	player1.id = 1;
	player2.id = 2;
	
	inicializarTabuleiro(tabuleiroP1);
	inicializarTabuleiro(tabuleiroP2);
	
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
				
				tabuleiroBarcos(tabuleiroP1, player1.id);
				Sleep(6000);
				system("cls");
				
				tabuleiroBarcos(tabuleiroP2, player2.id);
				porBarcos(tabuleiroP2);
				
				tabuleiroBarcos(tabuleiroP2, player2.id);
				
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








