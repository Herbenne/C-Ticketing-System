#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
// GROUP PROJECT
// Somo, Herbenne Rey V.
// Oreas, Nyl Bhoy
// Rapada, Prince Benmar
typedef struct ticket //for alternative names
{
    int id; // this is for ID to identify the user in the program, its like a passcode in case you wanted to update or edit
    char name[20]; // Names of user for ticekting, limits of 20 characters
    char movie[50]; // Names of Movie that user will type, limits of 50 character
    int seat; // this is for seat number of user on ticketing
    int timer; // this timer is for scheduled TIME of Movie
}ticket;

void create(); // create function, to make a new reservtion
void read(); // read the previous reservation or data that has been listed in text file
void update(); // updating the existing ticket from the start
void del(); // termination of existing ticket reservation

void delay(unsigned int mseconds){
    clock_t goal = mseconds + clock(); //this is for <time.h> to activate random number
    while(goal > clock());
}

int main(){ // this is simple int main where you can find the MENU option, then declaring argumentation (if statement) for user to pick 1-4.
    int pick;
    do
    {// this is the MENU
        system("COLOR 0B");
        printf("=================================================================\n=\t\t\t\t\t\t\t\t=\n=\t\tWELCOME TO OUR TICKETING SYSTEM\t\t\t=\n=\t\t\t\t\t\t\t\t=\n=================================================================");
        printf("\n[1] FOR CREATE\n");
        printf("[2] FOR READ\n");
        printf("[3] FOR UPDATE\n");
        printf("[4] FOR DELETE\n");
        printf("\n\n[0] FOR EXIT\n");
        printf("\nPLEASE ENTER YOUR INPUT: ");
        scanf("%d", &pick);
        if(pick == 1){ // if the user choose 1 the function of CREATE will run
            system("cls");
            create();
        }
        else if(pick == 2){ // if the user choose 2 the function of READ will run
            system("cls");
            read();
        }
        else if(pick == 3){ // if the user choose 3 the function of UPDATE will run
            system("cls");
            update();
        }
        else if(pick == 4){ // if the user choose 4 the function of DELETE will run
            system("cls");
            del();
        }
        else
            printf("\n\nInvalid Input!"); // then if the user input none of the choice, then it will says "Invalid Input"
    }while(pick!=0);

}

void create() // this is the program of CREATE function
{
    ticket *s; // this is the typedef struct above to use the alternative.
    FILE *fp; // this file pointer is to open a file.
    int i, n, j;
    printf("How many Ticket will you buy?(MAXIMUM OF 5): "); // this is where the user will type how many tickets he/she wants MAXof5
    scanf("%d", &n);
        if(n > 5){ // this one is fot the user that chose more than 5 tickets
            printf("PLEASE READ THE INSTRUCTIONS!\n");
            create(); // to reset in CREATE program
        }
    s = (ticket*)calloc(n, sizeof(ticket));
    fp = fopen("record.txt","w"); // This text file is where tha data will be recorded.
    for(i = 0; i < n; i++)
    {;
        printf("\nPlease Enter your own unique PASSCODE (NUMBERS ONLY): ");
        scanf("%d", &s[i]); // this is where the user will insert his own unique PASSCODE for identification

        printf("\nPlease Type the MOVIE that you like(NOTE NO SPACE): ");
        scanf("%s", s[i].movie); // this is the inside of typedef where the user will input his desire name movie

        s[i].seat = rand()%100; // randomized number 1-100 for movie seat
        s[i].timer = rand()%10; // randomized number 1-10 for scheduled time in movie
        printf("\nYour SEAT NUMBER is %d\n", s[i].seat); // this is inside of typedef struct which is the randomized number seat/
        printf("\nYour SCHEDULED TIME is %dpm\n", s[i].timer); // same with timer, this is where the randomized number will put as a scheduled time

        fflush(stdin); // this is to make the ouput buffer
        printf("\nEnter the Name of Customer: " );
        scanf("%s", s[i].name); // this is also in struct to make a name for user.

        fwrite(&s[i], sizeof(ticket), 1, fp); // and this is where the data will input from the pointed array.
    }
    fclose(fp); // To close the pointed stream
}

