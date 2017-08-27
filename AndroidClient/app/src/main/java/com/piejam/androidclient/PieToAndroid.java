package com.piejam.androidclient;


import java.nio.ByteBuffer;

class PieToAndroid {
    static final int P2A_MSG_SIZE = 4;

    int responseid = 0;

    void FillFromByteStream (byte[] ba) {
        ByteBuffer bb = ByteBuffer.wrap(ba);
        responseid = bb.getInt();
    }

}
