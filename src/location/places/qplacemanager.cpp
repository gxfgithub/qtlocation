/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qplacemanager.h"
#include "qplacemanager_p.h"
#include "qplacemanagerengine.h"

/*!
    \class QPlaceManager

    \brief The QPlaceManager class is responsible for the discovery and
    management of places.

    \inmodule QtLocation

    \ingroup places-main
*/

/*!
    \enum QPlaceManager::ConnectivityMode

    Defines the method of obtaining place data
    \value NoConnectivity There is no place data.
    \value OfflineMode The places data will come from an offline source.
    \value OnlineMode The place data will come from an online source.
    \value HybridMode The place data will come from a combination of offline and online sources.
*/

/*!
    \enum QPlaceManager::SearchVisibilityScope
    Defines the scope for searching places according to visibility.
    \value PublicSearch Searches will only be conducted on public places.
    \value PrivateSearch Searches will only be conducted on private places.
    \value PublicAndPrivateSearch Searches will be conducted on both public and private places
*/

/*!
    \enum QPlaceManager::ManagerFeature
    Defines the possible features that the place manager can possible.
    \value ImportFeature The manager supports import operations
    \value ExportFeature The manager supports export operations
    \value CheckInFeature The manaager supports check-in operations
    \value PostRatingFeature The manager supports posting ratings for places
    \value SuggestionFeature The manager supports the providing of suggestions
    \value ReportPlaceFeature The manager supports reporting a place if it is incorrect/inappropriate.
    \value AuthenticationFeature The manager supports authentication of a user.
    \value CreatePlaceFeature The manager supports the creation of places.
    \value UpdatePlaceFeature The manager supports the updating of places.
*/

/*!
    Constructs a new manager with the specified \a pareent and with the
    implementation provided by \a engine.

    This constructor is used internally by QGeoServiceProviderFactory. Regular
    users should acquire instances of QGeoRoutingManager with
    QGeoServiceProvider::routingManager();
*/
QPlaceManager::QPlaceManager(QPlaceManagerEngine *engine, QObject *parent)
    : QObject(parent), d(new QPlaceManagerPrivate)
{
    d->engine = engine;
    if (d->engine) {
        d->engine->setParent(this);

        connect(d->engine, SIGNAL(finished(QPlaceReply*)), this, SIGNAL(finished(QPlaceReply*)));
        connect(d->engine, SIGNAL(error(QPlaceReply*,QPlaceReply::Error)),
                this, SIGNAL(error(QPlaceReply*,QPlaceReply::Error)));
        connect(d->engine,SIGNAL(authenticationRequired(QAuthenticator*)),
                this, SIGNAL(authenticationRequired(QAuthenticator*)));
    } else {
        qFatal("The place manager engine that was set for this place manager was NULL.");
    }
}

/*!
    Destroys the manager.
*/
QPlaceManager::~QPlaceManager()
{
    delete d;
}

/*!
    Returns the name of the manager
*/
QString QPlaceManager::managerName() const
{
    return d->engine->managerName();
}

/*!
    Retrieves a details of place with \a place id.
*/
QPlaceDetailsReply *QPlaceManager::getPlaceDetails(const QString &placeId) const
{
    return d->engine->getPlaceDetails(placeId);
}

/*!
    Retrieves content from a given \a place according to thes parameters specified in
    \a request.
*/
QPlaceContentReply *QPlaceManager::getContent(const QGeoPlace &place, const QPlaceContentRequest &request) const
{
    return d->engine->getContent(place, request);
}

/*!
    Posts a \a rating to a \a place.
*/
QPlaceReply* QPlaceManager::postRating(const QString &placeId, qreal rating)
{
    return d->engine->postRating(placeId, rating);
}

/*!
    Searches for places according to a given \a request.
*/
QPlaceSearchReply *QPlaceManager::searchForPlaces(const QPlaceSearchRequest &request) const
{
    return d->engine->searchForPlaces(request);
}

