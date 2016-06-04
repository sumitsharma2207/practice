#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "binary_tree.h"

#define INPUT_FILE "tree.txt"

node *tree = NULL;

int main(int argc, char *argv[])
{
	unsigned int leaf_dist;
	create_bst(&tree, INPUT_FILE);

	node *cur_node = find_node(tree, atoi(argv[1]));
	get_nearest_leaf_down(cur_node, &leaf_dist);
	printf("Leaf dist in subtree for node %s is %d\n", argv[1], leaf_dist);
	get_nearest_leaf_complete_tree(tree, cur_node, &leaf_dist);
	printf("Leaf dist in complete for node %s is %d\n", argv[1], leaf_dist);
}

int print_binary_tree(node *root)
{
}

node *find_node(node *tree, int value)
{
	while (tree != NULL) {
		if (value == tree->val)
			return tree;
		else if (value < tree->val)
			return find_node(tree->left, value);
		else
			return find_node(tree->right, value);
	}

	return NULL;
}

int create_bst(node **tree, const char *input_file)
{
	int node_val;
	FILE *fp = fopen(input_file, "r");
	node *temp = *tree;
	while(fscanf(fp, "%d ", &node_val) > 0) {
		node *new_node = (node *) malloc(sizeof(node));
		new_node->val = node_val;
		if (!(*tree)) {
			*tree = new_node;
			continue;
		}
		temp = *tree;
		int found = 0;
		do {
			if (new_node->val <= temp->val) {
				if (temp->left == NULL) {
					temp->left = new_node;
					found = 1;
					printf("Node %d added to left of %d\n", new_node->val, temp->val);
				} else {
					temp = temp->left;
					continue;
				}
			} else {
				if (temp->right == NULL) {
					temp->right = new_node;
					found = 1;
					printf("Node %d added to right of %d\n", new_node->val, temp->val);
				} else {
					temp = temp->right;
					continue;
				}
			}
		} while (found == 0);
	}
}

void get_nearest_leaf_down(node *my_node, unsigned int *leaf_dist)
{
	unsigned int left_dist = UINT_MAX, right_dist = UINT_MAX;
	bool is_subtree = false;

	if (my_node == NULL) {
		*leaf_dist = UINT_MAX;
		return;
	}

	if (my_node->left == NULL && my_node->right == NULL) {
		*leaf_dist = 0;
		return;
	}

	if (my_node->left)
		get_nearest_leaf_down(my_node->left, &left_dist);
	if (my_node->right)
		get_nearest_leaf_down(my_node->right, &right_dist);

	if (left_dist < right_dist) {
		*leaf_dist = left_dist + 1;
		printf("Nearest leaf path %d\n", my_node->left->val);
	} else {
		*leaf_dist = right_dist + 1;
		printf("Nearest leaf path %d\n", my_node->right->val);
	}

	return;
}

void get_nearest_leaf_complete_tree(node *root, node *my_node, unsigned int *leaf_dist)
{
	unsigned int top_leaf_dist = UINT_MAX, temp_leaf_dist, subtree_leaf_dist;

	if (my_node == NULL || root == NULL) {
		*leaf_dist = UINT_MAX;
		return;
	}

	while (root != my_node) {
		node *sub_tree , *opp_tree;
		if (my_node->val < root->val) {
			sub_tree = root->left;
			opp_tree = root->right;
		} else {
			sub_tree = root->right;
			opp_tree = root->left;
		}

		get_nearest_leaf_down(opp_tree, &temp_leaf_dist);
		if ((temp_leaf_dist + 1) < top_leaf_dist)
			top_leaf_dist = temp_leaf_dist + 1;
		root = sub_tree;
		top_leaf_dist++;
	}

	get_nearest_leaf_down(my_node, &subtree_leaf_dist);
	if (subtree_leaf_dist < top_leaf_dist)
		*leaf_dist = subtree_leaf_dist;
	else
		*leaf_dist = top_leaf_dist;

	return;
}
