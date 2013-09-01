#include "World/MultiObjectsWorld.h"

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char *argv[])
{
	MultiObjectsWorld w;
	w.build();
	w.renderScene();
	return 0;
}
