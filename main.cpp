#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <wiringPi.h>
#include "bmp280.h"

int main(int argc, char **argv) {
    //	char * device = "/dev/i2c-0";
    //	char * device = "/dev/i2c-1";
    char * device = "/dev/i2c-2";
    //	char * device = "/dev/i2c-3";
    int devId = BMP280_I2C_ADDRESS1;

    try {
        BMP280 * bmp280 = new BMP280(device, devId);
        int fd = bmp280->init();
        if (fd < 0) {
            printf("Device not found");
            return -1;
        }

        printf("fd       : 0x%02x\n", fd);
        printf("chip id  : 0x%02x\n", bmp280->getChipId());
        printf("chip ver : 0x%02x\n", bmp280->getChipVersion());

        bmp280->reset();
        bmp280->setPowerMode(BMP280_NORMAL_MODE);
        bmp280->setTemperatureOversampling(BMP280_ULTRAHIGHRESOLUTION_OVERSAMP_TEMPERATURE);
        bmp280->setPressureOversampling(BMP280_ULTRAHIGHRESOLUTION_OVERSAMP_PRESSURE);
        bmp280->setIrrFilter(BMP280_FILTER_COEFF_16);
        bmp280->setStandbyTime(BMP280_STANDBY_TIME_250_MS);

        printf("---------------\n");
        printf("pw mode  : 0x%02x\n", bmp280->getPowerMode());
        printf("osrs_p   : 0x%02x\n", bmp280->getPressureOversampling());
        printf("osrs_t   : 0x%02x\n", bmp280->getTemperatureOversampling());
        printf("---------------\n");
        printf("filter   : 0x%02x\n", bmp280->getIrrFilter());
        printf("t_sb     : 0x%02x\n", bmp280->getStandbyTime());
        printf("---------------\n");
        printf("spi3w sts: 0x%02x\n", bmp280->getSpi3w());
        printf("measuring: 0x%02x\n", bmp280->getMeasuringStatus());
        printf("im_update: 0x%02x\n", bmp280->getImUpdateStatus());
        printf("---------------\n");

        while (1) {
            delay(1000);
            BMP280Data * bmp280Data = bmp280->getBMP280Data();
            printf("pressure   : %.2f hPa\n", bmp280Data->getPressure());
            printf("temperature: %.2f C\n", bmp280Data->getTemperature());
            printf("altitude   : %.2f m\n\n", bmp280Data->getAltitude());
            delete bmp280Data;
        }
        delete bmp280;
    } catch (std::exception & e) {
        printf("%s\n", e.what());
    }
    return 0;
}
