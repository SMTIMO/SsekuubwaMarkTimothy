#include <stdio.h>

int main(){
    int balance = 50000;
    int withdrawal = 20000;

    if (withdrawal > balance){
        printf("Insufficient funds. Your account balance is %d\n", balance);
    }
    else{
        balance -= withdrawal;
        printf("You have withdrawn %d\n", withdrawal);
        printf("Your new account balance is %d\n", balance);
    }
    return 0;
}