// Khalid Agnaber 101150

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *in;
int n_students,tuition_rate;


typedef struct crs{
    char c_name[20];
    char c_number[20];
    char grade;
    int credit_hours;
}course;

typedef struct Student{
    char f_name[20];
    char l_name[20];
    int id;
    int n_courses;
    double gpa;
    int tuition;
    int total_credits;
    course courses[10];
    char tuition_status;
    struct Student *next;
    struct Student *prev;
} student;

student*head;

void menu()
{
    printf("\n\n\t\t\t\t\tMenu");
    printf("\n\t\t-----------------------------------------------\n");
    printf("\n\t\t 1. Add a student\n");
    printf("\n\t\t 2. Update a student’s course Grade\n");
    printf("\n\t\t 3. Delete a student\n");
    printf("\n\t\t 4. Search for a student\n");
    printf("\n\t\t 5. Exit\n");
    printf("\n\t\t-----------------------------------------------\n");
    printf("\n\t Enter your choice: ");
}

double calculate_gpa(student* st)
{
double gpa=0, grade=0, total = 0;
int n_credit_hours=0;

    for (int i = 0; i < st->n_courses; i++)
    {
        if (st->courses[i].grade == 'A')
        {
            grade = (4 * st->courses[i].credit_hours);
        }
        else if (st->courses[i].grade == 'B')
        {
            grade = (3 * st->courses[i].credit_hours);
        }
        else if (st->courses[i].grade == 'C')
        {
            grade = (2 * st->courses[i].credit_hours);
        }
        else if (st->courses[i].grade == 'D')
        {
            grade = (1 * st->courses[i].credit_hours);
        }
        else if (st->courses[i].grade == 'F')
        {
        grade = (0 * st->courses[i].credit_hours);
        }
        total += grade;
    }

    for(int j=0;j < st->n_courses;j++)
    {
        n_credit_hours += st->courses[j].credit_hours;     
    }
    st->total_credits= n_credit_hours;
gpa = total / n_credit_hours;
    
return gpa;
}

int payment(student* std)
{
  int total=0;
  for(int i=0;i<std->n_courses;i++)
     {
        total+= (std->courses[i].credit_hours *tuition_rate);
      }
return total;
}

void update(){
in=fopen("stData.txt","w");
fprintf(in,"%d %d\n",n_students,tuition_rate);
student* st;
st=head;
    for(int i=0;i<n_students;i++)
    {
        fprintf(in,"%s %s %d %c %d\n",st->f_name,st->l_name,st->id,st->tuition_status,st->n_courses);
        for(int j=0;j<st->n_courses;j++)
            {
            fprintf(in,"%s %s %d %c \n",st->courses[j].c_name,st->courses[j].c_number,st->courses[j].credit_hours,st->courses[j].grade);
            }
    st=st->next;
    }
fclose(in);
}

void insert_student(student* new_node)
{
  new_node->next=head;
  head->prev=new_node;
  head=new_node;
}

student* fill_student(int id){
student *new_student;
int n_credits;
int i, j, k, mark=0, n_credit_hours=0;
double total, gpa;
in = fopen("stData.txt", "a");
new_student = (student*) malloc(sizeof(student));
new_student->id=id;

printf("Enter the student's first name: ");
scanf("%s", new_student->f_name);
printf("Enter the student's last name: ");
scanf("%s", new_student->l_name);
printf("Enter the number of courses: ");
scanf("%d", &new_student->n_courses);
printf("Enter the tuition payment status: ");
scanf(" %c", &new_student->tuition_status);

for (j = 0; j < new_student->n_courses; j++)
{

    printf("Enter the course's name: ");
    scanf("%s", new_student->courses[j].c_name);
    printf("Enter the course's number: ");
    scanf("%s", new_student->courses[j].c_number);
    printf("Enter the number of credits of this course: ");
    scanf("%d", &new_student->courses[j].credit_hours);
    printf("Enter the grade: ");
    scanf(" %c", &new_student->courses[j].grade);
}
printf("The student has been added successfully.\n");

  fprintf(in, "\n%s %s  %d  %c  %d\n", new_student->f_name, new_student->l_name, new_student->id, new_student->tuition_status, new_student->n_courses);
  for (k = 0; k < new_student->n_courses; k++)
  {
    fprintf(in, "%s  %s  %d  %c\n", new_student->courses[k].c_name, new_student->courses[k].c_number, new_student->courses[k].credit_hours, new_student->courses[k].grade);
  }

    total=calculate_gpa(new_student);
    new_student->gpa=total;
    new_student->tuition=payment(new_student);
new_student->next=NULL;
new_student->prev=NULL;  

(n_students)++;
  fclose(in);
return(new_student);  
}

