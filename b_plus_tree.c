#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _NODE
{
    int key_count;        // 키 개수
    int *key;             // 하나 여유분
    struct _NODE **child; // 자식도 여유분
    struct _NODE *parent;
    struct _NODE *next; // 바닥 연결리스트

} NODE;

NODE *create_node(int degree);
void up(int key, NODE *curr, NODE **root, int degree);
void insert_node(NODE *curr, int curr_key, NODE **root, int degree);
void connect_leaf(NODE *left_sibling, NODE *right_sibling);
NODE *leaf_split(NODE *curr, int degree);
NODE *parent_split(NODE *curr, int degree); // child가 있을 때
void delete_node(NODE *curr, int key, NODE **root, int degree);
void search_node(NODE **address, NODE *curr, int key);
void recursive_delete(NODE *curr, NODE **root, int degree);
int search_rightsmall(NODE *curr);

int search_rightsmall(NODE *curr)
{
    if (curr->child[0] == NULL)
    {
        return curr->key[0];
    }
    else
    {
        return search_rightsmall(curr->child[0]);
    }
}

void recursive_delete(NODE *curr, NODE **root, int degree)
{
    NODE *tmp;

    if ((curr->key_count) >= (degree - degree / 2 - 1)) // 지웠을때에도 최소길이를 만족해요^~^
    {
        return;
    }
    else
    {                             // 지웠을때 최소길이 만족이 안됨;;;;;;;;;;;;;;;;;;;;;고난 시작
        if (curr->parent == NULL) // 단군할아버지다
        {                         // 부모 없음
            return;               //사실 난 자식도없었고 부모도 없었다 ㅎㅎ;;
        }
        else // 부모가 있엉!
        {
            int child_idx = 0;
            for (int i = 0; i <= curr->parent->key_count; i++) // 나는 몇번째 자식인가
            {
                if (curr->parent->child[i] == curr) // 너는 내 자식이 아니란다.
                {
                    child_idx = i;
                }
            }

            if (child_idx == curr->parent->key_count) // 내가 막내라니 (젤 오른쪽)
            {
                NODE *left_sibling = curr->parent->child[child_idx - 1];                       // 내 왼쪽 형제를 찾는다.
                left_sibling->key[left_sibling->key_count] = curr->parent->key[child_idx - 1]; // 부모를 내려준다
                (curr->parent->key_count)--;                                                   // 나중에 부모 다 없어졌는지 확인해야대;; 언제 누가하는데? 바로 나
                (left_sibling->key_count)++;
                connect_leaf(left_sibling, curr->next);

                for (int i = 1; i < curr->key_count; i++) // 부모랑 key 0 같으니 0번 친구 건들면 안됨
                {
                    left_sibling->key[left_sibling->key_count] = curr->key[i];
                    left_sibling->child[left_sibling->key_count] = curr->child[i];

                    if (curr->child[i] != NULL)
                    {
                        curr->child[i]->parent = left_sibling;
                    }

                    (left_sibling->key_count)++;
                }

                left_sibling->child[left_sibling->key_count] = curr->child[curr->key_count];
                // check
                if (curr->child[curr->key_count] != NULL)
                {
                    curr->child[curr->key_count]->parent = left_sibling;
                }
                // free(curr);
                tmp = left_sibling;

                if ((left_sibling->key_count) >= (degree)) // left sibling이 다 찼는지 확인해서 다 찼으면 up을 해줘
                {
                    up(left_sibling->key[degree / 2], left_sibling, root, degree);
                }
            }
            else // 젤 오른쪽 아닐 때
            {
                NODE *right_sibling = curr->parent->child[child_idx + 1];
                curr->key[curr->key_count] = curr->parent->key[child_idx];
                (curr->key_count)++;
                (curr->parent->key_count)--;
                connect_leaf(curr, right_sibling->next);
                for (int i = 1; i < right_sibling->key_count; i++)
                {
                    curr->key[curr->key_count] = right_sibling->key[i];
                    curr->child[curr->key_count] = right_sibling->child[i];
                    if (right_sibling->child[i] != NULL)
                    {
                        right_sibling->child[i]->parent = curr;
                    }
                    (curr->key_count)++;
                }
                curr->child[curr->key_count] = right_sibling->child[right_sibling->key_count];
                if (right_sibling->child[right_sibling->key_count] != NULL)
                {
                    right_sibling->child[right_sibling->key_count]->parent = curr;
                }
                // free(right_sibling);
                for (int i = child_idx; i < curr->parent->key_count; i++)
                {
                    curr->parent->key[i] = curr->parent->key[i + 1];         // 부모 왼쪽으로 1보 이동!
                    curr->parent->child[i + 1] = curr->parent->child[i + 2]; // 자식들도 이동!
                }
                tmp = curr;

                if ((curr->key_count) >= (degree))
                { //내가 꽉찼어!!!~!~!~!~!~
                    up(curr->key[degree / 2], curr, root, degree);
                }
            }
        }

        if ((curr->parent->key_count) < (degree - degree / 2 - 1))
        { // 부모 가 최소개수가 안돼...
            if (curr->parent->parent == NULL)
            { // 내 부모가 단군이라니!!!!!!! 이제 곧 내가 단군이오 ㅎㅎ ;;
                if (curr->parent->key_count == 0)
                {
                    *root = tmp;
                    tmp->parent = NULL;
                }
                return;
            }
            recursive_delete(curr->parent, root, degree);
        }
    }
}

