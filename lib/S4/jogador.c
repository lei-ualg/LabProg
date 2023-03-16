#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogador.h"

const char *POSITIONS[] = {"Guarda-redes", "Defesa", "Medio", "Avancado"};

Posicao string_to_posicao(char *s)
{
    for (Posicao i = GR; i <= Avancado; i++)
        if (!strcmp(s, POSITIONS[i]))
            return i;
    return -1;
}
const char * posicao_to_string(Posicao p)
{
    return POSITIONS[p];
}

Jogador *jogador(char *primeiro_nome,char *ultimo_nome, int ano, Posicao p, int inter, int golos, char *clube)
{
    Jogador *j = malloc(sizeof(Jogador));

    j->primeiro_nome = strdup(primeiro_nome);
    j->ultimo_nome = strdup(ultimo_nome);
    j->clube = strdup(clube);
    j->ano = ano;
    j->pos = p;
    j->internacionalizacoes = inter;
    j->golos = golos;

    return j;
}

void free_jogador(Jogador *j)
{
    free(j->primeiro_nome);
    free(j->ultimo_nome);
    free(j->clube);
    free(j);
}

Jogador *jogador_dup(Jogador *j)
{
    Jogador *clone = malloc(sizeof(Jogador));

    clone->primeiro_nome = strdup(j->primeiro_nome);
    clone->ultimo_nome = strdup(j->ultimo_nome);
    clone->clube = strdup(j->clube);
    clone->ano = j->ano;
    clone->pos = j->pos;
    clone->internacionalizacoes = j->internacionalizacoes;
    clone->golos = j->golos;

    return clone;
}

void adiciona_internacionalizacao(Jogador *j, int golos)
{
    j->internacionalizacoes++;
    j->golos += golos;
}

void println_jogador(Jogador *j)
{
    printf("[%s][%s][%d][%s][%d][%d][%s]\n", j->primeiro_nome, j->ultimo_nome, j->ano, posicao_to_string(j->pos), j->internacionalizacoes, j->golos, j->clube);
}

void println_jogadores(Jogador *jogadores[], int n)
{
    if (n == 0)
        printf("*\n");
    else
    {
        for (int i = 0; i < n; i++)
            println_jogador(jogadores[i]);
    }
}

int get_jogadores(Jogador *jogadores[], int n)
{
    int res = 0;
    char nome[100] = {}, apelido[100] = {}, posicao[100] = {}, clube[100] = {};
    int ano_nascimento = 0, internacionalizacoes = 0, golos = 0;

    while ((res < n) && (scanf("%s %s %d %s %d %d %s", nome, apelido, &ano_nascimento, posicao, &internacionalizacoes, &golos, clube) != EOF))
        jogadores[res++] = jogador(nome, apelido, ano_nascimento, string_to_posicao(posicao), internacionalizacoes, golos, clube);

    return res;
}

int get_jogadores_from_file(FILE *f, Jogador *jogadores[], int n)
{
    int res = 0;
    char nome[100] = {}, apelido[100] = {}, posicao[100] = {}, clube[100] = {};
    int ano_nascimento = 0, internacionalizacoes = 0, golos = 0;

    fgetc(f);
    while ((res < n) && (fscanf(f, "%s\t%s\t%d\t%s\t%d\t%d\t%[^\n]%*[\n]", nome, apelido, &ano_nascimento, posicao, &internacionalizacoes, &golos, clube) != EOF))
        jogadores[res++] = jogador(nome, apelido, ano_nascimento, string_to_posicao(posicao), internacionalizacoes, golos, clube);

    return res;
}

Jogador *pesquisa_jogador(Jogador *jogadores[], int n, char *primeiro_nome, char *ultimo_nome)
{
    for (int i = 0; i < n; i++)
        if (!strcmp(jogadores[i]->primeiro_nome, primeiro_nome) && !strcmp(jogadores[i]->ultimo_nome, ultimo_nome))
            return jogadores[i];

    return NULL;
}

