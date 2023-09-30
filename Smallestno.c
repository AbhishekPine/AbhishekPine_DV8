#include<stdio.h>

int main(){
    
    int a, b;
    printf("enter the numbers a and b:\n");
    scanf("%d%d", &a,&b);
    
    (a<b)? printf("smallest number is %d", a) : printf("smallest number is %d", b);
    
}
