#include "mpdu.h"
#include <iostream>
#include <iomanip> // For std::hex and std::setw

void MPDU::initialize()
{

    // Clear the buffer first
    memset(buffer(), 0, Frame::Mtu);
    // buffer() returns a ptr to a SharedByteBuffer in Frame class
    // Frame::Mtu The maximum size (bytes) of a frame.

    // set address field in frame
    setDestination(GATEWAY_ADDRESS);

    // set the sensorID
    _sensorID = DEFAULT_DESENET_SLOT_NUMBER; // 15=0xF
    memcpy(buffer() + Frame::HEADER_SIZE, &_sensorID, 1);// copy the sensorID to the buffer after the GATEWAY_ADDRESS and LENGTH

    // set the type of frame to MPDU
    setType(FrameType::MPDU);

    clear();// reset the PDU count to 0 and set the length of the MPDU to 7

    // printMPDU();
}

SharedByteBuffer MPDU::proxy2mpdu()
{
    return SharedByteBuffer::proxy((buffer() + length() + 1), (Frame::Mtu - length() - 1));
    // returns a SharedByteBuffer object which is tied to the frame
    // this buffer begins at buffer()+length()+1 and has a length of maxFrameLen-actualLength-1
    //  +1 is because of PDU Header
    // remember SharedByteBuffer is not the buffer itself it only has the ptr to the buffer and the length of it
}

void MPDU::writePDUHeader(uint8_t type, SvGroup svgroup, size_t dataSize)
{
    SharedByteBuffer temp = SharedByteBuffer::proxy((buffer() + length()), (Frame::Mtu - length()));//temp is a SharedByteBuffer object which is tied to the frame
    // this buffer begins at buffer()+length() and has a length of maxFrameLen-actualLength
    // means that the buffer begins exactly at the end of the last added PDU

    uint8_t PDU_header = type << 7 | svgroup << 3 | dataSize;// composition of PDU header
    memset(temp.data(), PDU_header, sizeof(PDU_header));// write the PDU header to the buffer

    if (length() >= 7)
    {                        // Check if the buffer has at least 6 elements
        (*(buffer() + 6))++; // Increment the 6th element = nbr of PDU's
    }

    setLength(length() + dataSize + 1); // update new length
    // +1 because of the PDU header
}

void MPDU::printMPDU()
{
    std::cout << "MPDU is: ";
    for (int i = 0; i < 37; ++i)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>(*(buffer() + i)) << " ";
    }
    std::cout << std::endl; // Print newline after the loop
}

void MPDU::clear()
{
    memset(buffer() + Frame::HEADER_SIZE + 1, 0, 1);
    // Reset the PDU count to 0
    memset(buffer() + Frame::HEADER_SIZE + 1, 0, 1);
    // it is placed one byte behind the dest addr, we write value 0 and on 1 byte

    // set the length of the MPDU to 7 (Frame header = 5, delta E = 1, ePDUCount = 1)
    setLength(Frame::HEADER_SIZE + 2); // in the MPDU the length will be set to 2 because payload=2 ...
}
