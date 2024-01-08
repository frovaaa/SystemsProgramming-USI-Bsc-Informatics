#ifndef RACING_H_INCLUDED
#define RACING_H_INCLUDED

#include "racing_content.h"

struct race;
struct car;
struct driver;
struct team;

void init_car(struct car *c);
void init_driver(struct driver *c);
void init_team(struct team *c);
#endif
