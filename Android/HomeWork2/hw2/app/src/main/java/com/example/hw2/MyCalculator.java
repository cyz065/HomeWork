package com.example.hw2;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class MyCalculator extends Activity {
    private TextView textView;
    private String expression = ""; // 수식을 담기 위한 변수
    private List<Integer> checkList = new ArrayList<>();
    private LinkedList<String> list = new LinkedList(); // split 된 수식이 들어간다.
    private LinkedList<Double> numList =new LinkedList<>(); // list에 존재하는 숫자들이 추가된다.
    private LinkedList<String> opList = new LinkedList<>(); // 연산자들이 추가된다.
    private BigDecimal result; // 실수 연산의 정확도를 위해 BigDecimal 클래스 사용

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_calculator);
        setTextView();
        // 인텐트를 수신
        Intent intent = getIntent();
        // memo앱에서 인텐트를 전달 받는 경우 string에 memo앱에서 공유한 수식이 저장된다.
        // string이 null인 경우는, webView에서 인텐트를 전달 받는 경우이다.
        String string = intent.getStringExtra("CAL");
        if(string != null)
            intentCalc(string);
    }
    // 초기 textView를 설정해 준다.
    public void setTextView() {
        textView = findViewById(R.id.textView);
        textView.setText("");
    }

    public void numberButtonClick(View v) {
        // 연산 결과가 나온 후 숫자 버튼 클릭시 화면을 초기화 하고 새로운 연산을 수행한다.
        // 연산이 끝나는 경우 numList에는 1개의 숫자가 남게 된다. 이를 통해 연산 수행이 완료됨을 판단한다.
        if(!numList.isEmpty()) {
            expression = "";
            textView.setText("");
            checkList.clear();
            numList.clear();
            opList.clear();
            list.clear();
        }
        // 각각의 숫자 버튼이 클릭되는 경우 화면에 숫자 출력
        switch (v.getId()) {
            case R.id.num0: {
                textView.append("0");
                checkList.add(1);
                expression += "0";
                break;
            }
            case R.id.num1: {
                textView.append("1");
                checkList.add(1);
                expression += "1";
                break;
            }
            case R.id.num2: {
                textView.append("2");
                checkList.add(1);
                expression += "2";
                break;
            }
            case R.id.num3: {
                textView.append("3");
                checkList.add(1);
                expression += "3";
                break;
            }
            case R.id.num4: {
                textView.append("4");
                checkList.add(1);
                expression += "4";
                break;
            }
            case R.id.num5: {
                textView.append("5");
                checkList.add(1);
                expression += "5";
                break;
            }
            case R.id.num6: {
                textView.append("6");
                checkList.add(1);
                expression += "6";
                break;
            }
            case R.id.num7: {
                textView.append("7");
                checkList.add(1);
                expression += "7";
                break;
            }
            case R.id.num8: {
                textView.append("8");
                checkList.add(1);
                expression += "8";
                break;
            }
            case R.id.num9: {
                textView.append("9");
                checkList.add(1);
                expression += "9";
                break;
            }
        }
    }

    // 연산자, 소수점은 가장 처음에 올 수 없다. 따라서 checkList를 통해 연산자 또는 소수점이 가장 처음에 오는지 확인
    // 연산자 혹은 소수점이 처음에 오는 경우, 버튼을 터치해도 아무 반응이 없도록 한다.
    // 앞에 피연산자인 숫자가 존재하는 경우에만 연산자가 출력된다.
    // 연산자가 연속으로 오는 경우도 불가능 하므로 연산자가 연속으로 클릭 되는 경우도 아무 반응이 없도록 해준다.
    // -1 : = 연산자, 0 : 사칙연산자, 1 : 숫자, 2 : 소수점
    public void operatorClick(View v) {
        if(!checkList.isEmpty() && checkList.get(checkList.size() - 1) == 1) {
            switch (v.getId()) {
                case R.id.add: {
                    checkList.add(0);
                    textView.append("+");
                    expression += " + ";
                    break;
                } case R.id.sub: {
                    checkList.add(0);
                    textView.append("-");
                    expression += " - ";
                    break;
                } case R.id.mul: {
                    checkList.add(0);
                    textView.append("X");
                    expression += " X ";
                    break;
                } case R.id.div: {
                    checkList.add(0);
                    textView.append("/");
                    expression += " / ";
                    break;
                }
            }
        }
    }

    // 소수점이 연속으로 동시에 오는 것 방지
    public void dotClick(View v) {
        if(!checkList.isEmpty() && checkList.get(checkList.size() - 1) == 1 && checkList.get(checkList.size() - 1) != 2) {
            textView.append(".");
            checkList.add(2);
            expression += ".";
        }
    }

    // list에 공백을 기준으로 입력받은 수식을 split하게 되면, 숫자 & 연산자가 list에 추가된다.
    // 연산자 없이 숫자만 있는 경우 '='이 들어가는 것을 방지한다.
    // 위 과정을 opList가 empty가 될 때까지 반복한 뒤 결과를 화면에 출력한다.
    public void equalClick(View v) {
        if (!checkList.isEmpty() && checkList.get(checkList.size() - 1) == 1 && checkList.contains(0)) {
            checkList.add(-1);
            textView.append("=");
            for(String s : expression.split(" ")) {
                list.add(s);
            }
            // list에 존재하는 숫자와 연산자에 대하여 연산자는 opList에, 숫자는 String 타입을 double 타입으로 변경 한 뒤, numList에 추가 한다.
            if (list.size() >= 3) {
                for (int i = 0; i < list.size(); i++) {
                    if ("+".equals(list.get(i)) || "-".equals(list.get(i)) || "X".equals(list.get(i)) || "/".equals(list.get(i))) {
                        opList.add(list.get(i));
                    } else {
                        double tmp = Double.parseDouble(list.get(i));
                        numList.add(tmp);
                    }
                }
                // numList의 처음 인덱스와 두번째 인덱스에 존재하는 수를 pop하여 opList의 첫번째 인덱스에 존재하는 연산을 수행한뒤, 결과값을 head에 push한다.
                // opList가 empty가 될때까지 반복한다.
                // 최종적으로 numList에는 1개의 수만 남게되고 이 수가 최종 결과가 된다.
                while (!opList.isEmpty()) {
                    BigDecimal num1 = new BigDecimal(String.valueOf(numList.poll()));
                    BigDecimal num2 = new BigDecimal(String.valueOf(numList.poll()));
                    String op = opList.poll();

                    switch (op) {
                        case "+":
                            numList.addFirst(num1.add(num2).doubleValue());
                            break;
                        case "-":
                            numList.addFirst(num1.subtract(num2).doubleValue());
                            break;
                        case "X":
                            numList.addFirst(num1.multiply(num2).doubleValue());
                            break;
                        case "/":
                            numList.addFirst(num1.divide(num2, 5, RoundingMode.HALF_EVEN).doubleValue());
                            break;
                    }
                }
                // 정확한 실수 연산을 위해 BigDecimal 클래스를 사용하고, 실수 연산을이후 소수점 뒤에 발생하는 0을 제거하기 위해
                // stripTrailingZeros()메소드 사용
                // 수를 지수표현 (1E + 1)이 되지 않도록 하기 위해 toPlainString메소드를 통해 일반적인 숫자 표현으로 변경후 화면에 출력한다.
                // 화면 초기화를 위해 poll이 아닌 get을 사용한다.
                result = new BigDecimal(String.valueOf(numList.get(0)));
                result = new BigDecimal(String.valueOf(result.stripTrailingZeros()));
                textView.append(result.toPlainString());
            }
        }
    }
    // memo에서 공유받은 수식 문자열을 처리하기 위한 메소드
    // 문자열을 첫번째 인덱스부터 읽어서, 숫자와, 연산자를 각각 numList와 opList에 추가한다.
    // 이후 numList와 opList에 존재하는 숫자와 연산자에 대해 각각 연산을 수행 한뒤, 결과를 출력한다.
    public void intentCalc(String str) {
        String num = "";
        textView.append(str);
        // 숫자와, 연산자를 분리하는 과정
        for(int i = 0; i < str.length(); i++) {
            if(str.charAt(i) == '+' || str.charAt(i) == '-' || str.charAt(i) == 'X' || str.charAt(i) == '/') {
                char c = str.charAt(i);
                opList.add(Character.toString(c));
                if(!num.equals("")) {
                    numList.add(Double.parseDouble(num));
                    num = "";
                }
            }
            else if(str.charAt(i) == ' ') {
                continue;
            }
            else {
                char n = str.charAt(i);
                num += Character.toString(n);
            }
        }
        // 가장 마지막 숫자를 numList에 추가
        if(!num.equals("")) {
            numList.add(Double.parseDouble(num));
            num = "";
        }
        // 실제 연산을 수행
        while (!opList.isEmpty()) {
            BigDecimal num1 = new BigDecimal(String.valueOf(numList.poll()));
            BigDecimal num2 = new BigDecimal(String.valueOf(numList.poll()));
            String op = opList.poll();

            if (op.equals("+"))
                numList.addFirst(num1.add(num2).doubleValue());
            else if (op.equals("-"))
                numList.addFirst(num1.subtract(num2).doubleValue());
            else if (op.equals("X"))
                numList.addFirst(num1.multiply(num2).doubleValue());
            else if (op.equals("/"))
                numList.addFirst(num1.divide(num2, 5, RoundingMode.HALF_EVEN).doubleValue());
        }
        result = new BigDecimal(String.valueOf(numList.get(0)));
        result = new BigDecimal(String.valueOf(result.stripTrailingZeros()));
        textView.append("=");
        textView.append(result.toPlainString());
    }

    // webView를 실행 하는 버튼을 클릭하는 경우 webView는 같은 패키지 내에 존재하므로
    // 명시적 인텐트를 통해 인텐트를 전달한다.
    public void webViewClick(View v) {
        Intent intent = new Intent(this, MyWebBrowser.class);
        startActivity(intent);
    }
}