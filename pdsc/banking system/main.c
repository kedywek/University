#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>

#define LOAN_INTEREST 0.1
#define MAX_NAME_LEN 32
#define MAX_SURNAME_LEN 32
#define MAX_ADDRESS_LEN 64
#define INITIAL_SIZE 8
#define GROWTH_FACTOR 2

typedef struct Account {
    unsigned int accountNumber;
    char pesel[12];
    double balance;
    double credit;
    char name[MAX_NAME_LEN];
    char surname[MAX_SURNAME_LEN];
    char address[MAX_ADDRESS_LEN];
} Account;

void createFileIfNotExists();
void createAccount();
void getAccountNumber(unsigned int* accountNumber);
void getAccountPesel(char* destinacion);
void getAccountName(char* destinacion, char* message, unsigned int maxLen);
void getAddress(char* destinacion);
char *getLine();
void *extendData(void *data, size_t newSize, size_t elementSize);
void getBasicCommand();
bool confirmation();
void listAllaccount();
bool getAccountCommand();
void inputAccountNumber(char* destinacion);
void getAccount(int command, char* value);
void displayAccount(Account account);
unsigned int getNumberOfDigits();
void searchByAccountNumber(unsigned int accountNumber);
void searchByPesel(char* pesel);
void searchByName(char* name);
void searchBySurname(char* surname);
void searchByAddress(char* address);
void makeDeposit(unsigned int accountNumber, double amount);
void getAmount(double* amount);
void takeLoan(unsigned int accountNumber, double amount);
bool checkIfEmpty();
void transferMoney(unsigned int accountNumber, unsigned int accountNumber2, double amount);


int main() {
    createFileIfNotExists();
    printf("Welcome to the bank system\n");
    while (true)
    {
        getBasicCommand();
    }
    return 0;
}

void createFileIfNotExists() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        file = fopen("accounts.dat", "wb");
        if (file == NULL)
        {
            fprintf(stderr, "Error while creating the file");
            exit(1);
        }
    } else {
        fclose(file);
    }
}

void createAccount(){
    Account account;
    memset(&account, 0, sizeof(Account));
    getAccountNumber(&account.accountNumber);
    getAccountPesel(account.pesel);
    getAccountName(account.name, "Enter name: ", MAX_NAME_LEN);
    getAccountName(account.surname, "Enter surname: ", MAX_SURNAME_LEN);
    getAddress(account.address);
    account.balance = 0;
    account.credit = 0;
    if(confirmation()){
        FILE *file = fopen("accounts.dat", "ab");
        if (file == NULL)
        {
            fprintf(stderr, "Error while opening the file");
            exit(1);
        }
        else{
            size_t s = fwrite(&account, sizeof(Account), 1, file);
            fclose(file);
        }
    }
}

void getAccountNumber(unsigned int* accountNumber) {
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        fprintf(stderr, "Error while opening the file");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    *accountNumber = fileSize/sizeof(Account) + 1;
    fclose(file);
}

void inputAccountNumber(char* destinacion) {
    bool isNumber = false;
    char* number;
    unsigned int digits = getNumberOfDigits();
    unsigned int maxNumer;
    getAccountNumber(&maxNumer);
    while(isNumber == false){
        printf("Enter account number: ");
        isNumber = true;
        number = getLine();
        if (strlen(number) == 0){
            fprintf(stderr, "input can't be empty\n");
            free(number);
            isNumber = false;
            continue;
        }
        for (size_t i = 0; i < strlen(number); i++)
        {
            if(!isdigit(number[i])){
                fprintf(stderr, "Account number must constain only digits\n");
                free(number);
                isNumber = false;
                goto end;
            }
        }
        if (strlen(number) > digits)
        {
            fprintf(stderr, "Inputed string longer than number of digits of longest number\n");
            free(number);
            isNumber = false;
            continue;
        }
        if (atoi(number) > maxNumer-1)
        {
            fprintf(stderr, "Account number can't be bigger than the number of accounts\n");
            free(number);
            isNumber = false;
            continue;
        }
        end:
    }
    strcpy(destinacion, number);
    free(number);
}
void getAccountPesel(char* destinacion){

    bool isPesel = false;
    char* pesel;
    while(isPesel == false){
        printf("Enter PESEL: ");
        isPesel = true;
        pesel = getLine();
        if (strlen(pesel) == 0){
            fprintf(stderr, "input can't be empty\n");
            free(pesel);
            isPesel = false;
            continue;
        }
        if(strlen(pesel) != 11){
            fprintf(stderr, "PESEL must have 11 digits\n");
            free(pesel);
            isPesel = false;
            continue;
        }
        for (size_t i = 0; i < 11; i++)
        {
            if(!isdigit(pesel[i])){
                fprintf(stderr, "PESEL must constain only digits\n");
                free(pesel);
                isPesel = false;
                break;
            }
        }
    }
    strcpy(destinacion, pesel);
    free(pesel); 
}


