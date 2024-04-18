#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  //rb트리 1개의 사이즈만큼을 초기화해둔다.
  // TODO: initialize struct if needed
  //node에 대한 초기화도 함께 해주어야하지 않을까? 노드는 트리의 각 노드를 의미하니까
  node_t child = (node_t*)calloc(1, sizeof(node_t));//위에서 rbtree도 1만큼의 크기만 calloc해주었으니 얘도 마찬가지이다.
  child.color = RBTREE_BLACK;
  p->nil = child.parent = child;
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
  return t->root;
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
