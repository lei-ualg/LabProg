#include "festa1.h"
#include "lista.h"
#include <stdio.h>

// ---------------------------------------------------------------------------------------------- //

void test_main(void)
{
    double a[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    lista_println(array_to_lista(a, 5));
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