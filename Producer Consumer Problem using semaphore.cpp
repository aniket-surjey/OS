#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h> /* sem_t */
#include<stdlib.h>

#define BUF_SIZE 2

struct buffer {
        int data;
};

struct buffer buf[BUF_SIZE];

sem_t fill, empty;

int value, i;

void *producer(void *data);
void *consumer(void *data);

int main(void)
{
    int sel, prod_data, cons_data;
    int k;

    if (sem_init(&empty, 0, BUF_SIZE)) {
        printf("Error: semaphore not initialize\n");
        return -1;
    }
    if (sem_init(&fill, 0, 0)) {
        printf("Error: semaphore not initialize\n");
        return -1;
    }

    while (1) {
        printf(".........................................................\n");
        printf("Selection\n");
        printf("Producer : 1 | Consumer : 2 | Display : 3 | Exit : 0 || ");
        scanf("%d",&sel);
        printf(".........................................................\n");

        switch (sel) {
        case 1:
            sem_getvalue(&empty, &value);
//          printf("Prod_e: %d\n", value);
            sem_getvalue(&fill, &value);
//          printf("Prod_f: %d\n", value);
            printf("\nProducer\n");
            pthread_t prod_t;
            printf("Enter data:");
            scanf("%d", &prod_data);
            if (pthread_create(&prod_t, NULL, producer, (void *) &prod_data)) {
                printf("Error: thread not created\n");
                return -1;
            }
            break;
        case 2:
            printf("\nConsumer\n");
            sem_getvalue(&empty, &value);
//          printf("Cons_e: %d\n", value);
            sem_getvalue(&fill, &value);
//          printf("Cons_f: %d\n", value);
            pthread_t con_t;
            if (pthread_create(&con_t, NULL, consumer, (void *) &cons_data)) {
                printf("Error: thread not created\n");
                return -1;
            }
            if (i == 0) {
                printf("Buffer empty\n");
                break;
            }
//              sleep(1); // if commented then synchronization issue
            printf("Consume data: %d\n", cons_data);
            break;
        case 3:
                if (i == 0) {
                    printf("Buffer empty\n");
                    break;
                }
                for (k = 0; k < i; k++)
                    printf("buf[%d]: %d\n", k, buf[k].data);
                break;
        case 0:
            sem_destroy(&fill);
            sem_destroy(&empty);
            exit (0);
            break;
        }
    }
    sem_destroy(&fill);
    sem_destroy(&empty);
    return 0;
}

void *producer(void *arg)
{
    int data = *(int *) arg;

    if (sem_wait(&empty)) { /* wait */
        printf("Error: sem wait fail\n");
        pthread_exit(NULL);
    }

    buf[i].data = data;
    i++;

    if (sem_post(&fill)) { /* post */
        printf("Error: sem wait fail\n");
        pthread_exit(NULL);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{

    if (sem_wait(&fill)) { /* wait */
        printf("Error: sem wait fail\n");
        pthread_exit(NULL);
    }

    i--;
    *(int *) arg = buf[i].data;

    if (sem_post(&empty)) { /* post */
        printf("Error: sem wait fail\n");
        pthread_exit(NULL);
    }
    pthread_exit(NULL);
}
