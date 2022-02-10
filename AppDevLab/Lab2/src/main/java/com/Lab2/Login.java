package com.Lab2;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class Login extends HttpServlet {
    public void init() {
        if (HitCounter.hitCount == -1) {
            HitCounter.hitCount = 0;
        }
    }

    public void processRequest(HttpServletRequest request,
            HttpServletResponse response) throws IOException {
        response.setContentType("text/html;charSet=UTF-8");
        PrintWriter out = response.getWriter();
        try {
            String user = request.getParameter("username");
            String password = request.getParameter("password");
            if (Users.all_users.containsKey(user)) {
                if (Users.all_users.get(user).equals(password)) {
                    Users.sessionMap.put(Integer.toString(user.hashCode()),
                            user);
                    out.println("<html lang=\"en\">");
                    out.println("  <head>");
                    out.println(
                            "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />");
                    out.println("    <title>Online Registration</title>");
                    out.println(
                            "    <link rel=\"stylesheet\" href=\"css/main.css\" />");
                    out.println("  </head>");
                    out.println("  <body>");
                    out.println("    <div class=\"wrapper\">");
                    out.println("      <div class=\"form\">");
                    out.println("        <div class=\"heading\">");
                    out.println("          <h1>Course Form</h1>");
                    out.println("          <h3>Welcome " + user + "</h3>");
                    out.println("        </div>");
                    out.println(
                            "        <form action=\"./course\" method=\"post\">");
                    out.println(
                            "          <label class=\"input-label hidden\"> Username </label>");
                    out.println(
                            "          <input type=\"text\" name=\"username\" class=\"input-field hidden\" value=\""
                                    + Integer.toString(user.hashCode())
                                    + "\"/>");
                    out.println(
                            "          <label class=\"input-label\"> Roll No </label>");
                    out.println(
                            "          <input type=\"text\" name=\"rollno\" class=\"input-field\" />");
                    out.println(
                            "          <label class=\"input-label\"> Year </label>");
                    out.println(
                            "          <input type=\"text\" name=\"year\" class=\"input-field\" />");
                    out.println(
                            "          <label class=\"input-label\"> Semester </label>");
                    out.println(
                            "          <input type=\"text\" name=\"semester\" class=\"input-field\" />");
                    out.println(
                            "          <label class=\"input-label\"> Course </label>");
                    out.println(
                            "          <input type=\"text\" name=\"course\" class=\"input-field\" />");
                    out.println("          <div class=\"btn-container\">");
                    out.println(
                            "            <button type=\"submit\" class=\"btn submit\">Submit</button>");
                    out.println("          </div>");
                    out.println("        </form>");
                    out.println("      </div>");
                    out.println("    </div>");
                    out.println("  </body>");
                    out.println("</html>");
                } else {
                    response.sendRedirect("login");
                }
            } else {
                response.sendRedirect("login");
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            out.close();
        }
    }

    @Override
    public void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        HitCounter.hitCount++;
        processRequest(req, resp);
    }

    public void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        HitCounter.hitCount++;
        PrintWriter out = resp.getWriter();
        out.println("<html lang=\"en\">");
        out.println("  <head>");
        out.println(
                "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />");
        out.println("    <title>Online Registration</title>");
        out.println("    <link rel=\"stylesheet\" href=\"css/main.css\" />");
        out.println("  </head>");
        out.println("  <body>");
        out.println("    <div class=\"wrapper\">");
        out.println("      <div class=\"form\">");
        out.println("        <div class=\"heading\">");
        out.println("          <h1>Login</h1>");
        out.println("          <h3> Number of Total Hits : "
                + HitCounter.hitCount + "</h3>");
        out.println("        </div>");
        out.println("        <form action=\"./login\" method=\"post\">");
        out.println(
                "          <label class=\"input-label\"> Username </label>");
        out.println(
                "          <input type=\"text\" name=\"username\" class=\"input-field\" />");
        out.println(
                "          <label class=\"input-label\"> Password </label>");
        out.println(
                "          <input type=\"password\" name=\"password\" class=\"input-field\" />");
        out.println("          <div class=\"btn-container\">");
        out.println(
                "            <button type=\"submit\" class=\"btn submit\">Sign In</button>");
        out.println(
                "            <a href=\"./register.html\" class=\"btn\">Sign Up</a>");
        out.println("          </div>");
        out.println("        </form>");
        out.println("      </div>");
        out.println("    </div>");
        out.println("  </body>");
        out.println("</html>");
    }

}
