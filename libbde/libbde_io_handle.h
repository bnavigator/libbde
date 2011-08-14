/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2011, Joachim Metz <jbmetz@users.sourceforge.net>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBBDE_IO_HANDLE_H )
#define _LIBBDE_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libbde_array_type.h"
#include "libbde_encryption.h"
#include "libbde_libbfio.h"
#include "libbde_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint8_t *bde_signature;

typedef struct libbde_io_handle libbde_io_handle_t;

struct libbde_io_handle
{
	/* The current (storage media) offset
	 */
	off64_t current_offset;

	/* The format version
	 */
	int version;

	/* The bytes per sector
	 */
	uint16_t bytes_per_sector;

	/* The first metadata offset
	 */
	off64_t first_metadata_offset;

	/* The second metadata offset
	 */
	off64_t second_metadata_offset;

	/* The third metadata offset
	 */
	off64_t third_metadata_offset;

	union
	{
		/* The MFT mirror cluster block number
		 * Used by Windows Vista (version 1)
		 */
		uint64_t mft_mirror_cluster_block_number;

		/* The volume header offset
		 * Used by Windows 7 (version 2)
		 */
		off64_t volume_header_offset;
	};

	/* The encryption context
	 */
	libbde_encryption_context_t *encryption_context;

	/* The (binary) recovery password
	 */
	uint8_t recovery_password[ 16 ];

	/* Value to indicate the recovery password is set
	 */
	uint8_t recovery_password_is_set;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libbde_io_handle_initialize(
     libbde_io_handle_t **io_handle,
     liberror_error_t **error );

int libbde_io_handle_free(
     libbde_io_handle_t **io_handle,
     liberror_error_t **error );

int libbde_io_handle_read_volume_header(
     libbde_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     liberror_error_t **error );

int libbde_io_handle_read_sector(
     intptr_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfdata_cache_t *cache,
     int element_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint8_t read_flags,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif
