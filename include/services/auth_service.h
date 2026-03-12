#ifndef AUTH_SERVICE
#define AUTH_SERVICE

#include <cstdint> 
#include <vector>
#include "interfaces/user_persistence.h"

class Auth_Service {
    private:
        IUser_Persistence m_persistance; 

    public:
        Auth_Service(IUser_Persistence* persistance);
        bool is_registered(std::vector<uint8_t> uid);
        User get_user(std::vector<uint8_t> uid);
        void register_user(User u);
        void update_user(std::vector<uint8_t> uid, User u);
        void delete_user(std::vector<uint8_t> uid);        
};

#endif