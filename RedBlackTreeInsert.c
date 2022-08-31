#include <stdio.h>
#include <stdlib.h>

enum COLOR {Red, Black};

typedef struct node {
int info;
struct node *right;
struct node *left;
struct node *parent;
enum COLOR color;
}node;

typedef struct red_black_tree {
node *root;
node *NIL;
}red_black_tree;

node* new_node(int info) {
node* n = malloc(sizeof(node));
n->left = NULL;
n->right = NULL;
n->parent = NULL;
n->info = info;
n->color = Red;

return n;
}

red_black_tree* new_red_black_tree() {
red_black_tree *t = malloc(sizeof(red_black_tree));
node *nil_node = malloc(sizeof(node));
nil_node->left = NULL;
nil_node->right = NULL;
nil_node->parent = NULL;
nil_node->color = Black;
nil_node->info = 0;
t->NIL = nil_node;
t->root = t->NIL;

return t;
}

void left_rotate(red_black_tree *t, node *x) {
node *y = x->right;
x->right = y->left;
if(y->left != t->NIL) {
  y->left->parent = x;
}
y->parent = x->parent;
if(x->parent == t->NIL) { //x is root node
  t->root = y;
}
else if(x == x->parent->left) { //x is left child
  x->parent->left = y;
}
else { //x is right child
  x->parent->right = y;
}
y->left = x;
x->parent = y;
}

void right_rotate(red_black_tree *t, node *x) {
node *y = x->left;
x->left = y->right;
if(y->right != t->NIL) {
  y->right->parent = x;
}
y->parent = x->parent;
if(x->parent == t->NIL) { //x is root node
  t->root = y;
}
else if(x == x->parent->right) { //x is left child
  x->parent->right = y;
}
else { //x is right child
  x->parent->left = y;
}
y->right = x;
x->parent = y;
}

void insertion_fixup(red_black_tree *t, node *z) {
while(z->parent->color == Red) {
  if(z->parent == z->parent->parent->left) { //z.parent is the left child

    node *y = z->parent->parent->right; //uncle of z

    if(y->color == Red) { //case 1
      z->parent->color = Black;
      y->color = Black;
      z->parent->parent->color = Red;
      z = z->parent->parent;
    }
    else { //case2 or case3
      if(z == z->parent->right) { //case2
        z = z->parent; //made z.parent as new z
        left_rotate(t, z);
      }
      //case3
      z->parent->color = Black; //made parent black
      z->parent->parent->color = Red; //made parent red
      right_rotate(t, z->parent->parent);
    }
  }
  else { //z.parent is the right child
    node *y = z->parent->parent->left; //uncle of z

    if(y->color == Red) {
      z->parent->color = Black;
      y->color = Black;
      z->parent->parent->color = Red;
      z = z->parent->parent;
    }
    else {
      if(z == z->parent->left) {
        z = z->parent; //made z.parent as new z
        right_rotate(t, z);
      }
      z->parent->color = Black; //made parent black
      z->parent->parent->color = Red; //made parent red
      left_rotate(t, z->parent->parent);
    }
  }
}
t->root->color = Black;
}

void insert(red_black_tree *t, node *z) {
node* y = t->NIL; //variable for the parent of the added node
node* temp = t->root;

while(temp != t->NIL) {
  y = temp;
  if(z->info < temp->info)
    temp = temp->left;
  else
    temp = temp->right;
}
z->parent = y;

if(y == t->NIL) { //newly added node is root
  t->root = z;
}
else if(z->info < y->info) //info of child is less than its parent, left child
  y->left = z;
else
  y->right = z;

z->right = t->NIL;
z->left = t->NIL;

insertion_fixup(t, z);
}

void inorder(red_black_tree *t, node *n) {
if(n != t->NIL) {
  inorder(t, n->left);
  printf("%d\n", n->info);
  inorder(t, n->right);
}
}

void RedBlackTreeInsertion()
{
    red_black_tree *t = new_red_black_tree();

printf("Enter the number of nodes needs to be inserted \n ");
	int k,x;
	scanf("%d",&k);
	int Value;
	// Input The Nodes of The RedBlack Tree
	printf("Enter the values of the corresponding nodes \n");
	for(int i=0;i<k;i++)
	{
		scanf("%d",&Value);
		x =new_node(Value);
		insert(t,x);
	}
printf("\nFinal Tree after insertion of nodes is\n");
inorder(t, t->root);

}
int main()
{
RedBlackTreeInsertion();
return 0;
}
