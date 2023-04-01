// include --------------------------------------------------------------------------------------- //
#include "submission.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

const char *authors[] = {"Leonardo Marinho Albudane", "Bárbara Arsénio Pereira"};

//! typedef --------------------------------------------------------------------------------------- //

typedef enum E_Result // criar um tipo enumerado chamado result
{
    Accepted,            // 0
    PresentationError,   // 1
    WrongAnswer,         // 2
    OutputLimitExceeded, // ...
    MemoryLimitExceeded,
    TimeLimitExceeded,
    InvalidFunction,
    RuntimeError,
    CompileTimeError,
    InvalidSubmission,
    ProgramSizeExceeded,
    RequiresReevaluation,
    Evaluating
} Result;

typedef enum E_Status // criar um tipo enumerado chamado Status
{
    pending,
    final
} Status;

typedef enum E_Sort // criar um tipo enumerado chamado sort com as funçoes
{
    number_ascending, // 0
    number_descending,
    id,
    problem,
} Sort;

typedef struct S_Date // criar um tipo da estrutura chamada Date composta por int para cada
{
    int day;
    int month;
    int year;

    int hour;
    int minute;
} Date;

typedef struct S_Submission // criar um tipo da estrutura chamada Submission composta por int para id e pontos, string para o resto, e os enums anteriores
{
    int number;
    Date *time;
    int points;
    char *group;
    char *id;
    char *team;
    char *problem;
    char *language;
    Result result;
    Status status;
} Submission;

typedef struct S_Stats // tipo da estrutura chamada Stats para guardar as estatisticas do problema 2, string para o problemas e int para o total de cada
{
    char *problem;
    int total_submissions;
    int accepted_submissions;
    int presentation_error_submissions;
    int wrong_answer_submissions;
    int memory_limit_exceeded_submissions;
    int time_limit_exceeded_submissions;
    int runtime_error_submissions;
    int compile_time_error_submissions;
    int other_error_submissions;
} Stats;

typedef struct S_Problem
{
    char *id;
    int total_tries;
    int total_points;
} Problem;

typedef struct S_Rank // tipo da estrutura chamada rank para guardar as estatisticas do problema 5
{
    char *id;
    char *group;
    char *team;
    int total_points;
    int total_submissions;
    Problem **problems;
    int total_problems;
} Rank;

typedef int (*Comparer)(const void *, const void *);

//! global variables ------------------------------------------------------------------------------ //

const char *RESULTS[] = { // Strings para mais tarde converter de enum para string
    "Accepted", "Presentation Error", "Wrong Answer", "Output Limit Exceeded", "Memory Limit Exceeded", "Time Limit Exceeded", "Invalid Function", "Runtime Error", "Compile Time Error", "Invalid Submission", "Program Size Exceeded", "Requires Reevaluation", "Evaluating"};

const char *STATUS[] = {
    "pending", "final"};

const char *SORT[] = {
    "number_ascending", "number_descending", "id", "problem"};

//! constructors ---------------------------------------------------------------------------------- //

Date *c_time(char *time) // estrutura
{
    // YYYY/MM/DD HH:mm
    int year, month, day, hour, minute;
    sscanf(time, "%d/%d/%d %d:%d", &year, &month, &day, &hour, &minute); // ler a string da data (time)
    Date *d = malloc(sizeof(Date));                                      // guardar na heap manualmente
    d->day = day;                                                        // atribuir as informaçoes lidas à estrutura
    d->month = month;                                                    // usamos a setinha porque o d é um ponteiro, se d nao fosse um ponteiro usamos um .
    d->year = year;
    d->hour = hour;
    d->minute = minute;
    return d; // da return do ponteiro / endereço
}