void getAddress(char* destinacion){
    bool isAddress = false;
    char* address;
    while(isAddress == false){
        printf("Enter address: ");
        isAddress = true;
        address = getLine();
        if (strlen(address) == 0){
            fprintf(stderr, "input can't be empty\n");
            free(address);
            isAddress = false;
            continue;
        }
        if(strlen(address) > MAX_ADDRESS_LEN){
            fprintf(stderr, "Address is too long\n");
            free(address);
            isAddress = false;
        }
    }
    for (size_t i = 0; i < strlen(address); i++)
    {
        address[i] = toupper(address[i]);
    }
    
    strcpy(destinacion, address);
    free(address);
}

void getAccountName(char* destinacion, char* message, unsigned int maxLen){
    bool isName = false;
    char* name;
    while(isName == false){
        printf("%s", message);
        isName = true;
        name = getLine();
        if (strlen(name) == 0){
            fprintf(stderr, "input can't be empty\n");
            free(name);
            isName = false;
            continue;
        }
        if(strlen(name) > maxLen){
            fprintf(stderr, "Name is too long\n");
            free(name);
            isName = false;
            continue;
        }
        for (size_t i = 0; i < strlen(name); i++)
        {
            if(!isalpha(name[i])){
                fprintf(stderr, "PESEL must constain only digits\n");
                free(name);
                isName = false;
                break;
            }else{
                name[i] = toupper(name[i]);
            }
        }
    }
    strcpy(destinacion, name);
    free(name);
}
char* getLine(){
    size_t size = INITIAL_SIZE;
    unsigned int index = 0; 
    int character;
    char *line = malloc(INITIAL_SIZE * sizeof(char));
    if (line != NULL)
    {
        while ((character = getchar()) != '\n' && character != EOF)
        {
            if (index >= (size - 1))
            {
                size *= GROWTH_FACTOR;
                char *newLine;
                newLine = extendData(line, size, sizeof(char));
                if(newLine == NULL){
                    free(line);
                    return NULL;
                } else{
                    line = newLine;
                }
            }
            line[index] = character;
            index++;
        }
        line[index] = '\0';
        return line;
    }else{
        fprintf(stderr, "Failed to allocate memory for line in function getLine\n");
        free(line);
        return NULL;
    }
}

void *extendData(void *data, size_t newSize, size_t elementSize)
{
    char *newData = realloc(data, newSize * elementSize);
    if (newData == NULL)
    {
        fprintf(stderr, "Failed to reallocate memory at function extendData\n");
        return NULL;
    }
    else
    {
        return newData;
    }
}

void listAllaccount(){
    FILE * file = fopen("accounts.dat", "rb");
    if(file == NULL){
        fprintf(stderr, "Error while opening the file");
        exit(1);
    }
    Account account;
    while(fread(&account, sizeof(Account), 1, file)){
        displayAccount(account);
    }
    fclose(file);
}

bool confirmation(){
    printf("do you want to confirm the operation? (y/n): ");
    char* answer = getLine();
    if(answer[0] == 'y'){
        free(answer);
        return true;
    }else{
        free(answer);
        return false;
    }
}

void getAccount(int command, char* value){

    switch (command)
    {
    case 1:
        searchByAccountNumber(atoi(value));
        break;
    case 2:
        searchByPesel(value);
        break;
    case 3:
        searchByName(value);
        break;
    case 4:
        searchBySurname(value);
        break;
    case 5:
        searchByAddress(value);
        break;
    default:
        break;
    }
}

