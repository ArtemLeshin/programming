#include <math.h>
#include <stdio.h>
int main(){
int N=9;
int M=11;
for (int i=0; i<N; i++) {
 if (i<=ceil(N/2)) {
   M=M-2;
   }
 else{
  M=M+2;
 }
 for (int j=0; j<M;j++){
 printf("#");
 }
 printf("\n");
}

return 0;
}
