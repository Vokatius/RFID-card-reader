#ifndef INTERFACES_USER_AUTHENTICATION
#define INTERFACES_USER_AUTHENTICATION

#include <vector>

class IUserAuthentication {
    public:
        virtual std::vector<uint8_t> block_until_auth();
        virtual bool block_until_verified(std::vector<uint8_t> expectedUid);
        virtual std::vector<uint8_t> get_auth();
};

#endif
