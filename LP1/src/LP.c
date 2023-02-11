#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "our_ints.h"
#include "our_doubles.h"

const char *author = "Leonardo Marinho Albudane";

// Programa F ----------------------------------------------------------------------------------- //
double avg_km(double *data, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i += 4)
        sum += data[i];
    return sum / (n / 4);
}

double avg_km_hora_titulares(double *data, int n)
{
    double km_h = 0;
    int j = 0;
    for (int i = 0; i < n; i += 4)
        if (data[i + 1] >= 50)
        {
            km_h += data[i] / (data[i + 1] / 60);
            j++;
        }
    return km_h / j;
}

double avg_km_hora_substitutos(double *data, int n)
{
    double km_h = 0;
    int j = 0;
    for (int i = 0; i < n; i += 4)
        if (data[i + 1] < 50)
        {
            km_h += data[i] / (data[i + 1] / 60);
            j++;
        }
    return km_h / j;
}

double total_weight(double *data, int n)
{
    double sum_inicio = 0, sum_fim = 0;
    for (int i = 0; i < n; i += 4)
        sum_inicio += data[i + 2], sum_fim += data[i + 3];
    return sum_inicio - sum_fim;
}

void testF(void)
{
    double data[1000] = {};
    int n = doubles_get(data);
    printf("%.2f %.2f %.2f %.2f\n", avg_km(data, n), avg_km_hora_titulares(data, n), avg_km_hora_substitutos(data, n), total_weight(data, n));
}

// Programa G ----------------------------------------------------------------------------------- //

// Programa H ----------------------------------------------------------------------------------- //

void password(char *str, char *out)
{
    out[0] = '\0';
    for (int i = 0, c = 0, w = 1; str[i] != '\0'; i++, c++)
    {
        if ((str[i + 1] == '_' || str[i + 1] == '\0') && (w % 2))
            sprintf(out + strlen(out), "%c%d", str[i], c + 1);
        if (str[i] == '_')
            c = -1, w++;
    }
}

void testH(void)
{
    char string[1000] = {}, output[1000] = {};
    while (scanf("%s", string) != EOF)
        password(string, output), printf("%s\n", output);
}

// Unit Test ------------------------------------------------------------------------------------ //

void unit_tests()
{
    char output[1000] = {};
    password("All_in_all_it's_just_another_brick_in_the_wall", output);
    assert(!strcmp(output, "l3l3t4k5e3"));
    password("agua_mole_em_pedra_dura", output);
    assert(!strcmp(output, "a4m2a4"));
    password("aaa_bbbbb", output);
    assert(!strcmp(output, "a3"));
}

// Main ----------------------------------------------------------------------------------------- //

int main(int argc, char **argv)
{
    unit_tests();
    int x = 'F';
    if (argc > 1)
        x = *argv[1];

    switch (x)
    {
    case 'F':
        testF();
        break;
    case 'G':
        // testG();
        break;
    case 'H':
        testH();
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