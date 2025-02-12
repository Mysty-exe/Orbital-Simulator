#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <Utilities.h>
#include <Vector.h>
#include <Image.h>
#include <Animation.h>
#include <Particles.h>
#include <Timer.h>

using namespace std;

enum CelestialTypes
{
    STAR,
    PLANET,
    MOON,
    ASTEROID
};

class CelestialObject
{
public:
    SDL_Renderer *renderer;
    int width, height;
    string name;
    string objType;
    string folder;
    long double mass;
    long double radius;
    long double updateRadius;
    Vector position;
    Vector velocity;
    Vector acceleration;
    long double kineticEnergy;
    long double potentialEnergy;
    SDL_Rect rect, realRect;
    bool ctrl, editing;

    Animation object, viewObject;
    Image arrow, nameTxt, trajectory;
    Particles particles;
    Vector particlePos;
    Timer particleDurationTimer;

    CelestialObject();
    CelestialObject(SDL_Renderer *renderer, int width, int height, string name, string objType, string fileName);
    CelestialObject(SDL_Renderer *renderer, int width, int height, string n, string objType, string fileName, long double mass, long double radius, float x, float y, Vector vel);
    void setName(SDL_Renderer *renderer, string name);
    void calculateEnergies(vector<CelestialObject> &objects);
    static void applyForces(vector<CelestialObject> &objects, double timeStep, int timeRate);
    static void applyVelocities(vector<CelestialObject> &objects, double timeStep);
    static void display(SDL_Renderer *renderer, vector<CelestialObject> &objects, Vector panningOffset, int timeRate, double timeStep);
    static void updateAllSizes(SDL_Renderer *renderer, vector<CelestialObject> &objects);
    void drawTrajectory(SDL_Renderer *renderer, vector<CelestialObject> objects, Vector panningOffset, int timeRate, double timeStep);
    void updateSizeGradually(SDL_Renderer *renderer, double timeStep);
    void updateSizeInstant(SDL_Renderer *renderer);
    SDL_Rect *getRect();
    SDL_Rect *getRealRect();
};
