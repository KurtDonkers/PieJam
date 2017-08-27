#pragma once

#include <vector>
#include <memory>

#include "Planet.hpp"


class Star 
{
public:
    Star ();
    ~Star () = default;

    void Update (double simtime, double delta, std::vector<std::unique_ptr<Planet>>& planets, std::vector<std::unique_ptr<Star>>& stars);
    double GetPosX (void) {return (mPos[0]);}
    double GetPosY (void) {return (mPos[1]);}
    double GetMass (void) {return (mMass);}
    void DebugOutput (void);
    double GetVeerConstante (void) {return (mCVeer);}
    
private:
    void UpdateStar (double simtime, double delta, std::vector<std::unique_ptr<Planet>>& planets, std::vector<std::unique_ptr<Star>>& stars);
    void UpdateVeer (double simtime, double delta, std::vector<std::unique_ptr<Planet>>& planets, std::vector<std::unique_ptr<Star>>& stars);
    
    double mPos[2];
    double mVel[2];
    double mAccel[2];
    double mMass = 10.0;
    double mCVeer = 0.2;
    
    // tmp
    double mFrequencyAchtigIets;
    double mRadius;
    double mInitPos[2];
    double mdelta = 0.0;
};