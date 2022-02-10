package com.Lab2;

import java.util.ArrayList;
import java.util.HashMap;

public class Users {

    public static class RegInfo {
        String coursename;
        String sem;
        String year;

        public RegInfo(String coursename, String sem, String year) {
            this.coursename = coursename;
            this.sem = sem;
            this.year = year;
        }

        @Override
        public String toString() {
            return "RegInfo [coursename=" + coursename + ", sem=" + sem
                    + ", year=" + year + "]";
        }
    }

    // Usernames are mapped to values
    public static HashMap<String, String> all_users = new HashMap<>();
    // Hash of strings are mapped to strings
    public static HashMap<String, String> sessionMap = new HashMap<>();

    // HashMap of all the registrations of a user
    public static HashMap<String, ArrayList<RegInfo>> regMap = new HashMap<>();
}
