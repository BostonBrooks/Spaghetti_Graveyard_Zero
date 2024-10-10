/**
 * @file
 * @brief bbDrawable_drawFrame looks up a draw function of a given frame and
 * applies the draw function to (bbViewport* viewport, bbDrawable* drawable, bbFrame* frame)
 *
 * draw function needs access to bbSprites/bbAnimations/bbCompositions
 *
 * bbWidget borrows heavily from bbDrawable, but widgets are drawn to the screen,
 * where drawables are drawn to the viewport
 **/