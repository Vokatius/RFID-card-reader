#include "Base64.h"

#include <vector>
#include <array>
#include <Arduino.h>

#define BIT_MASK ((1 << 32) - 1)

namespace Base64 {
    static String convert_bytes_to_base64(uint8_t bytes[3]);
    static std::vector<uint8_t>  convert_symbols_to_bytes(char symbols[4]);

    String to_base64(vector<uint8_t> bytes, bool add_padding) {
        // Serial.println("Starting calc");
        uint8_t remaining_byte_amnt = bytes.size() % 3;

        String result = "";
        uint8_t bytes_arr[3] = {0};        
        for(uint8_t i = 0; i < bytes.size() - remaining_byte_amnt; i += 3) {
            // Serial.print("Loop nr: ");
            // Serial.println(i);
        
            for(int j = 0; j < 3; j++) {    
                // Serial.print("Sub-Loop nr: ");
                // Serial.println(i-3+j);        
                bytes_arr[j] = bytes[i+j];
            }
            result.concat(convert_bytes_to_base64(bytes_arr));
        }

        
        if(remaining_byte_amnt != 0) {
            uint8_t start = bytes.size() - remaining_byte_amnt;
            // Serial.print("SIZE: ");
            // Serial.print(bytes.size());
            // Serial.print(" remaining: ");
            // Serial.print(remaining_byte_amnt);
            // Serial.print(" start: ");
            // Serial.println(start);

            if(remaining_byte_amnt == 1) {             
                bytes_arr[0] = bytes[start];
                bytes_arr[1] = 0;
                bytes_arr[2] = 0;

                // Serial.print("Array: [0]->");
                // Serial.print(bytes_arr[0]);
                // Serial.print(", [1]->");
                // Serial.print(bytes_arr[1]);
                // Serial.print(", [2]->");
                // Serial.print(bytes_arr[2]);

                String partial = convert_bytes_to_base64(bytes_arr);
                result.concat(partial.c_str(), 2);
                if(add_padding) result.concat("==");
            } else {
                bytes_arr[0] = bytes[start];
                bytes_arr[1] = bytes[start + 1];
                bytes_arr[2] = 0;

                // Serial.print("Array: [0]->");
                // Serial.print(bytes_arr[0]);
                // Serial.print(", [1]->");
                // Serial.print(bytes_arr[1]);
                // Serial.print(", [2]->");
                // Serial.print(bytes_arr[2]);
                
                String partial = convert_bytes_to_base64(bytes_arr);
                result.concat(partial.c_str(), 3);
                if(add_padding) result.concat("=");
            }
        }

        return result;
    };

    vector<uint8_t> from_base64(String value) {
        Serial.println("Starting calc");
        vector<uint8_t> result = {};

        char symbols[4] = {};
        for(uint8_t i = 0; i < value.length(); i += 4) {
            Serial.print("Outer loop No.");
            Serial.println(i);
            for(uint8_t j = 0; j < 4; j++) {
                Serial.print("Inner loop No.");
                Serial.println(j);
                symbols[j] = value[i+j];
            }

            Serial.println("Getting Values");
            auto temp_values = convert_symbols_to_bytes(symbols);
            Serial.println("Inserting Values");
            result.insert(result.end(), temp_values.begin(), temp_values.end());
        }

        return result;
    };

    static String convert_bytes_to_base64(uint8_t bytes[3]) {
        // Serial.println("Starting temp calc");
        String result = "";
        uint32_t group = bytes[0] << 16 | bytes[1] << 8 | bytes[2];
        Serial.print("uint32_t to base64: ");
        Serial.println(group);

        // Serial.println("Starting loop");
        uint8_t temp_val;
        for(int offset = 3; offset >= 0; offset--) {
            // Serial.print("Bit mask: ");
            // Serial.println(BIT_MASK);

            // uint32_t complete_mask = (BIT_MASK - (63 << offset * 6));
            // Serial.print("complete mask: ");
            // Serial.println(complete_mask);

            // uint32_t inverted_mask = ~complete_mask;
            // Serial.print("inverted mask: ");
            // Serial.println(inverted_mask);

            // uint32_t unshifted = (group & inverted_mask);
            // Serial.print("unshifted: ");
            // Serial.println(unshifted);
            
            // uint8_t temp_val = unshifted >> (offset * 6);
            // Serial.print(offset + 1);
            // Serial.print("# Run. temp_val: ");
            // Serial.println(temp_val);

            temp_val = (group & ~(BIT_MASK - (63 << offset * 6))) >> (offset * 6);
            if(temp_val <= 25) {
                result.concat(char(temp_val + 65));
            } else if (temp_val <= 51) {
                result.concat(char(temp_val + 71));
            } else if(temp_val <= 61) {
                result.concat(char(temp_val - 4));
            } else if(temp_val == 62) {
                result.concat("+");
            } else {
                result.concat("/");
            }
            // Serial.print("Temp res: ");
            // Serial.println(result);
        }

        // Serial.print("Final res: ");
        // Serial.println(result);
        return result;
    };

    static std::vector<uint8_t> convert_symbols_to_bytes(char symbols[4]) {
        uint8_t padding_cnt = 0;
        uint32_t temp_val = 0;       

        for(uint8_t i = 0; i < 4; i++) {
            if(symbols[3-i] == 61) { // =
                padding_cnt++;
                continue;                
            }                 
            
            if(symbols[3-i] == 43) { // +
                temp_val += 62 << i * 6;
            } else if(symbols[3-i] == 47) { // /
                temp_val += 63 << i * 6;
            } else if(symbols[3-i] <=  57) { // numbers
                temp_val += (symbols[3-i] + 4) << i * 6;
            } else if(symbols[3-i] <= 90) { // capital letters
                temp_val += (symbols[3-i] - 65) << i * 6;
            } else { // lowercase letters
                temp_val += (symbols[3-i] - 71) << i * 6;
            }
        }

        // Serial.print("uint32_t from base64: ");
        // Serial.println(temp_val);

        std::vector<uint8_t> result = { };
        for(int offset = 2; offset >= 0; offset--) {
            result.push_back((temp_val & ~(BIT_MASK - (255 << offset * 8))) >> offset * 8);
        }

        if(padding_cnt > 0)
            result.resize(result.size() - padding_cnt);

        return result;
    }
}