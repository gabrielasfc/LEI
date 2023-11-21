const mongoose = require("mongoose");

var acordaoSchema = new mongoose.Schema({
  _id:{type:mongoose.Types.ObjectId},
  Nome: String,
  Desc: String,
});

module.exports = mongoose.model("acordaos_detail", acordaoSchema);
