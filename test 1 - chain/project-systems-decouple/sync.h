#ifndef SYNC_H
#define SYNC_H

#include <stddef.h>
#include <stdatomic.h>
#include <stdbool.h>

// Structure representing a node in the MPMC lock-free queue
typedef struct Node {
    void* data;
    _Atomic(struct Node*) next;
} Node;

// Structure representing the MPMC lock-free queue
typedef struct {
    _Atomic(Node*) head;
    _Atomic(Node*) tail;
    _Atomic(size_t) count; // Optional: to keep track of the number of elements
} MPMCQueue;

// Initializes a new MPMC lock-free queue
// Parameters:
//   queue - Pointer to the MPMCQueue to initialize
void mpmc_queue_init(MPMCQueue* queue);

// Enqueues an element into the MPMC lock-free queue
// Parameters:
//   queue - Pointer to the MPMCQueue
//   data  - Data to enqueue
// Returns:
//   true if the enqueue operation was successful, false otherwise
bool mpmc_queue_enqueue(MPMCQueue* queue, void* data);

// Dequeues an element from the MPMC lock-free queue
// Parameters:
//   queue - Pointer to the MPMCQueue
//   data  - Pointer to store the dequeued data
// Returns:
//   true if the dequeue operation was successful, false otherwise (e.g., queue is empty)
bool mpmc_queue_dequeue(MPMCQueue* queue, void** data);

// Checks if the MPMC lock-free queue is empty
// Parameters:
//   queue - Pointer to the MPMCQueue
// Returns:
//   true if the queue is empty, false otherwise
bool mpmc_queue_is_empty(MPMCQueue* queue);

// Optional: Returns the number of elements in the MPMC lock-free queue
// Parameters:
//   queue - Pointer to the MPMCQueue
// Returns:
//   Number of elements in the queue
size_t mpmc_queue_count(MPMCQueue* queue);

// Cleans up the MPMC lock-free queue (frees any remaining nodes)
// Parameters:
//   queue - Pointer to the MPMCQueue to clean up
void mpmc_queue_cleanup(MPMCQueue* queue);

#endif // SYNC_H