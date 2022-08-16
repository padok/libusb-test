#include <stdio.h>
#include <libusb.h>
#include <iostream>
using namespace std;

#define ERROR 1
#define SUCCESS 0

int main(int argc, char *argv[])
{
    libusb_context *ctx;
    int err = libusb_init(&ctx);
    if (err)
    {
        cout << "libusb_init error: " << err << endl;
        libusb_exit(ctx);
        return ERROR;
    }

    libusb_device **dev_list;
    ssize_t num_devs = libusb_get_device_list(ctx, &dev_list);
    if (num_devs < 1)
    {
        cout << "num_devs: " << num_devs << endl;
        cout << "exiting..." << endl;
        libusb_exit(ctx);
        return ERROR;
    }

    int i;
    for (i = 0; i < num_devs; i++)
    {
        struct libusb_device *device = dev_list[i];
        struct libusb_device_descriptor desc;
        libusb_get_device_descriptor(device, &desc);
        cout << "idVendor " << desc.idVendor << " idProduct " << desc.idProduct << endl;
        int bus_nur = libusb_get_bus_number(device);
        cout << "libusb_get_bus_number " << bus_nur << endl;
        cout << "libusb_get_device_speed " << libusb_get_device_speed(device) << endl;
    }

    libusb_free_device_list(dev_list, 1);

    libusb_exit(ctx);
    return SUCCESS;
}
