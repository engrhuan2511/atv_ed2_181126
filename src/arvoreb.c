#include <stddef.h>
#include "arvoreb.h"
#include "medicao.h"

/* Busca interna usada durante a insercao. Nao altera o contador de comparacoes, 
que no trabalho mede as buscas realizadas no comparativo, e se nao gostou eu vou la no Messias. */

static int busca_sem_contar(const NoB *x, int chave) {  

   if (x == NULL) return -1;
   int i = 0;
   while (i < x->n && chave > x->chave[i]) i++;

   if (i < x->n && chave == x->chave[i])
      return x->pos[i];

   if (x->folha)
      return -1;
   return busca_sem_contar(x-> filho[i], chave);
}

/* Conta um no por visita, conforme especificado. */

int arvb_busca(const ArvoreB *a, int chave) {
    if (a == NULL || a->raiz == NULL) return -1;

    const NoB *x = a->raiz;
    while (x != NULL) {
       comparacoes++;

       int i = 0;
       while (i < x->n && chave > x->chave[i]) i++;

       if (i < x->n && chave == x->chave[i])
          return x->pos[i];

       if (x->folha)
          return -1;

       x = x->filho[i];
   }
   return -1; 

}

/* Divide o filho cheio x->filho[i] em dois nos. Igual na Biblia, quando o Rei Salomao quis partir aquela
crianca ao meio. */
static void divide_filho(ArvoreB *a, NoB *x, int i) {
   int t = a->t;
   NoB *cheio = x->filho[i];
   NoB *direita = arvb_novo_no(a, cheio->folha);

   direita->n = t - 1;

   for (int j = 0; j < t - 1; j++) { 
      
   
        direita->chave[j] = cheio->chave[j + t];
        direita->pos[j] = cheio->pos[j + t];
    }

    if (!cheio->folha) {
        for (int j = 0; j < t; j++)
            direita->filho[j] = cheio->filho[j + t];
    }

    int chave_meio = cheio->chave[t - 1];
    int pos_meio = cheio->pos[t - 1];
    cheio->n = t - 1;

    for (int j = x->n; j >= i + 1; j--)
        x->filho[j + 1] = x->filho[j];
    x->filho[i + 1] = direita;

    for (int j = x->n - 1; j >= i; j--) {
        x->chave[j + 1] = x->chave[j];
        x->pos[j + 1] = x->pos[j];
    }

    x->chave[i] = chave_meio;
    x->pos[i] = pos_meio;
    x->n++;
}

/* Insere em um no que certamente que nao, nao esta cheio. */
static void insere_nao_cheio(ArvoreB *a, NoB *x, int chave, int pos) {
    int i = x->n - 1;

    if (x->folha) {
        while (i >= 0 && chave < x->chave[i]) {
            x->chave[i + 1] = x->chave[i];
            x->pos[i + 1] = x->pos[i];
            i--;
        }
        x->chave[i + 1] = chave;
        x->pos[i + 1] = pos;
        x->n++;
        return;
    }

    while (i >= 0 && chave < x->chave[i]) i--;
    i++;

    if (x->filho[i]->n == 2 * a->t - 1) {
        divide_filho(a, x, i);
        if (chave > x->chave[i]) i++;
    }

    insere_nao_cheio(a, x->filho[i], chave, pos);
}

void arvb_insere(ArvoreB *a, int chave, int pos) {
    if (a == NULL || a->t < 2) return;

    /* A arvore nao deve armazenar matriculas repetidas. tem que cloar cpf de alguem
    pra poder matricular*/
    if (busca_sem_contar(a->raiz, chave) != -1)
        return;

    if (a->raiz == NULL) {
        a->raiz = arvb_novo_no(a, 1);
        a->raiz->chave[0] = chave;
        a->raiz->pos[0] = pos;
        a->raiz->n = 1;
        return;
    }

    if (a->raiz->n == 2 * a->t - 1) {
        NoB *nova_raiz = arvb_novo_no(a, 0);
        nova_raiz->filho[0] = a->raiz;
        a->raiz = nova_raiz;
        divide_filho(a, nova_raiz, 0);
        insere_nao_cheio(a, nova_raiz, chave, pos);
    } else {
        insere_nao_cheio(a, a->raiz, chave, pos);
    }
}

int arvb_altura(const ArvoreB *a) {
    if (a == NULL || a->raiz == NULL) return 0;

    int altura = 0;
    const NoB *x = a->raiz;
    while (x != NULL) {
        altura++;
        if (x->folha) break;
        x = x->filho[0];
    }
    return altura;
}

/* Percorre apenas filhos cujo intervalo de chaves pode cruzar [ini, fim]. */
static int conta_faixa_no(const NoB *x, int ini, int fim) {
    if (x == NULL) return 0;

    int total = 0;
    for (int i = 0; i < x->n; i++) {
        if (x->chave[i] >= ini && x->chave[i] <= fim)
            total++;
    }

    if (!x->folha) {
        for (int i = 0; i <= x->n; i++) {
            /* Filho i contem valores entre chave[i-1] e chave[i].
               Limites estritos evitam visitar ramos fora da faixa. */
            if ((i == 0 || x->chave[i - 1] < fim) &&
                (i == x->n || x->chave[i] > ini)) {
                total += conta_faixa_no(x->filho[i], ini, fim);
            }
        }
    }

    return total;
}

int arvb_conta_faixa(const ArvoreB *a, int ini, int fim) {
    if (a == NULL || a->raiz == NULL || ini > fim) return 0;
    return conta_faixa_no(a->raiz, ini, fim);
}

 







}





