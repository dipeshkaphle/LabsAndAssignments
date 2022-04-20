package com.example.lab6



import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.Switch;
import android.widget.Toast;

import java.util.HashMap;
class MenuActivity : AppCompatActivity(), AdapterView.OnItemSelectedListener {
    lateinit var typeOfMenu : Spinner
    lateinit var drinksSpinner : Spinner
    lateinit var startersSpinner: Spinner
    lateinit var mainDishSpinner: Spinner
    lateinit var dessertsSpinner: Spinner

    var selectedOptions: HashMap<String, String> = HashMap()

    lateinit var orderBtn: Button


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_menu)
        typeOfMenu = findViewById(R.id.typeOfMenu)
        drinksSpinner =  findViewById(R.id.drinks_spinner)
        startersSpinner = findViewById(R.id.starters_spinner)
        mainDishSpinner = findViewById(R.id.maindish_spinner)
        dessertsSpinner = findViewById(R.id.desserts_spinner)


        makeSelectMenu(typeOfMenu,R.array.menu_types)
        makeSelectMenu(drinksSpinner,R.array.drinks)
        makeSelectMenu(startersSpinner,R.array.starters)
        makeSelectMenu(mainDishSpinner,R.array.main_dishes)
        makeSelectMenu(dessertsSpinner,R.array.desserts)


        orderBtn =  findViewById(R.id.order_btn)

        orderBtn.setOnClickListener {
            val intent= Intent(this, OrderActivity::class.java)
            intent.putExtra("selected_menu_type",selectedOptions.get("selected_menu_type"))
            intent.putExtra("selected_drink",selectedOptions.get("selected_drink"))
            intent.putExtra("selected_starter",selectedOptions.get("selected_starter"))
            intent.putExtra("selected_main_dish",selectedOptions.get("selected_main_dish"))
            intent.putExtra("selected_dessert",selectedOptions.get("selected_dessert"))
            startActivity(intent)
        }
    }

    fun makeSelectMenu(spinner: Spinner, textArrayResId: Int){

        val adapter = ArrayAdapter.createFromResource(
            this,
            textArrayResId,
            android.R.layout.simple_spinner_item
        )
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        spinner.adapter = adapter
        spinner.onItemSelectedListener= this
    }


    override fun onItemSelected(parent: AdapterView<*>, view: View?, position: Int, id: Long) {
        var objectKey = ""
        when (parent.id) {
            R.id.typeOfMenu -> objectKey = "selected_menu_type"
            R.id.drinks_spinner -> objectKey = "selected_drink"
            R.id.starters_spinner -> objectKey = "selected_starter"
            R.id.maindish_spinner -> objectKey = "selected_main_dish"
            R.id.desserts_spinner -> objectKey = "selected_dessert"
        }
        selectedOptions[objectKey] = parent.getItemAtPosition(position).toString()
    }

    override fun onNothingSelected(parent: AdapterView<*>?) {}
}


