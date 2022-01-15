package com.example.musicplayer;

import android.net.Uri;
import android.provider.MediaStore;

import java.io.Serializable;

public class Music implements Serializable {
    private String id;  // 음원 자체의 ID
    private String title;
    private String artist;
    private String albumId; // Album 이미지 ID
    private long duration;

    public Music(String id, String title, String artist, String albumId, long duration) {
        this.id = id;
        this.title = title;
        this.artist = artist;
        this.albumId = albumId;
        this.duration = duration;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getArtist() {
        return artist;
    }

    public void setArtist(String artist) {
        this.artist = artist;
    }

    public String getAlbumId() {
        return albumId;
    }

    public void setAlbumId(String albumId) {
        this.albumId = albumId;
    }

    public long getDuration() {
        return duration;
    }

    public void setDuration(long duration) {
        this.duration = duration;
    }

    public String getMusicPath() {
        return Uri.withAppendedPath(MediaStore.Audio.Media.EXTERNAL_CONTENT_URI, id).toString();
    }
    public String getAlbumPath() {
        return Uri.parse("content://media/external/audio/albumart/" + albumId).toString();
    }
}
