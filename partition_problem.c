#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LINE_LENGTH 1000

int factorial(int n){
	unsigned long long fact = 1;
    int i;

	if (n < 0)
        printf("Error! Factorial of a negative number doesn't exist.");
    else {
        for (i = 1; i <= n; ++i) {
            fact *= i;
        }
    }
	return fact;
}

int checkInArray(int x, int size,int S[]){
	for(int i=0; i<size; i++){
		if(x==S[i]) return 1;
	}
	return 0;
}

int checkDuplicate(){
	return 0;
}

void backtrack(int S[], int N){
	int nopts[N+2]; //array of top of stacks
	int option[N+2][N+2]; //array of stacks of options
	int start, move;
	int i, j, k;
	int candidate, sum, sum1, numberOfNonZero,numberOfNonZero1;
	int numberOfSolutions = 0;
	int counter = 1;
	int colSize = 0;

	//get total number of sets of combinations 
	for(i=1; i<=N;i++){
		colSize += (factorial(N))/(factorial(i)*factorial(N-i));
	}
	
	int array[colSize][N]; //array to be used in storing all possible combinations
	int S1[colSize][N];
	int S2[colSize][N];

	
	int index1 = 0;
	int index2 = 0;

	//initialize all the elements of the array to 0 so that there will be no garbage value
	for(i=0; i<colSize; i++){
		for (j=0; j<N; j++){
			array[i][j] = 0;
			S1[i][j] = 0;
			S2[i][j] = 0;
		}
	}
	
	move = start = 0; 
	nopts[start]= 1;
	
	while(1) { //while dummy stack is not empty 
		if(nopts[start] <= 0){ //pag nakuha na lahat ng combination
			numberOfSolutions = 0;

			for(i=0; i<colSize; i++){

				sum = 0;
				sum1 = 0;

				for(j=0; j<N; j++){
					// printf("S[j]: %d\n", S[j]);
					if(checkInArray(S[j],N,array[i])) sum += S[j];
					else sum1 += S[j];
				}
				
				// printf("sum: %d\n", sum);
				// printf("sum1: %d\n", sum1);

				if(sum == sum1){
					// printf("EQUAL!\n");
					
					index1 = 0;
					index2 = 0;

					for (j=0; j<N; j++){
						if(checkInArray(S[j],N,array[i])) S1[numberOfSolutions][index1++] = S[j];
						else S2[numberOfSolutions][index2++] = S[j];
					}
					numberOfSolutions++;
				}
			}

			printf("\nS = {");
			for(i=0; i<N; i++){
				if(i == N-1){
					printf("%d}\n", S[i]);
				}else printf("%d, ", S[i]);	
			}

			printf("Partitionings (%d solutions):\n", numberOfSolutions/2);

			if(numberOfSolutions==0){
				printf("There are no solutions\n");
			}

			for(i=0; i<numberOfSolutions/2; i++){
				printf("{");
				for(j=0; j<N; j++){
					if(S1[i][j+1]==0){ 
						printf("%d}", S1[i][j]);
						break;
					}
					else printf("%d, ", S1[i][j]);
				}
				
				printf("  {");

				for(j=0; j<N; j++){
					if(S2[i][j+1]==0){ 
						printf("%d}\n", S2[i][j]);
						break;
					}
					else printf("%d, ", S2[i][j]);
				}
			}
			break;
		}

		if(nopts[move]>0) {
			move++;
			nopts[move]=0; //initialize new move

			if(move>1) { //solution found!; print every time the stack is appended/changed
				for(i=1;i<move;i++){
					array[counter][i] = option[i][nopts[i]];
				}
				counter+=1;
			}
			if(move == 1) {
				for(candidate = N-1; candidate >=0; candidate--) {
					option[move][++nopts[move]] = S[candidate];
					// printf("nopts[move] %i candidate %i:\n", nopts[move], S[candidate]);           
				}
			}
			else {
				for(candidate = N-1; candidate>=0; candidate--) {
					for(i=move-1;i>=1;i--)
						if(S[candidate]==option[i][nopts[i]]) break;
					if(!(i>=1)) option[move][++nopts[move]] = S[candidate]; 
					else break; //break if the set (in any order) is already used so that it will not be printed again
				}
			}
		}
		else {
			move--;
			nopts[move]--;
		}
	}		
}

int main(){
	int numOfSets, n, i, j;
	int numOfSetsC = 0;
	int S[99];
	char line[MAX_LINE_LENGTH];

	double t;
	time_t t1, t2;
	//clock_t t1,t2;
	
	/* START CLOCK*/
	// time(&t1); 			//time_t
			//clock_t

	FILE *fp;
	fp = fopen("input.txt", "r");
	
	fgets(line, MAX_LINE_LENGTH, fp);
	numOfSets = atoi(line);

	for(i=0; i<numOfSets;i++){
		t1 = clock();
		n=0;

		fgets(line, MAX_LINE_LENGTH, fp);

		char *ptr = strtok(line, " ");
		while(ptr != NULL){
			S[n]=atoi(ptr);
			ptr = strtok(NULL, " ");
			n++;
		}

		

    	backtrack(S, n);
		printf("\n");
		t2 = clock();		//clock_t
		t = (double) (t2-t1)/ (double)CLOCKS_PER_SEC;
		printf("\nTime elapsed: %0.6f\n", t);
		
	}

	/* STOP CLOCK*/
	// time(&t2);			//time_t
	// t = difftime(t2,t1);

	
	
	
	return 0;
}