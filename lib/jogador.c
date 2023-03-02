// este operador serve para dizer ao compilador de C, que este ficheiro header so deve ser processado
// se ainda nao sido processado anteriormente
// le-se "se ainda nao tiver sido definido JOGADOR_H, define JOGADOR_H".
// Se o teste falhar (i.e. o JOGADOR_H ja foi definido), o compilador salta para o #endif e tudo o que esta
// dentro do #if e ignorado

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogador.h"

const char *POSITIONS[] = {"Guarda-redes", "Defesa", "Medio", "Avancado"};
// Dada uma string, retorna a posicao (valor enumerado) correspondente a string recebida
Posicao string_to_posicao(char *s)
{
    for (Posicao i = GR; i <= Avancado; i++)
        if (!strcmp(s, POSITIONS[i]))
            return i;
    return -1;
}

// Dada uma posicao, retorna uma String que descreve a posição
const char *posicao_to_string(Posicao p)
{
    return POSITIONS[p];
}

// Construtor do tipo Jogador, recebe os membros, e cria um novo jogador, e inicializa-o. Devolve
// um ponteiro para o jogador criado
Jogador *jogador(char *primeiro_nome, char *ultimo_nome, int ano, Posicao p, int inter, int golos, char *clube)
{
    Jogador *j = malloc(sizeof(Jogador));

    j->primeiro_nome = malloc(strlen(primeiro_nome) + 1);
    strcpy(j->primeiro_nome, primeiro_nome);
    j->ultimo_nome = malloc(strlen(ultimo_nome) + 1);
    strcpy(j->ultimo_nome, ultimo_nome);
    j->clube = malloc(strlen(clube) + 1);
    strcpy(j->clube, clube);

    j->ano = ano;
    j->pos = p;
    j->internacionalizacoes = inter;
    j->golos = golos;

    return j;
}

// Recebe um ponteiro para um jogador, e liberta a memória usada pelo tipo
void free_jogador(Jogador *j)
{
    free(j->primeiro_nome);
    free(j->ultimo_nome);
    free(j->clube);
    free(j);
}

// Recebe um ponteiro para um jogador, e cria uma copia (ou clone) profunda do jogador. Devolve um
// ponteiro para o jogador criado
Jogador *jogador_dup(Jogador *j)
{
    Jogador *clone = malloc(sizeof(Jogador));

    clone->primeiro_nome = malloc(strlen(j->primeiro_nome) + 1);
    strcpy(clone->primeiro_nome, j->primeiro_nome);
    clone->ultimo_nome = malloc(strlen(j->ultimo_nome) + 1);
    strcpy(clone->ultimo_nome, j->ultimo_nome);
    clone->clube = malloc(strlen(j->clube) + 1);
    strcpy(clone->clube, j->clube);

    clone->ano = j->ano;
    clone->pos = j->pos;
    clone->internacionalizacoes = j->internacionalizacoes;
    clone->golos = j->golos;

    return clone;
}

// Recebe um ponteiro para um jogador, e o numero de golos marcados num jogo, e adiciona um jogo (internacionalizacao) ao
// jogador, e atualiza o numero de golos marcados pelo jogador
void adiciona_internacionalizacao(Jogador *j, int golos)
{
    j->internacionalizacoes++;
    j->golos += golos;
}

// Imprime um jogador para o standard output, usando o formato:
//[<Primeiro Nome>][<Ultimo Nome>][<Ano>][<Posição>][<Internacionalizações>][Golos][Clube Atual]\n
// Exemplo:
//[Cristiano][Ronaldo][1985][Avancado][196][118][Al_Nassr]
void println_jogador(Jogador *j)
{
    printf("[%s][%s][%d][%s][%d][%d][%s]\n", j->primeiro_nome, j->ultimo_nome, j->ano, posicao_to_string(j->pos), j->internacionalizacoes, j->golos, j->clube);
}