student* insert(student *head, student *new_student)
{
student *walker;
walker=head;
if(head == NULL)
{
    head = new_student;
}
else
{
    while(walker->next!=NULL)
    {
    walker=walker->next;
    }
walker->next=new_student;
new_student->prev=walker;
walker=new_student;
}
return(head);
}

student* search(int id)
{
student*w;
w=head;
while(w!=NULL)
    {
        if(w->id==id)
        {
            return w;
        }
        else
        {
        w=w->next; 
        }
    }
return 0;
}


void update_grade(student* nod)
{
  char course_n[30];
  int i,j;
  char choice[5];
  char new_grade;

    if(nod!=NULL)
    {
    printf("Would you like to change the grade: ");
    scanf("%s",choice);
    while(strcmp(choice,"yes")==0)
        {
        printf("The courses that %s %s is taking are:\n",nod->f_name, nod->l_name);
        for(int i=0;i<nod->n_courses;i++)
            {
            printf("%s %s\n",nod->courses[i].c_name,nod->courses[i].c_number);
            }
        printf("Which class would you like to change its grade.\nEnter the course number:");
        scanf("%s",course_n);
        for(j=0;j<nod->n_courses;j++)
            {
                if(strcmp(nod->courses[j].c_number,course_n)==0)
                    {  
                        printf("The grade of that class is: %c\n",nod->courses[j].grade);
                        break;
                    }
            }

            printf("Please enter the new grade: ");
            scanf(" %c",&new_grade);
            nod->courses[j].grade=new_grade;
            printf("The grade of %s %s was updated\n",nod->f_name, nod->l_name);
            nod->gpa=calculate_gpa(nod);
            printf("would you like to change another grade?\n");
        scanf("%s",choice);
        } 
    update();
    }
    else
    {
    printf("The ID you entered is not registered on the list");
    } 
}

void delete_student(student* nod)
{
    student*delete;
    student*wlk;
    if(head==NULL)
    {
        printf("The list is empty");
    }
    else if(head->id==nod->id)  
    {
        delete=head;
        head=head->next;
        free(delete);
    }
    else
    {
        wlk=head;
        while(wlk->next!=NULL)
        {
            if(nod->id==wlk->next->id)
            {
                delete=wlk->next;
                delete->prev=wlk->prev;
                wlk->next=delete->next;
                free(delete);
                break;
            }
            wlk=wlk->next;
        }
    }
    (n_students)--;
printf("The student has been deleted successfully.\n");  
update();  
}

void display(student* nod)
{
    if(nod->tuition_status=='Y')
    {
        printf("Student Name: %s %s\n",nod->f_name,nod->l_name);
        printf("Student ID: %d\n",nod->id);
        printf("Number of courses enrolled: %d\n",nod->n_courses);
        printf("\nCourse No\tCourse Name\tCredits\tGrade\n");
        for(int i=0;i<nod->n_courses;i++)
        {
            printf("%s\t",nod->courses[i].c_number);
            printf("\t %s",nod->courses[i].c_name);
            printf("\t %d",nod->courses[i].credit_hours);
            printf("\t %c\n",nod->courses[i].grade);
        }
        printf("\nTotal number of credits: %d\n",nod->total_credits);
        printf("Mid-Semester GPA: %.2lf\n",nod->gpa);
       
    }
    else if(nod->tuition_status=='N')
    {
        printf("The student you entered did not pay his/her tuition.\n"); 
        printf("Student Name: %s %s\n",nod->f_name,nod->l_name);
        printf("Student ID: %d\n",nod->id);
        printf("Number of courses enrolled: %d\n",nod->n_courses);
        printf("\nCourse No\tCourse Name\tCredits\n");
        for(int i=0;i<nod->n_courses;i++)
        {
            printf("%s\t",nod->courses[i].c_number);
            printf("\t %s",nod->courses[i].c_name);
            printf(" \t %d \n",nod->courses[i].credit_hours);
        }
        printf("\nTotal number of credits: %d\n",nod->total_credits);
        printf("To access the grade report you should pay: %d$\n",nod->tuition);      
    }

}

