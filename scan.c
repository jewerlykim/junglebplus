#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>


#define N 3

typedef struct _NODE{
    int key_count; // Ű ����
    int key[N]; // �ϳ� ������ 
    struct _NODE *child[N+1]; // �ڽĵ� ������   
    struct _NODE *parent;

}NODE;


void up(int key, NODE *curr, NODE **root);
void insert_node(NODE *curr, int curr_key, NODE **root);
void delete_node(NODE *curr, int curr_key, NODE **root);
void reculsive_delete(NODE *curr, NODE **root);
NODE *split_node(NODE *curr);
NODE *search_node(NODE *curr, int key, int *answer, int *level);
NODE *search_leftbig(NODE *curr);

NODE *search_leftbig(NODE *curr) { // ��� ;;;
    if (curr->child[0]==NULL) { // ���� ������.........
        return curr;
    }
    else {
        return search_leftbig(curr->child[curr->key_count]);
    }
}

void reculsive_delete(NODE *curr, NODE **root){ // �ݺ��Ǵ� ��.. �����... 
            NODE *tmp;
    
            if ((curr->key_count)>=(N-N/2-1)) { // ������������ �ּұ��̸� �����ؿ�^~^
                return;
            }
            else{ // �������� �ּұ��� ������ �ȵ�;;;;;;;;;;;;;;;;;;;;;���� ����
                if (curr->parent==NULL) { // �θ� ����
                    return; //��� �� �ڽĵ������� �θ� ������ ����;;
                }
                else { // �θ� �־�!
                    int child_idx = 0;
                    for (int i=0;i <= curr->parent->key_count;i++){ // ���� ã����..
                        if (curr->parent->child[i] == curr) { //�ʴ� �� �ڽ��� �ƴ϶���...
                            child_idx = i;
                        }
                    }

                    if (child_idx == curr->parent->key_count) { //���� �������???~!!~
                        NODE * left_sibling = curr->parent->child[child_idx-1];
                        left_sibling->key[left_sibling->key_count] = curr->parent->key[child_idx-1];
                        (curr->parent->key_count)--; // ���߿� �θ� �� ���������� Ȯ���ؾߴ�;; ���� �����ϴµ�? �ٷ� ��
                        (left_sibling->key_count)++;
                        for (int i=0; i<curr->key_count;i++){
                            left_sibling->key[left_sibling->key_count]=curr->key[i];
                            left_sibling->child[left_sibling->key_count] = curr->child[i];
                            curr->child[i]->parent = left_sibling;
                            (left_sibling->key_count)++;
                        } 
                        left_sibling->child[left_sibling->key_count] = curr->child[curr->key_count];
                        // curr->child[curr->key_count]->parent = left_sibling;
                        // free(curr);
                        tmp = left_sibling;
                        //  left sibling�� �� á���� Ȯ���ؼ� �� á���� up �� ����
                        if ((left_sibling->key_count)>=(N)) {
                            up(left_sibling->key[N/2],left_sibling,root);
                        }
                        
                    }
                    else { //�� ���R �ƴъ�?;;;
                        NODE * right_sibling = curr->parent->child[child_idx+1];
                        curr->key[curr->key_count] = curr->parent->key[child_idx];
                        (curr->key_count)++;
                        (curr->parent->key_count)--;
                        for (int i=0; i < right_sibling->key_count; i++) {
                            curr->key[curr->key_count] = right_sibling->key[i];
                            curr->child[curr->key_count] = right_sibling->child[i];
                            if (right_sibling->child[i]!=NULL) {
                                right_sibling->child[i]->parent = curr;
                            }
                            (curr->key_count)++;
                        }
                        curr->child[curr->key_count] = right_sibling->child[right_sibling->key_count];
                        if (right_sibling->child[right_sibling->key_count]!=NULL) {
                            right_sibling->child[right_sibling->key_count]->parent = curr;
                        }
                        // free(right_sibling);
                        for (int i = child_idx; i<curr->parent->key_count;i++){
                            curr->parent->key[i]=curr->parent->key[i+1]; // �θ� �������� 1�� �̵�!
                            curr->parent->child[i+1] = curr->parent->child[i+2]; // �ڽĵ鵵 �̵�!
                        }
                        tmp = curr;

                        if ((curr->key_count)>=(N)) { //���� ��á��!!!~!~!~!~!~
                            up(curr->key[N/2],curr,root);
                        }
                    }
                }
                if ((curr->parent->key_count)<(N-N/2-1)) { // �θ� �� �ּҰ����� �ȵ�...
                    if (curr->parent->parent==NULL) {// �� �θ� �ܱ��̶��!!!!!!! ���� �� ���� �ܱ��̿� ���� ;;
                        if (curr->parent->key_count==0) {
                            *root = tmp;
                            tmp->parent = NULL;
                        }
                        return;
                    }
                    reculsive_delete(curr->parent,root);
                }
            }
}