Submission *c_submission(int number, char *time, int points, char *group, char *id, char *team, char *problem, char *language, Result result, Status status)
{                                               // estrutura
    Submission *s = malloc(sizeof(Submission)); // gardar na heap

    s->number = number; // atribur as informaçoes lidas à estrutura
    s->time = c_time(time);
    s->points = points;
    s->group = strdup(group); // copiar a string para a heap e da o endereço para o ponteiro
    s->id = strdup(id);
    s->team = strdup(team);
    s->problem = strdup(problem);
    s->language = strdup(language);
    s->result = result;
    s->status = status;
    return s;
}

Stats *c_stats(char *problem) // estrutura
{
    Stats *s = calloc(1, sizeof(Stats)); // guarda na heap, limpa os valores e o 1 é pq só é 1 ponteiro
    s->problem = strdup(problem);
    return s;
}

Rank *c_rank(char *id, char *group, char *team) // estrutura
{
    Rank *r = calloc(1, sizeof(Rank)); // guarda na heap
    r->id = strdup(id);
    r->group = strdup(group);
    r->team = strdup(team);
    r->total_points = 0;
    r->total_submissions = 0;
    return r;
}

Problem **c_problems(char **problems, int n) // estrutura
{
    Problem **p = calloc(n, sizeof(Problem *)); // guarda na heap
    for (int i = 0; i < n; i++)
    {
        p[i] = calloc(1,sizeof(Problem)); // guarda na heap
        p[i]->id = problems[i];       // não é preciso usar strdup pq a string ja esta na heap
        p[i]->total_tries = 0;
        p[i]->total_points = 0;
    }
    return p;
}

//! free ------------------------------------------------------------------------------------------ //

void free_submission(Submission *s) // libertar o ponteiro e cada um dos campos da estrutura que estao na heap, 1ºcampos, depois ponteiro
{
    free(s->time);
    free(s->group);
    free(s->id);
    free(s->team);
    free(s->problem);
    free(s->language);
    free(s);
}

void free_stats(Stats *s) // mesma coisa
{
    free(s->problem);
    free(s);
}

void free_problem(Problem *p) // mesma coisa
{
    free(p->id);
    free(p);
}

void free_rank(Rank *r) // mesma coisa
{
    free(r->id);
    free(r->group);
    free(r->team);
    free(r->problems);
    free(r);
}


void free_all(Submission **submissions, int n) // libertar as submissoes na heap
{
    for (int i = 0; i < n; i++)
        free_submission(submissions[i]);
    free(submissions);
}

void free_ranks(Rank **ranks, int n) // libertar as estatisticas na heap
{
    for (int i = 0; i < n; i++)
        free_rank(ranks[i]);
    free(ranks);
}

//! converters ------------------------------------------------------------------------------------------ //

Result c_result(char *result) // funçao tipo result, conversor para enum os resultados
{
    for (Result i = Accepted; i <= Evaluating; i++) // vai de accepted (0) a evaluating (ultimo)
        if (!strcmp(result, RESULTS[i]))            // vai comparar o enum com a string, se for igual é 0, se for diferente é 1. com ! inverte, se igual é 1
            return i;                               // se for igual retorna o i que é o enum
    return -1;                                      // 0 seria o accepted, então se for -1 é pq nao encontrou e vai dar erro
}

Status c_status(char *status) // funçao tipo status, conversor para enum os pending ou final
{
    for (Status i = pending; i <= final; i++)
        if (!strcmp(status, STATUS[i]))
            return i;
    return -1;
}

Sort c_sort(char *sort) // funçao tipo sort, conversor para enum os tipos de ordenaçao
{
    for (Sort i = number_ascending; i <= problem; i++)
        if (!strcmp(sort, SORT[i]))
            return i;
    return -1;
}

const char *s_result(Result result) // converte de enum para string
{
    return RESULTS[result]; // retorna a string do enum, ele vai buscar a string ao array de strings, pois a posição do array é o enum
}

const char *s_status(Status status) // converte de enum para string
{
    return STATUS[status];
}


