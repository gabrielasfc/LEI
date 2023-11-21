var Acordao = require("../models/acordao_details");
var mongoose = require('mongoose')

module.exports.list = () => {
    return Acordao.find()
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};

module.exports.addAcordao = (acordao) => {
    acordao["_id"] = new mongoose.Types.ObjectId()
    return Acordao.create(acordao)
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};

module.exports.alteraAcordao = (_id, acordao) => {
    return Acordao.findByIdAndUpdate(
        { _id: _id },
        { $set: acordao },
        { new: true }
    )
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};

module.exports.deleteAcordao = (_id) => {
    return Acordao.deleteOne(
        { _id: _id }
    )
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};
