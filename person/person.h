#ifndef PERSON_H
#define PERSON_H

typedef struct
{
    char name[50];
    int age;

    void (*set_name)(struct Person *, const char *);
    void (*set_age)(struct Person *, int);
    void (*print_info)(struct Person *);
} Person;

void Person_set_name(Person *self, const char *name);
void Person_set_age(Person *self, int age);
void Person_print_info(Person *self);

Person Person_create();

#endif
