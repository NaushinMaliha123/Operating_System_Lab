#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int a = 20, b = 5;

    pid_t child1, child2;

    child1 = fork();

    if (child1 == 0)
    {
        printf("Child 1 Process\n");

        printf("Addition = %d\n", a + b);
        printf("Subtraction = %d\n", a - b);
        printf("Multiplication = %d\n", a * b);

        return 0;
    }

    child2 = fork();

    if (child2 == 0)
    {
        printf("Child 2 Process\n");

        printf("Division = %d\n", a / b);

        return 0;
    }

    wait(NULL);
    wait(NULL);

    printf("Parent Process: Both children finished.\n");

    return 0;
}