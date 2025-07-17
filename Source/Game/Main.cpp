#include "Math/Math.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
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

    std::vector<viper::vec2> points{
        { -5, -5 },
        {  5, -5 },
        {  5,  5 },
        { -5,  5 },
        { -5, -5 },
    };

    viper::Model model{ points, {0, 0, 1} };

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

    // MAIN LOOP
    while (!quit) {
        time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        if (input.GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

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

        if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q)) audio.PlaySound("bass");
        if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W)) audio.PlaySound("snare");
        if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E)) audio.PlaySound("clap");
        if (input.GetKeyDown(SDL_SCANCODE_R) && !input.GetPreviousKeyDown(SDL_SCANCODE_W)) audio.PlaySound("close-hat");
        if (input.GetKeyDown(SDL_SCANCODE_T) && !input.GetPreviousKeyDown(SDL_SCANCODE_E)) audio.PlaySound("open-hat");

        // draw
        viper::vec3 color{ 0, 0, 0 };

        renderer.SetColor(color.r, color.g, color.b);
        renderer.Clear();

        model.Draw(renderer, input.GetMousePosition(), time.GetTime(), 10);

        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }


        viper::vec2 speed(-40.0f, 0.0f);
        float length = speed.Length();

        for (auto& star : stars) {
            star += speed * time.GetDeltaTime();
            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;
            renderer.SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawPoint(star.x, star.y);
        }
        

        renderer.Present();

    }

    renderer.Shutdown();
    audio.Shutdown();

    return 0;
}