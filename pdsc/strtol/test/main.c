#include <stdio.h>
#include <string.h>
#include <stdlib.h>
long sttrtol(const char* nPtr, char** endPtr, int base);
int main()
{   
    const char *str = "-1234567890123456789090";
    char *endPtr;
    char *endPtrr;
    long result = strtol(str, &endPtr, 0);
    long rresult = sttrtol(str, &endPtrr, 0);
    printf("Result: %ld\n", result);
    printf("End pointer: %s\n", endPtr);
    printf("Result: %ld\n", rresult);
    printf("End pointer: %s\n", endPtrr);
    return 0;
}
long sttrtol(const char* nPtr, char** endPtr, int base)
{       
    while (*nPtr == ' ' || *nPtr == '\t' || *nPtr == '\n')
        nPtr++;
    int sign = 1;
    if (*nPtr == '-'){
	    nPtr++;
        sign = -1;
    }
	if ((base < 2 || base > 36) && base != 0){
		return 0;
	}else{
		if(base == 0){
			if(*nPtr == '0'){
				base = 8;
				nPtr++;
			if(*(nPtr)=='x' || *(nPtr)=='X'){
					base = 16;
                    if((*(nPtr + 1) >= '0' && *(nPtr + 1) <='9') || ('a' <= *(nPtr + 1) && *(nPtr + 1) <= 'f') || ('A' <= *(nPtr + 1) && *(nPtr + 1) <= 'F')){
				        nPtr++;
                    }
				}
			}
			else{
				base = 10;
			}
		}
	}
    long result = 0;
    while (*nPtr != '\0') {
        int digit;
        if ('0' <= *nPtr && *nPtr <= '9') {
            digit = *nPtr - '0';
        } else if ('a' <= *nPtr && *nPtr <= 'z') {
            digit = *nPtr - 'a' + 10;
        } else if ('A' <= *nPtr && *nPtr <= 'Z') {
            digit = *nPtr - 'A' + 10;
        } else {
            break;
        }
        if (digit >= base) {
            break;
        }if(sizeof(long)== 8){
			if ((sign == 1 && (result > (0x7FFFFFFFFFFFFFFF - digit) / base)) ||
        		(sign == -1 && (result < (-0x7FFFFFFFFFFFFFFF + digit) / base))) {
           		if(sign == 1){
                	result = 0x7FFFFFFFFFFFFFFF;
            	}else{
                	result = -0x7FFFFFFFFFFFFFFF - 1;
            	}
			}else{
            	result = result * base + digit * sign;
        	}	
		}else{
			if ((sign == 1 && (result > (0x7FFFFFFF - digit) / base)) ||
        		(sign == -1 && (result < (-0x7FFFFFFF + digit) / base))) {
           		if(sign == 1){
                	result = 0x7FFFFFFF;
            	}else{
                	result = -0x7FFFFFFF - 1;
            	}

			}else{
            	result = result * base + digit * sign;
        	}
        }
        nPtr++;
    }
	if (endPtr) {
		*endPtr = (char*)nPtr;
	}
	return result;
}
