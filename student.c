#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
    int rollno;
    char name[50];
    struct subject
    {
        int marks;
    }sub[3]; 
    int total;
    float percent;
}student;
void insert()
{
  student *s;
  FILE *fp;
  int n,i,j;
  
  printf("Enter number of students:");
  scanf("%d",&n);
  s=(student*)calloc(n,sizeof(student));
  fp=fopen("stud.txt","w");

  for(i=0;i<n;i++)
  {
      s[i].total=0;
      s[i].percent=0;
      printf("Enter roll no:");
      scanf("%d",&s[i].rollno);
      fflush(stdin);
      printf("Enter name:");
      scanf("%[^\n]s",s[i].name);
     for(j=0;j<3;j++)
     {
         printf("Enter marks of subject.%d:",j+1);
         scanf("%d",&s[i].sub[j].marks);
         s[i].total+=s[i].sub[j].marks;
     }
     s[i].percent=s[i].total/3.0;
     fwrite(&s[i],sizeof(student),1,fp);
  }
  fclose(fp);
}
void display()
{
 FILE *fp;
 student s;
 int j;
  fp=fopen("stud.txt","r");
  if(fp==NULL)
  {
      printf("\nFile does not exist...........\n");
  }

printf("\n_________________________________RESULT OF STUDENT__________________________________________________________________________\n");
     printf("\nR_NO\t\tNAME\t\t\tC\tC++\tJAVA\tTotal\tPERCENTAGE\n");
     printf("_____________________________________________________________________________________________________________________________\n");
 while(fread(&s,sizeof(student),1,fp))
 {
     
     printf("\n%-7d%-25s",s.rollno,s.name);
     for(j=0;j<3;j++)
     {
         printf("%9d",s.sub[j].marks);
     }
     printf("%10d%9.2f\n",s.total,s.percent); 
}
fclose(fp);
 printf("-----------------------------------------------------------------------------------------------------------------------------\n");
}
void update()
{
 student s;
 FILE *fp,*fp1;
 int rno,found=0,i,j;
 fp=fopen("stud.txt","r");
 fp1=fopen("temp.txt","w");
 printf("\nEnter Roll no to update information:");
 scanf("%d",&rno);
 while(fread(&s,sizeof(student),1,fp))
 {
     if(s.rollno==rno)
     {
         found=1;
         s.total=0;
      s.percent=0;
      fflush(stdin);
      printf("Enter new name:");
      scanf("%[^\n]s",s.name);
     for(j=0;j<3;j++)
     {
         printf("Enter new marks of subject.%d:",j+1);
         scanf("%d",&s.sub[j].marks);
         s.total+=s.sub[j].marks;
     }
     s.percent=s.total/3.0;
     }
    fwrite(&s,sizeof(student),1,fp1);
 }
 fclose(fp);
 fclose(fp1);
 if(found)
 {
  printf("\n_______________Successfully updated the data________________\n");
 
  fp=fopen("stud.txt","w");
 fp1=fopen("temp.txt","r");
 /*int n=ftell(fp);
 printf("%d",n);*/
 
 while(fread(&s,sizeof(student),1,fp1))
 {
     fwrite(&s,sizeof(student),1,fp);
 }
 fclose(fp);
 fclose(fp1);
 }
 else
 {
  printf("\n__________________Data is not found______________\n");
 }

}
void search()
{
  FILE *fp;
 student s;
 int j,rno,found=0;
  fp=fopen("stud.txt","r");
  printf("\nEnter rollno to search:");
  scanf("%d",&rno);
  

    while(fread(&s,sizeof(student),1,fp))
   {
    if(s.rollno==rno)
    {
    printf("\n Congratulations!!!!!!!!!! Information is found........\n");
    printf("\n_________________________________RESULT OF STUDENT__________________________________________________________________________\n");
    printf("\nR_NO\t\tNAME\t\t\tC\tC++\tJAVA\tTotal\tPERCENTAGE\n");
    printf("_____________________________________________________________________________________________________________________________\n");
    found=1;
    printf("\n%-7d%-25s",s.rollno,s.name);
     for(j=0;j<3;j++)
     {
         printf("%9d",s.sub[j].marks);
     }
     printf("%10d%9.2f\n",s.total,s.percent);
     printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    }
   } 
  
  if(!found)
  {
      printf("\n________________________Sorry!!!!! Data is not found_________________\n");
  }
   fclose(fp);

}

void delete()
{
  student s;
 FILE *fp,*fp1;
 int rno,found=0,i,j;
 fp=fopen("stud.txt","r");
 fp1=fopen("temp.txt","w");
 printf("\nEnter Roll no to delete information:");
 scanf("%d",&rno);
 if(fp==NULL)
  {
      printf("\nFile does not exist...........\n");
    
  }
 while(fread(&s,sizeof(student),1,fp))
 {
     if(s.rollno==rno)
     {
         found=1;
     }
     if(s.rollno!=rno)
     {
         fwrite(&s,sizeof(student),1,fp1);
     }
 }
 fclose(fp);
 fclose(fp1);
 remove("stud.txt");
 rename("temp.txt","stud.txt");
 if(found)
 printf("\n_______________Deleted successfully_______________\n");
 else
 printf("\n_______________Data is not found___________________\n");
 
}
int main()
{
    int ch;
    printf("_________________________________________________________________________________________________________________________\n\n");
    printf("****************************************WELCOME TO STUDENT MANAGEMENT SYSTEM*******************************************\n");
    printf("__________________________________________________________________________________________________________________________\n");

    do{
    printf("\n1.Insert Data\n2.Display Data\n3.Update Data\n4.Search Data\n5.Delete Data\n6.Exit---------------------------------------------------------------------------");
    printf("\n\nEnter your choice:");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:insert();
        break;
        case 2:display();
        break;
        case 3:update();
        break;
        case 4:search();
        break;
        case 5:delete();
        break;
        case 6:printf("\n------------------------THANK YOU FOR VISITING------------------------\n");
        break;
        default:printf("\nInvalid choice......Try again!!!!");
        
    }

    }while(ch!=6);
return 0;
    

}