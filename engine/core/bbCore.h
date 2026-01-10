#ifndef BBCORE_H
#define BBCORE_H
#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbList.h"
#include "engine/logic/bbVPool.h"

/* The core is the part of the game engine that keeps things ticking and synchronises simulations between computers.
 * In the event of a new input to the core, an instruction is placed on the stack, and marked as an input for later reference.
 * Then the core is activated. the core pops an instruction from the stack and executes it. In doing so, more
 * instructions may be added to the stack. finally, the inverse instruction is added to a second stack.
 * then the next instruction is popped from the stack and the process continues.
 *
 * If the game needs to be rewound, instructions are popped from the second stack and acted upon,
 * instructions to redo inputs are put on the first stack.
 * If the game needs to be fast-forwarded again, instructions are found in the first stack.
 * */

/* Instructions are put on the do stack, then executed.
 * Inverse instructions are placed on the undo stack,
 * and new instructions are placed on the doStack
 *
 * If the instruction is an input (placed on stack before executing),
 * then the instruction in the undo stack has a pointer (called redo) to the original instruction
 * */



typedef struct
{
    bbVPool* pool;
    bbList doStack;
    bbList undoStack;
} bbCore;

bbFlag bbCore_init(bbCore* core);

///isInput should be true unless this is being called from an instruction
bbFlag bbCore_createDot(bbCore* core, bbScreenPoints SP, I32 numDots, bool isInput);
bbFlag bbCore_react(bbCore* core);

#endif //BBCORE_H