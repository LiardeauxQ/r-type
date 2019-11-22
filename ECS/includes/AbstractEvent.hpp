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
        virtual ~Event() {};

        [[nodiscard]] bool isOfType(string const &type) const;
        [[nodiscard]] any const &getValue() const { return m_value; }

    private:
        size_t m_type;
        any m_value;
    };
}

#endif //R_TYPE_IEVENT_HPP