void read() // READ function or program
{
    ticket sl;
    FILE *fp;
    int j;
    fp = fopen("record.txt","r"); // "R" to read the input data in the recorded text file.
    while(fread(&sl,sizeof(ticket),1, fp))
    {
        printf("CUSTOMER: %-20s \nPASSCODE: %-5d \nMOVIE: %-50s\nSEAT-NUMBER: %d\nSCHEDULED-TIME: %dpm\n", sl.name, sl.id, sl.movie, sl.seat, sl.timer);
    } // this is where tha organized data will show up.

    fclose(fp); // To close the pointed stream
}

void update() //to make a UPDATE program we will need a 2 text file, temporary text file and the original text file.
{
    ticket sl;
    FILE *fp, *fp1;
    int j, id, found = 0;
    fp = fopen("record.txt", "r"); // We will read the inserted data in record.txt
    fp1 = fopen("temp.txt", "w"); // Then we will edit it in the temporary textfile.
    printf("Enter The unique PASSCODE that you wanted to update: "); // You will choose What ID/PASSCODE of the user that you wanted to change.
    scanf("%d", &id);
    while(fread(&sl, sizeof(ticket),1,fp))
    {
        if(sl.id == id){ // Then the ID you insrted will be edited not only that also the entire data.
            found = 1; // IF the DATA has found we will need to type our new data like in CREATE function.
            srand(time(NULL));
            sl.seat = rand()%100;
            printf("\nYour NEW SEAT NUMBER TIME is %d", sl.seat);
            fflush(stdin);
            printf("\nPlease Type the NEW MOVIE that you like(NOTE NO SPACE): ");
            scanf("%[^\n]s", sl.movie);
            fflush(stdin);
            printf("\nEnter the NEW Name of Customer: " );
            scanf("%[^\n]s", sl.name);
        }
        fwrite(&sl,sizeof(ticket),1,fp1);
    }
    fclose(fp); // To close the pointed stream
    fclose(fp1); // To close the second pointed stream
    if(found){ // this is the argumentation if the insrted ID has found or not.
        fp = fopen("record.txt", "w"); // if the ID has found you will edit the recorded file
        fp1 = fopen("temp.txt", "r"); // then read the passcode in the temporary one

        while(fread(&sl, sizeof(ticket),1,fp1))
        {
            fwrite(&sl, sizeof(ticket),1,fp);
        }

        fclose(fp); // To close the first pointed stream
        fclose(fp1); // To close the second pointed stream
    }
    else
        printf("\nRECORD NOT FOUND\n");
}

void del() // Lastly the DELETION of Reservation Tickets
{          // Just like update we need 2 text file to make a change because we need to identify what specific data that we need to change.
    ticket sl;
    FILE *fp, *fp1;
    int j, id, found = 0;
    fp = fopen("record.txt", "r"); // Read the data in record.txt
    fp1 = fopen("temp.txt", "w"); // write the data but only the ID
    printf("Enter the unique CODE you wanted to DELETE: ");
    scanf("%d", &id); //insert ID
    while(fread(&sl, sizeof(ticket),1,fp))
    {
        if(sl.id == id){ //argumentation if the iserted ID is equal to the recorded ID
            found = 1; // TRUE = Found = TRUE
        }
        else
            fwrite(&sl,sizeof(ticket),1,fp1);
    }
    fclose(fp); // To close the first pointed stream
    fclose(fp1);// To close the second pointed stream
    if(found){ //Argumentation if FOUND is true or FALSE
        fp = fopen("record.txt", "w"); // RECORD = WRITE
        fp1 = fopen("temp.txt", "r"); // TEMP = READ

        while(fread(&sl, sizeof(ticket),1,fp1))
        {
            fwrite(&sl, sizeof(ticket),1,fp);
        }

        fclose(fp); // To close the first pointed stream
        fclose(fp1);// To close the second pointed stream
    }
    else
        printf("\nRECORD NOT FOUND\n"); //this will be the output when the user inserted the non-existing ID/PASSCODE
}
