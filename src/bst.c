/**
  *  Draft of Binary Search Tree
  *  which will be used for implementation
  *  of symbol table
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"
#include "error.h"
#include "util.h"

bst_node_t *bst_new_node(char *key)
{
    bst_node_t *n = malloc(sizeof *n);

    if(n == NULL) {
        fprintf(stderr, "Unable to allocate memory for BST node\n");
        exit(IFJ_INTERNAL_ERR);
    }

    n->left = NULL;
    n->right = NULL;
    n->key = ifj_strdup(key);

    return n;
}

void bst_destroy(bst_node_t *node)
{
    if(node == NULL) 
        return;
    if(node->left != NULL)
        bst_destroy(node->left);
    if(node->right != NULL)
        bst_destroy(node->right);

    free(node->key);
    free(node);
}

bst_node_t *bst_insert_node(bst_node_t *node, char *key)
{
    if(node == NULL) {
        return bst_new_node(key);
    } else {
        // Don't allow duplicates
        int sres = strcmp(key, node->key);
        if(sres < 0)
            node->left = bst_insert_node(node->left, key);
        else if(sres > 0)
            node->right = bst_insert_node(node->right, key);
    }

    return node;
}

bst_node_t *bst_lookup_node(bst_node_t *node, char *key)
{
    if(node == NULL) {
        return NULL;
    } else {
        int sres = strcmp(key, node->key);
        if(sres == 0) {
            return node;
        } else {
            if(sres < 0)
                return bst_lookup_node(node->left, key);
            else
                return bst_lookup_node(node->right, key);
        }
    }
}

// Tests
#ifdef IFJ_BST_DEBUG

void debug_bst_print_tree(bst_node_t *node)
{
    if(node == NULL)
        return;

    debug_bst_print_tree(node->left);
    printf("%s\n", node->key);
    debug_bst_print_tree(node->right);
}

int debug_bst_size(bst_node_t *node)
{
    if(node == NULL)
        return 0;

    return 1 + debug_bst_size(node->left) + debug_bst_size(node->right);
}

#include <math.h>
#include <time.h>

int main(int argc, char *argv[])
{
    char *ta[] = { "key", "Key", "string", "sTrIng", "STRING", "id",
                   "num", "i", "I", "key", "asdf3", "tea23", "_2314", NULL };
    int rc = 0;
    bst_node_t *root = NULL;

    // Test alloc
    root = bst_new_node("j");

    // Test insert
    for(unsigned int i = 0; ta[i] != NULL; i++)
        root = bst_insert_node(root, ta[i]);

    // Print tree
    debug_bst_print_tree(root);
    printf("Size: %d\n", debug_bst_size(root));

    // Test lookup
    for(unsigned int i = 0; ta[i] != NULL; i++) {
        bst_node_t *search = bst_lookup_node(root, ta[i]);
        if(search == NULL) {
            fprintf(stderr, "[FAIL] Couldn't find node with value %s\n", ta[i]);
            rc = 1;
        } else {
            if(strcmp(ta[i], search->key) == 0) {
                fprintf(stderr, "[PASS] Found node with correct value (%s == %s)\n",
                        ta[i], search->key);
            } else {
                fprintf(stderr, "[FAIL] Found node with incorrect value (%s != %s)\n",
                        ta[i], search->key);
                rc = 1;
            }
        }
    }

    // Test free (check with valgrind)
    bst_destroy(root);

    return rc;
}
#endif
