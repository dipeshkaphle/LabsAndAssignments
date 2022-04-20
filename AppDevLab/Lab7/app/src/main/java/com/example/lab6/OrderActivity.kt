package com.example.lab6

import android.os.Bundle
import android.view.View
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity


class OrderActivity : AppCompatActivity() {
    var selectedOptions = HashMap<String, String>()
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_order)
        val selected_menu_type = findViewById<View>(R.id.selected_menu_type) as TextView
        val selected_drink = findViewById<View>(R.id.selected_drink) as TextView
        val selected_starter = findViewById<View>(R.id.selected_starter) as TextView
        val selected_main_dish = findViewById<View>(R.id.selected_main_dish) as TextView
        val selected_dessert = findViewById<View>(R.id.selected_dessert) as TextView
        val extras = intent.extras
        if (extras != null) {
            selected_menu_type.text = extras.getString("selected_menu_type")
            selected_drink.text = extras.getString("selected_drink")
            selected_starter.text = extras.getString("selected_starter")
            selected_main_dish.text = extras.getString("selected_main_dish")
            selected_dessert.text = extras.getString("selected_dessert")
        }
    }
}
