/* #include <stdio.h>
int main() {
 //Задание1
	int year;
	printf("Еnter year:");
	scanf("%d",&year);
	if (year%400==0) {
		printf("YES\n");
	} else if (year%100==0) {
		printf("NO\n");
	} else if (year%4==0) {
                printf("YES\n");
	} else {
		printf("NO\n");
	}

//	Задание 2

	char scale;
	float degree;
	char f=102;
	char Cel=99;
	printf("Input temperature:");
	scanf("%f%c",&degree,&scale);

	if (scale=='c'||scale=='C'){
		printf("Ouput temperature: %0.2f%c\n",degree*1.8+32,f);
	}else if (scale=='f'||scale=='F'){
                printf("Ouput temperature:%0.2f%c\n",((degree-32)*5)/9,Cel);
	} else {
		printf("Ouput error\n");	
	}
    	
//     Задание, 3 условие задачи 5
	float x,y;
	printf("Enter coordinates(x y):");
	scanf("%f%f",&x,&y);
	if ((x<=1) && (y<=1) && (y>=-x)){
		printf("YES.\n"); // принадлежит
	} else{
		printf("NO.\n");// не принадлежит
	}

	

}
*/ 

#include <stdio.h>
int main(){
float x;
float y;
        printf("Type x:");
        scanf("%f",&x);
        printf("Type y:");
        scanf("%f",&y);

if ((x <= 1) && (y <= 1) && (y >= -x)){
printf("YES\n");
}
else {
printf("NO\n");
return 0;
}
}
