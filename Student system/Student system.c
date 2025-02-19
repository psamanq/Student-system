#include <stdio.h>
#include <string.h>

struct course
{
  char name[200];
  float grade;
};

struct date
{
    int year;
    int month;
    int day;
};

struct student
{
  char name[200];
  struct date dates;
  int student_number;
  char gender[200];
  int number_courses;
  struct course courses[40];
};

void readfile(struct student students[],int* index,char* filename)
{
  FILE* file = fopen(filename, "r");
  if(file == NULL)
  {
    printf("error.\n");
    return;
  }
    while (fscanf(file, "%[^\n]\n", students[*index].name) == 1) 
    {
      fscanf(file, "%d/%d/%d\n", &students[*index].dates.year, &students[*index].dates.month, &students[*index].dates.day);
      fscanf(file, "%d\n", &students[*index].student_number);
      fscanf(file, "%s\n", students[*index].gender);
      fscanf(file,"%d\n",&students[*index].number_courses);
       
      for(int i=0;i<students[*index].number_courses;i++)
      {
        fscanf(file,"%s %f\n",students[*index].courses[i].name,&students[*index].courses[i].grade);
      } 

      (*index)++;
    }

    fclose(file);
}

void updatefile(struct student students[],int* index,char* filename)
{
  FILE* file = fopen(filename, "w");
    if (file == NULL) 
    {
        printf("error.\n");
        return;
    }
  
  for(int i=0;i<*index;i++)
  {
    fprintf(file, "%s\n", students[i].name);
    fprintf(file, "%d/",students[i].dates.year);
    fprintf(file, "%d/",students[i].dates.month);
    fprintf(file, "%d\n",students[i].dates.day);
    fprintf(file, "%d\n",students[i].student_number);
    fprintf(file, "%s\n",students[i].gender);
    fprintf(file, "%d\n",students[i].number_courses);

    for(int j=0;j<students[i].number_courses;j++)
    {
      fprintf(file, "%s %.2f\n",students[i].courses[j].name,students[i].courses[j].grade); 
    }
    
    fprintf(file,"\n");
  }
  fclose(file);
}

void enterstudentinformation(struct student students[],int index,char* filename)
{
   FILE* file = fopen(filename, "a");
    if (file == NULL) 
    {
        printf("error opening file for writing.\n");
        return;
    }
    
  printf("enter name(full name):");
  scanf(" %[^\n]",students[index].name);
  fprintf(file, "%s\n", students[index].name);

  printf("enter the year of birth.:");
  scanf("%d",&students[index].dates.year);
  fprintf(file, "%d/",students[index].dates.year);

  printf("enter the month of birth.:");
  scanf("%d",&students[index].dates.month);
  fprintf(file, "%d/",students[index].dates.month);

  printf("enter the day of birth.:");
  scanf("%d",&students[index].dates.day);
  fprintf(file, "%d\n",students[index].dates.day);


  printf("enter student number:");
  scanf("%d",&students[index].student_number);
  fprintf(file, "%d\n",students[index].student_number);

  printf("enter gender(male or female):");
  scanf("%s",students[index].gender);
  fprintf(file, "%s\n",students[index].gender);

  printf("how many lessons do you want to add?");
  scanf("%d",&students[index].number_courses);
  fprintf(file,"%d\n",students[index].number_courses);

  for(int i=0;i<students[index].number_courses;i++)
  {
    printf("name course:");
    scanf("%s",students[index].courses[i].name);
    
    printf("grade course:");
    scanf("%f",&students[index].courses[i].grade);
    fprintf(file,"%s %.2f\n",students[index].courses[i].name,students[index].courses[i].grade);
  }


  fprintf(file,"\n");

  fclose(file);
}

void deletstudent(struct student students[],int* index,int studentnumber)
{
  for(int i=0;i<*index;i++)
  {
    if(students[i].student_number == studentnumber)
    {
      for(int j=i;j<*index-1;j++)
        {
          students[j]=students[j+1];
        }
        
       (*index)--;
       updatefile(students,index,"D:/students.txt");
       return;
    }
  }
  printf("student number %d not found\n",studentnumber);
}

void editinformation(struct student students[],int* index,int studentnumber,char informtion[])
{
  char newname[50];
  for(int i=0;i<*index;i++)
  {
    if(students[i].student_number == studentnumber)
    {
        if((strcmp("name",informtion)) == 0)
        {
          printf("enter new name(full name):");
          scanf(" %[^\n]",students[i].name);
        }
        else if((strcmp("date of birth",informtion)) == 0)
        {
          printf("enter the year of birth:");
          scanf("%d",&students[i].dates.year);

          printf("enter the month of birth:");
          scanf("%d",&students[i].dates.month);

          printf("enter the day of birth:");
          scanf("%d",&students[i].dates.day);
        }
        else if((strcmp("student number",informtion)) == 0)
        {
          printf("enter new student number:");
          scanf("%d",&students[i].student_number);
        }
        else if((strcmp("gender",informtion)) == 0)
        {
          printf("enter new gender(male or female):");
          scanf(" %[^\n]",students[i].gender);
        }
        else
        {
          printf("you enter wrong information\n");
        }
        updatefile(students,index,"D:/students.txt");
        return;
    }
  }
   printf("student number %d not found\n",studentnumber);
}

