#ifndef BASE_64
#define BASE_64

#include <vector>
#include <Arduino.h>

using namespace std;

//Implemented following the RFC:
//https://datatracker.ietf.org/doc/html/rfc4648#section-4

namespace Base64 {
    String toBase64(vector<uint8_t> bytes, bool addPadding = false);
    vector<uint8_t> fromBase64(String value);
}

#endif
