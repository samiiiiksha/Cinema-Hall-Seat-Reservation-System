#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct SeatNode {
    int row, col;
    struct SeatNode *next;
} SeatNode;

typedef struct CustomerNode {
    char name[30];
    int premiumCount;
    struct CustomerNode *next;
} CustomerNode;

typedef struct {
    char title[50];
    int booked[5][6];
    char customerName[5][6][30];
} Movie;

Movie *movies = NULL;
int movieCount = 0;
int movieCapacity = 0;
char adminUser[30] = "admin";
char adminPass[30] = "1234";

CustomerNode *customerTable[31];

void adminMenu(void);
void userMenu(void);
int adminLogin(void);
char *userLogin(void);

void addMovieNamed(const char *title);
void removeMovie(void);
void listMovies(void);
int selectMovie(void);

int strcicmp(const char *a, const char *b);
void merge(Movie arr[], int l, int m, int r);
void mergeSort(Movie arr[], int l, int r);
int binarySearchMovie(Movie arr[], int low, int high, const char *title);

int hashFunction(const char *name);
CustomerNode *loyalty(const char *name);
void recordPremiumBooking(const char *name);
void checkLoyaltyStatus(const char *name);

void displaySeatMap(Movie *m);
void bookSeat(Movie *m, const char *username);
void cancelSeat(Movie *m);
void searchBooking(Movie *m, const char *username);
void showSummary(Movie *m);
void showAllSummary(void);

int getPrice(int row);
int isValidSeat(int row, int col);
void toLowerStr(char *s);
int isAlphaStr(const char *s);
void freeAll(void);

int main(void) {
    int choice;

    printf("\n+-----+-----+-----+-----+-----+-----+-----+-----+\n");
    printf("          CINEMA SEAT RESERVATION SYSTEM\n");
    printf("+-----+-----+-----+-----+-----+-----+-----+-----+\n");

    addMovieNamed("The Odyssey");
    addMovieNamed("Peaky Blinders");
    addMovieNamed("Frankenstein");
    addMovieNamed("Inception");

    do {
        printf("\n+------------- MENU -------------+\n\n");
        printf(" 1. Login as User\n");
        printf(" 2. Login as Admin\n");
        printf(" 3. Exit\n\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: userMenu(); break;
            case 2: adminMenu(); break;
            case 3: printf("\nThank you for using!!\n\n"); break;
            default: printf("\nInvalid choice!!\n");
        }
    } while (choice != 3);

    freeAll();
    return 0;
}

int adminLogin(void) {
    char user[30], pass[30];

    printf("\n+---------- ADMIN LOGIN ----------+\n\n");
    printf("Username: ");
    scanf("%29s", user);
    printf("Password: ");
    scanf("%29s", pass);

    if (strcmp(user, adminUser) == 0 && strcmp(pass, adminPass) == 0) {
        printf("\nLogin successful!\n");
        return 1;
    }

    printf("\nInvalid credentials!!\n");
    return 0;
}

char *userLogin(void) {
    static char name[30];

    printf("\n+---------- USER LOGIN ----------+\n\n");
    printf("Enter your name: ");
    scanf("%29s", name);

    if (!isAlphaStr(name)) {
        printf("Invalid name, letters only!!\n");
        name[0] = '\0';
        return name;
    }

    toLowerStr(name);
    printf("\nWelcome, %s!!\n", name);
    return name;
}

void userMenu(void) {
    char *username = userLogin();
    if (username[0] == '\0') return;

    if (movieCount == 0) {
        printf("\nNo movies available right now. Check back later!!\n");
        return;
    }

    int choice, idx;
    do {
        printf("\n+---------- USER MENU (%s) ----------+\n", username);
        printf(" 1. List Movies\n");
        printf(" 2. View Seat Map\n");
        printf(" 3. Book Seat(s)\n");
        printf(" 4. Cancel a Booking\n");
        printf(" 5. Search My Bookings\n");
        printf(" 6. Check Loyalty Status\n");
        printf(" 7. Back to Main Menu\n\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                listMovies();
                break;
            case 2:
                idx = selectMovie();
                if (idx != -1) displaySeatMap(&movies[idx]);
                break;
            case 3:
                idx = selectMovie();
                if (idx != -1) bookSeat(&movies[idx], username);
                break;
            case 4:
                idx = selectMovie();
                if (idx != -1) cancelSeat(&movies[idx]);
                break;
            case 5:
                idx = selectMovie();
                if (idx != -1) searchBooking(&movies[idx], username);
                break;
            case 6:
                checkLoyaltyStatus(username);
                break;
            case 7:
                break;
            default:
                printf("\nInvalid choice!!\n");
        }
    } while (choice != 7);
}

