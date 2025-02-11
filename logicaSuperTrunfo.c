/*
Super trunfo nível Mestre.
Autor: Adriano Santos
Nesse programa, é possível cadastrar as cartas, listar e jogar. A comparação é feita pela renda percapta.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct
{
    char codigo[4];       // Código da carta (ex.: A01)
    int populacao;        // População da cidade
    float area;           // Área da cidade
    float pib;            // Produto Interno Bruto (PIB) da cidade
    int pontosTuristicos; // Número de pontos turísticos
    float densidadePop;
    float perCapta;
} CartaCidade;

int opcao;
int numeroSecreto, palpite;
// Número de estados e cidades
int numEstados = 8;
int numCidadesPorEstado = 4;

// vetor para armazenar as estruturas das cartas
CartaCidade cartas[32];

// Total das cartas
int totalCartas = 8 * 4;

// array dos estados
char estados[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

// incremento da carta que será adicionada.
int incremento = 0;

//variáveis da função jogar
char cartaJogador[4];
char cartaComputador[4];


//funções
int cadastrar(int *incremento);
int gerarMenu();
int listarCartas();
int jogar();
void limparTela();

int main()
{    
    gerarMenu();    

    switch (opcao)
    {
    case 1:              
        cadastrar(&incremento);
        break;
    case 2:        
        listarCartas();
        break;
    case 3:
        jogar();
        break;
    case 4:
        limparTela();
        printf("Obrigado por usar nosso jogo, ate mais!.\n");
        break;        
    default:
        limparTela();
        printf("Opcao invalida. Tente novamente.\n");        
    }

    return 0;
}

int cadastrar(int *incremento){
    if (*incremento < 32)
    {   
        limparTela();     
        printf("*************************************\n");
        printf("* Super Trunfo - Cadastro de cartas *\n");
        printf("*************************************\n\n");
        printf("Cadastro da carta %c%02d\n", estados[*incremento / numCidadesPorEstado], (*incremento % numCidadesPorEstado) + 1);

        // Pegar os dados e jogar no array (vetor)
        printf("Populacao da cidade: ");
        scanf("%d", &cartas[*incremento].populacao);

        printf("Area da cidade: ");
        scanf("%f", &cartas[*incremento].area);

        printf("PIB da cidade: ");
        scanf("%f", &cartas[*incremento].pib);

        printf("Pontos turisticos da cidade: ");
        scanf("%d", &cartas[*incremento].pontosTuristicos);

        cartas[*incremento].densidadePop =  cartas[*incremento].populacao / cartas[*incremento].area;
        cartas[*incremento].perCapta =  cartas[*incremento].pib / cartas[*incremento].populacao;

        (*incremento)++;
        limparTela();
        main();
    }
    return 0;
}

int gerarMenu() {        
    printf("*************************************\n");
    printf("* Super Trunfo - Listagem de Cartas *\n");
    printf("*************************************\n\n");
    printf("MENU\n");
    printf("1. Cadastrar Carta\n");
    printf("2. Listar Cartas\n");
    printf("3. Jogar\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao:\n\n");
    scanf("%d", &opcao);    
    return 0;
}


int listarCartas(){
    limparTela();
    printf("*************************************\n");
    printf("* Super Trunfo - Listagem de Cartas *\n");
    printf("*************************************\n\n");
    for (int i = 0; i < incremento; i++)
    {
        snprintf(cartas[i].codigo, sizeof(cartas[i].codigo), "%c%02d", estados[i / numCidadesPorEstado], (i % numCidadesPorEstado) + 1);
        printf("Carta: %s\n", cartas[i].codigo);
        printf("Populacao: %d\n", cartas[i].populacao);
        printf("Area: %.2f km^2\n", cartas[i].area);
        printf("PIB: %.2f\n", cartas[i].pib);
        printf("Pontos Turisticos: %d\n", cartas[i].pontosTuristicos);
        printf("Renda Percapta: %.2f\n", cartas[i].perCapta);
        printf("Densidade: %.2f\n", cartas[i].densidadePop);
        printf("\n");
    }

    main();

    return 0;    
}


int jogar(){
    char cartaDaLista[4];
    char cartaDescComputador[4];
    int achou;
    int contadorRand, cartaComputador, contadorVetor;


    limparTela();     
    printf("*************************************\n");
    printf("* Super Trunfo - Cadastro de cartas *\n");
    printf("*************************************\n\n");
    
    printf("Escolha a sua carta (ex: A01)\n\n");
    
    scanf("%4s", &cartaJogador);

    for (int i = 0; i < incremento; i++)
    {
        char cartaDaLista[4];
        sprintf(cartaDaLista, cartas[i].codigo, sizeof(cartas[i].codigo), "%c%02d", estados[i / numCidadesPorEstado], (i % numCidadesPorEstado) + 1);
        
        //para comparar as strings strings
        int resCartasJogo = strcmp(cartaJogador, cartaDaLista);

        if (resCartasJogo == 0){
            achou = i;
            break;        
        }
    }

    if (achou < 0){
        printf("A carta que voce escolheu, nao foi encontrada!");
        limparTela();
        gerarMenu();
    }else{
        contadorRand = incremento;
       
        srand(time(0));       
        cartaComputador = rand() % contadorRand;
        sprintf(cartaDescComputador, cartas[cartaComputador].codigo, sizeof(cartas[cartaComputador].codigo), "%c%02d", estados[cartaComputador / numCidadesPorEstado], (cartaComputador % numCidadesPorEstado) + 1);


        float batComputador = cartas[cartaComputador].perCapta;
        float batJogador = cartas[achou].perCapta;

        if (batComputador < batJogador){                        
            printf("----------------------------------------\n");
            printf("Voce GANHOU !!! \n");
            printf("----------------------------------------\n");
            printf("Sua carta: %s\n", cartaJogador);
            printf("Valor sua carta: %f\n", batJogador);
            printf("----------------------------------------\n");
            printf("Carta do Computador: %s\n", cartaDescComputador);
            printf("Valor computador: %f\n\n", batComputador);
        }else if (batComputador > batJogador) {
            printf("----------------------------------------\n");
            printf("Voce PERDEU :-(\n");
            printf("----------------------------------------\n");
            printf("Sua carta: %s\n", cartaJogador);
            printf("Valor sua carta: %.2f\n", batJogador);
            printf("----------------------------------------\n");
            printf("Carta do Computador: %s\n", cartaDescComputador);
            printf("Valor computador: %.2f\n\n", batComputador);
        }else if (batComputador == batJogador){
            printf("----------------------------------------\n");
            printf("Deu EMPATE!!\n");
            printf("----------------------------------------\n");
            printf("Sua carta: %s\n", cartaJogador);
            printf("Valor sua carta: %.2f\n", batJogador);
            printf("----------------------------------------\n");
            printf("Carta do Computador: %s\n", cartaDescComputador);
            printf("Valor computador: %.2f\n\n", batComputador);            
        }
        
    }

    main();
    return 0;
}


void limparTela()
{
    system("clear");
}