#include <stdio.h>
#include <stdlib.h>

int factorial (int n){
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

void backtrack(int N){
	int start, move;
	int nopts[N+2]; //array of top of stacks
	int option[N+2][N+2]; //array of stacks of options
	int i, candidate;
	
	int counter = 1;
	int S[] = {13, 17, 12, 8, 14, 6, 20, 10};
	int arr_size = sizeof(S)/sizeof(S[0]);
	int x = 0;

	//get total number of sets of combinations 
	for(i=1; i<=arr_size;i++){
		x += (factorial(arr_size))/(factorial(i)*factorial(arr_size-i));
	}
	
	int array[x+2][arr_size+2]; //array to be used in storing all possible combinations
	int S1[x+2][arr_size+2];
	int S2[x+2][arr_size+2];

	//initialize all the elements of the array to 0 so that there will be no garbage value
	for(i=1; i<=x; i++){
		for (int j=1; j<=arr_size; j++){
			array[i][j] = 0;
		}
	}
	
	move = start = 0; 
	nopts[start]= 1;
	
	while (nopts[start]>0) { //while dummy stack is not empty 
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
				for(candidate = arr_size-1; candidate >=0; candidate--) {
					option[move][++nopts[move]] = S[candidate];
					// printf("nopts[move] %i candidate %i:\n", nopts[move], S[candidate]);           
				}
			}
			else {
				for(candidate = arr_size-1; candidate>=0; candidate--) {
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

	int sum = 0;
	int sum1 = 0;

	int numberOfNonZero = 0;
	int numberOfNonZero1 = 0;
	int k;
	int numberOfSolutions = 0;

	for(i=1; i<=x; i++){
		k=i;
		while(k < x){
			sum = 0;
			sum1 = 0;
			numberOfNonZero = 0;
			numberOfNonZero1 = 0;
			for (int j=1; j<=arr_size; j++){
				if(array[i][j] != 0) numberOfNonZero++;
				if(array[k+1][j] != 0) numberOfNonZero1++;
				sum += array[i][j];
				sum1 += array[k+1][j];
			}

			int invalid = 0;
			if(sum == sum1 && (numberOfNonZero+numberOfNonZero1)==arr_size){
				for (int j=1; j<=arr_size; j++){
					for (int l=1; l<=arr_size; l++){
						if(array[i][j] == array[k+1][l] && array[i][j] != 0){
							invalid = 1;
							break;
						}
					}
					if(invalid) break;
				}
				if(!invalid){
					for (int j=1; j<=arr_size; j++){
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
	for(i=0; i<arr_size; i++){
		if(i == arr_size-1){
			printf("%d}\n", S[i]);
		}else printf("%d, ", S[i]);	
	}

	printf("Partitionings (%d solutions):\n", numberOfSolutions);

	for(i=0; i<numberOfSolutions; i++){
		printf("{");
		for(int j=1; j<arr_size; j++){
			if(S1[i][j+1] == 0){ 
				printf("%d}", S1[i][j]);
			 	break;
			}
			else printf("%d, ", S1[i][j]);
		}
		
		printf("  {");
		for(int j=1; j<arr_size; j++){
			if(S2[i][j+1] == 0){ 
				printf("%d}\n", S2[i][j]);
			 	break;
			}
			else printf("%d, ", S2[i][j]);
		}
	}
		
}

int main(){
    printf("Hello World!\n");
    backtrack(8);
}