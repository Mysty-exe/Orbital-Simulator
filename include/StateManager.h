#pragma once
#include <iostream>
#include <SDL.h>
#include <string>
#include <vector>
#include <Menu.h>
#include <Simulation.h>
#include <Vector.h>

using namespace std;

class StateManager
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    string title, state;
    int width, height;

    vector<string> events;
    bool click, holdClick;

    Menu menu;
    Simulation simulation;

public:
    StateManager(SDL_Window *window, SDL_Renderer *renderer, string title, int width, int height);
    string getTitle();
    string getState();
    void setState(string state);
    int getWidth();
    int getHeight();
    void setEvents(vector<string> newEvents);
    void run();
};