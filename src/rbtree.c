#include "rbtree.h"

#include <stdlib.h>

rbtree* new_rbtree(void) {
    rbtree* p = (rbtree*)calloc(1, sizeof(rbtree));
    if (p == NULL) {
        free(p);
        return NULL;
    }

   
    node_t* nil_node = (node_t*)calloc(1, sizeof(node_t));
    if (nil_node == NULL) {
        free(p);
        return NULL;
    }
    nil_node->color = RBTREE_BLACK;

    // root 및 nil 포인터에 동일한 노드
    p->root = nil_node;
    p->nil = nil_node;

    return p;
}
void LeftRotate(rbtree* t, node_t* x) {
	node_t* y;
	y = x->right;
	// x의 왼쪽 자식은 그대로 
	// x의 오른쪽 자식은 y의 왼쪽 자식
	x->right = y->left;
	if (y->left != t->nil) {
		y->left->parent = x; // 본인의 할아버지까지 거슬러가는 과정
	}
	y->parent = x->parent;
	if (x->parent == t->nil) {
		t->root = y; 
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}
void RightRotate(rbtree* t, node_t* y) {
	node_t* x;
	x = y->left;//y의 왼쪽자식에 있던 x.
	y->left = x->right; // x의 왼쪽에 있던 애 즉 y기준의 왼쪽 손자가 x의 오른쪽으로 붙는다.
	if (x->right != t->nil) {
		x->right->parent = y;
	}
	x->parent = y->parent;
	if (y->parent == t->nil) {
		t->rppt = x;
	}
	else if (y == y->parent->right)
		y->parent->right = x;
	else
		y->parent->left = x;
	x->right = y;
	y->parent = x;
}
void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}
void rb_insert_Fixup(rbtree* t, node_t* z) {
	node_t* y;
	while (z->parent->color == RBTREE_RED) {
		// 여기에 노드 z의 부모가 레드인 경우의 조건문을 추가해야 합니다.
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;
			if (y->color == RBTREE_RED) {
				z->parent->color = RBTREE_BLACK;
				y->color = RBTREE_BLACK;
				z->parent->parent->color = RBTREE_RED;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					LeftRotate(t, z);
				}
				z->parent->color = RBTREE_BLACK;
				z->parent->parent->color = RBTREE_RED;
				RightRotate(t, z->parent->parent);
			}
		}
		else {
			//TODO
			y = z->parent->parent->left;
			//다시 위에 if문부터 시작 을 해야한다.
			if (y->color == RBTREE_RED) {
				z->parent->color = RBTREE_BLACK;
				y->color = RBTREE_BLACK;
				z->parent->parent->color = RBTREE_RED;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					RightRotate(t, z);
				}
				z->parent->color = RBTREE_BLACK;
				z->parent->parent->color = RBTREE_RED;
				LeftRotate(t, z->parent->parent);
			}
		}
	}
	t->root->color = RBTREE_BLACK;

}

node_t *rbtree_insert(rbtree *t, const key_t key) {

	node_t* y = t->nil;
	node_t* x = t->root;
	while (x != t.nil) {
		y = x;
		if (key < x->key) {
			x = x->left;
		}
		else x = x->right;
	}
	node_t* z = (node_t*)calloc(1, sizeof(node_t));
	z->parent = y;
	if (z == t->nil)
		t->root = z;
	else if (z->key < key) {
		y->left = z;
	}
	else
		y->right = z;
	z->left = t->nil;
	z->right = t->nil;
	z->color = RBTREE_RED;
	rb_insert_Fixup(t, z);
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