void swap(course *c1,course *c2)
{
  course temp;
  temp= *c1;
  *c1=*c2;
  *c2=temp;
}

void fill_output()
{
    FILE*out;
    out=fopen("output.txt","w");
    student*node;
    node=head;
    for(int j=0;j<n_students;++j)
    {
        fprintf(out,"Student Name: %s %s\n",node->f_name,node->l_name);
        fprintf(out,"Student ID: %d\n",node->id);
        fprintf(out,"Number of courses enrolled: %d\n",node->n_courses);
        fprintf(out,"\nCourse No\tCourse Name\tCredits\tGrade\n");
            for(int i=0;i<node->n_courses;i++)
            {
            for(int j=i+1 ; j< node->n_courses ; j++)
                {
                    if(toupper(node->courses[i].c_number[0])>toupper(node->courses[j].c_number[0]))
                    {
                        swap(&node->courses[i],&node->courses[j]);
                    }
                }
            }
        for(int i=0;i<node->n_courses;i++)
        {
            fprintf(out,"%s\t",node->courses[i].c_number);
            fprintf(out,"\t %s",node->courses[i].c_name);
            fprintf(out,"\t %d",node->courses[i].credit_hours);
            fprintf(out,"\t %c\n",node->courses[i].grade);
        }
    fprintf(out,"\nTotal number of credits: %d\n",node->total_credits);
    fprintf(out,"Mid-Semester GPA: %.2lf\n",node->gpa);
    fprintf(out,"\n---------------------------------------------------\n");
     
     node=node->next;
   }
        fclose(out);
}


int main(){ 
int choice, n_credits, id;
student*st,*node,*temp,*stud,*nod;
head=(student*)malloc(sizeof(student));
in = fopen("stData.txt", "r");
if(in == NULL)
    {
    printf("FILE NOT FOUND!");    
    }
fscanf(in, "%d %d", &n_students, &tuition_rate);
head->next = NULL; 
temp = head;
for(int k=1; k<=n_students; k++)
    {
        node=(student*)malloc(sizeof(student)); 
        node->next = NULL;  

        temp->next = node;
        node->prev=temp;
        temp = temp->next;    
    }
st=head;
for (int i = 0; i < n_students; i++)
  {
fscanf(in, "%s %s %d %c %d\n", st->f_name, st->l_name, &(st->id), &(st->tuition_status), &(st->n_courses));
    for (int j=0; j < st->n_courses; j++)
    {
      fscanf(in, "%s %s %d %c", st->courses[j].c_name, st->courses[j].c_number, &st->courses[j].credit_hours, &st->courses[j].grade);
    }
    st->gpa=calculate_gpa(st);
    st->tuition=payment(st);
    st=st->next;
  }

do
{    
    menu();
    scanf("%d", &choice);

        switch (choice){        
          
            case 1: //Add a student
            printf("Please enter the ID: ");
            scanf("%d",&id);
            student*std;
            std=head;
            while(std!=NULL)
            {
            if(std->id==id)
            {
            printf("That student already exists.\n");
            printf("Enter a new ID: ");
            scanf("%d", &id);  
            std=head;  
            }
            else
            std=std->next;
            }
            stud=fill_student(id);
            insert_student(stud);
            update();
            break;

            case 2: //Update a student’s course Grade
            printf("Please enter the ID of the student you want to change his grade: ");
            scanf("%d",&id);
            nod=search(id);
            update_grade(nod);
            break;

            case 3: //Delete a student
            printf("Please enter the ID of the student you want to delete: ");
            scanf("%d",&id);
            nod=search(id);
            delete_student(nod);
            break;

            case 4: //Search for a student
            printf("Please enter the ID of the student: ");
            scanf("%d",&id);
            nod=search(id);
            if(nod==NULL)
            {
                printf("The ID you entered is not registered on the list.");
            }
            else
            {
                display(nod);
            }
            break;

            case 5: //Exit
                update();
                fill_output();
                printf("Goodbye, have a good day!\n");
                fclose(in);
            break;
            default:
            printf("\n\nInvalid input, try another input\n");
        }

}while(choice != 5);

return 0;    
}