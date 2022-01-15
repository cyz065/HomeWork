package com.example.hw2;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.webkit.WebBackForwardList;
import android.webkit.WebResourceRequest;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.EditText;
import android.widget.TextView;

public class MyWebBrowser extends Activity {
    private WebView webView;
    private EditText url;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_web_browser);
        webView = findViewById(R.id.WebView);
        url = findViewById(R.id.URL);

        // Calculator액티비티와, memo앱으로부터 인텐트를 전달받는다.
        Intent intent = getIntent();
        // u에는 memo앱으로부터 전달받은 URL이 존재하게 된다.
        String u = intent.getStringExtra("URL");
        // u 가 null인 경우에는 Calculator액티비티로부터 인텐트를 전달받은 경우가 된다.
        if(u != null) {
            if(!u.startsWith("http"))
                u = "http://" + u;
            webView.loadUrl(u);
        }

        WebSettings webSettings = webView.getSettings();
        webSettings.setJavaScriptEnabled(true);

        webView.setWebViewClient(new WebViewClient() {
            // 페이지 이동시 URL 변경
            @Override
            public boolean shouldOverrideUrlLoading(WebView view, WebResourceRequest request) {
                String newAddress = request.getUrl().toString();
                webView.loadUrl(newAddress);
                url.setText(newAddress);
                return false;
            }
        });
        // text창에 URL입력 뒤, 가상 키보드의 go버튼을 클릭하면 해당 웹 페이지로 이동한다.
        url.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView view, int actionId, KeyEvent event) {
                if(actionId == EditorInfo.IME_ACTION_GO) {
                    String address = url.getText().toString();
                    if(!address.startsWith("http://")) {
                        address = "http://" + address;
                    }
                    webView.loadUrl(address);
                    url.setText(webView.getUrl().toString());
                    // 입력 완료후 이동 시 키보드 숨김
                    InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
                    imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
                    return true;
                }
                return false;
            }
        });
    }
    // 계산기 실행 버튼 클릭시 계산기에 intent를 전달한다.
    // webBroswer와 Calculator는 같은 패키지에 존재하므로 명시적 인텐트를 사용한다.
    public void calClick(View v) {
        Intent intent = new Intent(this, MyCalculator.class);
        startActivity(intent);
    }
    // 이전페이지 버튼을 클릭한 경우, 이전페이지가 존재하면 이전페이지로 이동
    // 이동 후, 이동된 페이지의 URL을 text창에 출력
    public void previousClick(View V) {
        if(webView.canGoBack()) {
            WebBackForwardList list = webView.copyBackForwardList();
            int index = list.getCurrentIndex() - 1;
            String backUrl = list.getItemAtIndex(index).getUrl();
            webView.goBack();
            url.setText(backUrl);
        }
    }
    // 다음페이지 버튼 클릭 시, 다음페이지가 존재하는 경우 다음페이지로 이동
    // 이동 뒤, 이동된 페이지의 URL을 text창에 출력
    public void nextClick(View v) {
        if(webView.canGoForward()) {
            WebBackForwardList list = webView.copyBackForwardList();
            int index = list.getCurrentIndex() + 1;
            String forwardUrl = list.getItemAtIndex(index).getUrl();
            webView.goForward();
            url.setText(forwardUrl);
        }
    }
}
