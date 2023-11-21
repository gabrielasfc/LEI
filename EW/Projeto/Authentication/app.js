var createError = require("http-errors");
var express = require("express");
var session = require("express-session");
var logger = require("morgan");
var cors = require("cors");
var passport = require("passport");
var LocalStrategy = require("passport-local").Strategy;
var GoogleStrategy = require("passport-google-oauth20").Strategy;
var FacebookStrategy = require("passport-facebook");
require("dotenv").config();
const fileUpload = require("express-fileupload");

var mongoose = require("mongoose");
//var mongoDB = "mongodb://127.0.0.1/ProjetoEngWeb";
var mongoDB = process.env.MONGODB_URL;
mongoose.connect(mongoDB, {
  useNewUrlParser: true,
  useUnifiedTopology: true,
  serverSelectionTimeoutMS: 5000,
});

const db = mongoose.connection;
db.on("error", console.error.bind(console, "Erro de conexão ao MongoDB..."));
db.once("open", function () {
  console.log("Conexão ao MongoDB realizada com sucesso...");
});

// passport config
var User = require("./models/user");
passport.use(new LocalStrategy(User.authenticate()));
passport.serializeUser(User.serializeUser());
passport.deserializeUser(User.deserializeUser());

passport.use(
  new FacebookStrategy(
    {
      clientID: "",
      clientSecret: "",
      callbackURL: "http://localhost:8072/login/facebook/callback",
    },
    function (accessToken, refreshToken, profile, cb) {
      console.log(profile)
      User.findOne({ facebookID: profile.id })
        .then((user) => {
          if (user) {
            return cb(null, user);
          } else {
            var nameArray = profile.displayName.split(" ")
            const newUser = new User({
              username: profile.id,
              name: nameArray[0],
              surname: nameArray[1] ? nameArray[1] : "",
              email: "",
              filiation: "",
              level: 10,
              favorites: [],
              dateCreated: new Date().toISOString().substring(0, 19),
              lastAccess: "",
              facebookID: profile.id,
            });

            User.create(newUser)
              .then((response) => {
                return cb(null, newUser);
              })
              .catch((error) => {
                return cb(error);
              });
          }
        })
        .catch((error) => {
          return cb(error);
        });
    }
  )
);

passport.use(
  new GoogleStrategy(
    {
      clientID:
        "",
      clientSecret: "",
      callbackURL: "http://localhost:8072/login/google/callback",
    },
    function (accessToken, refreshToken, profile, cb) {
      User.findOne({ googleID: profile.id })
        .then((user) => {
          if (user) {
            return cb(null, user);
          } else {
            const newUser = new User({
              username: profile.emails[0].value || profile.id,
              name: profile.name.givenName || profile.displayName || "",
              surname: profile.name.familyName || "",
              email: "",
              filiation: "",
              level: 10,
              favorites: [],
              dateCreated: new Date().toISOString().substring(0, 19),
              lastAccess: "",
              googleID: profile.id,
            });

            User.create(newUser)
              .then((response) => {
                return cb(null, newUser);
              })
              .catch((error) => {
                return cb(error);
              });
          }
        })
        .catch((error) => {
          return cb(error);
        });
    }
  )
);

var usersRouter = require("./routes/users");

var app = express();
app.use(fileUpload());
app.use(express.static("assets"));

app.use(cors());
app.use(logger("dev"));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(
  session({
    secret: "olhafodasse",
    resave: false,
    saveUninitialized: true,
  })
);
app.use(passport.initialize());
app.use(passport.session());
app.use("/", usersRouter);

// catch 404 and forward to error handler
app.use(function (req, res, next) {
  next(createError(404));
});

// error handler
app.use(function (err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get("env") === "development" ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.jsonp({ error: err });
});

module.exports = app;
