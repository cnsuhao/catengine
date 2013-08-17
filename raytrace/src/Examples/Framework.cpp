#include "World/SphereWorld.h"
#include "Utility/RGBColor.h"
#include <stdio.h>

int main()
{
	RGBColor c(RGBColor::GREEN);
	printf("c(%f,%f,%f)\n", c.r, c.g, c.b);

	SphereWorld w;
	w.build();
	w.renderScene();
	return 0;
}

