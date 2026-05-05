#include <stdio.h>
#include <time.h>

int main(){
        time_t t=1;

        while(t>0){
                t=t*2;
        }

        t=t-1;
        printf("Max time_t: %lld\n",(long long)t);
        printf("Date: %s\n", ctime(&t));
        return 0;
}

