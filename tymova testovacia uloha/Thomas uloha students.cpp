#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // pre deklaraciu SYSTEMTIME , GetLocalTime() and GetSystemTime()

struct date {
	int d;
	int m;
	int y;
};

struct student {
	
	char fname[20];
	char lname[20];
	struct date dob;    //dob je nazov premennej
	char gender;
};


bool underageFunction(int day, int month, int year){ 			//funkcia na hladanie studentov pod 18 rokov
	
	SYSTEMTIME timePC;       //SYSTEMTIME struct
	GetLocalTime(&timePC);  //vyplni timePC casom
	
	if(year>=timePC.wYear-18){    
		if(year==timePC.wYear-18) { //ak je rok rovny aktualnemu roku-18
		
										//pripad ak sa jeho rok narodenia rovna s aktualnym rokom-18
			if(month>timePC.wMonth){ //ak je rok rovny s aktualnym-18 ale mesiac 
				return true;
			}else{                   //mesiac je mensi alebo rovny ako aktualny mesiac
				if(month==timePC.wMonth){
					if(day>timePC.wDay){
						return true;
					}else{
						return false;
					}
				}else{ //ak je jeho mesiac narodenia mensi ako je aktualny mesiac 
					return false;
				}
			}
			
			
			
		}else{                     
			return true; //je nezletily nerovna sa rok narodenia s aktualnym rokom-18
		} 	
	}else{
		return false; 
	}
	
}

bool virginCHfunction(int day,int month){			//funkcia na hladanie studentov zo znakom panna
	if( (month==8 && (day>=24 && day<=31) ) || (month==9 && (day>=1 && day<=23)) ){
		return true;
	}
	return false;
}

bool compareAge(int st1Y,int st1M,int st1D,int st2Y,int st2M,int st2D){					//funkcia na porovnanie veku dvoch studentov st1>st2
	int student1[]={st1Y,st1M,st1D};
    int student2[]={st2Y,st2M,st2D};
    
    for(int i=0;i<3;i++){
    	if(student1[i]>=student2[i]){
    		if(student1[i]==student2[i]){
			continue;
			}else{
				return true;
			}
		}else{
			return false;
		}
	}
}

int main(){
	
	struct student students[100];
	int index=0;
	struct student female[100];
	int indexF=0;
	struct student underage[100];
	int indexUG=0;
	struct student december[100];
	int indexDEC=0;
	struct student virgin[100];
	int indexV=0;
	
	FILE *studList;
	studList = fopen("studList.txt","r");
	
	while(fscanf(studList, "%s", &students[index].fname) != EOF){
		
		fscanf(studList, "%s", &students[index].lname);
		fscanf(studList, "%d", &students[index].dob.d);
		fscanf(studList, "%d", &students[index].dob.m);
		fscanf(studList, "%d", &students[index].dob.y);
		fscanf(studList, " %c", &students[index].gender);
		
		if(students[index].gender=='F'){         //hladanie zien
			female[indexF]=students[index];
			indexF++;
		}
		
		if(underageFunction(students[index].dob.d, students[index].dob.m, students[index].dob.y)){    //hladanie nezletilych
		underage[indexUG]=students[index];
		indexUG++;
		}
		
		if(students[index].dob.m==12){     //hladanie decembrovych
		december[indexDEC]=students[index];
		indexDEC++;	
		}
		
		if(virginCHfunction(students[index].dob.d,students[index].dob.m)){		//hladanie studentov zo znakom panna
		virgin[indexV]=students[index];	
		indexV++;
		}
		
		index++;
	}
	
	fclose(studList);
	
		
	
	for(int i=0;i<index;i++){					//vypis vsetkych
		
		printf("%d.  %s %s %d %d %d %c\n",i+1,students[i].fname,students[i].lname,
									  students[i].dob.d,students[i].dob.m,
									  students[i].dob.y,students[i].gender);
	}
	
	printf("\n Females: \n");
	
	for(int i=0;i<indexF;i++){					//vypis zien
		
		printf("\t%d.  %s %s %d %d %d %c\n",i+1,female[i].fname,female[i].lname,
									  female[i].dob.d,female[i].dob.m,
									  female[i].dob.y,female[i].gender);
	}
	
	printf("\n Underage students: \n");
	
	for(int i=0;i<indexUG;i++){					//vypis nezletilych
		
		printf("\t%d.  %s %s %d %d %d %c\n",i+1,underage[i].fname,underage[i].lname,
									  underage[i].dob.d,underage[i].dob.m,
									  underage[i].dob.y,underage[i].gender);
	}
	
	printf("\n Decembers students: \n");
	
	for(int i=0;i<indexDEC;i++){					//vypis nezletilych
		
		printf("\t%d.  %s %s %d %d %d %c\n",i+1,december[i].fname,december[i].lname,
									  december[i].dob.d,december[i].dob.m,
									  december[i].dob.y,december[i].gender);
	}
	
	printf("\n Virgin character have students: \n");
	
	for(int i=0;i<indexV;i++){					//vypis nezletilych
		
		printf("\t%d.  %s %s %d %d %d %c\n",i+1,virgin[i].fname,virgin[i].lname,
									  virgin[i].dob.d,virgin[i].dob.m,
									  virgin[i].dob.y,virgin[i].gender);
	}
	
	for(int i=0;i<index-1;i++){
		for(int j=0;j<index-i-1;j++){
			
			if(compareAge(students[j].dob.y,students[j].dob.m,students[j].dob.d,/*>*/students[j+1].dob.y,students[j+1].dob.m,students[j+1].dob.d)){
			struct student temp=students[j];
			students[j]=students[j+1];
			students[j+1]=temp;	
			}
		}
	}
	
	printf("\n students sorted by age: \n");
	
	for(int i=0;i<index;i++){					//vypis vsetkych zoradenych podla veku
		
		printf("\t%d.  %s %s %d %d %d %c\n",i+1,students[i].fname,students[i].lname,
									  students[i].dob.d,students[i].dob.m,
									  students[i].dob.y,students[i].gender);
	}
	
	
}
