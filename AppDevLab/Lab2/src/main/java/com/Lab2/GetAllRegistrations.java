package com.Lab2;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.Lab2.Users.RegInfo;

@WebServlet("/AllRegistrations")
public class GetAllRegistrations extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {

        PrintWriter out = resp.getWriter();
        out.println("All Registrations as of now:");
        for (String uname : Users.regMap.keySet()) {
            out.println("For User:" + uname);
            for (RegInfo regInfo : Users.regMap.get(uname)) {
                out.println("\t-" + regInfo.toString());
            }
        }
    }

}
