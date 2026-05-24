#include <stdio.h>
int main() {
printf("1 Задание\n");
//1 Наибольший общий делитель
	int i;
	int n=60,n1=20;
	for (i = n1;!(n%i==0 && n1%i==0);i--){
	} printf("НОД(%d, %d) = %d\n", n, n1, i);


printf("\n\n2 Задание\n");
 //2 Наименьшее общее кратное 
	int n2,a2=20,b=60;
	for (n2=a2;n2%a2!=0 || n2%b!=0; n2++) {
	} printf("НОК(%d, %d) = %d\n", a2, b, n2);

printf("\n\n3 Задание\n");
//3 простое ли число
   	int n3,a3=5;
        for (n3=2; n3<a3; n3++) {
            if (a3%n3==0) {
                break;
            }
        }
        
        if (n3==a3) {
            printf("%d Простое число\n",a3);
        } else {
            printf("%d Cоставное число\n",a3);
        }
     
printf("\n\n4 Задание\n\n");
//Задание 4 простое ли число
	int n4, a4 = 7;
	for (n4 = 2; n4 < a4 && a4 % n4 != 0; n4++) {
	}

	if (n4==a4) {
            printf("%d Простое число\n",a4);
        } else {
            printf("%d Cоставное число\n",a4);
        }
printf("\n\n5 Задание\n\n");
//Задание 5 составное ли число
	int s,n5,a5=20;
	for (s=0,n5=2;n5<a5;n5++){
		if (a5%n5==0){
			s=1;
			break;
		}
	}
	if (s==1) {
            printf("%d Cоставное число\n",a5);
        } else {
            printf("%d Простое число\n",a5);
        }    	



 
return 0;
}
