#pragma once
#include <memory>
#include "Vector.h"
#include "Color.h"
#include <cstddef>
#include <vector>

namespace pba
{
    class ParticleStateData
    {
    public:
        // count
        std::size_t nb() const { return positions.size(); }

        // position
        const Vector &pos(std::size_t i) const { return positions[i]; }
        void set_pos(std::size_t i, const Vector &p) { positions[i] = p; }

        // velocity
        const Vector &vel(std::size_t i) const { return velocities[i]; }
        void set_vel(std::size_t i, const Vector &v) { velocities[i] = v; }

        // color
        const Color &color(std::size_t i) const { return colors[i]; }

        void add(const Vector &p, const Vector &v, const Color &c)
        {
            positions.push_back(p);
            velocities.push_back(v);
            colors.push_back(c);
        }

        void clear()
        {
            positions.clear();
            velocities.clear();
            colors.clear();
        }

        void set_color(std::size_t i, const Color &c) { colors[i] = c; }

    private:
        std::vector<Vector> positions;
        std::vector<Vector> velocities;
        std::vector<Color> colors;
    };

    using ParticleState = std::shared_ptr<ParticleStateData>;
}