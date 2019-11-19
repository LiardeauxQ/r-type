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
    class AbstractEvent {
    public:
        AbstractEvent(string const &type, any value);
        virtual ~AbstractEvent() {};

        [[nodiscard]] bool isOfType(string const &type) const;

    private:
        size_t m_type;
        any m_value;
    };
}

#endif //R_TYPE_IEVENT_HPP
