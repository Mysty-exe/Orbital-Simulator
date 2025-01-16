#include <Transition.h>

Transition::Transition()
{
}

Transition::Transition(SDL_Renderer *renderer, int width, int height, int holdSpeed)
{
    this->renderer = renderer;
    this->width = width;
    this->height = height;
    this->holdSpeed = holdSpeed;
    getPossibleLocations();
}

void Transition::getPossibleLocations()
{
    locations.clear();
    for (int y = 0; y <= height; y += 32)
    {
        for (int x = 0; x <= width; x += 32)
        {
            locations.push_back(Vector(x, y));
        }
    }
}

string Transition::runTransition()
{
    if (transitionState == "In")
    {
        if (!pixelateTimer.isStarted())
        {
            pixelateTimer.start();
        }

        if (pixelateTimer.getTicks() >= 0.05)
        {
            pixelateTimer.stop();

            if (locations.size() <= 0 && !holdTimer.isStarted())
            {
                transitionState = "Hold";
                holdTimer.start();
            }
            else if (locations.size() > 0)
            {
                transitionState = "In";
                int random = rand() % locations.size();
                drawLocations.push_back(locations[random]);
                locations.erase(locations.begin() + random);
            }
        }
    }

    else if (transitionState == "Out")
    {
        if (!pixelateTimer.isStarted())
        {
            pixelateTimer.start();
        }

        if (pixelateTimer.getTicks() >= 0.05)
        {
            pixelateTimer.stop();
            if (drawLocations.size() <= 0)
            {
                transitionState = "Done";
            }
            else
            {
                int random = rand() % drawLocations.size();
                drawLocations.erase(drawLocations.begin() + random);
            }
        }
    }

    if (holdTimer.getTicks() >= holdSpeed * 1000)
    {
        transitionState = "Out";
        holdTimer.stop();
    }

    for (Vector v : drawLocations)
    {
        SDL_Rect rect = {v.x, v.y, 64, 64};
        SDL_SetRenderDrawColor(renderer, 46, 21, 68, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    return transitionState;
}
