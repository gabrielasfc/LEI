var Acordao = require("../models/acordao");

module.exports.list = (query, skip, limit) => {
    return Acordao.find(query)
        .skip(skip)
        .limit(limit)
        .sort({_id: -1})
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};

module.exports.getAcordao = (id) => {
    if (isNaN(parseInt(id)))
        throw new Error('O tipo do identificador do registo apresentado não corresponde a um número!')
    return Acordao.findOne({ _id: id })
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};

module.exports.getAcordaosNumber = (query) => {
    return Acordao.find(query)
        .count()
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};

module.exports.addAcordao = (acordao) => {
    return Acordao.find().sort({_id:-1}).limit(1)
        .then((response1) => {
            acordao["_id"] = parseInt(response1[0]._id, 10) + 1
            Acordao.create(acordao)
                .then((response2) => {
                    return response2;
                })
                .catch((error) => {
                    return error;
                });
        })
        .catch((error) => {
            return error
        })

};

module.exports.deleteAcordao = (id) => {
    return Acordao.deleteOne({ _id: id })
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};

module.exports.updateAcordao = (acordao) => {
    console.log(acordao)
    return Acordao.updateOne({ _id: acordao._id }, {$set: acordao})
        .then((response) => {
            return response;
        })
        .catch((error) => {
            return error;
        });
};
