#ifndef UTIL_TEXT_HPP
#define UTIL_TEXT_HPP

#include "pch.hpp" // IWYU pragma: export

#include <functional>

#include "Core/Drawable.hpp"
#include "Core/Texture.hpp"

#include "Util/Color.hpp"
#include "Util/Logger.hpp"
#include "Util/Transform.hpp"

namespace Util {
/**
 * @class Text
 * @brief A class representing a text.
 *
 * This class encapsulates the properties and behaviors of a text.
 * It includes properties such as texture and surface.
 * It also includes behaviors such as drawing the text.
 */
class Text : public Core::Drawable {
public:
    Text(const std::string &font, int size, const std::string &text,
<<<<<<< HEAD
         const Util::Color &color = Color(0.5F, 0.5F, 0.5F, 1.0F),
         int wrapLength = 0);
=======
         const Util::Color &color = Color(127, 127, 127));
>>>>>>> upstream/main

    glm::vec2 GetSize() const override { return m_Size; };

    /**
     * @brief Sets the text to the specified string.
     *
     * @param text The string to set.
     */
    void SetText(const std::string &text) {
        m_Text = text;
        ApplyTexture();
    }

    /**
     * @brief Sets the color of the text.
     *
     * @param color The color to set.
     */
    void SetColor(const Util::Color &color) {
        m_Color = color;
        ApplyTexture();
    };

    /**
     * @brief Draws the text with a given transform and z-index.
     *
     * @param transform The transform to apply to the text.
     * @param zIndex The z-index at which to draw the text.
     */
    void Draw(const Transform &transform, const float zIndex) override;

private:
    void InitProgram();
    void InitVertexArray();
    void InitUniformBuffer();

    /**
     * @brief Applies the texture to the text.
     * @note The user should call this function after updating the texture in
     * case of custom methods/functions are used.
     */
    void ApplyTexture();

    static constexpr int UNIFORM_SURFACE_LOCATION = 0;

    static std::unique_ptr<Core::Program> s_Program;
    static std::unique_ptr<Core::VertexArray> s_VertexArray;
    static std::unique_ptr<Core::UniformBuffer<Core::Matrices>> s_UniformBuffer;

private:
    std::unique_ptr<Core::Texture> m_Texture = nullptr;
    std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)>> m_Font;

    std::string m_Text;
    Util::Color m_Color;
    glm::vec2 m_Size;
    int m_wrapLength;
};
} // namespace Util

#endif
