
all: app

prepare:
	-mkdir bin
	-mkdir lib
	-mkdir -p build/app
	-mkdir -p build/src
	-mkdir -p build/unittest


# --------------- t3dlib -----------------
SRC_DIR   = src
BUILD_DIR = build/src
SRC       = $(wildcard $(SRC_DIR)/*.cpp)
OBJ       = $(patsubst %.cpp,%.o,$(subst $(SRC_DIR),$(BUILD_DIR),$(SRC)))
T3DLIB_CFLAGS = -fms-extensions -Isrc
t3dlib: prepare $(OBJ)
	ar cru lib/$@.a $(OBJ)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	g++ -Wall -fPIC $(T3DLIB_CFLAGS) -c -o $@ $<

$(SRC_DIR)/%.cpp : $(SRC_DIR)/%.h
	touch $@


# --------------- unittest -----------------
UNITTEST_SRC_DIR   = unittest
UNITTEST_BUILD_DIR = build/unittest
UNITTEST_SRC       = $(wildcard $(UNITTEST_SRC_DIR)/*.cpp)
UNITTEST_OBJ       = $(patsubst %.cpp,%.o,$(subst $(UNITTEST_SRC_DIR),$(UNITTEST_BUILD_DIR),$(UNITTEST_SRC)))
UNITTEST_CFLAGS    = -fms-extensions -Isrc -Iapp
unittest: t3dlib $(UNITTEST_OBJ)
	g++ -o bin/$@ lib/t3dlib.a $(UNITTEST_OBJ)
	./bin/unittest

$(UNITTEST_BUILD_DIR)/%.o : $(UNITTEST_SRC_DIR)/%.cpp
	g++ -Wall -fPIC $(UNITTEST_CFLAGS) -c -o $@ $<

$(UNITTEST_SRC_DIR)/%.cpp : $(UNITTEST_SRC_DIR)/%.h
	touch $@


# --------------- app -----------------
APP_SRC_DIR   = app
APP_BUILD_DIR = build/app
APP_SRC       = $(wildcard $(APP_SRC_DIR)/*.cpp)
APP_OBJ       = $(patsubst %.cpp,%.o,$(subst $(APP_SRC_DIR),$(APP_BUILD_DIR),$(APP_SRC)))
APP_CFLAGS    = -fms-extensions -Isrc -Iapp
app: t3dlib $(APP_OBJ)
	g++ -o bin/$@ lib/t3dlib.a $(APP_OBJ)

$(APP_BUILD_DIR)/%.o : $(APP_SRC_DIR)/%.cpp
	g++ -Wall -fPIC $(APP_CFLAGS) -c -o $@ $<

$(APP_SRC_DIR)/%.cpp : $(APP_SRC_DIR)/%.h
	touch $@

# ------------ clean --------------
clean:
	rm -rf bin
	rm -rf lib
	rm -rf build
