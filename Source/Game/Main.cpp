#include "Math/Math.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Core/Time.h"
#include <Renderer.h>

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>


constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 1024;

int main(int argc, char* argv[]) {
    viper::Time time;

    viper::Renderer renderer;

    renderer.Initialize();
    renderer.CreateWindow("Viper Engine", 1280, 1024);

    SDL_Event e;
    bool quit = false;

    // create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
    }
    viper::vec2 v(30, 40);

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    /*struct CustomLine {
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
    int randomBlue = viper::random::getRandomInt(255);*/

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        viper::vec2 speed(-40.0f, 0.0f);
        float length = speed.Length();

        for (auto& star : stars) {
            star += speed * time.GetDeltaTime();
            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;
            renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawPoint(star.x, star.y);
        }
        
        /*for (int i = 0; i < 100; i++) {
            renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawLine(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024, viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);

            renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawPoint(viper::random::getRandomInt(256) * 1280, viper::random::getRandomInt(256) * 1024);
        }*/

        renderer.Present();
        
        /*for (const CustomPoint& point : points) {
            SDL_SetRenderDrawColor(renderer, point.red, point.green, point.blue, 255);
            SDL_RenderPoint(renderer, point.x, point.y);
		}

        for (const CustomLine& line : lines) {
            SDL_SetRenderDrawColor(renderer, line.red, line.green, line.blue, 255);
            SDL_RenderLine(renderer, line.x1, line.y1, line.x2, line.y2);
		}*/

    }

    renderer.Shutdown();

    return 0;
}