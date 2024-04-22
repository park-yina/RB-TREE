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

void delete_rbtree(rbtree* t) {
    node_t* cur = t->root;
    node_t* pre = NULL;
    node_t* temp = NULL;
    while (cur != t->nil) {
        if (pre == cur->parent) {
            if (cur->left != t->nil) {
                // 왼쪽으로 이동
                pre = cur;
                cur = cur->left;
            }
            else if (cur->right != t->nil) {
                // 오른쪽으로 이동
                pre = cur;
                cur = cur->right;
            }
            else {
                // 리프
                temp = cur;
                cur = cur->parent;
                free(temp);
                if (cur->left == temp) {
                    cur->left = t->nil;
                }
                else {
                    cur->right = t->nil;
                }
            }
        }
        else if (pre == cur->left) {
            if (cur->right != t->nil) {
                // 오른쪽으로 이동
                pre = cur;
                cur = cur->right;
            }
            else {
                // 리프
                temp = cur;
                cur = cur->parent;
                free(temp);
                cur->right = t->nil;
            }
        }
        else { // pre == cur->right
            temp = cur;
            cur = cur->parent;
            free(temp);
        }
    }
    free(t->nil);
    free(t);
}


void leftRotate(rbtree* t, node_t* x) {
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

void rightRotate(rbtree* t, node_t* y) {
    node_t* x;
    x = y->left; // y의 왼쪽자식에 있던 x.
    y->left = x->right; // x의 왼쪽에 있던 애 즉 y기준의 왼쪽 손자가 x의 오른쪽으로 붙는다.
    if (x->right != t->nil) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == t->nil) {
        t->root = x;
    }
    else if (y == y->parent->right) {
        y->parent->right = x;
    }
    else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

void rb_insert_Fixup(rbtree* t, node_t* z) {
    node_t* y;
    while (z->parent->color == RBTREE_RED) {
        // 여기에 노드 z의 부모가 레드인 경우의 조건문을 추가해야 합니다.
        if (z->parent == t->nil) {
            break; // 종료 조건 추가
        }
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
                    leftRotate(t, z);
                }
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                rightRotate(t, z->parent->parent);
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
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(t, z);
                }
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                leftRotate(t, z->parent->parent);
            }
        }
    }
    t->root->color = RBTREE_BLACK;
}

node_t* rbtree_insert(rbtree* t, const key_t key) {
    node_t* y = t->nil;
    node_t* x = t->root;
    while (x != t->nil) {
        y = x;
        if (key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    node_t* z = (node_t*)calloc(1, sizeof(node_t));
    if (z == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }
    z->key = key;
    z->parent = y;
    if (y == t->nil) {
        t->root = z;
    }
    else if (key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = t->nil;
    z->right = t->nil;
    z->color = RBTREE_RED;
    rb_insert_Fixup(t, z);
    return t->root;
}

node_t* rbtree_find(const rbtree* t, const key_t key) {
    // TODO: implement find
    //rb트리는 이진트리의 속성을 그대로 가지고 있기 때문에 왼쪽에 작은 수 오른쪽에 큰수가 위치한다.
    node_t* target;
    target = t->root;
    while (target != t->nil) {
        if (target->key == key) {
            return target;
        }
        else if (target->key < key) {
            //타겟이 키보다 작다는건 좀 더 큰 쪽으로 뒤져야한다는 것
            target = target->right;
        }
        else if (target->key > key) {
            target = target->left;
        }
    }
    return NULL;
}

node_t* rbtree_min(const rbtree* t) {
    // TODO: implement find
      //트리에서 작은 경우를 찾으려면 왼쪽으로 뒤져야한다.
    node_t* min_tree = t->root;
    if (min_tree == NULL)return NULL;
    else if (min_tree->left == NULL) {
        if (min_tree->right != NULL)return min_tree->right;
        else {
            return NULL;
        }
    }
    else {
        while (min_tree->left != t->nil) {
            min_tree = min_tree->left;
        }
    }
    return min_tree;
}

node_t* rbtree_max(const rbtree* t) {
    node_t* max_tree = t->root;

    if (max_tree == NULL) return NULL;

    while (max_tree->right != t->nil) {
        max_tree = max_tree->right;
    }

    return max_tree;
}

void rb_grand(rbtree* t, node_t* n, node_t* p) {
    if (n->parent == t->nil) {
        //n의 부모가 nil이라는 것은 n이 루트라는 뜻
        t->root = p;
    }
    else if (n == n->parent->left) {
        //n이 왼쪽자식이다.
        n->parent->left = p;
    }
    else {
        n->parent->right = p;
    }
    p->parent = n->parent;
}
node_t* predecessor(rbtree* t, node_t* n) {
    node_t* temp = n;
    while (temp->right != t->nil) {
        temp = temp->right;
    }
    return temp;
}

int rbtree_erase(rbtree* t, node_t* p) {
    if (t == NULL) {
        return 0;
    }
    node_t* y = p;
    node_t* x;
    color_t color = y->color;
    if (p->left == t->nil) {
        x = p->right;
        rb_grand(t, p, p->right);
    }
    else if (p->right == t->nil) {
        x = p->left;
        rb_grand(t, p, p->left);
    }
    else {
        y = predecessor(t, p->left);
        color = y->color;
        x = y->left;
        if (y->parent == p) {
            x->parent = y;
        }
        else {
            rb_grand(t, y, y->left);
            y->left = p->left;
            y->left->parent = y;
            y->color = p->color;
        }
    }
    if (y->color == RBTREE_BLACK) {
        del_fixup(t, x);
    }
    // 이후에는 fixup도 구현해야
    return 0;
}
void del_fixup(rbtree* t, node_t* x) {
    node_t* w;
    while (x != t->root && x->color == RBTREE_BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RBTREE_RED) {
                w->color == RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                leftRotate(t, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
                w->color = RBTREE_RED;
                x = x->parent;
            }
            else if (w->right->color == RBTREE_BLACK) {
                w->left->color = RBTREE_BLACK;
                w->color = RBTREE_RED;
                rightRotate(t, w);
                w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = RBTREE_BLACK;
            w->right->color = RBTREE_BLACK;
            leftRotate(t, x->parent);
            x = t->root;
        }
        else {
            w = x->parent->left;
            if (w->color == RBTREE_RED) {
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                rightRotate(t, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
                w->color = RBTREE_RED;
                x = x->parent;
            }
            else if (w->left->color == RBTREE_BLACK) {
                w->right->color = RBTREE_BLACK;
                w->color = RBTREE_RED;
                leftRotate(t, w);
                w = x->parent->left;
            }
            w->color = x->parent->color;
            x->parent->color = RBTREE_BLACK;
            w->left->color = RBTREE_BLACK;
            rightRotate(t, x->parent);
            x = t->root;
        }
    }
    x->color = RBTREE_BLACK;
}

int rbtree_to_array(const rbtree* t, key_t* arr, const size_t n) {
    int idx = 0;

    if (t == NULL || t->root == t->nil || arr == NULL || n == 0)
        return 0;

    // 중위 순회 하면 순서대로 정렬되어 array만들 떄 도움됨
    inorderTraversal(t, t->root, arr, &idx, n);

    return idx; 
}
int rbtree_to_array(const rbtree* t, key_t* arr, const size_t n) {
    if (t == NULL || t->root == t->nil || arr == NULL || n == 0)
        return 0;

    int idx = 0;
    inorder(t, t->root, arr, &idx, n);

    return idx;
}
