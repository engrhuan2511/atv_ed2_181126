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
    int i = hash_funcao(h, chave);
 
    for (NoHash *p = h->lista[i]; p != NULL; p = p->prox) {
        comparacoes++;
        if (p->chave == chave)
            return p->pos;
    }
    return -1;
}
 
int hash_maior_lista(const Hash *h) {
    int maior = 0;
 
    for (int i = 0; i < h->m; i++) {
        int tam = 0;
        for (NoHash *p = h->lista[i]; p != NULL; p = p->prox)
            tam++;
        if (tam > maior)
            maior = tam;
    }
    return maior;
}
 
void hash_libera(Hash *h) {
    if (h == NULL) return;
 
    for (int i = 0; i < h->m; i++) {
        NoHash *p = h->lista[i];
        while (p != NULL) {
            NoHash *prox = p->prox;  /* guarda o próximo antes de liberar */
            free(p);
            p = prox;
        }
    }
    free(h->lista);
    free(h);
}