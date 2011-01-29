#ifndef _ANIMATION_H_
#define _ANIMATION_H_

class Animation
{
public:

Animation(int ticksPerFrame, int numFrames, bool repeat);

void update();
int getCurrentFrame();
bool isDone(); // always true in case repeat is activated

void reset();

private:

int ticksPerFrame;
int numFrames;
bool repeat;
int tick;
bool done;

};

#endif