void adminMenu(void) {
    if (!adminLogin()) return;

    int choice, idx;
    do {
        printf("\n+---------- ADMIN MENU ----------+\n");
        printf(" 1. List Movies\n");
        printf(" 2. Add Movie\n");
        printf(" 3. Remove Movie\n");
        printf(" 4. View Summary (one movie)\n");
        printf(" 5. View Summary (all movies)\n");
        printf(" 6. Back to Main Menu\n\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                listMovies();
                break;
            case 2: {
                char title[50];
                printf("\nEnter new movie title: ");
                scanf(" %49[^\n]", title);

                if (strlen(title) == 0) {
                    printf("Title can't be empty!!\n");
                    break;
                }
                if (binarySearchMovie(movies, 0, movieCount - 1, title) != -1) {
                    printf("\nThat movie already exists!!\n");
                    break;
                }

                addMovieNamed(title);
                printf("\n\"%s\" added successfully.\n", title);
                break;
            }
            case 3:
                removeMovie();
                break;
            case 4:
                idx = selectMovie();
                if (idx != -1) showSummary(&movies[idx]);
                break;
            case 5:
                showAllSummary();
                break;
            case 6:
                break;
            default:
                printf("\nInvalid choice!!\n");
        }
    } while (choice != 6);
}

int strcicmp(const char *a, const char *b) {
    while (*a && *b) {
        int ca = tolower((unsigned char) *a);
        int cb = tolower((unsigned char) *b);
        if (ca != cb) {
            return ca - cb;
        }
        a++;
        b++;
    }
    return (unsigned char) *a - (unsigned char) *b;
}

void addMovieNamed(const char *title) {
    if (movieCount == movieCapacity) {
        if (movieCapacity == 0) {
            movieCapacity = 2;
        } else {
            movieCapacity = movieCapacity * 2;
        }
        movies = realloc(movies, movieCapacity * sizeof(Movie));
    }

    Movie *m = &movies[movieCount];
    strncpy(m->title, title, sizeof(m->title) - 1);
    m->title[sizeof(m->title) - 1] = '\0';

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            m->booked[i][j] = 0;
            m->customerName[i][j][0] = '\0';
        }
    }

    movieCount++;

    mergeSort(movies, 0, movieCount - 1);
}

void removeMovie(void) {
    int idx = selectMovie();
    if (idx == -1) return;

    printf("\nRemoving \"%s\"...\n", movies[idx].title);

    for (int i = idx; i < movieCount - 1; i++) {
        movies[i] = movies[i + 1];
    }
    movieCount--;

    printf("Movie removed.\n");
}

void listMovies(void) {
    if (movieCount == 0) {
        printf("\nNo movies available!!\n");
        return;
    }

    printf("\n+----- MOVIES NOW SHOWING -----+\n");
    for (int i = 0; i < movieCount; i++) {
        printf(" %d. %s\n", i + 1, movies[i].title);
    }
}

int selectMovie(void) {
    if (movieCount == 0) {
        printf("\nNo movies available!!\n");
        return -1;
    }

    listMovies();
    int choice;
    printf("Enter movie number: ");

    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        printf("\nInvalid input!!\n");
        return -1;
    }

    int idx = choice - 1;
    if (idx < 0 || idx >= movieCount) {
        printf("\nInvalid movie number!!\n");
        return -1;
    }

    return idx;
}

void merge(Movie arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Movie *left = malloc(n1 * sizeof(Movie));
    Movie *right = malloc(n2 * sizeof(Movie));

    for (int i = 0; i < n1; i++) left[i] = arr[l + i];
    for (int j = 0; j < n2; j++) right[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcicmp(left[i].title, right[j].title) <= 0) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];

    free(left);
    free(right);
}

