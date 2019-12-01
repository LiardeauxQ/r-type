//
// Created by Quentin Liardeaux on 11/19/19.
//

#ifndef R_TYPE_IEVENT_HPP
#define R_TYPE_IEVENT_HPP

#include <string>
#include <functional>
#include <any>

using namespace std;

namespace ecs {
    class Event {
    public:
        Event(string const &type, any value);
        Event(const Event &other);
        Event(Event&& other) noexcept;
        ~Event() = default;

        [[nodiscard]] bool isOfType(string const &type) const;

        template <typename T>
        [[nodiscard]] const T& getValue() { return any_cast<T&>(m_value); }

        Event& operator=(const Event &) = default;
        Event& operator=(Event&& other) noexcept;
    private:
        size_t m_type;
        any m_value;
    };
}

#endif //R_TYPE_IEVENT_HPP