// Recebe um array de ponteiros para jogadores, e o numero de elementos no array n, e imprime
// todos os jogadores, pela ordem em que aparecem no array. Caso nao existam elementos no array
// imprime "*\n"
void println_jogadores(Jogador *jogadores[], int n)
{
    if (!n)
        printf("*\n");
    else
    {
        for (int i = 0; i < n; i++)
            println_jogador(jogadores[i]);
    }
}

// Dado um array de ponteiros para jogadores, e um numero n de jogadores a ler, le do standard input os n jogadores.
// cada jogador deve ser lido numa unica linha, com todos os membros separados por espaco, pela seguinte ordem
//<Primeiro Nome> <Ultimo Nome> <Ano Nascimento> <Posicao> <Internacionalizacoes> <Golos> <Clube Atual>
// Os membros que correspondem a cadeias de caracteres (strings) nao excederao os 100 caracteres cada.
// O metodo retorna o numero de jogadores efetivamente lidos.
int get_jogadores(Jogador *jogadores[], int n)
{
    int res = 0;
    char nome[100] = {}, apelido[100] = {}, posicao[100] = {}, clube[100] = {};
    int ano_nascimento = 0, internacionalizacoes = 0, golos = 0;

    while ((res < n) && (scanf("%s %s %d %s %d %d %s", nome, apelido, &ano_nascimento, posicao, &internacionalizacoes, &golos, clube) != EOF))
        jogadores[res++] = jogador(nome, apelido, ano_nascimento, string_to_posicao(posicao), internacionalizacoes, golos, clube);

    return res;
}

// Dado um array de ponteiros para jogadores, um numero n de jogadores, uma string com o primeiro nome,
// e uma string com o ultimo nome, este metodo procura no array jogadores pelo primeiro jogador
// que tenha o primeiro e ultimo nome iguais aos nomes recebidos, e retorna o ponteiro para esse jogador.
// Caso nao exista tal jogador, retorna-se o ponteiro NULL
Jogador *pesquisa_jogador(Jogador *jogadores[], int n, char *primeiro_nome, char *ultimo_nome)
{
    for (int i = 0; i < n; i++)
        if (!strcmp(jogadores[i]->primeiro_nome, primeiro_nome) && !strcmp(jogadores[i]->ultimo_nome, ultimo_nome))
            return jogadores[i];

    return NULL;
}

// Dado um array de ponteiros para jogadores, um numero n de jogadores nesse array, retorna o jogador
// com maior numero de golos marcados. Caso nao exista nenhum jogador, retorna-se NULL
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

// dado um array de entrada de ponteiros de jogadores in, e um array de saida de ponteiros de jogadores out,
// um inteiro n que corresponde ao numero de elementos de in, e uma string com um nome de um clube
// esta funcao procura no array in todos os jogadores que pertencam ao clube recebido, colocando-os no
// array de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int pesquisa_jogadores_clube(Jogador *in[], Jogador *out[], int n, char *clube)
{
    int res = 0;

    for (int i = 0; i < n; i++)
        if (!strcmp(in[i]->clube, clube))
            out[res++] = in[i];

    return res;
}

// dado um array de entrada de ponteiros de jogadores in, um array de saida de ponteiros de jogadores out,
// um inteiro n que corresponde ao numero de elementos de in, e dois inteiros que correspondem
// a um numero minimo e maximo de internacionalizacoes, esta funcao procura no array in todos
// os jogadores com numero de internacionalizacoes compreendido entre os valores minimo e maximo (inclusive),
// colocando-os no array de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int pesquisa_jogadores_inter(Jogador *in[], Jogador *out[], int n, int min_inter, int max_inter)
{
    int res = 0;

    for (int i = 0; i < n; i++)
        if ((in[i]->internacionalizacoes >= min_inter) && (in[i]->internacionalizacoes <= max_inter))
            out[res++] = in[i];

    return res;
}

// Coloquem aqui a funcao de teste que usaram para testar o problema G da Semana 2.
// Ou seja, "A funcao começa por ler um inteiro n representando o numero de jogadores que vao ser lidos..."
// etc etc.
void test_G_S2(void)
{
    int n = 0;
    scanf("%d", &n);

    Jogador **jogadores = malloc(n * sizeof(Jogador *));

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
}