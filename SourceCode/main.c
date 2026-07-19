#include <stdio.h>
#include <ctype.h>
#include <string.h>

int booked[5][6];
char customerName[5][6][30];

void displaySeatMap(void);
void bookSeat(void);
void cancelSeat(void);
void searchBooking(void);
void showSummary(void);
void showMenu(void);
int getPrice(int rowIndex);
int isValidSeat(int rowIndex, int seatIndex);

int main(void) {
    int choice;

    printf("\n+-----+-----+-----+-----+-----+-----+-----+-----+\n");
    printf("          CINEMA SEAT RESERVATION SYSTEM\n");
    printf("+-----+-----+-----+-----+-----+-----+-----+-----+\n");

    do {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaySeatMap();
                break;
            case 2:
                bookSeat();
                break;
            case 3:
                cancelSeat();
                break;
            case 4:
                searchBooking();
                break;
            case 5:
                showSummary();
                break;
            case 6:
                printf("\nThank you for using!!\n\n");
                break;
            default:
                printf("\nInvalid choice!!\n");
        }
    } while (choice != 6);

    return 0;
}

void displaySeatMap(void) {
    int i, j;

    printf("\n");
    printf("           '------------------------------------------------'\n");
    printf("          /                     S C R E E N                 \\\n");
    printf("          '-------------------------------------------------'\n\n");

    printf("\n");

    for (i = 0; i < 5; i++) {
        printf("           ");
        for (j = 0; j < 6; j++) {
            if (booked[i][j]) {
                if (i==0) {
                    printf("[      ]");
                } else {
                    printf(" [    ] ");
                }
            } else {
                if (i==0) {
                    printf("[  %c%d  ]", 'A' + i, j + 1);
                } else {
                    printf(" [ %c%d ] ", 'A' + i, j + 1);
                }
            }
        }

        if (i == 0) {
            printf("       Premium : %d\n", getPrice(i));
        } else {
            printf("       Regular : %d\n", getPrice(i));
        }
    }
}

void bookSeat(void) {
    char rowChar;
    int rowIndex, seatNum, seatIndex;
    char name[30];

    displaySeatMap();

    printf("\nEnter row letter: ");
    scanf(" %c", &rowChar);
    rowChar = toupper(rowChar);
    rowIndex = rowChar - 'A';

    printf("Enter seat number: ");
    scanf("%d", &seatNum);
    seatIndex = seatNum - 1;

    if (!isValidSeat(rowIndex, seatIndex)) {
        printf("\nInvalid seat!!\n");
        return;
    }

    if (booked[rowIndex][seatIndex]) {
        printf("\nSeat %c%d is already booked!\n", rowChar, seatNum);
        return;
    }

    printf("Enter customer name: ");
    scanf("%s", name);

    booked[rowIndex][seatIndex] = 1;
    strcpy(customerName[rowIndex][seatIndex], name);

    printf("\nSeat %c%d booked successfully for %s. Price: %d\n", rowChar, seatNum, name, getPrice(rowIndex));
}

void cancelSeat(void) {
    char rowChar;
    int rowIndex, seatNum, seatIndex;

    printf("\nEnter row letter: ");
    scanf(" %c", &rowChar);
    rowChar = toupper(rowChar);
    rowIndex = rowChar - 'A';

    printf("Enter seat number: ");
    scanf("%d", &seatNum);
    seatIndex = seatNum - 1;

    if (!isValidSeat(rowIndex, seatIndex)) {
        printf("\nInvalid seat!!\n");
        return;
    }

    if (!booked[rowIndex][seatIndex]) {
        printf("\nSeat %c%d is already free!!\n", rowChar, seatNum);
        return;
    }

    printf("\nCancelling booking for %s at seat %c%d\n", customerName[rowIndex][seatIndex], rowChar, seatNum);

    booked[rowIndex][seatIndex] = 0;
    strcpy(customerName[rowIndex][seatIndex], "");

    printf("Booking cancelled successfully.\n");
}

void searchBooking(void) {
    char searchh[30];
    int i, j, found = 0;

    printf("\nEnter customer name to search: ");
    scanf("%s", searchh);

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++) {
            if (strcmp(customerName[i][j], searchh) == 0) {
                printf("Found: Seat %c%d booked for %s\n", 'A' + i, j + 1, searchh);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No bookings found under the name \"%s\".\n", searchh);
    }
}

void showSummary(void) {
    int i, j;
    int totalSeats = 30;
    int totalBooked = 0;
    int revenue = 0;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++) {
            if (booked[i][j]) {
                totalBooked++;
                revenue += getPrice(i);
            }
        }
    }

    printf("\n+----------------- BOOKING SUMMARY -----------------+\n");
    printf(" Total seats     : %d\n", totalSeats);
    printf(" Seats booked    : %d\n", totalBooked);
    printf(" Seats available : %d\n", totalSeats - totalBooked);
    printf(" Revenue so far  : %d\n", revenue);
    printf("+-----------------------------------------------------+\n");
}

int getPrice(int rowIndex) {
    if (rowIndex == 0) {
        return 250;
    } else {
        return 150;
    }
}

int isValidSeat(int rowIndex, int seatIndex) {
    return (rowIndex >= 0 && rowIndex < 5 && seatIndex >= 0 && seatIndex < 6);
}

void showMenu(void) {
    printf("\n+--------------------- MENU ---------------------+\n\n");
    printf(" 1. View Seat Availability\n");
    printf(" 2. Book a Seat\n");
    printf(" 3. Cancel a Booking\n");
    printf(" 4. Search Booking by Name\n");
    printf(" 5. View Booking Summary\n");
    printf(" 6. Exit\n");
    printf("\n+------------------------------------------------+\n");
}
