#pragma once

// cereal
#include <cereal/cereal.hpp>
// cereal archive
#include <cereal/archives/json.hpp>
// cereal std 
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/queue.hpp>
#include <cereal/types/set.hpp>
#include <cereal/types/bitset.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/polymorphic.hpp>

// glm
#include <glm/glm.hpp>

// sfml
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// SERIALIZE FUNCTION DEFINITIONS FOR SFML, GLM, & OTHER LIBRARY TYPES
// ALSO INCLUDES INCLUDE HEADERS FOR ALL OF THE NECESSARY STANDARD LIBRARY TYPES


namespace glm 
{
    // glm::vec3
    template<class Archive>
    void serialize(Archive& archive, vec3& v3)
    {
        archive(cereal::make_nvp("x", v3.x), cereal::make_nvp("y", v3.y), cereal::make_nvp("z", v3.z));
    }

    // glm::vec2
    template<class Archive>
    void serialize(Archive& archive, vec2& v2)
    {
        archive(cereal::make_nvp("x", v2.x), cereal::make_nvp("y", v2.y));
    }
}

namespace sf 
{
    // sf::Vector2f
    template<class Archive>
    void serialize(Archive& archive, Vector2f v2)
    {
        archive(cereal::make_nvp("x", v2.x), cereal::make_nvp("y", v2.y));
    }

    // sf::Vector2i
    template<class Archive>
    void serialize(Archive& archive, Vector2i v2)
    {
        archive(cereal::make_nvp("x", v2.x), cereal::make_nvp("y", v2.y));
    }

    // sf::Color
    template<class Archive>
    void serialize(Archive& archive, Color& c)
    {
        archive(cereal::make_nvp("r", c.r), cereal::make_nvp("g", c.g), cereal::make_nvp("b", c.b), cereal::make_nvp("a", c.a));
    }

    // sf::FloatRect
    template<class Archive>
    void serialize(Archive& archive, FloatRect& fr)
    {
        archive(cereal::make_nvp("left", fr.left), cereal::make_nvp("top", fr.top), cereal::make_nvp("width", fr.width), cereal::make_nvp("height", fr.height));
    }

}