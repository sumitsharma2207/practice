typedef struct node_s {
	int val;
	struct node_s *left, *right;
} node;

int create_bst(node **tree, const char *input_file);
int print_binary_tree(node *root);
node *find_node(node *tree, int value);
void get_nearest_leaf_down(node *my_node, unsigned int *leaf_dist);
void get_nearest_leaf_complete_tree(node *root, node *my_node, unsigned int *leaf_dist);
void inorder_traversal(node *root);
void reverse_tree(node *tree);