void searchByAccountNumber(unsigned int accountNumber)
{
    FILE * file = fopen("accounts.dat", "rb");
    if(file == NULL){
        fprintf(stderr, "Error while opening the file");
        exit(1);
    }
    Account account;
    while(fread(&account, sizeof(Account), 1, file)){
        if(account.accountNumber == accountNumber){
            displayAccount(account);
            break;
        }
    }
    if(account.accountNumber != accountNumber){
        printf("Account not found\n");
    }
    fclose(file);
}

void searchByPesel(char* pesel)
{
    FILE * file = fopen("accounts.dat", "rb");
    if(file == NULL){
        fprintf(stderr, "Error while opening the file");
        exit(1);
    }
    Account account;
    while(fread(&account, sizeof(Account), 1, file)){
        if(strcmp(account.pesel, pesel) == 0){
            displayAccount(account);
        }
    }
    if(strcmp(account.pesel, pesel) != 0){
        printf("Account not found\n");
    }
    fclose(file);
}
void searchByName(char* name)
{
    FILE * file = fopen("accounts.dat", "rb");
    if(file == NULL){
        fprintf(stderr, "Error while opening the file");
        exit(1);
    }
    for (size_t i = 0; i < strlen(name); i++)
    {
        name[i] = toupper(name[i]);
    }
    
    Account account;
    while(fread(&account, sizeof(Account), 1, file)){
        if(strcmp(account.name, name) == 0){
            
            displayAccount(account);
        }
    }
    if(strcmp(account.name, name) != 0){
        printf("Account not found\n");
    }
    fclose(file);
}
void searchBySurname(char* surname)
{
    FILE * file = fopen("accounts.dat", "rb");
    if(file == NULL){
        fprintf(stderr, "Error while opening the file");
        exit(1);
    }
    for (size_t i = 0; i < strlen(surname); i++)
    {
        surname[i] = toupper(surname[i]);
    }
    Account account;
    while(fread(&account, sizeof(Account), 1, file)){
        if(strcmp(account.surname, surname) == 0){
            displayAccount(account);
        }
    }
    if(strcmp(account.surname, surname) != 0){
        printf("Account not found\n");
    }
    fclose(file);
}
void searchByAddress(char* address)
{
    FILE * file = fopen("accounts.dat", "rb");
    if(file == NULL){
        fprintf(stderr, "Error while opening the file");
        exit(1);
    }
    for (size_t i = 0; i < strlen(address); i++)
    {
        address[i] = toupper(address[i]);
    }
    
    Account account;
    while(fread(&account, sizeof(Account), 1, file)){
        if(strcmp(account.address, address) == 0){
            displayAccount(account);
        }
    }
    if(strcmp(account.address, address) != 0){
        printf("Account not found\n");
    }
    fclose(file);
}

void displayAccount(Account account){
    printf("\nAccount number: %d\n", account.accountNumber);
    printf("PESEL: %s\n", account.pesel);
    printf("Name: %s\n", account.name);
    printf("Surname: %s\n", account.surname);
    printf("Address: %s\n", account.address);
    printf("Balance: %.2f\n", account.balance);
    printf("Credit: %.2f\n", account.credit);
}

unsigned int getNumberOfDigits()
{
    unsigned int maxNumer;
    unsigned int digits=0;
    getAccountNumber(&maxNumer);
    maxNumer--; 
    while(maxNumer!=0)  
    {  
        maxNumer=maxNumer/10;  
        digits++;  
    }
    return digits;
}

