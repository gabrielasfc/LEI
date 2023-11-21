const mongoose = require('mongoose')

var fieldSchema = new mongoose.Schema({
    _id: Number,
    field: String
})

module.exports = mongoose.model('field', fieldSchema)

