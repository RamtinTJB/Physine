#ifndef PHYSINE_COLOR_H_
#define PHYSINE_COLOR_H_

#include <initializer_list>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

namespace {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist255(0, 255);
}

struct Color {
    int r, g, b;

    Color() : r{0}, g{0}, b{0} {}
    Color(int r, int g, int b) : r{r}, g{g}, b{b} {}
    Color(const std::initializer_list<int>& list) {
        std::vector<int> v(list);
        r = v[0];
        g = v[1];
        b = v[2];
    }

    static Color random_color() {
        int r = dist255(rng);
        int g = dist255(rng);
        int b = dist255(rng);
        return Color{r, g, b};
    }
    
    operator sf::Color () const {
        return sf::Color(r, g, b);
    }
};

const Color RED{255, 0, 0};
const Color GREEN{0, 255, 0};
const Color BLUE{0, 0, 255};

#endif
