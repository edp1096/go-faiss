/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// Copyright 2004-present Facebook. All Rights Reserved.
// -*- c -*-

#ifndef FAISS_AUTO_TUNE_C_H
#define FAISS_AUTO_TUNE_C_H

#include "Index_c.h"
#include "faiss_c.h"

#ifdef __cplusplus
extern "C" {
#endif

/// possible values of a parameter, sorted from least to most expensive/accurate
FAISS_DECLARE_CLASS(ParameterRange)

FAISS_DECLARE_GETTER(ParameterRange, const char*, name)

/// Getter for the values in the range. The output values are invalidated
/// upon any other modification of the range.
FAISS_C_API void faiss_ParameterRange_values(FaissParameterRange*, double**, size_t*);

/** Uses a-priori knowledge on the Faiss indexes to extract tunable parameters.
 */
FAISS_DECLARE_CLASS(ParameterSpace)

FAISS_DECLARE_DESTRUCTOR(ParameterSpace)

/// Parameter space default constructor
FAISS_C_API int faiss_ParameterSpace_new(FaissParameterSpace** space);

/// nb of combinations, = product of values sizes
FAISS_C_API size_t faiss_ParameterSpace_n_combinations(const FaissParameterSpace*);

/// get string representation of the combination
/// by writing it to the given character buffer.
/// A buffer size of 1000 ensures that the full name is collected.
FAISS_C_API int faiss_ParameterSpace_combination_name(
        const FaissParameterSpace*,
        size_t,
        char*,
        size_t);

/// set a combination of parameters described by a string
FAISS_C_API int faiss_ParameterSpace_set_index_parameters(
        const FaissParameterSpace*,
        FaissIndex*,
        const char*);

/// set a combination of parameters on an index
FAISS_C_API int faiss_ParameterSpace_set_index_parameters_cno(
        const FaissParameterSpace*,
        FaissIndex*,
        size_t);

/// set one of the parameters
FAISS_C_API int faiss_ParameterSpace_set_index_parameter(
        const FaissParameterSpace*,
        FaissIndex*,
        const char*,
        double);

/// print a description on stdout
FAISS_C_API void faiss_ParameterSpace_display(const FaissParameterSpace*);

/// add a new parameter (or return it if it exists)
FAISS_C_API int faiss_ParameterSpace_add_range(
        FaissParameterSpace*,
        const char*,
        FaissParameterRange**);

#ifdef __cplusplus
}
#endif

#endif
