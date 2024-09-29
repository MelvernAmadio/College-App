
// AUTHOR BY MELVERN AMADIO HIDAYAT

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct student
{
	char studentname[30];    //nama,nim,umur,gender,semester
	char NIM[20];
	int  age;
	char gender[20];
	int semester;
};

struct teacher
{
	char teachername[30];
	char teachercode[20];
	int age;
	char gender[20];
	char subject[30];
	
};

// student 
void printstudent(student s[],int size);
void viewstudent(student s[],int size);
void absenstudent(student s[],int& size);
void readstudent(student s[], int& size);
void name(student s[],int size); 
void nim(student s[], int start, int size); 
void age(student s[], int start, int end);

// teacher
void printteacher(teacher t[],int sizes);
void viewteacher(teacher t[],int sizes);
void absenteacher(teacher t[],int& size);
void readteacher(teacher t[], int& size);
void name(teacher t[],int sizes); 
void kode(teacher t[], int start, int sizes); 
void age(teacher t[], int start, int end);

//ALL
void viewall(student s[],int size,teacher t[],int sizes);
void search(student s[],int size,teacher t[],int sizes);


void printstudentdata(student s[],int n);
void printteacherdata(teacher t[],int n);

void main_menu()
{
	printf("\nWelcome to Binus Campus Absent APP\n");
	printf("=======================================\n");
	printf("1. View Student\n");
	printf("2. Student Attendance\n");
	printf("3. View Teacher\n");
	printf("4. Teacher Attendance\n");
	printf("5. View All People and Search\n");
	printf("Choice: ");
}

int choice;
int main()
{
	student s[1000];
	teacher t[1000];
	int size = 0;
	int sizes = 0;
	readstudent(s, size);
	readteacher(t, sizes);
	
	do
		{
			main_menu();
			do
		{
			printf("input(0 to exit) :");
			scanf("%d",&choice);getchar();
		}while(choice < 0 || choice > 5);
		
		switch(choice)
		{
			case 1: viewstudent(s,size);break;
			case 2: absenstudent(s,size);break;
			case 3: viewteacher(t,sizes); break;
			case 4: absenteacher(t,sizes);; break;
			case 5: viewall(s,size,t,sizes); search(s,size,t,sizes); break;
		}
	}while(choice != 0);
						
						

}



void readstudent(student s[],int &size)
{
	FILE *std = fopen("students.txt","r");

		while(!feof(std))
		{			
			fscanf(std,"%[^,],%[^,],%d,%[^,],%d\n",&s[size].studentname ,&s[size].NIM, &s[size].age, &s[size].gender, &s[size].semester);
			size+=1;
		}
	fclose(std);
}

//=====================================================================================================================================================
void viewstudent(student s[],int size)
{
//	readstudent(s, size);
	int input;
	do
	{
		puts("==============================");
		printstudent(s,size);	
		puts("1. order by name");
		puts("2. order by NIM");
		puts("3. order by age");
		puts("4. return to menu");
		puts("P.S. : we sorting it Ascending");
		printf("Choice:");
		do
		{
			scanf("%d",&input);getchar();
			
		}while(input < 0 || input > 4);
//		if(input == 0) continue;
		
		switch(input)
		{
			case 1 : name(s, size);break;
			case 2 : nim( s, 0, size-1); break;
			case 3 : age(s, 0, size-1); break;
			case 4: main();

		}
	}while(input != 0);
}

	


void printstudent(student s[],int size)
{
	if(size >0)
	{
		for(int i=0;i< size;i++)
		{
			printf("%s %s %d %s %d\n",s[i].studentname ,s[i].NIM, s[i].age, s[i].gender, s[i].semester);
		}
	}
}

void swap( student *a, student *b)
{
	student temp= *a;
	*a=*b;
	*b=temp;
}

void name(student s[],int size)
{
	for(int i=0;i<size;i++)
	{
		for(int j=0; j < size-i-1;j++)
		{
			if(strcmp(s[j].studentname,s[j+1].studentname) > 0)
			{
				student temp = s[j];
				s[j] = s[j+1];
				s[j+1] = temp; 
			}
		}
	}
};

