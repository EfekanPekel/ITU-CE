/*
* @Author
* Student Name: Mustafa Efekan PEKEL
* Student ID : 150140050
* Date: 12/05/2016
* BIL105E Spring Term CRN: 21831
* Homework 4
*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1729
struct person{
    int personId;
    double height;
    double weight;
    double BMI;
};
void abs_bubblesort(struct person arr[], int size, int threshold) {
    int i,j;
    for(i=0;i<size;i++){
        for(j=1;j<size-i;j++){
            if(fabs(arr[j-1].BMI - threshold) > fabs(arr[j].BMI - threshold)){
                struct person temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
}
int main(int argc, char *argv[]) {
    FILE *fp,*fp2;
    fp = fopen("height_weight.txt","r");
    int i,j;
    int N =  atoi(argv[1]);
    int M =  atoi(argv[2]);
    int threshold = atoi(argv[3]);
    //scanf("%d %d %d",&N,&M,&threshold);
    struct person array[N];
    struct person selected[M];
    char a[50],b[50],c[50];
    fscanf(fp,"%s %s %s",a,b,c);
    for(i=0;i<N;i++){
        fscanf(fp,"%d %lf %lf",&array[i].personId, &array[i].height, &array[i].weight);
        array[i].BMI = array[i].weight / ((array[i].height/100) * (array[i].height/100));
    }
    fp2 = fopen("output.txt","w+");
    fprintf(fp2,"%s\t%s\t%s\t%s\t%s\n","Person_id","Height(cm)","Weight(kg)","BMI","|BMI - Threshold|");
    abs_bubblesort(array, N, threshold);
    for(i=N-1;i>N-M-1;i--) {
        selected[N-i-1] = array[i];
    }
    for(i=0;i<M;i++) {
		fprintf(fp2,"%d\t%.0lf\t%.0lf\t%.2lf\t%.2lf\n",selected[i].personId,selected[i].height,selected[i].weight,selected[i].BMI,fabs(selected[i].BMI - threshold));
	}
	fclose(fp);
	fclose(fp2);

    return 0;
}