char *s_time(Date *time) // converte de struct para string
{
    char *s = malloc(16 * sizeof(char));                                                                // 16 pq é o tamanho da string
    sprintf(s, "%d/%02d/%02d %02d:%02d", time->year, time->month, time->day, time->hour, time->minute); // guarda na string s a data
    return s;
}

//! functions ------------------------------------------------------------------------------------- //

// filters --------------------------------------------------------------------------------------- //

int filter_by_result(Submission *s, Result result) // damos uma linha e um result (accepted por ex) e verifica se é igual
{
    return s->result == result;
}

int filter_by_problem(Submission *s, char *problem) // mesma coisa mas string para a letra do problema
{
    return !strcmp(s->problem, problem); // inverte pq strcmp devolve o contrario, queremos 1 para iguais
}

// filters and counters -------------------------------------------------------------------------- //

int filter_submissions_by_result(Submission **submissions_in, int n, Submission **submissions_out, Result result) // 1* ponteiro, 2* array de ponteiros
{
    int n_filtered = 0; // é necessario colocar =0 pois se nao o n_filtered vai ter o valor que ja havia na memoria
    for (int i = 0; i < n; i++)
        if (filter_by_result(submissions_in[i], result))       // se a funçao de cima retorna vdd passa a submissao do in para o out
            submissions_out[n_filtered++] = submissions_in[i]; // n_filtered++ é para aumentar o tamanho do array out
    return n_filtered;
}

int filter_submissions_by_problem(Submission **submissions_in, int n, Submission **submissions_out, char *problem)
{
    int n_filtered = 0;
    for (int i = 0; i < n; i++)
        if (filter_by_problem(submissions_in[i], problem)) // se a funçao retorna vdd (mesmo problema) passa as submissoes do in para o out
            submissions_out[n_filtered++] = submissions_in[i];
    return n_filtered;
}

int count_submissions_by_result(Submission **submissions, int n, Result result)
{
    int n_filtered = 0;
    for (int i = 0; i < n; i++)
        if (filter_by_result(submissions[i], result)) // faz a mesma coisa, só que ao invés de passar para o out, conta a quantidade de submissoes iguais ao result
            n_filtered++;
    return n_filtered;
}

int count_submissions_by_problem(Submission **submissions, int n, char *problem)
{
    int n_filtered = 0;
    for (int i = 0; i < n; i++)
        if (filter_by_problem(submissions[i], problem)) // faz a mesma coisa, só que ao invés de passar para o out, conta a quantidade de submissoes com o mesmo problema
            n_filtered++;
    return n_filtered;
}

int count_problems(Submission **submissions, int n, char ***problems_out)
{
    int n_problems = 0;
    *problems_out = calloc(1, sizeof(char *));
    (*problems_out)[n_problems] = strdup(submissions[0]->problem);
    n_problems++;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < n_problems; j++)
            if (!strcmp(submissions[i]->problem, (*problems_out)[j]))
                break;
            else if (j == n_problems - 1)
            {
                *problems_out = realloc(*problems_out, (n_problems + 1) * sizeof(char *));
                (*problems_out)[n_problems] = strdup(submissions[i]->problem);
                n_problems++;
                break;
            }
    return n_problems;
}

// Utils ----------------------------------------------------------------------------------------- //

int find_submission(Submission **submissions, int n, int number)
{
    for (int i = 0; i < n; i++)
        if (submissions[i]->number == number)
            return i;
    return -1;
}


void add_try_points(Rank *rank, Submission *submission)
{
    for (int i = 0; i < rank->total_problems; i++)
        if (!strcmp(rank->problems[i]->id, submission->problem))
        {
            rank->problems[i]->total_tries++;
            if(submission->points > rank->problems[i]->total_points)
                rank->problems[i]->total_points = submission->points;
            break;
        }
}

// Comparators ----------------------------------------------------------------------------------- //

int compare_by_number_asc(Submission **a, Submission **b)
{
    return (*a)->number - (*b)->number; // compara os numbers(numeros)
}

