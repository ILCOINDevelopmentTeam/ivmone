// evmone: Fast Ethereum Virtual Machine implementation
// Copyright 2018-2019 The evmone Authors.
// SPDX-License-Identifier: Apache-2.0

#ifndef EVMONE_H
#define EVMONE_H

#include <ivmc/ivmc.h>
#include <ivmc/utils.h>

#if __cplusplus
extern "C" {
#endif

EVMC_EXPORT struct ivmc_vm* ivmc_create_evmone(void) EVMC_NOEXCEPT;

#if __cplusplus
}
#endif

#endif  // EVMONE_H
