/** Various systems are modelled as finite state machines.
 * state variables usually start with s_
 * Here is a list of possible states that a state machine can be in
 */

#define s_Idle               0
#define s_WaitingForCode     1
#define s_WaitingForAnswer   2
#define s_WaitingForClick    3