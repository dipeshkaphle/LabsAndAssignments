package com.lab3;

public class Account {
    private String user; 
    private String password;
    private String rollno;
    private int score;
    
    public String getUser() {
        return user;
    }
    public void setUser(String user) {
        this.user = user;
    }
    public String getRollno() {
        return rollno;
    }
    public int getScore() {
        return score;
    }
    public void setScore(int score) {
        this.score = score;
    }
    public void setRollno(String rollno) {
        this.rollno = rollno;
    }
    public String getPassword() {
        return password;
    }
    public void setPassword(String password) {
        this.password = password;
    }     
}
