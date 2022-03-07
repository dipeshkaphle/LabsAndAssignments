
    <!DOCTYPE html>
    <html lang="en">

    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link href="styles.css" rel="stylesheet" >
        <title>Quiz Result</title>
    </head>

    <body style="background-color: darkslategrey ;">
        <section class="vh-100">
            <div class="container py-5 h-100">
                <div class="row d-flex justify-content-center align-items-center h-100">
                    <div class="col-12 col-md-8 col-lg-6 col-xl-5">
                        <div class="card shadow-2-strong" style="border-radius: 1rem;">
                            <div class="card-body p-5 text-center">
                                <h4 class="mb-4">Results</h4>
                                <div class="form-outline mb-4">
                                    <div class="input-group mb-3">
                                        <span class="w-25 justify-content-center " >Username</span>
                                        <input type="text" class="form-control mx-0" aria-label="Username" id="username" name="username" value=${messages.username} disabled>
                                    </div>
                                    <div class="input-group mb-3">
                                        <span class="w-25 justify-content-lg-center " >Roll No</span>
                                        <input type="text" class="form-control mx-0" aria-label="Roll No" id="rollno" name="rollno" value=${messages.rollno} disabled>
                                    </div>
                                    <div class="input-group mb-3">
                                        <span class="w-25 justify-content-lg-center " >Score</span>
                                        <input type="text" class="form-control mx-0" aria-label="Score" id="score" name="score" value=${messages.score} disabled>
                                    </div>
                                </div>
                                <form action="index.jsp" method="get">
                                    <button class="btn btn-primary btn-block" id="loginBtn" type="submit">Go Back to Login Page</button>
                                </form>

                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </section>
    </body>

    </html>