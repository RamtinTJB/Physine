#include <cmath>
#include <vector>
#include <random>
#include <cstdio>

#include "color.h"
#include "common.h"

namespace {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist255(0, 255);

    double hue_to_rgb(double p, double q, double t) {
        if (t < 0) t += 1;
        if (t > 1) t -= 1;
        if (t < 1.0/6.0) return p + (q - p) * 6 * t;
        if (t < 1.0/2.0) return q;
        if (t < 2.0/3.0) return p + (q - p) * (2.0/3.0 - t) * 6;
        return p;
    }
}

Color::Color(const std::initializer_list<int>& list) {
    std::vector<int> v(list);
    r = v[0];
    g = v[1];
    b = v[2];
    a = 255;
}

Color Color::random_color() {
    int r = dist255(rng);
    int g = dist255(rng);
    int b = dist255(rng);
    return Color{r, g, b};
}

Color Color::FromHSL(double h, double s, double l) {
    double r, g, b;
    if (std::abs(s) < EPSILON) {
        r = l; g = l; b = l;
    } else {
        double q = l < 0.5 ? l * (1.0 + s) : l + s - l*s;
        double p = 2*l - q;
        r = hue_to_rgb(p, q, h+1.0/3.0);
        g = hue_to_rgb(p, q, h);
        b = hue_to_rgb(p, q, h-1.0/3.0);
    }

    return Color{int(std::round(r*255)), int(std::round(g*255)), int(std::round(b*255)) };
} 

Color Color::FromHEX(const std::string& hex) {
    int r, g, b;
    sscanf(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);
    return Color{r, g, b};
}

const Color Color::WHITE       {255, 255, 255};
const Color Color::SILVER      {192, 192, 192};
const Color Color::GRAY        {128, 128, 128};
const Color Color::BLACK       {0, 0, 0};
const Color Color::RED         {255, 0, 0};
const Color Color::MAROON      {128, 0, 0};
const Color Color::YELLOW      {255, 255, 0};
const Color Color::OLIVE       {128, 128, 0};
const Color Color::LIME        {0, 255, 0};
const Color Color::GREEN       {0, 128, 0};
const Color Color::AQUA        {0, 255 ,255};
const Color Color::TEAL        {0, 128, 128};
const Color Color::BLUE        {0, 0, 255};
const Color Color::NAVY        {0, 0, 128};
const Color Color::FUCHSIA     {255, 0, 255};
const Color Color::PURPLE      {128, 0, 128};

const Color Color::TRANSPARENT(0, 0, 0, 0);
