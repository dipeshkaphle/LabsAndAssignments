
    <!DOCTYPE html>
    <html lang="en">

    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link href="styles.css" rel="stylesheet" >
        <style>
            .error {
                color: red;
            }
            
            .success {
                color: green;
            }
        </style>
        <title>Login in to Test Portal</title>
    </head>

    <body style="background-color:darkslategrey ;">
        <section class="vh-100" >
            <div class="container py-5 h-100">
                <div class="row d-flex justify-content-center align-items-center h-100">
                    <div class="col-12 col-md-8 col-lg-6 col-xl-5">
                        <div class="card shadow-2-strong" style="border-radius: 1rem;">
                            <div class="card-body p-5 text-center">
                                <h4 class="mb-4">Sign in</h4>
                                <form action="./viewTest" method="post">
                                    <div class="form-outline mb-4">
                                        <div class="input-group mb-3">
                                            <span class="w-25 justify-content-center " >Username</span>
                                            <input type="text" class="form-control mx-0" aria-label="Username" id="username" name="username" required>
                                        </div>
                                        <div class="input-group mb-3">
                                            <span class="w-25 justify-content-lg-center " >Roll No</span>
                                            <input type="text" class="form-control mx-0" aria-label="Password" id="rollno" name="rollno" required>
                                        </div>
                                        <div class="input-group mb-3">
                                            <span class="w-25 justify-content-lg-center " >Password</span>
                                            <input type="password" class="form-control mx-0" aria-label="Password" id="password" name="password" required>
                                        </div>
                                    </div>
                                    <button class="btn btn-primary btn-block" type="submit">Login</button>
                                </form>
                                <span class="error">${messages.Error}</span>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </section>
    </body>

    </html>