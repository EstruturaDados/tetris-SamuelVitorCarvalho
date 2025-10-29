#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

typedef struct
{
    char tipo;
    int id;
} Peca;

typedef struct
{
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

void inicializarFila(Fila *fila);
int filaCheia(Fila *fila);
int filaVazia(Fila *f);
void inserir(Fila *f, Peca *p);
void remover(Fila *f, Peca *p);
void mostrarFila(Fila *f);
void menu();
void gerarPeca(Fila *f, Peca *p);

int main()
{
    Fila fila;
    inicializarFila(&fila);
    int opcao;

    printf("============================\n");
    printf("   Jogo do Tetris   \n");
    printf("============================\n");

    mostrarFila(&fila);

    do
    {
        menu();
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            Peca p;
            remover(&fila, &p);
            if (!filaVazia(&fila))
            {
                printf("Peça removida: ID: %d, Tipo: %c\n", p.id, p.tipo);
            }
            mostrarFila(&fila);
            break;
        }
        case 2:
        {
            Peca novaPeca;
            gerarPeca(&fila, &novaPeca);

            printf("Peça gerada: Tipo %c, ID %d\n", novaPeca.tipo, novaPeca.id);

            inserir(&fila, &novaPeca);
            mostrarFila(&fila);
            break;
        }
        case 3:
            printf("Saindo do jogo Tetris.\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }

        if (opcao != 3)
        {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
            printf("\n");
        }
    } while (opcao != 3);

    return 0;
}

void menu()
{
    printf("Menu do jogo Tetris:\n");
    printf("1. Jogar peça (dequeue)\n");
    printf("2. Inserir nova peça (enqueue)\n");
    printf("3. Sair\n");
}

void inicializarFila(Fila *fila)
{
    fila->inicio = 0;
    fila->fim = 4;
    fila->total = 5;

    char tipos[] = {'I', 'O', 'T', 'L'};
    for (int i = 0; i < MAX; i++)
    {
        fila->itens[i].tipo = tipos[i % 4];
        fila->itens[i].id = i + 1;
    }
}

int filaCheia(Fila *fila)
{
    return fila->total == MAX;
}

int filaVazia(Fila *f)
{
    return f->total == 0;
}

void mostrarFila(Fila *f)
{
    if (filaVazia(f))
    {
        printf("Fila vazia.\n");
        return;
    }
    printf("Peças: ");
    for (int i = 0; i < f->total; i++)
    {
        int index = (f->inicio + i) % MAX;
        printf("[%c %d]", f->itens[index].tipo, f->itens[index].id);
    }
    printf("\n");
}

void gerarPeca(Fila *f, Peca *p)
{
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indiceAleatorio = rand() % 4;

    p->tipo = tipos[indiceAleatorio];

    if (filaVazia(f))
    {
        p->id = 1;
    }
    else
    {
        p->id = f->itens[f->fim].id + 1;
    }
}

void inserir(Fila *f, Peca *p)
{
    if (filaCheia(f))
    {
        printf("Fila cheia. Não é possível inserir nova peça.\n");
        return;
    }

    // Pega o ID do último elemento da fila + 1
    p->id = f->itens[f->fim].id + 1;
    f->fim = (f->fim + 1) % MAX;
    f->itens[f->fim] = *p;
    f->total++;
}

void remover(Fila *f, Peca *p)
{
    if (filaVazia(f))
    {
        printf("Fila vazia. Não é possível remover peça.\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}
