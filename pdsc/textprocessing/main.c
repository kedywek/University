#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GROWTH_FACTOR 2
#define INITIAL_SIZE 8

typedef struct
{
    char *data;
    size_t size;
} Line;

typedef struct
{
    Line **lines;
    size_t indexOfLast;
    size_t size;
} Text;

char *getLine();
void *extendData(void *data, size_t newSize, size_t elementSize);
void *extendLines(void *lines, size_t newSize, size_t elementSize);
Line *initializeLine(char* inputLine);
Text *initializeText();
Text *addLine(Text* text, Line* line);
Text *readText();
void freeMemText(Text *text);
void freeMemLine(Line *line);
Line *reverseLine(Line *line);
void *printText(Text *text);
void reverseWordsInLine(Line *line);
void *reverseLines(Text *text);

int main()
{
    Text *text = readText();
    for (size_t i = 0; i < text->indexOfLast; i++)
    {   
        text->lines[i] = reverseLine(text->lines[i]); 
    }
    reverseLines(text);
    printText(text);
    freeMemText(text);
    return 0;
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

void *extendLines(void *lines, size_t newSize, size_t elementSize)
{
    Text *newLines = realloc(lines, newSize * elementSize);
    if (newLines == NULL)
    {
        fprintf(stderr, "Failed to reallocate memory at function extendData\n");
        return NULL;
    }
    else
    {
        return newLines;
    }
}

Line *initializeLine(char* inputLine){
    Line *initializedLine = malloc(sizeof(Line));
    if (initializedLine == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for struct Line in function initializeLine\n");
        freeMemLine(initializedLine);
        free(inputLine); 
        return NULL;
    }
    initializedLine->size = strlen(inputLine) + 1 ;
    initializedLine->data = malloc(initializedLine->size * sizeof(char));
    if (initializedLine->data == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for Line.data in function initializeLine\n");
        freeMemLine(initializedLine);
        free(inputLine); 
        return NULL;
    }
    for (size_t i = 0; i < initializedLine->size - 1; i++)
    {
        initializedLine->data[i] = inputLine[i];
    }
    initializedLine->data[initializedLine->size - 1] = '\0';
    return initializedLine;
}

Text *initializeText()
{
    Text *text = malloc(sizeof(Text));
    if (text == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for struct Text in function initializeText\n");
        return NULL;
    }
    text->size = INITIAL_SIZE;
    text->indexOfLast = 0;
    text->lines = malloc(text->size * sizeof(Line *));
    if (text->lines == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for Text.lines in function initializeText\n");
        freeMemText(text);
        return NULL;
    }
    return text;
}

Text *addLine(Text* text, Line* line)
{   
    size_t size = text->size;
    if(text->indexOfLast + 1 >= size){
        size *= GROWTH_FACTOR;
        Line **newLines = extendLines(text->lines, size, sizeof(Line *));
        if(newLines  == NULL){
            return NULL;
        } else{
            text->lines = newLines;
            text->size = size;
        }
    }
    text->lines[text->indexOfLast] = line;
    text->indexOfLast++;
    text->lines[text->indexOfLast] = NULL;
    return text;
}

Text *readText()
{
    Text *text = initializeText();
    if (text == NULL) {
        return NULL; 
    }
    int character;
    while((character = getchar()) != EOF){
        ungetc(character, stdin);
        char *inputLine = getLine();
        if(inputLine != NULL){
            Line *currentLine = initializeLine(inputLine);
            if(currentLine != NULL){
                free(inputLine);
                text = addLine(text, currentLine);
                if(text == NULL){
                    freeMemText(text); 
                    return NULL; 
                }
            } else {
                freeMemText(text); 
                return NULL; 
            }
        } else {
            freeMemText(text);
            return NULL; 
        }
    }
    return text;
}

void freeMemText(Text *text)
{
    if (text != NULL)
    {
        if (text->lines != NULL)
        {
            for (size_t i = 0; text->lines[i] != NULL; i++)
            {
                freeMemLine(text->lines[i]);
            }
            free(text->lines);
        }
        free(text);
    }
}

void freeMemLine(Line *line)
{
    if (line != NULL)
    {
        if (line->data != NULL)
        {
            free(line->data);
        }
        free(line);
    }
}

Line *reverseLine(Line *line){
    for (size_t i = 0; i < (line->size - 1)/2; i++)
    {
        char tmp = line->data[i];
        line->data[i] = line->data[line->size - i - 2];
        line->data[line->size - i - 2] = tmp;
    }
    reverseWordsInLine(line);
    return line;
}

void *reverseLines(Text *text){
    for (size_t i = 0; i < (text->indexOfLast - 1)/2; i++)
        {   
            Line* tmp = text->lines[i];
            text->lines[i] = text->lines[text->indexOfLast - i - 1];
            text->lines[text->indexOfLast - i - 1] = tmp;
        }
    return NULL;
}

void *printText(Text *text){
     printf("\n");
    for (size_t i = 0; i <= text->indexOfLast - 1; i++)
        {
            printf("%s\n",text->lines[i]->data);
        }
        
    return NULL;
}
void reverseWordsInLine(Line *line) {
    unsigned start = 0;
    unsigned end;
    while (start < line->size - 1) {
        while (line->data[start] == ' ') {
            start++;
        }
        end = start;
        while (line->data[end] != ' ' && line->data[end] != '\n' && line->data[end] != EOF&& line->data[end] != '\0') {
            end++;
        }
        int wordStart = start;
        int wordEnd = end - 1;
        while (wordStart < wordEnd) {
            char temporary = line->data[wordStart];
            line->data[wordStart] = line->data[wordEnd];
            line->data[wordEnd] = temporary;
            wordStart++;
            wordEnd--;
        }
        start = end;
    }
}