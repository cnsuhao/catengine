#include "World/SphereWorld.h"

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char *argv[])
{
	SphereWorld w;
	w.build();
	w.renderScene();
	return 0;
}
