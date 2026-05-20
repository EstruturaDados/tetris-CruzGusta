#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//struct da peça contendo o ID e o nome
typedef struct{
    int id;
    char nome;
} Peca;

//definindo tamanho do vetor
#define MAX 5

//struct da fila
typedef struct{
    Peca peca[MAX];
    int inicio;
    int final;
    int quantidade;
} Fila;

//função para gerar iuma peça
Peca gerarPeca(int id){
    char tipo[] = {'I', 'O', 'T', 'L'};

    Peca nova;
    nova.id = id;
    nova.nome = tipo[rand() % 4];

    return nova;
}

//função para inicializar a fila
void inicializarFila(Fila *f){
    f->inicio = 0;
    f-> final = 0;
    f -> quantidade = 0;
}

//criação da enqueue para adicionar a peça
void enqueue(Fila *f, Peca nova){
    f->peca[f->final] = nova;
    f->final = (f->final + 1) % MAX;
    f->quantidade++;
}

//criação da dequeue para remover uma peça
Peca dequeue(Fila *f){
    Peca removida = f->peca[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->quantidade--;
    return removida;
}

//função para mostrar a fila
void mostrarFila(Fila *f){

    for(int i = 0; i < f->quantidade; i++){

        int indice = (f->inicio + i) % MAX;

        printf("[%d:%c] ",
               f->peca[indice].id,
               f->peca[indice].nome);
    }

    printf("\n");
}

//código main
int main(){

    srand(time(NULL));
    
    Fila fila;
    inicializarFila(&fila);

    for(int i= 0; i < MAX; i++){
        enqueue(&fila, gerarPeca(i + 1));
    } 

    int novoID = 6;

    int opcao;
    do{

        //menu do jogo:
    printf("\n   TETRIS   \n");
    printf("Selecione uma opção: \n");
    printf("1 - Jogar peça \n");
    printf("2 - Insetrir peça \n");
    printf("3 - Mostrar peça \n");
    printf("0 - Sair\n");
    scanf("%d", &opcao);

    switch(opcao){

        case 1:

        Peca removida = dequeue(&fila);
        printf("Peca jogada: [%d:%c]\n",
            removida.id,
            removida.nome);

        enqueue(&fila, gerarPeca(novoID));
        novoID++;
        mostrarFila(&fila);
        break;

        case 2:

        if(fila.quantidade < MAX){
            enqueue(&fila, gerarPeca(novoID));
            novoID++;

        }else{
            printf("Fila cheia!\n");
        }

        mostrarFila(&fila);
        break;

        case 3:
        mostrarFila(&fila);
        break;

        case 0:
        printf("Saindo...\n");
        break;

        default:
        printf("Opção invalida. \n");
    }
    }while(opcao != 0);

    return 0;
}