int partnim(student s[], int low, int high)
{
	char pivot[10];
	strcpy(pivot, s[high].NIM);
	int i=low-1;
	for(int j= low; j<high; j++)
	{
		if(strcmp(s[j].NIM, pivot)<0)
		{
			i++;
			swap(&s[i], &s[j]);
		}
	}
	
	swap(&s[i+1], &s[high]);
	return i+1;
}

void nim(student s[], int start, int size)
{ 
	if(start<size)
	{
		int index = partnim(s, start, size);
		nim(s, start, index-1);
		nim(s, index+1, size);
	}
}

void age(student s[], int start, int end)
{
    int i = start;
    int j = end;
    int pivot = s[(start + end) / 2].age;
    student temp;
    while (i <= j)
    {
        while (s[i].age < pivot)
        {
            i++;
        }
        while (s[j].age > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            temp = s[i];
            s[i] = s[j];
            s[j] = temp;
            i++;
            j--;
        }
    }
    if (start < j)
    {
        age(s, start, j);
    }
    if (i < end)
    {
        age(s, i, end);
    }
}

//================================================================================================================================================
void absenstudent(student s[],int& size)
{

	FILE *std;
	//INPUT NAMA
		char namastd[100];
		int checkname =0;
		

		do
		{	
			printf("Name:");
			scanf("%[^\n]", namastd);
			getchar();
			int length= strlen(namastd);
			
			for(int i=0; i<length; i++)
			{
				if(isalpha(namastd[i]))
				{
					checkname =1;	
				} 
				else if(namastd[i] ==' ')
				{
					checkname =1;
				} 
				else 
				{
					checkname=0;
					break;	
				}
			}
		}while(checkname==0);
		
		strcpy(s[size].studentname, namastd);
		
	//Input NIM
		char id[11];
		int lengthid;
		int checkid=0;
		do{						
			printf("Student's NIM (10 digits): ");
			scanf("%s", &id); getchar();
			lengthid= strlen(id);
			if(lengthid==10)
			{
				for(int i=0; i<lengthid; i++)
				{
					if (id[i]>='0'&& id[i]<='9' && id[0]=='2')
					{
						checkid++;
					}
				}				
			}

		}while(checkid != lengthid);
		strcpy(s[size].NIM, id);

		
		//INPUT GENDER
		do
		{
			printf("Gender[male/female]:");
			scanf("%s", &s[size].gender); 
			getchar();
		}while((strcmp(s[size].gender, "male")!=0) && strcmp(s[size].gender, "female")!=0);
		
		//Input AGE
		char umur[8];
		int lengthage;
		int checkage =0;
		do
		{
			printf("Age [Input digits only]:");
			scanf("%s", &umur); getchar();
			lengthage = strlen(umur);
			for(int i=0; i<lengthage; i++)
			{
				if(umur[i]>='0' && umur[i]<='9'&& umur[0]!='0')
				{
					checkage++;
				}
			}
		}while(checkage != lengthage);
		
		int Age= atoi(umur);
		s[size].age=Age;
		
		
	//INPUT SEMESTER
	char semester[8];
		int lengthsem;
		int checksem =0;
		do
		{
			printf("Current Semester [Input digits only]:");
			scanf("%s", &semester); getchar();
			lengthsem = strlen(semester);
			for(int i=0; i<lengthsem; i++)
			{
				if(semester[i]>='0' && semester[i]<='9'&& semester[0]!='0')
				{
					checksem++;
				}
			}
		}while(checksem != lengthsem);
		
		int semes= atoi(semester);
		s[size].semester=semes;
		
		std = fopen("students.txt","a+");
		for(int i=0;i< size+1;i++)
		{
			printf(" inserting Data: %s %s %d %s %d\n",s[i].studentname ,s[i].NIM, s[i].age, s[i].gender, s[i].semester);
		
			fprintf(std,"%s,%s,%d,%s,%d\n",s[i].studentname ,s[i].NIM, s[i].age, s[i].gender, s[i].semester);
		}
		fclose(std);
		size++;
	}
	
	
//=================================================================================================================================================

void readteacher(teacher t[], int& sizes)
{
	FILE *tch = fopen("teachers.txt","r");

		while(!feof(tch))
		{			
			fscanf(tch,"%[^,],%[^,],%d,%[^,],%[^\n]\n",&t[sizes].teachername,&t[sizes].teachercode, &t[sizes].age, &t[sizes].gender, &t[sizes].subject);
			sizes+=1;
		}
	fclose(tch);
}


