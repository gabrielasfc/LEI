var Tribunal = require('../models/tribunal')

module.exports.list = () => {
    return Tribunal.find()
            .then(response => { return response })
            .catch(error => { return error })
}

module.exports.getTribunal = id => {
    return Tribunal.findOne({_id: id})
            .then(response => { return response })
            .catch(error => { return error })
}

module.exports.addTribunal = t => {
    return Tribunal.create(t)
            .then(response => { return response })
            .catch(error => { return error })
}

module.exports.deleteTribunal = id => {
    return Tribunal.deleteOne({_id: id})
            .then(response => { return response })
            .catch(error => { return error })
}

module.exports.updateTribunal = t => {
    return Tribunal.updateOne({_id: t._id}, t)
            .then(response => { return response })
            .catch(error => { return error })
}