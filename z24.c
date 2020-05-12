#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <float.h>
typedef struct{
    char name[128];
    int group;
    double rating;
} Student;
Student** mass(FILE* input_file, int size);

Student** mass(FILE* input_file, int size){
    Student** a;
    char str[128];
    char *istr;
    char sep[10]=" ";
    a=(Student**)malloc(size*sizeof(Student*));
    for (int i=0; i<size; i++){
        a[i]=(Student*)malloc(sizeof(Student));
        fgets (str, 128 , input_file);
        istr = strtok (str,sep);
        if (istr != NULL){
            strcpy(a[i]->name,istr);
        }
        else{
            printf("not enough data");
            return -1;
        }
        istr = strtok (NULL,sep);
        if (atoi(istr)!=0){
            if (istr != NULL){
                a[i]->group=atoi(istr);
            }
            else{
                printf("not enough data");
                return -1;
            }
        }
        else{
            printf("incorrect data");
            return -1;
        }
        istr = strtok (NULL,sep);
        if (atof(istr)!=0){
            if (istr != NULL){
                a[i]->rating=atof(istr);
               // printf("%lf\n", a[i]->rating);
            }
            else{
                printf("not enough data");
                return -1;
            }
        }
        else{
            printf("incorrect data");
            return -1;
        }
        istr = strtok (NULL,sep);
        if (atof(istr)!=0){
            printf("extra data");
        }
    }
    return a;
}



int main(void){
    FILE* students;
    FILE* exp_students;
    FILE* output_file;
    Student** arrstudents;
    Student** arrexp_students;
    Student** temp;
    char str[514];
    int size=1;
    int size_exp=0;
    int k=0;
    students=fopen("students.txt", "r");
    exp_students=fopen("exp_students.txt", "r");
    if (fgets(str, 514, students)==NULL){
            printf("Error! No data!\n");
            return -1;
        }
        else{
            while(fgets(str, 514, students)){
                size++;
            }
            while(fgets(str, 514, exp_students)){
                size_exp++;
            }
            rewind(students);
            rewind(exp_students);
            arrstudents=mass(students, size);
            if (size_exp!=0){
                   arrexp_students=mass(exp_students, size_exp);
            }
            /*for (int i=0; i<size; i++){
                printf("%s ", arrstudents[i]->name);
                printf("%d ", arrstudents[i]->group);
                printf("%lf\n", arrstudents[i]->rating);
            }*/
            fclose(students);
            fclose(exp_students);
            if (size_exp!=0){
                for (int j=0; j<size_exp; j++){
                    for (int i=0; i<size; i++){
                        if ((strcmp(arrstudents[i]->name, arrexp_students[j]->name)==0) && (arrstudents[i]->group==arrexp_students[j]->group)){
                            k++;
                            free(arrstudents[i]);
                            for (int s=i; s<size-1; s++){
                                arrstudents[s]=arrstudents[s+1];
                            }
                        }
                    }
                }
                if (k!=0){
                    temp=(Student**)realloc(arrstudents, (size-k)*sizeof(Student*));
                    if(temp){
                        arrstudents=temp;
                    }
                }
            }
            output_file=fopen("data.txt", "w");
            for (int i=0; i<size-k; i++){
                fprintf(output_file, "%s ", arrstudents[i]->name);
                fprintf(output_file, "%d ", arrstudents[i]->group);
                fprintf(output_file, "%lf\n", arrstudents[i]->rating);
            }
            for (int i=0; i<size-k; i++){
                free(arrstudents[i]);
            }
            free(arrstudents);
            if(size_exp!=0){
                for (int i=0; i<size_exp; i++){
                    free(arrexp_students[i]);
                }
                free(arrexp_students);
            }
            return 0;
        }
}
