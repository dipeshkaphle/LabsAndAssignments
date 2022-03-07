package com.lab3;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

// This class can be used to initialize the database connection
public class DBConnection {

    static String url = "jdbc:mysql://db:3306/";
    static String user = "root";
    static String password = "password";
    static String db = "db";
    static String dbDriver = "com.mysql.jdbc.Driver";

    public static Connection initializeDatabase()
            throws SQLException, ClassNotFoundException {
        Class.forName(dbDriver);
        Connection con = DriverManager.getConnection(url + db, user,
                password);
        return con;
    }
}
