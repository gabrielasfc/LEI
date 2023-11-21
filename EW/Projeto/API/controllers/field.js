var Field = require('../models/field')

module.exports.list = () => {
    return Field.find()
            .then(response => { return response })
            .catch(error => { return error })
}

module.exports.addField = field => {
    return Field.create(field)
            .then(response => { return response })
            .catch(error => { return error })
}

module.exports.deleteField = id => {
    return Field.deleteOne({_id: id})
            .then(response => { return response })
            .catch(error => { return error })
}

module.exports.updateField = field => {
    return Field.updateOne({_id: field._id}, field)
            .then(response => { return response })
            .catch(error => { return error })
}