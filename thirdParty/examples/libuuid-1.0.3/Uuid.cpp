#include "Uuid.h"
#include <string.h>
#include <iostream>

namespace Utils{
char *UUID::uuidStr = new char[37];

char* UUID::Generate(uuid_t *uuid) {
    uuid_t __uuid;
    uuid_generate(__uuid);
    uuid_unparse(__uuid, uuidStr);

    if (uuid) {
        strcpy((char *)uuid, (const char *)&__uuid);
    }

    return uuidStr;
}

char* UUID::GenerateLower(uuid_t *uuid) {
    uuid_t __uuid;
    uuid_generate_random(__uuid);
    uuid_unparse_lower(__uuid, uuidStr);

    if (uuid) {
        strcpy((char *)uuid, (const char *)&__uuid);
    }

    return uuidStr;
}

char* UUID::GenerateUpper(uuid_t *uuid) {
    uuid_t __uuid;
    uuid_generate_time(__uuid);
    uuid_unparse_upper(__uuid, uuidStr);
    
    if (uuid) {
        strcpy((char *)uuid, (const char *)&__uuid);
    }

    return uuidStr;
}

int UUID::Type(uuid_t &uuid) {
    return uuid_type(uuid);
}

int UUID::Variant(uuid_t &uuid) {
    return uuid_variant(uuid);
}

int UUID::Compare(uuid_t &uuid1, uuid_t &uuid2) {
    return uuid_compare(uuid1, uuid2);
}

time_t UUID::Time(uuid_t &uuid) {
    struct timeval tv;
    time_t time_reg = uuid_time(uuid, &tv);
#ifdef DEBUG
    fprintf(stdout, "uuid time: (%ld, %ld): %s\n", tv.tv_sec, tv.tv_usec, ctime(&time_reg));
#endif

    return time_reg;
}

void UUID::Clear(uuid_t &uuid) {
    uuid_clear(uuid);
}

bool UUID::isNull(uuid_t &uuid) {
    return uuid_is_null(uuid);
}

int UUID::Test(const char * uuidStr, int isValid)
{
#ifdef DEBUG
    static const char * validStr[2] = {"invalid", "valid"};
#endif
    uuid_t uuidBits;
    int parsedOk;

    parsedOk = uuid_parse(uuidStr, uuidBits) == 0;
#ifdef DEBUG
    printf("%s is %s .", uuidStr, validStr[isValid]);
#endif
    if (parsedOk != isValid) {
#ifdef DEBUG
        printf(" says %s\n", validStr[parsedOk]);
#endif
        return -1;
    }

    return 0;
}
}

int main(int argc, char const *argv[])
{
    std::cout << Utils::UUID::Generate() << std::endl;
    std::cout << Utils::UUID::GenerateLower() << std::endl;
    std::cout << Utils::UUID::GenerateUpper() << std::endl;

    return 0;
}
