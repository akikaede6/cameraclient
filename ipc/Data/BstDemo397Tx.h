// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file BstDemo397Tx.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _FAST_DDS_GENERATED_BSTDEMO397TX_H_
#define _FAST_DDS_GENERATED_BSTDEMO397TX_H_


#include <fastrtps/utils/fixed_size_string.hpp>

#include <stdint.h>
#include <array>
#include <string>
#include <vector>
#include <map>
#include <bitset>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define eProsima_user_DllExport
#endif  // _WIN32

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(BstDemo397Tx_SOURCE)
#define BstDemo397Tx_DllAPI __declspec( dllexport )
#else
#define BstDemo397Tx_DllAPI __declspec( dllimport )
#endif // BstDemo397Tx_SOURCE
#else
#define BstDemo397Tx_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define BstDemo397Tx_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
} // namespace fastcdr
} // namespace eprosima


/*!
 * @brief This class represents the structure BstDemo397Tx defined by the user in the IDL file.
 * @ingroup BSTDEMO397TX
 */
class BstDemo397Tx
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport BstDemo397Tx();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~BstDemo397Tx();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object BstDemo397Tx that will be copied.
     */
    eProsima_user_DllExport BstDemo397Tx(
            const BstDemo397Tx& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object BstDemo397Tx that will be copied.
     */
    eProsima_user_DllExport BstDemo397Tx(
            BstDemo397Tx&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object BstDemo397Tx that will be copied.
     */
    eProsima_user_DllExport BstDemo397Tx& operator =(
            const BstDemo397Tx& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object BstDemo397Tx that will be copied.
     */
    eProsima_user_DllExport BstDemo397Tx& operator =(
            BstDemo397Tx&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x BstDemo397Tx object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const BstDemo397Tx& x) const;

    /*!
     * @brief Comparison operator.
     * @param x BstDemo397Tx object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const BstDemo397Tx& x) const;

    /*!
     * @brief This function sets a value in member HighBeamSt
     * @param _HighBeamSt New value for member HighBeamSt
     */
    eProsima_user_DllExport void HighBeamSt(
            char _HighBeamSt);

    /*!
     * @brief This function returns the value of member HighBeamSt
     * @return Value of member HighBeamSt
     */
    eProsima_user_DllExport char HighBeamSt() const;

    /*!
     * @brief This function returns a reference to member HighBeamSt
     * @return Reference to member HighBeamSt
     */
    eProsima_user_DllExport char& HighBeamSt();

    /*!
     * @brief This function sets a value in member FrontWiperSt
     * @param _FrontWiperSt New value for member FrontWiperSt
     */
    eProsima_user_DllExport void FrontWiperSt(
            char _FrontWiperSt);

    /*!
     * @brief This function returns the value of member FrontWiperSt
     * @return Value of member FrontWiperSt
     */
    eProsima_user_DllExport char FrontWiperSt() const;

    /*!
     * @brief This function returns a reference to member FrontWiperSt
     * @return Reference to member FrontWiperSt
     */
    eProsima_user_DllExport char& FrontWiperSt();

    /*!
     * @brief This function sets a value in member DriverDoorAjarSt
     * @param _DriverDoorAjarSt New value for member DriverDoorAjarSt
     */
    eProsima_user_DllExport void DriverDoorAjarSt(
            char _DriverDoorAjarSt);

    /*!
     * @brief This function returns the value of member DriverDoorAjarSt
     * @return Value of member DriverDoorAjarSt
     */
    eProsima_user_DllExport char DriverDoorAjarSt() const;

    /*!
     * @brief This function returns a reference to member DriverDoorAjarSt
     * @return Reference to member DriverDoorAjarSt
     */
    eProsima_user_DllExport char& DriverDoorAjarSt();

    /*!
     * @brief This function sets a value in member FLWinSt_G
     * @param _FLWinSt_G New value for member FLWinSt_G
     */
    eProsima_user_DllExport void FLWinSt_G(
            char _FLWinSt_G);

    /*!
     * @brief This function returns the value of member FLWinSt_G
     * @return Value of member FLWinSt_G
     */
    eProsima_user_DllExport char FLWinSt_G() const;

    /*!
     * @brief This function returns a reference to member FLWinSt_G
     * @return Reference to member FLWinSt_G
     */
    eProsima_user_DllExport char& FLWinSt_G();


    /*!
     * @brief This function returns the maximum serialized size of an object
     * depending on the buffer alignment.
     * @param current_alignment Buffer alignment.
     * @return Maximum serialized size.
     */
    eProsima_user_DllExport static size_t getMaxCdrSerializedSize(
            size_t current_alignment = 0);

    /*!
     * @brief This function returns the serialized size of a data depending on the buffer alignment.
     * @param data Data which is calculated its serialized size.
     * @param current_alignment Buffer alignment.
     * @return Serialized size.
     */
    eProsima_user_DllExport static size_t getCdrSerializedSize(
            const BstDemo397Tx& data,
            size_t current_alignment = 0);


    /*!
     * @brief This function serializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serialize(
            eprosima::fastcdr::Cdr& cdr) const;

    /*!
     * @brief This function deserializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void deserialize(
            eprosima::fastcdr::Cdr& cdr);



    /*!
     * @brief This function returns the maximum serialized size of the Key of an object
     * depending on the buffer alignment.
     * @param current_alignment Buffer alignment.
     * @return Maximum serialized size.
     */
    eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(
            size_t current_alignment = 0);

    /*!
     * @brief This function tells you if the Key has been defined for this type
     */
    eProsima_user_DllExport static bool isKeyDefined();

    /*!
     * @brief This function serializes the key members of an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serializeKey(
            eprosima::fastcdr::Cdr& cdr) const;

private:

    char m_HighBeamSt;
    char m_FrontWiperSt;
    char m_DriverDoorAjarSt;
    char m_FLWinSt_G;
};

#endif // _FAST_DDS_GENERATED_BSTDEMO397TX_H_