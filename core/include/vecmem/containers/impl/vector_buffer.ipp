/** VecMem project, part of the ACTS project (R&D line)
 *
 * (c) 2021 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */
#pragma once

// System include(s).
#include <cassert>

namespace {

   /// Function creating the smart pointer for @c vecmem::data::vector_buffer
   template< typename TYPE >
   std::unique_ptr< char, vecmem::details::deallocator >
   allocate_buffer_memory(
      typename vecmem::data::vector_buffer< TYPE >::size_type capacity,
      typename vecmem::data::vector_buffer< TYPE >::size_type size,
      vecmem::memory_resource& resource ) {

      // A sanity check.
      assert( capacity >= size );

      // Decide how many bytes to allocate.
      const std::size_t byteSize =
         ( ( capacity == size ) ? ( capacity * sizeof( TYPE ) ) :
           ( sizeof( std::size_t ) + capacity * sizeof( TYPE ) ) );

      // Return the appropriate smart pointer.
      return { capacity == 0 ? nullptr :
               static_cast< char* >( resource.allocate( byteSize ) ),
               { byteSize, resource } };
   }

} // private namespace

namespace vecmem { namespace data {

   template< typename TYPE >
   vector_buffer< TYPE >::
   vector_buffer( size_type size, memory_resource& resource )
   : vector_buffer( size, size, resource ) {

   }

   template< typename TYPE >
   vector_buffer< TYPE >::
   vector_buffer( size_type capacity, size_type size,
                  memory_resource& resource )
   : base_type( capacity, nullptr, nullptr ),
     m_memory( ::allocate_buffer_memory< TYPE >( capacity, size, resource ) ) {

      // Set the base class's pointers correctly.
      if( capacity > 0 ) {
         if( size == capacity ) {
            base_type::m_ptr = reinterpret_cast< pointer >( m_memory.get() );
         } else {
            base_type::m_size =
               reinterpret_cast< size_pointer >( m_memory.get() );
            *( base_type::m_size ) = size;
            base_type::m_ptr =
               reinterpret_cast< pointer >( m_memory.get() +
                                            sizeof( size_type ) );
         }
      }
   }

} // namespace data

   template< typename TYPE >
   data::vector_view< TYPE >&
   get_data( data::vector_buffer< TYPE >& data ) {

      return data;
   }

   template< typename TYPE >
   const data::vector_view< TYPE >&
   get_data( const data::vector_buffer< TYPE >& data ) {

      return data;
   }

} // namespace vecmem
