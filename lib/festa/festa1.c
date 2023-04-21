// podem adicionar outros includes, caso necessitem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "festa1.h"

// comece por identificar o ficheiro com o seu numero e nome de aluno
// substitua nestas constantes o seu numero de aluno, e o seu primeiro e ultimo nome
const int NUMERO_ALUNO = 77738;
const char NOME_ALUNO[] = "Leonardo Albudane";

/***************************        Problema A - 5 pontos       ****************************************/
Time time(int timezone, int horas, int minutos)
{
    Time t;
    t.timezone = timezone;
    t.horas = horas;
    t.minutos = minutos;
    return t;
}

Time time_read(char *s)
{
    // PATTERN: %d<HORA>,%d<MINUTO>,%d<TIMEZONE>
    int timezone;
    char horas[3], minutos[3];
    sscanf(s, "%[^,],%[^,],%d", horas, minutos, &timezone); // [^,] = tudo o que não seja uma virgula
    return time(timezone, atoi(horas), atoi(minutos));
}

void time_println(Time t)
{
    printf("%02d:%02d UTC%s%02d\n", t.horas, t.minutos, (t.timezone < 0 ? "-" : "+"), abs(t.timezone));
}

/***************************        Problema B - 5 pontos       ****************************************/
int *array_ptr_to_last_divider(int a[], int n, int *x)
{
    for (int i = n - 1; i >= 0; i--)
        if (a[i] % *x == 0)
            return &a[i];
    return NULL;
}

/***************************        Problema C - 5 pontos       ****************************************/
int *array_junta(int a[], int n, int b[], int m)
{
    int *c = calloc(n + m, sizeof(int));

    for (int i = 0; i < n+m; i++)
    {
        if (i < n)
            c[i] = a[i];
        else
            c[i] = b[i - n];
    }    
    return c;
}

/***************************        Problema D - 5 pontos       ****************************************/
Box box(const char *v)
{
    Box b = {v};
    return b;
}

Teste *teste(int id, char *name, char *type, const char *toBox)
{
    Teste *t = calloc(1, sizeof(Teste));
    t->id = id;
    t->name = strdup(name);
    strncpy(t->type, type, 5);
    t->box = box(toBox);
    
    return t;
}

void teste_free(Teste *t)
{
    free(t->name);
    free(t);
}

/***************************        Problema E - 5 pontos       ****************************************/
void filter_string_characters(const char *s, char *s_out, CharPredicate p)
{
    int len = 0;
    for(int i = 0; i < strlen(s); i++)
    {
        if (p(s[i]))
            s_out[len++] = s[i];
        s_out[len] = '\0';
    }
}

int is_vogal(char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void apenas_vogais(const char *s, char *s_out)
{
    filter_string_characters(s, s_out, is_vogal);
}

/***************************        Problema F - 5 pontos       ****************************************/
Aluno *aluno(int numero, char *nome, char *turno)
{
    Aluno *a = calloc(1, sizeof(Aluno));
    a->numero = numero;
    a->nome = strdup(nome);
    a->turno = strdup(turno);
    a->estado_avaliacao = Reprovado;

    return a;
}

int remove_sem_frequencia(Aluno *alunos_in[], int n, Aluno *alunos_out[])
{
    int n_out = 0;
    for (int i = 0; i < n; i++)
        if (alunos_in[i]->estado_avaliacao != Sem_Frequencia)
            alunos_out[n_out++] = alunos_in[i];

    return n_out;
}

int cmp_aluno(const void *a, const void *b)
{
    Aluno *aluno_a = *(Aluno **)a;
    Aluno *aluno_b = *(Aluno **)b;

    if (strcmp(aluno_a->turno, aluno_b->turno))
        return strcmp(aluno_a->turno, aluno_b->turno);
    else
        return aluno_a->numero - aluno_b->numero;
}

void ordena_turno_numero(Aluno *alunos[], int n)
{
    qsort(alunos, n, sizeof(Aluno *), cmp_aluno);
}

int remove_e_ordena(Aluno *alunos_in[], int n, Aluno *alunos_out[])
{
    int n_out = remove_sem_frequencia(alunos_in, n, alunos_out);
    ordena_turno_numero(alunos_out, n_out);
    return n_out;
}

/***************************        Problema G - 5 pontos       ****************************************/
Lista *array_to_lista(double a[], int n)
{
    Lista *l = lista();
    for (int i = n-1; i >= 0; i--)
        l = lista_insere(l, a[i]);
    return l;
}

/***************************        Problema H - 5 pontos       ****************************************/
int strings_iguais_recursivo(char *s1, char *s2)
{
    if (*s1 == '\0' && *s2 == '\0')
        return 1;
    else if (*s1 == '\0' || *s2 == '\0')
        return 0;
    else if (*s1 == *s2)
        return strings_iguais_recursivo(s1 + 1, s2 + 1);
    else
        return 0;
}

/***************************        Problema I - 10 pontos       ****************************************/
int get_lines(FILE *f, char ***lines)
{
    int n_lines = 0;
    char c = fgetc(f);
    *lines = calloc(1, sizeof(char *));
    (*lines)[0] = calloc(1, sizeof(char));
    (*lines)[0][0] = '\0';
    while (c != EOF)
    {
        if (c == '\n')
        {
            if (n_lines != 0)
            {
                int len = strlen((*lines)[n_lines]);
                (*lines)[n_lines] = realloc((*lines)[n_lines], (len + 2) * sizeof(char));
                (*lines)[n_lines][len] = c;
                (*lines)[n_lines][len + 1] = '\0';
            }
            n_lines++;
            *lines = realloc(*lines, (n_lines + 1) * sizeof(char *));
            (*lines)[n_lines] = calloc(1, sizeof(char));
        }
        else
        {
            int len = strlen((*lines)[n_lines]);
            (*lines)[n_lines] = realloc((*lines)[n_lines], (len + 2) * sizeof(char));
            (*lines)[n_lines][len] = c;
            (*lines)[n_lines][len + 1] = '\0';
        }
        c = fgetc(f);
    }

    int len = strlen((*lines)[n_lines]);
    if ((*lines)[n_lines][len] != '\n' && n_lines != 0)
    {
        (*lines)[n_lines] = realloc((*lines)[n_lines], (len + 2) * sizeof(char));
        (*lines)[n_lines][len] = '\n';
        (*lines)[n_lines][len + 1] = '\0';
    }
    n_lines++;
    return n_lines;
}

void reverse_file(const char *input_filename, const char *output_filename)
{
    FILE *f_in = fopen(input_filename, "r");
    FILE *f_out = fopen(output_filename, "w");

    char **lines = NULL;
    int n_lines = get_lines(f_in, &lines);
    for (int i = n_lines - 1; i >= 0; i--)
        fprintf(f_out, "%s", lines[i]);

    for (int i = 0; i < n_lines; i++)
        free(lines[i]);
    fclose(f_in);
    fclose(f_out);
}

/***************************        Main - para testes locais      ****************************************/
// #ifndef MOOSHAK_MAIN
// // podem ter aqui uma função de main se o desejarem para fazerem testes locais no vosso computador
// // tudo o que estiver aqui definido não será compilado quando submetido ao Mooshak
// int main(void)
// {
// #endif