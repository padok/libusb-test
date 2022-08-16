#include <stdio.h>
#include <libusb.h>
#include <iostream>
#include <cstring>

using namespace std;

#define ERROR 1
#define SUCCESS 0

template <typename Type, int Size>
void print_array(Type const (&array)[Size])
{
    std::cout << "[";
    for (int i = 0; i < Size; i++)
    {
        if (i)
            std::cout << " ," << array[i];
        else
            std::cout << array[i];
    }
    std::cout << "]" << std::endl;
}

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
        cout << "------------------" << endl;
        struct libusb_device *device = dev_list[i];
        struct libusb_device_descriptor desc;
        libusb_get_device_descriptor(device, &desc);
        cout << "idVendor " << desc.idVendor << " idProduct " << desc.idProduct << endl;
        cout << "bDeviceProtocol " << (unsigned int)desc.bDeviceProtocol << endl;

        int bus_nur = libusb_get_bus_number(device);
        cout << "libusb_get_bus_number " << bus_nur << endl;
        cout << "libusb_get_device_speed " << libusb_get_device_speed(device) << endl;

        int device_address = libusb_get_device_address(device);
        cout << "libusb_get_device_address " << device_address << endl;

        int port_number = libusb_get_port_number(device);
        cout << "libusb_get_port_number " << port_number << endl;

        uint8_t port_numbers_byte[8];
        memset(port_numbers_byte, 0, sizeof(port_numbers_byte));
        unsigned int port_numbers[8];
        int port_numbers_ret = libusb_get_port_numbers(device, port_numbers_byte, sizeof(port_numbers_byte));
        for (int i = 0; i < sizeof(port_numbers_byte); i++)
        {
            port_numbers[i] = port_numbers_byte[i];
        }
        std::memcpy(port_numbers, port_numbers_byte, sizeof(port_numbers_byte));
        cout << "libusb_get_port_numbers ";
        print_array(port_numbers);
        cout << endl;
    }

    libusb_free_device_list(dev_list, 1);

    libusb_exit(ctx);
    return SUCCESS;
}
