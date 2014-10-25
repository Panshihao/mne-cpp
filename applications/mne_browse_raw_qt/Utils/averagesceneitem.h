//=============================================================================================================
/**
* @file     averagesceneitem.h
* @author   Lorenz Esch <lorenz.esch@tu-ilmenau.de>;
*           Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>;
* @version  1.0
* @date     October, 2014
*
* @section  LICENSE
*
* Copyright (C) 2014, Lorenz Esch, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    Contains the declaration of the AverageSceneItem class.
*
*/

#ifndef AVERAGESCENEITEM_H
#define AVERAGESCENEITEM_H

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include <iostream>
#include <Eigen/Core>


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QGraphicsItem>
#include <QString>
#include <QColor>
#include <QPainter>
#include <QStaticText>
#include <QDebug>


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace Eigen;


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE MNEBrowseRawQt
//=============================================================================================================

namespace MNEBrowseRawQt
{


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================


//=============================================================================================================
/**
* AverageSceneItem...
*
* @brief The AverageSceneItem class provides a new data structure for visualizing averages in a 2D layout.
*/
class AverageSceneItem : public QGraphicsItem
{

public:
    //=========================================================================================================
    /**
    * Constructs a AverageSceneItem.
    */
    AverageSceneItem(QString channelName, int channelNumber, QPointF channelPosition, QColor defaultColors = Qt::red);

    //=========================================================================================================
    /**
    * Returns the bounding rect of the electrode item. This rect describes the area which the item uses to plot in.
    */
    QRectF boundingRect() const;

    //=========================================================================================================
    /**
    * Reimplemented paint function.
    */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QString             m_sChannelName;             /**< Holds the channel name.*/
    int                 m_iChannelNumber;           /**< Holds the channel number.*/
    QPointF             m_qpChannelPosition;        /**< Holds the channels 2D position in the scene.*/
    QList<QColor>       m_cAverageColors;           /**< Holds the current average color.*/
    QList<VectorXd>     m_lAverageData;             /**< Holds the channels average data which is to be plotted.*/
    QPair<int,int>      m_firstLastSample;          /**< Hold the first and last sample.*/

protected:
    //=========================================================================================================
    /**
    * Create a plot path and paint the average data
    *
    * @param [in] painter The painter used to plot in this item.
    */
    void paintAveragePath(QPainter *painter);
};

} // NAMESPACE MNEBrowseRawQt

#endif // AVERAGESCENEITEM_H