void changecoursegarde(struct student students[],int studentnumber,int* index)
{
   char course[50];
   float newgrade;
   for(int i=0;i<*index;i++)
   {
     if(students[i].student_number == studentnumber)
     {
         printf("%s course grades:\n",students[i].name);

         for(int j=0;j<students[i].number_courses;j++)
         {
          printf("%s:%.2f\n",students[i].courses[j].name,students[i].courses[j].grade);
         }

         printf("which course?\n");
         scanf("%s",course);

         printf("enter the new grade:");
         scanf("%f",&newgrade);
            
          for(int j=0;j<students[i].number_courses;j++)
          {
             if((strcmp(students[i].courses[j].name,course))==0)
             {
               students[i].courses[j].grade=newgrade;
               printf("grade for %s's %s course changed to %.2f.\n",students[i].name,course,newgrade);
               updatefile(students,index,"D:/students.txt");
               return; 
             }
          }
             printf("wrong course name\n");
             return;
     }    
   }
   printf("student number %d not found\n",studentnumber);
}

void addnewcourse(struct student students[],int* index)
{
  int studentnumber;
  printf("which student(student number)?");
  scanf("%d",&studentnumber);
  
  for(int i=0;i<*index;i++)
  {
      if(students[i].student_number == studentnumber)
      {
         printf("enter name of the new course:");
         scanf("%s",students[i].courses[students[i].number_courses].name);
         printf("enter grade:");
         scanf("%f",&students[i].courses[students[i].number_courses].grade);

         printf("%s course added with grade %.2f\n",students[i].courses[students[i].number_courses].name,students[i].courses[students[i].number_courses].grade);

         students[i].number_courses = (students[i].number_courses+1);
         
         updatefile(students,index,"D:/students.txt");
         return;
      }
  }
  printf("student number %d not found\n",studentnumber);
}

void showstudents(struct student students[],int index)
{
    printf("students:\n");
     for(int i=0;i<index;i++)
    {
      printf("%d-%s\tstudent number:%d\n",(i+1),students[i].name,students[i].student_number);
    }
}

void showcourses(struct student students[],int index)
{
  int studentnumber;
  printf("which student(student number)?");
  scanf("%d",&studentnumber);

   for(int i=0;i<index;i++)
  {
      if(students[i].student_number == studentnumber)
      {
        printf("%s course grades:\n",students[i].name);
        for(int j=0;j<students[i].number_courses;j++)
        {
          printf("%s:%.2f\n",students[i].courses[j].name,students[i].courses[j].grade);
        }
        return;
      }
  }
  printf("student number %d not found\n",studentnumber);
}



int main()
{
struct student students[30];
struct date dates[50];
struct course courses;
int number,index=0;
readfile(students,&index,"D:/students.txt");
do
{
printf("Options:\n");
printf("1-Enter student information.\n");
printf("2-Delete student information.\n");
printf("3-Edit student information.\n");
printf("4-Edit student grades.\n");
printf("5-Add new course.\n");
printf("6-Show students.\n");
printf("7-Show student grades.\n");
printf("8-Exit.\n");
printf("Please select the desired option:\n");
scanf("%d",&number);
printf("\n");

   switch (number)
   {
     case 1:
     {
     enterstudentinformation(students, index, "D:/students.txt");
     index++;
     break;
     }
     case 2:
     {
     int studentnumber; 
     printf("which student's information to delete(student number)?\n");
     scanf("%d",&studentnumber);
     deletstudent(students,&index,studentnumber);
     break;
     }
     case 3:
     {
     int studentnumber;
     char information[50];
     printf("which student's information to change (student number)?\n");
     scanf("%d",&studentnumber);
     printf("Which information to change (name , date of birth , student number , grade)?\n");
     scanf(" %[^\n]",information);
     editinformation(students,&index,studentnumber,information);
     break;
     }
     case 4:
     {
     int studentnumber;
     printf("which student's score will change (student number)?\n");
     scanf("%d",&studentnumber);
     changecoursegarde(students,studentnumber,&index);
     break;
     }
     case 5:
     {
     addnewcourse(students,&index);
     break;
     }
     case 6:
     {
     showstudents(students,index);
     printf("\n");
     break;
     }
     case 7:
     {
     showcourses(students,index);
     printf("\n");
     break;
     }
   }
   
}while(number != 8);

}