void delete_node(NODE *curr, int curr_key, NODE **root){
    int answer[5] = {0};
    int level = 0;
    NODE *tmp = search_node(curr, curr_key, answer, &level); // �ε����� �����ϴ� ����� �ּ�
    if (tmp==NULL) { // �ƿ� ������ϴµ� ã�� ������� ���� ŷ�޴´�;;
        printf("\n�ش��ϴ� �ε����� �������� �ʽ��ϴ�.");
    }
    else{ // �����Ѵ�;; �̰͵� �����;;
        int idx = -1; // Ȥ�ø� ����Ȯ���� ���� flag...!
        for (int i=0; i<(tmp->key_count); i++) { // Ű���� �ڽ��� ã�´�.. ���� ã�� ����...
            if (tmp->key[i]==curr_key) {
                idx = i;
            }
        }
        if (tmp->child[0]==NULL) { // �ڽ��� ����???? ������??!!

            for (int j=idx;j<(tmp->key_count);j++) { // �����ֱ� baby~~
                tmp->key[j] = tmp->key[j+1];
            } // ##########################������� ��������#######################


            (tmp->key_count)--; // Ű ���� �ϳ� �ٿ��� �̰� ���ϱ�? ����???
            reculsive_delete(tmp, root);
            // if ((tmp->key_count)>=(N-N/2-1)) { // ������������ �ּұ��̸� �����ؿ�^~^
            //     return;
            // }
            // else{ // �������� �ּұ��� ������ �ȵ�;;;;;;;;;;;;;;;;;;;;;���� ����
            //     if (tmp->parent==NULL) { // �θ� ����
            //         return; //��� �� �ڽĵ������� �θ� ������ ����;;
            //     }
            //     else { // �θ� �־�!
            //         int child_idx = 0;
            //         for (int i=0;i <= tmp->parent->key_count;i++){ // ���� ã����..
            //             if (tmp->parent->child[i] == tmp) { //�ʴ� �� �ڽ��� �ƴ϶���...
            //                 child_idx = i;
            //             }
            //         }

            //         if (child_idx == tmp->parent->key_count) { //���� �������???~!!~
            //             NODE * left_sibling = tmp->parent->child[child_idx-1];
            //             left_sibling->key[left_sibling->key_count] = tmp->parent->key[child_idx-1];
            //             (tmp->parent->key_count)--; // ���߿� �θ� �� ���������� Ȯ���ؾߴ�;; ���� �����ϴµ�? �ٷ� ��
            //             (left_sibling->key_count)++;
            //             for (int i=0; i<tmp->key_count;i++){
            //                 left_sibling->key[left_sibling->key_count]=tmp->key[i];
            //                 (left_sibling->key_count)++;
            //             } 
            //             free(tmp);
            //             //  left sibling�� �� á���� Ȯ���ؼ� �� á���� up �� ����
            //             if ((left_sibling->key_count)>=(N)) {
            //                 up(left_sibling->key[N/2],left_sibling,root);
            //             }
            //         }
            //         else { //�� ���R �ƴъ�?;;;
            //             NODE * right_sibling = tmp->parent->child[child_idx+1];
            //             tmp->key[tmp->key_count] = tmp->parent->key[child_idx];
            //             (tmp->key_count)++;
            //             (tmp->parent->key_count)--;
            //             for (int i=0; i < right_sibling->key_count; i++) {
            //                 tmp->key[tmp->key_count] = right_sibling->key[i];
            //                 (tmp->key_count)++;
            //             }
            //             free(right_sibling);
            //             for (int i = child_idx; i<tmp->parent->key_count;i++){
            //                 tmp->parent->key[i]=tmp->parent->key[i+1]; // �θ� �������� 1�� �̵�!
            //                 tmp->parent->child[i+1] = tmp->parent->child[i+2]; // �ڽĵ鵵 �̵�!
            //             }

            //             if ((tmp->key_count)>=(N)) { //���� ��á��!!!~!~!~!~!~
            //                 up(tmp->key[N/2],tmp,root);
            //             }
                        

            //         }
                    
            //     }
            //     if ((tmp->parent->key_count)<(N-N/2-1)) { // �θ� �� �ּҰ����� �ȵ�...
            //         reculsive_delete(tmp->parent, root);
            //     }

            // }

        }
        else { // �ڽ��� �ֳ�??? ���ڽĻ������ε� ����;;; ������ �ƴϳ׳פĳ׳׳׳�~
            NODE * leftbig_house;
            leftbig_house = search_leftbig(tmp->child[idx]);
            tmp->key[idx] = leftbig_house->key[(leftbig_house->key_count)-1];
            (leftbig_house->key_count)--;
            if (leftbig_house->key_count<(N-N/2-1)) { // �λ� ���԰����� �ڽ��̶� �� �ڸ��� �ٲٷ��� �ߴµ� �� �ڽ��� ���� �������� ����!
                reculsive_delete(leftbig_house,root);
            }
        }
    }
}


