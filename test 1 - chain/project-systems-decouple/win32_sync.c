#include "sync.h"
#include <windows.h>
#include <stdbool.h>

// Initializes a new MPMC lock-free queue
void mpmc_queue_init(MPMCQueue* queue) {
    if (queue == NULL) {
        return;
    }

    // Create a dummy node
    Node* dummy = (Node*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(Node));
    if (dummy == NULL) {
        return;
    }

    dummy->data = NULL;
    dummy->next = NULL;

    // Initialize head and tail to the dummy node
    atomic_store(&queue->head, dummy);
    atomic_store(&queue->tail, dummy);
    atomic_store(&queue->count, 0);
}

// Enqueues an element into the MPMC lock-free queue
bool mpmc_queue_enqueue(MPMCQueue* queue, void* data) {
    if (queue == NULL || data == NULL) {
        return false;
    }

    // Allocate a new node
    Node* newNode = (Node*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(Node));
    if (newNode == NULL) {
        return false;
    }

    newNode->data = data;
    newNode->next = NULL;

    Node* tail;
    Node* next;

    while (true) {
        tail = atomic_load(&queue->tail);
        next = atomic_load(&tail->next);

        // Check if tail is still the last node
        if (tail == atomic_load(&queue->tail)) {
            if (next == NULL) {
                // Try to link the new node to the tail
                if (InterlockedCompareExchangePointer((PVOID*)&tail->next, newNode, next) == next) {
                    break;
                }
            } else {
                // Tail was not actually the last node, move tail forward
                InterlockedCompareExchangePointer((PVOID*)&queue->tail, next, tail);
            }
        }
    }

    // Try to move tail to the new node
    InterlockedCompareExchangePointer((PVOID*)&queue->tail, newNode, tail);
    atomic_fetch_add(&queue->count, 1);

    return true;
}

// Dequeues an element from the MPMC lock-free queue
bool mpmc_queue_dequeue(MPMCQueue* queue, void** data) {
    if (queue == NULL || data == NULL) {
        return false;
    }

    Node* head;
    Node* tail;
    Node* next;

    while (true) {
        head = atomic_load(&queue->head);
        tail = atomic_load(&queue->tail);
        next = atomic_load(&head->next);

        // Check consistency
        if (head == atomic_load(&queue->head)) {
            if (head == tail) {
                // Queue is empty or tail is falling behind
                if (next == NULL) {
                    return false; // Queue is empty
                }
                // Tail is falling behind, try to advance it
                InterlockedCompareExchangePointer((PVOID*)&queue->tail, next, tail);
            } else {
                // Try to read the next node's data
                *data = next->data;
                if (InterlockedCompareExchangePointer((PVOID*)&queue->head, next, head) == head) {
                    break;
                }
            }
        }
    }

    // Free the old dummy node
    HeapFree(GetProcessHeap(), 0, head);
    atomic_fetch_sub(&queue->count, 1);

    return true;
}

// Checks if the MPMC lock-free queue is empty
bool mpmc_queue_is_empty(MPMCQueue* queue) {
    if (queue == NULL) {
        return true;
    }
    return atomic_load(&queue->count) == 0;
}

// Returns the number of elements in the MPMC lock-free queue
size_t mpmc_queue_count(MPMCQueue* queue) {
    if (queue == NULL) {
        return 0;
    }
    return atomic_load(&queue->count);
}

// Cleans up the MPMC lock-free queue (frees any remaining nodes)
void mpmc_queue_cleanup(MPMCQueue* queue) {
    if (queue == NULL) {
        return;
    }

    void* data;
    while (mpmc_queue_dequeue(queue, &data)) {
        // Just dequeue and ignore data to free nodes
    }

    Node* head = atomic_load(&queue->head);
    if (head != NULL) {
        HeapFree(GetProcessHeap(), 0, head);
    }
}