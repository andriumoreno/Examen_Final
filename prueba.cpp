#include<stdio.h>
#include<stdlib.h>
using namespace std;

void graficar();
void graficarArreglo();
void graficarSPL();


int datos[] = {5, 10, 96, 30, 2, 63,85,47,20,3,4,19};
int spl[100];


struct node
{
	int key;
	struct node *left, *right;
};

struct node* newNode(int key)
{
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->key = key;
	node->left = node->right = NULL;
	return (node);
}


struct node *rightRotate(struct node *x)
{
	struct node *y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}


struct node *leftRotate(struct node *x)
{
	struct node *y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}


struct node *splay(struct node *root, int key)
{
	
	if (root == NULL || root->key == key)
		return root;

	
	if (root->key > key)
	{
		if (root->left == NULL) return root;

		
		if (root->left->key > key)
		{
			
			root->left->left = splay(root->left->left, key);

		
			root = rightRotate(root);
		}
		else if (root->left->key < key) 
		{
			
			root->left->right = splay(root->left->right, key);

			if (root->left->right != NULL)
				root->left = leftRotate(root->left);
		}

		return (root->left == NULL)? root: rightRotate(root);
	}
	else 
	{
	
		if (root->right == NULL) return root;

	
		if (root->right->key > key)
		{
			
			root->right->left = splay(root->right->left, key);

			
			if (root->right->left != NULL)
				root->right = rightRotate(root->right);
		}
		else if (root->right->key < key)
		{
			
			root->right->right = splay(root->right->right, key);
			root = leftRotate(root);
		}

		
		return (root->right == NULL)? root: leftRotate(root);
	}
}

struct node *insert(struct node *root, int k)
{
	
	if (root == NULL) return newNode(k);

	
	root = splay(root, k);

	
	if (root->key == k) return root;

	struct node *newnode = newNode(k);


	if (root->key > k)
	{
		newnode->right = root;
		newnode->left = root->left;
		root->left = NULL;
	}

	else
	{
		newnode->left = root;
		newnode->right = root->right;
		root->right = NULL;
	}

	return newnode; 
}


void preOrder(struct node *root, int index)
{

	if (root != NULL)
	{
    spl[index]=root->key;
		printf("%d ", root->key);
		preOrder(root->left,index*2);
		preOrder(root->right,(index*2)+1);
	}
}





void graficar()
{
  graficarArreglo();
  graficarSPL();

  system("dot -Tpng -oarreglo.png arreglo.txt");
  system("dot -Tpng -ospl.png spl.txt");
}

void graficarArreglo()
{
  FILE* file = fopen("arreglo.txt", "w");
  fprintf(file, "digraph G {\n node[shape=record];\narray[label=\"x");
  for(int i = 1; i < sizeof(spl)/sizeof(int); i++)
  {
    if(spl[i] != -1)
      fprintf(file, "|%d", spl[i]);
    else
      fprintf(file, "|");
  }
  fprintf(file, "\"];\n}");
  fclose(file);
}

void graficarSPL()
{
  FILE* file = fopen("spl.txt", "w");
  fprintf(file, "digraph G {\n");

  if(spl[1] != -1)
  {
    fprintf(file, "%d\n", spl[1]);

    for(int i = 2; i < sizeof(spl)/sizeof(int); i++)
    {
      if(spl[i] != -1)
        fprintf(file, "%d->%d\n", spl[i/2], spl[i]);
    }
  }
  fprintf(file, "}");
  fclose(file);
}

int main()
{
    struct node *root =newNode(datos[0]);
    for(int i = 0; i < sizeof(spl)/sizeof(int); i++)
    {
      spl[i]=-1;
    }
    for(int i = 1; i < sizeof(datos)/sizeof(int); i++)
    {
      root=insert(root,datos[i]);
    }
    preOrder(root,1);
    graficar();
}
