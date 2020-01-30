#include <avl_tree.h>
#include <stdlib.h>
#include <stdio.h>

int
main()
{
    avl_node_t *head = NULL;
    // int i;
    // for (i = 0; i < 1000; i++)
    // {
    //     insert(&head, i);
    // }
    insert(&head, 3);
    insert(&head, 4);
    insert(&head, 5);
    insert(&head, 6);
    insert(&head, 7);
    insert(&head, 8);
    insert(&head, 9);

    delete_node(&head, 6);

    free_tree(head);
    printf("Finished\n");
}