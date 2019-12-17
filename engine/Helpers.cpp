#include "Helpers.hpp"

const char* Helpers::ToCString(const String::Utf8Value& value) {
    return *value ? *value : "<string conversion failed>";
}