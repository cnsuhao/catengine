SRCFILES = \
	src/Utility/RGBColor.cpp											\
	src/Utility/Point2D.cpp												\
	src/Utility/Point3D.cpp												\
	src/Utility/Vector3D.cpp											\
	src/Utility/Normal.cpp												\
	src/Utility/Matrix.cpp												\
	src/Utility/Ray.cpp														\
	src/Utility/ShadeRec.cpp											\
	src/Materials/Material.cpp										\
	src/GeometricObjects/GeometricObject.cpp			\
	src/GeometricObjects/Sphere.cpp								\
	src/World/ViewPlane.cpp												\
	src/World/World.cpp														\
	src/World/SphereWorld.cpp											\
	src/World/PerspectiveWorld.cpp								\
	src/Tracers/Tracer.cpp												\
	src/Tracers/SingleSphere.cpp

CFLAGS  = -g -Wall -Isrc -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lSDL2

all: prepare singleSphere perspectiveWorld

prepare:
	-mkdir bin

singleSphere:
	g++ -o bin/$@ $(CFLAGS) src/Examples/SingleSphereMain.cpp $(SRCFILES) $(LDFLAGS)

perspectiveWorld:
	g++ -o bin/$@ $(CFLAGS) src/Examples/PerspectiveMain.cpp $(SRCFILES) $(LDFLAGS)

clean:
	# find . -name "*.o" | xargs rm -rf
	rm -rf bin