void delete_node(NODE *curr, int key, NODE **root, int degree)
{
    NODE **address;
    address = (NODE **)malloc(sizeof(NODE *) * 2);
    memset(address, 0, sizeof(NODE *) * 2);
    search_node(address, curr, key); // Delete하기 위해서
    if (address[0] == NULL)
    {
        printf("없다\n");
        return;
    }
    else
    {                 // 리프에만 있을 때
        int idx = -1; // 내 위치 찾기
        for (int i = 0; i < address[0]->key_count; i++)
        {
            if (address[0]->key[i] == key)
            {
                idx = i;
                break;
            }
        }

        if (address[0]->child[0] == NULL)
        { // 자식이 없네???? 리프네??!!
            for (int j = idx; j < (address[0]->key_count); j++)
            { // 땡겨주기 baby~~
                address[0]->key[j] = address[0]->key[j + 1];
            }

            (address[0]->key_count)--; // 키 개수 하나 줄여줌 이게 끝일까? 과연???
            recursive_delete(address[0], root, degree);
        }

        if (address[1] != NULL)
        {
            memset(address, 0, sizeof(NODE *) * 2);
            search_node(address, *root, key);
            if (address[1] != NULL)
            {
                for (int i = 0; i < address[1]->key_count; i++)
                {
                    if (address[1]->key[i] == key)
                    {
                        idx = i;
                        break;
                    }
                }
                address[1]->key[idx] = search_rightsmall(address[1]->child[idx + 1]);
            }
            if (address[0] != NULL)
            {
                for (int i = 0; i < address[0]->key_count; i++)
                {
                    if (address[0]->key[i] == key)
                    {
                        idx = i;
                        break;
                    }
                }
                for (int j = idx; j < (address[0]->key_count); j++)
                { // 땡겨주기 baby~~
                    address[0]->key[j] = address[0]->key[j + 1];
                }
                (address[0]->key_count)--; // 키 개수 하나 줄여줌 이게 끝일까? 과연???
                recursive_delete(address[0], root, degree);
            }
        }
    }
}

void search_node(NODE **address, NODE *curr, int key) // 받기전에 주소 받을 것 malloc 해라
{
    if (curr->key_count == 0) // 만약 tree를 만들지 않고 search 할 경우
    {
        printf("먼저 키를 삽입해주세요.");
        return;
    }
    int i;
    for (i = 0; i < curr->key_count; i++)
    {
        if (curr->key[i] == key) // 찾았을 때
        {
            if (curr->child[0] == NULL)
            { // 리프인지 아닌지 확인
                address[0] = curr;
                return;
            }
            else
            {
                address[1] = curr;
            }
        }
        if (curr->key[i] > key)
        {
            if (curr->child[0] == 0)
            {
                return;
            }
            search_node(address, curr->child[i], key);
            break;
        }
    }
    if (i == curr->key_count)
    {
        if (curr->child[0] == 0) // 없어요
        {
            return;
        }
        search_node(address, curr->child[i], key);
    }
    return;
}

void connect_leaf(NODE *left_sibling, NODE *right_sibling)
{
    left_sibling->next = right_sibling;
}

