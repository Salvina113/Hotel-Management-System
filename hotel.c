#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Customer
{
    int roomNo;
    char name[50];
    int age;
    char gender[10];
    char phone[15];
    char roomType[20];
    int days;
};

void bookRoom();
void viewRooms();
void checkIn();
void checkOut();
void searchCustomer();
void updateBooking();
void cancelBooking();
void generateBill();
void reports();

int main()
{
    int choice;

    while(1)
    {
        printf("\n====================================");
        printf("\n     HOTEL MANAGEMENT SYSTEM");
        printf("\n====================================");
        printf("\n1. Book Room");
        printf("\n2. View Rooms");
        printf("\n3. Check In");
        printf("\n4. Check Out");
        printf("\n5. Search Customer");
        printf("\n6. Update Booking");
        printf("\n7. Cancel Booking");
        printf("\n8. Generate Bill");
        printf("\n9. Reports");
        printf("\n10. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                bookRoom();
                break;

            case 2:
                viewRooms();
                break;

            case 3:
                checkIn();
                break;

            case 4:
                checkOut();
                break;

            case 5:
                searchCustomer();
                break;

            case 6:
                updateBooking();
                break;

            case 7:
                cancelBooking();
                break;

            case 8:
                generateBill();
                break;

            case 9:
                reports();
                break;

            case 10:
                printf("\nThank You!\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}

void bookRoom()
{
    FILE *fp;
    struct Customer c;

    fp = fopen("customers.dat", "ab");

    if(fp == NULL)
    {
        printf("\nFile cannot be opened!");
        return;
    }

    printf("\n========== ROOM BOOKING ==========\n");

    printf("Enter Room Number : ");
    scanf("%d", &c.roomNo);

    printf("Enter Customer Name : ");
    scanf(" %[^\n]", c.name);

    printf("Enter Age : ");
    scanf("%d", &c.age);

    printf("Enter Gender : ");
    scanf("%s", c.gender);

    printf("Enter Phone Number : ");
    scanf("%s", c.phone);

    printf("Enter Room Type (Single/Double/Deluxe) : ");
    scanf("%s", c.roomType);

    printf("Enter Number of Days : ");
    scanf("%d", &c.days);

    fwrite(&c, sizeof(struct Customer), 1, fp);

    fclose(fp);

    printf("\n=================================");
    printf("\nRoom Booked Successfully!");
    printf("\nCustomer Details Saved.");
    printf("\n=================================\n");
}

void viewRooms()
{
    FILE *fp;
    struct Customer c;

    fp = fopen("customers.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo bookings found.\n");
        return;
    }

    printf("\n=========== BOOKED ROOMS ===========\n");

    while(fread(&c, sizeof(struct Customer), 1, fp))
    {
        printf("\nRoom No      : %d", c.roomNo);
        printf("\nName         : %s", c.name);
        printf("\nAge          : %d", c.age);
        printf("\nGender       : %s", c.gender);
        printf("\nPhone        : %s", c.phone);
        printf("\nRoom Type    : %s", c.roomType);
        printf("\nDays         : %d", c.days);
        printf("\n-----------------------------------");
    }

    fclose(fp);
}

void checkIn()
{
    int room;

    printf("\n========== CHECK IN ==========");

    printf("\nEnter Room Number: ");
    scanf("%d",&room);

    printf("\nRoom %d Checked In Successfully!\n", room);
}

void checkOut()
{
    int room;

    printf("\n========== CHECK OUT ==========");

    printf("\nEnter Room Number: ");
    scanf("%d",&room);

    printf("\nRoom %d Checked Out Successfully!\n", room);
}

void searchCustomer()
{
    FILE *fp;
    struct Customer c;
    int room, found = 0;

    fp = fopen("customers.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo records found.");
        return;
    }

    printf("\nEnter Room Number to Search: ");
    scanf("%d", &room);

    while(fread(&c, sizeof(struct Customer), 1, fp))
    {
        if(c.roomNo == room)
        {
            printf("\nCustomer Found");
            printf("\n------------------------");
            printf("\nRoom No   : %d", c.roomNo);
            printf("\nName      : %s", c.name);
            printf("\nAge       : %d", c.age);
            printf("\nGender    : %s", c.gender);
            printf("\nPhone     : %s", c.phone);
            printf("\nRoom Type : %s", c.roomType);
            printf("\nDays      : %d", c.days);

            found = 1;
            break;
        }
    }

    if(!found)
        printf("\nCustomer Not Found.");

    fclose(fp);
}

void updateBooking()
{
    FILE *fp;
    struct Customer c;
    int room, found = 0;

    fp = fopen("customers.dat","rb+");

    if(fp == NULL)
    {
        printf("\nNo Records Found.");
        return;
    }

    printf("\nEnter Room Number : ");
    scanf("%d",&room);

    while(fread(&c,sizeof(struct Customer),1,fp))
    {
        if(c.roomNo == room)
        {
            found = 1;

            printf("\nEnter New Phone Number : ");
            scanf("%s",c.phone);

            printf("Enter New Number of Days : ");
            scanf("%d",&c.days);

            fseek(fp,-sizeof(struct Customer),SEEK_CUR);
            fwrite(&c,sizeof(struct Customer),1,fp);

            printf("\nBooking Updated Successfully.");
            break;
        }
    }

    if(!found)
        printf("\nRoom Not Found.");

    fclose(fp);
}

void cancelBooking()
{
    checkOut();
}

void generateBill()
{
    FILE *fp;
    struct Customer c;
    int room, found = 0;
    float rent, total;

    fp = fopen("customers.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo Records Found.");
        return;
    }

    printf("\nEnter Room Number : ");
    scanf("%d",&room);

    while(fread(&c,sizeof(struct Customer),1,fp))
    {
        if(c.roomNo == room)
        {
            found = 1;

            if(strcmp(c.roomType,"Single")==0)
                rent = 1000;
            else if(strcmp(c.roomType,"Double")==0)
                rent = 1800;
            else
                rent = 2500;

            total = rent * c.days;

            printf("\n========== HOTEL BILL ==========");
            printf("\nCustomer Name : %s",c.name);
            printf("\nRoom Number   : %d",c.roomNo);
            printf("\nRoom Type     : %s",c.roomType);
            printf("\nDays Stayed   : %d",c.days);
            printf("\nRent / Day    : %.2f",rent);
            printf("\n-------------------------------");
            printf("\nTotal Amount  : %.2f",total);
            printf("\n===============================\n");

            break;
        }
    }

    if(!found)
        printf("\nCustomer Not Found.");

    fclose(fp);
}

void reports()
{
    FILE *fp;
    struct Customer c;
    int total = 0;

    fp = fopen("customers.dat","rb");

    if(fp == NULL)
    {
        printf("\nNo Records Found.");
        return;
    }

    while(fread(&c,sizeof(struct Customer),1,fp))
    {
        total++;
    }

    fclose(fp);

    printf("\n========== REPORT ==========");
    printf("\nTotal Booked Rooms : %d",total);
    printf("\nAvailable Rooms    : %d",20-total);
    printf("\nTotal Rooms        : 20");
    printf("\n============================\n");
}