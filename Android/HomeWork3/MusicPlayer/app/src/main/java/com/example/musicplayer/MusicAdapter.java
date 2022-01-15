package com.example.musicplayer;

import android.content.Context;
import android.net.Uri;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;

public class MusicAdapter extends BaseAdapter {
    private ArrayList<Music> musicArrayList;
    private LayoutInflater inflater;
    private Context context;

    public MusicAdapter(Context context, ArrayList<Music> list) {
        this.musicArrayList = list;
        this.context = context;
        this.inflater = LayoutInflater.from(context);
    }

    @Override
    public int getCount() {
        return musicArrayList.size();
    }

    @Override
    public Music getItem(int i) {
        return musicArrayList.get(i);
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {
        View itemLayout = inflater.inflate(R.layout.list_item_layout, null);
        ImageView imageView = (ImageView)itemLayout.findViewById(R.id.album);
        TextView textView = (TextView)itemLayout.findViewById(R.id.title);

        Uri uri = Uri.parse(musicArrayList.get(i).getAlbumPath());
        imageView.setImageURI(uri);
        textView.setText(musicArrayList.get(i).getTitle());
        return itemLayout;
    }
}