NODE *parent_split(NODE *curr, int degree)
{
    curr->key_count = degree / 2;
    NODE *right_node = create_node(degree);
    right_node->parent = curr->parent;
    right_node->key_count = degree - degree / 2 - 1;
    for (int i = (degree / 2) + 1; i <= degree - 1; i++)
    {
        right_node->key[i - (degree / 2) - 1] = curr->key[i];
    }

    for (int i = 0; i < degree - (degree / 2); i++) //
    {
        right_node->child[i] = curr->child[i + degree / 2 + 1];
        if (curr->child[i + degree / 2 + 1] != NULL)
            curr->child[i + degree / 2 + 1]->parent = right_node;
    }

    return right_node;
}

NODE *leaf_split(NODE *curr, int degree)
{
    curr->key_count = degree / 2;
    NODE *right_node = create_node(degree); // 오른쪽 잘린 놈 만들기

    right_node->parent = curr->parent;
    right_node->key_count = degree - degree / 2;

    for (int i = (degree / 2); i <= degree - 1; i++)
    {
        right_node->key[i - (degree / 2)] = curr->key[i];
    }
    connect_leaf(curr, right_node); // 바닥놈들 링크드리스트 연결

    return right_node; // 오른쪽 노드 주소값 리턴
}

void up(int key, NODE *curr, NODE **root, int degree)
{
    if (curr->parent == NULL) // 루트일 때
    {
        NODE *upper_node = create_node(degree); // 부모가 없을 때
        curr->parent = upper_node;              // curr 왼쪽 기준
        upper_node->child[0] = curr;

        if (curr->child[0] == NULL)
        { // root면서 leaf일 때 (한 줄 있을 때)
            upper_node->child[1] = leaf_split(curr, degree);
        }
        else // root인데 child가 있을 때
        {
            upper_node->child[1] = parent_split(curr, degree);
        }
        upper_node->key[0] = key;
        upper_node->key_count = 1;
        upper_node->parent = NULL;
        *root = upper_node;
    }
    else
    { // 루트가 아닐 때 (부모가 있을 때 merge)
        int idx;
        for (int i = 0; i < degree + 1; i++) // 나 찾기
        {
            if (curr->parent->child[i] == curr)
            {
                idx = i;
                break;
            }
        }

        for (int i = curr->parent->key_count; i > idx; i--) // 부모 밀기
        {
            curr->parent->key[i] = curr->parent->key[i - 1];
            curr->parent->child[i + 1] = curr->parent->child[i];
        }
        (curr->parent->key_count)++;
        curr->parent->key[idx] = key; // 빈 공간에 key 넣음

        // 루트가 아니고, 리프면 리프스플릿, 아니면 걍 스플릿
        if (curr->child[0] == NULL)
        {
            curr->parent->child[idx + 1] = leaf_split(curr, degree); // 오른쪽 분할 된 노드 연결
            if (idx != curr->parent->key_count)
            {
                connect_leaf(curr->parent->child[idx + 1], curr->parent->child[idx + 2]);
            }
        }
        else // 리프가 아닐 때
        {
            curr->parent->child[idx + 1] = parent_split(curr, degree);
        }
        if (curr->parent->key_count == degree)
        {
            up(curr->parent->key[degree / 2], curr->parent, root, degree);
        }
    }
}

void insert_node(NODE *curr, int curr_key, NODE **root, int degree)
{
    if (curr->child[0] == NULL) // 내가 리프일 떄
    {
        curr->key[curr->key_count] = curr_key; // 끝에다 값 넣고 정렬함
        for (int i = (curr->key_count) - 1; i >= 0; i--)
        {
            if (curr->key[i] >= curr->key[i + 1])
            {
                int tmp = curr->key[i];
                curr->key[i] = curr->key[i + 1];
                curr->key[i + 1] = tmp;
            }
            else
                break;
        }
        curr->key_count++; // 값 하나 넣었으니까 카운트++

        if (curr->key_count == degree)
        {
            up(curr->key[degree / 2], curr, root, degree);
        }
    }
    else
    { //리프가 아닐 때 (child 있음)
        NODE *tmp;
        int flag = 0;
        for (int i = 0; i < curr->key_count; i++)
        {
            if (curr->key[i] > curr_key)
            {
                tmp = curr->child[i];
                flag = 1;
                break;
            }
        }
        if (flag == 0) // 제일 오른쪽 자식이 될 때
        {
            tmp = curr->child[curr->key_count];
        }
        insert_node(tmp, curr_key, root, degree);
    }
}

