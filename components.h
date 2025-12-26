#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <stdint.h>
#include <stddef.h>

// Simulated Flash Sizes (e.g., 32MB)
#define FLASH_SIZE 0x2000000

// Project Name Offset (Simulated location in Flash)
// In a real system, this would be at a specific address in the image
#define PROJECT_NAME_OFFSET 0x1000
#define PROJECT_NAME_MAX_LEN 32

// Return Codes
typedef enum {
    PFR_STATUS_PASS = 0,
    PFR_STATUS_FAIL = 1
} PFR_Status;

// Mocks for SPI Flash (PCH / BMC)
typedef struct {
    uint8_t *memory;
    size_t size;
    char name[32]; // "PCH_SPI" or "BMC_SPI"
} SPI_Flash;

// FPGA Internal State (NVRAM)
typedef struct {
    char expected_project_name[PROJECT_NAME_MAX_LEN];
} FPGA_Config;

#endif // COMPONENTS_H
