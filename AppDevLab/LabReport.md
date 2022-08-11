---
title: AppDev Lab Report
author: 106119029 Dipesh Kafle
bibliography: "bibliography.bib"
link-citations: true
geometry: margin=1cm
toc: true
urlcolor: blue
---

## Ex No: 1

### Problem Statement

Create a web page for user registration using HTML, CSS. Validate the details entered using JavaScript.
When the user clicks on “Submit” button, validate all entries with the following sample conditions.  

1. Name should contain only alphabets 
2. Email should have a format of xyz@gmail.com 
3. Password must be of specific length and should contain alphabets, numbers, special characters 
4. Mobile number should be of length 10 (Insert country code if required with additional length) 

### Design

![](./pics/1_archi.png)

### Tools Used

- HTML
- CSS
- JavaScript

### Code

[Link](https://drive.google.com/file/d/1Pjy88P9bjsulvClYfYzLQ-hGavdAlIo8/view?usp=sharing)

### Screenshots of Application

 ![](./pics/1_1.png){width=50%}  ![](./pics/1_2.png){width=50%} 

| On Valid Input                 |  Giving invalid input(non matching pass) |
| :----------------------------- | ------------------------------ |
| ![](./pics/1_3.png){width=50%} | ![](./pics/1_4.png){width=50%}

| On invalid input               | On pressing clear button              |
| :----------------------------- | ------------------------------------- |
| ![](./pics/1_5.png){width=50%} | ![](./pics/1_6.png){width=50%}

## Ex No: 2

### Problem Statement

Course Registration App

1. Create a Login HTML file with given field :

- Username
- Password
- Sign Up Button
- Sign In Button

i. Sign Up Procedure

    a. Write a java program to invoke servlets from the Sign Up HTML file

    b. At the click of Submit button, the below dialog box should be displayed
    and data should be stored in the database.
    Welcome Username

ii. Sign In Procedure

    a. Login through the Sign In HTML form and write a java program for session
    tracking using Hidden field form. When you hit the “Sign In” button control
    should go to “Course registration” form and your session should start.

    b. Create a Course registration HTML file as below. Create a Hidden form field
    which should take the username from the Sign In HTML file and display it
    in the dialog box.
    `Welcome Username`

    c. Create a dialog box that takes username from the course registration form
    and displays it. `Welcome Username`

2. Write a java program to track sessions for a hit count using life cycle of a servlet

   i. Initialize global variable in init() method.

   ii. Increase the global variable everytime when you trigger doGet() method or
   doPost() method.

   iii. Display the total number of HITS in the browser whenever you call the Login
   HTML file.

### Design

![](./pics/architecture.png)

### Tools Used

- Java
- Maven for package management and building code
- Apache Tomcat
- HTML
- Visual Studio Code for code editing
- Docker

### Code

[Link](https://drive.google.com/file/d/1p62QR4HOqUuFMekYvBxW0_SMZ_k4gZ6r/view?usp=sharing)

### Screenshots of Application

| index.html              |
| :---------------------- |
| ![](./pics/index.png) |

| Signup Page                   |
| :---------------------------- |
| ![](./pics/signup.html.png) |

| Registering User Dipesh             |
| :---------------------------------- |
| ![](./pics/registeringDipesh.png) |

| On Successful Registration        |
| :-------------------------------- |
| ![](./pics/pageAfterSignUp.png) |

| Login Page (Shows the Hit Count till now as well) |
| :------------------------------------------------ |
| ![](./pics/login.png)                           |

| Logging in as Dipesh          |
| :---------------------------- |
| ![](./pics/LoginDipesh.png) |

| Course Registration Form with Hidden Field for Session Management |
| :---------------------------------------------------------------- |
| ![](./pics/CourseFormWithHiddenField.png)                       |

| Registering for a course         |
| :------------------------------- |
| ![](./pics/RegisterCourse.png) |

| Successful Registration            |
| :--------------------------------- |
| ![](./pics/CourseRegSuccess.png) |

| A get route to see all the registered users |
| :------------------------------------------ |
| ![](./pics/AllUsersList.png)              |

| A get route to see all the courses registered |
| :-------------------------------------------- |
| ![](./pics/AllRegistrations.png)            |

## Ex No: 3

### Problem Statement
Write programs in Java to create three-tier applications using JSP and Databases 
1. for conducting on-line examination.
2. for displaying student mark list. Assume that student information is available in database which has been stored in a database server.

- Procedure for creating design of client and server program 

1. Design the HTML page (Exam_Client.html) with thefollowing
    - Create a form to get the input from the user.
    - Use radio buttons to make various options for the questions
    - Set the URL of the server (Exam_Server.jsp) as the value of the action attribute.
    - Use submit button to invoke the server and send the form data to the server.

2. Create the JSP file with the following
    - Read the input from the client.
    - Retrieve the answers from the database.
    - Match the answers from the user with the correct answers from the database table.
    - For each correct answer increment the mark by 1.
    - Server displays the mark and result to the client as a response.

- Form Design 

1. Step1 :Create a database in MS-Accessor MySQL. For instance, you have to create a student database (min 15 students) inMS-Access or MySQL. Inside this database create a tablewith following fields. 
    - S.No
    - Roll Number
    - Name of Student
    - Marks
2. Step 2: Write a JSP document as following form format with style CSS format to conduct online exam and Validation (The form validation is also done in above JSP script)

### Design

![](./pics/lab3_design.png)

### Tools Used

- Java
- SQL
- Docker
- PhpMyAdmin
- Tomcat
- Maven for package management and building code

### Code

[Link](https://drive.google.com/file/d/1pJSmzBCXbejKpViBfYtkt7C7El5zzUlX/view?usp=sharing)

### Screenshots of Application

| Accounts in DB       |
| :------------------- |
| ![](./pics/3_db.png) |


|   Login with Student Dipesh |
| :------------------- |
| ![](./pics/3_1.png) |

|                    2 of the Question    |
| :------------------- | ---------   |
| ![](./pics/3_2.png){width=50%} | ![](./pics/3_3.png){width=50%}  |


|  Result of the given test of student Dipesh |
| :------------------- |
| ![](./pics/3_res.png) |


| All the results of students in table format |
| :------------------- |
| ![](./pics/3_getAllResults.png) |

## Ex No: 4

### Problem Statement
STUDENT REGISTRATION FOR TECHNICAL EVENTS

Create a web portal for student registration for various events in college technical festivals using ajax.

- The registration can be done through an HTML form.
- Each event has a 100/- fee and can be selected using the radio buttons.
- Based on the number of events selected, the total fee amount is generated automatically(using AJAX).
- While pressing ADD, the details should be stored in the database and the details should be visible under the Registration Summary, as the example given, using AJAX.
- The form and summary should be on the same page.
- In Summary, when an entry needs to be edited, the form should be filled automatically,based on which entry needs to be edited. After editing, the changes should be visible on the page(using AJAX) and database.
- A registration can be deleted from the registration summary, and effect should appear inthe database.

### Design

![](./pics/lab4_design.png)

### Tools Used

- NodeJS
- Docker
- HTML
- CSS
- MongoDB

### Code

[Link](https://drive.google.com/file/d/1ByndNQ2JBbmcCzdo3b6soMS8-Jt5CXR1/view?usp=sharing)

### Screenshots of Application

![](./pics/4_1.png)

| Registering Dipesh For Event |
| :---------------- |
| ![](./pics/4_2.png) |

| Registering for XYZ and Dipesh Registration shows up in side |
| :---------------- |
| ![](./pics/4_3.png) |


| XYZ's and Dipesh' Registration shows up in side |
| :---------------- |
| ![](./pics/4_4.png) |

| Clicking on edit button for XYZ's registration |
| :---------------- |
| ![](./pics/4_editbtn.png) |

| Changing events for registration |
| :---------------- |
| ![](./pics/4_change.png) |

| Registration is updated and it shows in sidebar |
| :---------------- |
| ![](./pics/4_changed.png) |


## Ex No: 5

### Problem Statement

Create an online shopping web application using HTML, Javascript and Database:  

Basic Features of the APP: 

- Only registered user can place orders 

- Registration required for new users 

- The frontend should have three modules : Search, Categories and Top Selection 

- Search module lets the user to search for the Main product (Ex. Clothing) 

- Categories module lets the user to choose different categories (Ex. Men, Women, Children) 

- Top Selection module displays product name, product ID, rating, price, quantity in-stock  

The backend should have five modules: Administrator, Producer, Individual customer, Business and Logistics 

- Administrator module monitors the entire application  

- Producer can add and delete products (include product details while adding) 

- Individual customer makes simple purchase orders and provide address for delivery 

- Business person makes bulk purchase orders and should provide their address and the items they are dealing with 

- Logistics module provides information about potential suppliers, accessibility and shipping details 

The application should provide the following functionalities: 

- Add to cart option for the customer  

- Should be able to see if the item is in-stock and the supplier details 

- Discount coupons using supercoins 

- Able to check the in-voice generated 

### Design

![](./pics/lab5_design.png)

### Tools Used

- Typescript 
- React
- Docker
- FastAPI Python
- Mongo DB

### Code

[Link](https://drive.google.com/file/d/1IuxL3ezj-Q4jhMRAgPXRfZYtO2m_kPaR/view?usp=sharing)

### Screenshots of Application

[Demo Link](https://www.loom.com/share/68e9c59cb2064ceb8e6a586865edd607)

## Ex No: 6

### Problem Statement

Create and save an XML document at the server, which contains 10 users Information. Write a Program, which takes user Id as an input and returns the User details by taking the user information from the XML document. 

- The registration should be done by XML. 
- First should create a login page for the users. 
- The user has name should contains only Alphabets and the Password must be of specific length and should contain alphabets, numbers, special characters. 
- The user information should contain at least address, phone number and email. 
- The user information should contain more than 10 users. 
- The data set can be use of students. 
- If the user wants to edit, then valid the user by OTP. OTP generated using random number, it can send to mail or phone. 

### Design

![](./pics/lab6_design.png)

### Tools Used

- NodeJS
- HTML
- CSS
- XML

### Code

[Link](https://drive.google.com/file/d/1vPUZ5b76tYp-CWbHahILMwxCIf6cPV--/view?usp=sharing)

### Screenshots of Application

![](./pics/6_1.png)

| XML DB |
| :------ |
| ![](./pics/6_xmldb_prechange.png) |

| Loggin In with User ABC |
| :------ |
| ![](./pics/6_4.png) |


| Changing username, Password[to correct format(8 char,1 alpha,1 num and 1 symbol)] and email, OTP is sent |
| :--------- |
| ![](./pics/6_6.png) |

| Access OTP | 
| :--------- |
| ![](./pics/6_7.png) |


| Entering OTP | 
| :--------- |
| ![](./pics/6_8.png) |

| Edited Info Successfully | 
| :--------- |
| ![](./pics/6_9.png) |

| After Edit |
| :--------- |
| ![](./pics/6_10.png) |

| XML after the edit |
| :----------------- |
| ![](./pics/6_xmldb_afterchange.png) |

## Ex No: 7

### Problem Statement

Design a Restaurant data entry App using Mobile Applicationin Android Studio

### Design

![](./pics/lab7_design.png)

### Tools Used

- Kotlin
- Android Studio

### Code

[Link](https://drive.google.com/file/d/1txJ1cZJu2My46YAj-2XJ_d_gzz7AgfDL/view?usp=sharing)

### Screenshots of Application

![](./pics/7_1.png)
![](./pics/7_2.png)
![](./pics/7_3.png)
![](./pics/7_4.png)
![](./pics/7_5.png)


## Ex No: 8

### Problem Statement

Create an app for capture image from the camera and store it in database by using Android studio.

1. Using Camera by Using Camera Application
2. Using Camera By using Camera API
3. Camera Permission Declarations in Manifest
4. Camera  Example  in  Android  Studio  by  Using  Camera  Intent  and  storing  the  cameraImage in Local Database

### Design

![](./pics/lab8_design.png)

### Tools Used

- Java
- Android Studio

### Code

[Link](https://drive.google.com/file/d/1lKgiAntKQmCxQ9Jro8ZD5mB95ewMcSKs/view?usp=sharing)

### Screenshots of Application

| ![](./pics/8_1.png){width=50%} | ![](./pics/8_2.png){width=50%}|

|![](./pics/8_3.png){width=50%} | ![](./pics/8_4.png){width=50%}|

## Ex No: 9

### Problem Statement

Create a mobile banking application for user registration. Get username, passwordand Retype password. Verify the registration by sending OTP to the mobile number.

After registration, allow the user to do following activities by sending OTP : 

1. Adding new Beneficiary
2. External Fund transfer
3. Online Bill payment

### Design

![](./pics/lab9_design.png)

### Tools Used

- Kotlin
- Android Studio
- Firebase

### Code

[Link](https://drive.google.com/file/d/1J-2ZWpPGcON8um97c1yeMRGMYvA3VxQA/view?usp=sharing)

### Screenshots of Application

| ![](./pics/9_reg1.jpeg){width=50%} | ![](./pics/9_reg2.jpeg){width=50%} |

| OTP Sent | OTP is added |
| :-------------------------------------------------- | ------------------------------------------------------ |
| ![](./pics/9_reg3.jpeg){width=50%} | ![](./pics/9_reg4.jpeg){width=50%} |


| ![](./pics/9_1.png){width=50%} | ![](./pics/9_2.png){width=50%} |


| ![](./pics/9_3.png){width=50%} | ![](./pics/9_4.png){width=50%} |


| ![](./pics/9_5.png){width=50%} | ![](./pics/9_6.png){width=50%} | 


| ![](./pics/9_7.png){width=50%} | ![](./pics/9_8.png){width=50%} | 


| ![](./pics/9_9.png){width=50%} | ![](./pics/9_10.png){width=50%} |


![](./pics/9_11.png){width=50%}

## Ex No: 10

### Problem Statement

Create an app for a museum that captures the museum labels 
using the phone camera andconverts the contents into speech.
The label may contain text and longitude and latitude. 
The app should recognise the text andlocation details and provide a speech output.

### Design

![](./pics/lab10_design.png)

### Tools Used

- Kotlin
- Android Studio
- Text To Speech
- Image to Text

### Code

[Link](https://drive.google.com/file/d/1Qua9j-9xb_pXgAqcuRYZ3bhaDgVWr-rt/view?usp=sharing)

### Screenshots of Application

| ![](./pics/10_1.jpeg){width=50%} | ![](./pics/10_2.jpeg){width=50%} |


| ![](./pics/10_3.jpeg){width=50%} | ![](./pics/10_4.jpeg){width=50%} |


| ![](./pics/10_5.jpeg){width=50%} | ![](./pics/10_6.jpeg){width=50%} |

## Ex No: 11

### Problem Statement

Write a program to call a number.

### Design


![](./pics/lab11_design.png)

### Tools Used

- Kotlin
- Android Studio

### Code

[Link](https://drive.google.com/file/d/1oNYYs8VgHArz-VmY_BIYtLnFhwFXJ1DI/view?usp=sharing)

### Screenshots of Application

| ![](./pics/11_1.jpeg){width=50%} | ![](./pics/11_2.jpeg){width=50%} |


| ![](./pics/11_3.jpeg){width=50%} | ![](./pics/11_4.jpeg){width=50%} |
