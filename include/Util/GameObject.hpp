#ifndef UTIL_GAME_OBJECT_HPP
#define UTIL_GAME_OBJECT_HPP

#include <glm/fwd.hpp>
#include <memory>
#include <vector>

#include "Core/Drawable.hpp"
#include "Util/Transform.hpp"

namespace Util {
/**
 * @class GameObject
 * @brief A class representing a game object.
 *
 * This class encapsulates the properties and behaviors of a game object.
 * @note This is an abstract class. Inherit from this class to create your own
 * game objects.
 *
 */
class GameObject {
public:
    /**
     * @brief Default constructor.
     */
    GameObject() = default;

    /**
     * @brief Parameterized constructor.
     *
     * @param drawable The Util::Drawable component of the game object.
     * @param zIndex The z-index of the game object.
     * @param visible The visibility of the game object.
     * @param children The children of the game object.
     */
    GameObject(std::unique_ptr<Core::Drawable> drawable, const float zIndex,
               const glm::vec2 &pivot = {0, 0}, const bool visible = true,
               const std::vector<std::shared_ptr<GameObject>> &children =
                   std::vector<std::shared_ptr<GameObject>>())
        : m_Drawable(std::move(drawable)),
          m_Children(children),
          m_ZIndex(zIndex),
          m_Visible(visible),
          m_Pivot(pivot) {}

    // Deleted copy constructor.
    GameObject(const GameObject &other) = delete;

    // Deleted move constructor.
    GameObject(GameObject &&other) = delete;

    /**
     * @brief Default destructor.
     */
    virtual ~GameObject() = default;

    // Deleted assignment operator.
    GameObject &operator=(const GameObject &other) = delete;

    /**
     * @brief Get the z-index of the game object.
     *
     * @return The z-index of the game object.
     */
    float GetZIndex() const { return m_ZIndex; }

    /**
     * @brief Get the transform of the game object.
     *
     * @return The transform of the game object.
     */
    Transform GetTransform() const { return m_Transform; }

    /**
     * @brief Get the size of its drawable component.
     *
     * @return vec2(x, y) representing the size of the drawable component.
     */
    glm::vec2 GetScaledSize() const {
        return m_Drawable->GetSize() * m_Transform.scale;
    };

    glm::vec2 GetSize() const { return m_Drawable->GetSize(); };
    /**
     * @brief Get the children of the game object.
     *
     * @return The children of the game object.
     */
    const std::vector<std::shared_ptr<GameObject>> &GetChildren() const {
        return m_Children;
    }

    bool GetVisible() { return m_Visible; }

    /**
     * @brief Set the pivot of the game object.
     *
     * @param pivot The pivot of the game object.
     */
    // void SetPivot(glm::vec2 pivot) { m_Pivot = pivot; }

    void SetPivotToLeftButton() {
        m_Pivot = {(-1) * glm::int64(m_Drawable->GetSize().x / 2),
                   (-1) * glm::int64(m_Drawable->GetSize().y / 2)};
    }

    /**
     * @brief Set the z-index of the game object.
     * z-index is used to determine the order in which game objects are drawn,
     * the greater z-index, the topper the its Util::Drawable is
     *
     * @param index The new z-index of the game object.
     */
    void SetZIndex(float index) { m_ZIndex = index; }

    /**
     * @brief Set the drawable component of the game object.
     *
     * @param drawable The new drawable component of the game object.
     */
    void SetDrawable(const std::shared_ptr<Core::Drawable> &drawable) {
        m_Drawable = drawable;
    }

    /**
     * @brief Set the visibility of the game object.
     *
     * @param visible The new visibility of the game object.
     */
    void SetVisible(const bool visible) { m_Visible = visible; }

    void SetPosition(const glm::vec2 position) {
        m_Transform.translation = position;
    }

    /**
     * @brief Add a child to the game object.
     *
     * @param child The new child of the game object.
     */
    void AddChild(const std::shared_ptr<GameObject> &child) {
        m_Children.push_back(child);
    }

    /**
     * @brief Remove a child from the game object.
     *
     * @param child The child to be removed.
     */
    void RemoveChild(const std::shared_ptr<GameObject> &child) {
        m_Children.erase(
            std::remove(m_Children.begin(), m_Children.end(), child),
            m_Children.end());
    }

    void Draw();

protected:
    Util::Transform m_Transform; // IDK if this should be here.

    std::shared_ptr<Core::Drawable> m_Drawable = nullptr;
    std::vector<std::shared_ptr<GameObject>> m_Children;

    float m_ZIndex;
    bool m_Visible = true;
    glm::vec2 m_Pivot;
};
} // namespace Util
#endif
