#include "World/PerspectiveWorld.h"

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char *argv[])
{
	PerspectiveWorld w;
	w.build();
	w.renderScene();
	return 0;
}

