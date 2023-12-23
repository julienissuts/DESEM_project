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

class MPDU : Frame{ // MPDU herits from Frame
private:
    desenet::SlotNumber _sensorID;
    uint8_t _nbrPDU;
public:
    MPDU() : Frame(Frame::Mtu)
    {
        initialize();
    }//we call the Frame constructor with the maximal transfer unit = max size of MPDU
    //this initialises an MPDU of size 37 in the frame class... the methods from frame class allow to write destination,
    //type of frame, sensorID etc.

    void initialize();


    void clear();

    SharedByteBuffer proxy2mpdu();
    void printMPDU();
    void writePDUHeader(uint8_t type, SvGroup svgroup, size_t dataSize);
    void incrementEPDUCount();
};

#endif // MPDU_H
