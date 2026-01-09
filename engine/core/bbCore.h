#ifndef BBCORE_H
#define BBCORE_H

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




#endif //BBCORE_H