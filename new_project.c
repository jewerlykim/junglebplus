#include <stdio.h>
#include <stdlib.h>
#define N 4 

typedef struct _NODE{

    struct _NODE *child[N+1]; // 자식도 여유분  
    int key[N]; // 하나 여유분  
    struct _NODE *parent;
    int key_count; // 키 개수

}NODE;

NODE *split_node(NODE *curr){ // UP함수의 공통 루틴
    curr->key_count = N/2; // 현재 구조체 사이즈 줄이기
    NODE *right_node = (NODE *)malloc(sizeof(NODE)); // 오른쪽 잘린 놈 만들기 
    right_node->parent = curr->parent; 
    right_node->key_count = N-N/2-1; 
    for (int i = (N/2)+1; i<N-1; i++){
        right_node->key[i] = curr->key[i-(N/2)-1]; 
    }    
    return right_node;
}

void up(int key, NODE *parent, NODE *curr, NODE **root){
    if (parent == NULL){
        // 올라갈 놈 구조체 만들기 
        NODE *upper_node = (NODE *)malloc(sizeof(NODE)); 
        curr->parent = upper_node;
        upper_node->child[0] = curr; 
        upper_node->child[1] = split_node(curr);  
        upper_node->key[0] = key; 
        upper_node->key_count = 1; 
        *root = upper_node; 
    }
    else{// 부모가 있을 때 
        int idx; 
        for (int i = 0 ; i < N+1; i++){
            if (parent->child[i] == curr){  //날 가리키는 값 찾음 
                idx = i; 
                break; 
            }
        }
        for (int i = parent->key_count; i> idx; i--){ // 부모 밀기 
            parent->key[i] = parent->key[i-1];
            parent->child[i+1] = parent->child[i];
        }
        parent->key_count++; 
        parent->key[idx] = key;  // 빈 공간에 key 넣음 
        parent->child[idx+1] = split_node(curr); // 오른쪽 분할 된 노드 연결 

        // 부모 키카운드 다찼는지 확인 
    }
}

void insert_node(NODE *curr, int curr_key){
    
    if (curr->child[0] == NULL){ // 리프일 때 
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
       
       if (curr->key_count == N){ // 리프인데 카운트 다 참 UP
        //    if (curr->parent == NULL){  // 부모가 없을 때 
        //         NODE *left_node = (NODE *)malloc(sizeof(NODE)); 
        //         left_node->parent = curr; 
        //         left_node->key_count = N/2; 
        //         for (int i = 0; i<(N/2); i++){
        //             left_node->key[i] = curr->key[i]; 
        //         }

        //         NODE *right_node = (NODE *)malloc(sizeof(NODE)); 
        //         right_node->parent = curr; 
        //         right_node->key_count = N-N/2-1; 
        //         for (int i = (N/2)+1; i<N-1; i++){
        //             right_node->key[i] = curr->key[i-(N/2)-1]; 
        //         }
        //         curr->key[0] = curr->key[N/2]; // 중간값 맨 앞으로 이동
        //         curr->key_count = 1;  

        //         curr->child[0] = left_node; // curr 왼쪽 오른쪽 자식으로 붙여줌 
        //         curr->child[1] = right_node;
        //    }
        //    else{ // 리프인데 부모가 있을 때 
        //         // 올라 가야해 
        //         // merge 함수를 만들어보자 (재귀)
        //         // 키가 다 찼니?, 자식이 다 찼니? 
        //         // split 올라갈 인덱스와 키 
        //         // up(key, parent)
        //         // 내려갔는데 꽉 찼다면 up 
           }
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