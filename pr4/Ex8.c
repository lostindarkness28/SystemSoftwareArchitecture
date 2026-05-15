#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define OPERATIONS 1000000
#define BLOCK_SIZE 64
#define POOL_SIZE 100000

typedef struct Node {
    struct Node* next;
} Node;

__thread Node* local_pool = NULL;

void init_pool() {
    for (int i = 0; i < POOL_SIZE; i++) {
        Node* node = (Node*)malloc(BLOCK_SIZE);
        node->next = local_pool;
        local_pool = node;
    }
}

void* pool_alloc() {
    if (local_pool == NULL)
        return NULL;

    Node* node = local_pool;
    local_pool = local_pool->next;
    return node;
}

void pool_free(void* ptr) {
    Node* node = (Node*)ptr;
    node->next = local_pool;
    local_pool = node;
}

void* malloc_test(void* arg) {
    for (int i = 0; i < OPERATIONS; i++) {
        void* ptr = malloc(BLOCK_SIZE);
        free(ptr);
    }
    return NULL;
}

void* pool_test(void* arg) {
    init_pool();

    for (int i = 0; i < OPERATIONS; i++) {
        void* ptr = pool_alloc();
        pool_free(ptr);
    }

    return NULL;
}

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void run_test(int threads_count, void* (*func)(void*), const char* name) {
    pthread_t threads[threads_count];

    double start = get_time();

    for (int i = 0; i < threads_count; i++)
        pthread_create(&threads[i], NULL, func, NULL);

    for (int i = 0; i < threads_count; i++)
        pthread_join(threads[i], NULL);

    double end = get_time();

    printf("%s | Threads: %d | Time: %.4f sec\n",
           name, threads_count, end - start);
}

int main() {
    int thread_counts[] = {1, 2, 4, 8};

    printf("=== malloc/free ===\n");

    for (int i = 0; i < 4; i++)
        run_test(thread_counts[i], malloc_test, "malloc/free");

    printf("\n=== thread-local pool ===\n");

    for (int i = 0; i < 4; i++)
        run_test(thread_counts[i], pool_test, "thread-local");

    return 0;
}
