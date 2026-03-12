#ifndef INTERFACES_USER_PERSISTENCE
#define INTERFACES_USER_PERSISTENCE

#include <string>

struct User {
    const std::string name;
    // UIDs might be 4, 7, or 10 bytes.
    const std::vector<uint8_t> uid;
};

class IUser_Persistence {
    public:
        virtual void create_user(User user);
        virtual User read_user(std::vector<uint8_t> uid);
        virtual void update_user(std::vector<uint8_t> uid, User user);
        virtual void delete_user(std::vector<uint8_t> uid);
};

#endif
