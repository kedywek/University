#include <limits.h>
#include <errno.h>	
#include <stdio.h>
#include <stdbool.h>

const char* skipWhitespace(const char* nPtr);
int handleSign(const char** nPtr);
int handleBase(const char** nPtr, int base, int* digitRead);
long checkOverflow(long result, int sign, int digit, int base);
long readDigit(const char** nPtr, int* digitRead, int sign, long result, int base);

long strtol(const char* nPtr, char** endPtr, int base)
{  
	const char *start = nPtr;
	int digitRead;
    nPtr = skipWhitespace(nPtr);
    int sign = handleSign(&nPtr);
	base = handleBase(&nPtr, base, &digitRead);
    if (base == -1){
        return 0;
	}
    long result = 0;
	result = readDigit(&nPtr, &digitRead, sign, result, base);
    
	if(digitRead != 1){
		nPtr = start;
	}
	if (endPtr) {
		*endPtr = (char*)nPtr;
	}
	return result;
}
const char* skipWhitespace(const char* nPtr) {
    while (*nPtr == ' ' || *nPtr == '\t' || *nPtr == '\n') {
        nPtr++;
    }
    return nPtr;
}
int handleSign(const char** nPtr) {
    int sign = 1;
    if (**nPtr == '-') {
        sign = -1;
        (*nPtr)++;
    } else if (**nPtr == '+') {
        (*nPtr)++;
    }
    return sign;
}

int handleBase(const char** nPtr, int base, int* digitRead) {
    if ((base < 2 || base > 36) && base != 0) {
        errno = EINVAL;
        return -1; // Error
    } else {
        if (base == 0 || base == 8 || base == 16) {
            if (**nPtr == '0') {
                if (*(*nPtr + 1) != 'x' && *(*nPtr + 1) != 'X') {
                    base = 8;
                }
                (*nPtr)++;
				*digitRead = 1; 
                if (**nPtr == 'x' || **nPtr == 'X') {
                    base = 16;
                    if ((*(*nPtr+1) >= '0' && *(*nPtr+1) <= '9') || ('a' <= *(*nPtr+1) && *(*nPtr+1) <= 'f') || ('A' <= *(*nPtr+1) && *(*nPtr+1) <= 'F')) {
                        (*nPtr)++;
                    }
                }
            } else {
                if (base == 0)
                    base = 10;
            }
        }
    }
    return base;
}

long checkOverflow(long result, int sign, int digit, int base){
		if((sign == 1 && (result > (LONG_MAX - digit) / base)) ||
			(sign == -1 && (result < (LONG_MIN + digit) / base))) {
			if(sign == 1){
				result = LONG_MAX;
				errno = ERANGE;
			}else{
				result = LONG_MIN;
				errno = ERANGE;
			}
		}else{
			result = result * base + digit * sign;
		}	
return result;}
long readDigit(const char** nPtr, int* digitRead, int sign, long result, int base){
	while (**nPtr != '\0') {
        int digit;
        if ('0' <= **nPtr && **nPtr <= '9') {
			*digitRead = 1;
            digit = **nPtr - '0';
        } else if ('a' <= **nPtr && **nPtr <= 'z') {
			*digitRead = 1;
            digit = **nPtr - 'a' + 10;
        } else if ('A' <= **nPtr && **nPtr <= 'Z') {
			*digitRead = 1;
            digit = **nPtr - 'A' + 10;
        } else {
            break;
        }
        if (digit >= base) {
            break;
        }
		result = checkOverflow(result, sign, digit, base);
        (*nPtr)++;
    }
	return result;

}