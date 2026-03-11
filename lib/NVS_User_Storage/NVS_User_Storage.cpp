#include <vector>
#include <Arduino.h>
#include "NVS_User_Storage.h"
#include "nvs_flash.h"
#include "nvs.h"

using namespace std;

#define NVS_NAMESPACE "USR_SPACE"

void NVS_User_Storage::init() {
    auto err = nvs_flash_init();
    if(err != ESP_OK) {
        //TODO: Error handling
        throw 1;
    }
}

nvs_handle_t NVS_User_Storage::get_handle() {
    nvs_handle_t handle;
    auto err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
    if(err != ESP_OK) {
        //TODO: Error handling
        throw 1;
    }

    return handle;
};

void NVS_User_Storage::create_user(User user) {

}

// User NVS_User_Storage::read_user(vector<uint8_t> uid);

// void NVS_User_Storage::update_user(vector<uint8_t> uid, User user);

// void NVS_User_Storage::delete_user(vector<uint8_t> uid);

// NVS_User_Storage::~NVS_Storage() {
//     auto err = nvs_flash_deinit();
//     if(err != ESP_OK) {
//         //TODO: Error handling
//         throw 1;
//     }
// }