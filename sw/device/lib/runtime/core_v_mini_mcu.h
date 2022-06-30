// Copyright 2022 OpenHW Group
// Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
// SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1

#ifndef COREV_MINI_MCU_H_
#define COREV_MINI_MCU_H_

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#define DEBUG_START_ADDRESS 0x10000000
#define DEBUG_SIZE 0x100000
#define DEBUG_END_ADDRESS (DEBUG_START_ADDRESS + DEBUG_SIZE)

#define PERIPHERAL_START_ADDRESS 0x20000000
#define PERIPHERAL_SIZE 0x100000
#define PERIPHERAL_END_ADDRESS (PERIPHERAL_START_ADDRESS + PERIPHERAL_SIZE)

#define EXT_SLAVE_START_ADDRESS 0x30000000
#define EXT_SLAVE_SIZE 0x1000000
#define EXT_SLAVE_END_ADDRESS (EXT_SLAVE_START_ADDRESS + EXT_SLAVE_SIZE)

#define SOC_CTRL_START_ADDRESS (PERIPHERAL_START_ADDRESS + 0x0000000)
#define SOC_CTRL_SIZE 0x0010000
#define SOC_CTRL_END_ADDRESS (SOC_CTRL_IDX_START_ADDRESS + SOC_CTRL_IDX_SIZE)

#define UART_START_ADDRESS (PERIPHERAL_START_ADDRESS + 0x0010000)
#define UART_SIZE 0x0010000
#define UART_END_ADDRESS (UART_START_ADDRESS + UART_SIZE)

#define EXT_PERIPHERAL_START_ADDRESS (PERIPHERAL_START_ADDRESS + 0x0020000)
#define EXT_PERIPHERAL_SIZE 0x0010000
#define EXT_PERIPHERAL_END_ADDRESS (EXT_PERIPHERAL_START_ADDRESS + EXT_PERIPHERAL_SIZE)

#define PLIC_START_ADDRESS (PERIPHERAL_START_ADDRESS + 0x0030000)
#define PLIC_SIZE 0x0010000
#define PLIC_END_ADDRESS (PLIC_START_ADDRESS + PLIC_SIZE)

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // COREV_MINI_MCU_H_
