package com.Lab2;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.Lab2.Users.RegInfo;

@WebServlet("/course")
public class Course extends HttpServlet {
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
            String userNameHash = request.getParameter("username");
            String user = Users.sessionMap.get(userNameHash);
            Users.sessionMap.remove(userNameHash);

            if (user == null) {
                out.println("<h1>You are not logged in!</h1>");
                out.println("<a href=\"login.html\">Login</a>");
                return;
            }
            String course = request.getParameter("course");
            String sem = request.getParameter("semester");
            String year = request.getParameter("year");
            RegInfo regInfo = new RegInfo(course, sem, year);
            if (Users.regMap.containsKey(user)) {
                Users.regMap.get(user).add(regInfo);
            } else {
                ArrayList<RegInfo> regInfoList = new ArrayList<RegInfo>();
                regInfoList.add(regInfo);
                Users.regMap.put(user, regInfoList);
            }

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
            out.println("          <h3>Course Registered Sucessfully</h3>");
            out.println("        </div>");
            out.println("      </div>");
            out.println("    </div>");
            out.println("  </body>");
            out.println("</html>");
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
