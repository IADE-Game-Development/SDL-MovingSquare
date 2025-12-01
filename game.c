#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "sdl_utils.h"

#define APP_NAME "Space Counter"
#define APP_WIDTH 800
#define APP_HEIGHT 600

#define CUBE_WIDTH 100
#define CUBE_HEIGHT 100

#define MAX_SPEED 50

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

int main(void)
{
    int counter = 0;

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        SDL_Log("SDL_Init error: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        APP_NAME,
        APP_WIDTH,
        APP_HEIGHT,
        SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int running = 1;
    const Uint32 FRAME_MS = 16; // ~60 FPS

    int x = 10;
    int y = 10;

    int velocity_x = 1;
    int velocity_y = 1;

    while (running)
    {
        Uint32 frame_start = SDL_GetTicks();

        x = x + velocity_x;
        y = y + velocity_y;

        if (x + CUBE_WIDTH > APP_WIDTH || x < 0)
        {
            velocity_x = -velocity_x;
            counter++;
            if (velocity_x > 0 && velocity_x < MAX_SPEED)
                velocity_x++;
            else if (velocity_x > -MAX_SPEED)
                velocity_x--;
        }

        if (y + CUBE_HEIGHT > APP_HEIGHT || y < 0)
        {
            velocity_y = -velocity_y;
            counter++;
            if (velocity_y > 0 && velocity_y < MAX_SPEED)
                velocity_y++;
            else if (velocity_y > -MAX_SPEED)
                velocity_y--;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = 0;

            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                if (event.key.key == SDLK_SPACE)
                {
                    // Reset the counter
                    counter = 0;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // background (black)
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // text color (white)
        const int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;

        SDL_RenderDebugTextFormat(
            renderer,
            (float)((APP_WIDTH - (charsize * 46)) / 2),
            (APP_HEIGHT / 2),
            "(This program has been running for %" SDL_PRIu64 " seconds.)",
            SDL_GetTicks() / 1000);

        SDL_RenderDebugTextFormat(renderer,
                                  0, 0, "velocity_x = %d || velocity_y = %d", velocity_x, velocity_y);

        SDL_RenderDebugTextFormat(renderer, 100, 100, "Counter: %d", counter);

        // --- RED SQUARE ---
        SDL_FRect rect = {x, y, CUBE_WIDTH, CUBE_HEIGHT};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);

        Uint32 elapsed = SDL_GetTicks() - frame_start;
        if (elapsed < FRAME_MS)
            SDL_Delay(FRAME_MS - elapsed);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
