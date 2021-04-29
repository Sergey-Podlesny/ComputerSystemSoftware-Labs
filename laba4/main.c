#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

pthread_mutex_t mutex;
pid_t gettid(void);
void *printInfo()
{
    time_t t;
    while(true)
    {
        sleep(2);
        pthread_mutex_lock( &mutex );
        time(&t);
        printf("Thread id: %d time: %s\n", gettid(), ctime(&t));
        pthread_mutex_unlock( &mutex );
    }
}

int main()
{
    pthread_mutex_init(&mutex,NULL);
    char c='z';
    int sizeOfThreads=0, flag = 1;
    pthread_t threadArr[10];
    printf("'+'Add thread\n'-'Delete thread\n'q'Exit");
    printf("\n");
    while(flag){
        scanf("%c",&c);
        switch (c)
        {
            case '+':
                if(sizeOfThreads <= 10) {
                    pthread_create(&threadArr[sizeOfThreads++], NULL, &printInfo, NULL);
                    printf("Thread created\n");
                }
                else {
                    printf("Max count of thread\n");
                }
                break;
            case '-':
                if(sizeOfThreads==0){
                    printf("Your deleted all threads\n");
                }
                else {
                    pthread_cancel(threadArr[sizeOfThreads-1]);
                    sizeOfThreads--;
                    printf("Thread was deleted\n");
                }
                break;
            case 'q':
                flag =0;
                printf("Exit.\n");
                break;
        }
    }

    return 0;
}



