#ifndef HELPERS
#define HELPERS

#include "libplatform/libplatform.h"
#include <v8.h>

using v8::String;

class Helpers {

	public:

		static const char* ToCString(const String::Utf8Value& value);

};

#endif