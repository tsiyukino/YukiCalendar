#include "RecurrenceRule.h"
#include <QJsonArray>
#include <algorithm>

RecurrenceRule::RecurrenceRule(QObject *parent)
    : QObject(parent)
    , m_type(None)
    , m_interval(1)
    , m_count(0)
    , m_months(0)
    , m_days(0)
    , m_hours(0)
    , m_minutes(0)
    , m_seconds(0)
{
}

RecurrenceRule::RecurrenceRule(const RecurrenceRule& other, QObject *parent)
    : QObject(parent)
    , m_type(other.m_type)
    , m_interval(other.m_interval)
    , m_weekDays(other.m_weekDays)
    , m_until(other.m_until)
    , m_count(other.m_count)
    , m_months(other.m_months)
    , m_days(other.m_days)
    , m_hours(other.m_hours)
    , m_minutes(other.m_minutes)
    , m_seconds(other.m_seconds)
{
}

void RecurrenceRule::setType(RecurrenceType type)
{
    if (m_type != type) {
        m_type = type;
        emit typeChanged();
    }
}

void RecurrenceRule::setInterval(int interval)
{
    if (m_interval != interval) {
        m_interval = interval;
        emit intervalChanged();
    }
}

void RecurrenceRule::setWeekDays(const QList<int>& weekDays)
{
    if (m_weekDays != weekDays) {
        m_weekDays = weekDays;
        emit weekDaysChanged();
    }
}

void RecurrenceRule::setUntil(const QDateTime& until)
{
    if (m_until != until) {
        m_until = until;
        emit untilChanged();
    }
}

void RecurrenceRule::setCount(int count)
{
    if (m_count != count) {
        m_count = count;
        emit countChanged();
    }
}

void RecurrenceRule::setMonths(int months)
{
    if (m_months != months) {
        m_months = months;
        emit monthsChanged();
    }
}

void RecurrenceRule::setDays(int days)
{
    if (m_days != days) {
        m_days = days;
        emit daysChanged();
    }
}

void RecurrenceRule::setHours(int hours)
{
    if (m_hours != hours) {
        m_hours = hours;
        emit hoursChanged();
    }
}

void RecurrenceRule::setMinutes(int minutes)
{
    if (m_minutes != minutes) {
        m_minutes = minutes;
        emit minutesChanged();
    }
}

void RecurrenceRule::setSeconds(int seconds)
{
    if (m_seconds != seconds) {
        m_seconds = seconds;
        emit secondsChanged();
    }
}

QJsonObject RecurrenceRule::toJson() const
{
    QJsonObject json;
    json["type"] = static_cast<int>(m_type);
    json["interval"] = m_interval;

    QJsonArray weekDaysArray;
    for (int day : m_weekDays) {
        weekDaysArray.append(day);
    }
    json["weekDays"] = weekDaysArray;

    if (m_until.isValid()) {
        json["until"] = m_until.toString(Qt::ISODate);
    }

    json["count"] = m_count;
    json["months"] = m_months;
    json["days"] = m_days;
    json["hours"] = m_hours;
    json["minutes"] = m_minutes;
    json["seconds"] = m_seconds;

    return json;
}

RecurrenceRule* RecurrenceRule::fromJson(const QJsonObject& json, QObject *parent)
{
    auto rule = new RecurrenceRule(parent);

    rule->setType(static_cast<RecurrenceType>(json["type"].toInt()));
    rule->setInterval(json["interval"].toInt(1));

    QList<int> weekDays;
    QJsonArray weekDaysArray = json["weekDays"].toArray();
    for (const QJsonValue& value : weekDaysArray) {
        weekDays.append(value.toInt());
    }
    rule->setWeekDays(weekDays);

    if (json.contains("until")) {
        rule->setUntil(QDateTime::fromString(json["until"].toString(), Qt::ISODate));
    }

    rule->setCount(json["count"].toInt(0));
    rule->setMonths(json["months"].toInt(0));
    rule->setDays(json["days"].toInt(0));
    rule->setHours(json["hours"].toInt(0));
    rule->setMinutes(json["minutes"].toInt(0));
    rule->setSeconds(json["seconds"].toInt(0));

    return rule;
}

