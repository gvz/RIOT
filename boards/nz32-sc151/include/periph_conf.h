/*
 * Copyright (C) 2016 Fundacion Inria Chile
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     nz32-sc151
 * @{
 *
 * @file
 * @brief       Peripheral MCU configuration for the limifrog-v1 board
 *
 * @author      Francisco Molina <francisco.molina@inria.cl>
 */

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include "periph_cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Clock system configuration
 * @{
 **/
#define CLOCK_HSI           (16000000U)         /* internal oscillator */
#define CLOCK_CORECLOCK     (32000000U)         /* desired core clock frequency */

/* configuration of PLL prescaler and multiply values */
/* CORECLOCK := HSI / CLOCK_PLL_DIV * CLOCK_PLL_MUL */
#define CLOCK_PLL_DIV       RCC_CFGR_PLLDIV2
#define CLOCK_PLL_MUL       RCC_CFGR_PLLMUL4
/* configuration of peripheral bus clock prescalers */
#define CLOCK_AHB_DIV       RCC_CFGR_HPRE_DIV1      /* AHB clock -> 32MHz */
#define CLOCK_APB2_DIV      RCC_CFGR_PPRE2_DIV1     /* APB2 clock -> 32MHz */
#define CLOCK_APB1_DIV      RCC_CFGR_PPRE1_DIV1     /* APB1 clock -> 32MHz */
/* configuration of flash access cycles */
#define CLOCK_FLASH_LATENCY FLASH_ACR_LATENCY

/* bus clocks for simplified peripheral initialization, UPDATE MANUALLY! */
#define CLOCK_AHB           (CLOCK_CORECLOCK / 1)
#define CLOCK_APB1          (CLOCK_CORECLOCK / 1)
#define CLOCK_APB2          (CLOCK_CORECLOCK / 1)
/** @} */

/**
 * @name    Timer configuration
 * @{
 */
static const timer_conf_t timer_config[] = {
    {
        .dev      = TIM5,
        .max      = 0xffffffff,
        .rcc_mask = RCC_APB1ENR_TIM5EN,
        .bus      = APB1,
        .irqn     = TIM5_IRQn
    }
};

#define TIMER_0_ISR         (isr_tim5)

#define TIMER_NUMOF         (sizeof(timer_config) / sizeof(timer_config[0]))
/** @} */

/**
 * @name    UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {
        .dev      = USART3,
        .rcc_mask = RCC_APB1ENR_USART3EN,
        .rx_pin   = GPIO_PIN(PORT_B, 11),
        .tx_pin   = GPIO_PIN(PORT_B, 10),
        .rx_af    = GPIO_AF7,
        .tx_af    = GPIO_AF7,
        .bus      = APB1,
        .irqn     = USART3_IRQn
    },
    {
        .dev      = USART2,
        .rcc_mask = RCC_APB1ENR_USART2EN,
        .rx_pin   = GPIO_PIN(PORT_A, 3),
        .tx_pin   = GPIO_PIN(PORT_A, 2),
        .rx_af    = GPIO_AF7,
        .tx_af    = GPIO_AF7,
        .bus      = APB1,
        .irqn     = USART2_IRQn
    },
    {
        .dev      = USART1,
        .rcc_mask = RCC_APB2ENR_USART1EN,
        .rx_pin   = GPIO_PIN(PORT_A, 10),
        .tx_pin   = GPIO_PIN(PORT_A, 9),
        .rx_af    = GPIO_AF7,
        .tx_af    = GPIO_AF7,
        .bus      = APB2,
        .irqn     = USART1_IRQn
    }
};

#define UART_0_ISR          (isr_usart3)
#define UART_1_ISR          (isr_usart2)
#define UART_2_ISR          (isr_usart1)

#define UART_NUMOF          (sizeof(uart_config) / sizeof(uart_config[0]))
/** @} */

/**
 * @name    PWM configuration
 * @{
 */
static const pwm_conf_t pwm_config[] = {
    {
        .dev      = TIM3,
        .rcc_mask = RCC_APB1ENR_TIM3EN,
        .chan     = { { .pin = GPIO_PIN(PORT_C, 6), .cc_chan = 0 },
                      { .pin = GPIO_PIN(PORT_C, 7), .cc_chan = 1 },
                      { .pin = GPIO_PIN(PORT_C, 8), .cc_chan = 2 },
                      { .pin = GPIO_PIN(PORT_C, 9), .cc_chan = 3 } },
        .af       = GPIO_AF2,
        .bus      = APB1
    }
};

#define PWM_NUMOF           (sizeof(pwm_config) / sizeof(pwm_config[0]))
/** @} */

/**
 * @name    SPI configuration
 *
 * @note    The spi_divtable is auto-generated from
 *          `cpu/stm32_common/dist/spi_divtable/spi_divtable.c`
 * @{
 */
static const uint8_t spi_divtable[2][5] = {
    {       /* for APB1 @ 32000000Hz */
        7,  /* -> 125000Hz */
        5,  /* -> 500000Hz */
        4,  /* -> 1000000Hz */
        2,  /* -> 4000000Hz */
        1   /* -> 8000000Hz */
    },
    {       /* for APB2 @ 32000000Hz */
        7,  /* -> 125000Hz */
        5,  /* -> 500000Hz */
        4,  /* -> 1000000Hz */
        2,  /* -> 4000000Hz */
        1   /* -> 8000000Hz */
    }
};

static const spi_conf_t spi_config[] = {
    {
        .dev      = SPI1,
        .mosi_pin = GPIO_PIN(PORT_B, 5),
        .miso_pin = GPIO_PIN(PORT_B, 4),
        .sclk_pin = GPIO_PIN(PORT_B, 3),
        .cs_pin   = GPIO_UNDEF,
        .af       = GPIO_AF5,
        .rccmask  = RCC_APB2ENR_SPI1EN,
        .apbbus   = APB2
    },
    {
        .dev      = SPI2,
        .mosi_pin = GPIO_PIN(PORT_B, 15),
        .miso_pin = GPIO_PIN(PORT_B, 14),
        .sclk_pin = GPIO_PIN(PORT_B, 13),
        .cs_pin   = GPIO_UNDEF,
        .af       = GPIO_AF5,
        .rccmask  = RCC_APB1ENR_SPI2EN,
        .apbbus   = APB1
    },
    {
        .dev      = SPI3,
        .mosi_pin = GPIO_PIN(PORT_C, 12),
        .miso_pin = GPIO_PIN(PORT_C, 11),
        .sclk_pin = GPIO_PIN(PORT_C, 10),
        .cs_pin   = GPIO_UNDEF,
        .af       = GPIO_AF6,
        .rccmask  = RCC_APB1ENR_SPI3EN,
        .apbbus   = APB1
    }
};

#define SPI_NUMOF           (sizeof(spi_config) / sizeof(spi_config[0]))
/** @} */

/**
 * @name    I2C configuration
  * @{
 */
#define I2C_NUMOF           (1)
#define I2C_0_EN            1
#define I2C_IRQ_PRIO        1
#define I2C_APBCLK          (36000000U)  /* Configurable from 2MHz to 50Mhz, steps of 2Mhz */

/* I2C 0 device configuration */
#define I2C_0_EVT_ISR       isr_i2c1_ev
#define I2C_0_ERR_ISR       isr_i2c1_er

static const i2c_conf_t i2c_config[] = {
    /* device, port, scl-, sda-pin-number, I2C-AF, ER-IRQn, EV-IRQn */
    {I2C1, GPIO_PIN(PORT_B,  8), GPIO_PIN(PORT_B,  9),
     GPIO_OD_PU, GPIO_AF4, I2C1_ER_IRQn, I2C1_EV_IRQn}
};
/** @} */

/**
 * @name    RTC configuration
 * @{
 */
#define RTC_NUMOF           (1U)
/** @} */

/**
 * @name    ADC configuration
 * @{
 */
#define ADC_CONFIG {              \
    { GPIO_PIN(PORT_C, 0), 10 },  \
    { GPIO_PIN(PORT_C, 1), 11 },  \
    { GPIO_PIN(PORT_C, 2), 12 },  \
    /* ADC Temperature channel */ \
    { GPIO_UNDEF,          16 },  \
    /* ADC VREF channel */        \
    { GPIO_UNDEF,          17 },  \
}

#define ADC_NUMOF           (5)
/** @} */

/**
 * @name   DAC configuration
 * @{
 */
static const dac_conf_t dac_config[] = {
    { .pin = GPIO_PIN(PORT_A,  4), .chan = 0 },
    { .pin = GPIO_PIN(PORT_A,  5), .chan = 1 }
};

#define DAC_NUMOF           (sizeof(dac_config) / sizeof(dac_config[0]))
/** @} */


#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
