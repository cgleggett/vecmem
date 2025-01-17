/** VecMem project, part of the ACTS project (R&D line)
 *
 * (c) 2021 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */
#pragma once

namespace vecmem::hip::details {

   /// Helper function for determining the "currently active device"
   int get_device();

} // namespace vecmem::hip::details