void makeDeposit(unsigned int accountNumber, double amount){
    FILE * file = fopen("accounts.dat", "rb+");
    if(file == NULL){
        fprintf(stderr, "Error while opening the file");
        exit(1);
    }
    Account account;
    while(fread(&account, sizeof(Account), 1, file)){
        if(account.accountNumber == accountNumber){
            account.balance += amount;
            if(account.balance < 0){
                fprintf(stderr, "Insufficient funds\n");
                break;   
            }
            fseek(file, -sizeof(Account), SEEK_CUR);
            displayAccount(account);
            if (confirmation())
            {
                fwrite(&account, sizeof(Account), 1, file);
            }
            break;
        }
    }
    fclose(file);
}
bool getAccountCommand(){
    printf("\n\nWith what do you want to look for account?\n");
    printf("1. Account number\n");
    printf("2. PESEL\n");
    printf("3. Name\n");
    printf("4. Surname\n");
    printf("5. Address\n");
    printf("6. Return\n");
    char* command = getLine();
    if(strcmp(command, "1") == 0){
        free(command);
        unsigned int digits = getNumberOfDigits();
        char value[digits];
        inputAccountNumber(value);
        getAccount(1, value);
        return true;
    }else if(strcmp(command, "2") == 0){
        free(command);
        char value[12];
        getAccountPesel(value);
        getAccount(2, value);
        return true;
    }else if(strcmp(command, "3") == 0){
        free(command);
        char value[MAX_NAME_LEN];
        getAccountName(value, "Enter name: ", MAX_NAME_LEN);
        getAccount(3, value);
        return true;
    }else if(strcmp(command, "4") == 0){
        free(command);
        char value[MAX_SURNAME_LEN];
        getAccountName(value, "Enter surname: ", MAX_SURNAME_LEN);
        getAccount(4, value);
        return true;
    }else if(strcmp(command, "5") == 0){
        free(command);
        char value[MAX_ADDRESS_LEN];
        getAddress(value);
        getAccount(5, value);
        return true;
    }else if(strcmp(command, "6") == 0){
        free(command);
        return true;
    }else{
        fprintf(stderr, "Invalid command\n");
        free(command);
        return false;
    }

}

void getAmount(double* amount){
    bool isNumber = false;
    double value;
    char* input;
    int dot;
    int afterDot;
    while(isNumber == false){
        printf("Enter amount: ");
        isNumber = true;
        input = getLine();
        dot = 0;
        afterDot = 0;
        size_t length = strlen(input);
        if (length == 0)
        {
            fprintf(stderr, "Input can't be empty\n");
            free(input);
            isNumber = false;
            continue;
        }
        for (size_t i = 0; i < length; i++)
        {
            if(!isdigit(input[i]) && input[i] != '.'){
                fprintf(stderr, "Amount must contain only digits and can't be negative\n");
                free(input);
                isNumber = false;
                goto end;
            }
            if (dot == 1)
            {
                afterDot++;
            }
            if(input[i] == '.'){
                dot++;
                if (strlen(input) == 1)
                {
                    fprintf(stderr, "Amount can't be only a dot\n");
                    free(input);
                    isNumber = false;
                    goto end;
                }
            }
            if(dot > 1){
                fprintf(stderr, "Amount can't contain more than one dot\n");
                free(input);
                isNumber = false;
                goto end;
            }
            if(afterDot > 2){
                fprintf(stderr, "Amount can't have more than two digits after dot\n");
                free(input);
                isNumber = false;
                goto end;
            }
            
        }
        value = strtod(input, NULL);        
        if (errno == ERANGE)
        {
            fprintf(stderr, "Amount is too big\n");
            isNumber = false;
        }
        end: 
    }
    *amount = value;
    free(input);
}
bool checkIfEmpty(){
    FILE *file = fopen("accounts.dat", "rb");
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == 0)
    {   
        printf("There are no accounts\n");
        return true;
    }
    fclose(file);
    return false;
}

