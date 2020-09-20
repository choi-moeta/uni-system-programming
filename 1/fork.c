/**
 * \file lab.c
 * \brief Main functionality program.
 *
 * \details Forking child process with its executing.
 *          Child process is a compiled lab.c file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/** \brief Spawn a child process
 *
 * \details Spawn a child process running a new program, as given by PROGRAM.
 *
 * \param program    The name of the program to runs;
 *                   the path will be searched for this program.
 * \param argList    A NULL-terminated list of character strings to be
 *                   passed as the program's argument list.
 * \return           Identifier of the spawned process.
 */

int spawn(char* program, char* const *argv)
{
    pid_t pid = fork();
    if ( pid == 0 )
    {
        printf("<~> Child pid %d\n", getpid());
        system("gcc ./lab.c ./functions.c -o lab");
        execvp(program, argv);
        fprintf(stderr, "an error occurred in execvp\n");
        abort();
    }
    else
    {
        printf("<~> parent pid %d\n", getpid());
        return pid;
    }
}

/** \brief Main function
 *
 * \details Spawn a child process running a new program, as given by PROGRAM.
 *
 * \param program    The name of the program to runs;
 *                   the path will be searched for this program.
 * \param argList    A NULL-terminated list of character strings to be
 *                   passed as the program's argument list.
 * \return           Integer 0 upon exit success.
 */

int main(char* program, char* const *argv)
{
    int childStatus;
    spawn("./lab", argv);
    wait(&childStatus);
    if(WIFEXITED(childStatus))
        printf("The child process exited normally with code %d.\n", WEXITSTATUS(childStatus));
    else
        printf("The child process exited abnormally.\n");
    return 0;
}