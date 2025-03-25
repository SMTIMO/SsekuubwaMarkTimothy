#include <stdio.h>

int main(){
for (int i =0; i<= 10; i++){
if (i == 5) {
    continue; //Skip the iteration when i equals 5
}
printf("%d\n", i);
}
return 0;
}