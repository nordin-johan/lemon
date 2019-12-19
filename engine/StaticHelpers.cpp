#include "StaticHelpers.hpp"

const char* StaticHelpers::ToCString(const String::Utf8Value& value) {
    return *value ? *value : "<string conversion failed>";
}