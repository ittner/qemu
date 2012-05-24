/**
 * Experimental "hello world device"
 *
 * Copyright (c) 2012 Alexandre Erwin Ittner <alexandre@ittner.com.br>
 *
 * This device is only intended as a demonstration/experimental hack and
 * should not be used in production environment. BTW, it's useless for
 * anything that may be called "production" :)
 *
 * ---------------------
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "hw.h"
#include "pci.h"



typedef struct _HelloWordlState {
    PCIDevice dev;
} HelloWordlState;



static int pci_hello_world_init(PCIDevice *dev)
{
    printf("pci_hello_world_init\n");
    return 0;
}

static int pci_hello_world_uninit(PCIDevice *dev)
{
    printf("pci_hello_world_uninit\n");
    return 0;
}

static void pci_hello_world_reset(DeviceState *d)
{
    printf("pci_hello_world_reset\n");
}


static void hello_world_class_init(ObjectClass *klass, void *data)
{
    printf("hello_world_class_init\n");
    DeviceClass *dc = DEVICE_CLASS(klass);
    PCIDeviceClass *k = PCI_DEVICE_CLASS(klass);

    k->init = pci_hello_world_init;
    k->exit = pci_hello_world_uninit;
    k->romfile = "";
    k->vendor_id = 0x1af4; /* Experimental vendor */
    k->device_id = 0x1042; /* Experimental device */
    k->revision = 1;
    k->class_id = PCI_CLASS_OTHERS;
    dc->reset = pci_hello_world_reset;
    dc->vmsd = NULL;
    dc->props = NULL;
}



static TypeInfo hello_world_info = {
    .name          = "helloworld",
    .parent        = TYPE_PCI_DEVICE,
    .instance_size = sizeof(HelloWordlState),
    .class_init    = hello_world_class_init,
};

static void hello_world_register_types(void)
{
    printf("hello_world_register_types\n");
    type_register_static(&hello_world_info);
}

type_init(hello_world_register_types)
