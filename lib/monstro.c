// este operador serve para dizer ao compilador de C, que este ficheiro header so deve ser processado
// se ainda nao sido processado anteriormente
// le-se "se ainda nao tiver sido definido MONSTRO_H, define MONSTRO_H".
// Se o teste falhar (i.e. o MONSTRO_H ja foi definido), o compilador salta para o #endif e tudo o que esta
// dentro do #if e ignorado

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monstro.h"
// Definicao do enumerado Tamanho

const char *SIZES[] = {"Tiny", "Small", "Medium", "Large", "Huge", "Gargantuan"};

// Dada uma string, retorna o tamanho (valor enumerado) correspondente a string recebida
Tamanho string_to_tamanho(char *s)
{
    for (Tamanho i = Tiny; i <= Gargantuan; i++)
        if (!strcmp(s, SIZES[i]))
            return i;
    return -1;
}

// Dada um tamanho, retorna uma String que descreve o tamanho
const char *tamanho_to_string(Tamanho t)
{
    return SIZES[t];
}

// Construtor do tipo Monstro, recebe os membros, e cria um novo monstro, e inicializa-o. Devolve
// um ponteiro para o monstro criado
Monstro *monstro(char *nome, char *tipo, Tamanho tam, int ac, int hp, double cr, char *trait)
{
    Monstro *m = malloc(sizeof(Monstro));

    m->nome = malloc(strlen(nome) + 1);
    strcpy(m->nome, nome);
    m->tipo = malloc(strlen(tipo) + 1);
    strcpy(m->tipo, tipo);
    m->trait = malloc(strlen(trait) + 1);
    strcpy(m->trait, trait);

    m->tam = tam;
    m->ac = ac;
    m->hp = hp;
    m->cr = cr;

    return m;
}

// Recebe um ponteiro para um monstro, e liberta a memória usada pelo tipo
void free_monstro(Monstro *m)
{
    free(m->nome);
    free(m->tipo);
    free(m->trait);
    free(m);
}

// Recebe um ponteiro para um monstro, e cria uma copia (ou clone) profunda do monstro. Devolve um
// ponteiro para o monstro criado
Monstro *monstro_dup(Monstro *m)
{
    Monstro *clone = malloc(sizeof(Monstro));

    clone->nome = malloc(strlen(m->nome) + 1);
    strcpy(clone->nome, m->nome);
    clone->tipo = malloc(strlen(m->tipo) + 1);
    strcpy(clone->tipo, m->tipo);
    clone->trait = malloc(strlen(m->trait) + 1);
    strcpy(clone->trait, m->trait);

    clone->tam = m->tam;
    clone->ac = m->ac;
    clone->hp = m->hp;
    clone->cr = m->cr;

    return clone;
}

// Recebe um ponteiro para um monstro, e atualiza algum dos seus membros com os valores recebidos
void atualiza_stats(Monstro *m, int ac, int hp, double cr)
{
    m->ac = ac;
    m->hp = hp;
    m->cr = cr;
}

// Imprime um monstro para o Standard Output, usando o seguinte formato:
//<Nome do Monstro> - <Tamanho> <Tipo Criatura>, AC:<Armor Class>, HP:<Hit Points>, CR: <Challenge Rating>, Trait: <trait>\n
// por exemplo:
// Imp – Tiny Fiend, AC:13, HP:10, CR:1.00, Trait:Shapechanger\n
void println_monstro(Monstro *m)
{
    printf("%s - %s %s, AC:%d, HP:%d, CR:%.2f, Trait:%s\n", m->nome, tamanho_to_string(m->tam), m->tipo, m->ac, m->hp, m->cr, m->trait);
}

// Recebe um array de ponteiros para monstros, e o numero de elementos no array n, e imprime
// todos os monstros, pela ordem em que aparecem no array. Caso nao existam elementos no array
// imprime "None\n"
void println_monstros(Monstro *monstros[], int n)
{
    if (!n)
        printf("None\n");
    else
        for (int i = 0; i < n; i++)
            println_monstro(monstros[i]);
}

