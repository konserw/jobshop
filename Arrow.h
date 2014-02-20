/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>

QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
QT_END_NAMESPACE

/*!
 * \brief Klasa rysująca strzałkę
 */
class Arrow : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 1 };
    virtual int type() const
        { return Type; }

    /*! Default Constructor.
     *
     * Creates an empty arrow object with start and end point to be set.
     * \param parent Pointer to GraphicsItem that owns newly constructed arrow.
     */
    explicit Arrow(QGraphicsItem *parent = 0);
    /*! Konstruktor parametryczny.
     *
     * Tworzy statyczny graficzny obiekt strzałki o podanych parametrach.
     * \param startPoint Punkt zaczepienia strzałki.
     * \param endPoint Punkt końca grotu strzałki.
     * \param parent Wskaźnika na rodzica do którego ma zostać dodana strzałka.
     */
    Arrow(const QPointF& startPoint, const QPointF& endPoint, QGraphicsItem *parent = 0);

    ///Zwraca prostokąt wewnątrz którego odbywa się rysowanie.
    virtual QRectF boundingRect() const;
    ///Zwraca kształt rysowanego obiektu.
    virtual QPainterPath shape() const;

    QPointF startPoint() const;
    void setStartPoint(const QPointF &startPoint);

    QPointF endPoint() const;
    void setEndPoint(const QPointF &endPoint);

protected:
    ///Metoda rysująca graficzą reprezentację obiektu.
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    ///Punkt początkowy strzałki
    QPointF m_startPoint;
    ///Punkt końcowy strzałki - grot
    QPointF m_endPoint;
    ///Wielokąt grotu strzałki
    QPolygonF arrowHead;
};

#endif