void viewteacher(teacher t[],int sizes)
{
//	readteacher(t, sizes);
	int input;
	do
	{
		puts("==============================");
		printteacher(t,sizes);	
		puts("1. order by name");
		puts("2. order by code");
		puts("3. order by age");
		puts("4. return to menu");
		puts("P.S. : we sorting it Ascending");
		printf("Choice:");
		do
		{
			scanf("%d",&input);getchar();
			
		}while(input < 0 || input > 4);

		
		switch(input)
		{
			case 1 : name(t, sizes);break;
			case 2 : kode(t, 0, sizes-1); break;
			case 3 : age(t, 0, sizes-1); break;
			case 4: main();

		}
	}while(input != 0);
}

void printteacher(teacher t[],int sizes)
{
	if(sizes >0)
	{
		for(int i=0;i< sizes;i++)
		{
			printf("%s %s %d %s %s\n",t[i].teachername ,t[i].teachercode, t[i].age, t[i].gender, t[i].subject);
		}
	}
}

void swap( teacher *x,teacher *y)
{
	teacher temp= *x;
	*x=*y;
	*y=temp;
}

void name(teacher t[],int sizes)
{
	for(int i=0;i<sizes;i++)
	{
		for(int j=0; j < sizes-i-1;j++)
		{
			if(strcmp(t[j].teachername,t[j+1].teachername) > 0)
			{
				teacher temp = t[j];
				t[j] = t[j+1];
				t[j+1] = temp; 
			}
		}
	}
}

int partkode(teacher t[], int low, int high)
{
	char pivots[10];
	strcpy(pivots, t[high].teachercode);
	int i=low-1;
	for(int j= low; j<high; j++)
	{
		if(strcmp(t[j].teachercode, pivots)<0)
		{
			i++;
			swap(&t[i], &t[j]);
		}
	}
	
	swap(&t[i+1], &t[high]);
	return i+1;
}

void kode(teacher t[], int start, int sizes)
{ 
	if(start<sizes)
	{
		int indext= partkode(t, start, sizes);
		kode(t, start, indext-1);
		kode(t, indext+1, sizes);
	}
}

void age(teacher t[], int start, int end)
{
    int i = start;
    int j = end;
    int pivot = t[(start + end) / 2].age;
    teacher temp;
    while (i <= j)
    {
        while (t[i].age < pivot)
        {
            i++;
        }
        while (t[j].age > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            temp = t[i];
            t[i] = t[j];
            t[j] = temp;
            i++;
            j--;
        }
    }
    if (start < j)
    {
        age(t, start, j);
    }
    if (i < end)
    {
        age(t, i, end);
    }
}
//====================================================================================================================================================
void absenteacher(teacher t[],int& size)
{
		FILE *tch;
	//INPUT NAMA
		char namatch[100];
		int checknametch =0;
		

		do
		{	
			printf("Name:");
			scanf("%[^\n]", namatch);
			getchar();
			int lengthtch= strlen(namatch);
			
			for(int i=0; i<lengthtch; i++)
			{
				if(isalpha(namatch[i]))
				{
					checknametch =1;	
				} 
				else if(namatch[i] ==' ')
				{
					checknametch =1;
				} 
				else 
				{
					checknametch=0;
					break;	
				}
			}
		}while(checknametch==0);
		
		strcpy(t[size].teachername, namatch);
		
	//Input Kode Dosen
		char kode[11];
		int lengthkode;
		int checkkode=0;
		do{						
			printf("Teacher's Code (3 digit numbers): ");
			scanf("%s", &kode); getchar();
			lengthkode= strlen(kode);
			if(lengthkode==3)
			{
				for(int i=0; i<lengthkode; i++)
				{
					if (kode[i]>='0'&& kode[i]<='9')
					{
						checkkode++;
					}
				}				
			}

		}while(checkkode != lengthkode);
		strcpy(t[size].teachercode, kode);

		
		//INPUT GENDER
		do
		{
			printf("Gender[male/female]:");
			scanf("%s", &t[size].gender); 
			getchar();
		}while((strcmp(t[size].gender, "male")!=0) && strcmp(t[size].gender, "female")!=0);
		
		//Input AGE
		char umurtch[8];
		int lengthage;
		int checkage =0;
		do
		{
			printf("Age [Input digits only]:");
			scanf("%s", &umurtch); getchar();
			lengthage = strlen(umurtch);
			for(int i=0; i<lengthage; i++)
			{
				if(umurtch[i]>='0' && umurtch[i]<='9'&& umurtch[0]!='0')
				{
					checkage++;
				}
			}
		}while(checkage != lengthage);
		
		int Agetch= atoi(umurtch);
		t[size].age=Agetch;
		
		//Input Matkul yang diajar
		char matkul[100];
		int checkmatkul =0;
		

		do
		{	
			printf("Subject:");
			scanf("%[^\n]", matkul);
			getchar();
			int lengthmatkul= strlen(matkul);
			
			for(int i=0; i<lengthmatkul; i++)
			{
				if(isalpha(matkul[i]))
				{
					checkmatkul =1;	
				} 
				else if(matkul[i] ==' ')
				{
					checkmatkul =1;
				} 
				else 
				{
					checkmatkul=0;
					break;	
				}
			}
		}while(checkmatkul==0);
		
		strcpy(t[size].subject, matkul);

		
		tch = fopen("teachers.txt","a+");
		for(int i=0;i< size+1;i++)
		{
			printf(" inserting Data: %s D%s %d %s %s\n",t[i].teachername ,t[i].teachercode, t[i].age, t[i].gender, t[i].subject);
		
			fprintf(tch,"%s,D%s,%d,%s,%s\n",t[i].teachername ,t[i].teachercode, t[i].age, t[i].gender, t[i].subject);
		}
		fclose(tch);
		size++;
	}
	
