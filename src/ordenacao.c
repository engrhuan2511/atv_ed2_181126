#include "ordenacao.h"
#include "medicao.h"

/* ===================== TAREFA 1: ORDENAÇÃO =====================
   Ordene v em ordem CRESCENTE de matrícula.
   A cada comparação entre duas matrículas, faça comparacoes++.
   Dica: copie o Aluno inteiro (struct), não só a matrícula. */

/* Insertion Sort: O(n^2). Soma 1 a cada comparação de matrículas. */
void ordena_insercao(Aluno *v, int n) {
    for (int i = 1; i < n; i++) {
        Aluno x = v[i];                       /* elemento a inserir */
        int j = i - 1;
        while (j >= 0 && (comparacoes++, v[j].matricula > x.matricula)) {
            v[j + 1] = v[j];                  /* desloca o maior para a direita */
            j--;
        }
        v[j + 1] = x;
    }
}

/* Quicksort: pivô no meio, partição de Hoare. Compara com o pivô. */
static void quick(Aluno *v, int ini, int fim) {
    int i = ini, j = fim, p = v[ini + (fim - ini) / 2].matricula;
    while (i <= j) {
        while (comparacoes++, v[i].matricula < p) i++;
        while (comparacoes++, v[j].matricula > p) j--;
        if (i <= j) { Aluno t = v[i]; v[i++] = v[j]; v[j--] = t; }
    }
    if (ini < j) quick(v, ini, j);            /* ordena o lado esquerdo */
    if (i < fim) quick(v, i, fim);            /* ordena o lado direito */
}

void ordena_quick(Aluno *v, int n) { if (n > 1) quick(v, 0, n - 1); }

void ordena_quick(Aluno *v, int n) { if (n > 1) quick(v, 0, n - 1); }
