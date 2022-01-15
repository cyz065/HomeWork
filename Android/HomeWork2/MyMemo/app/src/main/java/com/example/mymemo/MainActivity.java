package com.example.mymemo;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.ActionMode;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    private EditText editText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        editText = findViewById(R.id.Memo);
        editText.setCustomSelectionActionModeCallback(new ActionMode.Callback() {
            @Override
            public boolean onCreateActionMode(ActionMode actionMode, Menu menu) {
                return true;
            }

            @Override
            public boolean onPrepareActionMode(ActionMode actionMode, Menu menu) {
                return false;
            }

            public boolean onActionItemClicked(ActionMode actionMode, MenuItem menuItem) {
                int start = editText.getSelectionStart();
                int end = editText.getSelectionEnd();
                String str = editText.getText().toString();
                str.substring(start, end);

                switch(menuItem.getItemId()) {
                    // 메모장에 URL을 입력한뒤, 공유 버튼을 클릭한 경우,
                    // 인터넷을 Browser를 이용하므로 APP_BROWSER카테고리를 추가한다.
                    // URL이 담긴 문자열을 인텐트에 추가하여 암시적 인텐트를 전달한다.
                    case android.R.id.shareText :
                        if(str.contains(".com") || str.contains("www") || str.contains("http://")) {
                            Intent intent = new Intent(Intent.ACTION_MAIN);
                            intent.addCategory(Intent.CATEGORY_APP_BROWSER);
                            intent.putExtra("URL", str);
                            startActivity(intent);
                        }
                        // 메모장에 수식을 입력한 후, 공유 버튼을 클릭하는 경우,
                        // 공유 버튼 클릭시 사용 가능한 앱 리스트가 나타나도록 하기 위해 APP_MESSAGING카테고리를 추가한다.
                        // 수식이 담긴 문자열을 인텐트에 추가하여 전달한다.
                        else if(str.contains("+") || str.contains("-") || str.contains("X") || str.contains("/")) {
                            Intent intent = new Intent(Intent.ACTION_MAIN);
                            intent.addCategory(Intent.CATEGORY_APP_MESSAGING);
                            //intent.addCategory(Intent.CATEGORY_APP_CALCULATOR);
                            intent.putExtra("CAL", str);
                            startActivity(intent);
                        }
                }
                return true;
            }

            @Override
            public void onDestroyActionMode(ActionMode actionMode) {}
        });
    }
}