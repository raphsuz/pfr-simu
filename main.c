#include <stdio.h>
#include "components.h"
#include "flash_sim.h"
#include "fpga_pfr.h"

void run_test_scenario(const char *test_name, const char *golden_project, const char *pch_project, const char *bmc_project) {
    printf("========================================\n");
    printf("TEST SCENARIO: %s\n", test_name);
    printf("========================================\n");

    // Initialize Components
    SPI_Flash pch_flash;
    flash_init(&pch_flash, "PCH_SPI", pch_project);

    SPI_Flash bmc_flash;
    flash_init(&bmc_flash, "BMC_SPI", bmc_project);

    FPGA_Config fpga;
    pfr_init(&fpga, golden_project);

    // Run Check
    PFR_Status status = pfr_check_firmware(&fpga, &pch_flash, &bmc_flash);

    if (status == PFR_STATUS_PASS) {
        printf("RESULT: PASS\n");
    } else {
        printf("RESULT: FAIL\n");
    }
    printf("\n");

    // Cleanup
    flash_free(&pch_flash);
    flash_free(&bmc_flash);
}

int main() {
    printf("PFR Firmware Image Checking Simulation\n\n");

    // Scenario 1: All Match (Success)
    run_test_scenario("Scenario 1: Normal Operation (Match)", "ProjectX", "ProjectX", "ProjectX");

    // Scenario 2: BMC Mismatch
    run_test_scenario("Scenario 2: BMC Tampered (Mismatch)", "ProjectX", "ProjectX", "ProjectY");

    // Scenario 3: BIOS (PCH) Mismatch
    run_test_scenario("Scenario 3: BIOS Tampered (Mismatch)", "ProjectX", "ProjectZ", "ProjectX");

    return 0;
}
