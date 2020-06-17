//=============================================================================================================
/**
 * @file     averaging.h
 * @author   Gabriel Motta <gbmotta@mgh.harvard.edu>
 * @since    0.1.3
 * @date     May, 2020
 *
 * @section  LICENSE
 *
 * Copyright (C) 2020, Gabriel Motta. All rights reserved.
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
 * @brief    Contains the declaration of the averaging class.
 *
 */

#ifndef AVERAGING_H
#define AVERAGING_H

//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "averaging_global.h"

#include <anShared/Interfaces/IPlugin.h>

//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QtWidgets>
#include <QtCore/QtPlugin>

//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

namespace ANSHAREDLIB {
    class FiffRawViewModel;
    class AbstractModel;
    class Communicator;
}

namespace DISPLIB {
    class AveragingSettingsView;
    class ChannelSelectionView;
    class AverageLayoutView;
    class ChannelInfoModel;
    class EvokedSetModel;
    class ButterflyView;
}

namespace FIFFLIB {
    class FiffEvokedSet;
    class FiffEvoked;
    class FiffInfo;
}

//=============================================================================================================
// DEFINE NAMESPACE AVERAGINGPLUGIN
//=============================================================================================================

namespace AVERAGINGPLUGIN
{

//=============================================================================================================
// AVERAGINGPLUGIN FORWARD DECLARATIONS
//=============================================================================================================

//=============================================================================================================
/**
 * Averaging Plugin
 *
 * @brief The averaging class provides a plugin for computing averages.
 */
class AVERAGINGSHARED_EXPORT Averaging : public ANSHAREDLIB::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ansharedlib/1.0" FILE "averaging.json") //New Qt5 Plugin system replaces Q_EXPORT_PLUGIN2 macro
    // Use the Q_INTERFACES() macro to tell Qt's meta-object system about the interfaces
    Q_INTERFACES(ANSHAREDLIB::IPlugin)

public:
    //=========================================================================================================
    /**
     * Constructs an Averaging object.
     */
    Averaging();

    //=========================================================================================================
    /**
     * Destroys the Averaging object.
     */
    ~Averaging() override;

    // IPlugin functions
    virtual QSharedPointer<IPlugin> clone() const override;
    virtual void init() override;
    virtual void unload() override;
    virtual QString getName() const override;

    virtual QMenu* getMenu() override;
    virtual QDockWidget* getControl() override;
    virtual QWidget* getView() override;

    virtual void handleEvent(QSharedPointer<ANSHAREDLIB::Event> e) override;
    virtual QVector<ANSHAREDLIB::EVENT_TYPE> getEventSubscriptions() const override;

private:
    //=========================================================================================================
    /**
     * Loads new Fiff model whan current loaded model is changed
     *
     * @param [in,out] pNewModel    pointer to currently loaded FiffRawView Model
     */
    void onModelChanged(QSharedPointer<ANSHAREDLIB::AbstractModel> pNewModel);

    //=========================================================================================================
    /**
     * Change the number of averages
     *
     * @param[in] numAve     new number of averages
     */
    void onChangeNumAverages(qint32 numAve);

    //=========================================================================================================
    /**
     * Change the baseline from value
     *
     * @param[in] fromMSeconds     the new baseline from value in milliseconds
     */
    void onChangeBaselineFrom(qint32 fromMSeconds);

    //=========================================================================================================
    /**
     * Change the baseline to value
     *
     * @param[in] fromMSeconds     the new baseline to value in milliseconds
     */
    void onChangeBaselineTo(qint32 toMSeconds);

    //=========================================================================================================
    /**
     * Change the pre stim stim
     *
     * @param[in] mseconds     the new pres stim in milliseconds
     */
    void onChangePreStim(qint32 mseconds);

    //=========================================================================================================
    /**
     * Change the post stim stim
     *
     * @param[in] mseconds     the new post stim in milliseconds
     */
    void onChangePostStim(qint32 mseconds);

    //=========================================================================================================
    /**
     * Change the baseline active state
     *
     * @param[in] state     the new state
     */
    void onChangeBaselineActive(bool state);

    //=========================================================================================================
    /**
     * Reset the averaging plugin and delete all currently stored data
     *
     * @param[in] state     the new state
     */
    void onResetAverage(bool state);

    //=========================================================================================================
    /**
     * Gets called when compute button on GUI is clicked
     *
     * @param [in] bChecked     UNUSED - state of the button
     */
    void onComputeButtonClicked(bool bChecked);

