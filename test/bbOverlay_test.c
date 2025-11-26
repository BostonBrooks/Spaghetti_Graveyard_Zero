#include "engine/viewport/bbOverlays.h"


int main (void){

	bbDebug("Creating overlay:\n");
	bbOverlays *overlay;
    bbOverlays_new(&overlay, 2, 3);

	bbDebug("Outputting overlay:\n");
    bbOverlay_drawTest(overlay, NULL, NULL);
}