import usb.core
import usb.util
import struct

# find the device
dev = usb.core.find(idVendor=0x04B4, idProduct=0x0010)

# was it found
if dev is None:
    raise ValueError('Device not found')

#set the active configuration. With no arguments the first
# configuration will be the first one
dev.set_configuration()

# get an endpoint instance
cfg = dev.get_active_configuration()
interface_number = cfg[(0,0)].bInterfaceNumber
alternate_setting = usb.control.get_interface(dev,interface_number)
intf = usb.util.find_descriptor(
    cfg, bInterfaceNumber = interface_number,
    bAlternateSetting = alternate_setting
)


epOut = usb.util.find_descriptor(
    intf,
    # match the first OUT endpoint
    custom_match = \
    lambda e: \
        usb.util.endpoint_direction(e.bEndpointAddress) == \
        usb.util.ENDPOINT_OUT
)

epIn = usb.util.find_descriptor(
    intf,
    # match the first OUT endpoint
    custom_match = \
    lambda e: \
        usb.util.endpoint_direction(e.bEndpointAddress) == \
        usb.util.ENDPOINT_IN
)

assert epOut is not None
assert epIn is not None


def tester1(num):
    epOut.write('1', timeout=10000)
    inData= epIn.read(num)
    #for i in range(num):
        #inData= epIn.read(64)
    return inData
#epOut.write('1')
#epIn.read(64)

#numOfBytes=4
#epOut.write('test')
#epIn.read(numOfBytes)
