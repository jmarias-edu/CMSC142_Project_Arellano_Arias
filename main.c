#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	
	int array[colSize+2][N+2]; //array to be used in storing all possible combinations
	int S1[colSize+2][N+2];
	int S2[colSize+2][N+2];

	//initialize all the elements of the array to 0 so that there will be no garbage value
	for(i=1; i<=colSize; i++){
		for (int j=1; j<=N; j++){
			array[i][j] = 0;
		}
	}
	
	move = start = 0; 
	nopts[start]= 1;
	
	while(1) { //while dummy stack is not empty 
		if(nopts[start] <= 0){ //pag nakuha na lahat ng combination
			numberOfSolutions = 0;

			for(i=1; i<=colSize; i++){
				k=i;
				while(k < colSize){
					sum = 0;
					sum1 = 0;
					numberOfNonZero = 0;
					numberOfNonZero1 = 0;
					for (j=1; j<=N; j++){
						if(array[i][j] != 0) numberOfNonZero++;
						if(array[k+1][j] != 0) numberOfNonZero1++;
						sum += array[i][j];
						sum1 += array[k+1][j];
					}

					int invalid = 0;
					if(sum == sum1 && (numberOfNonZero+numberOfNonZero1)==N){
						for (j=1; j<=N; j++){
							for (int l=1; l<=N; l++){
								if(array[i][j] == array[k+1][l] && array[i][j] != 0){
									invalid = 1;
									break;
								}
							}
							if(invalid) break;
						}
						if(!invalid){
							for (j=1; j<=N; j++){
								S1[numberOfSolutions][j] = array[i][j];
								S2[numberOfSolutions][j] = array[k+1][j];
							}
							numberOfSolutions++;
						} 
					}
					k+=1;
				}
			}




			printf("\nS = {");
			for(i=0; i<N; i++){
				if(i == N-1){
					printf("%d}\n", S[i]);
				}else printf("%d, ", S[i]);	
			}

			printf("Partitionings (%d solutions):\n", numberOfSolutions);

			for(i=0; i<numberOfSolutions; i++){
				printf("{");
				for(j=1; j<N; j++){
					if(S1[i][j+1] == 0){ 
						printf("%d}", S1[i][j]);
						break;
					}
					else printf("%d, ", S1[i][j]);
				}
				
				printf("  {");
				for(j=1; j<N; j++){
					if(S2[i][j+1] == 0){ 
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
	int S[10];
	char line[MAX_LINE_LENGTH];

	FILE *fp;
	fp = fopen("input.txt", "r");
	
	fgets(line, MAX_LINE_LENGTH, fp);
	numOfSets = atoi(line);

	for(i=0; i<numOfSets;i++){
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
	}

	return 0;
}