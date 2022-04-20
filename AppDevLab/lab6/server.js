const express = require("express");
const app = express();
const fs = require("fs");
const xmlparser = require("xml2json");
const xmlf = require("xml-formatter");
const cookieParser = require("cookie-parser");
app.use(cookieParser());

app.use(
  express.json({
    limit: "5mb",
  })
);

var nodemailer = require("nodemailer");

var transporter = nodemailer.createTransport({
  service: "gmail",
  auth: {
    user: process.env.EMAIL,
    pass: process.env.PASS,
  },
});

console.log("Server started on port 8080.");
app.listen(8080);
let otpMap = {};

function sendMail(email, otp) {
  var details = {
    from: process.env.EMAIL,
    to: email, // Receiver's email id
    subject: "Your demo OTP is ", // Subject of the mail.
    text: otp, // Sending OTP
  };

  transporter.sendMail(details, function (error, data) {
    if (error) console.log(error);
    else console.log(data);
  });
}

app.get("/*", async (req, res) => {
  if (req.cookies.token === undefined || req.cookies.token === "") {
    if (req.path.includes("login") || req.path == "/style.css") {
      if (req.path == "/login") {
        res.sendFile(`login.html`, { root: __dirname + "/public" });
      } else
        res.sendFile(`${req.path.slice(1)}`, { root: __dirname + "/public" });
    } else {
      res.sendFile(`login.html`, { root: __dirname + "/public" });
    }
  } else if (req.path === "/") {
    res.sendFile(`index.html`, { root: __dirname + "/public" });
  } else if (req.path.split(".").length == 1) {
    if (!fs.existsSync(__dirname + "/public" + req.path + ".html")) {
      res.sendFile("404.html", { root: __dirname + "/public" });
    }
    res.sendFile(`${req.path.slice(1)}.html`, { root: __dirname + "/public" });
  } else {
    if (!fs.existsSync(__dirname + "/public" + req.path)) {
      res.sendFile("404.html", { root: __dirname + "/public" });
    }
    res.sendFile(req.path.slice(1), { root: __dirname + "/public" });
  }
});

app.post("/login", (req, res) => {
  // retriev the username and password from the request from info.xml via xml2json
  let info = xmlparser.toJson(fs.readFileSync(__dirname + "/info.xml", "utf8"));
  info = JSON.parse(info);
  info = info.document.user;
  console.log(req.body);
  username = req.body.name;
  password = req.body.password;
  let cur_user = info.filter((e) => e.name === username)[0];
  if (cur_user === undefined || cur_user.password !== password) {
    res.json({
      status: 500,
      message: "Invalid username or password",
      body: cur_user,
    });
  } else {
    res.cookie("token", cur_user.id);
    res.json({
      status: 200,
      message: "Successfully logged in",
      redirect: "/",
      body: cur_user,
    });
  }
});

app.post("/user", (req, res) => {
  if (req.cookies.token !== "") {
    // get user corresponding to token from xml file
    let info = xmlparser.toJson(
      fs.readFileSync(__dirname + "/info.xml", "utf8")
    );
    info = JSON.parse(info);
    info = info.document.user;
    let user = info.filter((e) => e.id === req.cookies.token)[0];
    if (user === undefined) {
      res.json({ status: 500, message: "Invalid token" });
    } else {
      res.json({ status: 200, message: "Successfully logged in", body: user });
    }
  } else {
    res.json({ status: 500, message: "Invalid token" });
  }
});

app.post("/logout", (req, res) => {
  res.cookie("token", "");
  res.json({ status: 200, message: "Successfully logged out" });
});

app.post("/register", (req, res) => {
  // retrieve name,rollno,password,fathername,branch,year from req and add it to xml using xmlformatter
  let info = xmlparser.toJson(fs.readFileSync(__dirname + "/info.xml", "utf8"));
  let doc = JSON.parse(info);
  info = doc.document.user;
  // console.log(info);
  if (info.filter((e) => e.id === req.body.id).length === 0) {
    info.push(req.body);
    doc.document.user = info;
    let tempxml = xmlparser.toXml(doc);
    // use xml formatter to format tempxml
    let formattedxml = xmlf(tempxml);
    fs.writeFileSync(__dirname + "/info.xml", formattedxml);
    res.json({
      status: 200,
      message: "Successfully registered",
      body: req.body,
    });
  } else {
    console.log(info.filter((e) => e.id === req.body.id));
    res.json({
      status: 500,
      message: "User already exists",
      body: info.filter((e) => e.id === id)[0],
    });
  }
});

app.post("/edit", (req, res) => {
  // use nodemailer to mail otp to user in cookie
  let info = xmlparser.toJson(fs.readFileSync(__dirname + "/info.xml", "utf8"));
  info = JSON.parse(info);
  info = info.document.user;
  console.log(req.cookies);
  let cur_user = info.filter((e) => e.id === req.cookies.token);
  if (cur_user.length === 0) {
    console.log(cur_user);
    res.json({ status: 500, message: "Invalid token" });
  } else {
    let otp = Math.floor(Math.random() * 10000);
    otpMap[cur_user[0].id] = otp;
    console.log(cur_user[0]);

    // sendMail(cur_user[0].email, otp);

    res.json({
      status: 200,
      message: "OTP sent to " + cur_user[0].email,
      redirect: "/edit",
      body: cur_user[0],
    });
  }
});

app.post("/mail", (req, res) => {
  // send otp from otp store if present, else send empty otp
  if (
    otpMap[req.cookies.token] !== undefined ||
    otpMap[req.cookies.token] !== null
  ) {
    res.json({
      status: 200,
      message: "OTP sent",
      body: otpMap[req.cookies.token],
    });
  } else {
    res.json({ status: 200, message: "OTP not sent", body: "" });
  }
});

app.post("/confirmedit", (req, res) => {
  console.log(req.body);
  if (req.body.otp != otpMap[req.cookies.token]) {
    res.json({ status: 500, message: "Wrong OTP" });
    console.log(req.body.otp, otpMap[req.cookies.token]);
    return;
  }
  req.body.otp = "";
  // replace the user in info.xml with the new user
  let info = xmlparser.toJson(fs.readFileSync(__dirname + "/info.xml", "utf8"));
  let doc = JSON.parse(info);
  info = doc.document.user;
  info = info.map((e) => {
    if (e.id === req.cookies.token) {
      e = { ...e, ...req.body };
      console.log(e);
    }
    return e;
  });
  doc.document.user = info;

  let tempxml = xmlparser.toXml(doc);

  // use xml formatter to format tempxml
  let formattedxml = xmlf(tempxml);
  fs.writeFileSync(__dirname + "/info.xml", formattedxml);
  res.json({ status: 200, message: "Successfully edited", body: req.body });
});
