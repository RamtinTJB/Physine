#ifndef PHYSINE_COLOR_H_
#define PHYSINE_COLOR_H_

#include <initializer_list>
#include <vector>

struct Color {
    int r, g, b;

    Color(int r, int g, int b) : r{r}, g{g}, b{b} {}
    Color(const std::initializer_list<int>& list) {
        std::vector<int> v(list);
        r = v[0];
        g = v[1];
        b = v[2];
    }
};

const Color RED{255, 0, 0};
const Color GREEN{0, 255, 0};
const Color BLUE{0, 0, 255};

#endif
