#include "engine/2point5D/bbOverlay.h"


int main (void){

	bbDebug("Creating overlay:\n");
	bbOverlay *overlay;
	bbOverlay_new(&overlay, 2, 3);

	bbDebug("Outputting overlay:\n");
	bbOverlay_draw(overlay, NULL, NULL);
}