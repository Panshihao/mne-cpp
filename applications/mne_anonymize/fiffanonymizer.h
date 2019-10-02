//=============================================================================================================
/**
* @file     fiffanonymizer.h
* @author   Juan Garcia-Prieto <Juan.GarciaPrieto@uth.tmc.edu> <juangpc@gmail.com>;
*           Wayne Mead <wayne.mead@uth.tmc.edu> <wayne.isk@gmail.com>;
*           Lorenz Esch <Lorenz.Esch@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>;
*           John C. Mosher <John.C.Mosher@uth.tmc.edu> <jcmosher@gmail.com>;
* @version  1.0
* @date     August, 2019
*
* @section  LICENSE
*
* Copyright (C) 2019, Juan Garcia-Prieto and Matti Hamalainen. All rights reserved.
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
* @brief     fiffanonymizer class declaration.
*
*/

#ifndef FIFFANONYMIZER_H
#define FIFFANONYMIZER_H


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include <fiff/fiff_stream.h>
#include <fiff/fiff_tag.h>
#include <fiff/fiff_types.h>


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QSharedPointer>
#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QStack>
#include <QDateTime>
#include <QDebug>
#include <QPointer>


//*************************************************************************************************************
//=============================================================================================================
// Eigen INCLUDES
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE
//=============================================================================================================

namespace MNEANONYMIZE
{


//=============================================================================================================
/**
* Description of what this class is intended to do (in detail).
*
* @brief FiffAnonymizer class declaration.
*/

class FiffAnonymizer
{
public:
    typedef QSharedPointer<FiffAnonymizer> SPtr;            /**< Shared pointer type for FiffAnonymizer. */
    typedef QSharedPointer<const FiffAnonymizer> ConstSPtr; /**< Const shared pointer type for FiffAnonymizer. */

    //=========================================================================================================
    /**
     * Constructs a FiffAnonymizer object.
     */
    FiffAnonymizer();

    //=========================================================================================================
    /**
    * Copy constructor for FiffAnonymizer object.
    * @param [in] A FiffAnonyzer object.
    */
    FiffAnonymizer(const FiffAnonymizer& obj);

    //=========================================================================================================
    /**
    * Move contructor
    * @param [in] a FiffAnonymizer object.
    */
    FiffAnonymizer(FiffAnonymizer &&obj);

    //=========================================================================================================
    /**
    * Calls the anonymizer routine.
    * @details This method is the main method in the class. It goes through the input file and tag by tag
    *   analyses if there might be some relevant information to anonymize and eventually does so.
    *   Finally the method would test if the input file should be deleted or renamed according to the
    *   flags set up during the object setup.
    */
    int anonymizeFile();

    //=========================================================================================================
    // PUBLIC INTERFACE
    /**
    * Specifies the input file to anonymize. This file will help to set a input Fiffstream object.
    * @param [in] String containing the input file name including its path.
    */
    void setFileIn(const QString &sFilePathIn);

    //=========================================================================================================
    /**
    * Specifies the output file to anonymize. This file will help to set a output Fiffstream object.
    * @param [in] String containing the output file name including its path.
    */
    void setFileOut(const QString &sFilePathOut);

    //=========================================================================================================
    /**
    * Sets the state of the FiffAnonymizer object's desired verbose mode. If set to TRUE, different messages will be
    * printed on screen during the anonymizing process. If set to false only a single line confirmation message will be
    * printed on each execution.
    * @param [in] Bool argument. [Default=FALSE]
    */
    void setVerboseMode(bool v);

    //=========================================================================================================
    /**
    * Retrieves the state of the FiffAnonyzer object's desired verbose mode.
    */
    bool getVerboseMode();

    //=========================================================================================================
    /**
    * Sets the state of the object the desired verbose mode to none. If set to TRUE, absolutely no message will be printed
    * to on screen during the anonymizing process.
    * @param [in] Bool argument.
    */
    void setQuietMode(bool q);

    /**
    * Sets the state of the FiffAnonymizer object's desired anonymization mode. If set to TRUE, apart from the default information
    * additional information will also be anonymized, like Subject's weight, height, or different project information.
    * printed on screen during the anonymizing process. [Default=FALSE].
    * @param [in] Bool argument.
    */
    void setBruteMode(bool b);

