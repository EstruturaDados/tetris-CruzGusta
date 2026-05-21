#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//struct da peça contendo o ID e o nome
typedef struct{
    int id;
    char nome;
} Peca;

//definindo tamanho da fila e o tamanho maximo da pilha
#define MAX 5
#define MAX_PILHA 3

//struct da fila
typedef struct{
    Peca peca[MAX];
    int inicio;
    int final;
    int quantidade;
} Fila;

//struct da pilha que guarda as peças
typedef struct{
    Peca peca[MAX_PILHA];
    int topo;
} Pilha;

//===== FUNÇÕES DE FILA E PEÇA =====
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
    printf("\nFILA: \n");
    for(int i = 0; i < f->quantidade; i++){

        int indice = (f->inicio + i) % MAX;

        printf("[%d:%c] ",
               f->peca[indice].id,
               f->peca[indice].nome);
    }

    printf("\n");
}

//===== FUNÇÔES DA PILHA =====
//função para inicializar peça
void inicializarPilha(Pilha *p){

    p->topo = -1;
}

//verificar se a peça está cheia
int pilhaCheia(Pilha *p){

    return p->topo == MAX_PILHA -1;
}

//verificar se a pilha está vazia
int pilhaVazia(Pilha *p){

    return p->topo == -1;
}

//push para colocar a peça na pilha
void push(Pilha *p, Peca nova){
    
    p->topo++;
    p->peca[p->topo] = nova;
}

//pop para remoção de peça
Peca pop(Pilha *p){
    
    Peca removida = p->peca[p->topo];
    p->topo--;
    return removida;
}

//função para mostrar a pilha
void mostraPilha(Pilha *p){

    printf("\nPILHA: \n");
    if(pilhaVazia(p)){

        printf("A pilha está vazia.\n");
        return;
    }
    for(int i = p->topo; i >= 0; i--){

        printf("[%d:%c]", p->peca[i].id, p->peca[i].nome);
        printf("\n");
    }
}
//código main
int main(){

    srand(time(NULL));
    
    Fila fila;
    inicializarFila(&fila);//para inicializar a fila

    Pilha pilha;
    inicializarPilha(&pilha);//para inicializar apilha

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
    printf("2 - Reservar peça \n");
    printf("3 - Usar peça reservada \n");
    printf("0 - Sair\n");
    scanf("%d", &opcao);

    switch(opcao){

        case 1:{
        
        Peca removida = dequeue(&fila);
        printf("Peca jogada: [%d:%c]\n",
            removida.id,
            removida.nome);

        enqueue(&fila, gerarPeca(novoID));
        novoID++;
        mostrarFila(&fila);
        mostraPilha(&pilha);
        break;
        }

        case 2:{
            
        if(!pilhaCheia(&pilha)){//verifica se a pilha não esta cheia
            
            Peca reservada = dequeue(&fila);//remove a peça da fila
            push(&pilha, reservada);//coloca a peça na pilha
            enqueue(&fila, gerarPeca(novoID));//repõe a peça na fila
            novoID++;
            printf("Peça reservada!\n");
        }else{

            printf("A pilha está cheia.\n");
        }
        mostrarFila(&fila);
        mostraPilha(&pilha);
        break;
        }

        case 3:{

        if(!pilhaVazia(&pilha)){ //verificar se a pilha não está vazia

            Peca usada = pop(&pilha);//remove a peça do topo
            printf("Peça usada: [%d:%c]\n", usada.id, usada.nome);//mostra qual foi usada
        }else{

            printf("A pilha está vazia.\n");
        }
        mostrarFila(&fila);
        mostraPilha(&pilha);
        break;
        }
        
        case 0:
        printf("Saindo...\n");
        break;

        default:
        printf("Opção invalida. \n");
    }
    }while(opcao != 0);

    return 0;
}