#include "flash_sim.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void flash_init(SPI_Flash *flash, const char *name, const char *project_name) {
    strncpy(flash->name, name, sizeof(flash->name) - 1);
    flash->size = FLASH_SIZE;
    flash->memory = (uint8_t *)malloc(flash->size);
    if (!flash->memory) {
        fprintf(stderr, "Failed to allocate memory for %s\n", name);
        exit(1);
    }
    // Clear memory
    memset(flash->memory, 0xFF, flash->size);

    // Write Project Name at the specific offset
    // In real life, this would be part of the firmware image checking process
    if (project_name) {
        strncpy((char *)(flash->memory + PROJECT_NAME_OFFSET), project_name, PROJECT_NAME_MAX_LEN);
    }
}

void flash_free(SPI_Flash *flash) {
    if (flash->memory) {
        free(flash->memory);
        flash->memory = NULL;
    }
}

int spi_read(SPI_Flash *flash, uint32_t address, uint8_t *buffer, size_t length) {
    if (address + length > flash->size) {
        printf("[SPI_ERR] Read out of bounds on %s\n", flash->name);
        return -1;
    }
    memcpy(buffer, flash->memory + address, length);
    return 0;
}
