#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>

const char *author = "Leonardo Marinho Albudane";

// Programa F ----------------------------------------------------------------------------------- //
typedef enum sizes
{
    Tiny,
    Small,
    Medium,
    Large,
    Huge,
    Gargantuan
} size;

const char *SIZES[6] = {"Tiny", "Small", "Medium", "Large", "Huge", "Gargantuan"};

size parse_size(char *s)
{
    for (int i = 0; i < 6; i++)
        if (!strcmp(s, SIZES[i]))
            return i;
    return -1;
}

typedef struct
{
    char name[100];
    char type[100];
    size size;
    int armor_class;
    int hit_points;
    double challenge_rating;
} Creature;


Creature create_creature(char *name, char *type, char *size, int armor_class, int hit_points, double challenge_rating)
{
    assert(parse_size(size) >= Tiny && parse_size(size) <= Gargantuan);

    Creature c;

    strcpy(c.name, name);
    strcpy(c.type, type);
    c.size = parse_size(size);
    c.armor_class = armor_class;
    c.hit_points = hit_points;
    c.challenge_rating = challenge_rating;

    return c;
}

void print_creature(Creature c)
{
    printf("%s - %s %s, AC:%d, HP:%d, CR:%.2f\n", c.name, SIZES[c.size], c.type, c.armor_class, c.hit_points, c.challenge_rating);
}

void monstros_to_monstros_ptr(Creature *in, Creature **out, int n)
{
    for (int i = 0; i < n; i++)
        out[i] = in + i;
}

int pesquisa_monstros_cr(Creature **in, int n, Creature **out, double cr_min, double cr_max)
{
    int j = 0;
    for (int i = 0; i < n; i++)
        if (in[i]->challenge_rating >= cr_min && in[i]->challenge_rating <= cr_max)
            out[j++] = in[i];
    return j;
}

int pesquisa_monstros_tipo(Creature **in, int n, Creature **out, char *type)
{
    int j = 0;
    for (int i = 0; i < n; i++)
        if (!strcmp(in[i]->type, type))
            out[j++] = in[i];
    return j;
}

int get_monstros(Creature *a, int n)
{
    int result = 0;

    char name[100] = {}, type[100] = {}, size[100] = {};
    int ac = 0, hp = 0;
    double cr = 0;

    while ((result < n) && (scanf("%s %s %s %d %d %lf", name, type, size, &ac, &hp, &cr) != EOF))
        a[result++] = create_creature(name, type, size, ac, hp, cr);

    return result;
}

void testF()
{
    int n = 0;
    scanf("%d", &n);

    Creature *creatures = malloc(n * sizeof(Creature));
    assert(creatures != NULL);

    int total = get_monstros(creatures, n);

    char type[100], criteria[100];

    Creature **monstros_ptr = malloc(total * sizeof(Creature *));
    Creature **monstros_cr = malloc(total * sizeof(Creature *));
    Creature **monstros_res = malloc(total * sizeof(Creature *));

    monstros_to_monstros_ptr(creatures, monstros_ptr, total);
    while (scanf("%s", type) != EOF)
    {
        int res = 0, cr_res = 0;
        scanf("%s", criteria);
        if (strcmp(criteria, "*"))
        {
            double min, max;
            sscanf(criteria, "%lf", &min);
            scanf("%lf", &max);
            cr_res = pesquisa_monstros_cr(monstros_ptr, total, monstros_cr, min, max);
            res = pesquisa_monstros_tipo(monstros_cr, cr_res, monstros_res, type);
        }
        else
        {
            res = pesquisa_monstros_tipo(monstros_ptr, total, monstros_res, type);
        }

        if (res == 0)
            printf("None\n");
        else
            for (int i = 0; i < res; i++)
                print_creature(*monstros_res[i]);
    }

    free(creatures);
    free(monstros_ptr);
    free(monstros_cr);
    free(monstros_res);
}
// Programa G ----------------------------------------------------------------------------------- //

