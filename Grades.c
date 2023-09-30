#include<stdio.h>

int main(){
    
    int marks;
    printf("enter the marks \n");
    scanf("%d", &marks);
    
    if(marks>=90 && marks <=100){
        printf("grade is A+");
    }
    
    else if(marks>=70 && marks<90){
        printf("grade is A");  
    }
    
    else if(marks>=30 && marks<70){
        printf("grade is B");  
    }
    
    else{
        printf("grade is C");  
    }
}
