#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define batchSize 420
#define nameSize 69

int mainMenu();
void newRecord();
void printRecord(int recordIndex);
void printAllRecords();
void printDatabase(int limit); //for debugging purposes
void deleteRecord();
void deleteAllRecords();
void capitalize(char* word);
int findIndex();

int batchArray[batchSize*4]={0};
int regNoArray[batchSize*4]={0};
char* firstNameArray[batchSize*4][nameSize]={0};
char* lastNameArray[batchSize*4][nameSize]={0};
float gpaArray[batchSize*4]={0};

int main() {
    // demo record 1
    batchArray[4]=17;
    regNoArray[4]=371;
    memcpy(firstNameArray[4], "Rasika", sizeof(firstNameArray[4]));
    memcpy(lastNameArray[4], "Warnakulasuriya", sizeof(firstNameArray[4]));
    gpaArray[4]=3.9;
    // demo record 2
    batchArray[2]=17;
    regNoArray[2]=370;
    memcpy(firstNameArray[2], "Lahiru", sizeof(firstNameArray[2]));
    memcpy(lastNameArray[2], "Range", sizeof(firstNameArray[2]));
    gpaArray[2]=3.8;
    // demo record 3
    batchArray[1]=17;
    regNoArray[1]=372;
    memcpy(firstNameArray[1], "Vano", sizeof(firstNameArray[1]));
    memcpy(lastNameArray[1], "Warna", sizeof(firstNameArray[1]));
    gpaArray[1]=3.7;
    // demo record 4
    batchArray[6]=17;
    regNoArray[6]=374;
    memcpy(firstNameArray[6], "Aveesha", sizeof(firstNameArray[6]));
    memcpy(lastNameArray[6], "Upasaka", sizeof(firstNameArray[6]));
    gpaArray[6]=3.6;
    // demo record 5
    batchArray[8]=1;
    regNoArray[8]=1;
    memcpy(firstNameArray[8], "A", sizeof(firstNameArray[8]));
    memcpy(lastNameArray[8], "B", sizeof(firstNameArray[8]));
    gpaArray[8]=1;
    printf("\nInitial data\n");
    printDatabase(10);
    printf("\nDelete signle record\n");
    deleteRecord(findIndex());
    printDatabase(10);
    printf("\nDelete all records\n");
    deleteAllRecords();
    printDatabase(10);
    return 0;
}
// generate a text-based main menu and return the selected option
int mainMenu() {
    int option;
    printf("--------------------------------------\nA VOLATILE STUDENT REGISTRATION SYSTEM\n--------------------------------------\n");
    printf("0. Quit\n1. Insert a student record\n2. Print a student record\n3. Print all student records\n4. Delete a student record\n");
    printf("------------------\nENTER OPTION [0-4]\n------------------\n>>> ");
    scanf("%d",&option);
    return option;
}
// make a new student record
void newRecord() {
    char firstName[nameSize];
    char lastName[nameSize];
    int i;
    // find the first empty record
    for (i=0; i<batchSize; i++) {

        if (batchArray[i]==0){
            break;
        }
    }
    printf("Enter batch (14/15/16/17): ");
    scanf("%d",batchArray+i);
    printf("Enter registration number: ");
    scanf("%d",regNoArray+i);
    printf("Enter first name         : ");
    scanf("%s",firstName);
    printf("Enter last name          : ");
    scanf("%s",lastName);
    printf("Enter cumulative GPA     : ");
    scanf("%f",gpaArray+i);
    // capitalize firstName and lastName and store
    capitalize(firstName);
    capitalize(lastName);
    memcpy(firstNameArray[i], firstName, sizeof(firstNameArray[i]));
    memcpy(lastNameArray[i], lastName, sizeof(firstNameArray[i]));
}
// print the recored with given regNo
void printRecord(int recordIndex) {

    if (recordIndex==-1) {
        printf("Record does not exist\n");
    }
    else {
        printf("Student %s %s (E/%d/%d) has a cumulative GPA of %.2f\n",firstNameArray[recordIndex],lastNameArray[recordIndex],batchArray[recordIndex],regNoArray[recordIndex],gpaArray[recordIndex]);
    }
}
// print all existing records
void printAllRecords() {
    int i;

    for (i=0; i<batchSize*4; i++) {
        
        if (batchArray[i]!=0) {
            printRecord(i);
        }
    }
}
// print the whole database including empty records
void printDatabase(int limit) {
    int i;

    for (i=0; i<limit; i++) {
        printf("%d ",i);
        printRecord(i);
    }
}
// delete the record with given regNo
void deleteRecord(int recordIndex) {

    if (recordIndex==-1) {
        printf("Record does not exist\n");
    }
    else {
        int i;
        batchArray[recordIndex]=0;
        regNoArray[recordIndex]=0;
        gpaArray[recordIndex]=0;

        for (i=0; i<nameSize; i++) {
            firstNameArray[recordIndex][i]=0;
            lastNameArray[recordIndex][i]=0;
        }
    }    
}
// clear the database
void deleteAllRecords() {
    int i;

    for (i=0; i<batchSize*4; i++) {
        
        if (batchArray[i]!=0) {
            deleteRecord(i);
        }
    }
}
// capitalize the first letter of the input string
void capitalize(char* word) {
    int i=1;
    word[0]=toupper(word[0]);

    while (word[i]!=0) {
        word[i]=tolower(word[i]);
        i++;
    }
}
// get query e no. and find corresponding array index
int findIndex() {
    char query[9];
    int queryBatch;
    int queryRegNo;
    int i;
    bool recordExists=0;
    printf("Enter registration number: ");
    scanf("%s",&query);
    // obtain batch and regNo from search query
    queryBatch=(query[2]-48)*10+(query[3]-48);
    queryRegNo=(query[5]-48)*100+(query[6]-48)*10+(query[7]-48);
    
    // find idex of matching regNo and batch
    for (i=0; i<batchSize*4; i++) {
        
        if (regNoArray[i]==queryRegNo && batchArray[i]==queryBatch) {
            recordExists=1;
            break;
        }
    }
    if (recordExists) {
        return i;
    }
    else {
        return -1;
    }
}