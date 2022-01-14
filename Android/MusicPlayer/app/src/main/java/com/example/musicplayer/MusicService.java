package com.example.musicplayer;

import static com.example.musicplayer.MusicPlayer.list;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Binder;
import android.os.Build;
import android.os.IBinder;
import android.util.Log;
import android.widget.RemoteViews;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.core.app.NotificationCompat;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import java.util.ArrayList;

public class MusicService extends Service implements MediaPlayer.OnPreparedListener, MediaPlayer.OnCompletionListener{

    IBinder mBinder = new MyBinder();
    MediaPlayer mediaPlayer;
    ArrayList<Music> musicArrayList;
    private int position;
    boolean playing = false;
    private boolean check = false;
    private RemoteViews remoteViews;

    public static String CHANNEL_ID = "music_channel";
    public static String CHANNEL_NAME = "music_name";
    public static String MAIN_ACTION = "MAIN";
    public static String PLAY_ACTION = "PLAY";
    public static String PREV_ACTION = "PREV";
    public static String NEXT_ACTION = "NEXT";
    public static String QUIT_ACTION = "QUIT";

    public static int NOTIFICATION_ID = 123;

    NotificationCompat.Builder notificationBuilder;

    @Override
    public void onCreate() {
        musicArrayList = list;
        super.onCreate();
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        Log.e("Bind", "Method");
        return mBinder;
    }

    @Override
    public void onPrepared(MediaPlayer mediaPlayer) {
        mediaPlayer.start();
    }

    // Player Activity에서 mediaPlayer에 접근 가능
    public class MyBinder extends Binder {
        MusicService getService() {
            return MusicService.this;
        }
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        position = intent.getIntExtra("POSITION", position);
        if (position != -1 && intent.getAction() == null) {
            playMedia(position);
            notification();
        }

        else if (intent.getAction().equals(PLAY_ACTION)) {
            if (mediaPlayer.isPlaying()) {
                mediaPlayer.pause();
            }
            else {
                mediaPlayer.start();
            }
            notification();
        }

        else if (intent.getAction().equals(NEXT_ACTION)) {
            next();
        }

        else if (intent.getAction().equals(PREV_ACTION)) {
            prev();
        }

        else if(intent.getAction().equals(QUIT_ACTION)) {
            stopForeground(true);
            if(isPlaying()) {
                stop();
            }
        }
        return START_NOT_STICKY;
    }


    // 재생
    private void playMedia(int pos) {
        if(mediaPlayer != null) {
            mediaPlayer.stop();
            mediaPlayer.release();
            if(musicArrayList != null) {
                createMediaPlayer(position);
                mediaPlayer.start();
            }
        }
        else {
            createMediaPlayer(position);
            mediaPlayer.start();
        }
        playing = true;
    }

    void start() {
        mediaPlayer.start();
        playing = true;
    }

    void pause() {
        mediaPlayer.pause();
        playing = false;
    }

    boolean isPlaying() {
        return mediaPlayer.isPlaying();
    }
    void stop() {
        mediaPlayer.stop();
    }
    int getDuration() {
        return mediaPlayer.getDuration();
    }
    void seekTo(int position) {
        mediaPlayer.seekTo(position);
    }

    void createMediaPlayer(int position) {
        mediaPlayer = MediaPlayer.create(getBaseContext(), Uri.parse(musicArrayList.get(position).getMusicPath()));
    }
    int getCurrentPosition() {
        return mediaPlayer.getCurrentPosition();
    }


    // 재생 완료시 호출되는 listener 등록
    void onCompleted() {
        mediaPlayer.setOnCompletionListener(this);
    }

    @Override
    public void onCompletion(MediaPlayer mp) {
        position++;
        if(position == musicArrayList.size()) {
            check = false;
            position--;
            sendMessage();
            createMediaPlayer(position);
            Toast.makeText(this, "All Music Played", Toast.LENGTH_LONG).show();
            playing = false;
        }
        else if(mediaPlayer != null && position < musicArrayList.size()) {
            check = true;
            sendMessage();
            createMediaPlayer(position);
            mediaPlayer.start();
            playing = true;
        }
        notification();
    }

