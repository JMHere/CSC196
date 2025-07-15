#include "Math/Math.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Core/Time.h"
#include <Renderer.h>
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include <iostream>
#include <vector>


constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 1024;

int main(int argc, char* argv[]) {
    // initialize engine systems
    viper::Time time;

    viper::Renderer renderer;

    renderer.Initialize();
    renderer.CreateWindow("Viper Engine", 1280, 1024);

    viper::InputSystem input;
    input.Initialize();

    // create audio system
    viper::AudioSystem audio;
    audio.Initialize();

    // initialize sounds
    audio.AddSound("bass.wav", "bass");
    audio.AddSound("snare.wav", "snare");
    audio.AddSound("clap.wav", "clap");
    audio.AddSound("close-hat.wav", "close-hat");
    audio.AddSound("open-hat.wav", "open-hat");

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
	}*/

    std::vector<viper::vec2> points;

    // MAIN LOOP
    while (!quit) {
        time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        // update engine systems
        audio.Update();
        input.Update();
        

        // get input
        /*if (input.GetKeyReleased(SDL_SCANCODE_A)) {
            std::cout << "pressed\n";
        }

        if (input.GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            std::cout << "mouse pressed\n";
        }*/

        // No space Check
        /*if (input.GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
            
        }*/

        
        // 10 pixel check
        if (input.GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            viper::vec2 position = input.GetMousePosition();
            if ((int)points.size() == 0) points.push_back(position);
            else if ((position - points.back()).Length() > 10)points.push_back(position);

        }

        if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q)) {
            audio.PlaySound("bass");
        }

        if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W)) {
            audio.PlaySound("snare");
        }

        if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E)) {
            audio.PlaySound("clap");
        }

        if (input.GetKeyDown(SDL_SCANCODE_R) && !input.GetPreviousKeyDown(SDL_SCANCODE_W)) {
            audio.PlaySound("close-hat");
        }

        if (input.GetKeyDown(SDL_SCANCODE_T) && !input.GetPreviousKeyDown(SDL_SCANCODE_E)) {
            audio.PlaySound("open-hat");
        }

        /*viper::vec2 mouse = input.GetMousePosition();
        std::cout << mouse.x << " " << mouse.y << std::endl;*/

        // draw
        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        /*for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor(255, 0, 0);
            std::cout << points[i].x << std::endl;
            renderer.DrawLine(points[i].x, points[i].y, points[static_cast<std::vector<viper::vec2, std::allocator<viper::vec2>>::size_type>(i) + 1].x, points[static_cast<std::vector<viper::vec2, std::allocator<viper::vec2>>::size_type>(i) + 1].y);
        }*/


        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }


        viper::vec2 speed(-40.0f, 0.0f);
        float length = speed.Length();

        /*for (auto& star : stars) {
            star += speed * time.GetDeltaTime();
            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;
            renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawPoint(star.x, star.y);
        }*/
        
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
    audio.Shutdown();

    return 0;
}