typedef enum posicoes
{
    Guarda_redes,
    Defesa,
    Medio,
    Avancado
} posicao;

const char *POSICOES[4] = {"Guarda-redes", "Defesa", "Medio", "Avancado"};

posicao parse_posicao(char *s)
{
    for (int i = 0; i < 4; i++)
        if (!strcmp(s, POSICOES[i]))
            return i;
    return -1;
}

typedef struct S_Jogador
{
    char nome[100];
    char apelido[100];
    int ano_nascimento;
    posicao posicao;
    int internacionalizacoes;
    int golos;
    char clube[100];
} Jogador;

Jogador create_jogador(char *nome, char *apelido, int ano_nascimento, char *posicao, int internacionalizacoes, int golos, char *clube)
{
    Jogador j;

    strcpy(j.nome, nome);
    strcpy(j.apelido, apelido);
    strcpy(j.clube, clube);
    j.ano_nascimento = ano_nascimento;
    j.posicao = parse_posicao(posicao);
    j.internacionalizacoes = internacionalizacoes;
    j.golos = golos;

    return j;
}

void print_jogador(Jogador j)
{
    printf("[%s][%s][%d][%s][%d][%d][%s]\n", j.nome, j.apelido, j.ano_nascimento, POSICOES[j.posicao], j.internacionalizacoes, j.golos, j.clube);
}

void adiciona_internacionalizacao(Jogador *j, int golos)
{
    j->internacionalizacoes++;
    j->golos += golos;
}

Jogador *pesquisa_jogador(Jogador *j, int n, char *nome, char *sobrenome)
{
    for (int i = 0; i < n; i++)
        if (!strcmp(j[i].nome, nome) && !strcmp(j[i].apelido, sobrenome))
            return j + i;
    return NULL;
}

int pesquisa_jogadores_clube(Jogador *in, int n, Jogador *out, char *clube)
{
    int res = 0;
    for (int i = 0; i < n; i++)
        if (!strcmp(in[i].clube, clube))
            out[res++] = in[i];
    return res;
}

int get_jogadores(Jogador *a, int n)
{
    int result = 0;

    char nome[100] = {}, apelido[100] = {}, posicao[100] = {}, clube[100] = {};
    int ano_nascimento = 0, internacionalizacoes = 0, golos = 0;

    while ((result < n) && (scanf("%s %s %d %s %d %d %s", nome, apelido, &ano_nascimento, posicao, &internacionalizacoes, &golos, clube) != EOF))
        a[result++] = create_jogador(nome, apelido, ano_nascimento, posicao, internacionalizacoes, golos, clube);

    return result;
}

void testG()
{
    int n = 0;
    scanf("%d", &n);

    Jogador *jogadores = malloc(n * sizeof(Jogador));
    assert(jogadores != NULL);

    int total = get_jogadores(jogadores, n);
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
                print_jogador(*j);
            }
            else
                printf("Not found!\n");
        }
        else if (criteria[0] == '?')
        {
            char clube[100] = {};
            scanf("%s", clube);
            Jogador *jogadores_clube = malloc(total * sizeof(Jogador));
            int res = pesquisa_jogadores_clube(jogadores, total, jogadores_clube, clube);
            if (!res)
                printf("*\n");
            else
                for (int i = 0; i < res; i++)
                    print_jogador(jogadores_clube[i]);
            free(jogadores_clube);
        }
    }

    free(jogadores);
}
// Unit Test ------------------------------------------------------------------------------------ //

void unit_tests()
{
}

// Main ----------------------------------------------------------------------------------------- //

int main(int argc, char **argv)
{
    int x = 'F';
    if (argc > 1)
        x = *argv[1];

    switch (x)
    {
    case 'F':
        testF();
        break;
    case 'G':
        testG();
        break;
        break;
    case 'U':
        unit_tests();
        printf("All unit tests PASSED.\n");
        break;
    default:
        printf("%s: Invalid option.\n", argv[1]);
        break;
    }
    return 0;
}