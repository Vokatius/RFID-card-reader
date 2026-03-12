#include <vector>
#include <Arduino.h>
#include "utils/Base64.h"
#include "storage/NVS_User_Storage.h"
#include "nvs_flash.h"
#include "nvs.h"

using namespace std;

#define NVS_NAMESPACE "USR_SPACE"

NVS_User_Storage::NVS_User_Storage(uint8_t maxNameLength)
: m_maxNameLength(maxNameLength) {};

void NVS_User_Storage::init() {
    auto err = nvs_flash_init();
    if(err != ESP_OK) {
        //TODO: Error handling
        throw 1;
    }

    m_isInit = true;
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
    if(!m_isInit)
        throw 1;

    auto handle = get_handle();

    auto err = nvs_set_str(handle, Base64::toBase64(user.uid).c_str(), user.name.c_str());
    if(err != ESP_OK) {
        //TODO: Error handling
        throw 1;
    }

    nvs_commit(handle);
    nvs_close(handle);
}

User NVS_User_Storage::read_user(vector<uint8_t> uid) {
    if(!m_isInit)
        throw 1;

    auto handle = get_handle();

    string name = {};
    name.resize(m_maxNameLength);

    auto size = size_t(m_maxNameLength);
    auto err = nvs_get_str(handle, Base64::toBase64(uid).c_str(), &name[0], &size); // &name[0] -> Passes pointer to first char of name
    if(err == ESP_ERR_NOT_FOUND)
        return {};

    if(err != ESP_OK) {
        //TODO: Error handling
        throw 1;
    }
    name.shrink_to_fit();

    nvs_close(handle);

    return User{name,uid}; 
}

void NVS_User_Storage::update_user(vector<uint8_t> uid, User user) {
    if(uid != user.uid)
        delete_user(uid);
    
    create_user(user);
}

void NVS_User_Storage::delete_user(vector<uint8_t> uid) {
    if(!m_isInit)
        throw 1;

    auto handle = get_handle();

    auto err = nvs_erase_key(handle, Base64::toBase64(uid).c_str());
    if(err != ESP_OK) {
        //TODO: Error handling
        throw 1;
    }

    nvs_commit(handle);
    nvs_close(handle);
}

NVS_User_Storage::~NVS_User_Storage() {
    auto err = nvs_flash_deinit();
    if(err != ESP_OK) {
        //TODO: Error handling
    }
}
