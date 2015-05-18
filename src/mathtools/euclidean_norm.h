/****************************************************************************
**
**  FougTools
**  Copyright Fougue (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language, the Qt and Open Cascade toolkits.
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

#ifndef MATHTOOLS_EUCLIDEAN_NORM_H
#define MATHTOOLS_EUCLIDEAN_NORM_H

#include "sqr_euclidean_norm.h"
#include <cmath>

namespace math {
namespace internal {

struct EuclideanFunc
{
  template<typename COORD_ITERATOR>
  static auto fromRange(COORD_ITERATOR begin, COORD_ITERATOR end) -> decltype(typeHelper(*begin))
  { return std::sqrt(SqrEuclideanFunc::fromRange(begin, end)); }

  template<std::size_t N, typename COORD_TYPE>
  static typename NumTraits<COORD_TYPE>::Real fromPtr(const COORD_TYPE* coordPtr)
  { return std::sqrt(SqrEuclideanFunc::fromPtr<N, COORD_TYPE>(coordPtr)); }
};

template<> struct NormTraits<internal::EuclideanFunc>
{
  typedef ArityNormSpecializationTag NormCategory;
};

} // namespace internal

/*! \brief Provides computation of the
 *         <a href="http://en.wikipedia.org/wiki/Norm_%28mathematics%29#Euclidean_norm">
 *         euclidean norm</a>
 *
 *  \headerfile euclidean_norm.h <mathtools/euclidean_norm.h>
 *  \ingroup mathtools
 */
typedef Norm<math::internal::EuclideanFunc> EuclideanNorm;

} // namespace math

#endif // MATHTOOLS_EUCLIDEAN_NORM_H
