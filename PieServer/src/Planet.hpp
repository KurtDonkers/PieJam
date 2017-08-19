#pragma once

class Planet 
{
public:
    Planet ();
    ~Planet () = default;

    void Update (double simtime);
    float GetPosX (void) {return (mPos[0]);}
    float GetPosY (void) {return (mPos[1]);}

private:
    float mPos[2];
    float mVel[2];
    float mAccel[2];

    // tmp
    float mFrequencyAchtigIets;
    float mRadius;
    float mInitPos[2];
};