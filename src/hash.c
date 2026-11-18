#include <stdlib.h>
#include "hash.h"
#include "medicao.h"

/* ===================== TAREFA 3: TABELA HASH =====================
   Encadeamento: cada posição da tabela é uma lista ligada de NoHash. */

Hash *hash_cria(int m) {
    Hash *h = malloc(sizeof(Hash));
    if (h == NULL) return NULL;
 
    h->m = m;
    h->n = 0;
    h->lista = calloc(m, sizeof(NoHash *));  /* m ponteiros, todos NULL */
    if (h->lista == NULL) {
        free(h);
        return NULL;
    }
    return h;
}
 
int hash_funcao(const Hash *h, int chave) {
    return chave % h->m;  /* método da divisão */
}
 
void hash_insere(Hash *h, int chave, int pos) {
    int i = hash_funcao(h, chave);
 
    NoHash *novo = malloc(sizeof(NoHash));
    if (novo == NULL) return;
 
    novo->chave = chave;
    novo->pos = pos;
    novo->prox = h->lista[i];  /* aponta para o antigo primeiro nó */
    h->lista[i] = novo;        /* novo vira o início da lista */
    h->n++;
}

int hash_busca(const Hash *h, int chave) {
    /* TODO: percorra a lista da posição hash_funcao(h, chave).
       Faça comparacoes++ a cada nó visitado.
       Achou: devolva p->pos. Chegou ao fim: devolva -1. */
    (void)h; (void)chave;
    return -1;
}

int hash_maior_lista(const Hash *h) {
    /* TODO: devolva o tamanho da maior lista da tabela. */
    (void)h;
    return 0;
}

void hash_libera(Hash *h) {
    if (h == NULL) return;
    /* TODO: libere todos os nós de todas as listas antes das linhas abaixo. */
    free(h->lista);
    free(h);
}
