#ifndef QPLACECATEGORY_H
#define QPLACECATEGORY_H

#include <QSharedDataPointer>
#include <QString>
#include <QVariant>
#include <QList>
#include "qplaceglobal.h"
#include "qplacealternativevalue.h"

namespace QT_PLACES_NAMESPACE {

class QPlaceManagerEngine;

class QPlaceCategoryPrivate;
class Q_PLACES_EXPORT QPlaceCategory
{
public:
    QPlaceCategory();
    QPlaceCategory(const QPlaceCategory &other);

    virtual ~QPlaceCategory();

    QPlaceCategory &operator=(const QPlaceCategory &other);

    bool operator==(const QPlaceCategory &other) const;
    bool operator!=(const QPlaceCategory &other) const {
        return !(other == *this);
    }

    QList<QPlaceAlternativeValue> alternativeNames() const;
    void setAlternativeNames(const QList<QPlaceAlternativeValue> &names);
    QString categoryId() const;
    void setCategoryId(const QString &catID);
    QString categorySystemId() const;
    void setCategorySystemId(const QString &catID);
    QString description() const;
    void setDescription(const QString &description);
    QString name() const;
    void setName(const QString &name);

    bool isEmpty() const;
private:
    QSharedDataPointer<QPlaceCategoryPrivate> d;
};

} // QT_PLACES_NAMESPACE

#endif // QPLACECATEGORY_H
