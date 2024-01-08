#include "racing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct race
{
    struct car *cars;
    struct driver *drivers;
    struct team *teams;
};

struct race *this_race;

struct car
{
    char *model;
    char *maker;
    char *driver;
    unsigned hp;
    unsigned price;

    struct car *next;
};

struct driver
{
    char *name;
    char *team;

    struct driver *next;
};

struct team
{
    char *name;

    struct team *next;
};

int racing_init(const char *f)
{
    // First thing I try to open the FILE;
    FILE *data = fopen(f, "r");
    if (!data)
        return -1;

    // Allocate memory for all struct pointers for the race
    this_race = malloc(sizeof(struct race));
    if (!this_race)
        return -1;
    struct car *this_cars = malloc(sizeof(struct car));
    if (!this_cars)
        return -1;
    else
        init_car(this_cars);
    struct driver *this_drivers = malloc(sizeof(struct driver));
    if (!this_drivers)
        return -1;
    else
        init_driver(this_drivers);
    struct team *this_teams = malloc(sizeof(struct team));
    if (!this_teams)
        return -1;
    else
        init_team(this_teams);

    // Every allocation is completed
    this_race->cars = this_cars;
    this_race->drivers = this_drivers;
    this_race->teams = this_teams;

    // Now I read the FILE data
    unsigned n_cars = 0, n_drivers = 0, n_teams = 0;

    char buff[1000 + 1];
    unsigned section_type = -1; // -1: nothing found, 0: car, 1: driver, 2: team
    while (fgets(buff, 1000 + 1, data))
    {
        if (strcmp("#car", buff) == 0)
            section_type = 0;
        else if (strcmp("#driver", buff) == 0)
            section_type = 1;
        else if (strcmp("#team", buff) == 0)
            section_type = 2;
        else if (strcmp("#end", buff) == 0)
        {
            switch (section_type)
            {
            case 0:
                ++n_cars;
                break;
            case 1:
                ++n_drivers;
                break;
            case 2:
                ++n_teams;
                break;
            default:
                // it was -1
                return -1;
            }
            section_type = -1;
        }
        else
        {

            if (section_type == 0)
            {
                if (!this_cars)
                {
                    this_cars = malloc(sizeof(struct car));
                    if (!this_cars)
                        return -1;
                }
                else
                    init_car(this_cars);

                // car
                if (strncmp(buff, "model=", sizeof(char) * 6) == 0)
                {
                    unsigned i = 0;
                    for (i = 0; buff[i] != '='; ++i)
                        ;
                    ++i;
                    strcpy(this_cars->model, &buff[i]);
                }
                else if (strncmp(buff, "maker=", sizeof(char) * 6) == 0)
                {
                    unsigned i = 0;
                    for (i = 0; buff[i] != '='; ++i)
                        ;
                    ++i;
                    strcpy(this_cars->maker, &buff[i]);
                }
                else if (strncmp(buff, "driver=", sizeof(char) * 7) == 0)
                {
                    unsigned i = 0;
                    for (i = 0; buff[i] != '='; ++i)
                        ;
                    ++i;
                    strcpy(this_cars->driver, &buff[i]);
                }
                else if (strncmp(buff, "hp=", sizeof(char) * 3) == 0)
                {
                    unsigned i = 0;
                    for (i = 0; buff[i] != '='; ++i)
                        ;
                    ++i;
                    this_cars->hp = atoi(&buff[i]);
                }
                else if (strncmp(buff, "price=", sizeof(char) * 6) == 0)
                {
                    unsigned i = 0;
                    for (i = 0; buff[i] != '='; ++i)
                        ;
                    ++i;
                    this_cars->price = atoi(&buff[i]);
                }
            }
            else if (section_type == 1)
            {
                // driver
                if (!this_drivers)
                {
                    this_drivers = malloc(sizeof(struct driver));
                    if (!this_drivers)
                        return -1;
                }

                if (strncmp(buff, "name=", sizeof(char) * 5) == 0)
                {
                    unsigned i = 0;
                    for (i = 0; buff[i] != '='; ++i)
                        ;
                    ++i;
                    strcpy(this_drivers->name, &buff[i]);
                }
                else if (strncmp(buff, "team=", sizeof(char) * 5) == 0)
                {
                    unsigned i = 0;
                    for (i = 0; buff[i] != '='; ++i)
                        ;
                    ++i;
                    strcpy(this_drivers->team, &buff[i]);
                }
            }
            else if (section_type == 2)
            {
                // team
                if (!this_teams)
                {
                    this_teams = malloc(sizeof(struct team));
                    if (!this_teams)
                        return -1;
                }

                if (strncmp(buff, "name=", sizeof(char) * 5) == 0)
                {
                    unsigned i = 0;
                    for (i = 0; buff[i] != '='; ++i)
                        ;
                    ++i;
                    strcpy(this_teams->name, &buff[i]);
                }
            }
            else
            {
                // found data but no opening #

                // it's returnig here everytime, idk why :(
                return -1;
            }
        }
    }

    // close file stream
    fclose(data);

    // return total number of cars, drivers and teams
    return n_cars + n_drivers + n_teams;
}

void init_car(struct car *c)
{
    c->driver = 0;
    c->hp = 0;
    c->maker = 0;
    c->model = 0;
    c->price = 0;
    c->next = 0;
}

void init_driver(struct driver *c)
{
    c->name = 0;
    c->team = 0;
    c->next = 0;
}

void init_team(struct team *c)
{
    c->name = 0;
    c->next = 0;
}

void racing_delete()
{
    for (struct car *c = this_race->cars; c != 0; c = this_race->cars)
    {
        this_race->cars = c->next;
        free(c);
    }
    for (struct driver *c = this_race->drivers; c != 0; c = this_race->drivers)
    {
        this_race->drivers = c->next;
        free(c);
    }
    for (struct team *c = this_race->teams; c != 0; c = this_race->teams)
    {
        this_race->teams = c->next;
        free(c);
    }
    free(this_race);
}

unsigned count_cars(const char *model, const char *maker, const char *driver,
                    const unsigned hp, const unsigned price)
{
    struct car *cars = this_race->cars;
    unsigned count = 0;
    while (cars)
    {
        if (
            model == 0 || strcmp(model, cars->model) == 0 && maker == 0 || strcmp(maker, cars->maker) == 0 && driver == 0 || strcmp(model, cars->driver) == 0 && hp == 0 || cars->model == hp && price == 0 || cars->price == hp)
        {
            ++count;
        }
        cars = cars->next;
    }
}

unsigned count_drivers(const char *name, const char *team)
{
    struct driver *drivers = this_race->drivers;
    unsigned count = 0;
    while (drivers)
    {
        if (name == 0 || strcmp(name, drivers->name) == 0)
        {
            if (team == 0 || strcmp(team, drivers->team) == 0)
            {
                ++count;
            }
        }
        drivers = drivers->next;
    }

    return count;
}

unsigned get_teams()
{
    struct team *teams = this_race->teams;
    unsigned count = 0;
    while (teams)
    {
        ++count;
        teams = teams->next;
    }

    return count;
}
