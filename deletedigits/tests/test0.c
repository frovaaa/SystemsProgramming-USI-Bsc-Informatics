#include <assert.h>
#include <string.h>

extern int delete_digits(char * s);

int main() {
    char buf[1000];
    *buf = 0;
    assert(!delete_digits(buf));
    assert(*buf == 0);

    strcpy(buf, "ciao mamma");
    assert(!delete_digits(buf));
    assert(strcmp(buf, "ciao mamma") == 0);
    
    strcpy(buf, "ciao mamma 0");
    assert(delete_digits(buf));
    assert(strcmp(buf, "ciao mamma ") == 0);
    
    strcpy(buf, "123 ciao mamma");
    assert(delete_digits(buf));
    assert(strcmp(buf, " ciao mamma") == 0);
    
    strcpy(buf, "123 ciao mamma");
    assert(delete_digits(buf));
    assert(strcmp(buf, " ciao mamma") == 0);
    
    strcpy(buf, "-123-345-89-");
    assert(delete_digits(buf));
    assert(strcmp(buf, "----") == 0);
    
    strcpy(buf, "0000011111");
    assert(delete_digits(buf));
    assert(strcmp(buf, "") == 0);
}

