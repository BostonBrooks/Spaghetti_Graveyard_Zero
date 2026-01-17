/**
 * @file
 * @brief mesh gives a height value for each vertex of the grid of tiles that
 * make up the ground surface. A mesh will also be used to give weightings to
 * different textures being blended to draw the ground surface
 * mesh provides enough padding to use Lanczos interpolation and Gaussian
 * differential interpolation. out-of-bound access returns some default value.
 */

#include <stdlib.h>
#include "engine/includes/game0.h"
#include "engine/includes/CSFML.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbArith.h"


typedef struct {
    I32 tiles_i;
    I32 tiles_j;
    U16 defaultValue;

// range of values = 2^8 * SCALE * POINTS_PER_PIXEL,
// where each colour chanel of a BMP file is 8 bits
    U16 elevations[];

} bbMesh;

I32 bbMesh_new (bbMesh** mesh, I32 tiles_i, I32 tiles_j);

I32 bbMesh_fromFile (bbMesh** mesh, I32 tiles_i, I32 tiles_j, char* path);


I32 bbMesh_getElevation_tile (bbMesh* Mesh, I32 tile_i, I32 tile_j);

/// get the elevation of a point on the meshes surface. we need this to be
/// deterministic.
I32 bbMesh_getElevation_point (bbMesh* Mesh, I32 point_i, I32 point_j);