void takeLoan(unsigned int accountNumber, double amount){
    FILE * file = fopen("accounts.dat", "rb+");
    if(file == NULL){
        fprintf(stderr, "Error while opening the file");
        exit(1);
    }
    Account account;
    while(fread(&account, sizeof(Account), 1, file)){
        if (account.balance + amount < 0)
        {
            fprintf(stderr, "Insufficient funds\n");
            break;
        }
        if (account.credit + amount < 0)
        {
            fprintf(stderr, "Can't repy more money than owed\n");
            break;
        }
        
        if(account.accountNumber == accountNumber){
            account.credit += amount;
            if(amount > 0){
                account.credit += amount * LOAN_INTEREST;
            }
            account.balance += amount;
            fseek(file, -sizeof(Account), SEEK_CUR);
            displayAccount(account);
            if (confirmation())
            {
                fwrite(&account, sizeof(Account), 1, file);
            }
            break;
        }
    }
    fclose(file);
}
void transferMoney(unsigned int accountNumber, unsigned int accountNumber2, double amount){
    FILE * file = fopen("accounts.dat", "rb+");
    if(file == NULL){
        fprintf(stderr, "Error while opening the file");
        exit(1);
    }
    Account account;
    Account account2;
    int accountIndex;
    while(fread(&account, sizeof(Account), 1, file)){
        if(account.accountNumber == accountNumber){
            if(account.balance - amount < 0){
                fprintf(stderr, "Insufficient funds\n");
                goto end;
            }
            account.balance -= amount;
            accountIndex = fseek(file, -sizeof(Account), SEEK_CUR);
            displayAccount(account);
            break;
        }
    }
    fseek(file, 0, SEEK_SET);
    while(fread(&account2, sizeof(Account), 1, file)){
        if(account2.accountNumber == accountNumber2){
            account2.balance += amount;
            fseek(file, -sizeof(Account), SEEK_CUR);
            displayAccount(account2);
            if (confirmation())
            {
                fwrite(&account2, sizeof(Account), 1, file);
                fseek(file, accountIndex, SEEK_SET);
                fwrite(&account, sizeof(Account), 1, file);
            }
            break;
        }
    }
    end:
    fclose(file);
}
void getBasicCommand()
{  
    printf("\n\nWhat do you want to do?\n");
    printf("1. List all accounts\n");
    printf("2. Create account\n");
    printf("3. Find account\n");
    printf("4. Make deposit\n");
    printf("5. Make withdrawl\n");
    printf("6. Take loan\n");
    printf("7. Repy loan\n");
    printf("8. Make transfer\n");
    printf("9. Exit\n");
    char* command = getLine();
    if(strcmp(command, "1") == 0){
        listAllaccount();
    }else if(strcmp(command, "2") == 0){
        createAccount();
    }
    else if(strcmp(command, "3") == 0){
        if (!checkIfEmpty())
        {
            bool result = false;
            while (result == false)
            {
                result = getAccountCommand();
            }
        }
    }
    else if(strcmp(command, "4") == 0){
        if (!checkIfEmpty())
        {        
            unsigned int digits = getNumberOfDigits();
            char value[digits];
            inputAccountNumber(value);
            double amount;
            getAmount(&amount);
            makeDeposit(atoi(value), amount);
        }
    }
    else if(strcmp(command, "5") == 0){
        if (!checkIfEmpty())
        {        
            unsigned int digits = getNumberOfDigits();
            char value[digits];
            inputAccountNumber(value);
            double amount;
            getAmount(&amount);
            makeDeposit(atoi(value), amount * -1);
        }
    }
    else if(strcmp(command, "6") == 0){
        if (!checkIfEmpty())
        {        
            unsigned int digits = getNumberOfDigits();
            char value[digits];
            inputAccountNumber(value);
            double amount;
            getAmount(&amount);
            takeLoan(atoi(value), amount);
        }
    }
    else if(strcmp(command, "7") == 0){
        if (!checkIfEmpty())
        {        
            unsigned int digits = getNumberOfDigits();
            char value[digits];
            inputAccountNumber(value);
            double amount;
            getAmount(&amount);
            takeLoan(atoi(value), amount * -1);
        }
    }
    else if(strcmp(command, "8") == 0){
        if (!checkIfEmpty())
        {        
            unsigned int digits = getNumberOfDigits();
            char value[digits];
            unsigned int digits2 = getNumberOfDigits();
            char value2[digits];
            printf("Sender");
            inputAccountNumber(value);
            printf("Reciver");
            inputAccountNumber(value2);
            double amount;
            getAmount(&amount);
            transferMoney(atoi(value), atoi(value2), amount);
        }
    }
    else if(strcmp(command, "9") == 0){
        free(command);
        exit(0);
    }else{
        fprintf(stderr, "Invalid command\n");
    }
    free(command);
}