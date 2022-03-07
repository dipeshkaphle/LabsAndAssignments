package com.lab3;

import java.io.IOException;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/viewTest")
public class Login extends HttpServlet {
    public static List<Question> questions;

    @Override
    public void init() throws ServletException {
        try {
            try (Connection conn = DBConnection.initializeDatabase();
                    Statement stmt = conn.createStatement();) {
                String sql = "select * from Question";
                ResultSet rs = stmt.executeQuery(sql);
                questions = new ArrayList<Question>();
                while (rs.next()) {
                    // Question q = new Question();
                    String question = rs.getString("question");
                    String option1 = rs.getString("option1");
                    String option2 = rs.getString("option2");
                    String option3 = rs.getString("option3");
                    String option4 = rs.getString("option4");
                    String answer = rs.getString("answer");
                    questions.add(new Question(question, option1, option2, option3, option4, answer));
                }
                System.out.println("Questions Fetched successfully");
            } catch (SQLException e) {
                System.out.println("Error with Fetching Questions");
                e.printStackTrace();
            }
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.getRequestDispatcher("index.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        Map<String, String> messages = new HashMap<String, String>();
        request.setAttribute("messages", messages);
        if (messages.get("Error") != null)
            messages.clear();

        try {
            String user = request.getParameter("username");
            String password = request.getParameter("password");
            String rollno = request.getParameter("rollno");

            Account acc = new Account();
            acc.setRollno(rollno);
            acc.setScore(0);
            acc.setPassword(password);
            acc.setUser(user);

            AccountDB accDAO = new AccountDB();
            if (accDAO.checkAccount(acc)) {
                messages.put("rollno", rollno);
                messages.put("username", user);
            } else
                messages.put("Error", "Account not Found");

        } catch (Exception e) {
            // TODO: handle exception
            messages.put("Error", e.toString());
        }

        if (messages.get("Error") != null)
            request.getRequestDispatcher("index.jsp").forward(request, response);
        else {
            request.getRequestDispatcher("/quiz.jsp").forward(request, response);
        }
    }

}
