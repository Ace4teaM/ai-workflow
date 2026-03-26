#include "sync.h"
#include <stdatomic.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Nom par défaut pour la mémoire partagée
#define SHM_NAME "/mpmc_queue_shm"
// Taille par défaut de la mémoire partagée (à ajuster selon les besoins)
#define SHM_SIZE 4096

// Structure interne pour la gestion de la mémoire partagée
typedef struct {
    int shm_fd;
    void* shm_ptr;
    size_t shm_size;
} SharedMemory;

// Variable globale pour la mémoire partagée (simplification)
static SharedMemory shared_mem = { -1, NULL, 0 };

// Fonction pour initialiser la mémoire partagée
static bool init_shared_memory(size_t size) {
    if (shared_mem.shm_ptr != NULL) {
        return true; // Déjà initialisée
    }

    shared_mem.shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shared_mem.shm_fd == -1) {
        return false;
    }

    if (ftruncate(shared_mem.shm_fd, size) == -1) {
        close(shared_mem.shm_fd);
        shm_unlink(SHM_NAME);
        return false;
    }

    shared_mem.shm_ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shared_mem.shm_fd, 0);
    if (shared_mem.shm_ptr == MAP_FAILED) {
        close(shared_mem.shm_fd);
        shm_unlink(SHM_NAME);
        return false;
    }

    shared_mem.shm_size = size;
    return true;
}

// Fonction pour libérer la mémoire partagée
static void cleanup_shared_memory() {
    if (shared_mem.shm_ptr != NULL) {
        munmap(shared_mem.shm_ptr, shared_mem.shm_size);
        shared_mem.shm_ptr = NULL;
    }
    if (shared_mem.shm_fd != -1) {
        close(shared_mem.shm_fd);
        shm_unlink(SHM_NAME);
        shared_mem.shm_fd = -1;
    }
    shared_mem.shm_size = 0;
}

// Initialise une nouvelle file MPMC lock-free
void mpmc_queue_init(MPMCQueue* queue) {
    if (queue == NULL) {
        return;
    }

    // Initialiser la mémoire partagée
    if (!init_shared_memory(SHM_SIZE)) {
        return;
    }

    // Placer la file dans la mémoire partagée
    MPMCQueue* shared_queue = (MPMCQueue*)shared_mem.shm_ptr;
    atomic_init(&shared_queue->head, NULL);
    atomic_init(&shared_queue->tail, NULL);
    atomic_init(&shared_queue->count, 0);

    // Copier l'adresse de la file partagée dans la file locale
    memcpy(queue, shared_queue, sizeof(MPMCQueue));
}

// Enfile un élément dans la file MPMC lock-free
bool mpmc_queue_enqueue(MPMCQueue* queue, void* data) {
    if (queue == NULL || data == NULL) {
        return false;
    }

    // Allouer un nouveau nœud
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return false;
    }

    atomic_init(&new_node->data, data);
    atomic_init(&new_node->next, NULL);

    // Récupérer la file partagée
    MPMCQueue* shared_queue = (MPMCQueue*)shared_mem.shm_ptr;

    // Enfilement lock-free
    Node* expected_tail = atomic_load(&shared_queue->tail);
    while (true) {
        if (atomic_compare_exchange_weak(&shared_queue->tail, &expected_tail, new_node)) {
            if (expected_tail != NULL) {
                atomic_store(&expected_tail->next, new_node);
            } else {
                atomic_store(&shared_queue->head, new_node);
            }
            atomic_fetch_add(&shared_queue->count, 1);
            return true;
        }
    }
}

// Défile un élément de la file MPMC lock-free
bool mpmc_queue_dequeue(MPMCQueue* queue, void** data) {
    if (queue == NULL || data == NULL) {
        return false;
    }

    // Récupérer la file partagée
    MPMCQueue* shared_queue = (MPMCQueue*)shared_mem.shm_ptr;

    // Défilement lock-free
    Node* expected_head = atomic_load(&shared_queue->head);
    while (expected_head != NULL) {
        if (atomic_compare_exchange_weak(&shared_queue->head, &expected_head, atomic_load(&expected_head->next))) {
            *data = atomic_load(&expected_head->data);
            atomic_fetch_sub(&shared_queue->count, 1);
            free(expected_head);
            return true;
        }
    }

    return false; // File vide
}

// Vérifie si la file MPMC lock-free est vide
bool mpmc_queue_is_empty(MPMCQueue* queue) {
    if (queue == NULL) {
        return true;
    }

    MPMCQueue* shared_queue = (MPMCQueue*)shared_mem.shm_ptr;
    return atomic_load(&shared_queue->head) == NULL;
}

// Retourne le nombre d'éléments dans la file MPMC lock-free
size_t mpmc_queue_count(MPMCQueue* queue) {
    if (queue == NULL) {
        return 0;
    }

    MPMCQueue* shared_queue = (MPMCQueue*)shared_mem.shm_ptr;
    return atomic_load(&shared_queue->count);
}

// Nettoie la file MPMC lock-free
void mpmc_queue_cleanup(MPMCQueue* queue) {
    if (queue == NULL) {
        return;
    }

    void* data;
    while (mpmc_queue_dequeue(queue, &data)) {
        // Libérer les données si nécessaire
    }

    cleanup_shared_memory();
}