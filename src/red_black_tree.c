#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum { RED, BLACK } Color;

typedef struct tn *tpn;
struct tn
{  
    int key;
    Color c;
    tpn l,r,p;  
};  

typedef struct RedBlackTree *RBT;
struct RedBlackTree
{
	tpn root;
	tpn NIL;
};

RBT T=NULL;

void RB_INSERT();
void RB_INSERT_FIXUP(tpn z);
void LEFT_ROTATE (tpn x);
void RIGHT_ROTATE (tpn x);
void RB_TRANSPLANT (tpn y, tpn x);
void RB_DELETE();
tpn TREE_MINIMUM(tpn x);
void RB_DELETE_FIXUP(tpn x);
void TT(tpn x);
int Height(tpn x); 
tpn **arrays(int height);
void TreeArray(tpn x, tpn **arr, int level, int index, int height);
void PrintTree(int height);



void RB_INSERT()
{
	tpn y=NULL, x=NULL;
	tpn z = (tpn)malloc(sizeof(struct tn));
	if(z==NULL)
    {
    	printf("\n Memory is full. Can't allocate pointer");
    	return;
	}
	y = T->NIL;
	x = T->root;
	int data=0;
	printf("\n Insert number: ");
    scanf("%d", &data);
    getchar();
	z->key = data;
	z->l = NULL;
	z->r = NULL;
	z->p = NULL;
	
	while(x!=T->NIL)
	
	{	y=x;
	
		if(z->key<x->key)
		{
			x=x->l;
		}
		
		else if (z->key>x->key)
		{
			x = x->r;
		}
		else if (z->key == x->key)
		{
			printf("\n Number already exists");
			return;
		}
	}
	
	z->p = y;
	
	if(y==T->NIL)
	{
		T->root = z;
	}
	else if (z->key<y->key)
	{
		y->l = z;
	}
	else {y->r = z;}
	
	z->l = T->NIL;
	z->r = T->NIL;
	z->c = RED;
	
	RB_INSERT_FIXUP(z);
	
}

void RB_INSERT_FIXUP(tpn z)
{
	tpn y=NULL;
	while (z->p->c==RED)
	{
		if (z->p == z->p->p->l)
		{
			y=z->p->p->r;
			
			if (y->c == RED)
			{
				z->p->c = BLACK;
				y->c = BLACK;
				z->p->p->c = RED;
				z = z->p->p;
			}
			
			else 
			{
				if (z==z->p->r)
				{
					z=z->p;
					LEFT_ROTATE (z);
				}
				z->p->c=BLACK;
				z->p->p->c = RED;
				RIGHT_ROTATE (z->p->p);
			}
		}
		
		else 
		{
			y=z->p->p->l;
			
			if (y->c == RED)
			{
				z->p->c = BLACK;
				y->c = BLACK;
				z->p->p->c = RED;
				z = z->p->p;
			}
			
			else 
			{
				if (z==z->p->l)
				{
					z=z->p;
					RIGHT_ROTATE (z);
				}
				z->p->c=BLACK;
				z->p->p->c = RED;
				LEFT_ROTATE (z->p->p);
			}
		}
	}
	
	T->root->c =BLACK;
}

void LEFT_ROTATE (tpn x)
{
	tpn y=NULL;
	y = x->r;
	x->r = y->l;
	
	if (y->l != T->NIL)
	{
		y->l->p = x;
	}
	
	y->p = x->p;
	
	if (x->p == T->NIL)
	{
		T->root = y;
	}
	else if (x==x->p->l)
	{
		x->p->l = y;
	}
	else {x->p->r = y;}
	
	y->l=x;
	x->p=y;
}


void RIGHT_ROTATE (tpn x)
{
	tpn y=NULL;
	y = x->l;
	x->l = y->r;
	
	if (y->r != T->NIL)
	{
		y->r->p = x;
	}
	
	y->p = x->p;
	
	if (x->p == T->NIL)
	{
		T->root = y;
	}
	else if (x==x->p->r)
	{
		x->p->r = y;
	}
	else {x->p->l = y;}
	
	y->r=x;
	x->p=y;
}

void RB_TRANSPLANT (tpn y, tpn x)
{
	if (y->p==T->NIL)
	{
		T->root = x;
	}
	
	else if (y==y->p->l)
	{
		y->p->l = x;
	}
	
	else {y->p->r = x;}
	x->p=y->p;
}

tpn TREE_MINIMUM(tpn x)
{
	while (x->l!=T->NIL)
	{
		x=x->l;
	}
	return x;
}


void RB_DELETE()
{
	tpn y=NULL, x=NULL;
	tpn z = NULL;
	int data=0;
	printf("\n Which number do you want to delete? ");
    scanf("%d", &data);
    getchar();
    z = T->root;
    while (z!=T->NIL && z->key !=data)
    {
    	if (data < z->key)
    	{
    		z = z->l;
		}
		else {z = z->r;}
	}
	if (z!=T->NIL)
	{
		y = z;
		Color y_original_color = y->c;
	
		if (z->l == T->NIL)
		{
			x = z->r;
			RB_TRANSPLANT(z, z->r);
		}
		else if (z->r == T->NIL)
		{
			x = z->l;
			RB_TRANSPLANT(z, z->l);
		}
		else 
		{
			y = TREE_MINIMUM(z->r);
			y_original_color = y->c;
			x = y->r;
		
			if (y->p == z)
			{
				x->p = y;
			}
			else
			{
				RB_TRANSPLANT(y,y->r);
				y->r = z->r;
				y->r->p = y;
			}
		
			RB_TRANSPLANT(z,y);
			y->l = z->l;
			y->l->p = y;
			y->c = z->c;
		}
	
		if (y_original_color == BLACK)
		{
			RB_DELETE_FIXUP(x);
		}
		free(z);
	}
    else { printf ("\n Number not found in the tree. \n");}
}

