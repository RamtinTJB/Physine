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

class Color {
    public:
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

        static const Color WHITE;
        static const Color SILVER;
        static const Color GRAY;
        static const Color BLACK;
        static const Color RED;
        static const Color MAROON;
        static const Color YELLOW;
        static const Color OLIVE;
        static const Color LIME;
        static const Color GREEN;
        static const Color AQUA;
        static const Color TEAL;
        static const Color BLUE;
        static const Color NAVY;
        static const Color FUCHSIA;
        static const Color PURPLE;

        static const Color TRANSPARENT;
};


#endif
