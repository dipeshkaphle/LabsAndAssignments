package com.Lab2;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;

@WebServlet("/HitCounter")
public class HitCounter extends HttpServlet {
    static int hitCount = -1;

    public void init() {
        if (hitCount == -1) {
            hitCount = 0;
        }
    }

    @Override
    public void doGet(javax.servlet.http.HttpServletRequest request,
            javax.servlet.http.HttpServletResponse response)
            throws javax.servlet.ServletException, java.io.IOException {
        hitCount++;
        response.getWriter()
                .println(String.format("Number of hits: %d", hitCount));
    }
}