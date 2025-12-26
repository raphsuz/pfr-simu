#ifndef FLASH_SIM_H
#define FLASH_SIM_H

#include "components.h"

// Initialize a flash device with a specific project name at the correct offset
void flash_init(SPI_Flash *flash, const char *name, const char *project_name);

// Free resources
void flash_free(SPI_Flash *flash);

// Simulate reading from SPI Flash
// Returns 0 on success, -1 on failure (out of bounds)
int spi_read(SPI_Flash *flash, uint32_t address, uint8_t *buffer, size_t length);

#endif // FLASH_SIM_H
