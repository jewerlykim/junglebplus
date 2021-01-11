#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4

typedef struct _NODE{
    int key_count; // 키 개수
    int key[N]; // 하나 여유분 
    struct _NODE *child[N+1]; // 자식도 여유분   
    struct _NODE *parent;

}NODE;


void up(int key, NODE *curr, NODE **root);
void insert_node(NODE *curr, int curr_key, NODE **root);
void delete_node(NODE *curr, int curr_key, NODE **root);
NODE *split_node(NODE *curr);
NODE *search_node(NODE *curr, int key, int *answer, int *level);

void delete_node(NODE *curr, int curr_key, NODE **root){
    int answer[5] = {0};
    int level = 0;
    NODE *tmp = search_node(curr, curr_key, answer, &level);
    if (tmp==NULL) { // 아예 존재안하는데 찾게 만들었어 정말 킹받는다;;
        printf("\n해당하는 인덱스가 존재하지 않습니다.");
    }
    else{ // 존재한다;; 이것도 힘들어;;
        if (tmp->child[0]==NULL) { // 자식이 없네????

            int idx = -1; // 혹시모를 오류확인을 위한 flag...!
            for (int i=0; i<(tmp->key_count); i++) { // 키에서 자신을 찾는다.. 나를 찾는 여행...
                if (tmp->key[i]==curr_key) {
                    idx = i;
                }
            }
            for (int j=idx;j<(tmp->key_count);j++) { // 땡겨주기 baby~~
                tmp->key[j] = tmp->key[j+1];
            } // ##########################여기까지 문제없음#######################


            (tmp->key_count)--; // 키 개수 하나 줄여줌 이게 끝일까? 과연???


            if ((tmp->key_count)>=(N-N/2-1)) { // 지웠을때에도 최소길이를 만족해요^~^
                return;
            }
            else{ // 지웠을때 최소길이 만족이 안됨;;;;;;;;;;;;;;;;;;;;;고난 시작
                if (tmp->parent==NULL) { // 부모 없음
                    return; //사실 난 자식도없었고 부모도 없었다 ㅎㅎ;;
                }
                else { // 부모가 있엉!
                    int child_idx = 0;
                    for (int i=0;i <= tmp->parent->key_count;i++){ // 나를 찾아줘..
                        if (tmp->parent->child[i] == tmp) { //너는 내 자식이 아니란다...
                            child_idx = i;
                        }
                    }

                    if (child_idx == tmp->parent->key_count) { //내가 막내라니???~!!~
                        NODE * left_sibling = tmp->parent->child[child_idx-1];
                        left_sibling->key[left_sibling->key_count] = tmp->parent->key[child_idx-1];
                        (tmp->parent->key_count)--; // 나중에 부모 다 없어졌는지 확인해야대;; 언제 누가하는데? 바로 나
                        (left_sibling->key_count)++;
                        for (int i=0; i<tmp->key_count;i++){
                            left_sibling->key[left_sibling->key_count]=tmp->key[i];
                            (left_sibling->key_count)++;
                        } 
                        free(tmp);
                        //  left sibling이 다 찼는지 확인해서 다 찼으면 up 을 해줘
                        if ((left_sibling->key_count)>=(N)) {
                            up(left_sibling->key[N/2],left_sibling,root);
                        }
                    }
                    else { //나 뫅놰 아닌뒙?;;;
                        NODE * right_sibling = tmp->parent->child[child_idx+1];
                        tmp->key[tmp->key_count] = tmp->parent->key[child_idx];
                        (tmp->key_count)++;
                        (tmp->parent->key_count)--;
                        for (int i=0; i < right_sibling->key_count; i++) {
                            tmp->key[tmp->key_count] = right_sibling->key[i];
                            (tmp->key_count)++;
                        }
                        free(right_sibling);
                        for (int i = child_idx; i<tmp->parent->key_count;i++){
                            tmp->parent->key[i]=tmp->parent->key[i+1]; // 부모 왼쪽으로 1보 이동!
                            tmp->parent->child[i+1] = tmp->parent->child[i+2]; // 자식들도 이동!
                        }

                        if ((tmp->key_count)>=(N)) { //내가 꽉찼어!!!~!~!~!~!~
                            up(tmp->key[N/2],tmp,root);
                        }
                        

                    }
                    
                }
                if ((tmp->parent->key_count)<(N-N/2-1)) { // 부모 가 최소개수가 안돼...
                    
                }

            }

        }
        else { // 자식이 있네??? 무자식상팔자인데 ㅉㅉ;;;

        }
    }


}


