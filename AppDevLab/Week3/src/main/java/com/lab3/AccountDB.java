package com.lab3;

import java.sql.*;

public class AccountDB {

    // CRUD Operations for the DAO
    public boolean checkAccount(Account acc) {
        int count = 0;
        Connection conn;
        try {
            conn = DBConnection.initializeDatabase();
            System.out.println("Connected to the SQL server successfully.");
            String selectQuery = "select * from Student where username = ? and password = ? and rollno = ?;";
            PreparedStatement pstmt = conn.prepareStatement(selectQuery);
            pstmt.setString(1, acc.getUser());
            pstmt.setString(2, acc.getPassword());
            pstmt.setString(3, acc.getRollno());
            ResultSet rs = pstmt.executeQuery();
            while (rs.next())
                count++;

        } catch (Exception e) {
            System.out.print(e.getMessage());
        }
        if (count > 0)
            return true;
        return false;
    }

    public boolean addAccount(Account acc) {
        boolean flag = true;
        Connection conn;
        try {
            conn = DBConnection.initializeDatabase();
            System.out.println("Connected to the SQL server successfully.");
            String addQuery = "insert into Student (username, password) values ('" + acc.getUser() + "', '"
                    + acc.getPassword() + "');";
            PreparedStatement pstmt = conn.prepareStatement(addQuery);
            pstmt.executeUpdate();
        } catch (Exception e) {
            System.out.print(e.getMessage());
            flag = false;
        }
        return flag;
    }

    public int updateScore(Account acc, int score) {
        String updateQuery = "update Student " + "set score = ? " + "where username = ?";
        Connection conn;
        int affectedrows = 0;

        try {
            conn = DBConnection.initializeDatabase();
            PreparedStatement pstmt = conn.prepareStatement(updateQuery);
            System.out.println("Connected to the SQL server successfully.");
            pstmt.setInt(1, score);
            pstmt.setString(2, acc.getUser());
            affectedrows = pstmt.executeUpdate();

        } catch (SQLException | ClassNotFoundException ex) {
            System.out.println(ex.getMessage());
        }
        return affectedrows;
    }

    public static void main(String arg[]) {
        Account acc = new Account();
        acc.setPassword("pass");
        acc.setUser("Dipesh");
        acc.setRollno("106119029");
        boolean x = new AccountDB().checkAccount(acc);
        System.out.print(x);
    }
}