Jogador *pesquisa_melhor_marcador(Jogador *jogadores[], int n)
{
    if (!n)
        return NULL;

    Jogador *melhor = jogadores[0];

    for (int i = 1; i < n; i++)
        if (jogadores[i]->golos > melhor->golos)
            melhor = jogadores[i];

    return melhor;
}

int pesquisa_jogadores(Jogador *in[], Jogador *out[], int n, int (*p) (Jogador*))
{
    int res = 0;

    for (int i = 0; i < n; i++)
        if (p(in[i]))
            out[res++] = in[i];

    return res;
}

int pesquisa_jogadores_clube(Jogador *in[], Jogador *out[], int n, char* clube)
{
    int res = 0;

    for (int i = 0; i < n; i++)
        if (!strcmp(in[i]->clube, clube))
            out[res++] = in[i];

    return res;
}

int pesquisa_jogadores_inter(Jogador *in[], Jogador *out[], int n, int min_inter, int max_inter)
{
    int res = 0;

    for (int i = 0; i < n; i++)
        if (in[i]->internacionalizacoes >= min_inter && in[i]->internacionalizacoes <= max_inter)
            out[res++] = in[i];

    return res;
}


void test_Jogador_File_Loading(void)
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");

    int n = 0;
    fscanf(f, "%d", &n);

    Jogador **jogadores = malloc(n * sizeof(Jogador *));

    int total = get_jogadores_from_file(f, jogadores, n);

    char criteria[100] = {};

    while (scanf("%s", criteria) != EOF)
    {
        if (criteria[0] == '+')
        {
            char nome[100] = {}, apelido[100] = {};
            int golos = 0;
            scanf("%s %s %d", nome, apelido, &golos);
            Jogador *j = pesquisa_jogador(jogadores, total, nome, apelido);
            if (j != NULL)
            {
                adiciona_internacionalizacao(j, golos);
                println_jogador(j);
            }
            else
                printf("Not found!\n");
        }
        else if (criteria[0] == '?')
        {
            char clube[100] = {};
            scanf("%s", clube);
            Jogador **jogadores_clube = malloc(total * sizeof(Jogador *));
            int res = pesquisa_jogadores_clube(jogadores, jogadores_clube, total, clube);
            println_jogadores(jogadores_clube, res);
            free(jogadores_clube);
        }
    }

    for (int i = 0; i < total; i++)
        free_jogador(jogadores[i]);
    free(jogadores);

    fclose(f);
}

int cmp_jogadores(const void *a, const void *b)
{
    Jogador *j1 = *(Jogador **) a;
    Jogador *j2 = *(Jogador **) b;

    return j1->internacionalizacoes == j2->internacionalizacoes ? (j1->golos < j2->golos ? 1 : -1) : (j1->internacionalizacoes < j2->internacionalizacoes ? 1 : -1);
}

void test_Jogador_Sorting(void)
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");

    int n = 0;
    fscanf(f, "%d", &n);

    Jogador **jogadores = malloc(n * sizeof(Jogador *));

    int total = get_jogadores_from_file(f, jogadores, n);

    qsort(jogadores, total, sizeof(Jogador *), cmp_jogadores);

    println_jogadores(jogadores, total);

    for (int i = 0; i < total; i++)
        free_jogador(jogadores[i]);
    free(jogadores);

    fclose(f);
}

int pesquisa(Jogador *j)
{
    return (j->pos == Avancado && j->golos < 20);
}

void test_Jogador_Pesquisa(void)
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");

    int n = 0;
    fscanf(f, "%d", &n);

    Jogador **jogadores = malloc(n * sizeof(Jogador *));

    int total = get_jogadores_from_file(f, jogadores, n);

    Jogador **jogadores_res = malloc(total * sizeof(Jogador *));
    int res = pesquisa_jogadores(jogadores, jogadores_res, total, pesquisa);

    println_jogadores(jogadores_res, res);

    for (int i = 0; i < total; i++)
        free_jogador(jogadores[i]);
    free(jogadores);
    free(jogadores_res);
}
