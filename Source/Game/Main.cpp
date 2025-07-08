#include <SDL3/SDL.h>
#include "..\Engine\Core\Random.h"
#include <iostream>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 1024;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL3 Project", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    struct CustomLine {
        int x1, y1, x2, y2;
		int red, green, blue;
    };

    struct CustomPoint {
		int x, y;
        int red, green, blue;
	};

	CustomPoint points[20]{};
    CustomLine lines[10]{};

    for (CustomLine& line : lines) {
        line.red = viper::random::getRandomInt(255);
        line.green = viper::random::getRandomInt(255);
        line.blue = viper::random::getRandomInt(255);

        line.x1 = 0 + 10;
		line.y1 = viper::random::getRandomInt(SCREEN_HEIGHT);
		line.x2 = SCREEN_WIDTH - 10;
		line.y2 = viper::random::getRandomInt(SCREEN_HEIGHT);
    }

    for (CustomPoint& point : points) {
        point.red = viper::random::getRandomInt(255);
        point.green = viper::random::getRandomInt(255);
        point.blue = viper::random::getRandomInt(255);
        point.x = viper::random::getRandomInt(SCREEN_WIDTH);
        point.y = viper::random::getRandomInt(SCREEN_HEIGHT);
	}

	std::cout << lines[0].red << " " << lines[0].green << " " << lines[0].blue << std::endl;

    int randomRed = viper::random::getRandomInt(255);
    int randomGreen = viper::random::getRandomInt(255);
    int randomBlue = viper::random::getRandomInt(255);

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set render draw color to black
        SDL_RenderClear(renderer); // Clear the renderer

        //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set render draw color to green
        //SDL_RenderFillRect(renderer, &greenSquare); // Render the rectangle
        
        for (const CustomPoint& point : points) {
            SDL_SetRenderDrawColor(renderer, point.red, point.green, point.blue, 255);
            SDL_RenderPoint(renderer, point.x, point.y);
		}

        for (const CustomLine& line : lines) {
            SDL_SetRenderDrawColor(renderer, line.red, line.green, line.blue, 255);
            SDL_RenderLine(renderer, line.x1, line.y1, line.x2, line.y2);
		}

        SDL_RenderPresent(renderer); // Render the screen
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}