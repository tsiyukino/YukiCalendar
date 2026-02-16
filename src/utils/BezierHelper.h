#ifndef BEZIERHELPER_H
#define BEZIERHELPER_H

#include <QPointF>
#include <QPainterPath>
#include <QLineF>

class BezierHelper
{
public:
    // Bezier curve parameters (Unity-style)
    static constexpr double RELATIVE_BEND = 0.25;
    static constexpr double MIN_BEND = 50.0;
    static constexpr int CONNECTION_STROKE_WIDTH = 2;

    // Create a Bezier curve path from start to end point
    static QPainterPath createBezierPath(const QPointF& start, const QPointF& end, bool isLeftToRight = true);

    // Calculate tangent point for control points
    static QPointF calculateTangent(const QPointF& point, const QPointF& direction, double distance);

    // Calculate tangent distance based on point distance
    static double calculateTangentDistance(const QPointF& start, const QPointF& end);
};

#endif // BEZIERHELPER_H