NODE *search_node(NODE *curr, int key, int *answer, int *level){
    // 만약 tree를 만들지 않고 search 할 경우
    if (curr->key_count == 0){
        printf("먼저 키를 삽입해주세요.");
        return NULL;
    }
    int i;
    for (i = 0; i < curr->key_count; i++){ // 
        if (curr->key[i] == key) {
            answer[*level] = i;
            printf("() ()\n");
            printf("(>_<) 찾았습니당! 요기요 : ");
            return curr;
        }
        if (curr->key[i] > key) {
            if (curr->child[0] == 0){
                printf("없어요 ㅡㅡ");
                return NULL;
            }
            answer[*level] = i;
            (*level)++;
            return (search_node(curr->child[i], key, answer, level));
            break;
        }
    }
    if (i == curr->key_count){
        if (curr->child[0] == 0){
            printf("없어요 ㅡㅡ");
            return NULL;
        }
        answer[*level] = i;
        (*level)++;
        return (search_node(curr->child[i], key, answer, level));
    }
    return NULL;
}



NODE *split_node(NODE *curr){ // UP함수의 공통 루틴
    curr->key_count = N/2; // 현재(왼쪽) 구조체 사이즈 줄이기
    NODE *right_node = (NODE *)malloc(sizeof(NODE)); // 오른쪽 잘린 놈 만들기 
    right_node->parent = curr->parent; 
    right_node->key_count = N-N/2-1; 
    for (int i = (N/2)+1; i<=N-1; i++){
        right_node->key[i-(N/2)-1] = curr->key[i]; 
    }
    for (int i = 0; i < N-(N/2); i++){
        right_node->child[i] = curr->child[i+N/2+1];
        if (curr->child[i+N/2+1] != NULL) 
            curr->child[i+N/2+1]->parent = right_node;
    }    
    return right_node; // 오른쪽 노드 주소값 리턴 
}

void up(int key, NODE *curr, NODE **root){
    if (curr->parent == NULL){ // 부모가 없을 때 
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
            if (curr->parent->child[i] == curr){  //날 가리키는 값 찾음 
                idx = i; 
                break; 
            }
        }
        for (int i = curr->parent->key_count; i> idx; i--){ // 부모 밀기 
            curr->parent->key[i] = curr->parent->key[i-1];
            curr->parent->child[i+1] = curr->parent->child[i];
        }

        (curr->parent->key_count)++; 
        curr->parent->key[idx] = key;  // 빈 공간에 key 넣음 
        curr->parent->child[idx+1] = split_node(curr); // 오른쪽 분할 된 노드 연결 
        if (curr->parent->key_count==N){
            up(curr->parent->key[N/2], curr->parent, root);
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
            up(curr->key[N/2], curr, root); 
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

// void visualizing(NODE *curr, int depth, int flag, char *space){
//     int i;
//     if (depth != 0){
//         if (flag == 0)
//             printf(" 왼 ");
//         else 
//             printf(" 오 ");
//     }

//     for (i = 0; i < curr->key_count; i++){
//         printf("%d", curr->key[i]);
//         if (curr->child[i] != NULL) {
            
//             visualizing(curr->child[i], depth + 1, 0);
//         }
//     }
//     printf("\n");
//     if (curr->child[i] != NULL)
//         visualizing(curr->child[i], depth + 1, 1);
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
    int key11 = 70;
    int key12 = 62;
    int key13 = 63;
    int key14 = 64;
    int key15 = 65;
    int key16 = 66;
    int key17 = 67;
    int key18 = 68;
    int key19 = 69;    
    
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
    insert_node(root, key11, &root);
    insert_node(root, key12, &root);
    insert_node(root, key13, &root);
    insert_node(root, key14, &root);
    // insert_node(root, 35, &root);
    insert_node(root, key15, &root);
    insert_node(root, key16, &root);
    insert_node(root, key17, &root);
    insert_node(root, key18, &root);
    insert_node(root, key19, &root);

    // printf("%d", root->child[0]->child[0]->key[0]);
    
    int key_tmp = 34;
    int answer[5] = {0};
    int level = 0;
    NODE *tmp = search_node(root, key_tmp, answer, &level);
    if (tmp != NULL){
        printf("root");
        if (level != 0){
            for (int i=0; i < level; i++){
                if (i != level)
                    printf("->");
                printf("%d", answer[i]);
            }
        }
        printf(": %d번 자리", answer[level] + 1);
    }
    printf("\n");
    // printf("%d",root->child[1]->key[1]);

    delete_node(root, key_tmp, &root);
    int second_answer[5] = {0};
    level = 0;
    NODE *ttmp = search_node(root, 33, second_answer, &level);
    if (ttmp != NULL){
        printf("root");
        if (level != 0){
            for (int i=0; i < level; i++){
                if (i != level)
                    printf("->");
                printf("%d", second_answer[i]);
            }
        }
        printf(": %d번 자리", second_answer[level] + 1);
    }
    printf("\n");
    // visualizing(root, 0, 0, " ");
}