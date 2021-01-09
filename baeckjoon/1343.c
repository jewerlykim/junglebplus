// 폴리오미노
# include <stdio.h>
# include <string.h>

int main()
{
    char A[500];
    int count=0;
    scanf("%s",A);
    int A_len = strlen(A);

    for (int i=0; i<A_len; i++){
        if (A[i]=='X') {
            count++;
            if (count == 5){
                A[i-4] = 'A';
                A[i-3] = 'A';
                A[i-2] = 'A';
                A[i-1] = 'A';
                count = 1;
            }

        }
        else {
            printf("%d\n",i);
            if (count != 0 && count != 2 && count != 4) {
                printf("-1");
                return 0;
            }
            else if (count==2) {
                A[i-1] = 'B';
                A[i-2] = 'B';
                count = 0;
            }    
            else if (count==4) {
                A[i-4] = 'A';
                A[i-3] = 'A';
                A[i-2] = 'A';
                A[i-1] = 'A';
                count = 0;
            }    
            else {
                count = 0;
                continue;
            }
        }
    }
    if (count != 0 && count != 2 && count != 4) {
        printf("-1");
        return 0;
    }
    else if (count==2) {
        A[A_len-1] = 'B';
        A[A_len-2] = 'B';
    }    
    else if (count==4) {
        A[A_len-4] = 'A';
        A[A_len-3] = 'A';
        A[A_len-2] = 'A';
        A[A_len-1] = 'A';
    }    

    printf("%s",A);
    return 0;    
}