// Dado um array de ponteiros para monstros, e um numero n de monstros a ler, le do standard input os n monstros.
// cada monstro deve ser lido numa unica linha, com todos os membros separados por espaco, pela seguinte ordem
//<Nome do Monstro> <Tipo Criatura> <Tamanho> <Armor Class> <Hit Points> <Challenge Rating> <Trait>.
// Os membros que correspondem a cadeias de caracteres (strings) nao excederao os 100 caracteres cada.
// O metodo retorna o numero de monstros efetivamente lidos.
int get_monstros(Monstro *monstros[], int n)
{
    char nome[100], tipo[100], trait[100], tam[100];
    int ac, hp, res = 0;
    double cr;

    while ((res < n) && (scanf("%s %s %s %d %d %lf %s", nome, tipo, tam, &ac, &hp, &cr, trait) != EOF))
        monstros[res++] = monstro(nome, tipo, string_to_tamanho(tam), ac, hp, cr, trait);

    return n;
}

// Dado um array de ponteiros para monstros, um numero n de monstros, uma string com o nome,
// esta funcao procura no array monstros pelo primeiro monstro com nome igual ao nome recebido,
//  e retorna o ponteiro para esse monstro.
// Caso nao exista tal monstro, retorna-se o ponteiro NULL
Monstro *pesquisa_monstro(Monstro *monstros[], int n, char *nome)
{
    for (int i = 0; i < n; i++)
        if (!strcmp(monstros[i]->nome, nome))
            return monstros[i];

    return NULL;
}

// Dado um array de ponteiros para monstros, um numero n de monstros nesse array, retorna o monstro
// com maior numero de hit points. Caso nao exista nenhum monstro, retorna-se NULL
Monstro *pesquisa_monstro_mais_duro(Monstro *monstros[], int n)
{
    if (!n)
        return NULL;

    Monstro *maior_hp = monstros[0];

    for (int i = 1; i < n; i++)
        if (monstros[i]->hp > maior_hp->hp)
            maior_hp = monstros[i];

    return maior_hp;
}

// dado um array de entrada de ponteiros de monstros in, e um array de saida de ponteiros de monstros out,
// um inteiro n que corresponde ao numero de elementos de in, e uma string com um nome de um tipo de monstro
// esta funcao procura no array in todos os monstros com o tipo recebido, colocando-os no
// array de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int pesquisa_monstros_tipo(Monstro *in[], Monstro *out[], int n, char *tipo)
{
    int res = 0;

    for (int i = 0; i < n; i++)
        if (!strcmp(in[i]->tipo, tipo))
            out[res++] = in[i];

    return res;
}

// dado um array de entrada de ponteiros de monstros in, um array de saida de ponteiros de monstros out,
// um inteiro n que corresponde ao numero de elementos de in, e dois inteiros que correspondem
// a um numero minimo e maximo do challenge rating, esta funcao procura no array in todos
// os monstros com challenge rating compreendido entre os valores minimo e maximo (inclusive),
// colocando-os no array de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int pesquisa_monstros_cr(Monstro *in[], Monstro *out[], int n, double cr_min, double cr_max)
{
    int res = 0;

    for (int i = 0; i < n; i++)
        if ((in[i]->cr >= cr_min) && (in[i]->cr <= cr_max))
            out[res++] = in[i];

    return res;
}

// Coloquem aqui a funcao de teste que usaram para testar o problema F da Semana 2.
// Ou seja, "A funcao começa por ler um inteiro n representando o numero de monstros que vao ser lidos..."
// etc etc.
void test_F_S2(void)
{
    int n = 0;
    scanf("%d", &n);

    Monstro **monstros = malloc(n * sizeof(Monstro *));

    int total = get_monstros(monstros, n);

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
}