NODE *search_node(NODE *curr, int key, int *answer, int *level){
    // ���� tree�� ������ �ʰ� search �� ���
    if (curr->key_count == 0){
        printf("���� Ű�� �������ּ���.");
        return NULL;
    }
    int i;
    for (i = 0; i < curr->key_count; i++){ // 
        if (curr->key[i] == key) {
            answer[*level] = i;
            // printf("() ()\n");
            // printf("(>_<) ã�ҽ��ϴ�! ���� : ");
            return curr;
        }
        if (curr->key[i] > key) {
            if (curr->child[0] == 0){
                printf("����� �Ѥ�");
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
            printf("����� �Ѥ�");
            return NULL;
        }
        answer[*level] = i;
        (*level)++;
        return (search_node(curr->child[i], key, answer, level));
    }
    return NULL;
}



NODE *split_node(NODE *curr){ // UP�Լ��� ���� ��ƾ
    curr->key_count = N/2; // ����(����) ����ü ������ ���̱�
    NODE *right_node = (NODE *)malloc(sizeof(NODE)); // ������ �߸� �� ����� 
	memset(right_node->child, 0, sizeof(NODE *) * (N+1)); 
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
    return right_node; // ������ ��� �ּҰ� ���� 
}

void up(int key, NODE *curr, NODE **root){
    if (curr->parent == NULL){ // �θ� ���� �� 
        NODE *upper_node = (NODE *)malloc(sizeof(NODE)); // �ö� �� ����ü ����� 
		memset(upper_node->child, 0, sizeof(NODE *) * (N+1)); 
        curr->parent = upper_node;
        upper_node->child[0] = curr; 
        upper_node->child[1] = split_node(curr);  
        upper_node->key[0] = key; 
        upper_node->key_count = 1; 
		upper_node->parent = NULL;
        *root = upper_node; 
    }
    else{// �θ� ���� �� 
        int idx; 
        for (int i = 0 ; i < N+1; i++){
            if (curr->parent->child[i] == curr){  //�� ����Ű�� �� ã�� 
                idx = i; 
                break; 
            }
        }
        for (int i = curr->parent->key_count; i> idx; i--){ // �θ� �б� 
            curr->parent->key[i] = curr->parent->key[i-1];
            curr->parent->child[i+1] = curr->parent->child[i];
        }

        (curr->parent->key_count)++; 
        curr->parent->key[idx] = key;  // �� ������ key ���� 
        curr->parent->child[idx+1] = split_node(curr); // ������ ���� �� ��� ���� 
        if (curr->parent->key_count==N){
            up(curr->parent->key[N/2], curr->parent, root);
        }
    }
}

void insert_node(NODE *curr, int curr_key, NODE **root){ // curr : ó���� root 
    if (curr->child[0] == NULL){ // ������ �� 
       curr->key[curr->key_count] = curr_key;
       for (int i = (curr->key_count)-1; i>=0; i--){
           if (curr->key[i] >= curr->key[i+1]){// ��� �� 
                int tmp=curr->key[i]; 
                curr->key[i] = curr->key[i+1]; 
                curr->key[i+1] = tmp; 
           }
           else
            break;   
       }
       curr->key_count++;
       
       if (curr->key_count == N){ // ������ �־ ����         
            up(curr->key[N/2], curr, root); 
       }
    } 
    else{ //������ �ƴ� �� (child ����)
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
//     // key �� 
// }

void visualizing(NODE *curr, int depth, int flag){
    int i;
    if (depth != 0){
        if (flag == 0)
            printf(" �� ");
        else 
            printf(" �� ");
    }

    for (i = 0; i < curr->key_count; i++){
        printf("%d", curr->key[i]);
        if (curr->child[i] != NULL) {
            
            visualizing(curr->child[i], depth + 1, 0);
        }
    }
    printf("\n");
    if (curr->child[i] != NULL)
        visualizing(curr->child[i], depth + 1, 1);
}

int main(){
    
    NODE *root;
    root = (NODE *)malloc(sizeof(NODE)); // start node 
	memset(root->child, 0, sizeof(NODE *) * (N+1));
	root->parent = NULL; 
    root->key_count = 0; 
	int insert_nbr_flag[100000] = {0};


	while (1){
		system("cls");
		char want;
		printf("--------------------------------------\n");
		printf("|       \\Welcome B-Tree World/       |\n");
		printf("|        ^^^^^^^^^^^^^^^^^^^^        |\n");
		printf("| 1. Visualizing                     |\n");
		printf("| 2. Search                          |\n");
		printf("| 3. Insert                          |\n");
		printf("| 4. Delete                          |\n");
		printf("--------------------------------------\n");
		printf("What do you wanna do? : ");
		scanf("%c", &want);

		int idx;
		int key;

		switch(want){
			case '1' : {
				system("cls");
				visualizing(root, 0, 0);
				printf("\n\n PRESS 'q' for Exit\n");
				char exit = _getch();
				if (exit == 'q'){
					break;
				}
			}

			case '2' : {
				printf("\nWhich Idx do you want? : ");
				scanf("%d", &idx);

				int answer[5] = {0};
				int level = 0;
				NODE *tmp = search_node(root, idx, answer, &level);
				if (tmp != NULL){
					printf("root");
					if (level != 0){
						for (int i=0; i < level; i++){
							if (i != level)
								printf("->");
							printf("%d", answer[i]);
						}
					}
					printf(": %d�� �ڸ�", answer[level] + 1);
				}
				printf("\n");
				printf("\n\n PRESS 'q' for Refresh\n");
				char exit = _getch();
				if (exit == 'q'){
					break;
				}
			}

			case '3' : {
				printf("\nWhich key do you want to insert? : ");
				scanf("%d", &key);
				if (insert_nbr_flag[key] == 1) {
					printf("That number has already been entered\n\n");
					printf("Do you want another number? [y / n] : ");
				}
				else {
					insert_node(root, key, &root);
					insert_nbr_flag[key] = 1; 
					printf("\nEverything Went Well\n\n");
					printf("Do you want more? [y / n] : ");
				}

				char user_answer;
				scanf("%s", &user_answer);

				while (strcmp(&user_answer, "y") == 0){
					printf("Your answer is 'YES'\n");
					printf("\nWhich key do you want to insert? : ");
					scanf("%d", &key);

					if (insert_nbr_flag[key] == 1) {
						printf("That number has already been entered\n\n");
						printf("Do you want another number? [y / n] : ");
					}
					else {
						insert_node(root, key, &root);
						insert_nbr_flag[key] = 1; 
						printf("\nEverything Went Well\n\n");
						printf("Do you want more? [y / n] : ");
					}
					memset(&user_answer, 0, 1);
					scanf("%s", &user_answer);

					if (strcmp(&user_answer, "n") == 0) {
						printf("Your answer is 'NO'\n\n");
						break;
					}
				}
				break;
			}

			case '4' : {
				int dNbr;
				printf("\nWhich key do you want to Delete? : ");
				scanf("%d", &dNbr);
				if (insert_nbr_flag[dNbr] == 0) {
					printf("That number hasn't been entered\n\n");
					printf("Do you want to delete another number? [y / n] : ");
				}
				else {
					delete_node(root, dNbr, &root);
					insert_nbr_flag[dNbr] = 0; 
					printf("\nEverything Went Well\n\n");
					printf("Do you want more? [y / n] : ");
				}

				char user_answer;
				scanf("%s", &user_answer);

				while (strcmp(&user_answer, "y") == 0){
					printf("Your answer is 'YES'\n");
					printf("\nWhich key do you want to Delete? : ");
					scanf("%d", &dNbr);

					if (insert_nbr_flag[dNbr] == 0) {
						printf("That number hasn't been entered\n\n");
						printf("Do you want another number? [y / n] : ");
					}
					else {
						delete_node(root, key, &root);
						insert_nbr_flag[dNbr] = 1; 
						printf("\nEverything Went Well\n\n");
						printf("Do you want more? [y / n] : ");
					}
					memset(&user_answer, 0, 1);
					scanf("%s", &user_answer);

					if (strcmp(&user_answer, "n") == 0) {
						printf("Your answer is 'NO'\n\n");
						break;
					}
				}
				break;

			}
		}
	}

    // int key1 = 30;
    // int key2 = 40;
    // int key3 = 50;
    // int key4 = 60;
    // int key5 = 41;
    // int key6 = 32;
    // int key7 = 33;
    // int key8 = 34;
    // int key9 = 29;
    // int key10 = 28;
    // int key11 = 70;
    // int key12 = 62;
    // int key13 = 63;
    // int key14 = 64;
    // int key15 = 65;
    // int key16 = 66;
    // int key17 = 67;
    // int key18 = 68;
    // int key19 = 69;    
    // int key20 = 27;    
    // int key21 = 26;    
    // int key22 = 42;    
    // int key23 = 43;    
    // int key24 = 44;    
    
    // insert_node(root, 1, &root); 
    // insert_node(root, key2, &root); 
    // insert_node(root, key3, &root); 
    // insert_node(root, key4, &root); 
    // insert_node(root, key5, &root); 
    // insert_node(root, key6, &root); 
    // insert_node(root, key7, &root); 
    // insert_node(root, key8, &root); 
    // insert_node(root, key9, &root); 
    // insert_node(root, key10, &root);
    // insert_node(root, key11, &root);
    // insert_node(root, key12, &root);
    // insert_node(root, key13, &root);
    // insert_node(root, key14, &root);
    // // insert_node(root, 35, &root);
    // insert_node(root, key15, &root);
    // insert_node(root, key16, &root);
    // insert_node(root, key17, &root);
    // insert_node(root, key18, &root);
    // insert_node(root, key19, &root);
    // insert_node(root, key20, &root);
    // insert_node(root, key21, &root);
    // insert_node(root, key22, &root);
    // insert_node(root, key23, &root);
    // insert_node(root, key24, &root);

    // // printf("%d", root->child[0]->child[0]->key[0]);
    
    // int key_tmp = 34;
    // int answer[5] = {0};
    // int level = 0;
    // // NODE *tmp = search_node(root, key_tmp, answer, &level);
    // // if (tmp != NULL){
    // //     printf("root");
    // //     if (level != 0){
    // //         for (int i=0; i < level; i++){
    // //             if (i != level)
    // //                 printf("->");
    // //             printf("%d", answer[i]);
    // //         }
    // //     }
    // //     printf(": %d�� �ڸ�", answer[level] + 1);
    // // }
    // // printf("\n");
    // // printf("%d",root->child[1]->key[1]);

    // // delete_node(root, 65, &root);
    // // delete_node(root, 64, &root);
    // // delete_node(root, 63, &root);
    // // delete_node(root, 62, &root);
    // // delete_node(root, 60, &root);
    // // delete_node(root, 66, &root);
    // delete_node(root, 67, &root);
    // // delete_node(root, 32, &root);
    // // delete_node(root, 34, &root);
    // // delete_node(root, 33, &root);
    // delete_node(root, 68, &root);
    // // delete_node(root, 41, &root);
    // // delete_node(root, 40, &root);
    // // delete_node(root, 29, &root);
    // // delete_node(root, 28, &root);
    // // delete_node(root, 30, &root);
    // // delete_node(root, 69, &root);
    // // delete_node(root, 50, &root);
    // // delete_node(root, 70, &root);
    // // printf("%p",root);
    // printf("%d  �ּ��ּ��ּ�\n",root->child[0]->child[0]->key[0]);
    // int second_answer[5] = {0};
    // level = 0;
    // NODE *ttmp = search_node(root, 35, second_answer, &level);
    // if (ttmp != NULL){
    //     printf("root");
    //     if (level != 0){
    //         for (int i=0; i < level; i++){
    //             if (i != level)
    //                 printf("->");
    //             printf("%d", second_answer[i]);
    //         }
    //     }
    //     printf(": %d�� �ڸ�", second_answer[level] + 1);
    // }
    // printf("\n");
    // visualizing(root, 0, 0);
}