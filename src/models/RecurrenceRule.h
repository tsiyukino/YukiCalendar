#ifndef RECURRENCERULE_H
#define RECURRENCERULE_H

#include <QObject>
#include <QDateTime>
#include <QList>
#include <QJsonObject>

class RecurrenceRule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(RecurrenceType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
    Q_PROPERTY(QList<int> weekDays READ weekDays WRITE setWeekDays NOTIFY weekDaysChanged)
    Q_PROPERTY(QDateTime until READ until WRITE setUntil NOTIFY untilChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(int months READ months WRITE setMonths NOTIFY monthsChanged)
    Q_PROPERTY(int days READ days WRITE setDays NOTIFY daysChanged)
    Q_PROPERTY(int hours READ hours WRITE setHours NOTIFY hoursChanged)
    Q_PROPERTY(int minutes READ minutes WRITE setMinutes NOTIFY minutesChanged)
    Q_PROPERTY(int seconds READ seconds WRITE setSeconds NOTIFY secondsChanged)

public:
    enum RecurrenceType {
        None = 0,
        Daily = 1,
        Weekly = 2,
        Monthly = 3,
        Yearly = 4,
        Custom = 5
    };
    Q_ENUM(RecurrenceType)

    explicit RecurrenceRule(QObject *parent = nullptr);
    RecurrenceRule(const RecurrenceRule& other, QObject *parent = nullptr);

    // Getters
    RecurrenceType type() const { return m_type; }
    int interval() const { return m_interval; }
    QList<int> weekDays() const { return m_weekDays; }
    QDateTime until() const { return m_until; }
    int count() const { return m_count; }
    int months() const { return m_months; }
    int days() const { return m_days; }
    int hours() const { return m_hours; }
    int minutes() const { return m_minutes; }
    int seconds() const { return m_seconds; }

    // Setters
    void setType(RecurrenceType type);
    void setInterval(int interval);
    void setWeekDays(const QList<int>& weekDays);
    void setUntil(const QDateTime& until);
    void setCount(int count);
    void setMonths(int months);
    void setDays(int days);
    void setHours(int hours);
    void setMinutes(int minutes);
    void setSeconds(int seconds);

    // Serialization
    QJsonObject toJson() const;
    static RecurrenceRule* fromJson(const QJsonObject& json, QObject *parent = nullptr);

    // Calculate occurrences
    QList<QDateTime> calculateOccurrences(const QDateTime& startTime, const QDateTime& rangeStart, const QDateTime& rangeEnd) const;

signals:
    void typeChanged();
    void intervalChanged();
    void weekDaysChanged();
    void untilChanged();
    void countChanged();
    void monthsChanged();
    void daysChanged();
    void hoursChanged();
    void minutesChanged();
    void secondsChanged();

private:
    RecurrenceType m_type;
    int m_interval;
    QList<int> m_weekDays;
    QDateTime m_until;
    int m_count;
    int m_months;
    int m_days;
    int m_hours;
    int m_minutes;
    int m_seconds;

    QList<QDateTime> calculateDailyOccurrences(const QDateTime& startTime, const QDateTime& rangeStart, const QDateTime& rangeEnd) const;
    QList<QDateTime> calculateWeeklyOccurrences(const QDateTime& startTime, const QDateTime& rangeStart, const QDateTime& rangeEnd) const;
    QList<QDateTime> calculateMonthlyOccurrences(const QDateTime& startTime, const QDateTime& rangeStart, const QDateTime& rangeEnd) const;
    QList<QDateTime> calculateYearlyOccurrences(const QDateTime& startTime, const QDateTime& rangeStart, const QDateTime& rangeEnd) const;
    QList<QDateTime> calculateCustomOccurrences(const QDateTime& startTime, const QDateTime& rangeStart, const QDateTime& rangeEnd) const;
};

#endif // RECURRENCERULE_H
