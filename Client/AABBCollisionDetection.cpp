//
// Created by Quentin Liardeaux on 11/7/19.
//

#include "AABBCollisionDetection.hpp"

AABBCollisionDetection::AABBCollisionDetection(const Frame &frameRect)
    : m_frameRect(frameRect)
{}

bool AABBCollisionDetection::isInside(double value, double min, double max) const {
    return min <= value && max >= value;
}

bool AABBCollisionDetection::isCollidingWith(shared_ptr<CollisionDetection> object) const {
    auto rectObject = dynamic_cast<AABBCollisionDetection*>(object.get());

    if (isInside(rectObject->m_frameRect.x, m_frameRect.x,
            m_frameRect.x + m_frameRect.width))
        return true;
    if (isInside(rectObject->m_frameRect.x + rectObject->m_frameRect.width,
            m_frameRect.x, m_frameRect.x + m_frameRect.width))
        return true;
    if (isInside(rectObject->m_frameRect.y, m_frameRect.y,
            m_frameRect.y - m_frameRect.height))
        return true;
    return isInside(rectObject->m_frameRect.y - rectObject->m_frameRect.height,
                    m_frameRect.y, m_frameRect.y - m_frameRect.height);
}