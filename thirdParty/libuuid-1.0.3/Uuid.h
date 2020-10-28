#ifndef __UUID__
#define __UUID__

#include "uuid/uuid.h"
// #define DEBUG

class UUID
{
public:
    static char* Generate(uuid_t *uuid = NULL);
    static char* GenerateLower(uuid_t *uuid = NULL);
    static char* GenerateUpper(uuid_t *uuid = NULL);

    static int Type(uuid_t &uuid);
    static int Variant(uuid_t &uuid);

    static int Compare(uuid_t &uuid1, uuid_t &uuid2);
    static void Clear(uuid_t &uuid);
    static bool isNull(uuid_t &uuid);

    static time_t Time(uuid_t &uuid);

    static int Test(const char* uuidStr, int isValid);

private:
    UUID() {}
    ~UUID() {}
    UUID(const UUID &uuid) {};

    static char *uuidStr;
};

#endif