void mergeSort(Movie arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int binarySearchMovie(Movie arr[], int low, int high, const char *title) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cmp = strcicmp(arr[mid].title, title);

        if (cmp == 0) return mid;
        if (cmp > 0) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

int hashFunction(const char *name) {
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        sum += name[i];
    }
    return sum % 31;
}

CustomerNode *loyalty(const char *name) {
    int idx = hashFunction(name);
    CustomerNode *node = customerTable[idx];

    while (node != NULL) {
        if (strcmp(node->name, name) == 0) return node;
        node = node->next;
    }

    CustomerNode *fresh = malloc(sizeof(CustomerNode));
    strncpy(fresh->name, name, sizeof(fresh->name) - 1);
    fresh->name[sizeof(fresh->name) - 1] = '\0';
    fresh->premiumCount = 0;
    fresh->next = customerTable[idx];
    customerTable[idx] = fresh;

    return fresh;
}

void recordPremiumBooking(const char *name) {
    CustomerNode *node = loyalty(name);
    node->premiumCount++;
}

void checkLoyaltyStatus(const char *name) {
    int idx = hashFunction(name);
    CustomerNode *node = customerTable[idx];

    while (node != NULL && strcmp(node->name, name) != 0) {
        node = node->next;
    }

    if (node == NULL || node->premiumCount == 0) {
        printf("\nNo premium seats booked yet!! Grab a front row seat to start earning status :D\n");
        return;
    }

    const char *tier;
    if (node->premiumCount >= 7) {
        tier = "Platinum";
    } else if (node->premiumCount >= 5) {
        tier = "Gold";
    } else if (node->premiumCount >= 3) {
        tier = "Silver";
    } else {
        tier = "Bronze";
    }

    printf("\n+-------- LOYALTY STATUS --------+\n");
    printf(" Premium seats booked : %d\n", node->premiumCount);
    printf(" Status               : %s\n", tier);
    printf("+---------------------------------+\n");
}

void displaySeatMap(Movie *m) {
    printf("\n           Now showing: %s\n", m->title);
    printf("           '------------------------------------------------'\n");
    printf("          /                     S C R E E N                 \\\n");
    printf("          '-------------------------------------------------'\n\n");

    for (int i = 0; i < 5; i++) {
        printf("           ");
        for (int j = 0; j < 6; j++) {
            if (m->booked[i][j] == 1) {
                if (i==0) {
                    printf("[      ]");
                } else {
                    printf(" [    ] ");
                }
            } else {
                if (i==0) {
                    printf("[  %c%d  ]", 'A' + i, j+1);
                } else {
                    printf(" [ %c%d ] ", 'A' + i, j+1);
                }
            }
        }

        if (i==0) {
            printf("       Premium : %d\n",getPrice(i));
        } else {
            printf("       Regular : %d\n",getPrice(i));
        }
    }
}

void bookSeat(Movie *m, const char *username) {
    displaySeatMap(m);

    SeatNode *cart = NULL;
    int seatCount = 0, total = 0;
    char more = 'y';

    while (more == 'y' || more == 'Y') {
        char rowChar;
        int row, seatNum, col;

        printf("\nEnter row letter: ");
        scanf(" %c", &rowChar);
        rowChar = toupper(rowChar);
        row = rowChar - 'A';

        printf("Enter seat number: ");
        scanf("%d", &seatNum);
        col = seatNum - 1;

        if (!isValidSeat(row, col)) {
            printf("\nInvalid seat!!\n");
        } else if (m->booked[row][col]) {
            printf("\nSeat %c%d is already booked!!\n", rowChar, seatNum);
        } else {
            int alreadyPicked = 0;
            for (SeatNode *n = cart; n != NULL; n = n->next) {
                if (n->row == row && n->col == col) {
                    alreadyPicked = 1;
                    break;
                }
            }

            if (alreadyPicked) {
                printf("\nYou already picked that seat!!\n");
            } else {
                SeatNode *node = malloc(sizeof(SeatNode));
                node->row = row;
                node->col = col;
                node->next = cart;
                cart = node;
                seatCount++;
                total += getPrice(row);
                printf("Added seat %c%d to your booking.\n", rowChar, seatNum);
            }
        }

        printf("Add another seat? (y/n): ");
        scanf(" %c", &more);
    }

    if (cart == NULL) {
        printf("\nNo seats booked.\n");
        return;
    }

    printf("\nConfirm booking %d seat(s) for %s, total %d? (y/n): ", seatCount, username, total);
    char confirm;
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y') {
        printf("\nBooking cancelled.\n");
        while (cart) {
            SeatNode *next = cart->next;
            free(cart);
            cart = next;
        }
        return;
    }

    while (cart) {
        m->booked[cart->row][cart->col] = 1;
        strncpy(m->customerName[cart->row][cart->col], username, 29);
        m->customerName[cart->row][cart->col][29] = '\0';

        if (cart->row == 0) {
            recordPremiumBooking(username);
        }

        SeatNode *next = cart->next;
        free(cart);
        cart = next;
    }

    printf("\n%d seat(s) booked successfully for %s. Total price: %d\n", seatCount, username, total);
}