    //=========================================================================================================
    /**
    * If found in the fiff file, the measurement date information will be overwritten in the file in order to match the date specified with this function.
    * @param [in] String containing the desired measurement date.
    */
    void setMeasurementDay(QString d);

    //=========================================================================================================
    /**
    * If found in the fiff file, the specified number of days will be subtracted from the measurement date information contained in each fif file.
    * @param [in] Integer with the number of dates to subtract from the measurement date.
    */
    void setMeasurementDayOffset(int d);

    //=========================================================================================================
    /**
    * If found in the fiff file, subject's birthday information will be overwritten in the file in order to match the date specified with this function.
    * @param [in] String containing the desired measurement date.
    */
    void setSubjectBirthday(QString d);

    //=========================================================================================================
    /**
    * If found in the fiff file, the specified number of days will be subtracted from the subject's birthday date information contained in each fif file.
    * @param [in] Integer with the number of dates to subtract from the subject's birthday date.
    */
    void setSubjectBirthdayOffset(int d);

    //=========================================================================================================
    /**
    * Sets fiffanonymizer to delete the input file after anonymization finishes. This is intended to avoid duplication of disk space usage.
    * If set to true, by its own, a confirmation message will be prompted to the user. Used with the --delete_input_file_after option.
    * It can be used with the option "avoid_delete_confirmation" so that no confirmation is prompt to the user.
    * @param [in] Bool argument. [Default=FALSE]
    */
    void setDeleteInputFileAfter(bool d);

    //=========================================================================================================
    /**
    * Method to avoid the need to prompt the user for confirmation of deletion of the input file after anonymization has finished.
    * As the deletion flag has to manually be set to true and this confirmation flag has to manually be set to false, the chances of
    * a user disadvertently deleted a relevant input file are (hopefully) minimized.
    * @param [in] Bool argument. [Default=TRUE]
    */
    void setDeleteInputFileAfterConfirmation(bool dc);

    //=========================================================================================================
    /**
    * Specifies a flag so that the user can specifiy the value of the subject's id tag. If found in the fiff file, the value
    * will be changed to match the one specified with this method.
    * @param [in] Integer with the subject's id.
    */
    void setSubjectHisId(int id);

    //PUBLIC MEMBERS. note "const" type qualifier. Left public for convenience.
    const double version;               /**< Version of this FiffAnonymizer application --> mne_fiffanonymize application will be based on it*/
    const double maxValidFiffVerion;    /**< Maximum version of the Fiff file standard compatible with this application.*/
    const QString versionStr;           /**< version translated to a string.*/
    const QString name;                 /**< Name of this application. Typically MNE_ANONYMIZE.*/
    const QString description;          /**< Application description*/

private:

    //=========================================================================================================
    /**
    * Updates a stack (m_pBlockTyeList points to it) with the type of block the input stream is in.
    * While reading an input file as a data stream, we will read tag by tag. Each tag can be inside a specific
    * block, as defined in Fiff file standard docs. FIFF_COMMENT tag (#206) will need to be censored/anonymized
    * only if it is contained inside a block of type "measurement info". Thus, we need to keep track of which
    * are we in, while reading. We do this by checking the first element in this stack (see censorTag() in case
    * FIFF_COMMENT.
    * This is a refactoring method, designed to make anonymizeFile() more readable.
    * @param [in] pointer to the tag being read. Normally the input Tag.
    */
    void updateBlockTypeList(FIFFLIB::FiffTag::SPtr pTag);

    //=========================================================================================================
    /**
    * Acquisition sw stamps in the fiff file the version of the fiff standard used to code the fiff file. This
    * anonymizer class has been developed according to a specific fiff version of this standard. If in the future,
    * this standard were to change, it should be noted through this method.
    * @param [in] pointer to the tag being read. Normally, the input Tag.
    */
    bool checkValidFiffFormatVersion(FIFFLIB::FiffTag::SPtr pTag);

    //=========================================================================================================
    /**
    * For a specific input tag, check if that tag belongs to a set of tags where relevant information should be
    * censored/anonymized. If so, perform such anonymization while copying the new tag into an output Tag.
    * This is the core method of the class where the actual anonymization takes place.
    * @param [in] pointer to the input tag being read from the input file.
    * @param [in] pointer to the output tag being written to the output file.
    */
    int censorTag(FIFFLIB::FiffTag::SPtr pInTag,FIFFLIB::FiffTag::SPtr pOutTag);

