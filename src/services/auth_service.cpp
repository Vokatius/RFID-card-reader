#include "services\auth_service.h"

Auth_Service::Auth_Service(IUser_Persistence& persistance)
: m_persistance(persistance) { };

bool Auth_Service::is_registered(std::vector<uint8_t> uid) {
    User u = m_persistance.read_user(uid);
    return &u != nullptr;
};

User Auth_Service::get_user(std::vector<uint8_t> uid) {
    User u = m_persistance.read_user(uid);
    return u;
};

void Auth_Service::update_user(std::vector<uint8_t> uid, User u) {
    if(!is_registered(uid))
        throw 1;

    if(u.name.length() > m_persistance.get_max_name_len())
        throw 1;

    m_persistance.update_user(uid, u);
};

void Auth_Service::register_user(User u) {
    if(is_registered(u.uid))
        throw 1;

    if(u.name.length() > m_persistance.get_max_name_len())
        throw 1;

    m_persistance.create_user(u);
};

void Auth_Service::delete_user(std::vector<uint8_t> uid) {
    if(!is_registered(uid))
        throw 1;
        
    m_persistance.delete_user(uid);
};