void cancelSeat(Movie *m) {
    char rowChar;
    int row, seatNum, col;

    printf("\nEnter row letter: ");
    scanf(" %c", &rowChar);
    rowChar = toupper(rowChar);
    row = rowChar - 'A';

    printf("Enter seat number: ");
    scanf("%d", &seatNum);
    col = seatNum - 1;

    if (!isValidSeat(row, col)) {
        printf("\nInvalid seat!!\n");
        return;
    }
    if (!m->booked[row][col]) {
        printf("\nSeat %c%d is already free!!\n", rowChar, seatNum);
        return;
    }

    char name[30];
    strcpy(name, m->customerName[row][col]);

    printf("\nCancelling booking for %s at seat %c%d\n", name, rowChar, seatNum);

    m->booked[row][col] = 0;
    m->customerName[row][col][0] = '\0';

    printf("Booking cancelled successfully.\n");
}

void searchBooking(Movie *m, const char *username) {
    int found = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            if (strcmp(m->customerName[i][j], username) == 0) {
                printf("Found: Seat %c%d booked for you\n", 'A' + i, j + 1);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No bookings found under your name.\n");
    }
}

void showSummary(Movie *m) {
    int totalSeats = 5 * 6;
    int totalBooked = 0, revenue = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            if (m->booked[i][j]) {
                totalBooked++;
                revenue += getPrice(i);
            }
        }
    }

    printf("\n+----------- SUMMARY: %s -----------+\n", m->title);
    printf(" Total seats     : %d\n", totalSeats);
    printf(" Seats booked    : %d\n", totalBooked);
    printf(" Seats available : %d\n", totalSeats - totalBooked);
    printf(" Revenue so far  : %d\n", revenue);
    printf("+-----------------------------------------------------+\n");
}

void showAllSummary(void) {
    int grandTotal = 0, grandBooked = 0, grandRevenue = 0;

    printf("\n+---------- ALL MOVIES SUMMARY ----------+\n");
    for (int i = 0; i < movieCount; i++) {
        int booked = 0, revenue = 0;
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 6; c++) {
                if (movies[i].booked[r][c]) {
                    booked++;
                    revenue += getPrice(r);
                }
            }
        }
        printf(" %-20s | booked: %2d/%2d | revenue: %d\n",
               movies[i].title, booked, 5 * 6, revenue);
        grandTotal += 5 * 6;
        grandBooked += booked;
        grandRevenue += revenue;
    }
    printf("-------------------------------------------------\n");
    printf(" TOTAL: %d/%d seats booked, revenue: %d\n", grandBooked, grandTotal, grandRevenue);
}

int getPrice(int row) {
    return (row == 0) ? 250 : 150;
}

int isValidSeat(int row, int col) {
    return (row >= 0 && row < 5 && col >= 0 && col < 6);
}

void toLowerStr(char *s) {
    for (int i = 0; s[i]; i++) s[i] = tolower((unsigned char) s[i]);
}

int isAlphaStr(const char *s) {
    if (strlen(s) == 0) return 0;
    for (int i = 0; s[i]; i++) {
        if (!isalpha((unsigned char) s[i])) return 0;
    }
    return 1;
}

void freeAll(void) {
    free(movies);

    for (int i = 0; i < 31; i++) {
        CustomerNode *node = customerTable[i];
        while (node) {
            CustomerNode *next = node->next;
            free(node);
            node = next;
        }
    }
}
