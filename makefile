CXX = g++
V8 = engine/lib/v8

define INCLUDE
	$(V8)/include
	engine/Core.cpp
	engine/Environment.cpp
	engine/Lemon.cpp
	engine/StaticHelpers.cpp
	engine/ObjectCreator.cpp
endef

define APP
	app/*.cpp
endef

define LIB
	$(V8)/out/x64.release/obj/
endef

define OBJ
	v8_monolith
endef

export INCLUDE
export APP
export LIB
export OBJ

build:
	$(CXX) -I $$INCLUDE $$APP -L $$LIB -l $$OBJ -std=c++0x -pthread -o lemon