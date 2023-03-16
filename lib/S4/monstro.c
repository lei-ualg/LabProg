#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "monstro.h"

const char *SIZES[] = {"Tiny", "Small", "Medium", "Large", "Huge", "Gargantuan"};

Tamanho string_to_tamanho(char *s)
{
    for (Tamanho i = Tiny; i <= Gargantuan; i++)
        if (!strcmp(s, SIZES[i]))
            return i;
    return -1;
}

const char * tamanho_to_string(Tamanho t)
{
    return SIZES[t];
}

Monstro *monstro(char *nome, char *tipo, Tamanho tam, int ac, int hp, double cr, char *trait)
{
    Monstro *m = malloc(sizeof(Monstro));

    m->nome = strdup(nome);
    m->tipo = strdup(tipo);
    m->trait = strdup(trait);

    m->tam = tam;
    m->ac = ac;
    m->hp = hp;
    m->cr = cr;

    return m;
}

void free_monstro(Monstro *m)
{
    free(m->nome);
    free(m->tipo);
    free(m->trait);
    free(m);
}

Monstro *monstro_dup(Monstro *m)
{
    return monstro(m->nome, m->tipo, m->tam, m->ac, m->hp, m->cr, m->trait);
}

void atualiza_stats(Monstro *m, int ac, int hp, double cr)
{
    m->ac = ac;
    m->hp = hp;
    m->cr = cr;
}

void println_monstro(Monstro *m)
{
    printf("%s - %s %s, AC:%d, HP:%d, CR:%.2f, Trait:%s\n", m->nome, tamanho_to_string(m->tam), m->tipo, m->ac, m->hp, m->cr, m->trait);
}

void println_monstros(Monstro *monstros[], int n)
{
    if (!n)
        printf("None\n");
    else
        for (int i = 0; i < n; i++)
            println_monstro(monstros[i]);
}

int get_monstros(Monstro *monstros[], int n)
{
    char nome[100], tipo[100], trait[100], tam[100];
    int ac, hp, res = 0;
    double cr;

    while ((res < n) && (scanf("%s %s %s %d %d %lf %s", nome, tipo, tam, &ac, &hp, &cr, trait) != EOF))
        monstros[res++] = monstro(nome, tipo, string_to_tamanho(tam), ac, hp, cr, trait);

    return n;
}

int get_monstros_from_file(FILE *f, Monstro *monstros[], int n)
{
    char nome[100], tipo[100], trait[100], tam[100];
    int ac, hp, res = 0;
    double cr;

    fgetc(f);
    while ((res < n) && (fscanf(f, "%[^,],%[^,],%[^,],%d,%d,%lf,%[^\n]%*[\n]", nome, tipo, tam, &ac, &hp, &cr, trait) != EOF))
    {
        monstros[res++] = monstro(nome, tipo, string_to_tamanho(tam), ac, hp, cr, trait);
    }

    return n;
}

Monstro *pesquisa_monstro(Monstro *monstros[], int n, char *nome)
{
    for (int i = 0; i < n; i++)
        if (!strcmp(monstros[i]->nome, nome))
            return monstros[i];

    return NULL;
}

Monstro *pesquisa_monstro_mais_duro(Monstro *monstros[], int n)
{
    Monstro *res = NULL;
    int max = 0;

    for (int i = 0; i < n; i++)
        if (monstros[i]->hp > max)
        {
            max = monstros[i]->hp;
            res = monstros[i];
        }

    return res;
}

int pesquisa_monstros(Monstro *in[], Monstro *out[], int n, int (*p) (Monstro*))
{
    int res = 0;

    for (int i = 0; i < n; i++)
        if (p(in[i]))
            out[res++] = in[i];

    return res;
}

int pesquisa_monstros_tipo(Monstro *in[], Monstro *out[], int n, char *tipo)
{
    int res = 0;

    for (int i = 0; i < n; i++)
        if (!strcmp(in[i]->tipo, tipo))
            out[res++] = in[i];

    return res;
}

int pesquisa_monstros_cr(Monstro *in[], Monstro *out[], int n, double cr_min, double cr_max)
{
    int res = 0;

    for (int i = 0; i < n; i++)
        if ((in[i]->cr >= cr_min) && (in[i]->cr <= cr_max))
            out[res++] = in[i];

    return res;
}

void test_Monstro_File_Loading(void)
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");

    int n = 0;
    fscanf(f, "%d", &n);

    Monstro **monstros = malloc(n * sizeof(Monstro *));

    int total = get_monstros_from_file(f, monstros, n);

    char type[100], criteria[100];

    Monstro **monstros_cr = malloc(total * sizeof(Monstro *));
    Monstro **monstros_res = malloc(total * sizeof(Monstro *));

    while (scanf("%s", type) != EOF)
    {
        int res = 0, cr_res = 0;
        scanf("%s", criteria);
        if (strcmp(criteria, "*"))
        {
            double min, max;
            sscanf(criteria, "%lf", &min);
            scanf("%lf", &max);
            cr_res = pesquisa_monstros_cr(monstros, monstros_cr, total, min, max);
            res = pesquisa_monstros_tipo(monstros_cr, monstros_res, cr_res, type);
        }
        else
        {
            res = pesquisa_monstros_tipo(monstros, monstros_res, total, type);
        }
        println_monstros(monstros_res, res);
    }

    for (int i = 0; i < total; i++)
        free_monstro(monstros[i]);
    free(monstros);
    free(monstros_cr);
    free(monstros_res);

    fclose(f);
}

int cmp_monstros(const void *a, const void *b)
{
    Monstro *m1 = *(Monstro **) a;
    Monstro *m2 = *(Monstro **) b;

    if (m1->cr == m2->cr)
        return strcmp(m1->nome, m2->nome);
    else
        return (m1->cr < m2->cr ? 1 : -1);
}


void test_Monstro_Sorting(void)
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");

    int n = 0;
    fscanf(f, "%d", &n);

    Monstro **monstros = malloc(n * sizeof(Monstro *));

    int total = get_monstros_from_file(f, monstros, n);

    qsort(monstros, total, sizeof(Monstro *), cmp_monstros);

    println_monstros(monstros, total);

    for (int i = 0; i < total; i++)
        free_monstro(monstros[i]);
    free(monstros);

    fclose(f);
}

int pesquisa(Monstro* m)
{
    return (m->hp > 10 && m->tam == Medium);
}

void test_Monstro_Pesquisa(void)
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");

    int n = 0;
    fscanf(f, "%d", &n);

    Monstro **monstros = malloc(n * sizeof(Monstro *));

    int total = get_monstros_from_file(f, monstros, n);

    Monstro **monstros_res = malloc(total * sizeof(Monstro *));
    int res = pesquisa_monstros(monstros, monstros_res, total, pesquisa);

    println_monstros(monstros_res, res);

    for (int i = 0; i < total; i++)
        free_monstro(monstros[i]);
    free(monstros);
    free(monstros_res);
}