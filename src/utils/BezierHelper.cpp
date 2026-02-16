#include "BezierHelper.h"
#include <cmath>
#include <algorithm>

QPainterPath BezierHelper::createBezierPath(const QPointF& start, const QPointF& end, bool isLeftToRight)
{
    double distance = QLineF(start, end).length();
    double tangentDistance = std::max(distance * RELATIVE_BEND, MIN_BEND);

    // For left-to-right connections, tangents point horizontally
    QPointF startTangent = start + QPointF(tangentDistance, 0);  // Right
    QPointF endTangent = end + QPointF(-tangentDistance, 0);     // Left

    QPainterPath path;
    path.moveTo(start);
    path.cubicTo(startTangent, endTangent, end);

    return path;
}

QPointF BezierHelper::calculateTangent(const QPointF& point, const QPointF& direction, double distance)
{
    // Normalize direction
    double length = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

    if (length < 0.001) {
        return point;
    }

    QPointF normalized(direction.x() / length, direction.y() / length);
    return point + QPointF(normalized.x() * distance, normalized.y() * distance);
}

double BezierHelper::calculateTangentDistance(const QPointF& start, const QPointF& end)
{
    double distance = QLineF(start, end).length();
    return std::max(distance * RELATIVE_BEND, MIN_BEND);
}