    //=========================================================================================================
    /**
    * Fiff standard defines a Tag Directory where a reference to all the tags in a file is stored. This directory
    * itself a tag which is stored (usually) at the end of the file. The tag directory stores the memory address
    * of every tag in the file (as an offset from the beging of the file). Thus, when altering the size of
    * anonymized tags, it has to be reworked. The fiff standard does not mandate to have this directory but it
    * seems convinient to build it. We do this on-the-fly, while reading each tag. And store all the info for the
    * directory inside m_pOutDir vector.
    * @param [in] pointer to the tag being read. Normally the input tag.
    * @param [in] actual file position of the input file (relative to the begining of the file).
    */
    void addEntryToDir(FIFFLIB::FiffTag::SPtr pTag,qint64 filePos);

    //=========================================================================================================
    /**
    * After finishing reading all the tags in the input file, we can add the final entry to the tag directory. This
    * is a set of four -1 integer values which will mark the end of the tag directory.
    */
    void addFinalEntryToDir();

    //=========================================================================================================
    /**
    * This method allows to transform between a vector and a regular tag structure. The vector will only contain
    * the data inside the Tag Directory tag (remember a tag directory is a tag itself). This allows to use all the
    * methods related to a tag (i.e. writeTag) while storing a newly updated tag directory into a fiff file.
    * @param [in] a pointer to a tag where the tag directory information can be stored.
    */
    void dir2tag(FIFFLIB::FiffTag::SPtr pTag);

    //=========================================================================================================
    /**
    * This stores the vector containing the tag directory. This vector was populated on-line while going through
    * the anonymizeFile method. Once the reading is finished the data needs to be saved in the output file.
    * @param [in] output file stream
    * @param [in] position in the file where the data can be written. (optional).
    */
    void writeDirectory(FIFFLIB::FiffStream* stream, FIFFLIB::fiff_long_t pos=-1);

    //=========================================================================================================
    /**
    * This function allows go through a the directory vector (m_pOutDir) and locate the position of any tag
    * containing a pointer. Since the position of the pointer will have probably been updated, we can no go back
    * and mend it.
    * Fiff file format defines a set of pointers to addresses in the fiff file. These are defined as integer
    * offset bytes since the begining of the file. As off fiff version 1.3 these pointers can be i. pointer to
    * the tag directory, ii. pointer to free space in the file (free block list). iii. nil pointer at the end of
    * the file (this one really contains no address info (duh!).
    * @param [in] output stream
    * @param [in] tag kind code to search for
    * @param [in] new position to store in the data field of the pointer tag.
    */
    void updatePointer(FIFFLIB::FiffStream* stream, FIFFLIB::fiff_int_t tagKind, FIFFLIB::fiff_long_t newPos);

    //=========================================================================================================
    /**
    * Helper function that prints messages to the command line only if the object has been set to a verbose mode.
    * This wraps QDebug functionality inline. Specified here in header file. If the obj is not set to be in a
    * verbose mode, it does nothing. Messages can be printed to a single line (followed by an eol character) or
    * can be printed in the same line as previous one. Note that to achieve this, messages will be "retained" one
    * call, in order to check if next call requests to print in the same line.
    * @param [in] String to print.
    * @param [in] bool value to indicate if the message should be printed to the same line as the previous message.
    */
    void printIfVerbose(const QString str,bool sameLine=false);

    //=========================================================================================================
    /**
    * If the user wants the name of the input file and the output file to be the same, well... it is not possible
    * in this universe other than masking this behaviour with an auxiliary output filename to be used during the
    * anonymizing process. Eventually, once the reading has finished correctly, the input file can be deleted and
    * the output file can then be called as the original input file. This function helps with this process.
    */
    QString generateRandomFileName();

    //=========================================================================================================
    /**
    * The user might request throught the flag "--delete_input_file_after" to have the input file deleted. If the
    * necessary control measures allow for it, then this function will delete the input file and set the control
    * member bool variable m_bInputFileDeleted to true.
    */
    void deleteInputFile();

    //=========================================================================================================
    /**
    * This function checks if the user has requested to have the input file deleted and if the deletion has been
    * confirmed by the user througha  command line prompt. This command line promt can be bypassed through the
    * m_bDeleteInputFileConfirmation flag, which is accessed through the setDeleteInputFileAfterConfirmation public
    * method.
    */
    bool checkDeleteInputFile();

