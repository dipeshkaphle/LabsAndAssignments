
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ page import="java.io.*" %>
    <%@ page import="java.util.*" %>
    <!DOCTYPE html>
    <html lang="en">

    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link href="styles.css" rel="stylesheet">
     <title>Quiz</title>
    </head>
<%
            String javascript = "";
            javascript+= "var pageno = 0;\n";
            javascript+= "var maxpages= " + (com.lab3.Login.questions.size()) + ";\n";
            javascript+= "document.getElementById('q0').hidden=false;\n";
            
            String allTheQns = "";
            int i = 0;

            for (com.lab3.Question qn : com.lab3.Login.questions) {
                allTheQns += String.format("<div class='box m-3' id='q%d' hidden=true>",i);
                allTheQns += String.format("<p>Question %d : %s ?</p>",i, qn.qn);
                
                allTheQns += "<div class='form-check'>";
                allTheQns += String.format("<input class='form-check-input' type='radio'  name=\"%d\" value=\"%s\">",
                        i, qn.o1);
                allTheQns += String.format("<input type='text' class='form-control' value='%s' disabled>", qn.o1);
                allTheQns += "</div>";
            
            
                allTheQns += "<div class='form-check'>";
                allTheQns += String.format("<input class='form-check-input' type='radio'  name=\"%d\" value=\"%s\">",
                        i, qn.o2);
                allTheQns += String.format("<input type='text' class='form-control' value='%s' disabled>", qn.o2);
                allTheQns += "</div>";
            
            
                allTheQns += "<div class='form-check'>";
                allTheQns += String.format("<input class='form-check-input' type='radio'  name=\"%d\" value=\"%s\">",
                        i, qn.o3);
                allTheQns += String.format("<input type='text' class='form-control' value='%s' disabled>", qn.o3);
                allTheQns += "</div>";
            
            
                allTheQns += "<div class='form-check'>";
                allTheQns += String.format("<input class='form-check-input' type='radio'  name=\"%d\" value=\"%s\">",
                        i, qn.o4);

                allTheQns += String.format("<input type='text' class='form-control' value='%s' disabled>", qn.o4);
                allTheQns += "</div>";

                allTheQns += "</div>";

                i = i + 1;
            }

%>

    <body >
        <nav class="navbar navbar-light" style="background-color:darkslategrey;">
            <div class=" container-fluid "  >
                <p class="navbar-brand m-3">Maths Quiz</p>
                <div class="d-flex">
                    <p class="navbar-brand m-3">${messages.username}</p>
                    <p class="navbar-brand m-3">${messages.rollno}</p>
                </div>
            </div>
        </nav>

        <div class="container h-100" >
            <div class="row h-100 justify-content-center">
                <form name="examForm " method="post" action="./results">
                    <%= allTheQns %>
                    <input type="text" class="form-control mx-0" id="username" name="username" value=${messages.username} hidden>
                    <input type="text" class="form-control mx-0" id="rollno" name="rollno" value=${messages.rollno} hidden>
                    <div class="box m-3 my-5 ">
                        <button type="submit " class="btn btn-primary btn-block ">Submit Your Answers!</button>
                    </div>
                </form>

            </div>

        </div>
        <div class="row justify-content-center">
            <nav aria-label="Page navigation example">
              <ul class="pagination">
                <li class="page-item"><button class="page-link" onclick="prev()" >Previous</button></li>
                <li class="page-item"><button class="page-link" onclick="next()">Next</button></li>
              </ul>
            </nav>
        </div>
    </body>
    <script>
        <%= javascript %>
        function next() {
          pageno++;
          if (pageno >= maxpages) {
            pageno = maxpages - 1;
          }
          for (let i = 0; i < maxpages; i++) {
            document.getElementById("q" + i).hidden = true;
          }
          document.getElementById("q" + pageno).hidden = false;
        }
        function prev() {
          pageno--;
          if (pageno < 0) {
            pageno = 0;
          }
          for (let i = 0; i < maxpages; i++) {
            document.getElementById("q" + i).hidden = true;
          }
          document.getElementById("q" + pageno).hidden = false;
        }
    </script>


    </html>