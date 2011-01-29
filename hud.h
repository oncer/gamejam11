#ifndef _HUD_H_
#define _HUD_H_

class Hud {

public:

void draw();
void setMaxHunger(int value);
void setHunger(int value);

private:

int maxHunger;
int hunger;

};

#endif
