/**
 * \file main.c
 * \brief Main functionality program.
 *
 * \details Creating threads.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

pthread_mutex_t examQueueMutex = PTHREAD_MUTEX_INITIALIZER;

/** \brief Print result
 *
 *  \details Print result of student examination.
 *
 *  \param studentNum Student number.
 *  \param result     Code of examination result.
 */

void examResult(void* studentNum, int result)
{
    int lastDigit = (int)studentNum % 10;
    int num = (int)studentNum + 1;

    if (result == 0)
        printf("Student %d kicked out.\n", num);
    else if (result == 1)
        printf("Student %d passed exam.\n", num);
    else if (result == 2)
        printf("Student %d was given another chance.\n", num);
}

/** \brief Proccess exam
 *
 *  \details Do exam until success.
 *
 *  \param num Student number.
 *  \return NULL-pointer
 */

void* takeExam(void* num)
{
    int rnd = 2;

    while (rnd == 2)
    {
        pthread_mutex_lock(&examQueueMutex);
        
        // struct timespec tim, tim2;
        // tim.tv_sec = 1;
        // tim.tv_nsec = 10;
        // nanosleep(&tim , &tim2);

        pthread_mutex_unlock(&examQueueMutex);

        rnd = random() % 3;
        examResult(num, rnd);
    }

    return NULL;
}

/** \brief Main function
 *
 * \details Creates threads again after end.
 *
 * \param program    The name of the program to runs;
 *                   the path will be searched for this program.
 * \param argList    A NULL-terminated list of character strings to be
 *                   passed as the program's argument list.
 * \return           Integer 0 upon exit success.
 */

int main(char* program, char* const *argv)
{
    // while (1)
    {
        int studentsCount = atoi(argv[1]);

        pthread_t threads[studentsCount];

        printf("<> %d students enter auditory.\n", studentsCount);

        for (int i = 0; i < studentsCount; i++)
            pthread_create(&(threads[i]), NULL, &takeExam, (void *)i);

        for (int i = 0; i < studentsCount; i++)
            pthread_join(threads[i], NULL);

        printf("<> Exam has ended.\n");
        printf("<> Starting new exam.\n");
    }

    return 0;
}