    //=========================================================================================================
    /**
    * This method is responsible to perform a complete check to see if the output filename should be changed.
    * If the outpuf file has a random name, because the user requested this name to be equal to the input filename.
    * And if the output filename has already been deleted, then it should return a true value. If the input file
    * has not been deleted, this method will prompt the user to delete it. The user might still answer no to this
    * confirmation.
    */
    bool checkRenameOutputFile();

    //=========================================================================================================
    /**
    * This method will rename the output file as the input file. It will be called only after all the necessary
    * verification steps have been tested through the checkRenameOutputFile method.
    * It sets the control member bool flag m_bOutputFileRenamed to true and if verbose mode is on, prints a
    * description message.
    */
    void renameOutputFileAsInputFile();

    bool m_bVerboseMode;                /**< Describes the verbosity mode of the object */
    bool m_bBruteMode;                  /**< Describes the level of anonymization to perform */
    bool m_bQuietMode;                  /**< Describes if the user wants no message to be printed to the command line */
    bool m_bDeleteInputFileAfter;       /**< Describes users request to delete the input file after anonymization */
    bool m_bDeleteInputFileConfirmation;/**< Describes users request to avoid confirmation prompt for input file deletion*/
    bool m_bInputFileDeleted;           /**< Describes if the input file has been deleted */
    bool m_bInOutFileNamesEqual;        /**< Describes users request to have both input and output files with the same name*/
    bool m_bOutputFileRenamed;          /**< Describes if the output file has been renamed to match the name the input file had */

    QString m_sDfltString;              /**< Default string to be used as substitution of other strings in a fiff file */
    QDateTime m_dateDfltDate;           /**< Default date to be used as substitution of dates found in a fiff file */

    QDateTime m_dateMeasurmentDate;     /**< Specific date requested by the user to be used as substitution of the meas. Initialized with m_dateDfltDate, modifiable through api */
    bool m_bUseMeasurementDayOffset;    /**< Describes users request to modify meas date by subtracting a specific number of days (defined in m_iMeasurementDateOffset)*/
    int  m_iMeasurementDayOffset;       /**< The number of days to subtract from the meas. date if the user requests so */

    QDateTime m_dateSubjectBirthday;    /**< */
    bool m_bUseSubjectBirthdayOffset;   /**< */
    int  m_iSubjectBirthdayOffset;      /**< */

    QByteArray m_BDfltMAC;              /**< */

    int m_iDfltSubjectId;               /**< */
    QString m_sDfltSubjectFirstName;    /**< */
    QString m_sDfltSubjectMidName;      /**< */
    QString m_sDfltSubjectLastName;     /**< */
    int m_iDfltSubjectWeight;           /**< */
    int m_iDfltSubjectHeight;           /**< */
    QString m_sDfltSubjectComment;      /**< */
    int m_iDfltSubjectHisId;            /**< */

    int m_iDfltProjectId;               /**< */
    QString m_sDfltProjectName;         /**< */
    QString m_sDfltProjectAim;          /**< */
    QString m_sDfltProjectPersons;      /**< */
    QString m_sDfltProjectComment;      /**< */

    QString m_sFileNameIn;              /**< */
    QString m_sFileNameOut;             /**< */

    QFile m_fFileIn;                    /**< */
    QFile m_fFileOut;                   /**< */

    QDebug m_printInSameLineHelper;     /**< */
    const bool m_bPrintInSameLine;      /**< */

    QSharedPointer<QStack<int32_t> > m_pBlockTypeList;  /**< */
    QSharedPointer<QVector<FIFFLIB::FiffDirEntry> > m_pOutDir; /**< */

};



//*************************************************************************************************************
//=============================================================================================================
// INLINE DEFINITIONS
//=============================================================================================================

//=========================================================================================================

inline void FiffAnonymizer::printIfVerbose(const QString str, bool sameLine)
{
    if(m_bVerboseMode)
    {
        QDebug * dbg;
        if(!sameLine)
        {
            m_printInSameLineHelper = qDebug();
        }
        dbg = &m_printInSameLineHelper;
        *dbg << str;
    }
}

}

#endif // MNEANONYMIZE