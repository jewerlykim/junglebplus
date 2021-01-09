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
    curr->key_count = N/2; // 현재(왼쪽) 구조체 사이즈 줄이기
    NODE *right_node = (NODE *)malloc(sizeof(NODE)); // 오른쪽 잘린 놈 만들기 
    right_node->parent = curr->parent; 
    right_node->key_count = N-N/2-1; 
    for (int i = (N/2)+1; i<=N-1; i++){
        right_node->key[i-(N/2)-1] = curr->key[i]; 
    }
    for (int i = 0; i <= N-(N/2); i++){
        right_node->child[i] = curr->child[i+N/2+1];
    }    
    return right_node; // 오른쪽 노드 주소값 리턴 
}

void up(int key, NODE *parent, NODE *curr, NODE **root){
    if (parent == NULL){ // 부모가 없을 때 
        NODE *upper_node = (NODE *)malloc(sizeof(NODE)); // 올라갈 놈 구조체 만들기 
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
        if (parent->key_count==N){
            up(parent->key[N/2], parent->parent, parent, root);
        }
    }
}

void insert_node(NODE *curr, int curr_key, NODE **root){ // curr : 처음엔 root 
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
       
       if (curr->key_count == N){ // 리프에 넣어서 꽉참 
            up(curr->key[N/2], curr->parent, curr, root); 
       }
    } 
    else{ //리프가 아닐 떄 (child 있음)
        NODE *tmp; 
        int flag = 0 ; 
        for (int i = 0 ; i<curr->key_count; i++){
            if (curr->key[i] > curr_key){
                tmp = curr->child[i]; 
                flag = 1; 
                break; 
            }
        }
        if (flag == 0){
            tmp = curr->child[curr->key_count]; 
        } 
        insert_node(tmp, curr_key, root); 
    }
}

// void create_node(int key){
//     // key 값 
// }

int main(){
    
    NODE *root;
    root = (NODE *)malloc(sizeof(NODE)); // start node 
    root->key_count = 0; 

    int key1 = 30;
    int key2 = 40;
    int key3 = 50;
    int key4 = 60;
    int key5 = 41;
    int key6 = 32;
    int key7 = 33;
    int key8 = 34;
    int key9 = 29;
    int key10 = 28;

    
    
    insert_node(root, key1, &root); 
    insert_node(root, key2, &root); 
    insert_node(root, key3, &root); 
    insert_node(root, key4, &root); 
    insert_node(root, key5, &root); 
    insert_node(root, key6, &root); 
    insert_node(root, key7, &root); 
    insert_node(root, key8, &root); 
    insert_node(root, key9, &root); 
    insert_node(root, key10, &root); 

    printf("1 %d\n", root->key[0]);
    // printf("2 %d\n", root->key[1]);
    printf("3ch %d\n", root->child[0]->key[0]);
    printf("4ch %d\n", root->child[0]->key[1]);
    // printf("4ch %d\n", root->child[0]->key[2]);
    printf("5ch %d\n", root->child[1]->key[0]);
    printf("6ch %d\n", root->child[0]->child[0]->key[0]);
    printf("6ch %d\n", root->child[0]->child[0]->key[1]);
    printf("6ch %d\n", root->child[0]->child[1]->key[0]);
    printf("6ch %d\n", root->child[0]->child[2]->key[0]);
    printf("6ch %d\n", root->child[1]->child[0]->key[0]);
    printf("6ch %d\n", root->child[1]->child[1]->key[0]);

    // free 
}