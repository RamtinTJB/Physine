#include "drawable.h"

#include <stdexcept>

void ImageDrawable::load_image() {
    if (!texture_.loadFromFile(image_path_)) {
        throw std::invalid_argument("Image does not exist");
    } else {
        std::cout << "Image Loaded!" << std::endl;
    }
}

void ImageDrawable::render([[maybe_unused]] const Transform* transform) {
    return;
}

Vector2f ImageDrawable::get_top_left(const Transform* transform) const {
    double width = transform->scale.x();
    double height = transform->scale.y();
    return Vector2f{transform->position.x() - width/2, transform->position.y() - height/2};
}

void ImageDrawable::draw(sf::RenderWindow* window, const Transform* transform) const {
    sf::Sprite sprite;
    sprite.setTexture(texture_);
    auto top_left = get_top_left(transform);
    auto center_offset = transform->position - top_left;
    sprite.setOrigin(center_offset.x(), center_offset.y());
    auto pos = transform->position;
    auto scale = transform->scale;
    sprite.setPosition(pos.x(), pos.y());
    sprite.setRotation(transform->rotation);
    // TODO Make Image resizing work
    /* sprite.setScale(scale.x(), scale.y()); */
    window->draw(sprite);
}