int compare_by_number_desc(Submission **a, Submission **b)
{
    return (*b)->number - (*a)->number; // compara os numbers
}

int compare_by_id(Submission **a, Submission **b)
{
    return strcmp((*a)->id, (*b)->id) ? strcmp((*a)->id, (*b)->id) : compare_by_number_desc(a,b); // se os ids(nomes) forem iguais compara os submission ids, organizaçao
}

int compare_by_problem(Submission **a, Submission **b)
{
    return strcmp((*a)->problem, (*b)->problem) ? strcmp((*a)->problem, (*b)->problem) : compare_by_number_desc(a,b); // se os problemas forem iguais compara os submission ids, organizaçao
}

int compare_alphabetically(char **a, char **b)
{
    return strcmp((*a), (*b));
}

int make_ranks_comparer(Rank **a, Rank **b)
{
    // 1 - total_points (decrescente)
    // 2 - total_submissions (crescente)
    // 3 - id (crescente)

    if ((*a)->total_points == (*b)->total_points)
        if ((*a)->total_submissions == (*b)->total_submissions)
            return strcmp((*a)->id, (*b)->id);
        else
            return (*a)->total_submissions < (*b)->total_submissions ? -1 : 1;
    else
        return (*a)->total_points > (*b)->total_points ? -1 : 1;
}

// Sorters --------------------------------------------------------------------------------------- //

void sort_submissions(Submission **submissions, int n, char *criteria)
{ // array de ponteiros de funçoes, 2 submissoes A e B
    int (*comparadores[4])(Submission **, Submission **) = {compare_by_number_asc, compare_by_number_desc, compare_by_id, compare_by_problem};
    qsort(submissions, n, sizeof(Submission *), (Comparer)comparadores[c_sort(criteria)]);
} // qsort ordena as submissoes por id, ----------> recebe dois void e troca para submission usando o typedef de cima, casting

// Printers -------------------------------------------------------------------------------------- //
void print_submission_simple(Submission *s) // para uma linha
{                                           // da print de tudo reparado por virgulas, s é o ponteiro, depois vao buscar ao time o ano, mes, dia.... result e status tem que passar pela funçao para virar string
    printf("%d,%s,%d,%s,%s,%s,%s\n", s->number, s_time(s->time), s->points, s->id, s->problem, s_result(s->result), s_status(s->status));
}

void muliple_print_simple(Submission **submissions, int n) // tipo loop para todas as linhas
{
    for (int i = 0; i < n; i++)
        print_submission_simple(submissions[i]);
}

void print_submission_stats(Stats *s)
{
    printf // print das estatisticas
        (
            "Problem: %s\n"
            "Total Submissions: %d\n"
            "Accepted: %d\n"
            "Presentation Error: %d\n"
            "Wrong Answer: %d\n"
            "Memory Limit Exceeded: %d\n"
            "Time Limit Exceeded: %d\n"
            "Run Time Error: %d\n"
            "Compile Time Error: %d\n"
            "Other Errors: %d\n",
            s->problem, s->total_submissions,
            s->accepted_submissions, s->presentation_error_submissions,
            s->wrong_answer_submissions, s->memory_limit_exceeded_submissions,
            s->time_limit_exceeded_submissions, s->runtime_error_submissions,
            s->compile_time_error_submissions, s->other_error_submissions);
}

void print_ranks(Rank **ranks, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%s %s\t", i + 1, ranks[i]->group, ranks[i]->team);
        for (int j = 0; j < ranks[i]->total_problems; j++)
            printf("%s:%d(%d)\t", ranks[i]->problems[j]->id, ranks[i]->problems[j]->total_points, ranks[i]->problems[j]->total_tries);
        printf("Total:%d\n", ranks[i]->total_points);
    }
}

// Main ------------------------------------------------------------------------------------------ //

