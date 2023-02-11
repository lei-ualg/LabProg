#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "our_ints.h"
#include "our_doubles.h"


// Programa A -----------------------------------------------------------------------------------
void testA()
{
        int n,x,m;
        int a[1000];
        int b[2];
        
        n = ints_get_until(-1,a);
        while(scanf("%d",&x) != EOF)
        {
                ...
                ints_println_special(b,m);
        }
}

// Programa B ---------------------------------------------------------------------------------
void testB()
{
}

// Programa C ----------------------------------------------------------------------------------


void testC()
{
}

// Programa D --------------------------------------------------------------------------------------------------
char *al_gharb(char *r, const char *s)
{
        int n = 0;
        for (int i = 0; s[i]; i++)
        {
                r[n++] = 48 + s[i] % 10;
                r[n++] = 48 + s[i] / 10 % 10;
        }
        r[n] = 0;
        return r;
}

void testD()
{

        
}

// Programa E ----------------------------------------------------------------------
char *linear_b(char *r, const char *s)
{
        //TODO: implement
}

void unit_test_linear_b(void)
{
        char s[1000];
        assert(strcmp(linear_b(s, "mota"), "mo-ta") == 0);
        assert(strcmp(linear_b(s, "azeite"), "a-ze-i-te") == 0);
        assert(strcmp(linear_b(s, "porta"), "po-re-ta") == 0);
        assert(strcmp(linear_b(s, "guerra"), "gu-e-re-ra") == 0);
        assert(strcmp(linear_b(s, "anzol"), "a-ne-zo-le") == 0);
        assert(strcmp(linear_b(s, "pneu"), "pe-ne-u") == 0);
        assert(strcmp(linear_b(s, "copos"), "co-po-se") == 0);
}


void testE(){

        
}


// MAIN
// Este main esta preparado para receber um argumento quando o programa e executado.
// Esse argumento, que se espera que seja um caracter
// sera usado para determinar qual das funcoes de teste (ou problema) serao executados.
// Caso nao seja passado nenhum argumento, e invocado o teste do problema A por omissao

int main(const int argc, const char* argv[])
{

        int x = 'A';
        if (argc > 1)
                x = *argv[1];

        if( x == 'A')
                testA();
        else if( x == 'B')
                testB();
        else if( x == 'C')
                testC();
        else if( x == 'D')
                testD();
        else if( x == 'E')
                testE();
        else if (x == 'U')
                printf("All unit tests PASSED.\n");

        return 0;
}
