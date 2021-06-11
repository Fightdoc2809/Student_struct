#define LINES 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct student
{
    unsigned int matrnr;
    char *lastname;
    struct student* next;
}Student, *Student_p;

Student_p StudentAlloc (char* info);
void StudentFree(Student_p info);
Student_p deepCopy(Student_p s);
Student_p shallowCopy(Student_p s);
int StudentEquals (Student_p s1, Student_p s2);
int hashCode(int);
void printStudents(Student_p*, int);
void print_menu (void);
void press_enter (void);
void clearscreen (int);

int i = 719;

int main() {

    FILE *in = stdin;
    char Datei [50];
    char buffer[400];
    char choice;
    int i = 0;
    struct student* hashArray[i];
    Student_p students [100];
    Student_p *ptr = students;


    for (int j = 0; j < 100; ++j) {
        students[j] = NULL;
    }

    printf("Aus welcher Datei möchtest du deine Eingaben einlesen? ");
    scanf("%s", Datei);
    in = fopen(Datei, "r");
    if (!in){
        fprintf(stderr, "Datei konnte nicht gefunden werden");
        exit(EXIT_FAILURE);
    }


    while (fgets(buffer, 400, in)){
        students[i] = StudentAlloc(buffer);
        i++;

    }
    printf("Alle Studenten wurden eingelesen");
    fflush(stdin);
    press_enter();
    for(int i = 0; i < 9; i++)
        printf("Adresse: %d\tName: %s\t MatNr.: %05d\n", students[i], students[i]->lastname, students[i]->matrnr);
    press_enter();
    clearscreen(LINES);


    do {
        clearscreen(LINES);
        print_menu();
        scanf("%c", buffer);                      // read a whole line from keyboard
        choice = buffer[0];                 // takes the first character as input
        fflush(stdin);
        switch (choice) {
            case '1':
                printStudents(ptr, 100);
                break;
            default : break;
        } /* end of switch */
    } while (choice!='0'); /* end of do-while */


printf ("Thanks for using the modern file-card system.\n");
return 0;
}

int hashCode(int matrnr){
    return matrnr % i;
}

void printStudents(Student_p* pointer, int laenge){

    Student_p pointer2;

    for(int i = 0; i < laenge; i++){
        pointer2 = pointer[i];
        if (pointer2)
        {
            printf("Adresse: %p\tName: %s\t MatNr.: %05d\n", pointer2, pointer2->lastname, pointer2->matrnr);
        }
    }
    press_enter();
}

Student_p StudentAlloc(char* info){
    char delimit[] = ";\n";

    Student_p AllocStudent;
    AllocStudent = malloc(sizeof(struct student));
    AllocStudent->matrnr = atoi(strtok(info, delimit));
    AllocStudent->lastname = malloc(sizeof(strtok(NULL,delimit)));
    strcpy(AllocStudent->lastname, strtok(NULL,delimit));
    return AllocStudent;
}

void StudentFree(Student_p info){
    free(info);

}

Student_p deepCopy(Student_p s){


}

Student_p shallowCopy(Student_p s){
    Student_p shallow_P = s;
    return shallow_P;
}

int StudentEquals (Student_p s1, Student_p s2){
    if (s1->matrnr == s2->matrnr && strcmp(s1->lastname, s2->lastname)){
        return 1;
    }
    return 0;
}

void print_menu (void) {
    printf (" Menu\n");
    printf ("-----------------------------\n\n");
    printf ("1. show Students\n");
    printf ("2. Free Students\n");
    printf ("3. shallow copy Students\n");
    printf ("4. deep Copy Students\n");
    printf ("5. Students Equal?\n");
    printf ("-----------------------------\n\n");
    printf ("To end the program, please press Enter without a choice\n");
    printf ("Please make a choice: ");
}

void clearscreen (int lines) {
    int i;
    for (i=0; i<lines; i++) printf ("\n");
}

void press_enter (void) {
    char ch=0;
    printf ("\nPlease press ENTER to continue ...\n");
    while (ch!=10) ch=getchar();
}