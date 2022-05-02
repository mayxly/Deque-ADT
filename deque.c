
#include "deque.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// === DEQUE NODES ==========================================================

// dnode is a node in a double-linked list (or deque) that stores a string
struct dnode
{
    char *data;
    struct dnode *next;
    struct dnode *prev;
};

// dnode_create(str) creates a deque node that stores string str.
// time: O(s), where s is the length of str
static struct dnode *dnode_create(const char *str)
{
    assert(str);
    struct dnode *dn = malloc(sizeof(struct dnode));
    dn->data = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(dn->data, str);
    dn->next = NULL;
    dn->prev = NULL;
    return dn;
}

// dnode_create(str, destroy_data) releases all resources allocated by dnode dn.
//   if destroy_data is true, the stored data is destroyed as well.
// time: O(1)
static void dnode_destroy(struct dnode *dn, bool destroy_data)
{
    assert(dn);
    if (destroy_data)
    {
        free(dn->data);
    }
    free(dn);
}

// === DEQUE ================================================================

// See deque.h for documentation
struct deque
{
    struct dnode *front;
    struct dnode *back;
    int length;
};

// See deque.h for documentation
struct deque *deque_create(void)
{
    struct deque *deq = malloc(sizeof(struct deque));
    deq->front = NULL;
    deq->back = NULL;
    deq->length = 0;
    return deq;
}

// See deque.h for documentation
void deque_destroy(struct deque *deq)
{
    assert(deq);
    while (deq->front != NULL)
    {
        struct dnode *destroy = deq->front;
        deq->front = deq->front->next;
        dnode_destroy(destroy, true);
    }
    free(deq);
}

// See deque.h for documentation
void deque_add_front(struct deque *deq, const char *str)
{
    assert(deq);
    assert(str);
    struct dnode *new_node = dnode_create(str);
    if (deq->front == NULL)
    {
        deq->front = new_node;
        deq->back = new_node;
        deq->length = 1;
    }
    else
    {
        deq->front->prev = new_node;
        new_node->next = deq->front;
        deq->front = new_node;
        deq->length += 1;
    }
}

// See deque.h for documentation
void deque_add_back(struct deque *deq, const char *str)
{
    assert(deq);
    assert(str);
    struct dnode *new_node = dnode_create(str);
    if (deq->front == NULL)
    {
        deq->front = new_node;
        deq->back = new_node;
        deq->length = 1;
    }
    else
    {
        deq->back->next = new_node;
        new_node->prev = deq->back;
        deq->back = new_node;
        deq->length += 1;
    }
}

// See deque.h for documentation
char *deque_remove_front(struct deque *deq)
{
    assert(deq);
    if (deq->front == NULL)
    {
        return NULL;
    }
    struct dnode *destroy = deq->front;
    char *ret_val = destroy->data;
    if (deq->length == 1)
    {
        deq->front = NULL;
        deq->back = NULL;
        deq->length = 0;
    }
    else
    {
        deq->front = deq->front->next;
        deq->front->prev = NULL;
        deq->length -= 1;
    }
    dnode_destroy(destroy, false);
    return ret_val;
}

// See deque.h for documentation
char *deque_remove_back(struct deque *deq)
{
    assert(deq);
    if (deq->front == NULL)
    {
        return NULL;
    }
    struct dnode *destroy = deq->back;
    char *ret_val = destroy->data;
    if (deq->length == 1)
    {
        deq->front = NULL;
        deq->back = NULL;
        deq->length = 0;
    }
    else
    {
        deq->back = deq->back->prev;
        deq->back->next = NULL;
        deq->length -= 1;
    }
    dnode_destroy(destroy, false);
    return ret_val;
}

// See deque.h for documentation
int deque_length(const struct deque *deq)
{
    assert(deq);
    return deq->length;
}

// See deque.h for documentation
void deque_print_forward(const struct deque *deq)
{
    assert(deq);
    if (deq->front != NULL)
    {
        struct dnode *current = deq->front;
        printf("[%s", current->data);
        current = current->next;
        while (current != NULL)
        {
            printf(" -> %s", current->data);
            current = current->next;
        }
        printf("]\n");
    }
    else
    {
        printf("[]\n");
    }
}

// See deque.h for documentation
void deque_print_backward(const struct deque *deq)
{
    assert(deq);
    if (deq->front != NULL)
    {
        struct dnode *current = deq->back;
        printf("[%s", current->data);
        current = current->prev;
        while (current != NULL)
        {
            printf(" <- %s", current->data);
            current = current->prev;
        }
        printf("]\n");
    }
    else
    {
        printf("[]\n");
    }
}
