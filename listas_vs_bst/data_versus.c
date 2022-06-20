#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SIZE_MAX 1000


struct list  {
    int values[SIZE_MAX]; 
};
typedef struct list list_t; //lista

struct BT  {
    int val;
    struct BT* left;
    struct BT* right;
};
typedef struct BT binaryt_t; //binary tree

//assinaturas das funções aqui 

void fill_list(list_t* l); //preenche a lista "aleatoriamente"

void print_list(list_t* l); 

int search_list(list_t* l, int n); //busca o numero escolhido na lista (linearmente)

binaryt_t* make_binary_tree();

void add_bin_tree_node(binaryt_t* root, int n); //add node na arvore

void print_tree(binaryt_t* root, int level);

int search_tree(binaryt_t* bst, int n); //busca o numero escolhido na arvore binaria (bst)

//main
int main()    {
    srand(time(NULL));
    int choosen_num = rand()%SIZE_MAX;
    printf("choosen: %d\n", choosen_num);
    
    list_t lista;
    fill_list(&lista);
    print_list(&lista);

    binaryt_t bst;
    bst.val = lista.values[0];
    bst.left = NULL;
    bst.right = NULL;

    for (int i = 1; i < SIZE_MAX; i++)  {
        add_bin_tree_node(&bst, lista.values[i]);
    }

    print_tree(&bst, 0);

    return 0;
}

//declaração das funcs

void fill_list(list_t* l)   {
    for (int i = 0; i < SIZE_MAX; i++)    {
        l->values[i] = rand()%SIZE_MAX;
        //printf("%dst choosen: %d\n", i+1, rand()); //mostra os sorteados pra formar a lista
    }
}

void print_list(list_t* l)  {
    
    printf("lista:\n[ ");
    for (int i = 0; i < SIZE_MAX; i++)  {
        printf("%d - ", l->values[i]);
    }
    printf("\b\b]\n");

    return;
}

void print_tree(binaryt_t* root, int level) {
    if (!root) {
        return;
    }
    for (int i = 0; i < level-1; i++) {
        printf(i!=0?"|   ":"    ");
    }


    printf("|--{%d\n", root->val);
    print_tree(root->left, level + 1);
    print_tree(root->right, level + 1);

    
}

void add_bin_tree_node(binaryt_t* root, int n)  {
    binaryt_t* new_node = (binaryt_t*) malloc(sizeof(binaryt_t));
    new_node->val = n;
    new_node->left = NULL;
    new_node->right = NULL;

    int is_left = 0;
    binaryt_t* previous_node;
    while (root != NULL) {
        previous_node = root;
        if (root->val >= new_node->val) {
            root = root->left;
            is_left = 1;
        }
        else {
            root = root->right;
            is_left = 0;
        }
        
    }
    if (is_left) previous_node->left = new_node;
    else previous_node->right = new_node;

    return;
}