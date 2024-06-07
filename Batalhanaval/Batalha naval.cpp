#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

//Cabeçalhos de funções
void menuInicial();


void limpaTela() {
    system("CLS");
}

void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]) {

    //Popula o tabuleiro com Água
    int linha, coluna;
    for (linha = 0; linha < 10; linha++) {
        for (coluna = 0; coluna < 10; coluna++) {
            tabuleiro[linha][coluna] = 'A';
            mascara[linha][coluna] = '*';
        }
    }

}

void exibeMapa() {
    //Mapa indicador de colunas
    int cont;
    for (cont = 0; cont < 10; cont++) {
        if (cont == 0) {
            cout << "     ";
        }
        cout << cont << " ";
    }
    cout << "\n";
    for (cont = 0; cont < 10; cont++) {
        if (cont == 0) {
            cout << "     ";
        }
        cout << "| ";
    }
    cout << "\n";

}

void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10], bool mostraGabarito) {


    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };

    //Exibe o tabuleiro
    int linha, coluna;
    for (linha = 0; linha < 10; linha++) {
        cout << linha << " - ";
        for (coluna = 0; coluna < 10; coluna++) {

            switch (mascara[linha][coluna]) {
            case 'A':
                cout << blue << " " << mascara[linha][coluna] << normal;
                break;
            case 'P':
                cout << green << " " << mascara[linha][coluna] << normal;
                break;
            default:
                cout << " " << mascara[linha][coluna];
                break;
            }

        }
        cout << "\n";
    }

    if (mostraGabarito == true) {
        for (linha = 0; linha < 10; linha++) {
            for (coluna = 0; coluna < 10; coluna++) {
                cout << " " << tabuleiro[linha][coluna];
            }
            cout << "\n";
        }
    }


}

void posicionaBarcos(char tabuleiro[10][10]) {

    //Coloca 10 barcos no tabuleiro
    int cont, quantidade = 10, quantidadePosicionada = 0;

    //Verifica se já posicionou todos os barcos
    while (quantidadePosicionada < quantidade) {

        int linhaAleatoria = rand() % 10;  //Gera número aleatório de 0 a 9
        int colunaAleatoria = rand() % 10; //Gera número aleatório de 0 a 9

        if (tabuleiro[linhaAleatoria][colunaAleatoria] == 'A') {

            //Posiciona 10 barcos aleatoriamente
            tabuleiro[linhaAleatoria][colunaAleatoria] = 'P';

            //Aumenta o contador de barcos posicionados
            quantidadePosicionada++;

        }

    }

}

void verificaTiro(char tabuleiro[10][10], int linhaJogada, int colunaJogada, int* pontos, string* mensagem) {

    //Verifica quantos pontos adicionar
    switch (tabuleiro[linhaJogada][colunaJogada]) {
    case 'P':
        *pontos = *pontos + 10;
        *mensagem = "Voce acertou um barco pequeno! (10 pts)";
        break;
    case 'A':
        *mensagem = "Voce acertou a agua";
        break;
    }

}

void jogo(string nomeDoJogador) {

    ///Variáveis Gerais
    char tabuleiro[10][10], mascara[10][10];             //Tabuleiro do Jogo
    int linha, coluna;                                   //Auxiliares de navegação
    int linhaJogada, colunaJogada;                      //Posicao escolhida pelo jogador
    int estadoDeJogo = 1;                               //1 = Jogo Acontecendo, 0 = Fim de Jogo
    int pontos = 0;                                     //Pontuação do Jogador
    int tentativas = 0, maximoDeTentativas = 5;         //Tentativas do jogador
    int opcao;                                          //Opções de fim de jogo
    string mensagem = "Bem vindo ao jogo!";             //Mensagem de feedback para o jogador

    //Inicia o tabuleiro com água
    iniciaTabuleiro(tabuleiro, mascara);

    //Posiciona barcos aleatoriamente
    posicionaBarcos(tabuleiro);

    while (tentativas < maximoDeTentativas) {

        limpaTela();

        //Exibe o mapa de indicações
        exibeMapa();

        //Exibe tabuleiro
        exibeTabuleiro(tabuleiro, mascara, false);

        cout << "\nPontos:" << pontos << ", Tentativas Restantes:" << maximoDeTentativas - tentativas;
        cout << "\n" << mensagem;

        //Verificação de dados
        linhaJogada = -1;
        colunaJogada = -1;

        while ((linhaJogada < 0 || colunaJogada < 0) || (linhaJogada > 9 || colunaJogada > 9)) {

            cout << "\n" << nomeDoJogador << ", digite uma linha:";
            cin >> linhaJogada;
            cout << "\n" << nomeDoJogador << ", digite uma coluna:";
            cin >> colunaJogada;

        }

        //Verifica o que aconteceu
        verificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontos, &mensagem);

        //Reveka o que está no tabuleiro
        mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

        tentativas++;

    }

    cout << "Fim de jogo, o que deseja fazer?";
    cout << "\n1-Jogar Novamente";
    cout << "\n2-Ir para o Menu";
    cout << "\n3-Sair";
    cin >> opcao;
    switch (opcao) {
    case 1:
        jogo(nomeDoJogador);
        break;
    case 2:
        menuInicial();
        break;
    }

}

void menuInicial() {

    //Opção escolhida pelo usuário
    int opcao = 0;

    //Nome do usuário
    string nomeDoJogador;

    //Enquanto o jogador não digita uma opcao válida, mostra o menu novamente
    while (opcao < 1 || opcao > 3) {
        limpaTela();
        cout << "Bem vindo ao Jogo de Batalha Naval";
        cout << "\n1 - Jogar";
        cout << "\n2 - Sobre";
        cout << "\n3 - Sair";
        cout << "\nEscolha uma opcao e tecle ENTER:";

        //Faz a leitura da opcao
        cin >> opcao;

        //Faz algo de acordo com a opcao escolhida
        switch (opcao) {
        case 1:
            //Inicia o jogo
            //cout << "Jogo iniciado";
            cout << "Qual seu nome?";
            cin >> nomeDoJogador;
            jogo(nomeDoJogador);
            break;
        case 2:
            //Mostra informacoes do Jogo
            cout << "DESENVOLVIDO PELO CLAUDIO MATHEUS PARA CONCLUSAO DO CURSO C E C++ COMPLETO EM 20/03";
            break;
        case 3:
            cout << "Ate mais!";
            break;
        }
    }

}

int main() {

    //Para gerar números realmente aleatórios
    srand((unsigned)time(NULL));

    menuInicial();
    return 0;
}