//===========================================================================================================================================================================================

void viewall(student s[],int size,teacher t[],int sizes)
{
	puts("");
	printf("All Present Students:\n");
	puts("");
	printstudent(s,size);
	puts("");
	printf("All Present Teachers:\n");
	puts("");
	printteacher(t,sizes);	
	
	
}

//=======================================================================================================================================================================================
void printstudentdata(student s[],int n)
{
	puts("data found!");
	printf("%s %s %d %s %d\n",s[n].studentname ,s[n].NIM, s[n].age, s[n].gender, s[n].semester);
	printf("==================================================\n");
	puts("");
}

void printteacherdata(teacher t[],int n)
{
	puts("data found!");
	printf("%s %s %d %s %s\n",t[n].teachername ,t[n].teachercode, t[n].age, t[n].gender, t[n].subject);
	printf("==================================================\n");
	puts("");
}


void search(student s[],int size,teacher t[],int sizes)
{
	int choice;
	char mahasiswa[100];
	char dosen[100];
	int umurmhs;
	do{
		puts("");
		printf("==========================\n");
		printf("1. search student by Name\n");
		printf("2. search teacher by Code\n");
		printf("3. search student by Age\n");
		printf("3. Return to menu\n");
		printf("P.S. : We are using Linear Search ^w^\n");
		printf("input choice:");
		scanf("%d",&choice); getchar();
		
	  }while(choice < 0 || choice > 3);
	  
	  switch(choice)
		{
			case 1: 
					printf("Student's name:");
					scanf("%s",&mahasiswa);getchar();
			{
				for(int i=0;i < size;i++)
				{
						if(strcmp(mahasiswa,s[i].studentname) == 0)
						{
							printstudentdata(s,i);
							break;
						}
					}
			} search(s,size,t,sizes); break;
			case 2: 
						printf("Teacher's Code (with D): ");
					scanf("%s",&dosen);getchar();
			{
				for(int i=0;i < sizes;i++)
				{
						if(strcmp(dosen,t[i].teachercode) == 0)
						{
							printteacherdata(t,i);
							break;
						}
					}
			} search(s,size,t,sizes); break;
			case 3: 
						printf("Student's Age: ");
					scanf("%d",&umurmhs);getchar();
			{
				for(int i=0;i < size;i++)
				{
						if(s[i].age == umurmhs)
						{
							printstudentdata(s,i);
							break;
						}
					}
			} search(s,size,t,sizes); break;			
			case 4: main(); break;
	
		}while(choice != 0);
	}
	

