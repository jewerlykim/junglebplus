#include <stdio.h>
#include <stdlib.h>
#define N 4 

typedef struct _NODE{

    struct _NODE *child[N]; 
    int key[N]; // 하나 여유분  
    struct _NODE *parent;
    int key_count; // 키 개수

}NODE;

void insert_node(NODE *curr, int curr_key){
    
    if (curr->child[0] == NULL){ // 리프일 때 
        // 키 개수 세기 및 대소 비교 
       curr->key[curr->key_count] = curr_key;
       for (int i = (curr->key_count)-1; i>=0; i--){
           if (curr->key[i] >= curr->key[i+1]){// 대소 비교 
                int tmp=curr->key[i]; 
                curr->key[i] = curr->key[i+1]; 
                curr->key[i+1] = tmp; 
           }
           else
            break;   
       }
       curr->key_count++; 
       if (curr->key_count == N){

           NODE *left_node = (NODE *)malloc(sizeof(NODE)); 
           left_node->parent = curr; 
           
           // 중간값 n//2
           // create node 
           // 노드 2개 생성 
           
       }
    } 
}

void create_node(int key){
    // key 값 
}

int main(){
    
    NODE *root;
    root = (NODE *)malloc(sizeof(NODE)); // start node 
    root->key_count = 0; 


    // int key = 30;
    // insert_node(root, key); 



    /*
    root = (NODE *)malloc(sizeof(NODE));
    create_node(key);
    delete(3); 
    insert(2); 
    */
}