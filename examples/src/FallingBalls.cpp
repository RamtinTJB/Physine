#include <iostream>
#include <random>

#include <Physine/common.h>
#include <Physine/world.h>
#include <Physine/drawable.h>
#include <Physine/collider.h>
#include <Physine/color.h>
#include <Physine/object_builder.h>

int main(int argc, const char** argv) {
    World world(1000, 1000);

    world.add_event_listener(EventType::Closed, [&world](Event e) { world.close(); });

    Object* rect1 = ObjectBuilder("Rect1")
        .drawable(new RectangleShape())
        .color(Color::RED)
        .collider<BoxCollider>()
        .position(Vector2f{500, 10})
        .scale(Vector2f{1000, 20})
        .mass(10000)
        .gravity(false)
        .kinetic(false)
        .build();

    Object* rect2 = ObjectBuilder::duplicate("Rect2", rect1)
        .position(Vector2f{500, 990})
        .build();

    Object* rect3 = ObjectBuilder::duplicate("Rect3", rect1)
        .position(Vector2f{10, 500})
        .scale(Vector2f{20, 1000})
        .build();

    Object* rect4 = ObjectBuilder::duplicate("Rect4", rect3)
        .position(Vector2f{990, 500})
        .build();

    world.add_object(rect1);
    world.add_object(rect2);
    world.add_object(rect3);
    world.add_object(rect4);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist500(0, 500);
    std::uniform_int_distribution<std::mt19937::result_type> dist50(10, 50);

    for (int i = 0; i < 100; i += 10) {
        Object* obj = ObjectBuilder("circle" + std::to_string(i))
            .drawable(new CircleShape())
            .color(Color::random_color())
            .position(Vector2f{i*10., i*10.})
            .scale(Vector2f{double(dist50(rng)), double(dist50(rng))})
            .velocity(Vector2f{double(dist500(rng)), double(dist500(rng))})
            .collider<CircleCollider>()
            .gravity(true)
            .build();
        obj->mass = obj->transform->scale.x();
        world.add_object(obj);
    }

    world.mainloop();

    return 0;
}
