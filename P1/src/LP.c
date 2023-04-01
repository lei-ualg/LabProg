#include "submission.h"
#include <stdio.h>

// ---------------------------------------------------------------------------------------------- //

void test_main(void)
{
    teste_leitura_simples();
    teste_estatisticas();
    teste_atualizacao();
    teste_ordenacao();
    teste_ranking();
}
// Main ----------------------------------------------------------------------------------------- //

int main(int argc, char **argv)
{
    int x = 'A';
    if (argc > 1)
        x = *argv[1];

    switch (x)
    {
    case 'A':
        teste_leitura_simples();
        break;
    case 'B':
        teste_estatisticas();
        teste_estatisticas();
        break;
    case 'C':
        teste_atualizacao();
        break;
    case 'D':
        teste_ordenacao();
        break;
    case 'E':
        teste_ranking();
        break;
    case 'X':
        test_main();
        break;
    default:
        printf("%s: Invalid option.\n", argv[1]);
        break;
    }
    return 0;
}