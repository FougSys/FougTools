/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#include "scoped_connection.h"

#include <QtCore/QObject>

namespace qtcore {

/*!
 * \class ScopedConnect
 * \brief Establishes a signal/slot connection between two QObjects and automatically breaks it
 *        upon destruction
 *
 * \headerfile scoped_connection.h <qttools/core/scoped_connection.h>
 * \ingroup qttools_core
 *
 *
 *  ScopedConnect guarantees that a signal/slot connection will get broken when the current scope
 *  dissapears
 */

ScopedConnect::ScopedConnect(const QObject* sender, const char* signal,
                             const QObject* receiver, const char* slot,
                             Qt::ConnectionType type)
    : m_sender(sender),
      m_receiver(receiver),
      m_signal(signal),
      m_slot(slot)
{
    QObject::connect(sender, signal, receiver, slot, type);
}

ScopedConnect::~ScopedConnect()
{
    QObject::disconnect(m_sender, m_signal, m_receiver, m_slot);
}

/*!
 * \class ScopedDisonnect
 * \brief Breaks a signal/slot connection between two QObjects and automatically re-establishes it
 *        upon destruction
 *
 * \headerfile scoped_connection.h <qttools/core/scoped_connection.h>
 * \ingroup qttools_core
 *
 *  ScopedDisonnect guarantees that a signal/slot connection will get restored when the current
 *  scope dissapears
 */

ScopedDisconnect::ScopedDisconnect(const QObject* sender, const char* signal,
                                   const QObject* receiver, const char* slot,
                                   Qt::ConnectionType type)
    : m_sender(sender),
      m_receiver(receiver),
      m_signal(signal),
      m_slot(slot),
      m_type(type)
{
    QObject::disconnect(sender, signal, receiver, slot);
}

ScopedDisconnect::~ScopedDisconnect()
{
    QObject::connect(m_sender, m_signal, m_receiver, m_slot, m_type);
}

} // namespace qtcore
