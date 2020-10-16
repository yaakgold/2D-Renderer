#include "Canvas.h"
#include "Image.h"
#include "SDL.h"
#include <iostream>

int main(int, char**)
{
    const unsigned int WIDTH = 800;
    const unsigned int HEIGHT = 600;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("2D Renderer", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    Canvas canvas(renderer, WIDTH, HEIGHT);
    Image image;
    image.Load("cat.bmp");

    Image image2;
    image2.Load("sus.bmp");

    Image image3;
    image3.Load("color.bmp", 127);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }

        canvas.Clear({ 0, 55, 0, 255 });

        canvas.DrawPoint({ 100, 100}, { 255, 255, 255, 255 });

        canvas.DrawLine({ 200, 200 }, { 300, 350 }, { 255, 0, 255, 255 });

        canvas.DrawRect(SDL_Rect{ 400, 400, 50, 50 }, { 255, 255, 0, 255 });

        canvas.DrawTriangle({ 500, 500 }, { 500, 550 }, { 700, 525 }, { 255, 0, 0, 255 });

        std::vector<SDL_Point> ps{ {100, 500}, {150, 450}, {10, 500}, {10, 10} };
        canvas.DrawLineList(ps, { 0, 255, 255, 255 });

        canvas.DrawCircle({ 200, 200 }, 100, { 255, 125, 0, 255 });

        canvas.DrawImage(&image, { 100, 100 });
        canvas.DrawImage(&image2, { 250, 250 }, { 0, 255, 0, 255 });
        canvas.DrawImage(&image3, { 150, 150 });

        //canvas.ProcessInvert();
        //canvas.ProcessMonochrome();
        //canvas.ProcessNightVision();
        //canvas.ProcessThreshold({180, 180, 180, 255});
        //canvas.ProcessBrightness(-100);
        //canvas.ProcessColor(50, 50, -100);

        canvas.Update();

        SDL_RenderClear(renderer);

        canvas.Draw(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();

    return 0;
}