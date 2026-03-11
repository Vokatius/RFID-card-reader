#ifndef NVS_USER_STORAGE;
#define NVS_USER_STORAGE;

#include <vector>
#include <Arduino.h>
#include "Interfaces.h"
#include "nvs.h"

using namespace std;

//More details here:
//https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/storage/nvs_flash.html#api-reference

class NVS_User_Storage : UserPersistance {
    private:
        nvs_handle_t get_handle();
    public:
        void init();
        void create_user(User user);
        User read_user(vector<uint8_t> uid);
        void update_user(vector<uint8_t> uid, User user);
        void delete_user(vector<uint8_t> uid);
};

#endif