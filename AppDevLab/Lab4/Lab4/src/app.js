const DB_URL = "mongodb://localhost:27017/lab4";
const express = require("express");
const app = express();
const mongoose = require("mongoose");
const Registration = require("./Registration");

mongoose.connect(DB_URL, {
  useUnifiedTopology: true,
  useNewUrlParser: true,
});

//BODY PARSER
app.use(express.urlencoded({ extended: false }));
app.use(express.raw());
app.use(express.json());

let db = mongoose.connection;

db.once("open", () => {
  console.log("Connected To Database");
});

db.on("error", (err) => {
  console.log(err);
});

// server client as static files
app.use(express.static("client"));

app.get("/api/summary", async (req, res) => {
  try {
    const registrations = await Registration.find({});
    res.send(registrations);
  } catch (err) {
    console.log(err);
    res.status(400).send(err);
  }
});

app.post("/api/register", async (req, res) => {
  console.log(req.body);
  try {
    if (!req.body._id) {
      const registration = new Registration(req.body);
      await registration.save();
      res.send(registration);
    } else {
      const registration = await Registration.findOneAndUpdate(
        { _id: req.body._id },
        req.body,
        { upsert: true, new: true }
      );
      res.send(registration);
    }
  } catch (err) {
    console.log(err);
    res.status(400).send(err);
  }
});

app.delete("/api/delete", async (req, res) => {
  try {
    const registration = await Registration.findByIdAndDelete(req.body._id);
    res.send(registration);
  } catch (err) {
    console.log(err);
    res.status(400).send(err);
  }
});

app.use((req, res, next) => {
  res.status(404).json({ message: "Enter Correct Route" });
});
module.exports = app;
