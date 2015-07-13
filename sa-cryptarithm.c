#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>


#define m 4


double T = 10, alpha = 0.99999, prob = 1, probtest;
int i,j, w,different,p,cost,newcost,iterations,times=00;
int occurances[26],val[26];
int value1[m],value2[m],value3[m+1],tempvalue1[m],tempvalue2[m],tempvalue3[m];
int val1, val2, val3,tempval1,tempval2,tempval3,dif;
char *first;
char *second;
char *third;


int test();
void update();

int main(int argc , char *argv[]){

	srand(time(NULL));

	for (i = 0; i < 26; i++){
		occurances[i] = -1;

	}
	if (strlen(argv[1]) == m && strlen(argv[1]) == strlen(argv[2])){

		printf("%s \n", argv[1]);
		printf("%s \n", argv[2]);

	}
	else {
		printf("1st and 2nd argument length must agree\n");
		getchar();
		exit(-1);
	}

	if (strlen(argv[3]) == m || strlen(argv[3]) == m + 1){
		printf("%s \n", argv[3]);

		first = (char *)malloc(m*sizeof(char));
		strcpy(first,argv[1]);
		second = (char *)malloc(m*sizeof(char));
		strcpy(second, argv[2]);
		third = (char *)malloc(m*sizeof(char) +1);
		strcpy(third, argv[3]);
	}
	else{

		printf("3d arguement has wrong length");
		getchar();
		exit(-1);
	}

	
	for (i = 0; i < m + 1; i++){
		
		if (i < m){
			occurances[first[i] - 'a'] = 1; //getting a value between 0-26 so this only works for lowercase letters
			occurances[second[i] - 'a'] = 1;
			occurances[third[i] - 'a'] = 1;
		}
		if (i == m && (strlen(third) == m + 1)){
			occurances[third[i] - 'a'] = 1;
		}

	}

	for (i = 0; i < 26; i++){
		if (occurances[i] == 1){
			different++;
		}
	}

	printf("There are %d different letters \n", different);

	if (different > 10){
		printf("Can't continue,there are more of 10 diferrent letters \n");
		getchar();
		exit(-1);
	}


	for (i = 0; i < 26; i++){
		
		if (occurances[i] != -1){
			val[i] = rand() % 10; // Give a random value to every letter 
			  
		}
	}
	printf("\n ");
	for (i = 0; i < m; i++){
		value1[i] = val[first[i] - 'a']; //Initialize the values of the strings
		value2[i] = val[second[i] - 'a'];
		value3[i] = val[third[i] - 'a'];
	}
	if (strlen(third) == m + 1){
		value3[m] = val[third[m] - 'a'];
	}

	printf("Value of first string is :");
	for (i = 0; i < m; i++){
		printf("%d", value1[i]);
	}

	printf("\n");

	printf("Value of second string is :");
	for (i = 0; i < m; i++){
		printf("%d", value2[i]);
	}

	printf("\n");
	printf("Value of third string is :");
	for (i = 0; i < m; i++){
		printf("%d", value3[i]);
	}
	if (strlen(third) == m + 1){
		printf("%d", value3[m]);
	}

	
	
	val1 = 0;
	val2 = 0;
	val3 = 0;
	for (i = 0; i < m; i++){    
		p = 1;
		for (j = i; j < m-1; j++){
			p =p * 10;
		}
		val1 += value1[i] * p;
		val2 += value2[i] * p;
	}
	


	if (strlen(third) == m + 1){
		for (i = 0; i <= m; i++){
			p = 1;
			for (j = i; j < m ; j++){
				p = p * 10;
			}
			val3 += value3[i] * p;
		}
	}
	else {
		for (i = 0; i < m; i++){
			p = 1;
			for (j = i; j < m - 1; j++){
				p = p * 10;
			}
			val3 += value3[i] * p;
		}
	}


	//printf("val1 = %d ",val1);
	//printf("val2 = %d ", val2);
	//printf("val3 = %d", val3);

	cost = abs(val3 - (val1 + val2));
	printf("\n");
	printf("initial cost is : %d \n \n",cost);

	iterations = 0; // How many fail attemps we have 

	while (T > 0.1 && (val1+val2 !=val3)){


		for (w= 0; w < 2*different; w++){	
			newcost = test();
			if (newcost == 0){
				update();
				cost = newcost;
				break;
			}
			
			else if ((newcost - cost) < 0){
				cost = newcost;
				update();
				iterations = 0;
			}
			else {
				dif = cost - newcost;
			
				prob = exp((dif / T));
				probtest = rand();
				probtest = probtest / RAND_MAX; // To get a value between a 0 and 1
				if (prob>probtest){
					cost = newcost;
					update();

					iterations = 0;

				}
				else {
					iterations++;
				}	
			}	
		}
		
		times++;
		
		if (iterations > 8 * different){

			break;
		}

		T *= alpha;
		}

	printf("val1 = %d ", val1);
	printf("val2 = %d ", val2);
	printf("val3 = %d \n", val3);
	printf("Finished  in %d times \n", times);

	printf("Final cost is %d", cost);
	getchar();
	
	
}


int test(){
	int letter, lettercost, lettercost2, s;
	int k = 0, same = 0;

	for (k = 0; k < m; k++){
		tempvalue1[k] = value1[k];
		tempvalue2[k] = value2[k];
		tempvalue3[k] = value3[k];
	}
	if (strlen(third) == m + 1){
		tempvalue3[m] = value3[m];
	}


	letter = rand() % 27;
	while (occurances[letter] == -1){
		letter = rand() % 27;
	}


LOOP:lettercost = rand() % 10;



	for (k = 0; k < m; k++){
		if (value1[k] == lettercost || value2[k] == lettercost || value3[k] == lettercost ){
			goto LOOP;
		}
	}
	
	if (strlen(third) == m + 1){
		
		while (value3[m] == lettercost){
		lettercost = rand() % 10;
		}

	}
	
	for (k = 0; k < m; k++){
		if ((first[k] - 'a') == letter){
			tempvalue1[k] = lettercost;
			
		}
		if ((second[k] -'a') == letter){
			tempvalue2[k] = lettercost;
			
		}
		if ((third[k] - 'a') == letter){
			tempvalue3[k] = lettercost;
			
		}

	}

	tempval1 = 0;
	tempval2 = 0;
	tempval3 = 0;
	for (k = 0; k < m; k++){
		p = 1;
		for (j = k; j < m - 1; j++){
			p = p * 10;
		}
		tempval1 += tempvalue1[k] * p;
		tempval2 += tempvalue2[k] * p;
	}



	if (strlen(third) == m + 1){
		for (k = 0; k <= m; k++){
			p = 1;
			for (j = k; j < m; j++){
				p = p * 10;
			}
			tempval3 += tempvalue3[k] * p;
		}
	}
	else {
		for (k = 0; k < m; k++){
			p = 1;
			for (j = k; j < m - 1; j++){
				p = p * 10;
			}
			tempval3 += tempvalue3[k] * p;
		}
	}

	s = abs(tempval3 - (tempval1 + tempval2));


	return s;
}

void update()
{
	int k;

	for (k = 0; k < m; k++){
		value1[k] = tempvalue1[k];
		value2[k] = tempvalue2[k];
		value3[k] = tempvalue3[k];
	}
	if (strlen(third) == m + 1){
		value3[m] = tempvalue3[m];
	}

	val1 = tempval1;
	val2 = tempval2;
	val3 = tempval3;


}