NODE *create_node(int degree)
{                                                                 //초기화 된 노드를 만든다 (차수만큼)
    NODE *temp = (NODE *)malloc(sizeof(NODE));                    // 새 노드 메모리 할당
    temp->key = (int *)malloc(sizeof(int) * degree);              // 키 배열 메모리 할당
    temp->child = (NODE **)malloc(sizeof(NODE *) * (degree + 1)); // 자식도 메모리 할당
    memset(temp->key, 0, sizeof(int) * degree);                   // 0으로 셋팅
    memset(temp->child, 0, sizeof(NODE *) * (degree + 1));        // 자식새끼도 0으로 셋팅
    temp->parent = NULL;                                          // 부모 일단 초기화
    temp->next = NULL;                                            // 밑단 연결리스트 next도 초기화
    return temp;
}

void visualizing(NODE *curr, int depth, int flag)
{
    int i;
    if (depth != 0)
    {
        if (flag == 0)
            printf(" 왼 ");
        else
            printf(" 오 ");
    }

    for (i = 0; i < curr->key_count; i++)
    {
        printf("%d", curr->key[i]);
        if (curr->child[i] != NULL)
        {

            visualizing(curr->child[i], depth + 1, 0);
        }
    }
    printf("\n");
    if (curr->child[i] != NULL)
        visualizing(curr->child[i], depth + 1, 1);
}

