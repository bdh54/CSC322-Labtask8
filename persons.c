#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMAL_PEOPLE 10
#define MAXIMAL_STRING_LENGTH 128

/*----Define data types */
typedef char string[MAXIMAL_STRING_LENGTH];
typedef struct personTag {
    string name;
    int age;
    struct personTag *bestFriend;
    } personType;
typedef personType *personPointer;
typedef personPointer peoplePointers[MAXIMAL_PEOPLE];

//Malloc function
void * Malloc(size_t Size) {

    void * Memory;

    if ((Memory = malloc(Size)) == NULL) {
        perror("Cannot malloc");
        exit(EXIT_FAILURE);
    } else {
        return(Memory);
    }
}

//Read in names and ages function
void readNamesAgesBesties(personPointer persons[], int *personCounter) {
//define name variable to be held to check if exit is entered before we allocate
    string name;
//define int i to be used in for loop
    int i;
//define int j for interior for loop 
    int j;
//Loop to read in the persons information
    while(*personCounter < MAXIMAL_PEOPLE) {
//get the name
        printf("Please enter person name, \"exit\" to exit : ");
        scanf("%s", name);
//if exit is entered, break
        if (strcmp(name, "exit") == 0) {
            break;
        }
//if we do not wish to exit, allocate memory for a new person
        personPointer person = (personPointer)Malloc(sizeof(personType));

//if memory is successfully allocated, put the name into the person
        strcpy(person -> name, name);

//get the persons age
        printf("Please enter %s's age : ", person -> name);
        scanf("%d", &(person  -> age));

//add person to the persons array
        persons[*personCounter] = person;
//increment personsCounter
        (*personCounter)++;

    }
//Once the people are read in, set best friends
    for(i = 0; i < *personCounter; ++i) {
        printf("Who is %s's best friend? ", persons[i] -> name);
        scanf("%s", name);
//interior for loop to find best friend in array
        for(j = 0; j < *personCounter; ++j) {
            if (strcmp(persons[j] -> name, name) == 0) {
                persons[i] -> bestFriend = persons[j];
                break;
            }
        }
    }

    
}

void displayPersons(personPointer persons[], int personCounter) {
//int i to be used in for loop
    int i;
    for(i = 0; i < personCounter; ++i) {
//Print out all the info of the person
        printf("%-20s is %3d, and his/her best friend is %s\n", persons[i] -> name, persons[i] -> age, persons[i] -> bestFriend -> name);
    }

}


int main(void) {
//define an array of person Pointers
    peoplePointers persons;
//define a counter
    int personCounter = 0;

//Call readNamesAges function to read in persons names and ages
    readNamesAgesBesties(persons, &personCounter);
//Call display info to display the persons array's information
    displayPersons(persons, personCounter);
}