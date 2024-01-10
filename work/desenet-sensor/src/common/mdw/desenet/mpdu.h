#ifndef MPDU_H
#define MPDU_H

#include "types.h"
#include "platform-config.h"
#include "frame.h"

#define SIZE_GATEWAY_ADDR 4
#define SIZE_MPDU_LEN 1
#define SIZE_DELTA_E 1
#define SIZE_ePDU_COUNT 1
#define SIZE_HEADER (SIZE_GATEWAY_ADDR + SIZE_MPDU_LEN + SIZE_DELTA_E + SIZE_ePDU_COUNT)
#define SIZE_DATA 30
#define SIZE_MPDU (SIZE_DATA + SIZE_HEADER)
#define EPDU_COUNT_POS (SIZE_GATEWAY_ADDR + SIZE_MPDU_LEN + SIZE_DELTA_E)
#define SIZE_PDU 7
// defines sizes of the different fields in the MPDU

class MPDU : public Frame
{ // MPDU herits from Frame
private:
    desenet::SlotNumber _sensorID; // sensorID is a slot number
    uint8_t _nbrPDU;               // number of PDUs
public:
    MPDU() : Frame(Frame::Mtu) // constructor of MPDU
    {
        initialize(); // initialise the MPDU
    }                 // we call the Frame constructor with the maximal transfer unit = max size of MPDU
    // this initialises an MPDU of size 37 in the frame class... the methods from frame class allow to write destination,
    // type of frame, sensorID etc.

    /**
     * @brief Initializes the MPDU (Medium Access Control Protocol Data Unit).
     *
     * This function clears the buffer, sets the destination address to the gateway address, sets the sensor ID, sets the frame type to MPDU, and finally clears the frame.
     */

    void initialize(); // initialise the MPDU

    /**
     * @brief Clears the MPDU (Medium Access Control Protocol Data Unit).
     *
     * This function clears the MPDU by resetting the PDU count to 0 and setting the length of the MPDU to 7.
     */
    void clear();

    /**
     * @brief Converts the proxy to an MPDU.
     *
     * This function returns a SharedByteBuffer object which is tied to the frame. This buffer begins at buffer()+length()+1 and has a length of maxFrameLen-actualLength-1. The +1 is because of the PDU Header which is 1 byte.
     *
     * @return A SharedByteBuffer object tied to the frame.
     */
    SharedByteBuffer proxy2mpdu();

    /**
     * @brief Prints the MPDU (Medium Access Control Protocol Data Unit).
     *
     * This function prints the MPDU to the console in hexadecimal format.
     */
    void printMPDU();

    /**
     * @brief Writes the PDU (Protocol Data Unit) header onto the frame.
     *
     * This function writes the PDU header to the buffer. The header includes the type, svgroup, and dataSize.
     *
     * @param type The type of the PDU.
     * @param svgroup The group of the sensor value.
     * @param dataSize The size of the data.
     */
    void writePDUHeader(uint8_t type, SvGroup svgroup, size_t dataSize);
};

#endif // MPDU_H
