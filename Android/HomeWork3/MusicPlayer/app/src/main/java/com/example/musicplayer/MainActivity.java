package com.example.musicplayer;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;

import java.util.ArrayList;

public class MainActivity extends Activity {
    private ListView listView;
    static ArrayList<Music> musicList = new ArrayList<>();
    public static final int EXTERNAL_STORAGE = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        permission();
        getMusicList();
        initListView();

        // list view에서 item 클릭시 Player화면으로 넘어감
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                Intent intent = new Intent(MainActivity.this, MusicPlayer.class);
                intent.putExtra("POSITION", i);
                startActivity(intent);
            }
        });
    }

    public void getMusicList() {
        Uri uri = MediaStore.Audio.Media.EXTERNAL_CONTENT_URI;
        String[] projection = {
                MediaStore.Audio.Media._ID,
                MediaStore.Audio.Media.TITLE,
                MediaStore.Audio.Media.ARTIST,
                MediaStore.Audio.Media.ALBUM_ID,
                MediaStore.Audio.Media.DURATION
        };
        Cursor cursor = getContentResolver().query(uri, projection, null, null, MediaStore.Audio.Media.TITLE);
        if(cursor != null) {
            while (cursor.moveToNext()) {
                String id = cursor.getString(0);
                String title = cursor.getString(1);
                String artist = cursor.getString(2);
                String albumId = cursor.getString(3);
                long duration = cursor.getLong(4);

                Music music = new Music(id, title, artist, albumId, duration);
                musicList.add(music);
            }
            cursor.close();
        }
    }

    // 권한의 획득
    public void permission() {
        if(checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(MainActivity.this, new String[] {Manifest.permission.READ_EXTERNAL_STORAGE}, EXTERNAL_STORAGE);
        }
        else {
            Toast.makeText(this, "Permission Granted", Toast.LENGTH_LONG).show();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if(requestCode == EXTERNAL_STORAGE) {
            if(grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                Toast.makeText(this, "Permission Granted", Toast.LENGTH_LONG).show();
            }
            else {
                ActivityCompat.requestPermissions(MainActivity.this, new String[] {Manifest.permission.READ_EXTERNAL_STORAGE}, EXTERNAL_STORAGE);
            }
        }
    }

    public void initListView() {
        listView = (ListView)findViewById(R.id.listView);
        MusicAdapter adapter = new MusicAdapter(this, musicList);
        listView.setAdapter(adapter);
    }
}