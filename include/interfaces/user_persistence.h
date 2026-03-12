#ifndef INTERFACES_USER_PERSISTENCE
#define INTERFACES_USER_PERSISTENCE

#include "interfaces/types.h"

class IUserPersistence {
    public:
        virtual void create_user(User user);
        virtual User read_user(std::vector<uint8_t> uid);
        virtual void update_user(std::vector<uint8_t> uid, User user);
        virtual void delete_user(std::vector<uint8_t> uid);
};

#endif