    //=========================================================================================================
    /**
     * Computes average and updates butterfly and 2D layout views
     */
    void computeAverage();

    //=========================================================================================================
    /**
     * Saves state of 'use averaging / use stim' checkboxes based on gui
     */
    void onCheckBoxStateChanged();

//    //=========================================================================================================
//    /**
//     * Change the stim channel
//     *
//     * @param[in] sStimCh     the new stim channel name
//     */
//    void onChangeStimChannel(const QString &sStimCh);

    //=========================================================================================================
    /**
     * Toggles dropping rejected when computing average
     */
    void onRejectionChecked(bool bState);

    //=========================================================================================================
    /**
     * Toggles display of Channel Selection widget GUI
     */
    void onChannelButtonClicked();

    //=========================================================================================================
    /**
     *  Loads averging GUI components that are dependent on FiffRawModel to be initialized
     */
    void loadFullGui();

    //=========================================================================================================
    /**
     * Clears saved averaging data
     */
    void clearAveraging();

    //=========================================================================================================
    /**
     * Call this slot whenever you want to make a screenshot of the butterfly or layout view.
     *
     * @param[out] imageType     The current iamge type: png, svg.
     */
    void onMakeScreenshot(const QString& imageType);

    QSharedPointer<ANSHAREDLIB::FiffRawViewModel>           m_pFiffRawModel;            /**< Pointer to currently loaded FiffRawView Model */
    QSharedPointer<QList<QPair<int,double>>>                m_pTriggerList;             /**< Pointer to list of stim triggers */
    QSharedPointer<FIFFLIB::FiffEvoked>                     m_pFiffEvoked;              /**< Pointer to object to store averaging data */
    QSharedPointer<FIFFLIB::FiffEvokedSet>                  m_pFiffEvokedSet;           /**< Pointer to object that can store m_pFiffEvoked and be added to a model */
    QSharedPointer<DISPLIB::EvokedSetModel>                 m_pEvokedModel;             /**< Pointer to model used to display averaging data from m_pFiffEvokedSet and m_pFiffEvoked */
    QSharedPointer<DISPLIB::ChannelSelectionView>           m_pChannelSelectionView;    /**< Pointer to Channel selection GUI */
    QSharedPointer<DISPLIB::ChannelInfoModel>               m_pChannelInfoModel;        /**< Pointer to model that holds channel info data */
    QSharedPointer<FIFFLIB::FiffInfo>                       m_pFiffInfo;                /**< Pointer to info about loaded fiff data */

    QPointer<ANSHAREDLIB::Communicator>                     m_pCommu;                   /**< To broadcst signals */
    QPointer<DISPLIB::ButterflyView>                        m_pButterflyView;           /**< The butterfly plot view. */
    QPointer<DISPLIB::AverageLayoutView>                    m_pAverageLayoutView;       /**< The average layout plot view */

    DISPLIB::AveragingSettingsView*                         m_pAveragingSettingsView;   /**< Pointer to averaging settings GUI */

    float                                                   m_fBaselineFrom;            /**< Baseline start - in seconds relative to stim(0) - can be negative*/
    float                                                   m_fBaselineTo;              /**< Baseline end - in seconds relative to stim(0) - can be negative*/
    float                                                   m_fPreStim;                 /**< Time before stim - in seconds - stored as positive number (>0) */
    float                                                   m_fPostStim;                /**< Time after stim - in seconds - stored as positive number (>0) */
    float                                                   m_fTriggerThreshold;        /**< Threshold to count stim channel events */

    QVBoxLayout*                                            m_pLayout;                  /**< Pointer to layout that holds parameter GUI tab elements */
    QTabWidget*                                             m_pTabView;                 /**< Pointer to object that stores multiple tabs of GUI items */

    bool                                                    m_bUseAnn;                  /**< Whether to use annotations to compute average. Currently always set to true (1) */
    bool                                                    m_bBasline;                 /**< Whether to apply baseline correction */
    bool                                                    m_bRejection;               /**< Whether to drop data points marked fro rejection when calculating average */
    bool                                                    m_bLoaded;                  /**< Whether the full GUI has already been laoaded */

    QRadioButton*                                           m_pAnnCheck;                /**< Radio Buttons to control m_bUseAnn. True (1) if this is checked. */
    QRadioButton*                                           m_pStimCheck;               /**< Radio Buttons to control m_bUseAnn. False (0) if this is checked. */

};

} // NAMESPACE

#endif // AVERAGING_H