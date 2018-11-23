#include <stdio.h>
#include <stdlib.h>

typedef struct date {
	int d;
	int m;
	int y;
};

typedef struct student {
	
	char fname[20];
	char lname[20];
	struct date dob;    //dob je nazov premennej
	char gender;
};

int main(){
	
	struct student students[100];
	int index=0;
	
	FILE *studList;
	studList = fopen("studList.txt","r");
	
	while(fscanf(studList, "%s", &students[index].fname) != EOF){
		
		fscanf(studList, "%s", &students[index].lname);
		fscanf(studList, "%d", &students[index].dob.d);
		fscanf(studList, "%d", &students[index].dob.m);
		fscanf(studList, "%d", &students[index].dob.y);
		fscanf(studList, " %c", &students[index].gender);
		
		index++;
	}
	
	fclose(studList);
	
	for(int i=0;i<index;i++){
		
		printf("%s %s %d %d %d %c\n",students[i].fname,students[i].lname,
									  students[i].dob.d,students[i].dob.m,
									  students[i].dob.y,students[i].gender);
		
		
	}
	
	
	
	
	
}
