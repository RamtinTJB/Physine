#ifndef PHYSINE_COLOR_H_
#define PHYSINE_COLOR_H_

#include <initializer_list>
#include <SFML/Graphics.hpp>
#include <string>

class Color {
    public:
        int r, g, b, a;

        Color() : r{0}, g{0}, b{0}, a{255} {}
        Color(int r, int g, int b) : r{r}, g{g}, b{b}, a{255} {}
        Color(int r, int g, int b, int a) : r{r}, g{g}, b{b}, a{a} {}
        Color(const std::initializer_list<int>&);

        static Color random_color();
        
        operator sf::Color () const {
            return sf::Color(r, g, b, a);
        }

        static Color FromHSL(double h, double s, double l);
        static Color FromHEX(const std::string&);

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