int read_submissions(FILE *f, Submission ***submissions)
{
    while (fgetc(f) != '\n'); // le a primeira linha caractere a caractere para ser ignorada

    int n = 0;
    int number, points;
    char time[100], group[101], id[101], team[101], problem[101], language[101], result[101], status[101];

    *submissions = calloc(1, sizeof(Submission *));

    while (fscanf(f, "%d\t%[^\t\n]\t%d\t%s\t%s\t%[^\t\n]\t%s\t%s\t%[^\t\n]\t%s\n", &number, time, &points, group, id, team, problem, language, result, status) != EOF)
    {
        if (n)
            *submissions = realloc(*submissions, (n+1) * sizeof(Submission *));
        (*submissions)[n++] = c_submission(number, time, points, group, id, team, problem, language, c_result(result), c_status(status));
    }

    return n;
}

int get_ranks(Submission **submissions, int n, Rank ***ranks, char **problems, int n_problems)
{
    int n_ranks = 0;
    *ranks = calloc(1, sizeof(Rank *));
    (*ranks)[n_ranks] = c_rank(submissions[0]->id, submissions[0]->group, submissions[0]->team);
    (*ranks)[n_ranks]->problems = c_problems(problems, n_problems);
    (*ranks)[n_ranks]->total_problems = n_problems;
    add_try_points((*ranks)[n_ranks], submissions[0]);
    (*ranks)[n_ranks]->total_submissions++;
    n_ranks++;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < n_ranks; j++)
        {
            if (!strcmp(submissions[i]->id, (*ranks)[j]->id))
            {
                (*ranks)[j]->total_submissions++;
                add_try_points((*ranks)[j], submissions[i]);
                break;
            }
            else if (j == n_ranks - 1) // se nao for igual a ninguem
            {
                *ranks = realloc(*ranks, (n_ranks + 1) * sizeof(Rank *));
                (*ranks)[n_ranks] = c_rank(submissions[i]->id, submissions[i]->group, submissions[i]->team);
                (*ranks)[n_ranks]->problems = c_problems(problems, n_problems);
                (*ranks)[n_ranks]->total_problems = n_problems;
                add_try_points((*ranks)[n_ranks], submissions[i]);
                (*ranks)[n_ranks]->total_submissions++;
                n_ranks++;
                break;
            }
        }

    for (int i = 0; i < n_ranks; i++)
    {
        for (int j = 0; j < (*ranks)[i]->total_problems; j++)
        {
            (*ranks)[i]->total_points += (*ranks)[i]->problems[j]->total_points;
        }
    }
    return n_ranks;
}

// tests ----------------------------------------------------------------------------------------- //
// exemplo_submissoes.tsv
void teste_leitura_simples(void)
{
    char filename[100];
    scanf("%s", filename);
    FILE *f = fopen(filename, "r");
    Submission **submissions = NULL;
    int n = read_submissions(f, &submissions);
    Submission **submissions_out = calloc(n, sizeof(Submission *));
    int out_size = filter_submissions_by_result(submissions, n, submissions_out, Accepted);
    muliple_print_simple(submissions_out, out_size);
    free_all(submissions, n);
    free(submissions_out);
    fclose(f);
}

