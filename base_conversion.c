#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define NUM_LEN 50

/* string reversal */
void reverse_string(char src[NUM_LEN]){
    char rev[NUM_LEN];
    memset(rev, 0, NUM_LEN);

    char *cursor = src;
    int num_chars = 0;
    while(*cursor != '\0'){
        cursor++;
        num_chars++;
    }
    cursor--;

    for(int i = 0; i < num_chars; i++){
        rev[i] = *cursor;
        cursor--;
    }

    memcpy(src, rev, NUM_LEN);
}

/* conversion to decimal */
unsigned long long convert_to_decimal(int base, char number[NUM_LEN]){
    char *cursor = number;
    unsigned long long dec = 0;
    int num_digits = 0;

    while(*cursor != '\0'){
        cursor++;
        num_digits++;
    }
    cursor--;

    for(int i = 0; i < num_digits; i++){
        unsigned long long base_to_power = (unsigned long long)pow((double)base, (double)i);
        int digit_val = 0;

        if(*cursor == 'A') digit_val = 10;
        else if(*cursor == 'B') digit_val = 11;
        else if(*cursor == 'C') digit_val = 12;
        else if(*cursor == 'D') digit_val = 13;
        else if(*cursor == 'E') digit_val = 14;
        else if(*cursor == 'F') digit_val = 15;
        else digit_val = *cursor - '0';

        dec += (digit_val * base_to_power);
        cursor--;
    }

    return dec;
}

/* conversion to desired base */
/* print_flag:
    0 if standard base conversion
    1 if sqrt2 base conversion
    others TBD
*/
char *rebase(int desired_base, unsigned long long dec, int print_flag){
    char leveled[NUM_LEN];
    memset(leveled, 0, NUM_LEN);
    int idx = 0;

    while(dec != 0){
        int rem = dec % desired_base;

        if(rem == 10) leveled[idx] = 'A';
        else if(rem == 11) leveled[idx] = 'B';
        else if(rem == 12) leveled[idx] = 'C';
        else if(rem == 13) leveled[idx] = 'D';
        else if(rem == 14) leveled[idx] = 'E';
        else if(rem == 15) leveled[idx] = 'F';
        else leveled[idx] = rem + '0';

        dec /= desired_base;
        idx++;
    }

    reverse_string(leveled);
    if(print_flag == 0){
        fprintf(stdout, "%s\n", leveled);
        return NULL;
    }
    else if(print_flag == 1){
        return leveled;
    }
    return NULL; /* TODO: handle other beta-expansion conversions later */
}

int main(int argc, char *argv[]){
    printf("%s\n", "*** base conversion wizard ***");

    char beta_flag;
    printf("%s", "are you performing beta-expansion? (y/n): ");
    scanf("%c", &beta_flag);

    if(beta_flag == 'y'){
        int base;
        printf("%s", "enter base: ");
        scanf("%d", &base);

        char number[NUM_LEN];
        memset(number, 0, NUM_LEN);
        printf("%s", "enter number: ");
        scanf("%s", number);

        char desired_base[NUM_LEN];
        memset(desired_base, 0, NUM_LEN);
        printf("%s", "enter desired base (sqrt2, golden, supergolden, e, pi): ");
        scanf("%s", desired_base);

        if(strcmp(desired_base, "sqrt2") == 0){
            unsigned long long dec = convert_to_decimal(base, number);
            printf("%s", "result: ");
            char *result = rebase(2, dec, 1);
            for(int i = 0; result[i] != '\0'; i++){
                printf("%c", result[i]);
                if(result[i+1] != '\0') printf("%c", '0');
            }
            printf("\n");
        }

        /* TODO: handle other beta-expansion conversions later */
    }
    else{
        int base;
        printf("%s", "enter base: ");
        scanf("%d", &base);

        char number[NUM_LEN];
        memset(number, 0, NUM_LEN);
        printf("%s", "enter number: ");
        scanf("%s", number);

        int desired_base;
        printf("%s", "enter desired base: ");
        scanf("%d", &desired_base);

        /* find and print result */
        unsigned long long dec = convert_to_decimal(base, number);
        printf("%s", "result: ");
        rebase(desired_base, dec, 0);
    }
}

/* Copyright Tim Losito 2020-2021 */
