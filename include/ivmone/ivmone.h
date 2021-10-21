// ivmone: Fast Ethereum Virtual Machine implementation
// Copyright 2018-2019 The ivmone Authors.
// SPDX-License-Identifier: Apache-2.0

#ifndef IVMONE_H
#define IVMONE_H

#include <ivmc/ivmc.h>
#include <ivmc/utils.h>

#if __cplusplus
extern "C" {
#endif

IVMC_EXPORT struct ivmc_vm* ivmc_create_ivmone(void) IVMC_NOEXCEPT;

#if __cplusplus
}
#endif

#endif  // IVMONE_H
