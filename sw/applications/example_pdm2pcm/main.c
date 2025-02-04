/*
 * Copyright 2022 EPFL
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Pierre Guillod <pierre.guillod@epfl.ch>, EPFL, STI-SEL
 */

#include <stdio.h>
#include <stdlib.h>

#include "core_v_mini_mcu.h"
#include "pdm2pcm_regs.h"

#include "mmio.h"

#include "groundtruth.h"

int main(int argc, char *argv[])
{
    printf("PDM2PCM DEMO\n");
    printf(" > Start\n");

    mmio_region_t pdm2pcm_base_addr = mmio_region_from_addr((uintptr_t)PDM2PCM_START_ADDRESS);

    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_CLKDIVIDX_REG_OFFSET ,15);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_REACHCOUNT_REG_OFFSET, 1);
    
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_DECIMCIC_REG_OFFSET, 15);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_DECIMHB1_REG_OFFSET, 31);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_DECIMHB2_REG_OFFSET, 63);
    
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB1COEF00_REG_OFFSET , 32768);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB1COEF01_REG_OFFSET , 19618);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB1COEF02_REG_OFFSET ,-3899);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB1COEF03_REG_OFFSET , 684);
    
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF00_REG_OFFSET , 32768);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF01_REG_OFFSET , 20716);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF02_REG_OFFSET ,-6529);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF03_REG_OFFSET , 3492);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF04_REG_OFFSET ,-2081);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF05_REG_OFFSET , 1250);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF06_REG_OFFSET ,-1013);

//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF00_REG_OFFSET , 60609);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF01_REG_OFFSET , 4854);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF02_REG_OFFSET ,-4640);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF03_REG_OFFSET , 4303);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF04_REG_OFFSET ,-3864);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF05_REG_OFFSET , 3353);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF06_REG_OFFSET ,-2805);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF07_REG_OFFSET , 2253);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF08_REG_OFFSET ,-1726);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF09_REG_OFFSET , 1252);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF10_REG_OFFSET ,-852);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF11_REG_OFFSET , 548);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF12_REG_OFFSET ,-385);
//    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF13_REG_OFFSET ,-178);

    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB1COEF00_REG_OFFSET, 1);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB1COEF01_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB1COEF02_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB1COEF03_REG_OFFSET, 0);

    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF00_REG_OFFSET, 1);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF01_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF02_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF03_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF04_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF05_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_HB2COEF06_REG_OFFSET, 0);

    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF00_REG_OFFSET, 1);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF01_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF02_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF03_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF04_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF05_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF06_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF07_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF08_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF09_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF10_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF11_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF12_REG_OFFSET, 0);
    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_FIRCOEF13_REG_OFFSET, 0);

    mmio_region_write32(pdm2pcm_base_addr, PDM2PCM_CONTROL_REG_OFFSET  , 1);

    int const COUNT = 5;

    int count = 0;
    int finish = 0;
    int fed = 0;
   
    while(finish == 0) {
        uint32_t status = mmio_region_read32(pdm2pcm_base_addr, PDM2PCM_STATUS_REG_OFFSET);
        if (!(status & 1)) {
            int32_t read = mmio_region_read32(pdm2pcm_base_addr, PDM2PCM_RXDATA_REG_OFFSET);
            if (fed == 1 || read != 0) {
                fed = 1;
                if(pdm2pcm_groundtruth[count] != (int)read) {
                    printf("ERROR: at index %d. read != groundtruth (resp. %d != %d).\n",count,(int)read,pdm2pcm_groundtruth[count]);
                    return EXIT_FAILURE;
                }
                ++count;
                if (count >= COUNT) {
                    finish = 1;
                    printf("SUCCESS: Readings correspond to ground truth.\n");
                }
            }
        }
    }
    return EXIT_SUCCESS;
}

