package com.piejam.androidclient;


import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class AndroidToPie {
    private static final int A2P_MSG_SIZE = 24;

    int cmdid = 0x42;
    int clientid = 3;
    int nrofstars = 1000;
    float r = 1;
    float g = 1;
    float b = 1; // [0..1]

    byte[] GetByteStream () {
        ByteBuffer bb = ByteBuffer.allocate(A2P_MSG_SIZE);
        bb.order(ByteOrder.LITTLE_ENDIAN); // optional, the initial order of a byte buffer is always BIG_ENDIAN.
        bb.putInt (cmdid);
        bb.putInt (clientid);
        bb.putInt (nrofstars);
        bb.putFloat (r);
        bb.putFloat (g);
        bb.putFloat (b);

        return bb.array();
    }
}
