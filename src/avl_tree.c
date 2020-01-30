#include <stdlib.h>
#include <stdio.h>
#include <avl_tree.h>

static inline int
height(avl_node_t *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

static inline void
right_rotate(avl_node_t **node)
{
    avl_node_t *y = (*node)->left;
    avl_node_t *T3 = y->right;

    (*node)->left = T3;
    y->right = *node;

    (*node)->height = MAX(height((*node)->left), height((*node)->right)) + 1;
    y->height = MAX(height(y->left), height(y->right)) + 1;

    *node = y;
}

static inline void
left_rotate(avl_node_t **node)
{
    avl_node_t *y = (*node)->right;
    avl_node_t *T3 = y->left;

    (*node)->right = T3;
    y->left = *node;

    (*node)->height = MAX(height((*node)->left), height((*node)->right)) + 1;
    y->height = MAX(height(y->left), height(y->right)) + 1;

    *node = y;
}

void free_tree(avl_node_t *head)
{
    if (head->left != NULL)
    {
        free_tree(head->left);
    }
    if (head->right != NULL)
    {
        free_tree(head->right);
    }
    free(head);
}

static inline int 
get_balance(avl_node_t *head)
{  
    if (head == NULL)  
        return 0;  
    return height(head->left) -  
           height(head->right);  
}  

inline static void
balance_tree(avl_node_t **head)
{
    int left_height = height((*head)->left), right_height = height((*head)->right);
    int max_height = MAX(left_height, right_height);
    int left_balance = get_balance((*head)->left);
    int right_balance = get_balance((*head)->right);

    (*head)->height = 1 + max_height;

    int balance = left_height - right_height;
    if (balance > 1 && left_balance >= 0)
    {
        return right_rotate(head);
    }
    if (balance < -1 && right_balance < 0)
    {
        return left_rotate(head);
    }
    if (balance > 1 && left_balance < 0)
    {
        left_rotate(&(*head)->left);
        return right_rotate(head);
    }
    if (balance < -1 && right_balance >= 0)
    {
        right_rotate(&(*head)->right);
        return left_rotate(head);
    }
}

void insert(avl_node_t **head, int value)
{
    if (*head == NULL)
    {
        *head = malloc(sizeof(avl_node_t));
        (*head)->height = 1;
        (*head)->left = NULL;
        (*head)->right = NULL;
        (*head)->value = value;
        return;
    }
    if (value < (*head)->value)
    {
        insert(&(*head)->left, value);
    }
    else if (value > (*head)->value)
    {
        insert(&(*head)->right, value);
    }
    else
    {
        printf("Nodes with the same values forbidden. Value: %d\n", value);
        return;
    }

    balance_tree(head);
}

static inline avl_node_t **
get_min_node(avl_node_t **head)
{
    while ((*head)->left != NULL)
    {
        head = &(*head)->left;
    }
    return head;
}

void delete_node(avl_node_t **head, int value)
{
    if (*head == NULL)
    {
        printf("avl_node_t with %d value didn't find", value);
        return;
    }
    if (value < (*head)->value)
    {
        delete_node(&(*head)->left, value);
    }
    else if (value > (*head)->value)
    {
        delete_node(&(*head)->right, value);
    }
    else
    {
        if (((*head)->left == NULL) || ((*head)->right == NULL))
        {
            if (((*head)->left == NULL) && ((*head)->right == NULL))
            {
                free(*head);
                *head = NULL;
            }
            else
            {
                avl_node_t *child = (*head)->left ? (*head)->left : (*head)->right;
                free(*head);
                *head = child;
            }
        }
        else
        {
            avl_node_t **min_node = get_min_node(&(*head)->right);
            (*min_node)->height = (*head)->height;
            (*min_node)->left = (*head)->left;
            (*min_node)->right = (*head)->right;
            free(*head);
            *head = *min_node;
            *min_node = NULL;
        }
    }
    if (*head == NULL)
    {
        return;
    }

    balance_tree(head);
}
