#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* Single perceptron with Intiger weights and Local minium
   Created by Dusan Radivojevic 26.06.2020 */

/*Activation function*/
double sigmoid(int x){
	return 1/(1+exp(-x));
}

/*Calculation for output value*/
int Out(int U1,int U2,int k1,int k2, int k3){
	int rez=k1+U1*k2+U2*k3;
	if(sigmoid(rez)>=0.5)rez=1;
	else rez=0;
	return rez;
}

int main(int argc, char *argv[]) {
	char LC='n';
	int i,j,k,n=0;
	int br1,br2,br3,br4,pr;
	double r1,r2,r3,r4,average,mini=1,LokMin=1;
	int k1,k2,k3,red=1;
	int Logic[6][4]={{0,0,0,1},{0,1,1,1},{1,1,1,0},{1,0,0,0},{1,1,0,0,},{1,0,1,0}};
	printf("Local minimum can shorten training time.\n");
	printf("Do you want to use local minimum? (Y/N): ");
	scanf("%c",&LC);
	if((LC!='y')&&(LC!='Y'))printf("Your choice is No.");
	printf("\nSupported features are: AND, OR, NAND, NOR, NOTa, NOTb\n");
	printf("Enter number from 0 to 5 (default is 0), for given choices respectively: ");
	scanf("%d",&n);
	if((n<0)||(n>5)){
		n=0;
		printf("Your choice in not valid! ");
	}
	/*Values thrue iteration are recorded.*/
	FILE* file_ptr = fopen("Record.txt", "w");
	fprintf (file_ptr, "Rbr\tb\tw1\tw2\tmin\taverage\n");
    /*Training algorithm*/
	clock_t start = clock();
	for(i=30;i>-30;i--){
		for(j=30;j>-30;j--){
			for(k=30;k>-30;k--){
				br1=i+0*j+0*k;
				br2=i+0*j+1*k;
				br3=i+1*j+0*k;
				br4=i+1*j+1*k;
				r1=Logic[n][0]-sigmoid(br1);
				r2=Logic[n][1]-sigmoid(br2);
				r3=Logic[n][2]-sigmoid(br3);
				r4=Logic[n][3]-sigmoid(br4);
				average=(pow(r1,2)+pow(r2,2)+pow(r3,2)+pow(r4,2))/4.0;
				if(average<mini){
					mini=average;
					k1=i;
					k2=j;
					k3=k;	
				}
				fprintf (file_ptr, "%d\t%d\t%d\t%d\t%.5lf\t%.5lf\n",red,i,j,k,mini,average);
				red++;
				/*Local minium option*/
				if((LC=='y')||(LC=='Y')){
					if(average>LokMin){
						LokMin=1;
				    	k=-30;
						if(mini<0.00001){
						j=-30;
						i=-30;
						}
					}
					else LokMin=average;
				}
			}
		}
	}	
	clock_t stop = clock();
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	/*Printing results*/
	printf("\nTraining finished for %.1fms! Accuracy %.1lf %%",elapsed,(1-mini)*100);
	printf("\nBias and Weights: b=%d, W1=%d, W2=%d",k1,k2,k3);
	printf("\n\na b\tf");	
	printf("\n0|0 =>  %d",Out(0,0,k1,k2,k3));
	printf("\n0|1 =>  %d",Out(0,1,k1,k2,k3));
	printf("\n1|0 =>  %d",Out(1,0,k1,k2,k3));
	printf("\n1|1 =>  %d",Out(1,1,k1,k2,k3));
	fprintf (file_ptr, "k1\tk2\tk3\tmin\ttime\n");
	fprintf (file_ptr, "%d\t%d\t%d\t%.5lf\t%.1f\n",k1,k2,k3,mini,elapsed);
	fclose(file_ptr);
	return 0;
}
