#include "Render.hpp"
#include "Scene.hpp"
#include "Triangle.hpp"
#include "vector.hpp"
#include "common.hpp"
#include "material.hpp"

#include <chrono>

// In the main function of the program, we create the scene (create objects and
// lights) as well as set the options for the render (image width and height,
// maximum recursion depth, field-of-view, etc.). We then call the render
// function().
int main(int argc, char** argv)
{

    // Change the definition here to change resolution
    Scene scene(784, 784);

    Material* red = new Material(MaterialType::DIFFUSE, Vector3f(0.0f));
    red->kd = Vector3f(0.63f, 0.065f, 0.05f);
    Material* green = new Material(MaterialType::DIFFUSE, Vector3f(0.0f));
    green->kd = Vector3f(0.14f, 0.45f, 0.091f);
    Material* white = new Material(MaterialType::DIFFUSE, Vector3f(0.0f));
    white->kd = Vector3f(0.725f, 0.71f, 0.68f);
    Material* light = new Material(MaterialType::DIFFUSE, ( Vector3f(0.747f + 0.058f, 0.747f + 0.258f, 0.747f)*8.0f +  Vector3f(0.740f + 0.287f, 0.740f + 0.160f, 0.740f) *15.6f+  Vector3f(0.737f + 0.642f, 0.737f + 0.159f, 0.737f)*18.4f));
    light->kd = Vector3f(0.65f);

    TriangleMesh floor("../models/cornellbox/floor.obj", white);
    TriangleMesh shortbox("../models/cornellbox/shortbox.obj", white);
    TriangleMesh tallbox("../models/cornellbox/tallbox.obj", white);
    TriangleMesh left("../models/cornellbox/left.obj", red);
    TriangleMesh right("../models/cornellbox/right.obj", green);
    TriangleMesh light_("../models/cornellbox/light.obj", light);

    scene.Add(&floor);
    scene.Add(&shortbox);
    scene.Add(&tallbox);
    scene.Add(&left);
    scene.Add(&right);
    scene.Add(&light_);

    scene.BuildBvh();

    Render r;

    auto start = std::chrono::system_clock::now();
    r.render(scene);
    auto stop = std::chrono::system_clock::now();

    std::cout << "Render complete: \n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";

    return 0;
}