#ifndef BUFILE_H_INCLUDED
#define BUFILE_H_INCLUDED

struct bufile;

typedef struct bufile BUFILE;

BUFILE * bufopen(char * begin, char * end);
void bufclose(BUFILE * buf);

char *bufgets(char *s, int size, BUFILE * buf);

#endif
