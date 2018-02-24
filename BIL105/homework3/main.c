/*
* @Author
* Student Name: Mustafa Efekan PEKEL
* Student ID : 150140050
* Date: 09/03/2016
* BIL105E Spring Term CRN: 21831
* Homework 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 80

int length=0,i=0,j,k,mahmut=0;

int user_menu(void){
    int selection;
    printf("0: Exit the program\n1: Set Current Character Sequence\n2: Get Substring\n3: Remove Substring\n4: Insert\n5: Replace\n");
    printf("\nEnter Your Choice: ");
    scanf("%d",&selection);
    return selection;
}

int set_ccs(char **ccs) {
    printf("Enter CCS: ");
    getchar();
    fgets(*ccs,SIZE,stdin);
    length = strlen(*ccs) - 1;
    *ccs = realloc(*ccs,length);
    *(*(ccs) + length) = '\0';
    if(length > 80) {
        return -1;
    }
    return (length) * sizeof(char);
}

char *sub_string (char *ccs, int begin_index, int end_index) {
    if(begin_index < 0 || end_index < 0 || begin_index > length-1 || end_index > length-1) {
        return NULL;
    }
    char *substring = malloc((end_index-begin_index+2)*sizeof(char));
    for(i=begin_index;i<end_index+2;i++) {
       *(substring+i-begin_index) = *(ccs+i);
    }
    *(substring + end_index - begin_index + 1) = '\0';
    return substring;
}

char *remove_string(char **ccs, int begin_index, int end_index) {
    if(begin_index < 0 || end_index < 0 || begin_index > length-1 || end_index > length-1) {
        return NULL;
    }
    char *removed = malloc((end_index-begin_index+2+1)*sizeof(char));
    for(i=begin_index;i<end_index+1;i++) {
       *(removed+i-begin_index) = *(*(ccs)+i);
    }
    *(removed+end_index-begin_index+1) = '\0';

    for(i=0;i<=length;i++){
        *(*(ccs)+begin_index+i) = *(*(ccs)+end_index+i+1);
    }
    length=length-(end_index-begin_index+2-1);
    *ccs = realloc(*ccs,length);
    *(*(ccs) + length) = '\0';
    return removed;
}

int insert_string(char **ccs, char *insert, int begin_index){
    int length_insert = strlen(insert) - 1;
    *(insert + length_insert) = '\0';
    *ccs = realloc(*ccs,sizeof(char)*(length+length_insert+1));
    for(i=length-1;i>=begin_index;i--){
        *(*(ccs)+i+length_insert) = *(*(ccs)+ i);
    }
    for(i=0;i<length_insert;i++){
        *(*(ccs)+begin_index+i) = *(insert + i);
    }
    length = length + length_insert +1;
    return length_insert * sizeof(char);
}

int replace_string(char **ccs, char *find, char *replace) {
    int length_find = strlen(find)-1;
    int length_replace = strlen(replace)-1;
    int end_index,begin_index,replacement=0;
    *(find + length_find) = '\0';
    *(replace + length_replace) = '\0';


    for(i=0;i<=length;i++){
        if(*(*(ccs)+i) == *(find)) {
        	if(length_find == 1){
        		begin_index = i;
        		end_index = i;
        		if(length_find == length_replace) {
	                	for(i=0;i<length_replace;i++){
	                    *(*(ccs)+begin_index+i) = *(replace + i);
	                    }
	            }	
	                else if(length_replace>length_find) {
	                    *ccs = realloc(*ccs,sizeof(char)*(length+(replacement+1)*(length_replace-length_find)+1));
	                    length = length+replacement*(length_replace-length_find)+1;
	                    for(j=length;j>=end_index;j--){
	                       *(*(ccs)+ length_replace - length_find + j) = *(*(ccs)+j);
	                    }
	                    for(i=0;i<length_replace;i++){
	                        *(*(ccs)+begin_index+i) = *(replace + i);
	                    }
	                    length = length+replacement*(length_replace-length_find)+1;
	                }
	                else if(length_find>length_replace) {
	                	
	                    *ccs = realloc(*ccs,sizeof(char)*(length+(replacement+1)*(length_replace-length_find)+1));
	                    length = length+replacement*(length_replace-length_find)+1;
	                    for(j=end_index;j<length;j++){
	                        *(*(ccs)+ length_replace - length_find + 1 + j) = *(*(ccs)+1+j);
	                    }
	                    for(i=0;i<length_replace;i++){
	                        *(*(ccs)+begin_index+i) = *(replace + i);
	                    }
	                    
	                }
	            }
	            replacement++;
        	}
	            for(j=1;j<length_find;j++) {
	                if(*(*(ccs)+ i+ j) != *(find + j)) {
	                    break;
	                }
	                else{
	                begin_index = i;
	                end_index = i+j;
	                if(length_find == length_replace) {
	                	for(i=0;i<length_replace;i++){
	                    *(*(ccs)+begin_index+i) = *(replace + i);
	                    }
	                }
	                else if(length_replace>length_find) {
	                    *ccs = realloc(*ccs,sizeof(char)*(length+(replacement+1)*(length_replace-length_find)+1));
	                    length = length+replacement*(length_replace-length_find)+1;
	                    for(j=length;j>=end_index;j--){
	                       *(*(ccs)+ length_replace - length_find + j) = *(*(ccs)+j);
	                    }
	                    for(i=0;i<length_replace;i++){
	                        *(*(ccs)+begin_index+i) = *(replace + i);
	                    }
	                    length = length+replacement*(length_replace-length_find)+1;
	                }
	                else if(length_find>length_replace) {
	                	
	                    *ccs = realloc(*ccs,sizeof(char)*(length+(replacement+1)*(length_replace-length_find)+1));
	                    length = length+replacement*(length_replace-length_find)+1;
	                    for(j=end_index;j<length;j++){
	                        *(*(ccs)+ length_replace - length_find + 1 + j) = *(*(ccs)+1+j);
	                    }
	                    for(i=0;i<length_replace;i++){
	                        *(*(ccs)+begin_index+i) = *(replace + i);
	                    }
	                    
	                }
	                replacement++;
	            }
	            
	            
	            }
			
        }

    *ccs = realloc(*ccs,sizeof(char)*(length+replacement*(length_replace-length_find)+1));
    free(find);
    free(replace);
    return replacement;

}

int main() {
    char *ccs;
    ccs = malloc(SIZE * sizeof(char));
    *ccs = '\0';
    int begin_index,end_index;
    while(1) {
        int selection = user_menu();
        if(selection == 0){
            printf("\nGoodbye!");
            break;
        }
        else if(selection !=1 && *ccs == '\0'){
            printf("\nYou have to set Current Character Sequence (CCS) before doing any operations!\n\n");
        }
        else if(selection == 1) {
            ccs = malloc(SIZE * sizeof(char));
            set_ccs(&ccs);
            printf("\n");
        }
        else if(selection == 2) {
            printf("Enter the BEGIN INDEX and END INDEX numbers: ");
            scanf("%d %d",&begin_index, &end_index);
            char *substring = sub_string(ccs, begin_index, end_index);
            printf("\nCCS:\"%s\"\n",ccs);
            printf("Substring(%d,%d): \"",begin_index,end_index);
            printf("%s\"\n\n",substring);
            free(substring);
        }
        else if(selection == 3) {
            printf("Enter the BEGIN INDEX and END INDEX numbers: ");
            scanf("%d %d",&begin_index, &end_index);
            char *removed = remove_string(&ccs,begin_index,end_index);
            printf("CCS:\"%s\"\n",ccs);
            printf("Removed String(%d,%d): \"",begin_index,end_index);
            printf("%s\"\n\n",removed);
            free(removed);
        }
        else if(selection == 4) {
            char *insert;
            insert = malloc(SIZE *sizeof(char));
            printf("Enter a new string for insertion: ");
            getchar();
            fgets(insert,SIZE,stdin);
            printf("Enter the BEGIN INDEX number where the new string begins:");
            scanf("%d",&begin_index);
            insert_string(&ccs,insert,begin_index);
            printf("CCS:\"%s\"\n\n",ccs);
        }
        else if(selection == 5){
            char *find = malloc(SIZE*sizeof(char));
            char *replace = malloc(SIZE*sizeof(char));
            printf("Find what: ");
            getchar();
            fgets(find,SIZE,stdin);
            printf("Replace with: ");
            fgets(replace,SIZE,stdin);
            int replacement = replace_string(&ccs,find,replace);
            printf("There were %d replacement.\n",replacement);
            printf("CCS:\"%s\"\n\n",ccs);
        }
    }

}
