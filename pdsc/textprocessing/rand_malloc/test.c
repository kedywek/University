#include "rand_malloc.h"
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
    Line **line;
    size_t index_of_last;
    size_t size;
} Text;

char* get_line();
void *extend_data(void *data, size_t newSize, size_t elementSize);
void *extend_text(void *text, size_t newSize, size_t elementSize);
Line *initialize_line();
Text *initialize_text();
Text *add_line();
Text *read_text();
void freemem_text(Text *text);
void freemem_line(Line *line);

int main()
{
    Text *text = read_text();
	freemem_text(text);
    return 0;
}

char* get_line(){
    size_t size = INITIAL_SIZE;
    unsigned int index = 0; 
    int character;
    char *line = malloc(INITIAL_SIZE * sizeof(char));
    if (line!=NULL)
    {
        while ((character = getchar()) != '\n' && character != EOF)
        {
        if (index >= (size - 1))
        {
            size *= GROWTH_FACTOR;
            char *newLine;
            newLine = extend_data(line, size, sizeof(char));
            if(newLine == NULL){
                free(line);
                return NULL;
            } else{
                line = newLine;
            }
        }
        line[index] = character;
        index ++;
        }
        line[index] = '\0';
        return line;
    }else{
        fprintf(stderr, "Failed to allocate memory for line in function get_line\n");
		free(line);
        return NULL;
    }
}
void *extend_data(void *data, size_t newSize, size_t elementSize)
{
    char *newData = realloc(data, newSize * elementSize);
    if (newData == NULL)
    {
        fprintf(stderr, "Failed to reallocate memory at function extend_data\n");
        return NULL;
    }
    else
    {
        return newData;
    }
}

void *extend_lines(void *line, size_t newSize, size_t elementSize)
{
    Text *new_lines = realloc(line, newSize * elementSize);
    if (new_lines == NULL)
    {
        fprintf(stderr, "Failed to reallocate memory at function extend_data\n");
        return NULL;
    }
    else
    {
        return new_lines;
    }
}
Line *initialize_line(char* input_line){
    Line *initialize_line = malloc(sizeof(Line));
    if (initialize_line == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for struct Line in function initialize_line\n");
        freemem_line(initialize_line);
        free(input_line); // <- This line should be removed
        return NULL;
    }
    initialize_line->size = strlen(input_line) + 1 ;
    initialize_line->data = malloc(initialize_line->size * sizeof(char));
    if (initialize_line->data == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for Line.data in function initialize_line\n");
        freemem_line(initialize_line);
        free(input_line); // <- This line should be removed
        return NULL;
    }
    for (size_t i = 0; i < initialize_line->size - 1; i++)
    {
         initialize_line->data[i] = input_line[i];
    }
    initialize_line->data[initialize_line->size - 1] = '\0';
    return initialize_line;
}
Text *initialize_text()
{
    Text *text = malloc(sizeof(Text));
    if (text == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for struct Text in function initialize_text\n");
        return NULL;
    }
    text->size = INITIAL_SIZE;
    text->index_of_last = 0;
    text->line = malloc(text->size * sizeof(Line *));
    if (text->line == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for Text.lines in function initialize_text\n");
		freemem_text(text);
        return NULL;
    }
    return text;
}
Text *add_line(Text* text, Line* line)
{   size_t size = text->size;
    if(text->index_of_last + 1 >= size){
        size *= GROWTH_FACTOR;
        Line **new_lines = extend_lines(text->line, size, sizeof(Line *));
        if(new_lines  == NULL){
            return NULL;
        } else{
            text->line = new_lines;
            text->size = size;
        }
    }
    text->line[text->index_of_last] = line;
    text->index_of_last ++;
    text->line[text->index_of_last] = NULL;
    return text;
}
Text *read_text()
{
    Text *text = initialize_text();
    if (text == NULL) {
        return NULL; // Failed to initialize text struct
    }
    
    while(getchar() != EOF){
        char *inputLine = get_line();
        if(inputLine != NULL){
            Line *current_line = initialize_line(inputLine);
            if(current_line != NULL){
                free(inputLine);
                text = add_line(text, current_line);
                if(text == NULL){
                    freemem_text(text); 
                    return NULL; 
                }
            } else {
                freemem_text(text); 
                return NULL; 
            }
        } else {
            freemem_text(text);
            return NULL; 
        }
    }
    return text;
}
void freemem_text(Text *text)
{
    if (text != NULL)
    {
        if (text->line != NULL)
        {
            for (size_t i = 0; text->line[i] != NULL; i++)
            {
                freemem_line(text->line[i]);
            }
            free(text->line);
        }
        free(text);
    }
}
void freemem_line(Line *line)
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