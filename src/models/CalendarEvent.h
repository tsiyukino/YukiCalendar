#ifndef CALENDAREVENT_H
#define CALENDAREVENT_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include "RecurrenceRule.h"
#include "ActionTreeData.h"

class CalendarEvent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QDateTime startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged)
    Q_PROPERTY(QDateTime endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(int importance READ importance WRITE setImportance NOTIFY importanceChanged)
    Q_PROPERTY(QString notes READ notes WRITE setNotes NOTIFY notesChanged)
    Q_PROPERTY(RecurrenceRule* recurrence READ recurrence WRITE setRecurrence NOTIFY recurrenceChanged)
    Q_PROPERTY(ActionTreeData* actionTree READ actionTree WRITE setActionTree NOTIFY actionTreeChanged)
    Q_PROPERTY(bool useTypeDefaults READ useTypeDefaults WRITE setUseTypeDefaults NOTIFY useTypeDefaultsChanged)
    Q_PROPERTY(bool isNew READ isNew WRITE setIsNew NOTIFY isNewChanged)
    Q_PROPERTY(bool isDragging READ isDragging WRITE setIsDragging NOTIFY isDraggingChanged)

    // Layout properties (calculated by EventLayoutCalculator)
    Q_PROPERTY(int column READ column WRITE setColumn NOTIFY columnChanged)
    Q_PROPERTY(int totalColumns READ totalColumns WRITE setTotalColumns NOTIFY totalColumnsChanged)
    Q_PROPERTY(double widthFraction READ widthFraction WRITE setWidthFraction NOTIFY widthFractionChanged)
    Q_PROPERTY(double offsetFraction READ offsetFraction WRITE setOffsetFraction NOTIFY offsetFractionChanged)

public:
    explicit CalendarEvent(QObject *parent = nullptr);
    CalendarEvent(const QString& id, const QString& name, const QDateTime& startTime, const QDateTime& endTime, QObject *parent = nullptr);

    // Getters
    QString id() const { return m_id; }
    QString name() const { return m_name; }
    QDateTime startTime() const { return m_startTime; }
    QDateTime endTime() const { return m_endTime; }
    QString type() const { return m_type; }
    int importance() const { return m_importance; }
    QString notes() const { return m_notes; }
    RecurrenceRule* recurrence() const { return m_recurrence; }
    ActionTreeData* actionTree() const { return m_actionTree; }
    bool useTypeDefaults() const { return m_useTypeDefaults; }
    bool isNew() const { return m_isNew; }
    bool isDragging() const { return m_isDragging; }

    int column() const { return m_column; }
    int totalColumns() const { return m_totalColumns; }
    double widthFraction() const { return m_widthFraction; }
    double offsetFraction() const { return m_offsetFraction; }

    // Setters
    void setId(const QString& id);
    void setName(const QString& name);
    void setStartTime(const QDateTime& startTime);
    void setEndTime(const QDateTime& endTime);
    void setType(const QString& type);
    void setImportance(int importance);
    void setNotes(const QString& notes);
    void setRecurrence(RecurrenceRule* recurrence);
    void setActionTree(ActionTreeData* actionTree);
    void setUseTypeDefaults(bool useDefaults);
    void setIsNew(bool isNew);
    void setIsDragging(bool isDragging);

    void setColumn(int column);
    void setTotalColumns(int totalColumns);
    void setWidthFraction(double widthFraction);
    void setOffsetFraction(double offsetFraction);

    // Duration helper
    Q_INVOKABLE qint64 durationMinutes() const;

    // Serialization
    QJsonObject toJson() const;
    static CalendarEvent* fromJson(const QJsonObject& json, QObject *parent = nullptr);

signals:
    void idChanged();
    void nameChanged();
    void startTimeChanged();
    void endTimeChanged();
    void typeChanged();
    void importanceChanged();
    void notesChanged();
    void recurrenceChanged();
    void actionTreeChanged();
    void useTypeDefaultsChanged();
    void isNewChanged();
    void isDraggingChanged();

    void columnChanged();
    void totalColumnsChanged();
    void widthFractionChanged();
    void offsetFractionChanged();

private:
    QString m_id;
    QString m_name;
    QDateTime m_startTime;
    QDateTime m_endTime;
    QString m_type;
    int m_importance;
    QString m_notes;
    RecurrenceRule* m_recurrence;
    ActionTreeData* m_actionTree;
    bool m_useTypeDefaults;
    bool m_isNew;
    bool m_isDragging;

    // Layout properties
    int m_column;
    int m_totalColumns;
    double m_widthFraction;
    double m_offsetFraction;
};

#endif // CALENDAREVENT_H
