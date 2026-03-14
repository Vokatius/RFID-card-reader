#include "utils/Base64.h"

#include <vector>
#include <array>
#include <Arduino.h>

#define BIT_MASK ((1ULL << 32) - 1)

namespace Base64 {
    static String convertBytesToBase64(uint8_t bytes[3]);
    static std::vector<uint8_t>  convertSymbolsToBytes(char symbols[4]);

    String toBase64(vector<uint8_t> bytes, bool addPadding) {
        // Serial.println("Starting calc");
        uint8_t remainingByteAmount = bytes.size() % 3;

        String result = "";
        uint8_t bytesArr[3] = {0};
        for(uint8_t i = 0; i < bytes.size() - remainingByteAmount; i += 3) {
            // Serial.print("Loop nr: ");
            // Serial.println(i);
        
            for(int j = 0; j < 3; j++) {    
                // Serial.print("Sub-Loop nr: ");
                // Serial.println(i-3+j);        
                bytesArr[j] = bytes[i+j];
            }
            result.concat(convertBytesToBase64(bytesArr));
        }

        if(remainingByteAmount != 0) {
            uint8_t start = bytes.size() - remainingByteAmount;
            // Serial.print("SIZE: ");
            // Serial.print(bytes.size());
            // Serial.print(" remaining: ");
            // Serial.print(remainingByteAmount);
            // Serial.print(" start: ");
            // Serial.println(start);

            if(remainingByteAmount == 1) {
                bytesArr[0] = bytes[start];
                bytesArr[1] = 0;
                bytesArr[2] = 0;

                // Serial.print("Array: [0]->");
                // Serial.print(bytesArr[0]);
                // Serial.print(", [1]->");
                // Serial.print(bytesArr[1]);
                // Serial.print(", [2]->");
                // Serial.print(bytesArr[2]);

                String partial = convertBytesToBase64(bytesArr);
                result.concat(partial.c_str(), 2);
                if(addPadding) result.concat("==");
            } else {
                bytesArr[0] = bytes[start];
                bytesArr[1] = bytes[start + 1];
                bytesArr[2] = 0;

                // Serial.print("Array: [0]->");
                // Serial.print(bytesArr[0]);
                // Serial.print(", [1]->");
                // Serial.print(bytesArr[1]);
                // Serial.print(", [2]->");
                // Serial.print(bytesArr[2]);
                
                String partial = convertBytesToBase64(bytesArr);
                result.concat(partial.c_str(), 3);
                if(addPadding) result.concat("=");
            }
        }

        return result;
    };

    vector<uint8_t> fromBase64(String value) {
        while(value.length() % 4 > 0) {
            value.concat("=");
        }

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
            auto tempValues = convertSymbolsToBytes(symbols);
            Serial.println("Inserting Values");
            result.insert(result.end(), tempValues.begin(), tempValues.end());
        }

        return result;
    };

    static String convertBytesToBase64(uint8_t bytes[3]) {
        // Serial.println("Starting temp calc");
        String result = "";
        uint32_t group = bytes[0] << 16 | bytes[1] << 8 | bytes[2];
        // Serial.print("uint32_t to base64: ");
        // Serial.println(group);

        // Serial.println("Starting loop");
        uint8_t tempVal;
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

            tempVal = (group & ~(BIT_MASK - (63 << offset * 6))) >> (offset * 6);
            if(tempVal <= 25) {
                result.concat(char(tempVal + 65));
            } else if (tempVal <= 51) {
                result.concat(char(tempVal + 71));
            } else if(tempVal <= 61) {
                result.concat(char(tempVal - 4));
            } else if(tempVal == 62) {
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

    static std::vector<uint8_t> convertSymbolsToBytes(char symbols[4]) {
        uint8_t paddingCount = 0;
        uint32_t tempVal = 0;

        for(uint8_t i = 0; i < 4; i++) {
            if(symbols[3-i] == 61) { // =
                paddingCount++;
                continue;                
            }                 
            
            if(symbols[3-i] == 43) { // +
                tempVal += 62 << i * 6;
            } else if(symbols[3-i] == 47) { // /
                tempVal += 63 << i * 6;
            } else if(symbols[3-i] <=  57) { // numbers
                tempVal += (symbols[3-i] + 4) << i * 6;
            } else if(symbols[3-i] <= 90) { // capital letters
                tempVal += (symbols[3-i] - 65) << i * 6;
            } else { // lowercase letters
                tempVal += (symbols[3-i] - 71) << i * 6;
            }
        }

        // Serial.print("uint32_t from base64: ");
        // Serial.println(tempVal);

        std::vector<uint8_t> result = { };
        for(int offset = 2; offset >= 0; offset--) {
            result.push_back((tempVal & ~(BIT_MASK - (255 << offset * 8))) >> offset * 8);
        }

        if(paddingCount > 0)
            result.resize(result.size() - paddingCount);

        return result;
    }
}
