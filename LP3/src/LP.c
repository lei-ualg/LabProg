#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "monstro.h"
#include "jogador.h"

const char *author = "Leonardo Marinho Albudane";

// Programa F ----------------------------------------------------------------------------------- //

// void testF()
// {
    
// }
// Programa G ----------------------------------------------------------------------------------- //

void testG()
{
   
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
        test_F_S2();
        break;
    case 'G':
        test_G_S2();
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