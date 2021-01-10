# include <stdio.h>

int main()
{
    int N, K, answer=0;
    int one_twocount=0,thr_four_male=0,thr_four_female=0,five_six_male=0,five_six_female=0;
    scanf("%d %d",&N,&K);
    // printf("%d %d",N,K);
    for (int i=0; i<N; i++){
        int sex, grade;
        scanf("%d %d", &sex, &grade);
        if (K==1){
            printf("%d",N);
            return 0;
        }
        if (grade==1 || grade==2) { // 1학년 혹은 2학년이라면
            one_twocount++;
            // answer++;
            // if (one_twocount%K!=0) {
            //     answer--;
            // }

        }
        else if (grade==3 || grade==4) {
            // answer++; // 3학년 혹은 4학년이라면
            if (sex==0) {
                thr_four_female++;
                // if (thr_four_female%K==0) {
                //     answer--;
                // }
            }
            else
            {
                thr_four_male++;
                // if (thr_four_male%K==0){
                //     answer--;
                // }
            }
        }
        else {
            // answer++;
            if (sex==0) {
                five_six_female++;
                // if (five_six_female%K==0) {
                //     answer--;
                // }
            }
            else
            {
                five_six_male++;
                // if (five_six_male%K==0){
                //     answer--;
                // }
            }
        }
    }
    if (one_twocount%K==0) {
        answer += one_twocount/K;
    } 
    else 
        answer += one_twocount/K + 1;
    if (thr_four_male%K==0) {
        answer += thr_four_male/K;
    } 
    else 
        answer += thr_four_male/K + 1;
    if (thr_four_female%K==0) {
        answer += thr_four_female/K;
    } 
    else 
        answer += thr_four_female/K + 1;
    if (five_six_male%K==0) {
        answer += five_six_male/K;
    } 
    else 
        answer += five_six_male/K + 1;
    if (five_six_female%K==0) {
        answer += five_six_female/K;
    } 
    else 
        answer += five_six_female/K + 1;
    printf("%d",answer);

}