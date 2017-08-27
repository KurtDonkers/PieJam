package com.piejam.androidclient;

import android.os.Bundle;
import android.os.Handler;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.TextView;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class MainActivity extends AppCompatActivity {

    public PieJamSocketHandler mPieJamSocketHandler = new PieJamSocketHandler();
    private Handler handler = new Handler();
    TextView mResponseOutput;
    EditText mClientIdInput;
    SeekBar mNrofStarsInput;
    private int mCounter = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
        mResponseOutput = (TextView) findViewById(R.id.reply);
        mClientIdInput = (EditText) findViewById(R.id.clientidEdit);
        mNrofStarsInput = (SeekBar) findViewById(R.id.nrofStarsEdit);
        //mPieJamSocketHandler.connect();
        final AndroidToPie senddata = SetPacketToSend();
        mPieJamSocketHandler.setSendData(senddata);
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                PieToAndroid rcvdata = mPieJamSocketHandler.getRcvData();
                mResponseOutput.setText (Integer.toString(rcvdata.responseid));
                AndroidToPie senddata2 = SetPacketToSend();
                mPieJamSocketHandler.setSendData(senddata2);
                handler.postDelayed(this, 100);
            }
        }, 100);
    }

    AndroidToPie SetPacketToSend () {
        AndroidToPie senddata = new AndroidToPie();
        senddata.cmdid = 42;
        senddata.clientid = 0;//Integer.parseInt(mClientIdInput.getText().toString());
        senddata.nrofstars = mNrofStarsInput.getProgress();
        senddata.r = 0.0f;
        senddata.g = 0.0f;
        senddata.b = 0.0f;
        return (senddata);
    }

    @Override
    protected void onResume() {
        super.onResume();
        mPieJamSocketHandler.connect();
    }

    @Override
    protected void onPause() {
        super.onPause();
        mPieJamSocketHandler.disconnect();
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        //mPieJamSocketHandler.connect();
    }

    @Override
    protected void onStop() {
        super.onStop();
        //mPieJamSocketHandler.disconnect();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        //mPieJamSocketHandler.disconnect();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

}
