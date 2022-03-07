package com.lab3;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/getAllResults")
public class GetAllResults extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            try (Connection conn = DBConnection.initializeDatabase();
                    Statement stmt = conn.createStatement();) {

                PrintWriter pw = resp.getWriter();

                pw.println("<head>");
                pw.println("<meta charset=\"UTF-8\">");
                pw.println("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
                pw.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
                pw.println("<link href=\"styles.css\" rel=\"stylesheet\">");
                pw.println("<title>Quiz Scores</title>");
                pw.println("</head>");

                pw.println("<table class=\"table table-striped\">");
                pw.println("<thead>");
                pw.println("<tr>");
                pw.println("<th scope=\"col\">Roll</th>");
                pw.println("<th scope=\"col\">Name</th>");
                pw.println("<th scope=\"col\">Score</th>");
                pw.println("</tr>");
                pw.println("</thead>");
                pw.println("<tbody>");

                String sql = "select * from accounts;";
                ResultSet rs = stmt.executeQuery(sql);
                while (rs.next()) {
                    String username = rs.getString("username");
                    String score = rs.getString("score");
                    String rollno = rs.getString("rollno");
                    if (score == null)
                        score = "null";

                    pw.println("<tr>");
                    pw.println("<td>" + rollno + "</td>");
                    pw.println("<td>" + username + "</td>");
                    pw.println("<td>" + score + "</td>");
                }
                pw.println("</tbody>");
                pw.println("</table>");
            } catch (SQLException e) {
                e.printStackTrace();
            }
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

    }
}
