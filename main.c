#include <stdio.h>
#include <stdlib.h>

// ESTRUTURA

int contador, i, inseridos;

typedef struct NO {
    int reg;
    int nivel;
    struct NO *esq, *dir;
} NO;

typedef struct Arvore {
    NO *no;
} Arvore;

// FUNÇÕES

void iniciaABB(Arvore *arvore) {
    arvore->no = NULL;
    printf("Arvore Binaria iniciada!\n");
}

int arvoreVazia(Arvore *arvore) {
    if (arvore->no == NULL) {
        return 0;
    } else {
        return 1;
    }
}

void insereElemento(Arvore *arvore, int x) {
    if (arvoreVazia(arvore) == 0) {
        arvore->no = malloc(sizeof(NO));
        arvore->no->reg = x;
        arvore->no->esq = NULL;
        arvore->no->dir = NULL;
        arvore->no->nivel = 0;
        contador = 0;
        printf("Elemento %d inserido na ABB!\n", x);
    } else {
        NO *aux = arvore->no;
        NO *novo = malloc(sizeof(NO));
        novo->reg = x;
        novo->esq = NULL;
        novo->dir = NULL;
        contador++;
        while (aux != NULL) {
            if (x > aux->reg) {
                if (aux->dir == NULL) {
                    aux->dir = novo;
                    aux->dir->nivel = contador;
                    contador = 0;
                    printf("Elemento %d inserido na ABB!\n", x);
                    return;
                } else {
                    aux = aux->dir;
                    contador++;
                }
            } else if (x < aux->reg) {
                if (aux->esq == NULL) {
                    aux->esq = novo;
                    aux->esq->nivel = contador;
                    contador = 0;
                    printf("Elemento %d inserido na ABB!\n", x);
                    inseridos++;
                    return;
                } else {
                    aux = aux->esq;
                    contador++;
                }
            }

        }
    }
}

void pesquisaElemento(Arvore *arvore, int x) {
    NO *aux = arvore->no;
    while (aux != NULL) {
        if (x == aux->reg) {
            printf("O numero %d existe na arvore!\n", x);
            return;
        } else {
            if (x > aux->reg) {
                aux = aux->dir;
            } else {
                aux = aux->esq;
            }
        }
    }
    printf("O numero %d nao existe na arvore!\n", x);
}

void InOrdem(NO *no, int vetor[100]) {
    if (no != NULL) {
        InOrdem(no->esq, vetor);
        vetor[contador] = no->reg;
        contador++;
        InOrdem(no->dir, vetor);
    }
}

void montaNovaArvore(int vetor[], int esquerda, int direita, Arvore *arvore) {
    int med;
    if (esquerda > direita) {
        return;
    } else {
        med = ((direita - esquerda) / 2) + esquerda;
        insereElemento(arvore, vetor[med]);
        montaNovaArvore(vetor, esquerda, (med - 1), arvore);
        montaNovaArvore(vetor, (med + 1), direita, arvore);
    }
}

void balanceiaABB(int vetor[100], Arvore *arvore) {
    InOrdem(arvore->no, vetor);
    int raiz = contador / 2;
    int resto = contador % 2;
    arvore->no = NULL;
    if (resto == 0) {
        raiz--;
        int esquerda = 0;
        int direita = contador - 1;
        montaNovaArvore(vetor, esquerda, direita, arvore);
    } else {
        int esquerda = 0;
        int direita = contador - 1;
        montaNovaArvore(vetor, esquerda, direita, arvore);
    }
}

void imprimeConformeNivel(NO *fonte, int nivel) {

    if (fonte == NULL) return;

    if (nivel == 1){
        printf("%d ", fonte->reg);
    }
    else if (nivel > 1) {
        imprimeConformeNivel(fonte->esq, nivel - 1);
        imprimeConformeNivel(fonte->dir, nivel - 1);
    }
}

int altura(NO *no) {
    if (no == NULL) return 0;

    else {
        int lheight = altura(no->esq);
        int rheight = altura(no->dir);

        if (lheight > rheight) {
            return (lheight + 1);
        }
        else {
            return (rheight + 1);
        }
    }
}

void imprimeNivelOrdenados(NO *fonte) {

    int h = altura(fonte);
    int i;
    for (i=1; i<=h; i++)
    imprimeConformeNivel(fonte, i);
}

int main() {

    Arvore arvore;
    int sair = 0, opcao = 0, elemento;
    int vetor[100];

    do {
        printf("\nMenu\n\n1 - Inicia ABB\n2 - Insere elemento na ABB\n3 - Pesquisa elemento na ABB\n4 - Balanceia ABB\n5 - Mostra elementos por nivel da ABB\n9 - Sair\nDigite sua opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                iniciaABB(&arvore);
                break;
            case 2:
                printf("Digite o elemento a ser inserido:");
                scanf("%d", &elemento);
                insereElemento(&arvore, elemento);
                break;
            case 3:
                printf("Digite o elemento a ser inserido:");
                scanf("%d", &elemento);
                pesquisaElemento(&arvore, elemento);
                break;
            case 4:
                balanceiaABB(vetor, &arvore);
                break;
            case 5:
                imprimeNivelOrdenados(arvore.no);
                break;
            case 9:
                sair = 9;
                break;
            default:
                printf("Opcão inexistente!\n");
                break;
        }
    } while (sair != 9);

    return 0;
}