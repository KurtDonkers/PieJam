package com.piejam.androidclient;


import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class PieToAndroid {
    static final int P2A_MSG_SIZE = 4;

    int responseid = 0;

    void FillFromByteStream (byte[] ba) {
        ByteBuffer bb = ByteBuffer.wrap(ba);
        bb.order(ByteOrder.LITTLE_ENDIAN); // optional, the initial order of a byte buffer is always BIG_ENDIAN.
        responseid = bb.getInt();
    }

}
