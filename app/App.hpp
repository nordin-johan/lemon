#ifndef APP
#define APP

#include "../engine/Lemon.hpp"

using v8::Context;

class App : public Lemon {

	public:	

		void Start(int argc, char* argv[]);
		
};

#endif