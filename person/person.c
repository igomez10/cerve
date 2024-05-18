#include <stdio.h>
#include <string.h>
#include "person.h"

// person
Person create_person(const char *name, int age)
{
    Person person;
    strcpy(person.name, name);
    person.age = age;
    return person;
}
