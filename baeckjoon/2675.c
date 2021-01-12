// 문자열 반복
# include <stdio.h>
# include <string.h>

int main(){
    int test_case;
    scanf("%d",&test_case);
    for (int i=0; i<test_case;i++){
        int R;
        char string[20];
        scanf("%d",&R);
        scanf("%s",string);
        // printf("%d %s",R,string);
        // printf("%lu",strlen(string));
        for (int j=0; j<strlen(string);j++){
            for (int i=0;i<R;i++){
                printf("%c",string[j]);
            }
        }
        printf("\n");


    }



    return 0;
}