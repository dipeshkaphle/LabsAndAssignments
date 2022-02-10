package com.Lab2;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/register")
public class Register extends HttpServlet {

    public void init() {
        if (HitCounter.hitCount == -1) {
            HitCounter.hitCount = 0;
        }
    }

    // stores all the userss
    // public static HashMap<String, String> users = new HashMap<String,
    // String>();

    public void processRequest(HttpServletRequest request,
            HttpServletResponse response) throws IOException {
        response.setContentType("text/html;charSet=UTF-8");
        PrintWriter out = response.getWriter();
        try {
            String user = request.getParameter("username");
            String password = request.getParameter("password");
            String confirmPassword = request.getParameter("confirm-password");
            if (Users.all_users.containsKey(user)) {
                response.sendRedirect("register.html");
            } else {
                if (password.equals(confirmPassword)) {
                    Users.all_users.put(user, password);
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
                    out.println("          <h1>Welcome " + user + " </h1>");
                    out.println("        </div>");
                    out.println("        <div class=\"btn-container\">");
                    out.println(
                            "          <a href=\"./login\" class=\"btn\">Sign In</a>");
                    out.println("        </div>");
                    out.println("      </div>");
                    out.println("    </div>");
                    out.println("  </body>");
                    out.println("</html>");
                } else {
                    response.sendRedirect("register.html");
                }
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
}
