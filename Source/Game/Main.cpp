#include "Math/Math.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
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

    // Dog Graph
    std::vector<viper::vec2> points{
        { 45, 20 },
        { 15, 20 },
        { 10, 15 },
        { 10, 5 },
        { 0, -5 },
        {  10, -5 },
        {  20, -10 },
        {  40, -10 },
        {  50, -5 },
        {  60, -5 },
        {  50, 5 },
        {  50, 15 },
        {  45, 20 },
        {  40, 20 },
        {  50, 30 },
        {  50, 45 },
        {  50, 40 },
        {  55, 35 },
        {  55, 30 },
        {  50, 20 },
        {  60, 30 },
        {  60, 40 },
        {  55, 45 },
        {  50, 45 },
        {  45, 50 },
        {  35, 50 },
        {  35, 35 },
        {  35, 50 },
        {  30, 50 },
        {  25, 45 },
        {  25, 40 },
        {  25, 45 },
        {  25, 50 },
        {  20, 50 },
        {  15, 40 },
        {  15, 25 },
        {  20, 20 },
        
    };

    viper::Model model{ points, viper::vec3{0, 0, 1} };
    viper::Transform transform{ viper::vec2{640, 512}, 0, 10 };

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

        //play drum sounds
        //if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q)) audio.PlaySound("bass");
        //if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W)) audio.PlaySound("snare");
        //if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E)) audio.PlaySound("clap");
        //if (input.GetKeyDown(SDL_SCANCODE_R) && !input.GetPreviousKeyDown(SDL_SCANCODE_W)) audio.PlaySound("close-hat");
        //if (input.GetKeyDown(SDL_SCANCODE_T) && !input.GetPreviousKeyDown(SDL_SCANCODE_E)) audio.PlaySound("open-hat");

        //if (input.GetKeyDown(SDL_SCANCODE_A)) transform.rotation -= viper::math::degToRad(90 * time.GetDeltaTime());
        //if (input.GetKeyDown(SDL_SCANCODE_D)) transform.rotation += viper::math::degToRad(90 * time.GetDeltaTime());

        float speed = 200;

        viper::vec2 direction{ 0, 0 };
        if (input.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;//speed * time.GetDeltaTime();
        if (input.GetKeyDown(SDL_SCANCODE_S)) direction.y =  1;//speed * time.GetDeltaTime();
        if (input.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;//speed * time.GetDeltaTime();
        if (input.GetKeyDown(SDL_SCANCODE_D)) direction.x =  1;//speed * time.GetDeltaTime();

        if (direction.LengthSqr() > 0) {
            direction = direction.Normalized();
            transform.position += (direction * speed) * time.GetDeltaTime();
        }

        // draw
        viper::vec3 color{ 0, 0, 0 };

        renderer.SetColor(color.r, color.g, color.b);
        renderer.Clear();

        //model.Draw(renderer, input.GetMousePosition(), 0, 2);
        model.Draw(renderer, transform);

        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }


        viper::vec2 speedz(-40.0f, 0.0f);
        float length = speedz.Length();

        for (auto& star : stars) {
            star += speedz * time.GetDeltaTime();
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