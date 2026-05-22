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
#define MAX_PILHA 5 //trocado de 3 para 5 para realizar a inversão da pilha com fila

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

//funçaõ do enqueue para adicinar a peça na frente da fila
void enqueueFrente(Fila *f, Peca nova){
    f->inicio = (f->inicio - 1 + MAX) % MAX;
    f->peca[f->inicio] = nova;
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

int filaVazia(Fila *f){

    return f->quantidade == 0;
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

//criação da struct para desfazer
typedef struct{
    int tipoAcao;
    Peca peca;
} Historico;

//código main
int main(){

    srand(time(NULL));
    
    Fila fila;
    inicializarFila(&fila);//para inicializar a fila

    Pilha pilha;
    inicializarPilha(&pilha);//para inicializar apilha

    Historico ultimaAcao;
    ultimaAcao.tipoAcao = -1; //guarda a ultima ação, qual peça foi mexida

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
    printf("4 - Trocar peça do topo da pilha com a da frente da fila\n");
    printf("5 - Desfazer ultima jogada\n");
    printf("6 - Inverter fila com pilha\n");
    printf("0 - Sair\n");
    scanf("%d", &opcao);

    switch(opcao){

        case 1:{
        
            if(!filaVazia(&fila)){

                Peca removida = dequeue(&fila);
                ultimaAcao.tipoAcao = 1;
                ultimaAcao.peca = removida;

                printf("Peca jogada: [%d:%c]\n",
                removida.id,
                removida.nome);

                enqueue(&fila, gerarPeca(novoID));
                novoID++;
            }else{

                printf("A fila está vazia.\n");
            }
            
            mostrarFila(&fila);
            mostraPilha(&pilha);
            break;
        }

        case 2:{
            
            if(!pilhaCheia(&pilha) && !filaVazia(&fila)){
        
                Peca reservada = dequeue(&fila);

                ultimaAcao.tipoAcao = 2;
                ultimaAcao.peca = reservada;

                push(&pilha, reservada);
                enqueue(&fila, gerarPeca(novoID));
                novoID++;

                printf("Peça reservada!\n");

            }else if(pilhaCheia(&pilha)){

                printf("A pilha está cheia.\n");

         }else{

            printf("A fila está vazia.\n");
         }

            mostrarFila(&fila);
            mostraPilha(&pilha);

            break;
        }

        case 3:{

        if(!pilhaVazia(&pilha)){ //verificar se a pilha não está vazia

            Peca usada = pop(&pilha);//remove a peça do topo

            ultimaAcao.tipoAcao = 3;
            ultimaAcao.peca = usada;

            printf("Peça usada: [%d:%c]\n", usada.id, usada.nome);//mostra qual foi usada
        }else{

            printf("A pilha está vazia.\n");
        }
        mostrarFila(&fila);
        mostraPilha(&pilha);
        break;
        }

        case 4:{

            if(!pilhaVazia(&pilha) && !filaVazia(&fila)){

                Peca temp;
                temp = fila.peca[fila.inicio];//guarda peça do inicio da fila
                fila.peca[fila.inicio] = pilha.peca[pilha.topo];//coloca a peça na frente da fila
                pilha.peca[pilha.topo] = temp;//coloca a peça antiga no topo da pilha
                ultimaAcao.tipoAcao = 4;
                printf("Troca realizada! \n");

            }else if(pilhaVazia(&pilha)){

                printf("A pilha está vazia.\n");

            }else{

                printf("A fila está vazia.\n");
            }

            mostrarFila(&fila);
            mostraPilha(&pilha);

            break;
        }

        case 5:{

        //desfazer jogar peça
         if(ultimaAcao.tipoAcao == 1){

            fila.final = (fila.final - 1 + MAX) % MAX;
            fila.quantidade--;

            enqueueFrente(&fila, ultimaAcao.peca);

            printf("Ultima jogada desfeita!\n");

            ultimaAcao.tipoAcao = -1;
        }else if(ultimaAcao.tipoAcao == 2){

            //remove a peça nova gerada no final da fila
            fila.final = (fila.final - 1 + MAX) % MAX;

            fila.quantidade--;

            //remove a peça da pilha
            pop(&pilha);

            //devolve a peça original para frente da fila
            enqueueFrente(&fila, ultimaAcao.peca);

            printf("Reserva desfeita!\n");

            ultimaAcao.tipoAcao = -1;
        }else if(ultimaAcao.tipoAcao == 3){

        push(&pilha, ultimaAcao.peca);

        printf("Uso da peça reservada desfeito!\n");

        ultimaAcao.tipoAcao = -1;
        }else if(ultimaAcao.tipoAcao == 4){

            Peca temp;
            temp = fila.peca[fila.inicio];

            fila.peca[fila.inicio] = pilha.peca[pilha.topo];

            pilha.peca[pilha.topo] = temp;

            printf("Troca desfeita! \n");

            ultimaAcao.tipoAcao = -1;
        }else{

            printf("Nenhuma jogada para desfazer.\n");
        }

        mostrarFila(&fila);
        mostraPilha(&pilha);

        break;
        }

        case 6:{

            Fila filaAux;
            inicializarFila(&filaAux);

            Pilha pilhaAux;
            inicializarPilha(&pilhaAux);

            while(fila.quantidade > 0){
                
                push(&pilhaAux, dequeue(&fila));
            }

            while(!pilhaVazia(&pilha)){

                enqueue(&filaAux, pop(&pilha));
            }
            
            fila = filaAux;
            pilha = pilhaAux;

            printf("Fila e Pilha invertidas.\n");

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