QList<QDateTime> RecurrenceRule::calculateOccurrences(const QDateTime& startTime, const QDateTime& rangeStart, const QDateTime& rangeEnd) const
{
    if (m_type == None) {
        QList<QDateTime> result;
        if (startTime >= rangeStart && startTime <= rangeEnd) {
            result.append(startTime);
        }
        return result;
    }

    switch (m_type) {
    case Daily:
        return calculateDailyOccurrences(startTime, rangeStart, rangeEnd);
    case Weekly:
        return calculateWeeklyOccurrences(startTime, rangeStart, rangeEnd);
    case Monthly:
        return calculateMonthlyOccurrences(startTime, rangeStart, rangeEnd);
    case Yearly:
        return calculateYearlyOccurrences(startTime, rangeStart, rangeEnd);
    case Custom:
        return calculateCustomOccurrences(startTime, rangeStart, rangeEnd);
    default:
        return QList<QDateTime>();
    }
}

QList<QDateTime> RecurrenceRule::calculateDailyOccurrences(const QDateTime& startTime, const QDateTime& rangeStart, const QDateTime& rangeEnd) const
{
    QList<QDateTime> occurrences;
    QDateTime current = startTime;
    int occurrenceCount = 0;

    while (current <= rangeEnd) {
        if (m_until.isValid() && current > m_until) {
            break;
        }

        if (m_count > 0 && occurrenceCount >= m_count) {
            break;
        }

        if (current >= rangeStart) {
            occurrences.append(current);
        }

        current = current.addDays(m_interval);
        occurrenceCount++;
    }

    return occurrences;
}

QList<QDateTime> RecurrenceRule::calculateWeeklyOccurrences(const QDateTime& startTime, const QDateTime& rangeStart, const QDateTime& rangeEnd) const
{
    QList<QDateTime> occurrences;
    QDateTime current = startTime;
    int occurrenceCount = 0;

    while (current <= rangeEnd) {
        if (m_until.isValid() && current > m_until) {
            break;
        }

        if (m_count > 0 && occurrenceCount >= m_count) {
            break;
        }

        // Check if current day of week is in the weekDays list
        if (m_weekDays.isEmpty() || m_weekDays.contains(current.date().dayOfWeek())) {
            if (current >= rangeStart) {
                occurrences.append(current);
                occurrenceCount++;
            }
        }

        current = current.addDays(1);

        // Move to next week if we've completed a week
        if (current.date().dayOfWeek() == 1) { // Monday
            current = current.addDays(7 * (m_interval - 1));
        }
    }

    return occurrences;
}

QList<QDateTime> RecurrenceRule::calculateMonthlyOccurrences(const QDateTime& startTime, const QDateTime& rangeStart, const QDateTime& rangeEnd) const
{
    QList<QDateTime> occurrences;
    QDateTime current = startTime;
    int occurrenceCount = 0;

    while (current <= rangeEnd) {
        if (m_until.isValid() && current > m_until) {
            break;
        }

        if (m_count > 0 && occurrenceCount >= m_count) {
            break;
        }

        if (current >= rangeStart) {
            occurrences.append(current);
        }

        current = current.addMonths(m_interval);
        occurrenceCount++;
    }

    return occurrences;
}

QList<QDateTime> RecurrenceRule::calculateYearlyOccurrences(const QDateTime& startTime, const QDateTime& rangeStart, const QDateTime& rangeEnd) const
{
    QList<QDateTime> occurrences;
    QDateTime current = startTime;
    int occurrenceCount = 0;

    while (current <= rangeEnd) {
        if (m_until.isValid() && current > m_until) {
            break;
        }

        if (m_count > 0 && occurrenceCount >= m_count) {
            break;
        }

        if (current >= rangeStart) {
            occurrences.append(current);
        }

        current = current.addYears(m_interval);
        occurrenceCount++;
    }

    return occurrences;
}

QList<QDateTime> RecurrenceRule::calculateCustomOccurrences(const QDateTime& startTime, const QDateTime& rangeStart, const QDateTime& rangeEnd) const
{
    QList<QDateTime> occurrences;
    QDateTime current = startTime;
    int occurrenceCount = 0;

    while (current <= rangeEnd) {
        if (m_until.isValid() && current > m_until) {
            break;
        }

        if (m_count > 0 && occurrenceCount >= m_count) {
            break;
        }

        if (current >= rangeStart) {
            occurrences.append(current);
        }

        // Add custom interval
        current = current.addMonths(m_months);
        current = current.addDays(m_days);
        current = current.addSecs(m_hours * 3600 + m_minutes * 60 + m_seconds);
        occurrenceCount++;
    }

    return occurrences;
}
