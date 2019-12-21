#ifndef RPS
#define RPS
enum States {INIT, P1, P2, DONE};
void RPC();
int getWinner();
char getP1Shape();
char getP2Shape();
void updatePlayer1(int);
void updatePlayer2(int);
void updateState(int);
#endif