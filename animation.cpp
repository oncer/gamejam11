#include "animation.h"

Animation::Animation(int ticksPerFrame, int numFrames, bool repeat)
:ticksPerFrame(ticksPerFrame),
    numFrames(numFrames),
    repeat(repeat)
{
    reset();
}

void Animation::update()
{
    if (done) return;
    tick++;
    if (tick >= ticksPerFrame * numFrames) {
        if (repeat) {
            tick = 0;
        } else {
            tick--;
            done = true;
        }
    }
}

int Animation::getCurrentFrame()
{
    return tick / ticksPerFrame;
}

bool Animation::isDone()
{
    return done;
}

void Animation::reset()
{
    tick = 0;
    done = false;
}

