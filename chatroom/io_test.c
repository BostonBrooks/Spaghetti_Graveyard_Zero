#include "io.h"

int main(void){

    int number = get_integer_input("Enter text to test function: ");

    printf("You entered the number %d\n", number);

    char username[64];

    get_valid_username(username, "Please input your username: ");

    printf("Your username is: %s\n", username);

    exit(EXIT_SUCCESS);

}