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
 * @file BstDemo397Rx.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _FAST_DDS_GENERATED_BSTDEMO397RX_H_
#define _FAST_DDS_GENERATED_BSTDEMO397RX_H_


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
#if defined(BstDemo397Rx_SOURCE)
#define BstDemo397Rx_DllAPI __declspec( dllexport )
#else
#define BstDemo397Rx_DllAPI __declspec( dllimport )
#endif // BstDemo397Rx_SOURCE
#else
#define BstDemo397Rx_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define BstDemo397Rx_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
} // namespace fastcdr
} // namespace eprosima


/*!
 * @brief This class represents the structure BstDemo397Rx defined by the user in the IDL file.
 * @ingroup BSTDEMO397RX
 */
class BstDemo397Rx
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport BstDemo397Rx();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~BstDemo397Rx();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object BstDemo397Rx that will be copied.
     */
    eProsima_user_DllExport BstDemo397Rx(
            const BstDemo397Rx& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object BstDemo397Rx that will be copied.
     */
    eProsima_user_DllExport BstDemo397Rx(
            BstDemo397Rx&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object BstDemo397Rx that will be copied.
     */
    eProsima_user_DllExport BstDemo397Rx& operator =(
            const BstDemo397Rx& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object BstDemo397Rx that will be copied.
     */
    eProsima_user_DllExport BstDemo397Rx& operator =(
            BstDemo397Rx&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x BstDemo397Rx object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const BstDemo397Rx& x) const;

    /*!
     * @brief Comparison operator.
     * @param x BstDemo397Rx object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const BstDemo397Rx& x) const;

    /*!
     * @brief This function sets a value in member HighBeamReq
     * @param _HighBeamReq New value for member HighBeamReq
     */
    eProsima_user_DllExport void HighBeamReq(
            char _HighBeamReq);

    /*!
     * @brief This function returns the value of member HighBeamReq
     * @return Value of member HighBeamReq
     */
    eProsima_user_DllExport char HighBeamReq() const;

    /*!
     * @brief This function returns a reference to member HighBeamReq
     * @return Reference to member HighBeamReq
     */
    eProsima_user_DllExport char& HighBeamReq();

    /*!
     * @brief This function sets a value in member WiperRequ
     * @param _WiperRequ New value for member WiperRequ
     */
    eProsima_user_DllExport void WiperRequ(
            char _WiperRequ);

    /*!
     * @brief This function returns the value of member WiperRequ
     * @return Value of member WiperRequ
     */
    eProsima_user_DllExport char WiperRequ() const;

    /*!
     * @brief This function returns a reference to member WiperRequ
     * @return Reference to member WiperRequ
     */
    eProsima_user_DllExport char& WiperRequ();

    /*!
     * @brief This function sets a value in member DoorsLockReq
     * @param _DoorsLockReq New value for member DoorsLockReq
     */
    eProsima_user_DllExport void DoorsLockReq(
            char _DoorsLockReq);

    /*!
     * @brief This function returns the value of member DoorsLockReq
     * @return Value of member DoorsLockReq
     */
    eProsima_user_DllExport char DoorsLockReq() const;

    /*!
     * @brief This function returns a reference to member DoorsLockReq
     * @return Reference to member DoorsLockReq
     */
    eProsima_user_DllExport char& DoorsLockReq();

    /*!
     * @brief This function sets a value in member FLDMControl
     * @param _FLDMControl New value for member FLDMControl
     */
    eProsima_user_DllExport void FLDMControl(
            char _FLDMControl);

    /*!
     * @brief This function returns the value of member FLDMControl
     * @return Value of member FLDMControl
     */
    eProsima_user_DllExport char FLDMControl() const;

    /*!
     * @brief This function returns a reference to member FLDMControl
     * @return Reference to member FLDMControl
     */
    eProsima_user_DllExport char& FLDMControl();


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
            const BstDemo397Rx& data,
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

    char m_HighBeamReq;
    char m_WiperRequ;
    char m_DoorsLockReq;
    char m_FLDMControl;
};

#endif // _FAST_DDS_GENERATED_BSTDEMO397RX_H_