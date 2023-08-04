#include <stdio.h>
#include <stdbool.h>

#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\e[m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN "\033[36m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"

int row;
char col;

struct aSeat {
    int row;
    char col1;
    char col2;
    char col3;
    char col4;
};

struct aSeat passenger[5];

void printSeat() {
    printf("\nSeats marked as 'X' are reserved.\n\n");
    printf("---------------------------------------------------------------------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("|\t%d\t|\t%c\t|\t%c\t|\t%c\t|\t%c\t|\n", i + 1, passenger[i].col1, passenger[i].col2, passenger[i].col3, passenger[i].col4);
        printf("---------------------------------------------------------------------------------\n");
    }
}

bool validateRow(int row) {
    return (row >= 1 && row <= 5);
}

bool validateColumn(char col) {
    return (col >= 'A' && col <= 'D');
}

bool validateInput(char conf) {
    return (conf == 'Y' || conf == 'y' || conf == 'N' || conf == 'n');
}

void getInput(int *row, char *col) {
    printf("\nEnter row (1 - 5): ");
    scanf("%d", row);

    while (!validateRow(*row)) {
        printf(COLOR_RED "\n\tInvalid row!" COLOR_OFF " Please enter a value between 1 and 5: ");
        scanf("%d", row);
    }

    printf("Enter column (A - D): ");
    scanf(" %c", col);

    while (!validateColumn(*col)) {
        printf(COLOR_RED "\n\tInvalid column!" COLOR_OFF " Please enter a value between A and D: ");
        scanf(" %c", col);
    }

    printf("\n");
}

void assignSeat() {
    for (int i = 0; i < 5; i++) {
        passenger[i].col1 = 'A';
        passenger[i].col2 = 'B';
        passenger[i].col3 = 'C';
        passenger[i].col4 = 'D';
    }
}

bool isSeatTaken(int row, char col) {
    int index = row - 1;

    switch (col) {
        case 'A':
            return passenger[index].col1 == 'X';
        case 'B':
            return passenger[index].col2 == 'X';
        case 'C':
            return passenger[index].col3 == 'X';
        case 'D':
            return passenger[index].col4 == 'X';
        default:
            return false;
    }
}

void markSeatTaken(int row, char col) {
    int index = row - 1;

    switch (col) {
        case 'A':
            passenger[index].col1 = 'X';
            break;
        case 'B':
            passenger[index].col2 = 'X';
            break;
        case 'C':
            passenger[index].col3 = 'X';
            break;
        case 'D':
            passenger[index].col4 = 'X';
            break;
    }
}

char seatConf() {
    char conf;

    printf(COLOR_BOLD "\tDo you confirm this seat? [Y / N]: " COLOR_OFF);
    scanf(" %c", &conf);

    while (!validateInput(conf)) {
        printf(COLOR_RED "\n\tInvalid input!" COLOR_OFF " Please enter only Y or N: ");
        scanf(" %c", &conf);
    }
    printf("\n");

    return conf;
}

char enterAgain() {
    char conf;

    printf(COLOR_BOLD "\tDo you want to reserve a seat again? [Y / N]: " COLOR_OFF);
    scanf(" %c", &conf);

    while (!validateInput(conf)) {
        printf(COLOR_RED "\n\tInvalid input!" COLOR_OFF " Please enter only Y or N: ");
        scanf(" %c", &conf);
    }
    printf("\n");

    return conf;
}

int main(int argc, char *argv[]) {
    int seats = 20;
    bool taken;
    char conf, again;

    printf("---------------------------------------------------------------------------------\n");
    printf(COLOR_YELLOW "\t\t\t  Welcome to Room 4 Airlines.\n" COLOR_OFF);
    printf("---------------------------------------------------------------------------------\n");
    printf(COLOR_BOLD "\nPlease input the necessary details to reserve your seat.\n" COLOR_OFF);

    assignSeat();

    do {
        printSeat();

        getInput(&row, &col);

        again = 'N';
        conf = 'N';
        conf = seatConf();

        taken = isSeatTaken(row, col);

        if (conf == 'Y' || conf == 'y') {
            if (!taken) {
                markSeatTaken(row, col);
                // Only display seat status if the seat is not occupied
                printSeat();
                printf(COLOR_GREEN "\n\t\t\t  Seat booked successfully!" COLOR_OFF);
                seats--;
            } else {
                printf(COLOR_RED "\n\t\t  Seat is already taken. Please choose another seat.\n" COLOR_OFF);
            }
        }

        if (seats <= 20 && seats > 0) {
            printf("\n---------------------------------------------------------------------------------\n\n");
            again = enterAgain();
            printf("\n---------------------------------------------------------------------------------\n");
        } else if (seats == 0) {
            printf(COLOR_GREEN "\n\t\t  All seats are booked!" COLOR_OFF);
            break;
        }

        taken = false;

    } while (again == 'Y' || again == 'y' || taken);

    printf(COLOR_CYAN COLOR_BOLD"\n\t\t  Thank you for booking with Room 4 Airlines!\n\n" COLOR_OFF);

    return 0;
}
