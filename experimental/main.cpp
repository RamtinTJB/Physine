#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <cstdlib>

const int SCREEN_WIDTH = 2000;
const int SCREEN_HEIGHT = 2000;
const int NUM_OBJECTS = 10000;
const float TIME_STEP = 1.0f / 60.0f;
const float CIRCLE_R = 5.0f;

struct Vector2 {
    float x, y;

    Vector2 operator+(const Vector2& v) const { return { x + v.x, y + v.y }; }
    Vector2 operator-(const Vector2& v) const { return { x - v.x, y - v.y }; }
    Vector2 operator*(float s) const { return { x * s, y * s }; }
    Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
    Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
};

struct Circle {
    Vector2 position;
    Vector2 velocity;
    float radius;
    sf::CircleShape shape;
};

void UpdatePositions(std::vector<Circle>& circles, float dt) {
    for (auto& circle : circles) {
        circle.position += circle.velocity * dt;

        // Boundary collision with walls
        if (circle.position.x < circle.radius) {
            circle.position.x = circle.radius;
            circle.velocity.x *= -1;
        }
        if (circle.position.x > SCREEN_WIDTH - circle.radius) {
            circle.position.x = SCREEN_WIDTH - circle.radius;
            circle.velocity.x *= -1;
        }
        if (circle.position.y < circle.radius) {
            circle.position.y = circle.radius;
            circle.velocity.y *= -1;
        }
        if (circle.position.y > SCREEN_HEIGHT - circle.radius) {
            circle.position.y = SCREEN_HEIGHT - circle.radius;
            circle.velocity.y *= -1;
        }

        // Update the position of the shape for rendering
        circle.shape.setPosition(circle.position.x - circle.radius, circle.position.y - circle.radius);
    }
}

void ResolveCollisions(std::vector<Circle>& circles) {
    // Grid parameters
    const int gridSize = 200;
    const int gridCols = SCREEN_WIDTH / gridSize + 1;
    const int gridRows = SCREEN_HEIGHT / gridSize + 1;
    std::vector<std::vector<int>> grid(gridCols * gridRows);

    // Assign circles to grid cells
    for (int i = 0; i < circles.size(); ++i) {
        int cellX = circles[i].position.x / gridSize;
        int cellY = circles[i].position.y / gridSize;
        int cellIndex = cellY * gridCols + cellX;
        grid[cellIndex].push_back(i);
    }

    // Check collisions within each cell
    for (int cellIndex = 0; cellIndex < grid.size(); ++cellIndex) {
        const std::vector<int>& cell = grid[cellIndex];
        for (size_t i = 0; i < cell.size(); ++i) {
            Circle& A = circles[cell[i]];
            for (size_t j = i + 1; j < cell.size(); ++j) {
                Circle& B = circles[cell[j]];

                Vector2 delta = B.position - A.position;
                float dist2 = delta.x * delta.x + delta.y * delta.y;
                float radiusSum = A.radius + B.radius;

                if (dist2 < radiusSum * radiusSum) {
                    float dist = std::sqrt(dist2);
                    if (dist == 0.0f) {
                        dist = 0.01f;
                        delta = { radiusSum, 0 };
                    }
                    Vector2 normal = delta * (1.0f / dist);
                    float overlap = radiusSum - dist;

                    // Separate circles
                    A.position -= normal * (overlap * 0.5f);
                    B.position += normal * (overlap * 0.5f);

                    // Update shapes' positions
                    A.shape.setPosition(A.position.x - A.radius, A.position.y - A.radius);
                    B.shape.setPosition(B.position.x - B.radius, B.position.y - B.radius);

                    // Elastic collision response
                    Vector2 relativeVelocity = B.velocity - A.velocity;
                    float velAlongNormal = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;
                    if (velAlongNormal > 0) continue;

                    float impulse = -(1 + 1.0f) * velAlongNormal / 2; // Restitution = 1.0f
                    Vector2 impulseVector = normal * impulse;

                    A.velocity -= impulseVector;
                    B.velocity += impulseVector;
                }
            }
        }
    }
}

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "2D Physics Engine");

    std::vector<Circle> circles(NUM_OBJECTS);

    // Initialize circles with random positions and velocities
    for (auto& circle : circles) {
        circle.position = { static_cast<float>(rand() % SCREEN_WIDTH), static_cast<float>(rand() % SCREEN_HEIGHT) };
        circle.velocity = { static_cast<float>(rand() % 400 - 200), static_cast<float>(rand() % 400 - 200) };
        circle.radius = CIRCLE_R;

        // Initialize the shape
        circle.shape = sf::CircleShape(circle.radius);
        circle.shape.setFillColor(sf::Color::White);
        circle.shape.setPosition(circle.position.x - circle.radius, circle.position.y - circle.radius);
    }

    sf::Clock clock;
    float accumulator = 0.0f;
    float fpsTimer = 0.0f;
    int frameCount = 0;

    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculate delta time
        float dt = clock.restart().asSeconds();
        accumulator += dt;
        fpsTimer += dt;
        frameCount++;

        if (fpsTimer >= 1.0f) {
          float fps = frameCount / fpsTimer;
          std::cout << fps << '\n';
          fpsTimer = 0.0f;
          frameCount = 0;
        }

        // Fixed time step loop
        while (accumulator >= TIME_STEP) {
            UpdatePositions(circles, TIME_STEP);
            ResolveCollisions(circles);
            accumulator -= TIME_STEP;
        }

        // Clear screen
        window.clear(sf::Color::Black);

        // Draw the circles
        for (const auto& circle : circles) {
            window.draw(circle.shape);
        }

        // Update the window
        window.display();
    }

    return 0;
}

