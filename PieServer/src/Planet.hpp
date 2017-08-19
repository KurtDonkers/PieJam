#pragma once

class Planet 
{
public:
    Planet ();
    ~Planet () = default;

    void Update (double simtime);
    double GetPosX (void) {return (mPos[0]);}
    double GetPosY (void) {return (mPos[1]);}
    double GetMass (void) {return (mMass);}

private:
    double mPos[2];
    double mVel[2];
    double mAccel[2];
    double mMass = 100000000.0;

    // tmp
    double mFrequencyAchtigIets;
    double mRadius;
    double mInitPos[2];
};

