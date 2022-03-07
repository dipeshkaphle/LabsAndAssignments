package com.lab3;

import java.io.IOException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/results")
public class ExamServer extends HttpServlet {

    public int getScore(List<String> clientAns) {
        int score = 0;
        for (int idx = 0; idx < clientAns.size(); idx++) {
            if (clientAns.get(idx) == null)
                continue;
            if (clientAns.get(idx).equals(Login.questions.get(idx).ans))
                score = score + 1;
        }
        return score;

    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Preprocess request: we actually don't need to do any business stuff, so just
        // display JSP.
        request.getRequestDispatcher("/exam-result.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        Map<String, String> messages = new HashMap<String, String>();
        request.setAttribute("messages", messages);

        try {

            String user = request.getParameter("username");
            String rollno = request.getParameter("rollno");
            List<String> clientAnswers = Arrays.asList(request.getParameter("0"), request.getParameter("1"),
                    request.getParameter("2"), request.getParameter("3"), request.getParameter("4"));
            int score = getScore(clientAnswers);

            Account acc = new Account();
            acc.setRollno(rollno);
            acc.setUser(user);

            AccountDB accDAO = new AccountDB();
            if (accDAO.updateScore(acc, score) >= 0) {
                messages.put("rollno", rollno);
                messages.put("username", user);
                messages.put("score", String.valueOf(score));
            } else
                messages.put("Error", "Score Update Error. Retake Test");

        } catch (Exception e) {
            messages.put("Error", e.toString());
        }

        if (messages.get("Error") != null)
            request.getRequestDispatcher("index.jsp").forward(request, response);

        request.getRequestDispatcher("/exam-result.jsp").forward(request, response);
    }

}