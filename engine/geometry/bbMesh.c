/**
 * @file
 * @brief mesh gives a height value for each vertex of the grid of tiles that
 * make up the ground surface. A mesh will also be used to give weightings to
 * different textures being blended to draw the ground surface
 * mesh provides enough padding to use Lanczos interpolation and Gaussian
 * differential interpolation. out-of-bound access returns some default value.
 */

#include <stdlib.h>
#include "engine/geometry/bbMesh.h"

//cant remember what this should be, will experiment later :P
static const I32 PADDING = 8;
static const I32 SCALE = 2;

I32 bbMesh_new (bbMesh** mesh, I32 tiles_i, I32 tiles_j){

    I32 vertices_i = tiles_i + 2 * PADDING + 1;
    I32 vertices_j = tiles_j + 2 * PADDING + 1;
    bbMesh* Mesh = malloc (sizeof (bbMesh)
            + vertices_i * vertices_j * sizeof(U8));
    bbAssert(Mesh != NULL, "null malloc\n");

    Mesh->tiles_i = tiles_i;
    Mesh->tiles_j = tiles_j;
    Mesh->defaultValue = 128;
    *mesh = Mesh;
    return f_Success;
};

I32 bbMesh_fromFile (bbMesh** mesh, I32 tiles_i, I32 tiles_j, char* path){
    bbMesh* Mesh;
    bbMesh_new(&Mesh, tiles_i, tiles_j);
    I32 vertices_i = tiles_i + 2 * PADDING + 1;
    I32 vertices_j = tiles_j + 2 * PADDING + 1;
    sfImage* height_map;
    sfVector2u height_map_size;
    const sfUint8* height_map_values;

    height_map = sfImage_createFromFile(path);
    bbAssert(height_map != NULL, "file not found\n");
    height_map_size = sfImage_getSize(height_map);
    height_map_values = sfImage_getPixelsPtr(height_map);

    for (I32 i = 0; i< vertices_i; i++){
        for (I32 j = 0; j < vertices_j; j++){
            if (i >= height_map_size.x || j >= height_map_size.y){
                Mesh->elevations[(j + i * vertices_j)] = Mesh->defaultValue;
            } else {
                Mesh->elevations[(j + i * vertices_j)]
                = height_map_values[(j + i * height_map_size.x) * 4]
                        *SCALE*POINTS_PER_PIXEL;
            }
        }
    }

    sfImage_destroy(height_map);
    *mesh = Mesh;
    return f_Success;
}


I32 bbMesh_getElevation_tile (bbMesh* Mesh, I32 tile_i, I32 tile_j) {

    I32 vertices_i = Mesh->tiles_i + 2 * PADDING + 1;
    I32 vertices_j = Mesh->tiles_j + 2 * PADDING + 1;

    I32 vertex_i = tile_i+PADDING;
    I32 vertex_j = tile_j+PADDING;

    if (vertex_i < 0 || vertex_j < 0 || vertex_i > vertices_i || vertex_j >
            vertices_j){
        return Mesh->defaultValue;
        //elevation out of bounds
    }
    return Mesh->elevations[(vertex_j + vertex_i * vertices_j)];
}

I32 bbMesh_getElevation_point (bbMesh* Mesh, I32 point_i, I32 point_j){
    I32 tile_i = bbArith_div (point_i, POINTS_PER_TILE);
    I32 tile_j = bbArith_div (point_j, POINTS_PER_TILE);

    I32 residual_i = bbArith_mod(point_i, POINTS_PER_TILE);
    I32 residual_j = bbArith_mod(point_j, POINTS_PER_TILE);

    if (residual_i == 0 && residual_j == 0){
        return bbMesh_getElevation_tile(Mesh, tile_i, tile_j);
    }
    if(residual_i <= residual_j){ // Upper triangle of tile

        I64 left_elevation = bbMesh_getElevation_tile(Mesh, tile_i, tile_j);
        I64 middle_elevation =
                bbMesh_getElevation_tile(Mesh, tile_i, tile_j + 1);
        I64 right_elevation =
                bbMesh_getElevation_tile(Mesh, tile_i + 1, tile_j + 1);

        // product of two 32 bit ints, so use 64 bits
        // though it's unlikely there will be overflow
        I64 a = (right_elevation - middle_elevation) * residual_i;
        I64 b = (middle_elevation - left_elevation) * residual_j;

        I64 c = bbArith64_div((a + b), POINTS_PER_TILE);

        return (c + left_elevation);


    }
    // Lower triangle of tile
    I64 left_elevation = bbMesh_getElevation_tile(Mesh, tile_i, tile_j);
    I64 middle_elevation =
            bbMesh_getElevation_tile(Mesh, tile_i + 1, tile_j);
    I64 right_elevation =
            bbMesh_getElevation_tile(Mesh, tile_i + 1, tile_j + 1);

    I64 a = (middle_elevation - left_elevation) * residual_i;
    I64 b = (right_elevation - middle_elevation) * residual_j;

    I64 c = bbArith64_div((a + b), POINTS_PER_TILE);

    return (c + left_elevation);
}