int main()
{
    int degree = 4;
    // scanf("%d", &degree);
    NODE *root = create_node(degree); // 창조신 만듬
    int insert_nbr_flag[100000] = {0};

    NODE **address;
    address = (NODE **)malloc(sizeof(NODE *) * 2);
    memset(address, 0, sizeof(NODE *) * 2);

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

    insert_node(root, key1, &root, degree);
    insert_node(root, key2, &root, degree);
    insert_node(root, key3, &root, degree);
    insert_node(root, key4, &root, degree);
    insert_node(root, key5, &root, degree);
    insert_node(root, key6, &root, degree);
    insert_node(root, key7, &root, degree);
    insert_node(root, key8, &root, degree);
    insert_node(root, key9, &root, degree);
    insert_node(root, key10, &root, degree);

    search_node(address, root, 40);
    // printf("%d\n", address[0]->next->key[0]);
    delete_node(root, 50, &root, degree);
    delete_node(root, 60, &root, degree);
    delete_node(root, 30, &root, degree);

    // insert_node(root, key11, &root, degree);
    // insert_node(root, key12, &root, degree);
    // insert_node(root, key13, &root, degree);
    // insert_node(root, key14, &root, degree);
    // insert_node(root, key15, &root, degree);
    // insert_node(root, key16, &root, degree);
    // insert_node(root, key17, &root, degree);
    // insert_node(root, key18, &root, degree);
    // insert_node(root, key19, &root, degree);
    // insert_node(root, key20, &root, degree);
    // insert_node(root, key21, &root, degree);
    // insert_node(root, key22, &root, degree);
    // insert_node(root, key23, &root, degree);
    // insert_node(root, key24, &root, degree);

    printf("%d\n", root->key[0]);
    printf("%d\n", root->child[0]->next->key[0]);
    printf("%d\n", root->child[0]->next->next->key[0]);
    printf("%d\n", root->child[0]->next->next->next->key[0]);
    // printf("%d\n", root->child[0]->next->next->next->next->key[0]);

    // while (1)
    // {
    //     // system("cls");
    //     char want;
    //     printf("--------------------------------------\n");
    //     printf("|       \\Welcome B-Tree World/       |\n");
    //     printf("|        ^^^^^^^^^^^^^^^^^^^^        |\n");
    //     printf("| 1. Visualizing                     |\n");
    //     printf("| 2. Search                          |\n");
    //     printf("| 3. Insert                          |\n");
    //     printf("| 4. Delete                          |\n");
    //     printf("--------------------------------------\n");
    //     printf("What do you wanna do? : ");
    //     scanf("%c", &want);

    //     int idx;
    //     int key;

    //     switch (want)
    //     {
    //     case '1':
    //     {
    //         // system("cls");
    //         visualizing(root, 0, 0);
    //         printf("\n\n PRESS 'q' for Exit\n");
    //         char exit;
    //         scanf("%s", &exit);
    //         if (exit == 'q')
    //         {
    //             break;
    //         }
    //     }

    //         // case '2':
    //         // {
    //         //     printf("\nWhich Idx do you want? : ");
    //         //     scanf("%d", &idx);

    //         //     int answer[5] = {0};
    //         //     int level = 0;
    //         //     NODE *tmp = search_node(root, idx, answer, &level);
    //         //     if (tmp != NULL)
    //         //     {
    //         //         printf("root");
    //         //         if (level != 0)
    //         //         {
    //         //             for (int i = 0; i < level; i++)
    //         //             {
    //         //                 if (i != level)
    //         //                     printf("->");
    //         //                 printf("%d", answer[i]);
    //         //             }
    //         //         }
    //         //         printf(": %d번 자리", answer[level] + 1);
    //         //     }
    //         //     printf("\n");
    //         //     printf("\n\n PRESS 'q' for Refresh\n");
    //         //     char exit;
    //         //     scanf("%s", &exit);
    //         //     if (exit == 'q')
    //         //     {
    //         //         break;
    //         //     }
    //         // }

    //     case '3':
    //     {
    //         printf("\nWhich key do you want to insert? : ");
    //         scanf("%d", &key);
    //         if (insert_nbr_flag[key] == 1)
    //         {
    //             printf("That number has already been entered\n\n");
    //             printf("Do you want another number? [y / n] : ");
    //         }
    //         else
    //         {
    //             insert_node(root, key, &root, degree);
    //             insert_nbr_flag[key] = 1;
    //             printf("\nEverything Went Well\n\n");
    //             printf("Do you want more? [y / n] : ");
    //         }

    //         char user_answer;
    //         scanf("%s", &user_answer);

    //         while (strcmp(&user_answer, "y") == 0)
    //         {
    //             printf("Your answer is 'YES'\n");
    //             printf("\nWhich key do you want to insert? : ");
    //             scanf("%d", &key);

    //             if (insert_nbr_flag[key] == 1)
    //             {
    //                 printf("That number has already been entered\n\n");
    //                 printf("Do you want another number? [y / n] : ");
    //             }
    //             else
    //             {
    //                 insert_node(root, key, &root, degree);
    //                 insert_nbr_flag[key] = 1;
    //                 printf("\nEverything Went Well\n\n");
    //                 printf("Do you want more? [y / n] : ");
    //             }
    //             memset(&user_answer, 0, 1);
    //             scanf("%s", &user_answer);

    //             if (strcmp(&user_answer, "n") == 0)
    //             {
    //                 printf("Your answer is 'NO'\n\n");
    //                 break;
    //             }
    //         }
    //         break;
    //     }

    //         // case '4':
    //         // {
    //         //     int dNbr;
    //         //     printf("\nWhich key do you want to Delete? : ");
    //         //     scanf("%d", &dNbr);
    //         //     if (insert_nbr_flag[dNbr] == 0)
    //         //     {
    //         //         printf("That number hasn't been entered\n\n");
    //         //         printf("Do you want to delete another number? [y / n] : ");
    //         //     }
    //         //     else
    //         //     {
    //         //         delete_node(root, dNbr, &root);
    //         //         insert_nbr_flag[dNbr] = 0;
    //         //         printf("\nEverything Went Well\n\n");
    //         //         printf("Do you want more? [y / n] : ");
    //         //     }

    //         //     char user_answer;
    //         //     scanf("%s", &user_answer);

    //         //     while (strcmp(&user_answer, "y") == 0)
    //         //     {
    //         //         printf("Your answer is 'YES'\n");
    //         //         printf("\nWhich key do you want to Delete? : ");
    //         //         scanf("%d", &dNbr);

    //         //         if (insert_nbr_flag[dNbr] == 0)
    //         //         {
    //         //             printf("That number hasn't been entered\n\n");
    //         //             printf("Do you want another number? [y / n] : ");
    //         //         }
    //         //         else
    //         //         {
    //         //             delete_node(root, key, &root);
    //         //             insert_nbr_flag[dNbr] = 1;
    //         //             printf("\nEverything Went Well\n\n");
    //         //             printf("Do you want more? [y / n] : ");
    //         //         }
    //         //         memset(&user_answer, 0, 1);
    //         //         scanf("%s", &user_answer);

    //         //         if (strcmp(&user_answer, "n") == 0)
    //         //         {
    //         //             printf("Your answer is 'NO'\n\n");
    //         //             break;
    //         //         }
    //         //     }
    //         //     break;
    //         // }
    //     }
    // }

    return 0;
}