void teste_estatisticas(void)
{
    char filename[100];
    scanf("%s", filename);
    FILE *f = fopen(filename, "r");
    Submission **submissions = NULL;
    int n = read_submissions(f, &submissions);
    Submission **submissions_out = calloc(n, sizeof(Submission *));
    char problem[101], command[100];
    while (scanf("%s", command) != EOF)
    {
        if (!strcmp(command, "STATS"))
        {
            scanf("%s", problem);
            int out_size = filter_submissions_by_problem(submissions, n, submissions_out, problem);
            Stats *s = c_stats(problem);
            s->total_submissions = out_size;
            s->accepted_submissions = count_submissions_by_result(submissions_out, out_size, Accepted);
            s->presentation_error_submissions = count_submissions_by_result(submissions_out, out_size, PresentationError);
            s->wrong_answer_submissions = count_submissions_by_result(submissions_out, out_size, WrongAnswer);
            s->memory_limit_exceeded_submissions = count_submissions_by_result(submissions_out, out_size, MemoryLimitExceeded);
            s->time_limit_exceeded_submissions = count_submissions_by_result(submissions_out, out_size, TimeLimitExceeded);
            s->runtime_error_submissions = count_submissions_by_result(submissions_out, out_size, RuntimeError);
            s->compile_time_error_submissions = count_submissions_by_result(submissions_out, out_size, CompileTimeError);
            s->other_error_submissions = out_size - (s->accepted_submissions + s->presentation_error_submissions + s->wrong_answer_submissions + s->memory_limit_exceeded_submissions + s->time_limit_exceeded_submissions + s->runtime_error_submissions + s->compile_time_error_submissions);
            print_submission_stats(s);
            free_stats(s);
        }
    }

    free_all(submissions, n);
    free(submissions_out);
    fclose(f);
}

void teste_atualizacao(void)
{
    char filename[100];
    scanf("%s", filename);
    FILE *f = fopen(filename, "r+");
    Submission **submissions = NULL;
    int n = read_submissions(f, &submissions);
    char command[100];
    int number, points;
    while (scanf("%s", command) != EOF)
    {
        if (!strcmp(command, "UPDATE"))
        {
            scanf("%d", &number);
            int index = find_submission(submissions, n, number);
            if (index >= 0)
            {
                scanf("%d", &points);
                submissions[index]->points = points;
                submissions[index]->status = final;
                submissions[index]->result = Accepted;

                print_submission_simple(submissions[index]);
            }
            else
            {
                printf("Invalid Submission!\n");
            }
        }
    }
    fseek(f, 0, SEEK_SET);
    while (fgetc(f) != '\n');
    fseek(f, ftell(f), SEEK_SET);

    for (int i = 0; i < n; i++)
        fprintf(f, "%d\t%s\t%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", submissions[i]->number, s_time(submissions[i]->time), submissions[i]->points, submissions[i]->group, submissions[i]->id, submissions[i]->team, submissions[i]->problem, submissions[i]->language, s_result(submissions[i]->result), s_status(submissions[i]->status));

    fflush(f);
    ftruncate(fileno(f), ftell(f));
    
    free_all(submissions, n);
    fclose(f);
}

void teste_ordenacao(void)
{
    char filename[100];
    scanf("%s", filename);
    FILE *f = fopen(filename, "r");
    Submission **submissions = NULL;
    int n = read_submissions(f, &submissions);
    char command[100], arg[100];
    while (scanf("%s%s", command, arg) != EOF)
    {
        if (!strcmp(command, "ORDER"))
            sort_submissions(submissions, n, arg);
        else if (!strcmp(command, "PRINT"))
        {
            if (!strcmp(arg, "*"))
                muliple_print_simple(submissions, n);
            else
            {
                int q = atoi(arg);
                muliple_print_simple(submissions, q);
            }
        }
    }
    free_all(submissions, n);
    fclose(f);
}

void teste_ranking(void)
{
    char filename[100];
    scanf("%s", filename);
    FILE *f = fopen(filename, "r");

    Submission **submissions = NULL;
    int n = read_submissions(f, &submissions);

    char **problems = NULL;
    int n_problems = count_problems(submissions, n, &problems);
    qsort(problems, n_problems, sizeof(char *), (Comparer)compare_alphabetically);

    Rank **ranks = NULL;
    int n_ranks = get_ranks(submissions, n, &ranks, problems, n_problems);
    qsort(ranks, n_ranks, sizeof(Rank *), (Comparer)make_ranks_comparer);

    print_ranks(ranks, n_ranks > 15 ? 15 : n_ranks);

    free_ranks(ranks, n_ranks);
    free_all(submissions, n);
    for (int i = 0; i < n_problems; i++)
        free(problems[i]);
    fclose(f);
}