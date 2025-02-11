#pragma once

#include "Fyziks/Api.h"
#include "Body.h"

#include <vector>
#include <map>

namespace fy {
    class FYZIKS_API World {
    public:
        std::vector<Body *> bodies;
        fy::Vec2f gravity;
        int iterations;
        float timeStep;

        World() : gravity(fy::Vec2f(0, 9.81f)), iterations(8), timeStep(1.0f / 60.0f) {}

        void step();

        void add(Body *body) {
            bodies.push_back(body);
        }

        void remove(Body *body) {
            for (auto it = bodies.begin(); it != bodies.end(); ++it) {
                if (*it == body) {
                    bodies.erase(it);
                    return;
                }
            }
        }

        void clear() {
            bodies.clear();
        }

    private:
        void broadPhase();

        void applyForces();

        void moveObjects();
    };
}
