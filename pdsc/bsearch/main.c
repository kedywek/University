#include <stdlib.h>
#include <stdio.h>

void* bsearch ( const void* key , const void* base, size_t num, size_t size, int (* compar ) ( const void * , const void * ) ) {
    size_t first = 0, last = num;
    while ( first < last ) {
        size_t mid = first + ( last - first ) / 2;
        if ( compar ( key, base + mid * size ) < 0 ) {
            last = mid;
        } else if ( compar ( key, base + mid * size ) > 0 ) {
            first = mid + 1;
        } else {
            return ( void* ) ( base + mid * size );
        }
    }
    return NULL;
}
int compare ( const void* a, const void* b ) {
    int result = *( int* ) a - *( int* ) b;
    return *( int* ) a - *( int* ) b;
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int key = 1;
    void* result = bsearch ( &key, arr, 10, sizeof ( int ), compare );
    if ( result == NULL ) {
        printf ( "Not found\n" );
    } else {
        printf ( "Found\n" );
        printf ( "%d\n", *( int* ) result );
    }
    return 0;
}