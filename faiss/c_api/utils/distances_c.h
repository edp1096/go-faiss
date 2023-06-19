/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// Copyright 2004-present Facebook. All Rights Reserved.
// -*- c -*-

#ifndef FAISS_DISTANCES_C_H
#define FAISS_DISTANCES_C_H

#include <stdlib.h>

#ifdef _MSC_VER
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "../api_declarations.h"

/*********************************************************
 * Optimized distance/norm/inner prod computations
 *********************************************************/

/// Compute pairwise distances between sets of vectors
FAISS_C_API void faiss_pairwise_L2sqr(
        int64_t d,
        int64_t nq,
        const float* xq,
        int64_t nb,
        const float* xb,
        float* dis,
        int64_t ldq,
        int64_t ldb,
        int64_t ldd);

/// Compute pairwise distances between sets of vectors
/// arguments from "faiss_pairwise_L2sqr"
/// ldq equal -1 by default
/// ldb equal -1 by default
/// ldd equal -1 by default
FAISS_C_API void faiss_pairwise_L2sqr_with_defaults(
        int64_t d,
        int64_t nq,
        const float* xq,
        int64_t nb,
        const float* xb,
        float* dis);

/// compute the inner product between nx vectors x and one y
FAISS_C_API void faiss_fvec_inner_products_ny(
        float* ip, /* output inner product */
        const float* x,
        const float* y,
        size_t d,
        size_t ny);

/// compute ny square L2 distance between x and a set of contiguous y vectors
FAISS_C_API void faiss_fvec_L2sqr_ny(
        float* dis,
        const float* x,
        const float* y,
        size_t d,
        size_t ny);

/// squared norm of a vector
FAISS_C_API float faiss_fvec_norm_L2sqr(const float* x, size_t d);

/// compute the L2 norms for a set of vectors
FAISS_C_API void faiss_fvec_norms_L2(float* norms, const float* x, size_t d, size_t nx);

/// same as fvec_norms_L2, but computes squared norms
FAISS_C_API void faiss_fvec_norms_L2sqr(float* norms, const float* x, size_t d, size_t nx);

/// L2-renormalize a set of vector. Nothing done if the vector is 0-normed
FAISS_C_API void faiss_fvec_renorm_L2(size_t d, size_t nx, float* x);

/// Setter of threshold value on nx above which we switch to BLAS to compute
/// distances
FAISS_C_API void faiss_set_distance_compute_blas_threshold(int value);

/// Getter of threshold value on nx above which we switch to BLAS to compute
/// distances
FAISS_C_API int faiss_get_distance_compute_blas_threshold();

/// Setter of block sizes value for BLAS distance computations
FAISS_C_API void faiss_set_distance_compute_blas_query_bs(int value);

/// Getter of block sizes value for BLAS distance computations
FAISS_C_API int faiss_get_distance_compute_blas_query_bs();

/// Setter of block sizes value for BLAS distance computations
FAISS_C_API void faiss_set_distance_compute_blas_database_bs(int value);

/// Getter of block sizes value for BLAS distance computations
FAISS_C_API int faiss_get_distance_compute_blas_database_bs();

/// Setter of number of results we switch to a reservoir to collect results
/// rather than a heap
FAISS_C_API void faiss_set_distance_compute_min_k_reservoir(int value);

/// Getter of number of results we switch to a reservoir to collect results
/// rather than a heap
FAISS_C_API int faiss_get_distance_compute_min_k_reservoir();

#ifdef __cplusplus
}
#endif

#endif
