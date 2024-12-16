void *extendData(void *data, size_t newSize, size_t elementSize);

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


int main(){
	printf("Hello world");
	return 0;
}