/*!
    Provides recommendation based on a given \a request.
*/
QPlaceSearchReply *QPlaceManager::recommendations(const QGeoPlace &place, const QPlaceSearchRequest &request) const
{
    return d->engine->recommendations(place, request);
}

/*!
    Requests a set of text predictions for a given \a request
*/
QPlaceTextPredictionReply *QPlaceManager::textPredictions(const QPlaceSearchRequest &request) const
{
    return d->engine->textPredictions(request);
}

/*!
    Returns the connectivity mode of the manager.
*/
QPlaceManager::ConnectivityModes QPlaceManager::connectivityMode() const
{
    return d->engine->connectivityMode();
}

/*!
    Sets the connectivity \a mode of the manager.
*/
void QPlaceManager::setConnectivityMode(QPlaceManager::ConnectivityModes mode)
{
    d->engine->setConnectivityMode(mode);
}

/*!
    Returns the list of connectivity modes that the manager supports.
*/
QPlaceManager::ConnectivityModes QPlaceManager::supportedConnectivityModes() const
{
    return d->engine->supportedConnectivityModes();
}

/*!
    Saves a \a place at the given \a scope.
*/
QPlaceIdReply *QPlaceManager::savePlace(const QGeoPlace &place, VisibilityScope scope)
{
    return d->engine->savePlace(place, scope);
}

/*!
    Removes a \a place from the manager
*/
QPlaceReply *QPlaceManager::removePlace(const QGeoPlace &place)
{
    return d->engine->removePlace(place);
}

/*
    Returns the available scopes in which places can be saved.
*/
QPlaceManager::VisibilityScopes QPlaceManager::supportedSaveVisibilityScopes()
{
    return d->engine->supportedSaveVisibilityScopes();
}

/*!
    Initializes the manager categories.
*/
QPlaceReply *QPlaceManager::initializeCategories()
{
    return d->engine->initializeCategories();
}

/*!
    Returns a list of top level categories if \a parent is default contstructed; otherwise returns
    a list of subcategories of \a parent.
*/
QList<QPlaceCategory> QPlaceManager::categories(const QPlaceCategory &parent) const
{
    return d->engine->categories(parent);
}

/*!
    Returns a list of names of available managers that
    can be used to instantiate manager instances.
*/
QStringList QPlaceManager::availableManagers() {
    return QPlaceManagerPrivate::factories().keys();
}

/*!
    Returns the locale of the manager.
    The locale is used as a hint to determine
    what language place details should be returned in.
*/
QLocale QPlaceManager::locale() const
{
    return d->engine->locale();
}

/*!
    Sets the locale of the manager.
*/
void QPlaceManager::setLocale(const QLocale &locale)
{
    d->engine->setLocale(locale);
}

/*!
\fn void QPlaceManager::finished(QPlaceReply* reply)

This signal is emitted when \a reply has finished processing.

If reply->error() equals QPlaceReply::NoError then the processing
finished successfully.

This signal and QPlaceReply::finished() will be emitted at the same time.

\note Do no delete the \a reply object in the slot connected to this signal.
Use deleteLater() instead.
*/

/*!
\fn void QPlaceManager::error(QPlaceReply* reply, QPlaceReply::Error error, const QString &errorString)

This signal is emitted when an error has been detected in the processing of
\a reply.  The QPlaceManager::finished() signal will probably follow.

The error will be described by the error code \a error.  If \a errorString is
not empty it will contain a textual description of the error meant for developers
and not end users.

This signal and QPlaceReply::error() will be emitted at the same time.

\note Do no delete the \a reply object in the slot connected to this signal.
Use deleteLater() instead.
*/

/*!
    \fn void QPlaceManager::authenticationRequired(QAuthenticator *authenticator)

    This signal is emitted if authentication details are required by the manager
    to peform certain operations.  If the authentication was successful, the next time
    the operations are performed, the same credentials are used and the
    authenticationRequired signal is not emitted again.

    If authentication is unsuccessful, the manager will emit the signal again.
*/
