/** VecMem project, part of the ACTS project (R&D line)
 *
 * (c) 2021 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

#pragma once

// Local include(s).
#include "vecmem/containers/data/vector_view.hpp"

// System include(s).
#include <cstddef>

/// Perform a linear transformation using the received vectors
void linearTransform( vecmem::data::vector_view< const int > constants,
                      vecmem::data::vector_view< const int > input,
                      vecmem::data::vector_view< int > output );

/// Function incrementing the elements of the received vector using atomics
void atomicTransform( std::size_t iterations,
                      vecmem::data::vector_view< int > vec );
