#ifndef NVS_USER_STORAGE
#define NVS_USER_STORAGE

#include <vector>
#include <Arduino.h>
#include "interfaces/user_persistence.h"
#include "nvs.h"

//More details here:
//https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/storage/nvs_flash.html#api-reference

class NVS_User_Storage : public IUser_Persistence {
    private:
        const uint8_t m_max_name_length;
        bool m_isInit = false;
        nvs_handle_t get_handle();
    public:
        void init();
        void create_user(User user);
        User read_user(std::vector<uint8_t> uid);
        void update_user(std::vector<uint8_t> uid, User user);
        void delete_user(std::vector<uint8_t> uid);
        uint8_t get_max_name_len();
        NVS_User_Storage(uint8_t max_name_length);
        ~NVS_User_Storage();
};

#endif
