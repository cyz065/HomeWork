package com.example.musicplayer;

import static com.example.musicplayer.MainActivity.musicList;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;
import java.util.ArrayList;

public class MusicPlayer extends AppCompatActivity {
    ImageView album;
    TextView title, totalTime, curTime;
    ImageView play, next, previous;
    SeekBar seekBar;

    Handler handler = new Handler();

    int position = 0;
    int seekPos;
    public static ArrayList<Music> list = musicList;
    MusicService musicService = null;
    boolean message = false;

    // 음악 재생이 끝난 경우 Service에서 Activity로 BroadCast를 보내고 UI 변경
    private BroadcastReceiver receiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            message = intent.getBooleanExtra("result", false);
            position = musicService.getPosition();
            setUI();
        }
    };

    // Service와 연결을 통해 Service의 mediaplyaer에 접근이 가능
    private ServiceConnection connection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder iBinder) {
            MusicService.MyBinder myBinder = (MusicService.MyBinder) iBinder;
            musicService = myBinder.getService();
            seekBar.setMax(musicService.getDuration() / 1000);
            setUI();
            musicService.onCompleted();
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            musicService = null;
        }
    };

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.music_player);
        initView();
        getIntentMethod();
        setUI();

        // seek바 설정
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (musicService != null && fromUser)
                    musicService.seekTo(progress);

                if (seekBar.getMax() <= progress) {
                    musicService.onCompleted();
                    //position = musicService.getPosition();
                    setUI();
                    Log.d("Player Activity", "Play Finished");
                    if (position == list.size() - 1) {
                        play.setImageResource(R.drawable.ic_play);
                    }
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                musicService.pause();
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                musicService.seekTo(seekBar.getProgress());
                if (seekBar.getProgress() > 0) {
                    musicService.seekTo(musicService.getCurrentPosition());
                    musicService.start();
                }
            }
        });

        // 재생버튼
        play.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (musicService.isPlaying()) {
                    musicService.pause();
                    play.setImageResource(R.drawable.ic_play);
                } else if (!musicService.isPlaying() && musicService != null) {
                    musicService.seekTo(musicService.getCurrentPosition());
                    musicService.start();
                    play.setImageResource(R.drawable.ic_pause);
                }
            }
        });

        // 다음버튼 클릭
        next.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                musicService.next();
                position = musicService.getPosition();
                setUI();
            }
        });

        // 이전버튼 클릭
        previous.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                musicService.prev();
                position = musicService.getPosition();
                setUI();
            }
        });

        // 알림창에서 데이터를 받는 경우 getNoti함수 실행
        getNoti();

        // seekBar progress 진행을 위한 Thread
        MusicPlayer.this.runOnUiThread(new Runnable() {
            public void run() {
                if (musicService != null) {
                    int mCurrentPosition = musicService.getCurrentPosition() / 1000;
                    seekBar.setProgress(musicService.getCurrentPosition());
                    curTime.setText(formattedTime(mCurrentPosition));
                }
                handler.postDelayed(this, 200);
            }
        });
    }

    // Service와 BroadCastReceiver 연결
    @Override
    protected void onResume() {
        super.onResume();
        Intent serviceIntent = new Intent(this, MusicService.class);
        bindService(serviceIntent, connection, BIND_AUTO_CREATE);
        LocalBroadcastManager.getInstance(this).registerReceiver(receiver, new IntentFilter("FINISHED"));
    }

    // 리시버와 서비스 연결 해제
    @Override
    protected void onDestroy() {
        super.onDestroy();
        LocalBroadcastManager.getInstance(this).unregisterReceiver(receiver);
        unbindService(connection);
    }

    // 뷰 초기화
    public void initView() {
        album = (ImageView) findViewById(R.id.album_image);
        title = (TextView) findViewById(R.id.music_title);

        play = (ImageView) findViewById(R.id.play_pause);
        next = (ImageView) findViewById(R.id.next);
        previous = (ImageView) findViewById(R.id.previous);

        seekBar = (SeekBar) findViewById(R.id.progress);

        curTime = (TextView) findViewById(R.id.current_time);
        totalTime = (TextView) findViewById(R.id.total_time);
    }


    // Main에서 position을 받아 music 객체의 정보를 service에 전달
    public void getIntentMethod() {
        position = getIntent().getIntExtra("POSITION", position);
        if (list != null) {
            play.setImageResource(R.drawable.ic_pause);
        }
        Intent intent = new Intent(this, MusicService.class);
        intent.putExtra("POSITION", position);
        startService(intent);
    }

    // seekBar 시간 출력
    private String formattedTime(int mCurrentPosition) {
        String totalOut = "";
        String totalNew = "";
        String seconds = String.valueOf(mCurrentPosition % 60);
        String minutes = String.valueOf(mCurrentPosition / 60);
        totalOut = minutes + ":" + seconds;
        totalNew = minutes + ":" + "0" + seconds;
        if (seconds.length() == 1)
            return totalNew;
        else
            return totalOut;
    }

    // Player의 기본적인 UI 설정
    public void setUI() {
        if (list != null && position < list.size()) {
            try {
                Uri uri = Uri.parse(list.get(position).getAlbumPath());
                album.setImageURI(uri);
            } catch (Exception e) {
                album.setImageResource(R.drawable.ic_play);
            }
            title.setText(list.get(position).getTitle());
            seekBar.setMax((int) list.get(position).getDuration());
            int total = (int) list.get(position).getDuration() / 1000;
            totalTime.setText(formattedTime(total));
        }
    }

    // 알림창을 통해 데이터를 받는경우
    public void getNoti() {
        String action = getIntent().getAction();
        if (action != null && action.equals("ACTION_MAIN")) {
            position = getIntent().getIntExtra("POSITION", 0);
            seekPos = getIntent().getIntExtra("SEEK", 0);

            if (musicService.isPlaying())
                play.setImageResource(R.drawable.ic_pause);
            else
                play.setImageResource(R.drawable.ic_play);

            if (position < list.size()) {
                Uri uri = Uri.parse(list.get(position).getAlbumPath());
                album.setImageURI(uri);
                title.setText(list.get(position).getTitle());
                seekBar.setMax((int) list.get(position).getDuration());
                seekBar.setProgress(seekPos);
                musicService.seekTo(seekPos);
                int total = (int) list.get(position).getDuration() / 1000;
                totalTime.setText(formattedTime(total));
            }
        }
    }
}