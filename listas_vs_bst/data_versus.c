#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define RERUNS 100
#define SIZE_MAX 2000 //define o tamanho da pool do sorteio e das estruturas estaticamente

//estruturas aqui
struct list  {
    int values[SIZE_MAX]; 
};
typedef struct list list_t; //lista

struct BT  {
    int val; //(==)
    struct BT* left; //(<=)
    struct BT* right; //(>)
};
typedef struct BT binaryt_t; //binary tree


//assinaturas das funções aqui 
void fill_list(list_t* l); //preenche a lista "aleatoriamente"

void add_bst_node(binaryt_t* root, int n); //add uma nova arvore no branch respectivo da arvore

int search_list(list_t* l, int n); //busca o numero escolhido na lista (linearmente), retorna o numero de passos

int search_tree(binaryt_t* bst, int n); //busca o numero escolhido na arvore binaria (bst), retorna o numero de passos

void print_list(list_t* l); 

void print_tree(binaryt_t* root, int level);

//main
int main()    {

    int data[RERUNS][3]; //guarda a simulação
    srand(time(NULL)); //seed pra gerar os nums aleatorios

    printf("se os passos estiverem negativos, entao nao foi achado o valor, e os passos representam a busca completa.\n");

    for (int turn = 0; turn < RERUNS; turn++) { //repete
        //setando o numero a ser sorteado
        int choosen_num = rand()%SIZE_MAX;
        printf("\n----------------------\nchoosen: %d", choosen_num);
        
        //inicializando a lista
        list_t lista;
        fill_list(&lista); //preenchendo a lista aleatoriamente

        //inicializando a arvore binaria
        binaryt_t bst;
        bst.val = lista.values[0];
        bst.left = NULL;
        bst.right = NULL;
        for (int i = 1; i < SIZE_MAX; i++)  { //preenchendo ela de acordo com a regra para ser uma BST, com os mesmos valores da lista.
            add_bst_node(&bst, lista.values[i]);
        }

        // descomentar caso queira verificar os resultados na mão
        //print_list(&lista); 
        //print_tree(&bst, 1);

        int bst_results = search_tree(&bst, choosen_num);
        int lista_results = search_list(&lista, choosen_num);
        data[turn][0] = bst_results;
        data[turn][1] = lista_results;
        data[turn][2] = SIZE_MAX;

        printf("\nbusca na BST: %d steps\nbusca na lista: %d steps\n", bst_results, lista_results); //resultados
    }

    FILE *fp;
    fp = fopen("./results/fixed_size_set.csv", "w+");
    fprintf(fp, "bst,lista,st_size\n");
    for (int i = 0; i < RERUNS; i++)  { // resumo
        printf("turn %d - bst:%d, lista:%d\n", i+1, data[i][0], data[i][1]);
        fprintf(fp, "%d,%d\n", data[i][0], data[i][1]);
    }
    fclose(fp);

    return data;
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

void print_tree(binaryt_t* root, int level) { //print recursivo da arvore com niveis (preordem)
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

void add_bst_node(binaryt_t* root, int n)  {
    //cria o node
    binaryt_t* new_node = (binaryt_t*) malloc(sizeof(binaryt_t));
    new_node->val = n;
    new_node->left = NULL;
    new_node->right = NULL;

    int is_left = 0; //decide qual lado vai jogar o node
    binaryt_t* previous_node;
    while (root != NULL) { //ate chegar no fim de um node
        previous_node = root; // lembra o ultimo node caminhado
        if (root->val >= new_node->val) { //o valor do node atual é maior que do novo
            root = root->left; //vai pra esquerda
            is_left = 1;
        }
        else { //direita
            root = root->right;
            is_left = 0;
        }
        
    }
    if (is_left) previous_node->left = new_node; //se for pra esquerda no final, coloca o novo node lá
    else previous_node->right = new_node;

    return;
}

int search_list(list_t* l, int n)   {
    int i = 0;
    for (; i < SIZE_MAX; i++)  {
        if (l->values[i] == n) return i+1;  //achou, retorna os passos
    }
    return -i; //não achou, retorna o negativo dos passos
}

int search_tree(binaryt_t* bst, int n)  {
    for (int i = 0; i < SIZE_MAX; i++)    {
        if (bst == NULL) return -(i+1); //esgotou a busca sem achar
        else if (bst->val == n) return i+1; //achou aqui
        else if (n > bst->val) bst = bst->right; //num é maior, vai pra direita
        else bst = bst->left; //num é menor ou igual, vai pra esquerda
    }

    return 0; //deu ruim, em teoria isso aqui nunca pode acontecer
}