void RB_DELETE_FIXUP(tpn x)
{
	tpn y=NULL;
	while (x!=T->root && x->c == BLACK)
	{
		if (x==x->p->l)
		{
			y = x->p->r;
			
			if (y->c == RED)
			{
				y->c = BLACK;
				x->p->c = RED;
				LEFT_ROTATE(x->p);
				y=x->p->r;
			}
			
			if (y->l->c == BLACK && y->r->c == BLACK)
			{
				y->c = RED;
				x = x->p;
			}
			
			else 
			{
				if (y->r->c ==  BLACK)
				{
					y->l->c = BLACK;
					y->c = RED;
					RIGHT_ROTATE(y);
					y = x->p->r;
				}
				
				y->c = x->p->c;
				x->p->c = BLACK;
				y->r->c = BLACK;
				LEFT_ROTATE(x->p);
				x=T->root;
			}
		}
		
		else 
		{
			y = x->p->l;
			
			if (y->c == RED)
			{
				y->c = BLACK;
				x->p->c = RED;
				RIGHT_ROTATE(x->p);
				y=x->p->l;
			}
			
			if (y->r->c == BLACK && y->l->c == BLACK)
			{
				y->c = RED;
				x= x->p;
			}
			
			else 
			{
				if (y->l->c ==  BLACK)
				{
					y->r->c = BLACK;
					y->c = RED;
					LEFT_ROTATE(y);
					y = x->p->l;
				}
				
				y->c = x->p->c;
				x->p->c = BLACK;
				y->l->c = BLACK;
				RIGHT_ROTATE(x->p);
				x=T->root;
			}
		}
	}
	x->c = BLACK;
}


int Height(tpn x) 
{
	int maxHeight=0;
    if (x == T->NIL) 
	{
        return 0;
    }

    int leftHeight = Height(x->l);
    int rightHeight = Height(x->r);
    
    if (leftHeight>rightHeight)
    {
    	maxHeight = leftHeight;
	}
	else
	{
		maxHeight = rightHeight;
	}
	
	return (maxHeight + 1);
}

void TT(tpn x)
{
	if(T->root==T->NIL)
    {
    	printf("\n The tree is empty \n");
	}
	else
	{
		if(x!=T->NIL)
		{
			TT(x->l);
			printf("\n %d: [Parent: %d, Left: %d, Right: %d] (%s)", x->key, x->p->key, x->l->key, x->r->key, x->c ==RED ? "RED" : "BLACK");
			TT(x->r);
		}
	}
}



tpn **arrays(int height)
{
	int i,j;
	tpn **arr = (tpn**)malloc(height * sizeof(tpn*));
	for (i = 0; i < height; i++)
	{
		arr[i] = (tpn*)malloc((pow(2, i)) * sizeof(struct tn));
		
		for(j=0;j<pow(2,i);j++)
		{
			arr[i][j]=NULL;
		}
	}
	return arr;
}

void TreeArray(tpn x, tpn **arr, int level, int index, int height)
{
	int i,j;
	
	if(x==T->NIL || level >=height)
	{
		return;
	}
	arr[level][index] = x;

	TreeArray(x->l, arr, level+1, 2*index, height);
	TreeArray(x->r, arr, level+1, 2*index+1, height);
}

void PrintTree(int height)
{
	int i,j;

	tpn **arr = arrays(height);
	
	TreeArray(T->root, arr, 0,0, height);
	
	for(i=0; i<height;i++)
	{
		printf("\nLevel %d: ", i+1);
		
		for(j=0; j<pow(2, i); j++)
		{
			if(arr[i][j] !=NULL)
			{
				printf("%d(%s),", arr[i][j]->key, arr[i][j]->c ==RED ? "R" : "B");
			}
			else
			{
				printf("-,");
			}
		}
		
	}

 	for (i = 0; i < height; i++) 
	{
        free(arr[i]);  
    }

	free(arr);
	
	printf("\n");
	
}


int main(void)
{
	int sel=0;
	int height=0;
    
    T = (RBT)malloc(sizeof(struct RedBlackTree));
    if(T==NULL)
    {
    	printf("\n Memory is full. Can't allocate pointer");
    	return 1;
	}
    T->NIL = (tpn)malloc(sizeof(struct tn));
    if(T->NIL==NULL)
    {
    	printf("\n Memory is full. Can't allocate pointer");
    	return 1;
	}
	T->NIL->key=0;
	T->NIL->l = T->NIL;
	T->NIL->r = T->NIL;
    T->NIL->c = BLACK;
    T->root = T->NIL;
    
    while(sel!=4)
    {
    	printf("\n\n Menu selections \n");
   		printf("\n-------------------\n");
   		printf("\n 1. Insert \n");
   		printf("\n 2. Print \n");
   		printf("\n 3. Delete \n");
   		printf("\n 4. Exit \n");
    	printf("\n Enter choice: ");
    	scanf("%d", &sel);
    	getchar();
    	
    	switch(sel)
    	{
    		case 1:
				RB_INSERT();
    		break;
    		
    		case 2:
    			{
    				height=Height(T->root);
    				printf("\n Height: %d \n", height-1);
    				PrintTree(height);
    				TT(T->root);
    			}
    		break;
    		
    		case 3:
    				RB_DELETE();
    		break;
    		
    		case 4:
    				return 0;
    		break;
    		
    		default:
    			printf("\n This choice does not exist \n");
    		break;
    			
		}
	}

return 0;
	
}
