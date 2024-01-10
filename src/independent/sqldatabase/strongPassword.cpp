
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <string.h>


using namespace std;
int strongPassword(const char *pass) {
    int checkSpecial = 0;
    int len = strlen(pass);
    
    if (len <= 12) {
        return 1; // Password length is less than or equal to 12
    }

    const char specialChars[] = "!~/[*^&@";
    for (int i = 0; i < len; i++) {
        if (strchr(specialChars, pass[i])) {
            checkSpecial = 1;
            break;
        }
    }
    if (checkSpecial == 0) {
        return 2; // Password doesn't contain a special character
    }

    int checkUpper = 0;
    for (int i = 0; i < len; i++) {
        if (isupper(pass[i])) {
            checkUpper = 1;
            break;
        }
    }
    if (checkUpper == 0) {
        return 3; // Password doesn't contain an uppercase letter
    }

    return 0; // Strong password
}

