#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  if (p == NULL) {
	  return NULL;
  }
  //rb트리 1개의 사이즈만큼을 초기화해둔다.
  // TODO: initialize struct if needed
  //node에 대한 초기화도 함께 해주어야하지 않을까? 노드는 트리의 각 노드를 의미하니까
  p->root = NULL;
  p->nil = (node_t*)calloc(1, sizeof(node_t));
  p->nil->color = RBTREE_BLACK;
  p->nil->parent = NULL;
  p->nil->left = NULL;
  p->nil->right = NULL;
  return p;
}
void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
	//트리에서 작은 경우를 찾으려면 왼쪽으로 뒤져야한다.
	node_t* max_tree = t->root;
	if (max_tree == NULL)return NULL;
	else if (max_tree->left == NULL) {
		if (max_tree->right != NULL)return max_tree->right;
		else {
			return NULL;
		}
	}
	else {
		while (max_tree->left != t->nil) {
			max_tree = max_tree->left;
		}
	}
  return max_tree;
}
node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
