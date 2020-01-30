#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct avl_node_s avl_node_t;

struct avl_node_s
{
    int value;
    avl_node_t *left, *right;
    int height;
};

void insert(avl_node_t **, int);
void free_tree(avl_node_t *);
void delete_node(avl_node_t **, int);
