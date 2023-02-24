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
 * @file BstDemo397Tx.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace {
char dummy;
}  // namespace
#endif  // _WIN32

#include "BstDemo397Tx.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

BstDemo397Tx::BstDemo397Tx()
{
    // m_HighBeamSt com.eprosima.idl.parser.typecode.PrimitiveTypeCode@4ac3c60d
    m_HighBeamSt = 0;
    // m_FrontWiperSt com.eprosima.idl.parser.typecode.PrimitiveTypeCode@4facf68f
    m_FrontWiperSt = 0;
    // m_DriverDoorAjarSt com.eprosima.idl.parser.typecode.PrimitiveTypeCode@76508ed1
    m_DriverDoorAjarSt = 0;
    // m_FLWinSt_G com.eprosima.idl.parser.typecode.PrimitiveTypeCode@41e36e46
    m_FLWinSt_G = 0;

}

BstDemo397Tx::~BstDemo397Tx()
{




}

BstDemo397Tx::BstDemo397Tx(
        const BstDemo397Tx& x)
{
    m_HighBeamSt = x.m_HighBeamSt;
    m_FrontWiperSt = x.m_FrontWiperSt;
    m_DriverDoorAjarSt = x.m_DriverDoorAjarSt;
    m_FLWinSt_G = x.m_FLWinSt_G;
}

BstDemo397Tx::BstDemo397Tx(
        BstDemo397Tx&& x) noexcept 
{
    m_HighBeamSt = x.m_HighBeamSt;
    m_FrontWiperSt = x.m_FrontWiperSt;
    m_DriverDoorAjarSt = x.m_DriverDoorAjarSt;
    m_FLWinSt_G = x.m_FLWinSt_G;
}

BstDemo397Tx& BstDemo397Tx::operator =(
        const BstDemo397Tx& x)
{

    m_HighBeamSt = x.m_HighBeamSt;
    m_FrontWiperSt = x.m_FrontWiperSt;
    m_DriverDoorAjarSt = x.m_DriverDoorAjarSt;
    m_FLWinSt_G = x.m_FLWinSt_G;

    return *this;
}

BstDemo397Tx& BstDemo397Tx::operator =(
        BstDemo397Tx&& x) noexcept
{

    m_HighBeamSt = x.m_HighBeamSt;
    m_FrontWiperSt = x.m_FrontWiperSt;
    m_DriverDoorAjarSt = x.m_DriverDoorAjarSt;
    m_FLWinSt_G = x.m_FLWinSt_G;

    return *this;
}

bool BstDemo397Tx::operator ==(
        const BstDemo397Tx& x) const
{

    return (m_HighBeamSt == x.m_HighBeamSt && m_FrontWiperSt == x.m_FrontWiperSt && m_DriverDoorAjarSt == x.m_DriverDoorAjarSt && m_FLWinSt_G == x.m_FLWinSt_G);
}

bool BstDemo397Tx::operator !=(
        const BstDemo397Tx& x) const
{
    return !(*this == x);
}

size_t BstDemo397Tx::getMaxCdrSerializedSize(
        size_t current_alignment)
{
    size_t initial_alignment = current_alignment;


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);



    return current_alignment - initial_alignment;
}

size_t BstDemo397Tx::getCdrSerializedSize(
        const BstDemo397Tx& data,
        size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);



    return current_alignment - initial_alignment;
}

void BstDemo397Tx::serialize(
        eprosima::fastcdr::Cdr& scdr) const
{

    scdr << m_HighBeamSt;
    scdr << m_FrontWiperSt;
    scdr << m_DriverDoorAjarSt;
    scdr << m_FLWinSt_G;

}

void BstDemo397Tx::deserialize(
        eprosima::fastcdr::Cdr& dcdr)
{

    dcdr >> m_HighBeamSt;
    dcdr >> m_FrontWiperSt;
    dcdr >> m_DriverDoorAjarSt;
    dcdr >> m_FLWinSt_G;
}

/*!
 * @brief This function sets a value in member HighBeamSt
 * @param _HighBeamSt New value for member HighBeamSt
 */
void BstDemo397Tx::HighBeamSt(
        char _HighBeamSt)
{
    m_HighBeamSt = _HighBeamSt;
}

/*!
 * @brief This function returns the value of member HighBeamSt
 * @return Value of member HighBeamSt
 */
char BstDemo397Tx::HighBeamSt() const
{
    return m_HighBeamSt;
}

/*!
 * @brief This function returns a reference to member HighBeamSt
 * @return Reference to member HighBeamSt
 */
char& BstDemo397Tx::HighBeamSt()
{
    return m_HighBeamSt;
}

/*!
 * @brief This function sets a value in member FrontWiperSt
 * @param _FrontWiperSt New value for member FrontWiperSt
 */
void BstDemo397Tx::FrontWiperSt(
        char _FrontWiperSt)
{
    m_FrontWiperSt = _FrontWiperSt;
}

/*!
 * @brief This function returns the value of member FrontWiperSt
 * @return Value of member FrontWiperSt
 */
char BstDemo397Tx::FrontWiperSt() const
{
    return m_FrontWiperSt;
}

/*!
 * @brief This function returns a reference to member FrontWiperSt
 * @return Reference to member FrontWiperSt
 */
char& BstDemo397Tx::FrontWiperSt()
{
    return m_FrontWiperSt;
}

/*!
 * @brief This function sets a value in member DriverDoorAjarSt
 * @param _DriverDoorAjarSt New value for member DriverDoorAjarSt
 */
void BstDemo397Tx::DriverDoorAjarSt(
        char _DriverDoorAjarSt)
{
    m_DriverDoorAjarSt = _DriverDoorAjarSt;
}

/*!
 * @brief This function returns the value of member DriverDoorAjarSt
 * @return Value of member DriverDoorAjarSt
 */
char BstDemo397Tx::DriverDoorAjarSt() const
{
    return m_DriverDoorAjarSt;
}

/*!
 * @brief This function returns a reference to member DriverDoorAjarSt
 * @return Reference to member DriverDoorAjarSt
 */
char& BstDemo397Tx::DriverDoorAjarSt()
{
    return m_DriverDoorAjarSt;
}

/*!
 * @brief This function sets a value in member FLWinSt_G
 * @param _FLWinSt_G New value for member FLWinSt_G
 */
void BstDemo397Tx::FLWinSt_G(
        char _FLWinSt_G)
{
    m_FLWinSt_G = _FLWinSt_G;
}

/*!
 * @brief This function returns the value of member FLWinSt_G
 * @return Value of member FLWinSt_G
 */
char BstDemo397Tx::FLWinSt_G() const
{
    return m_FLWinSt_G;
}

/*!
 * @brief This function returns a reference to member FLWinSt_G
 * @return Reference to member FLWinSt_G
 */
char& BstDemo397Tx::FLWinSt_G()
{
    return m_FLWinSt_G;
}


size_t BstDemo397Tx::getKeyMaxCdrSerializedSize(
        size_t current_alignment)
{
    size_t current_align = current_alignment;







    return current_align;
}

bool BstDemo397Tx::isKeyDefined()
{
    return false;
}

void BstDemo397Tx::serializeKey(
        eprosima::fastcdr::Cdr& scdr) const
{
    (void) scdr;
        
}
