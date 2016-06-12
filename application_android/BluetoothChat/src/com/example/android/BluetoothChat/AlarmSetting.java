package com.example.android.BluetoothChat;

import java.util.Calendar;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.Dialog;
import android.content.Intent;
import android.content.res.Resources;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.NumberPicker;

@SuppressLint("NewApi")
public class AlarmSetting extends Activity {
	NumberPicker np_h = null;
    NumberPicker np_m = null;
    NumberPicker np_s = null;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_INDETERMINATE_PROGRESS);
		setContentView(R.layout.alarm_control);
		
		Calendar calender = Calendar.getInstance();
	    int hour = calender.get(Calendar.HOUR);
	    int month = calender.get(Calendar.MONTH);
	    int second = calender.get(Calendar.SECOND);
	    
//	    final Dialog alarmDialog = new Dialog(this);
//	    alarmDialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
//	    alarmDialog.setContentView(R.layout.alarm_control);
	 
	    Button okBtn = (Button) findViewById(R.id.alarm_btn_ok);
	    Button cancelBtn = (Button) findViewById(R.id.alarm_btn_cancel);
	 
	    np_h = (NumberPicker) findViewById(R.id.alarm_hour);
	    np_m = (NumberPicker) findViewById(R.id.alarm_min);
	    np_s = (NumberPicker) findViewById(R.id.alarm_sec);
	    
	    np_h.setMinValue(0);
	    np_h.setMaxValue(48);
	    np_m.setMinValue(0);
	    np_m.setMaxValue(60);
	    np_s.setMinValue(0);
	    np_s.setMaxValue(60);
	    
	    np_h.setDescendantFocusability(NumberPicker.FOCUS_BLOCK_DESCENDANTS);
	    np_h.setWrapSelectorWheel(false);
	    np_h.setValue(0);
	    np_m.setDescendantFocusability(NumberPicker.FOCUS_BLOCK_DESCENDANTS);
	    np_m.setWrapSelectorWheel(false);
	    np_m.setValue(0);
	    np_s.setDescendantFocusability(NumberPicker.FOCUS_BLOCK_DESCENDANTS);
	    np_s.setWrapSelectorWheel(false);
	    np_s.setValue(0);
	    
	    np_h.setOnValueChangedListener(new NumberPicker.OnValueChangeListener() {
	        @Override
	        public void onValueChange(NumberPicker picker, int oldVal, int newVal) {
	            
	        }
	    });
	    np_m.setOnValueChangedListener(new NumberPicker.OnValueChangeListener() {
	        @Override
	        public void onValueChange(NumberPicker picker, int oldVal, int newVal) {
	            
	        }
	    });
	    np_s.setOnValueChangedListener(new NumberPicker.OnValueChangeListener() {
	        @Override
	        public void onValueChange(NumberPicker picker, int oldVal, int newVal) {
	            
	        }
	    });
	    
	    okBtn.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
//	            editBirthday.setText(String.valueOf(np.getValue()));
//	            birthdayDialog.dismiss();
	        	sendMSG();
	        	
	        }
	    });
	    cancelBtn.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	finish();
	        }
	    });
	 
	}
	
	private void sendMSG(){		// Send a message to MainActivity
		Intent myIntent = new Intent();
		myIntent.putExtra("hour", String.valueOf(np_h.getValue()));
		myIntent.putExtra("min", String.valueOf(np_m.getValue()));
		myIntent.putExtra("sec", String.valueOf(np_s.getValue()));
		this.setResult(RESULT_OK, myIntent);
		this.finish();
	}
	 
	private void setDividerColor(NumberPicker picker, int color) {
	    java.lang.reflect.Field[] pickerFields = NumberPicker.class.getDeclaredFields();
	    for (java.lang.reflect.Field pf : pickerFields) {
	        if (pf.getName().equals("mSelectionDivider")) {
	            pf.setAccessible(true);
	            try {
	                ColorDrawable colorDrawable = new ColorDrawable(color);
	                pf.set(picker, colorDrawable);
	            } catch (IllegalArgumentException e) {
	                e.printStackTrace();
	            } catch (Resources.NotFoundException e) {
	                e.printStackTrace();
	            } catch (IllegalAccessException e) {
	                e.printStackTrace();
	            }
	            break;
	        }
	    }
	}

}