    int getPosition() {
        return position;
    }

    void next() {
        if(position + 1 == musicArrayList.size())
            position = 0;
        else
            position ++;
        playMedia(position);
        mediaPlayer.setOnCompletionListener(this);
        notification();
    }

    void prev() {
        if(position == 0)
            position = musicArrayList.size() - 1;
        else
            position--;
        playMedia(position);
        mediaPlayer.setOnCompletionListener(this);
        notification();
    }

    // UI설정을 위한 방송 전달
    private void sendMessage() {
        Intent intent = new Intent("FINISHED");
        intent.putExtra("result", check);
        LocalBroadcastManager.getInstance(this).sendBroadcast(intent);
    }

    public void notification() {
        NotificationManager manager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            NotificationChannel notificationChannel = new NotificationChannel(CHANNEL_ID, CHANNEL_NAME, NotificationManager.IMPORTANCE_DEFAULT);
            manager.createNotificationChannel(notificationChannel);
        }

        // 알림창 컨트롤
        Intent mainIntent = new Intent(getApplicationContext(), MusicPlayer.class);
        position = getPosition();
        mainIntent.setAction(MAIN_ACTION);
        mainIntent.putExtra("POSITION", position);
        mainIntent.putExtra("SEEK", mediaPlayer.getCurrentPosition());
        mainIntent.putExtra("IS_PLAYING", mediaPlayer.isPlaying());

        PendingIntent pendingIntent = PendingIntent.getActivity(MusicService.this, 0, mainIntent, PendingIntent.FLAG_UPDATE_CURRENT);
        remoteViews = new RemoteViews(getPackageName(), R.layout.notification);

        if(mediaPlayer.isPlaying())
            remoteViews.setImageViewResource(R.id.play_pause_btn, R.drawable.ic_pause);
        else
            remoteViews.setImageViewResource(R.id.play_pause_btn, R.drawable.ic_play);

        remoteViews.setTextViewText(R.id.noti_title, musicArrayList.get(position).getTitle());
        remoteViews.setImageViewUri(R.id.image, Uri.parse(musicArrayList.get(position).getAlbumPath()));

        // 이전버튼
        Intent prevIntent = new Intent(this, MusicService.class);
        prevIntent.setAction(PREV_ACTION);

        PendingIntent pendingPrevIntent = PendingIntent.getService(MusicService.this, 0, prevIntent, 0);

        // 실행 버튼
        Intent playIntent = new Intent(this, MusicService.class);
        playIntent.setAction(PLAY_ACTION);
        PendingIntent pendingPlayIntent = PendingIntent.getService(MusicService.this, 0, playIntent, 0);

        // 다음 버튼
        Intent nextIntent = new Intent(this, MusicService.class);
        nextIntent.setAction(NEXT_ACTION);
        PendingIntent pendingNextIntent = PendingIntent.getService(MusicService.this, 0, nextIntent, 0);

        // quit 버튼
        Intent quitIntent = new Intent(this, MusicService.class);
        quitIntent.setAction(QUIT_ACTION);
        PendingIntent pendingQuitIntent = PendingIntent.getService(MusicService.this, 0, quitIntent, 0);

        // 알림창 UI 설정
        notificationBuilder = new NotificationCompat.Builder(MusicService.this, CHANNEL_ID)
                .setSmallIcon(R.drawable.ic_music_note)
                .setContent(remoteViews)
                .setContentTitle("Music Player")
                .setContentIntent(pendingIntent);

        // 각 버튼에 대한 이벤트 리스너 등록
        remoteViews.setOnClickPendingIntent(R.id.previous_btn, pendingPrevIntent);
        remoteViews.setOnClickPendingIntent(R.id.next_btn, pendingNextIntent);
        remoteViews.setOnClickPendingIntent(R.id.play_pause_btn, pendingPlayIntent);
        remoteViews.setOnClickPendingIntent(R.id.close, pendingQuitIntent);

        // notification 시작
        startForeground(NOTIFICATION_ID, notificationBuilder.build());
    }
}