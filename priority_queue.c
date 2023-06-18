#include <stdlib.h>
#include "graph.h"
#include "priority_queue.h"

struct _queue_el {
    GraphNode* node;
    unsigned int priority;
    struct _queue_el* next;
};

void pqueue_add_el(QueueEl** root, GraphNode* node, unsigned int priority)
{
    QueueEl* pel = (QueueEl*) malloc(sizeof(QueueEl));
    pel->node = node;
    pel->priority = priority;
    pel->next = NULL;

    if(*root == NULL)
    {
        *root = pel;
        return;
    }

    if(priority < (*root)->priority)
    {
        pel->next = *root;
        *root = pel;
        return;
    }

    QueueEl* current = *root;
    while(current->next != NULL && priority >= current->next->priority)
    {
        current = current->next;
    }
    // root->next > pel
    QueueEl* temp = current->next;
    current->next = pel;
    pel->next = temp;
}

GraphNode* pqueue_next_el(QueueEl** root)
{
    QueueEl* ptemp;
    GraphNode* node;

    if(*root == NULL)
    {
        return NULL;
    }

    ptemp = *root;

    *root = (*root)->next;

    node = ptemp->node;

    free(ptemp);

    return node;
}

void pqueue_remove_node(QueueEl** root, GraphNode* node)
{
    QueueEl* current = *root;
    QueueEl* last = current;

    if(current == NULL)
    {
        return;
    }
    if(current->node == node)
    {
        *root = current->next;
        free(current);
    }

    current = current->next;

    while(current != NULL && current->node != node)
    {
        last = current;
        current = current->next;
    }

    if(current != NULL)
    {
        last->next = current->next;
        free(current);
    }
}

void pqueue_free_all(QueueEl** root)
{
    QueueEl* next = *root;
    while(next != NULL)
    {
        QueueEl* temp = next;
        next = temp->next;
        free(temp);
    }
}