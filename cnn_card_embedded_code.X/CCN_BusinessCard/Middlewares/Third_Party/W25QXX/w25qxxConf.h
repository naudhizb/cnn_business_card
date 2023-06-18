#ifndef _W25QXXCONFIG_H
#define _W25QXXCONFIG_H


/*
 * +----------+        +-----------+
 * |Page(256B)+-+      |Sector(4KB)+-+
 * +-+--------+ | ---> +-+---------+ |
 *   |       x16|        |        x8 |
 *   +----------+        +-----------+
 *
 *                            |
 *                            v
 * +----------+        +-----------+
 * |Chip(4 MB)+-+      |Block(32KB)+-+
 * +-+--------+ | <--- +-+---------+ |
 *   |          |        |       x256|
 *   +----------+        +-----------+
 */

#define _W25QXX_SPI                   hspi1
#define _W25QXX_CS_GPIO               FLASH_CS_GPIO_Port
#define _W25QXX_CS_PIN                FLASH_CS_Pin
#define _W25QXX_USE_FREERTOS          0
#define _W25QXX_ROUTINE_IRQ			  1
#define _W25QXX_DEBUG                 0
#define _W25QXX_USE_DMA 	      0

extern SPI_HandleTypeDef _W25QXX_SPI;
#endif
