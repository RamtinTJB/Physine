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
    int r, g, b, a;

    Color() : r{0}, g{0}, b{0}, a{255} {}
    Color(int r, int g, int b) : r{r}, g{g}, b{b}, a{255} {}
    Color(int r, int g, int b, int a) : r{r}, g{g}, b{b}, a{a} {}
    Color(const std::initializer_list<int>& list) {
        std::vector<int> v(list);
        r = v[0];
        g = v[1];
        b = v[2];
        a = 255;
    }

    static Color random_color() {
        int r = dist255(rng);
        int g = dist255(rng);
        int b = dist255(rng);
        return Color{r, g, b};
    }
    
    operator sf::Color () const {
        return sf::Color(r, g, b, a);
    }
};

const Color WHITE       {255, 255, 255};
const Color SILVER      {192, 192, 192};
const Color GRAY        {128, 128, 128};
const Color BLACK       {0, 0, 0};
const Color RED         {255, 0, 0};
const Color MAROON      {128, 0, 0};
const Color YELLOW      {255, 255, 0};
const Color OLIVE       {128, 128, 0};
const Color LIME        {0, 255, 0};
const Color GREEN       {0, 128, 0};
const Color AQUA        {0, 255 ,255};
const Color TEAL        {0, 128, 128};
const Color BLUE        {0, 0, 255};
const Color NAVY        {0, 0, 128};
const Color FUCHSIA     {255, 0, 255};
const Color PURPLE      {128, 0, 128};

const Color TRANSPARENT(0, 0, 0, 0);

#endif
